// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
//版权所有(C) Microsoft Corporation。保留所有权利。

using System;
using System.Threading;
using System.Collections;
using System.Collections.Generic;

// 将线程同步事件封装在此类中， 
// 以便于将这些事件传递给 Consumer 和
// Producer 类。
public class SyncEvents
{
    public SyncEvents()
    {
        // AutoResetEvent 用于“新项”事件，因为
        // 我们希望每当使用者线程响应此事件时，
        // 此事件就会自动重置。
        _newItemEvent = new AutoResetEvent(false);

        // ManualResetEvent 用于“退出”事件，因为
        // 我们希望发出此事件的信号时有多个线程响应。
        // 如果使用 AutoResetEvent，事件
        // 对象将在单个线程作出响应之后恢复为 
        // 未发信号的状态，而其他线程将
        // 无法终止。
        _exitThreadEvent = new ManualResetEvent(false);

        // 这两个事件也放在一个 WaitHandle 数组中，以便
        // 使用者线程可以使用 WaitAny 方法
        // 阻塞这两个事件。
        _eventArray = new WaitHandle[2];
        _eventArray[0] = _newItemEvent;
        _eventArray[1] = _exitThreadEvent;
    }

    // 公共属性允许对事件进行安全访问。
    public EventWaitHandle ExitThreadEvent
    {
        get { return _exitThreadEvent; }
    }
    public EventWaitHandle NewItemEvent
    {
        get { return _newItemEvent; }
    }
    public WaitHandle[] EventArray
    {
        get { return _eventArray; }
    }

    private EventWaitHandle _newItemEvent;
    private EventWaitHandle _exitThreadEvent;
    private WaitHandle[] _eventArray;
}

// Producer 类（使用一个辅助线程）
// 将项异步添加到队列中，共添加 20 个项。
public class Producer 
{
    public Producer(Queue<int> q, SyncEvents e)
    {
        _queue = q;
        _syncEvents = e;
    }
    public void ThreadRun()
    {
        int count = 0;
        Random r = new Random();
        while (!_syncEvents.ExitThreadEvent.WaitOne(0, false))
        {
            lock (((ICollection)_queue).SyncRoot)
            {
                while (_queue.Count < 20)
                {
                    _queue.Enqueue(r.Next(0, 100));
                    _syncEvents.NewItemEvent.Set();
                    count++;
                }
            }
        }
        Console.WriteLine("Producer thread: produced {0} items", count);
    }
    private Queue<int> _queue;
    private SyncEvents _syncEvents;
}

// Consumer 类通过自己的辅助线程使用队列
// 中的项。Producer 类使用 NewItemEvent 
// 将新项通知 Consumer 类。
public class Consumer
{
    public Consumer(Queue<int> q, SyncEvents e)
    {
        _queue = q;
        _syncEvents = e;
    }
    public void ThreadRun()
    {
        int count = 0;
        while (WaitHandle.WaitAny(_syncEvents.EventArray) != 1)
        {
            lock (((ICollection)_queue).SyncRoot)
            {
                int item = _queue.Dequeue();
            }
            count++;
        }
        Console.WriteLine("Consumer Thread: consumed {0} items", count);
    }
    private Queue<int> _queue;
    private SyncEvents _syncEvents;
}

public class ThreadSyncSample
{
    private static void ShowQueueContents(Queue<int> q)
    {
        // 对集合进行枚举本来就不是线程安全的，
        // 因此在整个枚举过程中锁定集合以防止
        // 使用者和制造者线程修改内容
        // 是绝对必要的。（此方法仅由
        // 主线程调用。）
        lock (((ICollection)q).SyncRoot)
        {
            foreach (int i in q)
            {
                Console.Write("{0} ", i);
            }
        }
        Console.WriteLine();
    }

    static void Main()
    {
        // 配置结构，该结构包含线程同步
        // 所需的事件信息。
        SyncEvents syncEvents = new SyncEvents();

        // 泛型队列集合用于存储要制造和使用的
        // 项。此例中使用的是“int”。
        Queue<int> queue = new Queue<int>();

        // 创建对象，一个用于制造项，一个用于
        // 使用项。将队列和线程同步事件传递给
        // 这两个对象。
        Console.WriteLine("Configuring worker threads...");
        Producer producer = new Producer(queue, syncEvents);
        Consumer consumer = new Consumer(queue, syncEvents);

        // 为制造者对象和使用者对象创建线程
        // 对象。此步骤并不创建或启动
        // 实际线程。
        Thread producerThread = new Thread(producer.ThreadRun);
        Thread consumerThread = new Thread(consumer.ThreadRun);

        // 创建和启动两个线程。
        Console.WriteLine("Launching producer and consumer threads...");        
        producerThread.Start();
        consumerThread.Start();

        // 为制造者线程和使用者线程设置 10 秒的运行时间。
        // 使用主线程（执行此方法的线程）
        // 每隔 2.5 秒显示一次队列内容。
        for (int i = 0; i < 4; i++)
        {
            Thread.Sleep(2500);
            ShowQueueContents(queue);
        }

        // 向使用者线程和制造者线程发出终止信号。
        // 这两个线程都会响应，由于 ExitThreadEvent 是
        // 手动重置的事件，因此除非显式重置，否则将保持“设置”。
        Console.WriteLine("Signaling threads to terminate...");
        syncEvents.ExitThreadEvent.Set();

        // 使用 Join 阻塞主线程，首先阻塞到制造者线程
        // 终止，然后阻塞到使用者线程终止。
        Console.WriteLine("main thread waiting for threads to finish...");
        producerThread.Join();
        consumerThread.Join();
    }
}
