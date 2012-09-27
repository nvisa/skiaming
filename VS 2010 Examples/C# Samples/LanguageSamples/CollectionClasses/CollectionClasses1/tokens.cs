// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
//版权所有(C) Microsoft Corporation。保留所有权利。

// tokens.cs
using System;
// 使命名空间 System.Collections 可用:
using System.Collections;

// 声明 Tokens 类:
public class Tokens : IEnumerable
{
   private string[] elements;

   Tokens(string source, char[] delimiters)
   {
      // 将字符串分析为标记:
      elements = source.Split(delimiters);
   }

   // IEnumerable 接口实现:
   // 声明 IEnumerable 所需的
   // GetEnumerator() 方法
   public IEnumerator GetEnumerator()
   {
      return new TokenEnumerator(this);
   }

   // 内部类实现 IEnumerator 接口:
   private class TokenEnumerator : IEnumerator
   {
      private int position = -1;
      private Tokens t;

      public TokenEnumerator(Tokens t)
      {
         this.t = t;
      }

      // 声明 IEnumerator 所需的 MoveNext 方法:
      public bool MoveNext()
      {
         if (position < t.elements.Length - 1)
         {
            position++;
            return true;
         }
         else
         {
            return false;
         }
      }

      // 声明 IEnumerator 所需的 Reset 方法:
      public void Reset()
      {
         position = -1;
      }

      // 声明 IEnumerator 所需的 Current 属性:
      public object Current
      {
         get
         {
            return t.elements[position];
         }
      }
   }

   // 测试标记 TokenEnumerator

   static void Main()
   {
      // 通过将字符串分解为标记来测试标记:
      Tokens f = new Tokens("This is a well-done program.", 
         new char[] {' ','-'});
      foreach (string item in f)
      {
         Console.WriteLine(item);
      }
   }
}

