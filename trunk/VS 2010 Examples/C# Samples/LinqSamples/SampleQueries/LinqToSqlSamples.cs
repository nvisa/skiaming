// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
//版权所有(C) Microsoft Corporation。保留所有权利。

using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Data.Linq;
using nwind;
using SampleSupport;
using System.IO;
using System.Windows.Forms;
using System.Data.SqlClient;
using System.Transactions;
using System.Linq.Expressions;
using System.Data.Linq.Provider;
using System.Data.Linq.Mapping;
using System.Reflection;
using System.Data.Linq.SqlClient;
using System.Xml.Linq;

namespace SampleQueries {
    [Title("101 个 Linq To Sql 查询示例")]
    [Prefix("LinqToSql")]
    public class LinqToSqlSamples : SampleHarness {
        
        private readonly static string dbPath = Path.GetFullPath(Path.Combine(Application.StartupPath, @"..\..\Data\NORTHWND.MDF"));
        private readonly static string sqlServerInstance = @".\SQLEXPRESS";
        private readonly static string connString = "AttachDBFileName='" + dbPath + "';Server='" + sqlServerInstance + "';user instance=true;Integrated Security=SSPI;Connection Timeout=60";

        private Northwind db;

        [Category("Where")]
        [Title("Where - 1")]
        [Description("此示例使用 WHERE 筛选在伦敦的客户。")]
        public void LinqToSqlWhere01() {
            var q =
                from c in db.Customers
                where c.City == "London"
                select c;
            ObjectDumper.Write(q);
        }

        [Category("Where")]
        [Title("Where - 2")]
        [Description("此示例使用 WHERE 筛选" +
                     "1994 年或之后雇用的雇员。")]
        public void LinqToSqlWhere02() {
            var q =
                from e in db.Employees
                where e.HireDate >= new DateTime(1994, 1, 1)
                select e;

            ObjectDumper.Write(q);
        }

        [Category("Where")]
        [Title("Where - 3")]
        [Description("此示例使用 WHERE 筛选库存量在订货点水平之下" +
                     "但未断货的产品。")]
        public void LinqToSqlWhere03() {
            var q =
                from p in db.Products
                where p.UnitsInStock <= p.ReorderLevel && !p.Discontinued
                select p;

            ObjectDumper.Write(q);
        }

        [Category("Where")]
        [Title("Where - 4")]
        [Description("此示例使用 WHERE 筛选出 UnitPrice 大于 10 或" +
                     "已停产的产品。")]
        public void LinqToSqlWhere04() {
            var q =
                from p in db.Products
                where p.UnitPrice > 10m || p.Discontinued
                select p;

            ObjectDumper.Write(q, 0);
        }

        [Category("Where")]
        [Title("Where - 5")]
        [Description("此示例调用 WHERE 两次以筛选出 UnitPrice 大于 10" +
                     "且已停产的产品。")]
        public void LinqToSqlWhere05() {
            var q =
                db.Products.Where(p=>p.UnitPrice > 10m).Where(p=>p.Discontinued);

            ObjectDumper.Write(q, 0);
        }

        [Category("Where")]
        [Title("First - 简单用法")]
        [Description("此示例使用 First 选择表中的第一个发货方。")]
        public void LinqToSqlWhere06() {
            Shipper shipper = db.Shippers.First();
            ObjectDumper.Write(shipper, 0);
        }

        [Category("Where")]
        [Title("First - 元素")]
        [Description("此示例使用 First 选择 CustomerID 为“BONAP”的单个客户。")]
        public void LinqToSqlWhere07() {
            Customer cust = db.Customers.First(c => c.CustomerID == "BONAP");
            ObjectDumper.Write(cust, 0);
        }

        [Category("Where")]
        [Title("First - 条件")]
        [Description("此示例使用 First 选择运费大于 10.00 的订单。")]
        public void LinqToSqlWhere08() {
            Order ord = db.Orders.First(o => o.Freight > 10.00M);
            ObjectDumper.Write(ord, 0);
        }

        [Category("Select/Distinct")]
        [Title("Select - 简单用法")]
        [Description("此示例使用 SELECT 返回" +
                     "仅含客户联系人姓名的序列。")]
        public void LinqToSqlSelect01() {
            var q =
                from c in db.Customers
                select c.ContactName;

            ObjectDumper.Write(q);
        }

        [Category("Select/Distinct")]
        [Title("Select - 匿名类型 1")]
        [Description("此示例使用 SELECT 和匿名类型返回" +
                     "仅含客户联系人姓名和电话号码的序列。")]
        public void LinqToSqlSelect02() {
            var q =
                from c in db.Customers
                select new {c.ContactName, c.Phone};

            ObjectDumper.Write(q);
        }

        [Category("Select/Distinct")]
        [Title("Select - 匿名类型 2")]
        [Description("此示例使用 SELECT 和匿名类型返回" +
                     "仅含雇员姓名和电话号码的序列，" +
                     "并将 FirstName 和 LastName 字段合并为一个字段“Name”， " +
                     "此外在所得的序列中将 HomePhone 字段重命名为 Phone。")]
        public void LinqToSqlSelect03() {
            var q =
                from e in db.Employees
                select new {Name = e.FirstName + " " + e.LastName, Phone = e.HomePhone};

            ObjectDumper.Write(q, 1);
        }

        [Category("Select/Distinct")]
        [Title("Select - 匿名类型 3")]
        [Description("此示例使用 SELECT 和匿名类型返回" +
                     "所有产品的 ID 以及 HalfPrice" +
                     "(设置为产品单价除以 2 所得的值)" +
                     "的序列。")]
        public void LinqToSqlSelect04() {
            var q =
                from p in db.Products
                select new {p.ProductID, HalfPrice = p.UnitPrice / 2};
            ObjectDumper.Write(q, 1);
        }

        [Category("Select/Distinct")]
        [Title("Select - 条件")]
        [Description("此示例使用 SELECT 和条件语句返回产品名称" +
                     " 和产品供货状态的序列。")]
        public void LinqToSqlSelect05() {
            var q =
                from p in db.Products
                select new {p.ProductName, Availability = p.UnitsInStock - p.UnitsOnOrder < 0 ? "Out Of Stock": "In Stock"};

            ObjectDumper.Write(q, 1);
        }

        [Category("Select/Distinct")]
        [Title("Select - 已命名类型")]
        [Description("此示例使用 SELECT 和已知类型返回雇员姓名的序列。")]
        public void LinqToSqlSelect06() {
            var q =
                from e in db.Employees                
                select new Name {FirstName = e.FirstName, LastName = e.LastName};

            ObjectDumper.Write(q, 1);
        }

        [Category("Select/Distinct")]
        [Title("Select - 筛选")]
        [Description("此示例使用 SELECT 和 WHERE 返回" +
                     "仅含伦敦客户联系人姓名的序列。")]
        public void LinqToSqlSelect07() {
            var q =
                from c in db.Customers
                where c.City == "London"
                select c.ContactName;

            ObjectDumper.Write(q);
        }

        [Category("Select/Distinct")]
        [Title("Select - 整形")]
        [Description("此示例使用 SELECT 和匿名类型返回" +
                     "有关客户的数据的整形子集。")]
        public void LinqToSqlSelect08() {
            var q =
                from c in db.Customers
                select new {
                    c.CustomerID,
                    CompanyInfo = new {c.CompanyName, c.City, c.Country},
                    ContactInfo = new {c.ContactName, c.ContactTitle}
                };

            ObjectDumper.Write(q, 1);
        }

        [Category("Select/Distinct")]
        [Title("Select - 嵌套")]
        [Description("此示例使用嵌套查询返回" +
                     "所有订单及其 OrderID 的序列、" +
                     "打折订单中项目的子序列以及免送货" +
                     "所省下的金额。")]
        public void LinqToSqlSelect09() {
            var q =
                from o in db.Orders
                select new {
                    o.OrderID,
                    DiscountedProducts =
                        from od in o.OrderDetails
                        where od.Discount > 0.0
                        select od,
                    FreeShippingDiscount = o.Freight
                };

            ObjectDumper.Write(q, 1);
        }

        // 基于其国家/地区将电话号码转换为
        //国际格式的电话转换器。
        // 对于来自 Northwind 数据库的电话号码， 
        //此示例仅支持美国和英国格式。
        public string PhoneNumberConverter(string Country, string Phone)
        {
            Phone = Phone.Replace(" ", "").Replace(")", ")-");
            switch (Country)
            {
                case "USA":
                    return "1-" + Phone;
                case "UK":
                    return "44-" + Phone;
                default:
                    return Phone;
            }
        }

        [Category("Select/Distinct")]
        [Title("Select - 本地方法调用 1")]
        [Description("此示例使用" + 
                     "“PhoneNumberConverter”的本地方法调用将电话号码" + 
                     "转换为国际格式。")]
        public void LinqToSqlLocalMethodCall01()
        {
            var q = from c in db.Customers
                    where c.Country == "UK" || c.Country == "USA"
                    select new { c.CustomerID, c.CompanyName, Phone = c.Phone, InternationalPhone = PhoneNumberConverter(c.Country, c.Phone) };

            ObjectDumper.Write(q);
        }

        [Category("Select/Distinct")]
        [Title("Select - 本地方法调用 2")]
        [Description("此示例使用本地方法调用" + 
                     "将电话号码转换为国际格式" + 
                     "并创建 XDocument。")]
        public void LinqToSqlLocalMethodCall02()
        {
            XDocument doc = new XDocument(
                new XElement("Customers", from c in db.Customers
                                          where c.Country == "UK" || c.Country == "USA"
                                          select (new XElement("Customer",
                                              new XAttribute("CustomerID", c.CustomerID),
                                              new XAttribute("CompanyName", c.CompanyName),
                                              new XAttribute("InterationalPhone", PhoneNumberConverter(c.Country, c.Phone))
                                              ))));

            Console.WriteLine(doc.ToString());
        }


        [Category("Select/Distinct")]
        [Title("Distinct")]
        [Description("此示例使用 Distinct 选择" +
                     "有客户的唯一城市的序列。")]
        public void LinqToSqlSelect10() {
            var q = (
                from c in db.Customers
                select c.City )
                .Distinct();

            ObjectDumper.Write(q);
        }

        [Category("Count/Sum/Min/Max/Avg")]
        [Title("Count - 简单用法")]
        [Description("此示例使用 Count 得到数据库中客户的数量。")]
        public void LinqToSqlCount01() {
            var q = db.Customers.Count();
            Console.WriteLine(q);
        }

        [Category("Count/Sum/Min/Max/Avg")]
        [Title("Count - 条件")]
        [Description("此示例使用 Count 得到数据库中未断货产品" +
                     "的数量。")]
        public void LinqToSqlCount02() {
            var q = db.Products.Count(p => !p.Discontinued);
            Console.WriteLine(q);
        }

        [Category("Count/Sum/Min/Max/Avg")]
        [Title("Sum - 简单用法")]
        [Description("此示例使用 Sum 得到所有订单的总运费。")]
        public void LinqToSqlCount03() {
            var q = db.Orders.Select(o => o.Freight).Sum();
            Console.WriteLine(q);
        }

        [Category("Count/Sum/Min/Max/Avg")]
        [Title("Sum - 映射")]
        [Description("此示例使用 Sum 得到所有产品的订货总数。")]
        public void LinqToSqlCount04() {
            var q = db.Products.Sum(p => p.UnitsOnOrder);
            Console.WriteLine(q);
        }

        [Category("Count/Sum/Min/Max/Avg")]
        [Title("Min - 简单用法")]
        [Description("此示例使用 Min 查找任意产品的最低单价。")]
        public void LinqToSqlCount05() {
            var q = db.Products.Select(p => p.UnitPrice).Min();
            Console.WriteLine(q);
        }

        [Category("Count/Sum/Min/Max/Avg")]
        [Title("Min - 映射")]
        [Description("此示例使用 Min 查找任意订单的最低运费。")]
        public void LinqToSqlCount06() {
            var q = db.Orders.Min(o => o.Freight);
            Console.WriteLine(q);
        }

        [Category("Count/Sum/Min/Max/Avg")]
        [Title("Min - 元素")]
        [Description("此示例使用 Min 查找每个类别中单价最低的" +
                     "产品。")]
        public void LinqToSqlCount07() {
            var categories =
                from p in db.Products
                group p by p.CategoryID into g
                select new {
                    CategoryID = g.Key,
                    CheapestProducts =
                        from p2 in g
                        where p2.UnitPrice == g.Min(p3 => p3.UnitPrice)
                        select p2
                };

            ObjectDumper.Write(categories, 1);
        }

        [Category("Count/Sum/Min/Max/Avg")]
        [Title("Max - 简单用法")]
        [Description("此示例使用 Max 查找任意雇员的最近雇用日期。")]
        public void LinqToSqlCount08() {
            var q = db.Employees.Select(e => e.HireDate).Max();
            Console.WriteLine(q);
        }

        [Category("Count/Sum/Min/Max/Avg")]
        [Title("Max - 映射")]
        [Description("此示例使用 Max 查找任意产品的最大库存量。")]
        public void LinqToSqlCount09() {
            var q = db.Products.Max(p => p.UnitsInStock);
            Console.WriteLine(q);
        }

        [Category("Count/Sum/Min/Max/Avg")]
        [Title("Max - 元素")]
        [Description("此示例使用 Max 查找每个类别中单价最高的" +
                     "产品。")]
        public void LinqToSqlCount10() {
            var categories =
                from p in db.Products
                group p by p.CategoryID into g
                select new {
                    g.Key,
                    MostExpensiveProducts =
                        from p2 in g
                        where p2.UnitPrice == g.Max(p3 => p3.UnitPrice)
                        select p2
                };

            ObjectDumper.Write(categories, 1);
        }

        [Category("Count/Sum/Min/Max/Avg")]
        [Title("Average - 简单用法")]
        [Description("此示例使用 Average 得到所有订单的平均运费。")]
        public void LinqToSqlCount11() {
            var q = db.Orders.Select(o => o.Freight).Average();
            Console.WriteLine(q);
        }

        [Category("Count/Sum/Min/Max/Avg")]
        [Title("Average - 映射")]
        [Description("此示例使用 Average 得到所有产品的平均单价。")]
        public void LinqToSqlCount12() {
            var q = db.Products.Average(p => p.UnitPrice);
            Console.WriteLine(q);
        }

        [Category("Count/Sum/Min/Max/Avg")]
        [Title("Average - 元素")]
        [Description("此示例使用 Average 查找每个类别中单价高于" +
                     "该类别平均单价的产品。")]
        public void LinqToSqlCount13() {
            var categories =
                from p in db.Products
                group p by p.CategoryID into g
                select new {
                    g.Key, 
                    ExpensiveProducts =
                        from p2 in g
                        where p2.UnitPrice > g.Average(p3 => p3.UnitPrice)
                        select p2
                };

            ObjectDumper.Write(categories, 1);
        }

        [Category("Join")]
        [Title("SelectMany - 一对多 - 1")]
        [Description("此示例在第 2 个 From 语句中使用外键导航" +
                     "来生成伦敦客户的所有订单的平面序列。")]
        public void LinqToSqlJoin01() {
            var q =
                from c in db.Customers
                where c.City == "London"
                from o in c.Orders
                select o;

            ObjectDumper.Write(q);
        }

        [Category("Join")]
        [Title("SelectMany - 一对多 - 2")]
        [Description("此示例在 Where 子句中使用外键导航" +
                     "筛选其供应商在美国且" +
                     "缺货的产品。")]
        public void LinqToSqlJoin02() {
            var q =
                from p in db.Products
                where p.Supplier.Country == "USA" && p.UnitsInStock == 0
                select p;

            ObjectDumper.Write(q);
        }

        [Category("Join")]
        [Title("SelectMany - 多对多")]
        [Description("此示例在 From 子句中使用外键导航" +
                     "筛选在西雅图的雇员，" +
                     "同时列出其所在地区。")]
        public void LinqToSqlJoin03() {
            var q =
                from e in db.Employees
                from et in e.EmployeeTerritories
                where e.City == "Seattle"
                select new {e.FirstName, e.LastName, et.Territory.TerritoryDescription};

            ObjectDumper.Write(q);
        }

        [Category("Join")]
        [Title("SelectMany - 自联接")]
        [Description("此示例在 Select 子句中使用外键导航" +
                     "筛选成对的雇员，每对中" +
                     "一个雇员隶属于另一个雇员，且" +
                     "两个雇员都来自相同城市。")]
        public void LinqToSqlJoin04() {
            var q =
                from e1 in db.Employees
                from e2 in e1.Employees
                where e1.City == e2.City
                select new {
                    FirstName1 = e1.FirstName, LastName1 = e1.LastName,
                    FirstName2 = e2.FirstName, LastName2 = e2.LastName,
                    e1.City
                };

            ObjectDumper.Write(q);
        }

