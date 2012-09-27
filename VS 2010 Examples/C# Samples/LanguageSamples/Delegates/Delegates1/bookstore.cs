// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
//版权所有(C) Microsoft Corporation。保留所有权利。

// bookstore.cs
using System;

// 用于处理书店的一组类:
namespace Bookstore 
{
   using System.Collections;

   // 描述图书列表中的一本书:
   public struct Book
   {
      public string Title;        // 书名。
      public string Author;       // 作者。
      public decimal Price;       // 价格。
      public bool Paperback;      // 是否为平装本？

      public Book(string title, string author, decimal price, bool paperBack)
      {
         Title = title;
         Author = author;
         Price = price;
         Paperback = paperBack;
      }
   }

   // 声明一个用于处理书的委托类型:
   public delegate void ProcessBookDelegate(Book book);

   // 维护一个图书数据库。
   public class BookDB
   {
      // 列出数据库中的所有图书:
      ArrayList list = new ArrayList();   

      // 向数据库中添加图书:
      public void AddBook(string title, string author, decimal price, bool paperBack)
      {
         list.Add(new Book(title, author, price, paperBack));
      }

      // 对每本平装图书调用传入委托来进行处理: 
      public void ProcessPaperbackBooks(ProcessBookDelegate processBook)
      {
         foreach (Book b in list) 
         {
            if (b.Paperback)
            // 调用该委托：
               processBook(b);
         }
      }
   }
}

// 使用 Bookstore 类：
namespace BookTestClient
{
   using Bookstore;

   // 计算图书总价格和平均价格的类：
   class PriceTotaller
   {
      int countBooks = 0;
      decimal priceBooks = 0.0m;

      internal void AddBookToTotal(Book book)
      {
         countBooks += 1;
         priceBooks += book.Price;
      }

      internal decimal AveragePrice()
      {
         return priceBooks / countBooks;
      }
   }

   // 测尝试书数据库的类：
   class Test
   {
      // 打印书名。
      static void PrintTitle(Book b)
      {
         Console.WriteLine("   {0}", b.Title);
      }

      // 下面开始执行。
      static void Main()
      {
         BookDB bookDB = new BookDB();

         // 用一些书初始化数据库：
         AddBooks(bookDB);      

         // 打印所有平装本的书名：
         Console.WriteLine("Paperback Book Titles:");
         // 创建一个与静态方法 Test.PrintTitle 关联的
         // 新委托对象：
         bookDB.ProcessPaperbackBooks(new ProcessBookDelegate(PrintTitle));

         // 使用 PriceTotaller 对象
         // 获取平装本的平均价格：
         PriceTotaller totaller = new PriceTotaller();
         // 创建一个与对象 totaller 的非静态方法
         // AddBookToTotal 关联的新委托对象：
         bookDB.ProcessPaperbackBooks(new ProcessBookDelegate(totaller.AddBookToTotal));
         Console.WriteLine("Average Paperback Book Price: ${0:#.##}",
            totaller.AveragePrice());
      }

      // 用一些测尝试书初始化图书数据库：
      static void AddBooks(BookDB bookDB)
      {
         bookDB.AddBook("The C Programming Language", 
            "Brian W. Kernighan and Dennis M. Ritchie", 19.95m, true);
         bookDB.AddBook("The Unicode Standard 2.0", 
            "The Unicode Consortium", 39.95m, true);
         bookDB.AddBook("The MS-DOS Encyclopedia", 
            "Ray Duncan", 129.95m, false);
         bookDB.AddBook("Dogbert's Clues for the Clueless", 
            "Scott Adams", 12.00m, true);
      }
   }
}

