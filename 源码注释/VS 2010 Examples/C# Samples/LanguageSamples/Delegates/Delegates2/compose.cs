// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
//版权所有(C) Microsoft Corporation。保留所有权利。

// compose.cs
using System;

delegate void MyDelegate(string s);

class MyClass
{
    public static void Hello(string s)
    {
        Console.WriteLine("  Hello, {0}!", s);
    }

    public static void Goodbye(string s)
    {
        Console.WriteLine("  Goodbye, {0}!", s);
    }

    public static void Main()
    {
        MyDelegate a, b, c, d;

        // 创建引用 Hello 方法的 
        // 委托对象 a：
        a = new MyDelegate(Hello);
        // 创建引用 Goodbye 方法的 
        // 委托对象 b：
        b = new MyDelegate(Goodbye);
        // a 和 b 两个委托组成 c， 
        // c 将按顺序调用这两个方法：
        c = a + b;
        // 从组合委托中移除 a 而保留 d， 
        // 后者仅调用 Goodbye 方法：
        d = c - a;

        Console.WriteLine("Invoking delegate a:");
        a("A");
        Console.WriteLine("Invoking delegate b:");
        b("B");
        Console.WriteLine("Invoking delegate c:");
        c("C");
        Console.WriteLine("Invoking delegate d:");
        d("D");
    }
}