        [Category("Join")]
        [Title("GroupJoin - 双向联接")]
        [Description("此示例显式联接两个表并从这两个表投影出结果。")]
        public void LinqToSqlJoin05() {
            var q =
                from c in db.Customers
                join o in db.Orders on c.CustomerID equals o.CustomerID into orders
                select new {c.ContactName, OrderCount = orders.Count()};

            ObjectDumper.Write(q);
        }

        [Category("Join")]
        [Title("GroupJoin - 三向联接")]
        [Description("此示例显式联接三个表并分别从每个表投影出结果。")]
        public void LinqToSqlJoin06() {
            var q =
                from c in db.Customers
                join o in db.Orders on c.CustomerID equals o.CustomerID into ords
                join e in db.Employees on c.City equals e.City into emps
                select new {c.ContactName, ords=ords.Count(), emps=emps.Count()};

            ObjectDumper.Write(q);
        }

        [Category("Join")]
        [Title("GroupJoin - 左外部联接")] 
        [Description("此示例说明如何通过使用 DefaultIfEmpty() 获取 LEFT OUTER JOIN。在雇员没有订单时，DefaultIfEmpty() 方法返回 null。" )]
        public void LinqToSqlJoin07() {
            var q =
                from e in db.Employees
                join o in db.Orders on e equals o.Employee into ords
                from o in ords.DefaultIfEmpty()
                select new {e.FirstName, e.LastName, Order = o};

            ObjectDumper.Write(q);
        }

        [Category("Join")]
        [Title("GroupJoin - 投影的 Let 赋值")]
        [Description("此示例从联接投影出最终“Let”表达式。")]
        public void LinqToSqlJoin08() {
            var q = 
                from c in db.Customers
                join o in db.Orders on c.CustomerID equals o.CustomerID into ords
                let z = c.City + c.Country
                from o in ords                  
                select new {c.ContactName, o.OrderID, z};

            ObjectDumper.Write(q);
        }

        [Category("Join")]
        [Title("GroupJoin - 组合键")]
        [Description("此示例显示带有组合键的联接。")]
        public void LinqToSqlJoin09() {
            var q =
                from o in db.Orders
                from p in db.Products
                join d in db.OrderDetails 
                    on new {o.OrderID, p.ProductID} equals new {d.OrderID, d.ProductID}
                    into details
                from d in details
                select new {o.OrderID, p.ProductID, d.UnitPrice};

            ObjectDumper.Write(q);
        }

        [Category("Join")]
        [Title("GroupJoin - 可为 null\\不可为 null 的键关系")]
        [Description("此示例显示如何构造一侧可为 null 而另一侧不可为 null 的联接。")]
        public void LinqToSqlJoin10() {
            var q =
                from o in db.Orders
                join e in db.Employees 
                    on o.EmployeeID equals (int?)e.EmployeeID into emps
                from e in emps
                select new {o.OrderID, e.FirstName};

            ObjectDumper.Write(q);
        }

        [Category("Order By")]
        [Title("OrderBy - 简单用法")]
        [Description("此示例使用 orderby 按雇用日期对雇员" +
                     "进行排序。")]
        public void LinqToSqlOrderBy01() {
            var q =
                from e in db.Employees
                orderby e.HireDate
                select e;

            ObjectDumper.Write(q);
        }

        [Category("Order By")]
        [Title("OrderBy - 带 Where")]
        [Description("此示例使用 where 和 orderby 按运费" +
                     "进行排序。")]
        public void LinqToSqlOrderBy02() {
            var q =
                from o in db.Orders
                where o.ShipCity == "London"
                orderby o.Freight
                select o;

            ObjectDumper.Write(q);
        }

        [Category("Order By")]
        [Title("OrderByDescending")]
        [Description("此示例使用 orderby 按单价从高到低的顺序对" +
                     "进行排序。")]
        public void LinqToSqlOrderBy03() {
            var q =
                from p in db.Products
                orderby p.UnitPrice descending
                select p;

            ObjectDumper.Write(q);
        }

        [Category("Order By")]
        [Title("ThenBy")]
        [Description("此示例使用复合的 orderby 对客户进行排序，" +
                     "进行排序。")]
        public void LinqToSqlOrderBy04() {
            var q =
                from c in db.Customers
                orderby c.City, c.ContactName
                select c;

            ObjectDumper.Write(q);
        }

        [Category("Order By")]
        [Title("ThenByDescending")]
        [Description("此示例使用 orderby 先按发往国家再按运费从高到低的顺序" +
                     "对 EmployeeID 1 的订单进行排序。")]
        public void LinqToSqlOrderBy05() {
            var q =
                from o in db.Orders
                where o.EmployeeID == 1
                orderby o.ShipCountry, o.Freight descending
                select o;

            ObjectDumper.Write(q);
        }


        [Category("Order By")]
        [Title("OrderBy - Group By")]
        [Description("此示例使用 orderby、Max 和 Group By 得出每种类别中单价最高的产品，" +
                     "并按 CategoryID 对这组产品进行排序。")]
        public void LinqToSqlOrderBy06() {
            var categories =
                from p in db.Products
                group p by p.CategoryID into g
                orderby g.Key
                select new {
                    g.Key,
                    MostExpensiveProducts =
                        from p2 in g
                        where p2.UnitPrice == g.Max(p3 => p3.UnitPrice)
                        select p2
                };

            ObjectDumper.Write(categories, 1);
        }

        [Category("Group By/Having")]
        [Title("GroupBy - 简单用法")]
        [Description("此示例使用 Group By 按 CategoryID 划分" +
                     "产品。")]
        public void LinqToSqlGroupBy01() {
            var q =
                from p in db.Products
                group p by p.CategoryID into g
                select g;

            ObjectDumper.Write(q, 1);
        }

        [Category("Group By/Having")]
        [Title("GroupBy - Max")]
        [Description("此示例使用 Group By 和 Max " +
                     "查找每个 CategoryID 的最高单价。")]
        public void LinqToSqlGroupBy02() {
            var q =
                from p in db.Products
                group p by p.CategoryID into g
                select new {
                    g.Key,
                    MaxPrice = g.Max(p => p.UnitPrice)
                };

            ObjectDumper.Write(q, 1);
        }

        [Category("Group By/Having")]
        [Title("GroupBy - Min")]
        [Description("此示例使用 Group By 和 Min " +
                     "查找每个 CategoryID 的最低单价。")]
        public void LinqToSqlGroupBy03() {
            var q =
                from p in db.Products
                group p by p.CategoryID into g
                select new {
                    g.Key,
                    MinPrice = g.Min(p => p.UnitPrice)
                };

            ObjectDumper.Write(q, 1);
        }

        [Category("Group By/Having")]
        [Title("GroupBy - Average")]
        [Description("此示例使用 Group By 和 Average " +
                     "得到每个 CategoryID 的平均单价。")]
        public void LinqToSqlGroupBy04() {
            var q =
                from p in db.Products
                group p by p.CategoryID into g
                select new {
                    g.Key,
                    AveragePrice = g.Average(p => p.UnitPrice)
                };

            ObjectDumper.Write(q, 1);
        }

        [Category("Group By/Having")]
        [Title("GroupBy - Sum")]
        [Description("此示例使用 Group By 和 Sum " +
                     "得到每个 CategoryID 的单价总计。")]
        public void LinqToSqlGroupBy05() {
            var q =
                from p in db.Products
                group p by p.CategoryID into g
                select new {
                    g.Key,
                    TotalPrice = g.Sum(p => p.UnitPrice)
                };

            ObjectDumper.Write(q, 1);
        }

        [Category("Group By/Having")]
        [Title("GroupBy - Count")]
        [Description("此示例使用 Group By 和 Count " +
                     "得到每个 CategoryID 中产品的数量。")]
        public void LinqToSqlGroupBy06() {
            var q =
                from p in db.Products
                group p by p.CategoryID into g
                select new {
                    g.Key,
                    NumProducts = g.Count()
                };

            ObjectDumper.Write(q, 1);
        }

        [Category("Group By/Having")]
        [Title("GroupBy 以及条件 Count")]
        [Description("此示例使用 Group By 和 Count " +
                     "得到每个 CategoryID 中断货" +
                     "产品的数量。")]
        public void LinqToSqlGroupBy07() {
            var q =
                from p in db.Products
                group p by p.CategoryID into g
                select new {
                    g.Key,
                    NumProducts = g.Count(p => p.Discontinued)
                };

            ObjectDumper.Write(q, 1);
        }

        [Category("Group By/Having")]
        [Title("GroupBy - 后跟 Where")]
        [Description("此示例在 Group By 子句后使用 Where 子句" +
                     "查找所有至少有 10 种产品的类别。")]
        public void LinqToSqlGroupBy08() {
            var q =
                from p in db.Products
                group p by p.CategoryID into g
                where g.Count() >= 10
                select new {
                    g.Key,
                    ProductCount = g.Count()
                };

            ObjectDumper.Write(q, 1);
        }

        [Category("Group By/Having")]
        [Title("GroupBy - 多列")]
        [Description("此示例使用 Group By 按 CategoryID 和 SupplierID 将产品分组。")]
        public void LinqToSqlGroupBy09() {
            var categories =
                from p in db.Products
                group p by new { p.CategoryID, p.SupplierID } into g
                select new {g.Key, g};

            ObjectDumper.Write(categories, 1);
        }

        [Category("Group By/Having")]
        [Title("GroupBy - 表达式")]
        [Description("此示例使用 Group By 返回两个产品序列。" +
                     "第一个序列包含" +
                     "单价大于 10 的产品。第二个序列包含" +
                     "单价小于或等于 10 的产品。")]
        public void LinqToSqlGroupBy10() {
            var categories =
                from p in db.Products
                group p by new { Criterion = p.UnitPrice > 10 } into g
                select g;

            ObjectDumper.Write(categories, 1);
        }

        [Category("Exists/In/Any/All/Contains")]
        [Title("Any - 简单用法")]
        [Description("此示例使用 Any 仅返回没有订单的客户。")]
        public void LinqToSqlExists01() {
            var q =
                from c in db.Customers
                where !c.Orders.Any()
                select c;

            ObjectDumper.Write(q);
        }

        [Category("Exists/In/Any/All/Contains")]
        [Title("Any - 条件")]
        [Description("此示例使用 Any 仅返回至少有" +
                     "一种产品断货的类别。")]
        public void LinqToSqlExists02() {
            var q =
                from c in db.Categories
                where c.Products.Any(p => p.Discontinued)
                select c;

            ObjectDumper.Write(q);
        }

        [Category("Exists/In/Any/All/Contains")]
        [Title("All - 条件")]
        [Description("此示例使用 All 返回所有订单都运往" +
                     "其所在城市的客户或未下订单的客户。")]
        public void LinqToSqlExists03() {
            var q =
                from c in db.Customers
                where c.Orders.All(o => o.ShipCity == c.City)
                select c;

            ObjectDumper.Write(q);
        }

        [Category("Exists/In/Any/All/Contains")]
        [Title("Contains - 一个对象")]
        [Description("此示例使用 Contain 查找哪个客户包含 OrderID 为 10248 的订单。")] 
        public void LinqToSqlExists04()
        {
            var order = (from o in db.Orders
                         where o.OrderID == 10248
                         select o).First();

            var q = db.Customers.Where(p => p.Orders.Contains(order)).ToList();

            foreach (var cust in q)
            {
                foreach (var ord in cust.Orders)
                {
                    Console.WriteLine("客户 {0} 具有 OrderID  {1}。", cust.CustomerID, ord.OrderID);
                }
            }
        }

        [Category("Exists/In/Any/All/Contains")]
        [Title("Contains - 多个值")]
        [Description("此示例使用 Contains 查找其所在城市为西雅图、伦敦、巴黎或温哥华的客户。")]
        public void LinqToSqlExists05()
        {
            string[] cities = new string[] { "Seattle", "London", "Vancouver", "Paris" };
            var q = db.Customers.Where(p=>cities.Contains(p.City)).ToList();

            ObjectDumper.Write(q);
        }


        [Category("Union All/Union/Intersect")]
        [Title("Concat - 简单用法")]
        [Description("此示例使用 Concat 返回所有客户和雇员的" +
                     "电话/传真号码的序列。")]
        public void LinqToSqlUnion01() {
            var q = (
                     from c in db.Customers
                     select c.Phone
                    ).Concat(
                     from c in db.Customers
                     select c.Fax
                    ).Concat(
                     from e in db.Employees
                     select e.HomePhone
                    );

            ObjectDumper.Write(q);
        }

        [Category("Union All/Union/Intersect")]
        [Title("Concat - 复合")]
        [Description("此示例使用 Concat 返回所有客户和雇员的" +
                     "姓名与电话号码映射的序列。")]
        public void LinqToSqlUnion02() {
            var q = (
                     from c in db.Customers
                     select new {Name = c.CompanyName, c.Phone}
                    ).Concat(
                     from e in db.Employees
                     select new {Name = e.FirstName + " " + e.LastName, Phone = e.HomePhone}
                    );

            ObjectDumper.Write(q);
        }

        [Category("Union All/Union/Intersect")]
        [Title("Union")]
        [Description("此示例使用 Union 返回有客户或雇员任意一方居住的" +
                     "所有国家/地区的序列。")]
        public void LinqToSqlUnion03() {
            var q = (
                     from c in db.Customers
                     select c.Country
                    ).Union(
                     from e in db.Employees
                     select e.Country
                    );

            ObjectDumper.Write(q);
        }

        [Category("Union All/Union/Intersect")]
        [Title("Intersect")]
        [Description("此示例使用 Intersect 返回客户和雇员双方都居住的" +
                     "所有国家/地区的序列。")]
        public void LinqToSqlUnion04() {
            var q = (
                     from c in db.Customers
                     select c.Country
                    ).Intersect(
                     from e in db.Employees
                     select e.Country
                    );

            ObjectDumper.Write(q);
        }

        [Category("Union All/Union/Intersect")]
        [Title("Except")]
        [Description("此示例使用 Except 返回有客户居住但无雇员居住的" +
                     "所有国家/地区的序列。")]
        public void LinqToSqlUnion05() {
            var q = (
                     from c in db.Customers
                     select c.Country
                    ).Except(
                     from e in db.Employees
                     select e.Country
                    );

            ObjectDumper.Write(q);
        }

        [Category("Top/Bottom")]
        [Title("Take")]
        [Description("此示例使用 Take 选择所雇用的前 5 个雇员。")]
        public void LinqToSqlTop01() {
            var q = (
                from e in db.Employees
                orderby e.HireDate
                select e)
                .Take(5);

            ObjectDumper.Write(q);
        }

        [Category("Top/Bottom")]
        [Title("Skip")]
        [Description("此示例使用 Skip 选择 10 种最贵产品之外的所有产品。")]
        public void LinqToSqlTop02() {
            var q = (
                from p in db.Products
                orderby p.UnitPrice descending
                select p)
                .Skip(10);

            ObjectDumper.Write(q);
        }

        [Category("Paging")]
        [Title("分页 - 索引")]
        [Description("此示例使用 Skip 和 Take 运算符进行分页，" +
                     "跳过前 50 个记录，然后返回接下来 10 个，因此" +
                     "提供 Products 表第 6 页的数据。")]
        public void LinqToSqlPaging01() {
            var q = (
                from c in db.Customers
                orderby c.ContactName
                select c)
                .Skip(50)
                .Take(10);

            ObjectDumper.Write(q);
        }

        [Category("Paging")]
        [Title("分页 - 按唯一键排序")]
        [Description("此示例使用 Where 子句和 Take 运算符进行分页，" +
                     "首先筛选得到仅 50 (第 5 页最后一个 ProductID " +
                     ")以上的 ProductID，然后按 ProductID 排序，最后取前 10 个结果，" +
                     "因此提供 Products 表第 6 页的数据。" +
                     "请注意，此方法仅适用于按唯一键排序的情况。")]
        public void LinqToSqlPaging02() {
            var q = (
                from p in db.Products
                where p.ProductID > 50
                orderby p.ProductID
                select p)
                .Take(10);

            ObjectDumper.Write(q);
        }
        [Category("SqlMethods")]
        [Title("SqlMethods - Like")]
        [Description("此示例使用 SqlMethods 筛选 CustomerID 以“C”开头的客户。")]
        public void LinqToSqlSqlMethods01()
        {

            var q = from c in db.Customers
                    where SqlMethods.Like(c.CustomerID, "C%")
                    select c;

            ObjectDumper.Write(q);

        }

