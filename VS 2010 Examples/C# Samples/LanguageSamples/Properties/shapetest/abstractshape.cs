// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
//版权所有(C) Microsoft Corporation。保留所有权利。

// abstractshape.cs
// 编译时使用：/target:library
// csc /target:library abstractshape.cs
using System;

public abstract class Shape
{
   private string myId;

   public Shape(string s)
   {
      Id = s;   // 调用 Id 属性的 set 访问器
   }

   public string Id
   {
      get 
      {
         return myId;
      }

      set
      {
         myId = value;
      }
   }

   // Area 为只读属性 - 只需要 get 访问器：
   public abstract double Area
   {
      get;
   }

   public override string ToString()
   {
      return Id + " Area = " + string.Format("{0:F2}",Area);
   }
}

