// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
//版权所有(C) Microsoft Corporation。保留所有权利。

// tokens2.cs
using System;
using System.Collections;

public class Tokens: IEnumerable
{
   private string[] elements;

   Tokens(string source, char[] delimiters)
   {
      elements = source.Split(delimiters);
   }

   // IEnumerable 接口实现:

   public TokenEnumerator GetEnumerator() // 非 IEnumerable 版本
   {
      return new TokenEnumerator(this);
   }

   IEnumerator IEnumerable.GetEnumerator() // IEnumerable 版本
   {
      return (IEnumerator) new TokenEnumerator(this);
   }

   // 内部类实现 IEnumerator 接口:

   public class TokenEnumerator: IEnumerator
   {
      private int position = -1;
      private Tokens t;

      public TokenEnumerator(Tokens t)
      {
         this.t = t;
      }

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

      public void Reset()
      {
         position = -1;
      }

      public string Current // 非 IEnumerator 版本: 类型安全
      {
         get
         {
            return t.elements[position];
         }
      }

      object IEnumerator.Current // IEnumerator 版本: 返回对象
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
      Tokens f = new Tokens("This is a well-done program.", 
         new char [] {' ','-'});
      foreach (string item in f) // 要将 string 更改为 int
      {
         Console.WriteLine(item);
      }
   }
}