        [Category("SqlMethods")]
        [Title("SqlMethods - DateDiffDay")]
        [Description("此示例使用 SqlMethods 查找在创建订单后的 10 天内已发货的所有订单")]
        public void LinqToSqlSqlMethods02()
        {

            var q = from o in db.Orders
                    where SqlMethods.DateDiffDay(o.OrderDate, o.ShippedDate) < 10
                    select o;

            ObjectDumper.Write(q);

        }

        [Category("已编译查询")]
        [Title("已编译查询 - 1")]
        [Description("此示例创建一个已编译查询，然后使用它检索输入城市的客户")]
        public void LinqToSqlCompileQuery01()
        {
            //创建已编译查询
            var fn = CompiledQuery.Compile((Northwind db2, string city) =>
                from c in db2.Customers
                where c.City == city
                select c);

            Console.WriteLine("****** Call compiled query to retrieve customers from London ******");
            var LonCusts = fn(db, "London");
            ObjectDumper.Write(LonCusts);

            Console.WriteLine();

            Console.WriteLine("****** Call compiled query to retrieve customers from Seattle ******");
            var SeaCusts = fn(db, "Seattle");
            ObjectDumper.Write(SeaCusts);

        }


        [Category("Insert/Update/Delete")]
        [Title("Insert - 简单用法")]
        [Description("此示例使用 InsertOnSubmit 方法将新客户添加到 " +
                     "Customers 表对象。调用 SubmitChanges 将此" +
                     "新 Customer 保持到数据库。")]
        public void LinqToSqlInsert01() {
            var q =
                from c in db.Customers
                where c.Region == "WA"
                select c;

            Console.WriteLine("*** BEFORE ***");
            ObjectDumper.Write(q);


            Console.WriteLine();
            Console.WriteLine("*** INSERT ***");
            var newCustomer = new Customer { CustomerID = "MCSFT",
                                             CompanyName = "Microsoft",
                                             ContactName = "John Doe",
                                             ContactTitle = "Sales Manager",
                                             Address = "1 Microsoft Way",
                                             City = "Redmond",
                                             Region = "WA",
                                             PostalCode = "98052",
                                             Country = "USA",
                                             Phone = "(425) 555-1234",
                                             Fax = null
                                           };
            db.Customers.InsertOnSubmit(newCustomer);
            db.SubmitChanges();


            Console.WriteLine();
            Console.WriteLine("*** AFTER ***");
            ObjectDumper.Write(q);



            Cleanup64();  // 还原以前的数据库状态
        }

        private void Cleanup64() {
            SetLogging(false);

            db.Customers.DeleteAllOnSubmit(from c in db.Customers where c.CustomerID == "MCSFT" select c);
            db.SubmitChanges();
        }

        [Category("Insert/Update/Delete")]
        [Title("Insert - 一对多")]
        [Description("此示例使用 InsertOnSubmit 方法将新类别添加到 " +
                     "Categories 表对象，并将新 Product 添加到与此新 Category 有外键关系的 " +
                     "Products 表。调用" +
                     "SubmitChanges 将这些新对象及其关系保持到" +
                     "数据库。")]
        public void LinqToSqlInsert02() {

            Northwind db2 = new Northwind(connString);

            DataLoadOptions ds = new DataLoadOptions();

            ds.LoadWith<nwind.Category>(p => p.Products);
            db2.LoadOptions = ds;

            var q = (
                from c in db2.Categories
                where c.CategoryName == "Widgets"
                select c);


            Console.WriteLine("*** BEFORE ***");
            ObjectDumper.Write(q, 1);


            Console.WriteLine();
            Console.WriteLine("*** INSERT ***");
            var newCategory = new Category { CategoryName = "Widgets",
                                             Description = "Widgets are the customer-facing analogues " +
                                                           "to sprockets and cogs."
                                           };
            var newProduct = new Product { ProductName = "Blue Widget",
                                           UnitPrice = 34.56M,
                                           Category = newCategory
                                         };
            db2.Categories.InsertOnSubmit(newCategory);
            db2.SubmitChanges();


            Console.WriteLine();
            Console.WriteLine("*** AFTER ***");
            ObjectDumper.Write(q, 1);

            Cleanup65();  // 还原以前的数据库状态
        }

        private void Cleanup65() {
            SetLogging(false);

            db.Products.DeleteAllOnSubmit(from p in db.Products where p.Category.CategoryName == "Widgets" select p);
            db.Categories.DeleteAllOnSubmit(from c in db.Categories where c.CategoryName == "Widgets" select c);
            db.SubmitChanges();
        }

        [Category("Insert/Update/Delete")]
        [Title("插入 - 多对多")]
        [Description("此示例使用 InsertOnSubmit  方法将新雇员添加到 " +
                     "Employees 表对象，将新 Territory 添加到 Territories 表对象，" +
                     "并将新 EmployeeTerritory 添加到与此新 Employee 和新 Territory 有外键关系的 " +
                     "EmployeeTerritories 表对象。" +
                     "调用 SubmitChanges 将这些新对象及其" +
                     "关系保持到数据库。")]
        public void LinqToSqlInsert03() {

            Northwind db2 = new Northwind(connString);

            DataLoadOptions ds = new DataLoadOptions();
            ds.LoadWith<nwind.Employee>(p => p.EmployeeTerritories);
            ds.LoadWith<nwind.EmployeeTerritory>(p => p.Territory);

            db2.LoadOptions = ds;
            var q = (
                from e in db.Employees
                where e.FirstName == "Nancy"
                select e);



            Console.WriteLine("*** BEFORE ***");
            ObjectDumper.Write(q, 1);


            Console.WriteLine();
            Console.WriteLine("*** INSERT ***");
            var newEmployee = new Employee { FirstName = "Kira",
                                             LastName = "Smith"
                                           };
            var newTerritory = new Territory { TerritoryID = "12345",
                                               TerritoryDescription = "Anytown",
                                               Region = db.Regions.First()
                                             };
            var newEmployeeTerritory = new EmployeeTerritory { Employee = newEmployee,
                                                               Territory = newTerritory
                                                             };
            db.Employees.InsertOnSubmit(newEmployee);
            db.Territories.InsertOnSubmit(newTerritory);
            db.EmployeeTerritories.InsertOnSubmit(newEmployeeTerritory);
            db.SubmitChanges();


            Console.WriteLine();
            Console.WriteLine("*** AFTER ***");
            ObjectDumper.Write(q, 2);



            Cleanup66();  // 还原以前的数据库状态
        }

        private void Cleanup66() {
            SetLogging(false);

            db.EmployeeTerritories.DeleteAllOnSubmit(from et in db.EmployeeTerritories where et.TerritoryID == "12345" select et);
            db.Employees.DeleteAllOnSubmit(from e in db.Employees where e.FirstName == "Kira" && e.LastName == "Smith" select e);
            db.Territories.DeleteAllOnSubmit(from t in db.Territories where t.TerritoryID == "12345" select t);
            db.SubmitChanges();
        }

        [Category("Insert/Update/Delete")]
        [Title("Update - 简单用法")]
        [Description("此示例使用 SubmitChanges 将对检索到的一个" +
                     "Customer 对象做出的更新保持回数据库。")]
        public void LinqToSqlInsert04() {
            var q =
                from c in db.Customers
                where c.CustomerID == "ALFKI"
                select c;

            Console.WriteLine("*** BEFORE ***");
            ObjectDumper.Write(q);


            Console.WriteLine();
            Console.WriteLine("*** UPDATE ***");
            Customer cust = db.Customers.First(c => c.CustomerID == "ALFKI");
            cust.ContactTitle = "Vice President";
            db.SubmitChanges();


            Console.WriteLine();
            Console.WriteLine("*** AFTER ***");
            ObjectDumper.Write(q);

            Cleanup67();  // 还原以前的数据库状态
        }

        private void Cleanup67() {
            SetLogging(false);

            Customer cust = db.Customers.First(c => c.CustomerID == "ALFKI");
            cust.ContactTitle = "Sales Representative";
            db.SubmitChanges();
        }

        [Category("Insert/Update/Delete")]
        [Title("Update - 进行多个更改并显示")]
        [Description("此示例使用 SubmitChanges 将对检索到的" +
                     "进行的更新保持回数据库。还演示如何确定多少对象已更改，" +
                     "哪些对象已更改，以及哪些对象成员已更改。")]
        public void LinqToSqlInsert05() {
            var q = from p in db.Products
                    where p.CategoryID == 1
                    select p;

            Console.WriteLine("*** BEFORE ***");
            ObjectDumper.Write(q);


            Console.WriteLine();
            Console.WriteLine("*** UPDATE ***");
            foreach (var p in q)
            {
                p.UnitPrice += 1.00M;
            }

            //
            ChangeSet cs = db.GetChangeSet();
            Console.WriteLine("*** CHANGE SET ***");
            Console.WriteLine("Number of entities inserted: {0}", cs.Inserts.Count);
            Console.WriteLine("Number of entities updated:  {0}", cs.Updates.Count);
            Console.WriteLine("Number of entities deleted:  {0}", cs.Deletes.Count);
            Console.WriteLine();

            Console.WriteLine("*** GetOriginalEntityState ***");
            foreach (object o in cs.Updates)
            {
                Product p = o as Product;
                if (p != null)
                {
                    Product oldP = db.Products.GetOriginalEntityState(p);
                    Console.WriteLine("** Current **");
                    ObjectDumper.Write(p);
                    Console.WriteLine("** Original **");
                    ObjectDumper.Write(oldP);
                    Console.WriteLine();
                }
            }
            Console.WriteLine();

            Console.WriteLine("*** GetModifiedMembers ***");
            foreach (object o in cs.Updates)
            {
                Product p = o as Product;
                if (p != null)
                {
                    foreach (ModifiedMemberInfo mmi in db.Products.GetModifiedMembers(p))
                    {
                        Console.WriteLine("Member {0}", mmi.Member.Name);
                        Console.WriteLine("\tOriginal value: {0}", mmi.OriginalValue);
                        Console.WriteLine("\tCurrent  value: {0}", mmi.CurrentValue);
                    }
                }
            }

            db.SubmitChanges();

            Console.WriteLine();
            Console.WriteLine("*** AFTER ***");
            ObjectDumper.Write(q);

            Cleanup68();  // 还原以前的数据库状态
        }

        private void Cleanup68() {
            SetLogging(false);

            var q =
                from p in db.Products
                where p.CategoryID == 1
                select p;

            foreach (var p in q) {
                p.UnitPrice -= 1.00M;
            }
            db.SubmitChanges();
        }

        [Category("Insert/Update/Delete")]
        [Title("Delete - 简单用法")]
        [Description("此示例使用 DeleteOnSubmit 方法从 OrderDetail 表对象中 " +
                     "删除 OrderDetail。调用 SubmitChanges 将此" +
                     "删除保持到数据库。")]
        public void LinqToSqlInsert06() {
            Console.WriteLine("*** BEFORE ***");
            ObjectDumper.Write(from c in db.OrderDetails where c.OrderID == 10255 select c);


            Console.WriteLine();
            Console.WriteLine("*** DELETE ***");
            //Beverages
            OrderDetail orderDetail = db.OrderDetails.First(c => c.OrderID == 10255 && c.ProductID == 36);

            db.OrderDetails.DeleteOnSubmit(orderDetail);
            db.SubmitChanges();


            Console.WriteLine();
            Console.WriteLine("*** AFTER ***");
            ClearDBCache();
            ObjectDumper.Write(from c in db.OrderDetails where c.OrderID == 10255 select c);



            Cleanup69();  // 还原以前的数据库状态
        }

        private void Cleanup69() {
            SetLogging(false);

            OrderDetail orderDetail = new OrderDetail()
                                      {
                                          OrderID = 10255,
                                          ProductID = 36,
                                          UnitPrice = 15.200M,
                                          Quantity = 25,
                                          Discount = 0.0F
                                      };
            db.OrderDetails.InsertOnSubmit(orderDetail);

            db.SubmitChanges();
        }

        [Category("Insert/Update/Delete")]
        [Title("删除 - 一对多")]
        [Description("此示例使用 DeleteOnSubmit 方法从 Orders 和 Order Details 表中删除 " +
                     "Order 和 Order Detail。首先从 Order Details 删除，然后" +
                     "从 Orders 删除。调用 SubmitChanges 将此删除保持到数据库。")]
        public void LinqToSqlInsert07() {
            var orderDetails =
                from o in db.OrderDetails
                where o.Order.CustomerID == "WARTH" && o.Order.EmployeeID == 3
                select o;

            Console.WriteLine("*** BEFORE ***");
            ObjectDumper.Write(orderDetails);

            Console.WriteLine();
            Console.WriteLine("*** DELETE ***");
            var order =
                (from o in db.Orders
                 where o.CustomerID == "WARTH" && o.EmployeeID == 3
                 select o).First();

            foreach (OrderDetail od in orderDetails)
            {
                db.OrderDetails.DeleteOnSubmit(od);
            }

            db.Orders.DeleteOnSubmit(order);

            db.SubmitChanges();


            Console.WriteLine();
            Console.WriteLine("*** AFTER ***");
            ObjectDumper.Write(orderDetails);



            Cleanup70();  // 还原以前的数据库状态
        }

        private void Cleanup70() {
            SetLogging(false);

            Order order = new Order()
                          {
                              CustomerID = "WARTH",
                              EmployeeID = 3,
                              OrderDate = new DateTime(1996, 7, 26),
                              RequiredDate = new DateTime(1996, 9, 6),
                              ShippedDate = new DateTime(1996, 7, 31),
                              ShipVia = 3,
                              Freight = 25.73M,
                              ShipName = "Wartian Herkku",
                              ShipAddress = "Torikatu 38",
                              ShipCity = "Oulu",
                              ShipPostalCode="90110",
                              ShipCountry = "Finland"
                          };

                              //Order, Cus, Emp, OrderD, ReqD, ShiD, ShipVia, Frei, ShipN, ShipAdd, ShipCi, ShipReg, ShipPostalCost, ShipCountry
                              //10266	WARTH	3	1996-07-26 00:00:00.000	1996-09-06 00:00:00.000	1996-07-31 00:00:00.000	3	25.73	Wartian Herkku	Torikatu 38	Oulu	NULL	90110	Finland

            OrderDetail orderDetail = new OrderDetail()
                                      {
                                          ProductID = 12,
                                          UnitPrice = 30.40M,
                                          Quantity = 12,
                                          Discount = 0.0F
                                      };
            order.OrderDetails.Add(orderDetail);

            db.Orders.InsertOnSubmit(order);
            db.SubmitChanges();
        }


        [Category("Insert/Update/Delete")]
        [Title("删除 - 推理删除")]
        [Description("此示例演示，在实体对象的引用实体将该对象从其 EntitySet 中移除时，推理删除如何导致在" +
                     "该对象上发生实际的删除操作。" +
                     "仅当实体的关联映射将 DeleteOnNull 设置为 true 且 CanBeNull 为 false 时，" +
                     "才会发生推理删除行为。")]
        public void LinqToSqlInsert08()
        {
            Console.WriteLine("*** BEFORE ***");
       
            ObjectDumper.Write(from o in db.Orders where o.OrderID == 10248 select o);
            ObjectDumper.Write(from d in db.OrderDetails where d.OrderID == 10248 select d);

            Console.WriteLine();
            Console.WriteLine("*** INFERRED DELETE ***");
            Order order = db.Orders.First(x => x.OrderID == 10248);
            OrderDetail od = order.OrderDetails.First(d => d.ProductID == 11);
            order.OrderDetails.Remove(od);

            db.SubmitChanges();

            Console.WriteLine();
            Console.WriteLine("*** AFTER ***");
            ClearDBCache();
            ObjectDumper.Write(from o in db.Orders where o.OrderID == 10248 select o);
            ObjectDumper.Write(from d in db.OrderDetails where d.OrderID == 10248 select d);
            CleanupInsert08();  // 还原以前的数据库状态
        }

        private void CleanupInsert08()
        {
            SetLogging(false);
            OrderDetail od = new OrderDetail() { ProductID = 11, Quantity = 12, UnitPrice = 14, OrderID = 10248, Discount = 0 };
            db.OrderDetails.InsertOnSubmit(od);
            db.SubmitChanges();
        }

