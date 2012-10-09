// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
//版权所有(C) Microsoft Corporation。保留所有权利。

// CSharpServer.cs
// 编译时使用：/target:library
// 生成后命令：regasm CSharpServer.dll /tlb:CSharpServer.tlb

using System;
using System.Runtime.InteropServices;
namespace CSharpServer
{
   // 由于 .NET Framework 接口和组件类的行为必须与 
   // 对象一样，因此必须为其提供 GUID。
   [Guid("DBE0E8C4-1C61-41f3-B6A4-4E2F353D3D05")]
   public interface IManagedInterface
   {
      int PrintHi(string name);
   }

   [Guid("C6659361-1625-4746-931C-36014B146679")]
   public class InterfaceImplementation : IManagedInterface
   {
      public int PrintHi(string name)
      {
         Console.WriteLine("Hello, {0}!", name);
         return 33;
      }
   }
}

