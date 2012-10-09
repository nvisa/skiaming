// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
//版权所有(C) Microsoft Corporation。保留所有权利。

// XMLsample.cs
// 编译时使用：/doc:XMLsample.xml
using System;

/// <summary>
/// 此处显示类级别摘要文档。 </summary>
/// <remarks>
/// 较长的注释可通过 remarks 标记与类型或成员 
/// 关联 </remarks>
public class SomeClass
{
   /// <summary>
   /// Name 属性的存储区</summary>
   private string myName = null;

   /// <summary>
   /// 类构造函数。 </summary>
   public SomeClass()
   {
       // TODO: 在此处添加构造函数逻辑
   }
   
   /// <summary>
   /// Name 属性 </summary>
   /// <value>
   /// value 标记用于描述属性值</value>
   public string Name
   {
      get 
      {
         if ( myName == null )
         {
            throw new Exception("Name is null");
         }
             
         return myName;
      }
   }

   /// <summary>
   /// SomeMethod 的说明。</summary>
   /// <param name="s"> 此处显示 s 的参数说明</param>
   /// <seealso cref="String">
   /// 可以在任何标记上使用 cref 特性来引用类型或成员
   /// 编译器将检查该引用是否存在。 </seealso>
   public void SomeMethod(string s)
   {
   }

   /// <summary>
   /// 一些其他方法。 </summary>
   /// <returns>
   /// 返回结果通过 returns 标记描述。</returns>
   /// <seealso cref="SomeMethod(string)">
   /// 注意引用特定方法的 cref 特性的使用 </seealso>
   public int SomeOtherMethod()
   {
      return 0;
   }

   /// <summary>
   /// 应用程序的入口点。
   /// </summary>
   /// <param name="args"> 命令行参数列表</param>
   public static int Main(String[] args)
   {
      // TODO: 在此处添加启动应用程序的代码

       return 0;
   }
}