        [Category("Insert/Update/Delete")]
        [Title("插入 - 使用动态 CUD 重写")]
        [Description("此示例使用 DataContext  提供的分部方法 InsertRegion 插入一个区域。" +
                     "对 SubmitChanges 的调用调用 InsertRegion 重写，后者使用动态 CUD 运行 " +
                     "Linq To SQL 生成的默认 SQL 查询")]
        public void LinqToSqlInsert09()
        {
            Console.WriteLine("*** BEFORE ***");
            ObjectDumper.Write(from c in db.Regions where c.RegionID == 32 select c);


            Console.WriteLine();
            Console.WriteLine("*** INSERT OVERRIDE ***");
            //Beverages
            Region nwRegion = new Region() { RegionID = 32, RegionDescription = "Rainy" };

            db.Regions.InsertOnSubmit(nwRegion);
            db.SubmitChanges();


            Console.WriteLine();
            Console.WriteLine("*** AFTER ***");
            ClearDBCache();
            ObjectDumper.Write(from c in db.Regions where c.RegionID == 32 select c);

            CleanupInsert09();  // 还原以前的数据库状态
        }

        private void CleanupInsert09()
        {
            SetLogging(false);

            db.Regions.DeleteAllOnSubmit(from r in db.Regions where r.RegionID == 32 select r);
            db.SubmitChanges();
        }

        [Category("Insert/Update/Delete")]
        [Title("带有 Attach 的 Update" )]
        [Description("此示例从另一个层中获取实体，使用 Attach 和 AttachAll " +
                     "将反序列化后的实体附加到数据上下文，然后更新实体。" +
                     "更改被提交到数据库。")]
        public void LinqToSqlInsert10()
        {
           
            // 通常，通过从其他层反序列化 XML 来获取要附加的实体。
            // 不支持将实体从一个 DataContext 附加到另一个 DataContext。
            // 因此若要复制反序列化实体的操作，将在此处重新创建这些实体。
            Customer c1;
            List<Order> deserializedOrders = new List<Order>();
            Customer deserializedC1;

            using (Northwind tempdb = new Northwind(connString))
            {
                c1 = tempdb.Customers.Single(c => c.CustomerID == "ALFKI");
                Console.WriteLine("Customer {0}'s original address {1}", c1.CustomerID, c1.Address);
                Console.WriteLine();
                deserializedC1 = new Customer { Address = c1.Address, City = c1.City,
                                                CompanyName=c1.CompanyName, ContactName=c1.ContactName,
                                                ContactTitle=c1.ContactTitle, Country=c1.Country,
                                                CustomerID=c1.CustomerID, Fax=c1.Fax,
                                                Phone=c1.Phone, PostalCode=c1.PostalCode,
                                                Region=c1.Region};
                Customer tempcust = tempdb.Customers.Single(c => c.CustomerID == "ANTON");
                foreach (Order o in tempcust.Orders)
                {
                    Console.WriteLine("Order {0} belongs to customer {1}", o.OrderID, o.CustomerID);
                    deserializedOrders.Add(new Order {CustomerID=o.CustomerID, EmployeeID=o.EmployeeID,
                                                      Freight=o.Freight, OrderDate=o.OrderDate, OrderID=o.OrderID,
                                                      RequiredDate=o.RequiredDate, ShipAddress=o.ShipAddress,
                                                      ShipCity=o.ShipCity, ShipName=o.ShipName,
                                                      ShipCountry=o.ShipCountry, ShippedDate=o.ShippedDate,
                                                      ShipPostalCode=o.ShipPostalCode, ShipRegion=o.ShipRegion,
                                                      ShipVia=o.ShipVia});
                }
                
                Console.WriteLine();

                Customer tempcust2 = tempdb.Customers.Single(c => c.CustomerID == "CHOPS");
                var c3Orders = tempcust2.Orders.ToList();
                foreach (Order o in c3Orders)
                {
                    Console.WriteLine("Order {0} belongs to customer {1}", o.OrderID, o.CustomerID);
                }
                Console.WriteLine();
            }

            using (Northwind db2 = new Northwind(connString))
            {
                // 将第一个实体附加到当前数据上下文，以跟踪更改。
                db2.Customers.Attach(deserializedC1);
                Console.WriteLine("***** Update Customer ALFKI's address ******");
                Console.WriteLine();
                // 更改所跟踪的实体。
                deserializedC1.Address = "123 First Ave";

                // 附加订单列表中的所有实体。
                db2.Orders.AttachAll(deserializedOrders);
                // 将订单更新为属于其他客户。
                Console.WriteLine("****** Assign all Orders belong to ANTON to CHOPS ******");
                Console.WriteLine();

                foreach (Order o in deserializedOrders)
                {
                    o.CustomerID = "CHOPS";
                }

                // 在当前数据上下文中提交更改。
                db2.SubmitChanges();
            }

            // 检查是否像预期的那样提交了订单。
            using (Northwind db3 = new Northwind(connString))
            {
                Customer dbC1 = db3.Customers.Single(c => c.CustomerID == "ALFKI");

                Console.WriteLine("Customer {0}'s new address {1}", dbC1.CustomerID, dbC1.Address);
                Console.WriteLine();

                Customer dbC2 = db3.Customers.Single(c => c.CustomerID == "CHOPS");

                foreach (Order o in dbC2.Orders)
                {
                    Console.WriteLine("Order {0} belongs to customer {1}", o.OrderID, o.CustomerID);
                }
              
            }

            CleanupInsert10();
        }

        private void CleanupInsert10()
        {
            int[] c2OrderIDs = { 10365, 10507, 10535, 10573, 10677, 10682, 10856 };
            using (Northwind tempdb = new Northwind(connString))
            {
                Customer c1 = tempdb.Customers.Single(c => c.CustomerID == "ALFKI");
                c1.Address = "Obere Str. 57";
                foreach (Order o in tempdb.Orders.Where(p => c2OrderIDs.Contains(p.OrderID)))
                    o.CustomerID = "ANTON";
                tempdb.SubmitChanges();
            }
        }

        [Category("Insert/Update/Delete")]
        [Title("使用 Attach 更新和删除")]
        [Description("此示例从一个上下文提取实体，并使用 Attach 和 AttachAll " +
                     "附加来自其他上下文的实体，然后更新这两个实体，" +
                     "删除一个实体，添加另一个实体。更改被提交到" +
                     "数据库")]
        public void LinqToSqlInsert11()
        {
            // 通常，通过从其他层反序列化
            // XML 获取要附加的实体。
            // 此示例使用 LoadWith 在一个查询中预先加载客户和订单，
            //并禁用延迟加载。
            Customer cust = null;
            using (Northwind tempdb = new Northwind(connString))
            {
                DataLoadOptions shape = new DataLoadOptions();
                shape.LoadWith<Customer>(c => c.Orders);
                // 加载第一个客户实体及其订单。
                tempdb.LoadOptions = shape;
                tempdb.DeferredLoadingEnabled = false;
                cust = tempdb.Customers.First(x => x.CustomerID == "ALFKI");
            }

            Console.WriteLine("Customer {0}'s original phone number {1}", cust.CustomerID, cust.Phone);
            Console.WriteLine();

            foreach (Order o in cust.Orders)
            {
                Console.WriteLine("Customer {0} has order {1} for city {2}", o.CustomerID, o.OrderID, o.ShipCity);
            }

            Order orderA = cust.Orders.First();
            Order orderB = cust.Orders.First(x => x.OrderID > orderA.OrderID);

            using (Northwind db2 = new Northwind(connString))
            {
                // 将第一个实体附加到当前数据上下文，以跟踪更改。
                db2.Customers.Attach(cust);
                // 附加相关订单以进行跟踪; 否则将在提交时插入它们。
                db2.Orders.AttachAll(cust.Orders.ToList());

                // 更新客户。
                cust.Phone = "2345 5436";
                // 更新第一个订单。
                orderA.ShipCity = "Redmond";
                // 移除第二个订单。
                cust.Orders.Remove(orderB);
                // 创建一个新订单并将它添加到客户。
                Order orderC = new Order() { ShipCity = "New York" };
                Console.WriteLine("Adding new order");
                cust.Orders.Add(orderC);

                //现在提交所有更改
                db2.SubmitChanges();
            }

            // 验证是否按预期应用了更改。
            using (Northwind db3 = new Northwind(connString))
            {
                Customer newCust = db3.Customers.First(x => x.CustomerID == "ALFKI");
                Console.WriteLine("Customer {0}'s new phone number {1}", newCust.CustomerID, newCust.Phone);
                Console.WriteLine();

                foreach (Order o in newCust.Orders)
                {
                    Console.WriteLine("Customer {0} has order {1} for city {2}", o.CustomerID, o.OrderID, o.ShipCity);
                }
            }

            CleanupInsert11();
        }

        private void CleanupInsert11()
        {
            int[] alfkiOrderIDs = { 10643, 10692, 10702, 10835, 10952, 11011 };

            using (Northwind tempdb = new Northwind(connString))
            {
                Customer c1 = tempdb.Customers.Single(c => c.CustomerID == "ALFKI");
                c1.Phone = "030-0074321";
                Order oa = tempdb.Orders.Single(o => o.OrderID == 10643);
                oa.ShipCity = "Berlin";
                Order ob = tempdb.Orders.Single(o => o.OrderID == 10692);
                ob.CustomerID = "ALFKI";
                foreach (Order o in c1.Orders.Where(p => !alfkiOrderIDs.Contains(p.OrderID)))
                    tempdb.Orders.DeleteOnSubmit(o);

                tempdb.SubmitChanges();
            }
        }
        [Category("同时更改")]
        [Title("开放式并发 - 1")]
        [Description("这个示例和下一个示例演示开放式并发。在此示例中，" +
                     "其他用户在您读取数据之前对 Product 1 做出更新并将其更新提交，" +
                     "因此未发生冲突。")]
        public void LinqToSqlSimultaneous01() {
            Console.WriteLine("OTHER USER: ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~");

            // 打开与数据库的第二个连接以模拟
            // 将要对 Products 表进行更改的另一个用户
            Northwind otherUser_db = new Northwind(connString) { Log = db.Log };

            var otherUser_product = otherUser_db.Products.First(p => p.ProductID == 1);
            otherUser_product.UnitPrice = 999.99M;
            otherUser_db.SubmitChanges();

            Console.WriteLine("~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~");


            Console.WriteLine();
            Console.WriteLine("YOU:  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~");

            var product = db.Products.First(p => p.ProductID == 1);
            product.UnitPrice = 777.77M;

            bool conflict = false;
            try {
                db.SubmitChanges();
            }
            //OptimisticConcurrencyException
            catch (ChangeConflictException) {
                conflict = true;
            }

            Console.WriteLine();
            if (conflict) {
                Console.WriteLine("* * * OPTIMISTIC CONCURRENCY EXCEPTION * * *");
                Console.WriteLine("Another user has changed Product 1 since it was first requested.");
                Console.WriteLine("Backing out changes.");
            }
            else {
                Console.WriteLine("* * * COMMIT SUCCESSFUL * * *");
                Console.WriteLine("Changes to Product 1 saved.");
            }

            Console.WriteLine("~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~");



            Cleanup71();  // 还原以前的数据库状态
        }

        private void Cleanup71() {
            ClearDBCache();
            SetLogging(false);

            var product = db.Products.First(p => p.ProductID == 1);
            product.UnitPrice = 18.00M;
            db.SubmitChanges();
        }

        [Category("同时更改")]
        [Title("开放式并发 - 2")]
        [Description("这个示例和上一个示例演示开放式并发。在此示例中，" +
                     "其他用户在您读取数据之后、完成更新之前对 Product 1 做出更新并将其更新提交，" +
                     "因此导致了开放式并发冲突。" +
                     "此时将回滚您的更改，使您可以从数据库检索新更新的数据，" +
                     "并决定如何继续进行您自己的更新。")]
        public void LinqToSqlSimultaneous02()
        {
            Console.WriteLine("YOU:  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~");

            var product = db.Products.First(p => p.ProductID == 1);

            Console.WriteLine("~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~");


            Console.WriteLine();
            Console.WriteLine("OTHER USER: ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~");

            // 打开与数据库的第二个连接以模拟
            // 将要对 Products 表进行更改的另一个用户。
            Northwind otherUser_db = new Northwind(connString) { Log = db.Log };

            var otherUser_product = otherUser_db.Products.First(p => p.ProductID == 1);
            otherUser_product.UnitPrice = 999.99M;
            otherUser_db.SubmitChanges();

            Console.WriteLine("~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~");


            Console.WriteLine();
            Console.WriteLine("YOU (continued): ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~");

            product.UnitPrice = 777.77M;

            bool conflict = false;
            try {
                db.SubmitChanges();
            }
            //OptimisticConcurrencyException
            catch (ChangeConflictException) {
                conflict = true;
            }

            Console.WriteLine();
            if (conflict) {
                Console.WriteLine("* * * OPTIMISTIC CONCURRENCY EXCEPTION * * *");
                Console.WriteLine("Another user has changed Product 1 since it was first requested.");
                Console.WriteLine("Backing out changes.");
            }
            else {
                Console.WriteLine("* * * COMMIT SUCCESSFUL * * *");
                Console.WriteLine("Changes to Product 1 saved.");
            }

            Console.WriteLine("~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ");



            Cleanup72();  // 还原以前的数据库状态
        }

        private void Cleanup72() {
            ClearDBCache();
            SetLogging(false);

            // 事务失败后将自动回滚数据
        }

        [Category("同时更改")]
        [Title("事务 - 隐式")]
        [Description("此示例演示由 SubmitChanges 创建的" +
                     "隐式事务。更新 prod2 的 UnitsInStock 字段使" +
                     "该字段为负值，而这违反了" +
                     "服务器上的 CHECK 约束。这导致" +
                     "更新这两个产品的事务失败，此时将回滚所有更改。")]
        public void LinqToSqlSimultaneous03()
        {
            Console.WriteLine("*** BEFORE ***");
            ObjectDumper.Write(from p in db.Products where p.ProductID == 4 select p);
            ObjectDumper.Write(from p in db.Products where p.ProductID == 5 select p);


            Console.WriteLine();
            Console.WriteLine("*** UPDATE WITH IMPLICIT TRANSACTION ***");
            try {
                Product prod1 = db.Products.First(p => p.ProductID == 4);
                Product prod2 = db.Products.First(p => p.ProductID == 5);
                prod1.UnitsInStock -= 3;
                prod2.UnitsInStock -= 5;    // 错误: 这将使库存量变为负值
                // db.SubmitChanges 隐式使用事务，以便
                // 同时接受或同时拒绝两个更新
                db.SubmitChanges();
            }
            catch (System.Data.SqlClient.SqlException e) {
                Console.WriteLine(e.Message);
            }


            Console.WriteLine();
            Console.WriteLine("*** AFTER ***");
            ClearDBCache();
            ObjectDumper.Write(from p in db.Products where p.ProductID == 4 select p);
            ObjectDumper.Write(from p in db.Products where p.ProductID == 5 select p);



            Cleanup73();  // 还原以前的数据库状态
        }

        private void Cleanup73() {
            SetLogging(false);

            // 事务失败后将自动回滚数据
        }

        [Category("同时更改")]
        [Title("事务 - 显式")]
        [Description("此示例演示使用显式事务。" +
                     "通过在事务中加入对数据的读取以防止出现开放式并发异常，" +
                     "显式事务可以提供更多的保护。" +
                     "如同上一个查询中，更新 prod2 的 UnitsInStock 字段将使" +
                     "该字段为负值，而这违反了" +
                     "数据库中的 CHECK 约束。这导致" +
                     "更新这两个产品的事务失败，此时将回滚所有更改。")]
        public void LinqToSqlSimultaneous04()
        {
            Console.WriteLine("*** BEFORE ***");
            ObjectDumper.Write(from p in db.Products where p.ProductID == 4 select p);
            ObjectDumper.Write(from p in db.Products where p.ProductID == 5 select p);


            Console.WriteLine();
            Console.WriteLine("*** UPDATE WITH EXPLICIT TRANSACTION ***");
            // 显式使用 TransactionScope 可以确保
            // 在读写之间数据库中的数据
            // 不发生变化
            using (TransactionScope ts = new TransactionScope()) {
                try {
                    Product prod1 = db.Products.First(p => p.ProductID == 4);
                    Product prod2 = db.Products.First(p => p.ProductID == 5);
                    prod1.UnitsInStock -= 3;
                    prod2.UnitsInStock -= 5;    // 错误: 这将使库存量变为负值
                    db.SubmitChanges();
                }
                catch (System.Data.SqlClient.SqlException e) {
                    Console.WriteLine(e.Message);
                }
            }


            Console.WriteLine();
            Console.WriteLine("*** AFTER ***");
            ClearDBCache();
            ObjectDumper.Write(from p in db.Products where p.ProductID == 4 select p);
            ObjectDumper.Write(from p in db.Products where p.ProductID == 5 select p);



            Cleanup74();  // 还原以前的数据库状态
        }

        private void Cleanup74() {
            SetLogging(false);

            // 事务失败后将自动回滚数据
        }

