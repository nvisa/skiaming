// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
//版权所有(C) Microsoft Corporation。保留所有权利。

using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;

using nwind;

namespace LinqToNorthwind {
    public static class Samples {

        public static void Sample1(Northwind db) 
        { 
            // 使用 Where() 仅查找匹配的元素
            IEnumerable<Customer> q = db.Customers.Where(c => c.City == "London");
            ObjectDumper.Write(q, 0);
        }

        public static void Sample2(Northwind db)
        {
            // 使用 First() 替换 Where()，以查找第一个元素，或仅查找一个元素
            Customer cust = db.Customers.First(c => c.CustomerID == "ALFKI");
            ObjectDumper.Write(cust, 0);
        }

        public static void Sample3(Northwind db) 
        {
            // 使用 Select() 映射/投影结果
            var q = db.Customers.Select(c => c.ContactName);
            ObjectDumper.Write(q, 0);
        }

        public static void Sample4(Northwind db)
        {
            // 使用匿名类构造函数仅检索特定数据
            var q = db.Customers.Select(c => new {c.ContactName, c.Phone});
            ObjectDumper.Write(q, 0);
        }

        public static void Sample5(Northwind db) 
        {
            // 结合使用 Where() 和 Select() 进行一般查询
            var q = db.Customers.Where(c => c.City == "London").Select(c => c.ContactName);
            ObjectDumper.Write(q, 0);
        }

        public static void Sample6(Northwind db) 
        { 
            // 使用 SelectMany() 来扁平化集合
            IEnumerable<Order> q = db.Customers.SelectMany(c => c.Orders);
            ObjectDumper.Write(q, 0);
        }

        public static void Sample7(Northwind db) 
        {
            // 使用查询表达式简化通用 select/where 模式
            var q = from c in db.Customers
                    from o in c.Orders
                    where c.City == "London"
                    select new {c.ContactName, o.OrderDate};
            ObjectDumper.Write(q, 0);
        }

        public static void Sample8(Northwind db) 
        {
            // 使用 orderby 对结果进行排序
            var q = from c in db.Customers orderby c.City, c.ContactName select c;
            ObjectDumper.Write(q, 0);
        }

        public static void Sample9(Northwind db) 
        {
            // 使用 group x by y 来产生一系列组分区
            var q = from p in db.Products group p by p.CategoryID into Group select new {CategoryID=Group.Key, Group};
            ObjectDumper.Write(q, 1);
        }

        public static void Sample10(Northwind db) 
        {
            // 使用 group-by 和 Min()/Max() 之类的聚合函数对组分区计算值
            var q = from p in db.Products
                    group p by p.CategoryID into g
                    select new {
                        Category = g.Key,
                        MinPrice = g.Min(p => p.UnitPrice),
                        MaxPrice = g.Max(p => p.UnitPrice)
                        };
            ObjectDumper.Write(q, 1);
        }

        public static void Sample11(Northwind db) 
        {
            // 使用 Any() 确定集合是否至少有一个元素，或至少有一个匹配条件的元素
            var q = from c in db.Customers
                    where c.Orders.Any()
                    select c;
            ObjectDumper.Write(q, 0);
        }

        public static void Sample12(Northwind db) 
        {
            // 使用 All() 确定集合的所有元素是否都匹配某个条件(或者确定集合是否是空的!)
            var q = from c in db.Customers
                    where c.Orders.All(o => o.ShipCity == c.City)
                    select c;
            ObjectDumper.Write(q, 0);
        }

        public static void Sample13(Northwind db) 
        {
            // 使用 Take(n) 将序列限制为仅含有前 n 个元素
            var q = db.Customers.OrderBy(c => c.ContactName).Take(5);
            ObjectDumper.Write(q, 0);
        }

        public static void Sample14(Northwind db) 
        {
            // 使用 SubmitChanges() 将所有更改提交回数据库
            Customer cust = db.Customers.First(c => c.CustomerID == "ALFKI");
            cust.ContactTitle = "Sith Lord";
            // 其他更改 ...
            db.SubmitChanges();
        }
        
        public static void Sample15(Northwind db) 
        {
            using(System.Transactions.TransactionScope ts = new System.Transactions.TransactionScope()) {            
                // 使用 SubmitChanges() 将所有更改提交回数据库
                Customer cust = db.Customers.First(c => c.CustomerID == "ALFKI");
                cust.ContactTitle = "Sith Lord";
                // 其他更改...
                db.SubmitChanges();
                ts.Complete();
            }
        }        
    }
}
