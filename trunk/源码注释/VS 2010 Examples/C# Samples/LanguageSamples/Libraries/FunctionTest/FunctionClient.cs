// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
//版权所有(C) Microsoft Corporation。保留所有权利。

// FunctionClient.cs
// 编译时使用：/reference:DigitCounter.dll;Factorial.dll
// 参数：3 5 10
using System; 
// 下面的 using 指令使 Functions
// 命名空间中定义的类型可用于此编译单元：
using Functions;
class FunctionClient 
{ 
    public static void Main(string[] args) 
    { 
        Console.WriteLine("Function Client"); 

        if ( args.Length == 0 ) 
        {
            Console.WriteLine("Usage: FunctionTest ... "); 
            return; 
        } 

        for ( int i = 0; i < args.Length; i++ ) 
        { 
            int num = Int32.Parse(args[i]); 
            Console.WriteLine(
               "The Digit Count for String [{0}] is [{1}]", 
               args[i], 
               // 调用 DigitCount 类中的
               // NumberOfDigits 静态方法：
               DigitCount.NumberOfDigits(args[i])); 
            Console.WriteLine(
               "The Factorial for [{0}] is [{1}]", 
                num,
               // 调用 Factorial 类中的 Calc 静态方法：
                Factorial.Calc(num) ); 
        } 
    } 
}