        [Category("Null")]
        [Title("null")]
        [Description("此示例使用 null 值查找" +
                     "不隶属于另一个雇员的所有雇员。")]
        public void LinqToSqlNull01() {
            var q =
                from e in db.Employees
                where e.ReportsToEmployee == null
                select e;

            ObjectDumper.Write(q);
        }

        [Category("Null")]
        [Title("Nullable<T>.HasValue")]
        [Description("此示例使用 Nullable<T>.HasValue 查找" +
                     "不隶属于另一个雇员的所有雇员。")]
        public void LinqToSqlNull02()
        {
            var q =
                from e in db.Employees
                where !e.ReportsTo.HasValue
                select e;

            ObjectDumper.Write(q);
        }

        [Category("Null")]
        [Title("Nullable<T>.Value")]
        [Description("此示例将 Nullable<T>.Value 用于 " +
                     "返回前者的 EmployeeID 编号。" +
                     "请注意，" +
                     ".Value 为可选。")]
        public void LinqToSqlNull03()
        {
            var q =
                from e in db.Employees
                where e.ReportsTo.HasValue
                select new {e.FirstName, e.LastName, ReportsTo = e.ReportsTo.Value};

            ObjectDumper.Write(q);
        }

        [Category("字符串/日期函数")]
        [Title("字符串串联")]
        [Description("此示例使用 + 运算符在形成" +
                     "经计算得出的客户 Location 值过程中将字符串字段和" +
                     "字符串串联在一起。")]
        public void LinqToSqlString01()
        {
            var q =
                from c in db.Customers
                select new { c.CustomerID, Location = c.City + ", " + c.Country };

            ObjectDumper.Write(q, 1);
        }

        [Category("字符串/日期函数")]
        [Title("String.Length")]
        [Description("此示例使用 Length 属性查找名称短于 " +
                     "10 个字符的所有产品。")]
        public void LinqToSqlString02()
        {
            var q =
                from p in db.Products
                where p.ProductName.Length < 10
                select p;

            ObjectDumper.Write(q);
        }

        [Category("字符串/日期函数")]
        [Title("String.Contains(substring)")]
        [Description("此示例使用 Contains 方法查找所有其联系人姓名中" +
                     "包含“Anders”的客户。")]
        public void LinqToSqlString03()
        {
            var q =
                from c in db.Customers
                where c.ContactName.Contains("Anders")
                select c;

            ObjectDumper.Write(q);
        }

        [Category("字符串/日期函数")]
        [Title("String.IndexOf(substring)")]
        [Description("此示例使用 IndexOf 方法查找每个客户" +
                     "联系人姓名中出现第一个空格的位置。")]
        public void LinqToSqlString04()
        {
            var q =
                from c in db.Customers
                select new {c.ContactName, SpacePos = c.ContactName.IndexOf(" ")};

            ObjectDumper.Write(q);
        }

        [Category("字符串/日期函数")]
        [Title("String.StartsWith(prefix)")]
        [Description("此示例使用 StartsWith 方法查找" +
                     "联系人姓名以“Maria”开头的客户。")]
        public void LinqToSqlString05()
        {
            var q =
                from c in db.Customers
                where c.ContactName.StartsWith("Maria")
                select c;

            ObjectDumper.Write(q);
        }

        [Category("字符串/日期函数")]
        [Title("String.EndsWith(suffix)")]
        [Description("此示例使用 EndsWith 方法查找" +
                     "联系人姓名以“Anders”结尾的客户。")]
        public void LinqToSqlString06()
        {
            var q =
                from c in db.Customers
                where c.ContactName.EndsWith("Anders")
                select c;

            ObjectDumper.Write(q);
        }

        [Category("字符串/日期函数")]
        [Title("String.Substring(start)")]
        [Description("此示例使用 Substring 方法返回产品名称中" +
                     "从第四个字母开始的部分。")]
        public void LinqToSqlString07()
        {
            var q =
                from p in db.Products
                select p.ProductName.Substring(3);

            ObjectDumper.Write(q);
        }

        [Category("字符串/日期函数")]
        [Title("String.Substring(start, length)")]
        [Description("此示例使用 Substring 方法查找" +
                     "家庭电话号码第七位到第九位是“555”的雇员。")]
        public void LinqToSqlString08()
        {
            var q =
                from e in db.Employees
                where e.HomePhone.Substring(6, 3) == "555"
                select e;

            ObjectDumper.Write(q);
        }

        [Category("字符串/日期函数")]
        [Title("String.ToUpper()")]
        [Description("此示例使用 ToUpper 方法返回" +
                     "姓氏已转换为大写的雇员姓名。")]
        public void LinqToSqlString09()
        {
            var q =
                from e in db.Employees
                select new {LastName = e.LastName.ToUpper(), e.FirstName};

            ObjectDumper.Write(q);
        }

        [Category("字符串/日期函数")]
        [Title("String.ToLower()")]
        [Description("此示例使用 ToLower 方法返回" +
                     "已转换为小写的类别名称。")]
        public void LinqToSqlString10()
        {
            var q =
                from c in db.Categories
                select c.CategoryName.ToLower();

            ObjectDumper.Write(q);
        }

        [Category("字符串/日期函数")]
        [Title("String.Trim()")]
        [Description("此示例使用 Trim 方法返回雇员家庭电话号码的" +
                     "前五位，并移除前导和" +
                     "尾随空格。")]
        public void LinqToSqlString11() {
            var q =
                from e in db.Employees
                select e.HomePhone.Substring(0, 5).Trim();

            ObjectDumper.Write(q);
        }

        [Category("字符串/日期函数")]
        [Title("String.Insert(pos, str)")]
        [Description("此示例使用 Insert 方法返回第五位" +
                     "为 ) 的雇员电话号码的序列，" +
                     "并在 ) 后面插入一个 :。")]
        public void LinqToSqlString12() {
            var q =
                from e in db.Employees
                where e.HomePhone.Substring(4, 1) == ")"
                select e.HomePhone.Insert(5, ":");

            ObjectDumper.Write(q);
        }

        [Category("字符串/日期函数")]
        [Title("String.Remove(start)")]
        [Description("此示例使用 Remove 方法返回第 5 位" +
                     "为 ) 的雇员电话号码的序列，" +
                     "并移除从第十个字符开始的所有字符。")]
        public void LinqToSqlString13() {
            var q =
                from e in db.Employees
                where e.HomePhone.Substring(4, 1) == ")"
                select e.HomePhone.Remove(9);

            ObjectDumper.Write(q);
        }

        [Category("字符串/日期函数")]
        [Title("String.Remove(start, length)")]
        [Description("此示例使用 Remove 方法返回第 5 位" +
                     "为 ) 的雇员电话号码的序列，" +
                     "并移除前六个字符。")]
        public void LinqToSqlString14() {
            var q =
                from e in db.Employees
                where e.HomePhone.Substring(4, 1) == ")"
                select e.HomePhone.Remove(0, 6);

            ObjectDumper.Write(q);
        }

        [Category("字符串/日期函数")]
        [Title("String.Replace(find, replace)")]
        [Description("此示例使用 Replace 方法返回 Country 字段中" +
                     "UK 被替换为 United Kingdom 以及" +
                     "USA 被替换为 United States of America 的" +
                     "供应商信息。")]
        public void LinqToSqlString15() {
            var q =
                from s in db.Suppliers
                select new {
                    s.CompanyName,
                    Country = s.Country.Replace("UK", "United Kingdom")
                                       .Replace("USA", "United States of America")
                };

            ObjectDumper.Write(q);
        }

        
        [Category("字符串/日期函数")]
        [Title("DateTime.Year")]
        [Description("此示例使用 DateTime 的 Year 属性" +
                     "查找 1997 年下的订单。")]
        public void LinqToSqlString16() {
            var q =
                from o in db.Orders
                where o.OrderDate.Value.Year == 1997
                select o;

            ObjectDumper.Write(q);
        }

        [Category("字符串/日期函数")]
        [Title("DateTime.Month")]
        [Description("此示例使用 DateTime 的 Month 属性" +
                     "查找十二月下的订单。")]
        public void LinqToSqlString17() {
            var q =
                from o in db.Orders
                where o.OrderDate.Value.Month == 12
                select o;

            ObjectDumper.Write(q);
        }

        [Category("字符串/日期函数")]
        [Title("DateTime.Day")]
        [Description("此示例使用 DateTime 的 Day 属性" +
                     "查找某月 31 日下的订单。")]
        public void LinqToSqlString18() {
            var q =
                from o in db.Orders
                where o.OrderDate.Value.Day == 31
                select o;

            ObjectDumper.Write(q);
        }

        [Category("对象标识")]
        [Title("对象缓存 - 1")]
        [Description("此示例演示在两次执行相同查询时，是如何" +
                     "每次都引用内存中相同对象的。")]
        public void LinqToSqlObjectIdentity01() {
            Customer cust1 = db.Customers.First(c => c.CustomerID == "BONAP");
            Customer cust2 = db.Customers.First(c => c.CustomerID == "BONAP");

            Console.WriteLine("cust1 and cust2 refer to the same object in memory: {0}",
                              Object.ReferenceEquals(cust1, cust2));
        }

        [Category("对象标识")]
        [Title("对象缓存 - 2")]
        [Description("此示例演示在执行返回" +
                     "数据库中相同行的不同查询时，" +
                     "是如何每次都引用内存中相同对象的。")]
        public void LinqToSqlObjectIdentity02() {
            Customer cust1 = db.Customers.First(c => c.CustomerID == "BONAP");
            Customer cust2 = (
                from o in db.Orders
                where o.Customer.CustomerID == "BONAP"
                select o )
                .First()
                .Customer;

            Console.WriteLine("cust1 and cust2 refer to the same object in memory: {0}",
                              Object.ReferenceEquals(cust1, cust2));
        }

        [Category("对象加载")]
        [Title("延迟加载 - 1")]
        [Description("此示例演示如果原始查询未请求数据，" +
                     "在所检索到各个对象的链接中导航" +
                     "如何能导致触发对数据库的新查询。")]
        public void LinqToSqlObject01() {
            var custs =
                from c in db.Customers
                where c.City == "Sao Paulo"
                select c;

            foreach (var cust in custs) {
                foreach (var ord in cust.Orders) {
                    Console.WriteLine("CustomerID {0} has an OrderID {1}.", cust.CustomerID, ord.OrderID);
                }
            }
        }

        [Category("对象加载")]
        [Title("LoadWith - 预先加载 - 1")]
        [Description("此示例演示如何在原始查询过程中" +
                     "使用 LoadWith 请求相关数据，" +
                     "以便稍后在检索到的各个对象中导航时" +
                     "不需要对数据库进行额外的往返。")]
        public void LinqToSqlObject02() {

            Northwind db2 = new Northwind(connString);
            db2.Log = this.OutputStreamWriter;

            DataLoadOptions ds = new DataLoadOptions();
            ds.LoadWith<nwind.Customer>(p => p.Orders);

            db2.LoadOptions = ds;

            var custs = (
                from c in db2.Customers
                where c.City == "Sao Paulo"
                select c);

            foreach (var cust in custs) {
                foreach (var ord in cust.Orders) {
                    Console.WriteLine("CustomerID {0} has an OrderID {1}.", cust.CustomerID, ord.OrderID);
                }
            }
        }

        [Category("对象加载")]
        [Title("延迟加载 + AssociateWith")]
        [Description("此示例演示如果原始查询未请求数据，" +
                     "在所检索到各个对象的链接中导航" +
                     "如何以触发对数据库的新查询而告终。此示例还说明" +
                     "在延迟加载关系对象时可以使用 Assoicate With 筛选它们。")]
        public void LinqToSqlObject03() {

            Northwind db2 = new Northwind(connString);
            db2.Log = this.OutputStreamWriter;

            DataLoadOptions ds = new DataLoadOptions();
            ds.AssociateWith<nwind.Customer>(p => p.Orders.Where(o=>o.ShipVia > 1));

            db2.LoadOptions = ds;
            var custs =
                from c in db2.Customers
                where c.City == "London"
                select c;

            foreach (var cust in custs) {
                foreach (var ord in cust.Orders) {
                    foreach (var orderDetail in ord.OrderDetails) {
                        Console.WriteLine("CustomerID {0} has an OrderID {1} that ShipVia is {2} with ProductID {3} that has name {4}.",
                            cust.CustomerID, ord.OrderID, ord.ShipVia, orderDetail.ProductID, orderDetail.Product.ProductName);
                    }
                }
            }
        }

        [Category("对象加载")]
        [Title("LoadWith - 预先加载 + AssociateWith")]
        [Description("此示例演示如何在原始查询过程中" +
                     "使用 LoadWith 请求相关数据，" +
                     "以便稍后在检索到的各个对象中导航时" +
                     "此示例还说明在急切加载关系对象时可以" +
                     "使用 Assoicate With 对它们进行排序。")]
        public void LinqToSqlObject04() {

            Northwind db2 = new Northwind(connString);
            db2.Log = this.OutputStreamWriter;

            DataLoadOptions ds = new DataLoadOptions();
            ds.LoadWith<Customer>(p => p.Orders);
            ds.LoadWith<Order>(p => p.OrderDetails);
            ds.AssociateWith<Order>(p=>p.OrderDetails.OrderBy(o=>o.Quantity));

            db2.LoadOptions = ds;
         
            var custs = (
                from c in db2.Customers
                where c.City == "London"
                select c );

            foreach (var cust in custs) {
                foreach (var ord in cust.Orders) {
                    foreach (var orderDetail in ord.OrderDetails) {
                        Console.WriteLine("CustomerID {0} has an OrderID {1} with ProductID {2} that has Quantity {3}.",
                            cust.CustomerID, ord.OrderID, orderDetail.ProductID, orderDetail.Quantity );
                    }
                }
            }
        }

        private bool isValidProduct(Product p) {
            return p.ProductName.LastIndexOf('C') == 0;
        }

        [Category("对象加载")]
        [Title("延迟加载 - (1:M)")]
        [Description("此示例演示如果原始查询未请求数据，" +
             "在所检索到对象的各个关系中导航" +
             "如何能导致触发对数据库的新查询。")]
        public void LinqToSqlObject05() {
            var emps = from e in db.Employees
                       select e;

            foreach (var emp in emps) {
                foreach (var man in emp.Employees) {
                    Console.WriteLine("Employee {0} reported to Manager {1}.", emp.FirstName, man.FirstName);
                }
            }
        }

        [Category("对象加载")]
        [Title("延迟加载 - (Blob)")]
        [Description("此示例演示如果数据类型为 Link，" +
             "在所检索到各个对象的链接中导航" +
             "如何能停止触发对数据库的新查询。")]
        public void LinqToSqlObject06() {
            var emps = from c in db.Employees
                       select c;

            foreach (Employee emp in emps) {
                Console.WriteLine("{0}", emp.Notes);
            }
        }


        [Category("对象加载")]
        [Title("加载重写")]
        [Description("此示例重写 Category 类中的分部方法 LoadProducts。加载某种类别的产品时，"+ 
        "调用 LoadProducts 以加载此类别中未停产的产品。")]
        public void LinqToSqlObject07()
        {
            Northwind db2 = new Northwind(connString);

            DataLoadOptions ds = new DataLoadOptions();

            ds.LoadWith<nwind.Category>(p => p.Products);
            db2.LoadOptions = ds;

            var q = (
                from c in db2.Categories
                where c.CategoryID < 3
                select c);

            foreach (var cat in q)
            {
                foreach (var prod in cat.Products)
                {
                    Console.WriteLine("Category {0} has a ProductID {1} that Discontined = {2}.", cat.CategoryID, prod.ProductID, prod.Discontinued);
                }
            }
        }

        [Category("转换运算符")]
        [Title("AsEnumerable")]
        [Description("此示例使用 AsEnumerable 以便使用 Where 的客户端 IEnumerable<T> " +
                     "实现，而不是默认的 IQueryable<T> " +
                     "将在服务器上转换为 SQL 并执行的" +
                     "默认 Query(Of T) 实现。这很有必要，因为 Where 子句" +
                     "引用了用户定义的客户端方法 isValidProduct，" +
                     "该方法不能转换为 SQL。")]
        [LinkedMethod("isValidProduct")]
        public void LinqToSqlConversion01() {
            var q =
                from p in db.Products.AsEnumerable()
                where isValidProduct(p)
                select p;

            ObjectDumper.Write(q);
        }

        [Category("转换运算符")]
        [Title("ToArray")]
        [Description("此示例使用 ToArray 将查询直接计算为数组，" +
                     "并获取第 3 个元素。")]
        public void LinqToSqlConversion02() {
            var q =
                from c in db.Customers
                where c.City == "London"
                select c;

            Customer[] qArray = q.ToArray();
            ObjectDumper.Write(qArray[3], 0);
        }

