// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
//版权所有(C) Microsoft Corporation。保留所有权利。

using System;
using System.Threading;

// Fibonacci 类为使用辅助
// 线程执行长时间的 Fibonacci(N) 计算提供了一个接口。
// N 是为 Fibonacci 构造函数提供的，此外还提供了
// 操作完成时对象发出的事件信号。
// 然后，可以使用 FibOfN 属性来检索结果。
public class Fibonacci
{
    public Fibonacci(int n, ManualResetEvent doneEvent)
    {
        _n = n;
        _doneEvent = doneEvent;
    }

    // 供线程池使用的包装方法。
    public void ThreadPoolCallback(Object threadContext)
    {
        int threadIndex = (int)threadContext;
        Console.WriteLine("thread {0} started...", threadIndex);
        _fibOfN = Calculate(_n);
        Console.WriteLine("thread {0} result calculated...", threadIndex);
        _doneEvent.Set();
    }

    // 计算第 N 个斐波纳契数的递归方法。
    public int Calculate(int n)
    {
        if (n <= 1)
        {
            return n;
        }
        else
        {
            return Calculate(n - 1) + Calculate(n - 2);
        }
    }

    public int N { get { return _n; } }
    private int _n;

    public int FibOfN { get { return _fibOfN; } }
    private int _fibOfN;

    ManualResetEvent _doneEvent;
}

public class ThreadPoolExample
{
    static void Main()
    {
        const int FibonacciCalculations = 10;

        // 每个 Fibonacci 对象使用一个事件
        ManualResetEvent[] doneEvents = new ManualResetEvent[FibonacciCalculations];
        Fibonacci[] fibArray = new Fibonacci[FibonacciCalculations];
        Random r = new Random();

        // 使用 ThreadPool 配置和启动线程：
        Console.WriteLine("launching {0} tasks...", FibonacciCalculations);
        for (int i = 0; i < FibonacciCalculations; i++)
        {
            doneEvents[i] = new ManualResetEvent(false);
            Fibonacci f = new Fibonacci(r.Next(20,40), doneEvents[i]);
            fibArray[i] = f;
            ThreadPool.QueueUserWorkItem(f.ThreadPoolCallback, i);
        }

        // 等待池中的所有线程执行计算...
        WaitHandle.WaitAll(doneEvents);
        Console.WriteLine("Calculations complete.");

        // 显示结果...
        for (int i= 0; i<FibonacciCalculations; i++)
        {
            Fibonacci f = fibArray[i];
            Console.WriteLine("Fibonacci({0}) = {1}", f.N, f.FibOfN);
        }
    }
}