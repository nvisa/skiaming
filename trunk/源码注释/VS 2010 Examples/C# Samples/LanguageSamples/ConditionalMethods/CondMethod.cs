// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
//版权所有(C) Microsoft Corporation。保留所有权利。

// CondMethod.cs
// 编译时使用：/target:library /d:DEBUG
using System; 
using System.Diagnostics;
namespace TraceFunctions 
{
   public class Trace 
   { 
       [Conditional("DEBUG")] 
       public static void Message(string traceMessage) 
       { 
           Console.WriteLine("[TRACE] - " + traceMessage); 
       } 
   } 
}

