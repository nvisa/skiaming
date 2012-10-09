// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
using System;
using IronPython.Hosting;
using Microsoft.Scripting.Hosting;

namespace PythonSample
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Loading helloworld.py...");

            ScriptRuntime py = Python.CreateRuntime();
            dynamic helloworld = py.UseFile("helloworld.py");

            Console.WriteLine("helloworld.py loaded!");

            for (int i = 0; i < 1000; i++)
            {
                Console.WriteLine(helloworld.welcome("Employee #{0}"), i);
            }
            Console.ReadLine();
        }
    }
}