        [Category("转换运算符")]
        [Title("ToList")]
        [Description("此示例使用 ToList 将查询直接计算为 List<T>。")]
        public void LinqToSqlConversion03() {
            var q =
                from e in db.Employees
                where e.HireDate >= new DateTime(1994, 1, 1)
                select e;

            List<Employee> qList = q.ToList();
            ObjectDumper.Write(qList, 0);
        }

        [Category("转换运算符")]
        [Title("ToDictionary")]
        [Description("此示例使用 ToDictionary 将查询和键表达式直接" +
                     "键表达式直接计算为 Dictionary<K, T>。")]
        public void LinqToSqlConversion04() {
            var q =
                from p in db.Products
                where p.UnitsInStock <= p.ReorderLevel && !p.Discontinued
                select p;

            Dictionary<int, Product> qDictionary = q.ToDictionary(p => p.ProductID);

            foreach (int key in qDictionary.Keys) {
                Console.WriteLine("Key {0}:", key);
                ObjectDumper.Write(qDictionary[key]);
                Console.WriteLine();
            }
        }

        [Category("直接 SQL")]
        [Title("SQL 查询")]
        [Description("此示例使用 ExecuteQuery<T> 执行任意 SQL 查询，" +
                     "并将所得的行映射为 Product 对象的序列。")]
        public void LinqToSqlDirect01() {
            var products = db.ExecuteQuery<Product>(
                "SELECT [Product List].ProductID, [Product List].ProductName " +
                "FROM Products AS [Product List] " +
                "WHERE [Product List].Discontinued = 0 " +
                "ORDER BY [Product List].ProductName;"
            );

            ObjectDumper.Write(products);
        }

        [Category("直接 SQL")]
        [Title("SQL 命令")]
        [Description("此示例使用 ExecuteCommand 执行任意 SQL 命令，" +
                     "本例中为将所有产品单价提高 1.00 的批量更新。")]
        public void LinqToSqlDirect02() {
            Console.WriteLine("*** BEFORE ***");
            ObjectDumper.Write(from p in db.Products select p);


            Console.WriteLine();
            Console.WriteLine("*** UPDATE ***");
            db.ExecuteCommand("UPDATE Products SET UnitPrice = UnitPrice + 1.00");


            Console.WriteLine();
            Console.WriteLine("*** AFTER ***");
            ClearDBCache();
            ObjectDumper.Write(from p in db.Products select p);



            Cleanup110();  // 还原以前的数据库状态
        }

        private void Cleanup110() {
            SetLogging(false);

            db.ExecuteCommand("UPDATE Products SET UnitPrice = UnitPrice - 1.00");
        }

        [Category("ADO.NET 互操作")]
        [Title("连接互操作")]
        [Description("此示例使用预先存在的 ADO.NET 连接创建 Northwind  对象，" +
                     "本例中的查询返回" +
                     "运费至少为 500.00 的所有订单。")]
        public void LinqToSqlAdo01() {
            // 创建标准 ADO.NET 连接:
            SqlConnection nwindConn = new SqlConnection(connString);
            nwindConn.Open();

            // ... 其他 ADO.NET 数据库访问代码 ... //

            // 使用预先存在的 ADO.NET 连接创建 DataContext:
            Northwind interop_db = new Northwind(nwindConn) { Log = db.Log };

            var orders =
                from o in interop_db.Orders
                where o.Freight > 500.00M
                select o;

            ObjectDumper.Write(orders);

            nwindConn.Close();
        }

        [Category("ADO.NET 互操作")]
        [Title("事务互操作")]
        [Description("此示例使用预先存在的 ADO.NET 连接创建 Northwind  对象，" +
                     "然后与此对象共享一个 ADO.NET 事务。此事务" +
                     "既用于通过 ADO.NET 连接执行 SQL 命令，又用于" +
                     "通过 Northwind 对象提交更改。当事务因违反 CHECK  约束而中止时，" +
                     "将回滚所有更改，包括" +
                     "通过 SqlCommand 做出的更改，以及通过" +
                     "Northwind 对象做出的更改。")]
        public void LinqToSqlAdo02() {
            var q =
                from p in db.Products
                where p.ProductID == 3
                select p;

            Console.WriteLine("*** BEFORE ***");
            ObjectDumper.Write(q);


            Console.WriteLine();
            Console.WriteLine("*** INSERT ***");

            // 创建标准 ADO.NET 连接:
            SqlConnection nwindConn = new SqlConnection(connString);
            nwindConn.Open();

            // 使用预先存在的 ADO.NET 连接创建 DataContext:
            Northwind interop_db = new Northwind(nwindConn) { Log = db.Log };

            SqlTransaction nwindTxn = nwindConn.BeginTransaction();

            try {
                SqlCommand cmd = new SqlCommand("UPDATE Products SET QuantityPerUnit = 'single item' WHERE ProductID = 3");
                cmd.Connection = nwindConn;
                cmd.Transaction = nwindTxn;
                cmd.ExecuteNonQuery();

                // 共享预先存在的 ADO.NET 事务:
                //interop_db.LocalTransaction = nwindTxn;
                interop_db.Transaction = nwindTxn;

                Product prod1 = interop_db.Products.First(p => p.ProductID == 4);
                Product prod2 = interop_db.Products.First(p => p.ProductID == 5);
                prod1.UnitsInStock -= 3;
                prod2.UnitsInStock -= 5;    // 错误: 这将使库存量变为负值

                interop_db.SubmitChanges();

                nwindTxn.Commit();
            }
            catch (Exception e) {
                // 如果事务发生错误，则将回滚所有更改，
                // 包其中包括直接通过 ADO.NET 连接进行的任何更改
                Console.WriteLine(e.Message);
                Console.WriteLine("Error submitting changes... all changes rolled back.");
            }

            nwindConn.Close();


            Console.WriteLine();
            Console.WriteLine("*** AFTER ***");
            ClearDBCache();
            ObjectDumper.Write(q);



            Cleanup112();  // 还原以前的数据库状态
        }
        private void Cleanup112() {
            SetLogging(false);

            // 事务失败后将自动回滚数据
        }

        [Category("存储过程")]
        [Title("标量返回")]
        [Description("此示例使用存储过程返回在“WA”地区的客户数。")]
        public void LinqToSqlStoredProc01() {
            int count = db.CustomersCountByRegion("WA");

            Console.WriteLine(count);
        }

        [Category("存储过程")]
        [Title("单一结果集")]
        [Description("此示例使用存储过程返回在伦敦的客户的 CustomerID、ContactName、ompanyName" +
        " 和 City。")]
        public void LinqToSqlStoredProc02() {
            ISingleResult<CustomersByCityResult> result = db.CustomersByCity("London");

            ObjectDumper.Write(result);
        }

        [Category("存储过程")]
        [Title("单个结果集 - 多个可能形状")]
        [Description("此示例使用存储过程返回" +
        "“WA”地区中的一组客户。返回的结果集形状取决于传入的参数。" +
        "如果参数等于 1，则返回所有客户属性。" +
        "如果参数等于 2，则返回 CustomerID、ContactName 和 CompanyName 属性。")]
        public void LinqToSqlStoredProc03() {
            Console.WriteLine("********** Whole Customer Result-set ***********");
            IMultipleResults result = db.WholeOrPartialCustomersSet(1);
            IEnumerable<WholeCustomersSetResult> shape1 = result.GetResult<WholeCustomersSetResult>();

            ObjectDumper.Write(shape1);

            Console.WriteLine();
            Console.WriteLine("********** Partial Customer Result-set ***********");
            result = db.WholeOrPartialCustomersSet(2);
            IEnumerable<PartialCustomersSetResult> shape2 = result.GetResult<PartialCustomersSetResult>();

            ObjectDumper.Write(shape2);
        }

        [Category("存储过程")]
        [Title("多个结果集")]
        [Description("此示例使用存储过程返回客户“SEVES”及其所有订单。")]
        public void LinqToSqlStoredProc04() {
            IMultipleResults result = db.GetCustomerAndOrders("SEVES");

            Console.WriteLine("********** Customer Result-set ***********");
            IEnumerable<CustomerResultSet> customer = result.GetResult<CustomerResultSet>();
            ObjectDumper.Write(customer);
            Console.WriteLine();

            Console.WriteLine("********** Orders Result-set ***********");
            IEnumerable<OrdersResultSet> orders = result.GetResult<OrdersResultSet>();
            ObjectDumper.Write(orders);
        }

        [Category("存储过程")]
        [Title("Out 参数")]
        [Description("此示例使用返回 Out 参数的存储过程。")]
        public void LinqToSqlStoredProc05() {
            decimal? totalSales = 0;
            string customerID = "ALFKI";

            // 输出参数是按引用传递的，以支持
            //参数为“in/out”的方案。在这种情况下，参数仅为
            //“out”。
            db.CustomerTotalSales(customerID, ref totalSales);

            Console.WriteLine("Total Sales for Customer '{0}' = {1:C}", customerID, totalSales);
        }


        [Category("用户定义的函数")]
        [Title("标量函数 - Select")]
        [Description("此示例演示在投影中使用用户定义的标量函数。")]
        public void LinqToSqlUserDefined01() {
            var q = from c in db.Categories
                    select new {c.CategoryID, TotalUnitPrice = db.TotalProductUnitPriceByCategory(c.CategoryID)};

            ObjectDumper.Write(q);
        }

        [Category("用户定义的函数")]
        [Title("标量函数 - Where")]
        [Description("此示例演示在 Where 子句中使用用户定义的标量函数。")]
        public void LinqToSqlUserDefined02()
        {
            var q = from p in db.Products
                    where p.UnitPrice == db.MinUnitPriceByCategory(p.CategoryID)
                    select p;

            ObjectDumper.Write(q);
        }

        [Category("用户定义的函数")]
        [Title("表值函数")]
        [Description("此示例演示从用户定义的表值函数进行选择。")]
        public void LinqToSqlUserDefined03()
        {
            var q = from p in db.ProductsUnderThisUnitPrice(10.25M)
                    where !(p.Discontinued ?? false)
                    select p;

            ObjectDumper.Write(q);
        }

        [Category("用户定义的函数")]
        [Title("表值函数 - Join")]
        [Description("此示例演示联接用户定义的表值函数的结果。")]
        public void LinqToSqlUserDefined04()
        {
            var q = from c in db.Categories
                    join p in db.ProductsUnderThisUnitPrice(8.50M) on c.CategoryID equals p.CategoryID into prods
                    from p in prods
                    select new {c.CategoryID, c.CategoryName, p.ProductName, p.UnitPrice};

            ObjectDumper.Write(q);
        }

        [Category("DataContext 函数")]
        [Title("CreateDatabase() 和 DeleteDatabase() ")]
        [Description("此示例使用 CreateDatabase() 基于 Mapping.cs 中的 NewCreateDB 架构创建新数据库，" +
                     "并使用 DeleteDatabase() 删除这个新创建的数据库。")]
        public void LinqToSqlDataContext01() {

            // 创建一个临时文件夹以存储新创建的数据库 
            string userTempFolder = Environment.GetEnvironmentVariable("SystemDrive") + @"\LinqToSqlSamplesTemp";
            Directory.CreateDirectory(userTempFolder);

            Console.WriteLine("********** Create NewCreateDB ***********");
            string userMDF = System.IO.Path.Combine(userTempFolder, @"NewCreateDB.mdf");
            string connStr = String.Format(@"Data Source=.\SQLEXPRESS;AttachDbFilename={0};Integrated Security=True;Connect Timeout=30;User Instance=True; Integrated Security = SSPI;", userMDF);
            NewCreateDB newDB = new NewCreateDB(connStr);

            newDB.CreateDatabase();

            if (newDB.DatabaseExists() && File.Exists(Path.Combine(userTempFolder, @"NewCreateDB.mdf")))
                Console.WriteLine("NewCreateDB is created");
            else
                Console.WriteLine("Error: NewCreateDB is not successfully created");

            Console.WriteLine();
            Console.WriteLine("********* Insert data and query *********");

            var newRow = new Person { PersonID = 1, PersonName = "Peter", Age = 28 };

            newDB.Persons.InsertOnSubmit(newRow);
            newDB.SubmitChanges();

            var q = from x in newDB.Persons
                    select x;

            ObjectDumper.Write(q);

            Console.WriteLine();
            Console.WriteLine("************ Delete NewCreateDB **************");
            newDB.DeleteDatabase();

            if (File.Exists(Path.Combine(userTempFolder, @"NewCreateDB.mdf")))
                Console.WriteLine("Error: NewCreateDB is not yet deleted");
            else
                Console.WriteLine("NewCreateDB is deleted");

            // 删除为此测试用例创建的临时文件夹 
            Directory.Delete(userTempFolder);

        }

        [Category("DataContext 函数")]
        [Title("DatabaseExists()")]
        [Description("此示例使用 DatabaseExists() 验证数据库是否存在。")]
        public void LinqToSqlDataContext02() {

            Console.WriteLine("*********** Verify Northwind DB exists ***********");
            if (db.DatabaseExists())
                Console.WriteLine("Northwind DB exists");
            else
                Console.WriteLine("Error: Northwind DB does not exist");

            Console.WriteLine();
            Console.WriteLine("********* Verify NewCreateDB does not exist **********");
            string userTempFolder = Environment.GetEnvironmentVariable("Temp");
            string userMDF = System.IO.Path.Combine(userTempFolder, @"NewCreateDB.mdf");
            NewCreateDB newDB = new NewCreateDB(userMDF);

            if (newDB.DatabaseExists())
                Console.WriteLine("Error: NewCreateDB DB exists");
            else
                Console.WriteLine("NewCreateDB DB does not exist");
        }

        [Category("DataContext 函数")]
        [Title("SubmitChanges()")]
        [Description("此示例演示必须调用 SubmitChanges() 才能" +
         "向实际的数据库提交更新。")]
        public void LinqToSql1DataContext03() {
            Customer cust = db.Customers.First(c=>c.CustomerID == "ALFKI");

            Console.WriteLine("********** Original Customer CompanyName **********");
            var q = from x in db.Customers
                     where x.CustomerID == "ALFKI"
                     select x.CompanyName;

            Console.WriteLine();
            ObjectDumper.Write(q);

            Console.WriteLine();
            Console.WriteLine("*********** Update and call SubmitChanges() **********");

            cust.CompanyName = "CSharp Programming Firm";
            db.SubmitChanges();

            Console.WriteLine();
            ObjectDumper.Write(q);

            Console.WriteLine();
            Console.WriteLine("*********** Update and did not call SubmitChanges() **********");

            cust.CompanyName = "LinqToSql Programming Firm";

            Console.WriteLine();
            ObjectDumper.Write(q);

            Cleanup122();  // 还原以前的数据库状态      
        }

        private void Cleanup122() {
            SetLogging(false);
            Customer cust = db.Customers.First(c=>c.CustomerID == "ALFKI");
            cust.CompanyName = "Alfreds Futterkiste";
            db.SubmitChanges();
        }
 
        [Category("DataContext 函数")]
        [Title("CreateQuery()")]
        [Description("此示例使用 CreateQuery() 从表达式创建 IQueryable<T>。")]
        public void LinqToSqlDataContext04() {

            var c1 = Expression.Parameter(typeof(Customer), "c");
            PropertyInfo City = typeof(Customer).GetProperty("City");

            var pred = Expression.Lambda<Func<Customer, bool>>(
                Expression.Equal(
                Expression.Property(c1, City),
                  Expression.Constant("Seattle")
               ), c1
            );

            IQueryable custs = db.Customers;
            Expression expr = Expression.Call(typeof(Queryable), "Where",
                new Type[] { custs.ElementType }, custs.Expression, pred);
            IQueryable<Customer> q = db.Customers.AsQueryable().Provider.CreateQuery<Customer>(expr);

            ObjectDumper.Write(q);
        }

        [Category("DataContext 函数")]
        [Title("日志")]
        [Description("此示例使用 Db.Log 关闭和打开数据库的日志记录显示。")]
        public void LinqToSqlDataContext05() {
            Console.WriteLine("**************** Turn off DB Log Display *****************");
            db.Log = null;
            var q = from c in db.Customers
                    where c.City == "London"
                    select c;

            ObjectDumper.Write(q);

            Console.WriteLine();
            Console.WriteLine("**************** Turn on DB Log Display  *****************");

            db.Log = this.OutputStreamWriter;
            ObjectDumper.Write(q);


        }

