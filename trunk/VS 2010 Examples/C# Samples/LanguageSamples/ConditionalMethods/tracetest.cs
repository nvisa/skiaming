// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
//版权所有(C) Microsoft Corporation。保留所有权利。

// TraceTest.cs
// 编译时使用：/reference:CondMethod.dll
// 参数：A B C
using System; 
using TraceFunctions; 

public class TraceClient 
{
   public static void Main(string[] args) 
   { 
      Trace.Message("Main Starting"); 
   
      if (args.Length == 0) 
      { 
          Console.WriteLine("No arguments have been passed"); 
      } 
      else 
      { 
          for( int i=0; i < args.Length; i++)    
          { 
              Console.WriteLine("Arg[{0}] is [{1}]",i,args[i]); 
          } 
      } 

       Trace.Message("Main Ending"); 
   } 
}