        [Category("高级")]
        [Title("动态查询 - Select")]
        [Description("此示例动态生成查询以返回每个客户的联系人姓名。" + 
                     "GetCommand 方法用于获取查询的已生成 T-SQL。")]
        public void LinqToSqlAdvanced01()
        {
            ParameterExpression param = Expression.Parameter(typeof(Customer), "c");
            Expression selector = Expression.Property(param, typeof(Customer).GetProperty("ContactName"));
            Expression pred = Expression.Lambda(selector, param);

            IQueryable<Customer> custs = db.Customers;
            Expression expr = Expression.Call(typeof(Queryable), "Select", new Type[] { typeof(Customer), typeof(string) }, Expression.Constant(custs), pred);
            IQueryable<string> query = db.Customers.AsQueryable().Provider.CreateQuery<string>(expr);

            System.Data.Common.DbCommand cmd = db.GetCommand(query);
            Console.WriteLine("Generated T-SQL:");
            Console.WriteLine(cmd.CommandText);
            Console.WriteLine();

            ObjectDumper.Write(query);
        }

        [Category("高级")]
        [Title("动态查询 - Where")]
        [Description("此示例动态生成查询以筛选在伦敦的客户。")]
        public void LinqToSqlAdvanced02()
        {
            IQueryable<Customer> custs = db.Customers;
            ParameterExpression param = Expression.Parameter(typeof(Customer), "c");
            Expression right = Expression.Constant("London");
            Expression left = Expression.Property(param, typeof(Customer).GetProperty("City"));
            Expression filter = Expression.Equal(left, right);
            Expression pred = Expression.Lambda(filter, param);

            Expression expr = Expression.Call(typeof(Queryable), "Where", new Type[] { typeof(Customer) }, Expression.Constant(custs), pred);
            IQueryable<Customer> query = db.Customers.AsQueryable().Provider.CreateQuery<Customer>(expr);
            ObjectDumper.Write(query);
        }

        [Category("高级")]
        [Title("动态查询 - OrderBy")]
        [Description("此示例动态生成查询以筛选在伦敦的客户，" +
                     " 并按 ContactName 对这些客户进行排序。")]
        public void LinqToSqlAdvanced03()
        {
            ParameterExpression param = Expression.Parameter(typeof(Customer), "c");

            Expression left = Expression.Property(param, typeof(Customer).GetProperty("City"));
            Expression right = Expression.Constant("London");
            Expression filter = Expression.Equal(left, right);
            Expression pred = Expression.Lambda(filter, param);

            IQueryable custs = db.Customers;

            Expression expr = Expression.Call(typeof(Queryable), "Where",
                new Type[] { typeof(Customer) }, Expression.Constant(custs), pred);

            expr = Expression.Call(typeof(Queryable), "OrderBy",
                new Type[] { typeof(Customer), typeof(string) }, custs.Expression, Expression.Lambda(Expression.Property(param, "ContactName"), param));


            IQueryable<Customer> query = db.Customers.AsQueryable().Provider.CreateQuery<Customer>(expr);

            ObjectDumper.Write(query);
        }


        [Category("高级")]
        [Title("动态查询 - Union")]
        [Description("此示例动态生成联合，以返回客户或雇员任意一方" +
                     "居住的所有国家/地区的序列。")]
        public void LinqToSqlAdvanced04()
        {
            IQueryable<Customer> custs = db.Customers;
            ParameterExpression param1 = Expression.Parameter(typeof(Customer), "e");
            Expression left1 = Expression.Property(param1, typeof(Customer).GetProperty("City"));
            Expression pred1 = Expression.Lambda(left1, param1);

            IQueryable<Employee> employees = db.Employees;
            ParameterExpression param2 = Expression.Parameter(typeof(Employee), "c");
            Expression left2 = Expression.Property(param2, typeof(Employee).GetProperty("City"));
            Expression pred2 = Expression.Lambda(left2, param2);

            Expression expr1 = Expression.Call(typeof(Queryable), "Select", new Type[] { typeof(Customer), typeof(string) }, Expression.Constant(custs), pred1);
            Expression expr2 = Expression.Call(typeof(Queryable), "Select", new Type[] { typeof(Employee), typeof(string) }, Expression.Constant(employees), pred2);

            IQueryable<string> q1 = db.Customers.AsQueryable().Provider.CreateQuery<string>(expr1);
            IQueryable<string> q2 = db.Employees.AsQueryable().Provider.CreateQuery<string>(expr2);

            var q3 = q1.Union(q2);

            ObjectDumper.Write(q3);
        }

        [Category("高级")]
        [Title("标识")]
        [Description("此示例演示如何插入新联系人以及从" +
                     "数据库检索新分配的 ContactID。")]
        public void LinqToSqlAdvanced05() {

            Console.WriteLine("ContactID is marked as an identity column");
            Contact con = new Contact() { CompanyName = "New Era", Phone = "(123)-456-7890" };

            db.Contacts.InsertOnSubmit(con);
            db.SubmitChanges();

            Console.WriteLine();
            Console.WriteLine("The ContactID of the new record is {0}", con.ContactID);

            cleanup130(con.ContactID);

        }
        void cleanup130(int contactID) {
            SetLogging(false);
            Contact con = db.Contacts.Where(c=>c.ContactID == contactID).First();
            db.Contacts.DeleteOnSubmit(con);
            db.SubmitChanges();
        }

        [Category("高级")]
        [Title("嵌套在 From 中")]
        [Description("此示例使用 OrderByDescending 和 Take 返回" +
                     "最贵的 10 种产品中断货的产品。")]
        public void LinqToSqlAdvanced06() {
            var prods = from p in db.Products.OrderByDescending(p => p.UnitPrice).Take(10)
                    where p.Discontinued
                    select p;

            ObjectDumper.Write(prods, 0);
        }

        [Category("视图")]
        [Title("查询 - 匿名类型")]
        [Description("此示例使用 SELECT 和 WHERE 返回到货城市" +
                     "为伦敦的发票的序列。")]
        public void LinqToSqlView01() {
            var q =
                from i in db.Invoices
                where i.ShipCity == "London"
                select new {i.OrderID, i.ProductName, i.Quantity, i.CustomerName};

            ObjectDumper.Write(q, 1);
        }

        [Category("视图")]
        [Title("视图 - 标识映射")]
        [Description("此示例使用 SELECT 查询 QuarterlyOrders。")]
        public void LinqToSqlView02() {
            var q =
                from qo in db.QuarterlyOrders
                select qo;

            ObjectDumper.Write(q, 1);
        }

        [Category("继承")]
        [Title("简单")]
        [Description("此示例返回所在城市为伦敦的所有联系人。")]
        public void LinqToSqlInheritance01()
        {
            var cons = from c in db.Contacts                       
                       select c;

            foreach (var con in cons) {
                Console.WriteLine("Company name: {0}", con.CompanyName);
                Console.WriteLine("Phone: {0}", con.Phone);
                Console.WriteLine("This is a {0}", con.GetType());
                Console.WriteLine();
            }

        }

        [Category("继承")]
        [Title("OfType")]
        [Description("此示例使用 OfType 返回所有客户联系人。")]
        public void LinqToSqlInheritance02()
        {
            var cons = from c in db.Contacts.OfType<CustomerContact>()
                       select c;

            ObjectDumper.Write(cons, 0);
        }

        [Category("继承")]
        [Title("IS")]
        [Description("此示例使用 IS 返回所有发货方联系人。")]
        public void LinqToSqlInheritance03()
        {
            var cons = from c in db.Contacts
                       where c is ShipperContact
                       select c;

            ObjectDumper.Write(cons, 0);
        }

        [Category("继承")]
        [Title("AS")]
        [Description("此示例使用 AS 返回 FullContact 或 null。")]
        public void LinqToSqlInheritance04()
        {
            var cons = from c in db.Contacts
                       select c as FullContact;

            ObjectDumper.Write(cons, 0);
        }

        [Category("继承")]
        [Title("Cast")]
        [Description("此示例使用强制转换检索居住在伦敦的客户联系人。")]
        public void LinqToSqlInheritance05()
        {
            var cons = from c in db.Contacts
                       where c.ContactType == "Customer" && ((CustomerContact)c).City == "London"
                       select c;

            ObjectDumper.Write(cons, 0);
        }

        [Category("继承")]
        [Title("UseAsDefault")]
        [Description("此示例演示未知联系人类型" +
                     "将被自动转换为默认联系人类型。")]
        public void LinqToSqlInheritance06()
        {
            Console.WriteLine("***** INSERT Unknown Contact using normal mapping *****");
            Contact contact = new Contact() { ContactType = null, CompanyName = "Unknown Company", Phone = "333-444-5555" };
            db.Contacts.InsertOnSubmit(contact);
            db.SubmitChanges();

            Console.WriteLine();
            Console.WriteLine("***** Query Unknown Contact using inheritance mapping *****");
            var con = (from c in db.Contacts
                       where c.CompanyName == "Unknown Company" && c.Phone == "333-444-5555"
                       select c).First();

            Console.WriteLine("The base class nwind.BaseContact had been used as default fallback type");
            Console.WriteLine("The discriminator value for con is unknown. So, its type should be {0}", con.GetType().ToString());

            cleanup140(contact.ContactID);

        }

        void cleanup140(int contactID) {
            SetLogging(false);
            Contact con = db.Contacts.Where(c=>c.ContactID == contactID).First();
            db.Contacts.DeleteOnSubmit(con);
            db.SubmitChanges();

        }

        [Category("继承")]
        [Title("插入新记录")]
        [Description("此示例演示如何创建新发货方联系人。")]
        public void LinqToSqlInheritance07()
        {
            Console.WriteLine("****** Before Insert Record ******");
            var ShipperContacts = from sc in db.Contacts.OfType<ShipperContact>()
                                     where sc.CompanyName == "Northwind Shipper"
                                     select sc;

            Console.WriteLine();
            Console.WriteLine("There is {0} Shipper Contact matched our requirement", ShipperContacts.Count());

            ShipperContact nsc = new ShipperContact() { CompanyName = "Northwind Shipper", Phone = "(123)-456-7890" };
            db.Contacts.InsertOnSubmit(nsc);
            db.SubmitChanges();

            Console.WriteLine();
            Console.WriteLine("****** After Insert Record ******");
            ShipperContacts = from sc in db.Contacts.OfType<ShipperContact>()
                               where sc.CompanyName == "Northwind Shipper"
                               select sc;

            Console.WriteLine();
            Console.WriteLine("There is {0} Shipper Contact matched our requirement", ShipperContacts.Count());
            db.Contacts.DeleteOnSubmit(nsc);
            db.SubmitChanges();

        }

        [Category("外部映射")]
        [Title("加载和使用外部映射")]
        [Description("此示例演示如何创建使用外部 XML 映射源的数据上下文。")]
        public void LinqToSqlExternal01()
        {
            // 加载映射源
            string path = Path.GetFullPath(Path.Combine(Application.StartupPath, @"..\..\Data\NorthwindMapped.map"));

            XmlMappingSource mappingSource = XmlMappingSource.FromXml(File.ReadAllText(path));

            // 使用映射源创建上下文
            Mapped.NorthwindMapped nw = new Mapped.NorthwindMapped(db.Connection, mappingSource);

            // 演示外部映射的实体的使用
            Console.WriteLine("****** Externally-mapped entity ******");
            Mapped.Order order = nw.Orders.First();
            ObjectDumper.Write(order, 1);

            // 演示外部映射的继承层次结构的使用
            var contacts = from c in nw.Contacts
                           where c is Mapped.EmployeeContact
                           select c;
            Console.WriteLine();
            Console.WriteLine("****** Externally-mapped inheritance hierarchy ******");
            foreach (var contact in contacts)
            {
                Console.WriteLine("Company name: {0}", contact.CompanyName);
                Console.WriteLine("Phone: {0}", contact.Phone);
                Console.WriteLine("This is a {0}", contact.GetType());
                Console.WriteLine();
            }

            // 演示外部映射的存储过程的使用
            Console.WriteLine();
            Console.WriteLine("****** Externally-mapped stored procedure ******");
            foreach (Mapped.CustOrderHistResult result in nw.CustomerOrderHistory("ALFKI"))
            {
                ObjectDumper.Write(result, 0);
            }

            // 演示外部映射的用户定义标量函数的使用
            Console.WriteLine();
            Console.WriteLine("****** Externally-mapped scalar UDF ******");
            var totals = from c in nw.Categories
                         select new { c.CategoryID, TotalUnitPrice = nw.TotalProductUnitPriceByCategory(c.CategoryID) };
            ObjectDumper.Write(totals);

            // 演示外部映射的用户定义表值函数的使用
            Console.WriteLine();
            Console.WriteLine("****** Externally-mapped table-valued UDF ******");
            var products = from p in nw.ProductsUnderThisUnitPrice(9.75M)
                           where p.SupplierID == 8
                           select p;
            ObjectDumper.Write(products);
        }

        [Category("开放式并发")]
        [Title("获取冲突信息")]
        [Description("此示例演示如何检索导致开放式并发异常的更改。")]
        public void LinqToSqlOptimistic01() {
            Console.WriteLine("YOU:  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~");
            Product product = db.Products.First(p => p.ProductID == 1);
            Console.WriteLine("~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~");
            Console.WriteLine();
            Console.WriteLine("OTHER USER: ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~");
            // 打开与数据库的第二个连接以模拟
            // 将要对 Products 表进行更改的另一个用户
            Northwind otherUser_db = new Northwind(connString) { Log = db.Log };
            Product otherUser_product = otherUser_db.Products.First(p => p.ProductID == 1);
            otherUser_product.UnitPrice = 999.99M;
            otherUser_product.UnitsOnOrder = 10;
            otherUser_db.SubmitChanges();
            Console.WriteLine("~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~");
            Console.WriteLine("YOU (continued): ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~");
            product.UnitPrice = 777.77M;

            bool conflictOccurred = false;
            try {
                db.SubmitChanges(ConflictMode.ContinueOnConflict);
            } catch (ChangeConflictException) {
                Console.WriteLine("* * * OPTIMISTIC CONCURRENCY EXCEPTION * * *");
                foreach (ObjectChangeConflict aConflict in /*ex.Conflicts*/db.ChangeConflicts) {
                    Product prod = (Product)aConflict.Object;
                    Console.WriteLine("The conflicting product has ProductID {0}", prod.ProductID);
                    Console.WriteLine();
                    Console.WriteLine("Conflicting members:");
                    Console.WriteLine();
                    foreach (MemberChangeConflict memConflict in aConflict.MemberConflicts) {
                        string name = memConflict.Member/*MemberInfo*/.Name;
                        string yourUpdate = memConflict.CurrentValue.ToString();
                        string original = memConflict.OriginalValue.ToString();
                        string theirUpdate = memConflict.DatabaseValue.ToString();
                        if (memConflict.IsModified/*HaveModified*/) {
                            Console.WriteLine("'{0}' was updated from {1} to {2} while you updated it to {3}",
                                              name, original, theirUpdate, yourUpdate);
                        } else {
                            Console.WriteLine("'{0}' was updated from {1} to {2}, you did not change it.",
                                name, original, theirUpdate);
                        }
                    }
                    Console.WriteLine();
                }
                conflictOccurred = true;
            }

            Console.WriteLine();
            if (!conflictOccurred) {

                Console.WriteLine("* * * COMMIT SUCCESSFUL * * *");
                Console.WriteLine("Changes to Product 1 saved.");
            }
            Console.WriteLine("~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ");

            ResetProducts(); // 清理
        }

        private void ResetProducts() {
            ClearDBCache();
            Northwind dbClean = new Northwind(connString);
            Product[] prod = new Product[4];
            decimal[] price = new decimal[4] { 18.00M, 19.00M, 10.00M, 22.00M };
            for (int i = 0; i < 4; i++) {
                prod[i] = dbClean.Products.First(p => p.ProductID == i + 1);
                prod[i].UnitPrice = price[i];
            }
            prod[0].UnitsInStock = 39;
            prod[0].UnitsOnOrder = 0;
            dbClean.SubmitChanges();
        }

        //OptimisticConcurrencyConflict
        private void WriteConflictDetails(IEnumerable<ObjectChangeConflict> conflicts) {
            //OptimisticConcurrencyConflict
            foreach (ObjectChangeConflict conflict in conflicts)
            {
                DescribeConflict(conflict);
            }
        }

        private void DescribeConflict(ObjectChangeConflict conflict) {
            Product prod = (Product)conflict.Object;
            Console.WriteLine("Optimistic Concurrency Conflict in product {0}", prod.ProductID);
            //OptimisticConcurrencyMemberConflict
            foreach (MemberChangeConflict memConflict in conflict.MemberConflicts/*GetMemberConflicts()*/) {
                string name = memConflict.Member.Name;
                string yourUpdate = memConflict.CurrentValue.ToString();
                string original = memConflict.OriginalValue.ToString();
                string theirUpdate = memConflict.DatabaseValue.ToString();
                if (memConflict.IsModified) {
                    Console.WriteLine("'{0}' was updated from {1} to {2} while you updated it to {3}",
                                      name, original, theirUpdate, yourUpdate);
                } else {
                    Console.WriteLine("'{0}' was updated from {1} to {2}, you did not change it.",
                        name, original, theirUpdate);
                }
            }
        }

        [Category("开放式并发")]
        [Title("解决冲突: 覆盖当前值")]
        [Description("此示例演示如何自动解决并发冲突。\r\num"
               + "“覆盖当前值”选项将新数据库值写入客户端对象。")]
        public void LinqToSqlOptimistic02()
        {
            Northwind otherUser_db = new Northwind(connString);
            db.Log = null;

            Product product = db.Products.First(p => p.ProductID == 1);
            Console.WriteLine("You retrieve the product 1, it costs {0}", product.UnitPrice);
            Console.WriteLine("There are {0} units in stock, {1} units on order", product.UnitsInStock, product.UnitsOnOrder);
            Console.WriteLine();

            Console.WriteLine("Another user changes the price to 22.22 and UnitsInStock to 22");
            Product otherUser_product = otherUser_db.Products.First(p => p.ProductID == 1);
            otherUser_product.UnitPrice = 22.22M;
            otherUser_product.UnitsInStock = 22;
            otherUser_db.SubmitChanges();

            Console.WriteLine("You set the price of product 1 to 1.01 and UnitsOnOrder to 11");
            product.UnitPrice = 1.01M;
            product.UnitsOnOrder = 11;
            try {
                Console.WriteLine("You submit");
                Console.WriteLine();
                db.SubmitChanges();
            } catch (ChangeConflictException) {
                WriteConflictDetails(db.ChangeConflicts); // 将更改后的对象/成员写入控制台
                Console.WriteLine();
                Console.WriteLine("Resolve by overwriting current values");
                db.ChangeConflicts.ResolveAll(RefreshMode.OverwriteCurrentValues);
                db.SubmitChanges();
            }
            Console.WriteLine();
            Northwind dbResult = new Northwind(connString);
            Product result = dbResult.Products.First(p => p.ProductID == 1);
            Console.WriteLine("Now product 1 has price={0}, UnitsInStock={1}, UnitsOnOrder={2}",
                result.UnitPrice, result.UnitsInStock, result.UnitsOnOrder);
            Console.WriteLine();
            ResetProducts(); // 清理
        }

        [Category("开放式并发")]
        [Title("解决冲突: 保留当前值")]
        [Description("此示例演示如何自动解决并发冲突。\r\num"
             + "“保留当前值”选项将所有内容都更改为此客户端的值。")]
        public void LinqToSqlOptimistic03()
        {
            Northwind otherUser_db = new Northwind(connString);
            db.Log = null;

            Product product = db.Products.First(p => p.ProductID == 1);
            Console.WriteLine("You retrieve the product 1, it costs {0}", product.UnitPrice);
            Console.WriteLine("There are {0} units in stock, {1} units on order", product.UnitsInStock, product.UnitsOnOrder);
            Console.WriteLine();

            Console.WriteLine("Another user changes the price to 22.22 and UnitsInStock to 22");
            Product otherUser_product = otherUser_db.Products.First(p => p.ProductID == 1);
            otherUser_product.UnitPrice = 22.22M;
            otherUser_product.UnitsInStock = 22;
            otherUser_db.SubmitChanges();

            Console.WriteLine("You set the price of product 1 to 1.01 and UnitsOnOrder to 11");
            product.UnitPrice = 1.01M;
            product.UnitsOnOrder = 11;
            try {
                Console.WriteLine("You submit");
                Console.WriteLine();
                db.SubmitChanges();
            } catch (ChangeConflictException) {
                WriteConflictDetails(db.ChangeConflicts); // 将更改后的对象/成员写入控制台
                Console.WriteLine();
                Console.WriteLine("Resolve by keeping current values");
                db.ChangeConflicts.ResolveAll(RefreshMode.KeepCurrentValues);
                db.SubmitChanges();
            }
            Console.WriteLine();
            Northwind dbResult = new Northwind(connString);
            Product result = dbResult.Products.First(p => p.ProductID == 1);
            Console.WriteLine("Now product 1 has price={0}, UnitsInStock={1}, UnitsOnOrder={2}",
                result.UnitPrice, result.UnitsInStock, result.UnitsOnOrder);
            Console.WriteLine();
            ResetProducts(); // 清理
        }

        [Category("开放式并发")]
        [Title("解决冲突: 保留更改")]
        [Description("此示例演示如何自动解决并发冲突。\r\num"
           + "“保留更改”选项保留当前用户做出的所有更改，"
           + "并合并其他用户做出的更改(如果当前用户未更改相应的字段)。")]
        public void LinqToSqlOptimistic04()
        {
            Northwind otherUser_db = new Northwind(connString);
            db.Log = null;

            Product product = db.Products.First(p => p.ProductID == 1);
            Console.WriteLine("You retrieve the product 1, it costs {0}", product.UnitPrice);
            Console.WriteLine("There are {0} units in stock, {1} units on order", product.UnitsInStock, product.UnitsOnOrder);
            Console.WriteLine();

            Console.WriteLine("Another user changes the price to 22.22 and UnitsInStock to 22");
            Product otherUser_product = otherUser_db.Products.First(p => p.ProductID == 1);
            otherUser_product.UnitPrice = 22.22M;
            otherUser_product.UnitsInStock = 22;
            otherUser_db.SubmitChanges();

            Console.WriteLine("You set the price of product 1 to 1.01 and UnitsOnOrder to 11");
            product.UnitPrice = 1.01M;
            product.UnitsOnOrder = 11;
            try {
                Console.WriteLine("You submit");
                Console.WriteLine();
                db.SubmitChanges();
            } catch (ChangeConflictException) {
                WriteConflictDetails(db.ChangeConflicts); // 将更改后的对象/成员写入控制台
                Console.WriteLine();
                Console.WriteLine("Resolve by keeping changes");
                db.ChangeConflicts.ResolveAll(RefreshMode.KeepChanges);
                db.SubmitChanges();
            }
            Console.WriteLine();
            Northwind dbResult = new Northwind(connString);
            Product result = dbResult.Products.First(p => p.ProductID == 1);
            Console.WriteLine("Now product 1 has price={0}, UnitsInStock={1}, UnitsOnOrder={2}",
                result.UnitPrice, result.UnitsInStock, result.UnitsOnOrder);
            Console.WriteLine();
            ResetProducts(); // 清理
        }

        [Category("开放式并发")]
        [Title("自定义解决规则")]
        [Description("演示使用 MemberConflict.Resolve 来编写自定义解决规则。\r\num")]
        public void LinqToSqlOptimistic05()
        {
            Northwind otherUser_db = new Northwind(connString);
            db.Log = null;

            Product product = db.Products.First(p => p.ProductID == 1);
            Console.WriteLine("You retrieve the product 1, it costs {0}", product.UnitPrice);
            Console.WriteLine("There are {0} units in stock, {1} units on order", product.UnitsInStock, product.UnitsOnOrder);
            Console.WriteLine();

            Console.WriteLine("Another user changes the price to 22.22 and UnitsOnOrder to 2");
            Product otherUser_product = otherUser_db.Products.First(p => p.ProductID == 1);
            otherUser_product.UnitPrice = 22.22M;
            otherUser_product.UnitsOnOrder = 2;
            otherUser_db.SubmitChanges();

            Console.WriteLine("You set the price of product 1 to 1.01 and UnitsOnOrder to 11");
            product.UnitPrice = 1.01M;
            product.UnitsOnOrder = 11;
            bool needsSubmit = true;
            while (needsSubmit) {
                try {
                    Console.WriteLine("You submit");
                    Console.WriteLine();
                    needsSubmit = false;
                    db.SubmitChanges();
                } catch (ChangeConflictException) {
                    needsSubmit = true;
                    WriteConflictDetails(db.ChangeConflicts); // 将更改后的对象/成员写入控制台
                    Console.WriteLine();
                    Console.WriteLine("Resolve by higher price / order");
                    foreach (ObjectChangeConflict conflict in db.ChangeConflicts) {
                        conflict.Resolve(RefreshMode.KeepChanges);
                        foreach (MemberChangeConflict memConflict in conflict.MemberConflicts) {
                            if (memConflict.Member.Name == "UnitPrice") {
                                //始终使用最高价格
                                decimal theirPrice = (decimal)memConflict.DatabaseValue;
                                decimal yourPrice = (decimal)memConflict.CurrentValue;
                                memConflict.Resolve(Math.Max(theirPrice, yourPrice));
                            } else if (memConflict.Member.Name == "UnitsOnOrder") {
                                //始终使用金额更高的订单
                                short theirOrder = (short)memConflict.DatabaseValue;
                                short yourOrder = (short)memConflict.CurrentValue;
                                memConflict.Resolve(Math.Max(theirOrder, yourOrder));
                            }
                        }
                    }
                }
            }
            Northwind dbResult = new Northwind(connString);
            Product result = dbResult.Products.First(p => p.ProductID == 1);
            Console.WriteLine("Now product 1 has price={0}, UnitsOnOrder={1}",
                result.UnitPrice, result.UnitsOnOrder);
            Console.WriteLine();
            ResetProducts(); // 清理
        }

        [Category("开放式并发")]
        [Title("Submit 带 FailOnFirstConflict")]
        [Description("Submit(FailOnFirstConflict) 在检测到第一个冲突时引发开放式并发异常。\r\num"
           + "每次只能处理一个异常，因此您对每个冲突都必须提交。")]
        public void LinqToSqlOptimistic06()
        {
            db.Log = null;
            Northwind otherUser_db = new Northwind(connString);

            // 您加载 3 种产品
            Product[] prod = db.Products.OrderBy(p => p.ProductID).Take(3).ToArray();
            for (int i = 0; i < 3; i++) {
                Console.WriteLine("You retrieve the product {0}, it costs {1}", i + 1, prod[i].UnitPrice);
            }
            // 其他用户更改这些产品
            Product[] otherUserProd = otherUser_db.Products.OrderBy(p => p.ProductID).Take(3).ToArray();
            for (int i = 0; i < 3; i++) {
                decimal otherPrice = (i + 1) * 111.11M;
                Console.WriteLine("Other user changes the price of product {0} to {1}", i + 1, otherPrice);
                otherUserProd[i].UnitPrice = otherPrice;
            }
            otherUser_db.SubmitChanges();
            Console.WriteLine("Other user submitted changes");

            // 您更改自己加载的产品
            for (int i = 0; i < 3; i++) {
                decimal yourPrice = (i + 1) * 1.01M;
                Console.WriteLine("You set the price of product {0} to {1}", i + 1, yourPrice);
                prod[i].UnitPrice = yourPrice;
            }

            // 提交
            bool needsSubmit = true;
            while (needsSubmit) {
                try {
                    Console.WriteLine("======= You submit with FailOnFirstConflict =======");
                    needsSubmit = false;
                    db.SubmitChanges(ConflictMode.FailOnFirstConflict);
                } catch (ChangeConflictException) {
                    foreach (ObjectChangeConflict conflict in db.ChangeConflicts) {
                        DescribeConflict(conflict); // 将更改写入控制台
                        Console.WriteLine("Resolve conflict with KeepCurrentValues");
                        conflict.Resolve(RefreshMode.KeepCurrentValues);
                    }
                    needsSubmit = true;
                }
            }
            Northwind dbResult = new Northwind(connString);
            for (int i = 0; i < 3; i++) {
                Product result = dbResult.Products.First(p => p.ProductID == i + 1);
                Console.WriteLine("Now the product {0} has price {1}", i + 1, result.UnitPrice);
            }
            ResetProducts(); // 清理
        }

        [Category("开放式并发")]
        [Title("Submit 带 ContinueOnConflict")]
        [Description("Submit(ContinueOnConflict) 收集所有并发冲突并在检测到最后一个冲突时引发异常。\r\num"
           + "所有冲突在一个 Catch 语句中处理。\r\num"
           + "此次更新之前，也有可能其他用户更新过相同的对象，因此有可能引发另一起开放式并发异常，需要再次处理。")]
        public void LinqToSqlOptimistic07()
        {
            db.Log = null;
            Northwind otherUser_db = new Northwind(connString);

            // 您加载 3 种产品
            Product[] prod = db.Products.OrderBy(p => p.ProductID).Take(3).ToArray();
            for (int i = 0; i < 3; i++) {
                Console.WriteLine("You retrieve the product {0}, it costs {1}", i + 1, prod[i].UnitPrice);
            }
            // 其他用户更改这些产品
            Product[] otherUserProd = otherUser_db.Products.OrderBy(p => p.ProductID).Take(3).ToArray();
            for (int i = 0; i < 3; i++) {
                decimal otherPrice = (i + 1) * 111.11M;
                Console.WriteLine("Other user changes the price of product {0} to {1}", i + 1, otherPrice);
                otherUserProd[i].UnitPrice = otherPrice;
            }
            otherUser_db.SubmitChanges();
            Console.WriteLine("Other user submitted changes");

            // 您更改自己加载的产品
            for (int i = 0; i < 3; i++) {
                decimal yourPrice = (i + 1) * 1.01M;
                Console.WriteLine("You set the price of product {0} to {1}", i + 1, yourPrice);
                prod[i].UnitPrice = yourPrice;
            }

            // 提交
            bool needsSubmit = true;
            while (needsSubmit) {
                try {
                    Console.WriteLine("======= You submit with ContinueOnConflict =======");
                    needsSubmit = false;
                    db.SubmitChanges(ConflictMode.ContinueOnConflict);
                } catch (ChangeConflictException) {
                    foreach (ObjectChangeConflict conflict in db.ChangeConflicts) {
                        DescribeConflict(conflict); // 将更改写入控制台
                        Console.WriteLine("Resolve conflict with KeepCurrentValues");
                        conflict.Resolve(RefreshMode.KeepCurrentValues);
                    }
                    needsSubmit = true;
                }
            }
            Northwind dbResult = new Northwind(connString);
            for (int i = 0; i < 3; i++) {
                Product result = dbResult.Products.First(p => p.ProductID == i + 1);
                Console.WriteLine("Now the product {0} has price {1}", i + 1, result.UnitPrice);
            }
            ResetProducts(); // 清理
        }


      
        [Category("扩展性分部方法")]
        [Title("带有 OnValidate 的 Update")]
        [Description("此示例重写 Order 类的 OnValidate 分部方法。更新订单时，它验证"
        +" ShipVia 不能大于 100，否则将引发异常且不将更新发送到数据库。")]
        public void LinqToSqlExtensibility01()
        {

            var order = (from o in db.Orders
                         where o.OrderID == 10355
                         select o).First();
            ObjectDumper.Write(order);
            Console.WriteLine();

            Console.WriteLine("***** Update Order to set ShipVia to 120 and submit changes ******");
            Console.WriteLine();

            order.ShipVia = 120;
            try
            {
                db.SubmitChanges();
            }
            catch (Exception e)
            {
                Console.WriteLine("****** Catch exception throw by OnValidate() ******");
                Console.WriteLine(e.Message);
            }

            Console.WriteLine();
            Console.WriteLine("****** verify that order's ShipVia didn't get changed in db. ******");
            Northwind db2 = new Northwind(connString);
            var order2 = (from o in db2.Orders
                          where o.OrderID == 10355
                          select o).First();

            ObjectDumper.Write(order2);

             
        }

       

        public override void InitSample() {
            ClearDBCache();
            SetLogging(true);
        }

        public void ClearDBCache() {
            // 创建一个新的 Northwind 对象，以空对象缓存从头开始
            // 新 Northwind 对象将重复利用活动的 ADO.NET 连接

            TextWriter oldLog;
            if (db == null)
                oldLog = null;
            else
                oldLog = db.Log;

            db = new Northwind(connString) { Log = oldLog };
        }

        public void SetLogging(bool logging) {
            if (logging) {
                db.Log = this.OutputStreamWriter;
            }
            else {
                db.Log = null;
            }
        }

        public override void HandleException(Exception e) {
            Console.WriteLine("Unable to connect to the Northwind database on SQL Server instance.");
            Console.WriteLine("Try restarting SQL Server or your computer.");
            Console.WriteLine();
            Console.WriteLine("If the problem persists, see the Troubleshooting section of the Readme for tips.");
            Console.WriteLine();
            Console.WriteLine();
            Console.WriteLine("Exception:");
            base.HandleException(e);
        }

        public class Name {
            public string FirstName;
            public string LastName;
        }
    }
}
