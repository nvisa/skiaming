// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
//版权所有(C) Microsoft Corporation。保留所有权利。

using System;
using System.Collections;   
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Windows.Forms;
using System.Xml.Linq;
using SampleSupport;

//版本 Mad01

namespace SampleQueries {
    [Title("101 个 LINQ 查询示例")]
    [Prefix("Linq")]
    public class LinqSamples : SampleHarness 
    {        
        private readonly static string dataPath = Path.GetFullPath(Path.Combine(Application.StartupPath, @"..\..\Data\"));
        
        # region Sample Data Collections

        // 以 Northwnd 数据为基础的示例对象，
        // 但与后者并不完全相同。

        public class Customer
        {
            public string CustomerID { get; set; }
            public string CompanyName { get; set; }
            public string Address { get; set; }
            public string City { get; set; }
            public string Region { get; set; }
            public string PostalCode { get; set; }
            public string Country { get; set; }
            public string Phone { get; set; }
            public string Fax { get; set; }
            public Order[] Orders { get; set; }
        }

        public class Order
        {
            public int OrderID { get; set; }
            public DateTime OrderDate { get; set; }
            public decimal Total { get; set; }
        }

        public class Product
        {
            public int ProductID { get; set; } 
            public string ProductName { get; set; }
            public string Category { get; set; }
            public decimal UnitPrice { get; set; }
            public int UnitsInStock { get; set; }
        }

        public class Supplier
        {
            public string SupplierName { get; set; }
            public string Address { get; set; }
            public string City { get; set; }
            public string Country { get; set; }
        }
        
        private List<Product> productList;
        private List<Customer> customerList;
        private List<Supplier> supplierList;

        #endregion

        [Category("限制运算符")]
        [Title("Where - 简单用法 1")]
        [Description("此示例使用 Where 子句查找数组中值小于 5 的所有元素。")]
        public void Linq1() {
            int[] numbers = { 5, 4, 1, 3, 9, 8, 6, 7, 2, 0 };

            var lowNums =
                from num in numbers
                where num < 5
                select num;
        
            Console.WriteLine("Numbers < 5:");
            foreach (var x in lowNums) {
                Console.WriteLine(x);
            }
        }
        
        [Category("限制运算符")]
        [Title("Where - 简单用法 2")]
        [Description("此示例使用 Where 子句查找所有缺货产品。")]
        public void Linq2() {
            List<Product> products = GetProductList();

            var soldOutProducts =
                from prod in products
                where prod.UnitsInStock == 0
                select prod;
            
            Console.WriteLine("Sold out products:");
            foreach (var product in soldOutProducts) {
                Console.WriteLine("{0} is sold out!", product.ProductName);
            }
        }
        
        [Category("限制运算符")]
        [Title("Where - 简单用法 3")]
        [Description("此示例使用 Where 子句查找所有有货且" +
                     "单价大于 3.00 的产品。")]
        public void Linq3() {
            List<Product> products = GetProductList();

            var expensiveInStockProducts =
                from prod in products
                where prod.UnitsInStock > 0 && prod.UnitPrice > 3.00M
                select prod;
            
            Console.WriteLine("In-stock products that cost more than 3.00:");
            foreach (var product in expensiveInStockProducts) {
                Console.WriteLine("{0} is in stock and costs more than 3.00.", product.ProductName);
            }
        }
        
        [Category("限制运算符")]
        [Title("Where - 深化")]
        [Description("此示例使用 Where 子句查找所有在华盛顿的客户，" +
                     "然后，它使用 Foreach 循环来循环访问属于每个客户的订单集合。")]
        public void Linq4() {
            List<Customer> customers = GetCustomerList();

            var waCustomers =
                from cust in customers
                where cust.Region == "WA"
                select cust;

            Console.WriteLine("Customers from Washington and their orders:");
            foreach (var customer in waCustomers)
            {
                Console.WriteLine("Customer {0}: {1}", customer.CustomerID, customer.CompanyName);
                foreach (var order in customer.Orders)
                {
                    Console.WriteLine("  Order {0}: {1}", order.OrderID, order.OrderDate);
                }
            }
        }
        
        [Category("限制运算符")]
        [Title("Where - 带索引")]
        [Description("此示例演示带索引的 Where 子句，该子句返回其名称短于" +
                    "其值的数字。")]
        public void Linq5() {
            string[] digits = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };

            var shortDigits = digits.Where((digit, index) => digit.Length < index);
        
            Console.WriteLine("Short digits:");
            foreach (var d in shortDigits)
            {
                Console.WriteLine("The word {0} is shorter than its value.", d);
            }
        }

        [Category("投影运算符")]
        [Title("Select - 简单用法 1")]
        [Description("此示例使用 Select 子句生成一个整数序列，其中每个整数都比" +
                     "现有整数数组中的相应整数大一。")]
        public void Linq6() {
            int[] numbers = { 5, 4, 1, 3, 9, 8, 6, 7, 2, 0 };

            var numsPlusOne =
                from num in numbers
                select num + 1;
            
            Console.WriteLine("Numbers + 1:");
            foreach (var i in numsPlusOne) {
                Console.WriteLine(i);
            }
        } 
        
        [Category("投影运算符")]
        [Title("Select - 简单用法 2")]
        [Description("此示例使用 Select 语句返回产品名称序列。")]
        public void Linq7() {
            List<Product> products = GetProductList();

            var productNames =
                from prod in products
                select prod.ProductName;
            
            Console.WriteLine("Product Names:");
            foreach (var productName in productNames) {
                Console.WriteLine(productName);
            }
        }

        [Category("投影运算符")]
        [Title("Select - 转换")]
        [Description("此示例使用 Select 语句生成表示" +
                     "整数序列文本形式的字符串的序列。")]
        public void Linq8() {
            int[] numbers = { 5, 4, 1, 3, 9, 8, 6, 7, 2, 0 };
            string[] strings = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };

            var textNums = 
                from num in numbers
                select strings[num];
            
            Console.WriteLine("Number strings:");
            foreach (var str in textNums) {
                Console.WriteLine(str);
            }           
        }

        [Category("投影运算符")]
        [Title("Select - 匿名类型 1")]
        [Description("此示例使用 Select 语句生成包含 " +
                     "原始数组中每个单词的大写和小写形式的序列。")]
        public void Linq9() {
            string[] words = { "aPPLE", "BlUeBeRrY", "cHeRry" };

            var upperLowerWords =
                from word in words
                select new {Upper = word.ToUpper(), Lower = word.ToLower()};

            foreach (var wordPair in upperLowerWords) {
                Console.WriteLine("Uppercase: {0}, Lowercase: {1}", wordPair.Upper, wordPair.Lower);
            }
        }

        [Category("投影运算符")]
        [Title("Select - 匿名类型 2")]
        [Description("此示例使用 Select 语句生成一个序列，其中包含" +
                     "数字的文本表示形式和一个指示这些文本的长度是偶数还是奇数的布尔值。")]
        public void Linq10() {
            int[] numbers = { 5, 4, 1, 3, 9, 8, 6, 7, 2, 0 };
            string[] strings = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };

            var digitOddEvens =
                from num in numbers
                select new {Digit = strings[num], Even = (num % 2 == 0)};

            foreach (var digit in digitOddEvens) {
                Console.WriteLine("The digit {0} is {1}.", digit.Digit, digit.Even ? "even" : "odd");
            }
        }
        
        [Category("投影运算符")]
        [Title("Select - 匿名类型 3")]
        [Description("此示例使用 Select 语句生成包含" +
                     "产品某些属性(包括在所得类型中重命名为 Price 的 UnitPrice)" +
                     "的序列。")]
        public void Linq11() {
            List<Product> products = GetProductList();

            var productInfos =
                from prod in products
                select new {prod.ProductName, prod.Category, Price = prod.UnitPrice};
            
            Console.WriteLine("Product Info:");
            foreach (var productInfo in productInfos) {
                Console.WriteLine("{0} is in the category {1} and costs {2} per unit.", productInfo.ProductName, productInfo.Category, productInfo.Price);
            }
        } 

        [Category("投影运算符")]
        [Title("Select - 带索引")]
        [Description("此示例使用带索引的 Select 子句确定数组中整数的值是否" +
                     "与其在数组中的位置相符。")]
        public void Linq12() {
            int[] numbers = { 5, 4, 1, 3, 9, 8, 6, 7, 2, 0 };

            var numsInPlace = numbers.Select((num, index) => new {Num = num, InPlace = (num == index)});
        
            Console.WriteLine("Number: In-place?");
            foreach (var n in numsInPlace) {
                Console.WriteLine("{0}: {1}", n.Num, n.InPlace);
            }
        }

        [Category("投影运算符")]
        [Title("Select - 筛选")]
        [Description("此示例结合使用 select 和 where，以建立一个" +
                     "返回每个小于 5 的数字的文本形式的简单查询。")]
        public void Linq13() {
            int[] numbers = { 5, 4, 1, 3, 9, 8, 6, 7, 2, 0 };
            string[] digits = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };

            var lowNums =
                from num in numbers
                where num < 5
                select digits[num];
            
            Console.WriteLine("Numbers < 5:");
            foreach (var num in lowNums) {
                Console.WriteLine(num);
            }       
        }
        
        [Category("投影运算符")]
        [Title("SelectMany - 复合 From 1")]
        [Description("此示例使用复合 From 子句进行查询，该查询" +
                     "返回来自两个数组的所有数字对，其中 numbersA 数字小于" +
                     "numbersB 数字。")]
        public void Linq14() {
            int[] numbersA = { 0, 2, 4, 5, 6, 8, 9 };
            int[] numbersB = { 1, 3, 5, 7, 8 };

            var pairs =
                from a in numbersA
                from b in numbersB
                where a < b
                select new {a, b};
        
            Console.WriteLine("Pairs where a < b:");
            foreach (var pair in pairs) {
                Console.WriteLine("{0} is less than {1}", pair.a, pair.b);
            }
        }
        
        [Category("投影运算符")]
        [Title("SelectMany - 复合 From 2")]
        [Description("此示例使用复合 From 子句选择" +
                     "订单总价小于 500.00 的所有订单。")]
        public void Linq15() {
            List<Customer> customers = GetCustomerList();

            var orders =
                from cust in customers
                from order in cust.Orders
                    where order.Total < 500.00M
                    select new {cust.CustomerID, order.OrderID, order.Total};
        
            ObjectDumper.Write(orders);
        }

        [Category("投影运算符")]
        [Title("SelectMany - 复合 From 3")]
        [Description("此示例使用复合 From 子句选择" +
                     "1998 年或之后下的所有订单。")]
        public void Linq16() {
            List<Customer> customers = GetCustomerList();

            var orders =
                from cust in customers
                from order in cust.Orders
                    where order.OrderDate >= new DateTime(1998, 1, 1)
                    select new {cust.CustomerID, order.OrderID, order.OrderDate};
        
            ObjectDumper.Write(orders);
        }

        [Category("投影运算符")]
        [Title("SelectMany - 带 Let")]
        [Description("此示例使用复合 From 子句选择" +
                     "订单总价大于 2000.00 的所有订单，并使用 Let 语句避免" +
                     "重复请求总价。")] 
        public void Linq17() {
            List<Customer> customers = GetCustomerList();

            var orders =
                from cust in customers
                from order in cust.Orders
                let total = order.Total
                where total >= 2000.0M
                select new {cust.CustomerID, order.OrderID, total};

            ObjectDumper.Write(orders);
        }
    
        [Category("投影运算符")]
        [Title("SelectMany - 复合 From")]
        [Description("此示例使用复合 From 子句，以便可以在选择客户的订单之前" +
                     "对客户进行筛选。这使得查询更高效，因为" +
                     "不必选择然后放弃华盛顿以外的客户的订单。")]
        public void Linq18() {
            List<Customer> customers = GetCustomerList();

            DateTime cutoffDate = new DateTime(1997, 1, 1);

            var orders =
                from cust in customers
                where cust.Region == "WA"
                from order in cust.Orders
                    where order.OrderDate >= cutoffDate
                    select new {cust.CustomerID, order.OrderID};
        
            ObjectDumper.Write(orders);
        }
        
        [Category("投影运算符")]
        [Title("SelectMany - 带索引")]
        [Description("此示例使用带索引的 SelectMany 子句选择所有订单， " +
                     "同时按从查询返回这些订单的顺序引用" +
                     "客户。")]
        public void Linq19() {
            List<Customer> customers = GetCustomerList();

            var customerOrders =
                customers.SelectMany(
                    (cust, custIndex) =>
                    cust.Orders.Select(o => "Customer #" + (custIndex + 1) +
                                            " has an order with OrderID " + o.OrderID));

            ObjectDumper.Write(customerOrders);
        }
        
        [Category("分区运算符")]
        [Title("Take - 简单用法")]
        [Description("此示例使用 Take 获取源数据表中的 " +
                     "所有元素。")]
        public void Linq20() {
            int[] numbers = { 5, 4, 1, 3, 9, 8, 6, 7, 2, 0 };
            
            var first3Numbers = numbers.Take(3);
            
            Console.WriteLine("First 3 numbers:");
            foreach (var n in first3Numbers) {
                Console.WriteLine(n);
            }
        }
        
        [Category("分区运算符")]
        [Title("Take - 嵌套")]
        [Description("此示例使用 Take 获取华盛顿客户的前 3 个 " +
                     "的所有订单。")]
        public void Linq21() {
            List<Customer> customers = GetCustomerList();

            var first3WAOrders = (
                from cust in customers
                from order in cust.Orders
                where cust.Region == "WA"
                select new {cust.CustomerID, order.OrderID, order.OrderDate} )
                .Take(3);
            
            Console.WriteLine("First 3 orders in WA:");
            foreach (var order in first3WAOrders) {
                ObjectDumper.Write(order);
            }
        }

        [Category("分区运算符")]
        [Title("Skip - 简单用法")]
        [Description("此示例使用 Skip 获取数组中除前 4 个元素以外的" +
                     "所有元素。")]
        public void Linq22() {
            int[] numbers = { 5, 4, 1, 3, 9, 8, 6, 7, 2, 0 };
            
            var allButFirst4Numbers = numbers.Skip(4);
            
            Console.WriteLine("All but first 4 numbers:");
            foreach (var n in allButFirst4Numbers) {
                Console.WriteLine(n);
            }
        }
        
        [Category("分区运算符")]
        [Title("Skip - 嵌套")]
        [Description("此示例使用 Take 获取美国客户前 2 个订单之外的 " +
                     "的所有订单。")]
        public void Linq23() {
            List<Customer> customers = GetCustomerList();

            var waOrders =
                from cust in customers
                from order in cust.Orders
                where cust.Region == "WA"
                select new {cust.CustomerID, order.OrderID, order.OrderDate};
        
            var allButFirst2Orders = waOrders.Skip(2);
            
            Console.WriteLine("All but first 2 orders in WA:");
            foreach (var order in allButFirst2Orders) {
                ObjectDumper.Write(order);
            }
        }    
            
        [Category("分区运算符")]
        [Title("TakeWhile - 简单用法")]
        [Description("此示例使用 TakeWhile 返回从数组开头起的所有元素，" +
                     "直到读到不小于 6 的数字。")]
        public void Linq24() {
            int[] numbers = { 5, 4, 1, 3, 9, 8, 6, 7, 2, 0 };
            
            var firstNumbersLessThan6 = numbers.TakeWhile(n => n < 6);
            
            Console.WriteLine("First numbers less than 6:");
            foreach (var num in firstNumbersLessThan6) {
                Console.WriteLine(num);
            }
        }
        
        [Category("分区运算符")]
        [Title("TakeWhile - 带索引")]
        [Description("此示例使用 TakeWhile 返回从数组开头起的所有元素，" +
                    "直到碰到小于自身在数组中位置" +
                    "总字符数。")]
        public void Linq25() {
            int[] numbers = { 5, 4, 1, 3, 9, 8, 6, 7, 2, 0 };
            
            var firstSmallNumbers = numbers.TakeWhile((n, index) => n >= index);
            
            Console.WriteLine("First numbers not less than their position:");
            foreach (var n in firstSmallNumbers) {
                Console.WriteLine(n);
            }
        }
        
        [Category("分区运算符")]
        [Title("SkipWhile - 简单用法")]
        [Description("此示例使用 SkipWhile 获取数组中从第一个" +
                    "能被 3 整除的元素开始的所有元素。")]
        public void Linq26() {
            int[] numbers = { 5, 4, 1, 3, 9, 8, 6, 7, 2, 0 };
            
            // 在 lambda 表达式中，“n”是输入参数，连续标识
            // 集合中的每个元素。它被推断为
            // int 类型，因为数字是一个 int 数组。
            var allButFirst3Numbers = numbers.SkipWhile(n => n % 3 != 0);
            
            Console.WriteLine("All elements starting from first element divisible by 3:");
            foreach (var n in allButFirst3Numbers) {
                Console.WriteLine(n);
            }
        }
        
        [Category("分区运算符")]
        [Title("SkipWhile - 带索引")]
        [Description("此示例使用 SkipWhile 获取数组中从第一个" +
                    "小于自身位置的元素开始的所有元素。")]
        public void Linq27() {
            int[] numbers = { 5, 4, 1, 3, 9, 8, 6, 7, 2, 0 };
            
            var laterNumbers = numbers.SkipWhile((n, index) => n >= index);
            
            Console.WriteLine("All elements starting from first element less than its position:");
            foreach (var n in laterNumbers) {
                Console.WriteLine(n);
            }
        }
        
        [Category("排序运算符")]
        [Title("OrderBy - 简单用法 1")]
        [Description("此示例使用 orderby 按字母顺序对单词列表进行排序。")]
        public void Linq28() {
            string[] words = { "cherry", "apple", "blueberry" };
            
            var sortedWords =
                from word in words
                orderby word
                select word;
            
            Console.WriteLine("The sorted list of words:");
            foreach (var w in sortedWords) {
                Console.WriteLine(w);
            }
        }

        [Category("排序运算符")]
        [Title("OrderBy - 简单用法 2")]
        [Description("此示例使用 orderby 按长度对单词列表进行排序。")]
        public void Linq29() {
            string[] words = { "cherry", "apple", "blueberry" };
            
            var sortedWords =
                from word in words
                orderby word.Length
                select word;
            
            Console.WriteLine("The sorted list of words (by length):");
            foreach (var w in sortedWords) {
                Console.WriteLine(w);
            }
        }
        
        [Category("排序运算符")]
        [Title("OrderBy - 简单用法 3")]
        [Description("此示例使用 Orderby 按名称对产品列表进行排序。" +
                    "在子句末尾使用“descending”关键字可执行反向排序。")]
        public void Linq30() {
            List<Product> products = GetProductList();

            var sortedProducts =
                from prod in products
                orderby prod.ProductName
                select prod;
        
            ObjectDumper.Write(sortedProducts);
        }

        // 用于排序运算符的自定义比较器
        public class CaseInsensitiveComparer : IComparer<string>
        {
            public int Compare(string x, string y)
            {
                return string.Compare(x, y, StringComparison.OrdinalIgnoreCase);
            }
        }

        [Category("排序运算符")]
        [Title("OrderBy - 比较器")]
        [Description("此示例使用 OrderBy 子句和自定义比较器" +
                     "对数组中的单词进行不区分大小写的排序。")]
        [LinkedClass("CaseInsensitiveComparer")]
        public void Linq31() {
            string[] words = { "aPPLE", "AbAcUs", "bRaNcH", "BlUeBeRrY", "ClOvEr", "cHeRry"};
            
            var sortedWords = words.OrderBy(a => a, new CaseInsensitiveComparer());
                
            ObjectDumper.Write(sortedWords);
        }
        
        [Category("排序运算符")]
        [Title("OrderByDescending - 简单用法 1")]
        [Description("此示例使用 orderby 和 descending 按从高到低的顺序" +
                     "对 double 类型的数据表进行排序。")]
        public void Linq32() {
            double[] doubles = { 1.7, 2.3, 1.9, 4.1, 2.9 };
            
            var sortedDoubles =
                from d in doubles
                orderby d descending
                select d;
            
            Console.WriteLine("The doubles from highest to lowest:");
            foreach (var d in sortedDoubles) {
                Console.WriteLine(d);
            }
        }
        
        [Category("排序运算符")]
        [Title("OrderByDescending - 简单用法 2")]
        [Description("此示例使用 orderby 按库存量从高到低的顺序" +
                     "从高到低对产品的数据表进行排序。")]
        public void Linq33() {
            List<Product> products = GetProductList();

            var sortedProducts =
                from prod in products
                orderby prod.UnitsInStock descending
                select prod;
        
            ObjectDumper.Write(sortedProducts);
        }

        [Category("排序运算符")]
        [Title("OrderByDescending - 比较器")]
        [Description("此示例使用方法语法来调用 OrderByDescending，因为它" +
                    " 使您可以使用自定义比较器。")]
        [LinkedClass("CaseInsensitiveComparer")]
        public void Linq34() {
            string[] words = { "aPPLE", "AbAcUs", "bRaNcH", "BlUeBeRrY", "ClOvEr", "cHeRry"};
            
            var sortedWords = words.OrderByDescending(a => a, new CaseInsensitiveComparer());
                
            ObjectDumper.Write(sortedWords);
        }
        
        [Category("排序运算符")]
        [Title("ThenBy - 简单用法")]
        [Description("此示例使用复合 OrderBy 对产品列表" +
                     "先按其名称长度排序，再按名称自身的字母顺序排序。")]
        public void Linq35() {
            string[] digits = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };

            var sortedDigits =
                from digit in digits 
                orderby digit.Length, digit
                select digit;
        
            Console.WriteLine("Sorted digits:");
            foreach (var d in sortedDigits) {
                Console.WriteLine(d);
            }
        }

        [Category("排序运算符")]
        [Title("ThenBy - 比较器")]
        [Description("此示例中的第一个查询使用方法语法来调用 OrderBy 和 ThenBy 及自定义比较器，" +
                     "对数组中的单词先按单词长度排序，再进行不区分大小写的排序。" +
                     "后面的两个查询显示了执行相同任务的其他方法。")]
        [LinkedClass("CaseInsensitiveComparer")]
        public void Linq36() {
            string[] words = { "aPPLE", "AbAcUs", "bRaNcH", "BlUeBeRrY", "ClOvEr", "cHeRry"};
            
            var sortedWords =
                words.OrderBy(a => a.Length)
                     .ThenBy(a => a, new CaseInsensitiveComparer());

            // 其他方法。TODO 在此处使用 ThenBy 是否正确? 它似乎可用于此示例数组。
            var sortedWords2 =
                from word in words
                orderby word.Length
                select word;

            var sortedWords3 = sortedWords2.ThenBy(a => a, new CaseInsensitiveComparer());
                
            ObjectDumper.Write(sortedWords);

            ObjectDumper.Write(sortedWords3);
        }
        
        [Category("排序运算符")]
        [Title("ThenByDescending - 简单用法")]
        [Description("此示例使用复合 Order By 对产品列表" +
                     "先按类别排序，再按单价从高到低排序。")]
        public void Linq37() {
            List<Product> products = GetProductList();

            var sortedProducts =
                from prod in products
                orderby prod.Category, prod.UnitPrice descending
                select prod;
        
            ObjectDumper.Write(sortedProducts);
        }

        [Category("排序运算符")]
        [Title("ThenByDescending - 比较器")]
        [Description("此示例使用 OrderBy 子句和 ThenBy 子句及自定义比较器" +
                     "对数组中的单词先按单词长度排序，" +
                     "再进行不区分大小写的降序排序。")]
        [LinkedClass("CaseInsensitiveComparer")]
        public void Linq38() {
            string[] words = { "aPPLE", "AbAcUs", "bRaNcH", "BlUeBeRrY", "ClOvEr", "cHeRry"};
            
            var sortedWords =
                words.OrderBy(a => a.Length)
                     .ThenByDescending(a => a, new CaseInsensitiveComparer());
                
            ObjectDumper.Write(sortedWords);
        }
        
        [Category("排序运算符")]
        [Title("Reverse")]
        [Description("此示例使用 Reverse 将数组中所有第二个字母为“i”的数字，" +
                     "以其在原始数组中的相反顺序创建列表。")]
        public void Linq39() {
            string[] digits = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
            
            var reversedIDigits = (
                from digit in digits
                where digit[1] == 'i'
                select digit)
                .Reverse();
            
            Console.WriteLine("A backwards list of the digits with a second character of 'i':");
            foreach (var d in reversedIDigits) {
                Console.WriteLine(d);
            }             
        }

        [Category("分组运算符")]
        [Title("GroupBy - 简单用法 1")]
        [Description("此示例使用 Group By 按" +
                    "数字除以 5 所得的余数划分数字列表。")]
        public void Linq40() {
            int[] numbers = { 5, 4, 1, 3, 9, 8, 6, 7, 2, 0 };
            
            var numberGroups =
                from num in numbers
                group num by num % 5 into numGroup
                select new { Remainder = numGroup.Key, Numbers = numGroup };
            
            foreach (var grp in numberGroups) {
                Console.WriteLine("Numbers with a remainder of {0} when divided by 5:", grp.Remainder);
                foreach (var n in grp.Numbers) {
                    Console.WriteLine(n);
                }
            }
        }
        
        [Category("分组运算符")]
        [Title("GroupBy - 简单用法 2")]
        [Description("此示例使用 Group By 按" +
                     "单词的首字母划分单词列表。")]
        public void Linq41() {
            string[] words = { "blueberry", "chimpanzee", "abacus", "banana", "apple", "cheese" };
            
            var wordGroups =
                from num in words
                group num by num[0] into grp
                select new { FirstLetter = grp.Key, Words = grp };
            
            foreach (var wordgrp in wordGroups) {
                Console.WriteLine("Words that start with the letter '{0}':", wordgrp.FirstLetter);
                foreach (var word in wordgrp.Words) {
                    Console.WriteLine(word);
                }
            }
        }
        
        [Category("分组运算符")]
        [Title("GroupBy - 简单用法 3")]
        [Description("此示例使用 Group By 按类别划分产品列表。")]
        public void Linq42() {
            List<Product> products = GetProductList();

            var orderGroups =
                from prod in products
                group prod by prod.Category into prodGroup
                select new { Category = prodGroup.Key, Products = prodGroup };
                           
            ObjectDumper.Write(orderGroups, 1);
        }
        
        [Category("分组运算符")]
        [Title("GroupBy - 嵌套")]
        [Description("此示例使用 Group By 先按年再按月" +
                     "划分每个客户的订单列表。")]
        public void Linq43() {
            List<Customer> customers = GetCustomerList();

            var customerOrderGroups = 
                from cust in customers
                select
                    new {cust.CompanyName, 
                         YearGroups =
                             from order in cust.Orders
                             group order by order.OrderDate.Year into yearGroup
                             select
                                 new {Year = yearGroup.Key,
                                      MonthGroups = 
                                          from order in yearGroup
                                          group order by order.OrderDate.Month into MonthGroup
                                          select new { Month = MonthGroup.Key, Orders = MonthGroup }
                                     }
                        };
                           
            ObjectDumper.Write(customerOrderGroups, 3);
        }
        
        public class AnagramEqualityComparer : IEqualityComparer<string>
        {
            public bool Equals(string x, string y) {
                return getCanonicalString(x) == getCanonicalString(y);
            }

            public int GetHashCode(string obj) {
                return getCanonicalString(obj).GetHashCode();
            }
            
            private string getCanonicalString(string word) {
                char[] wordChars = word.ToCharArray();
                Array.Sort<char>(wordChars);
                return new string(wordChars);
            }
        }
        
        [Category("分组运算符")]
        [Title("GroupBy - 比较器")]
        [Description("此示例使用 GroupBy 方法语法以及使互为变位词的单词相匹配的自定义比较器来" +
                     "划分数组中经过裁剪的元素。")]
        [LinkedClass("AnagramEqualityComparer")]
        public void Linq44() {
            string[] anagrams = {"from   ", " salt", " earn ", "  last   ", " near ", " form  "};

            var orderGroups = anagrams.GroupBy(w => w.Trim(), new AnagramEqualityComparer());
                           
            ObjectDumper.Write(orderGroups, 1);
        }
        
        [Category("分组运算符")]
        [Title("GroupBy - 比较器、映射")]
        [Description("此示例使用 GroupBy 方法以及使互为变位词的单词相匹配的自定义比较器来" +
                     "对数组的已剪裁元素进行分区，" +
                     "然后将结果转换为大写。")]
        [LinkedClass("AnagramEqualityComparer")]
        public void Linq45() {
            string[] anagrams = {"from   ", " salt", " earn ", "  last   ", " near ", " form  "};

            var orderGroups = anagrams.GroupBy(
                        w => w.Trim(), 
                        a => a.ToUpper(),
                        new AnagramEqualityComparer()
                        );
                           
            ObjectDumper.Write(orderGroups, 1);
        }
                     
        [Category("集合运算符")]
        [Title("Distinct - 1")]
        [Description("此示例使用 Distinct 移除 300 的因子" +
                    "数据表中重复的数据行。")]
        public void Linq46() {
            int[] factorsOf300 = { 2, 2, 3, 5, 5 };
            
            var uniqueFactors = factorsOf300.Distinct();

            Console.WriteLine("Prime factors of 300:");
            foreach (var f in uniqueFactors) {
                Console.WriteLine(f);
            }
        }
        
        [Category("集合运算符")]
        [Title("Distinct - 2")]
        [Description("此示例使用 Distinct 查找唯一类别名称。")]
        public void Linq47() {
            List<Product> products = GetProductList();
            
            var categoryNames = (
                from prod in products
                select prod.Category)
                .Distinct();
                                                 
            Console.WriteLine("Category names:");
            foreach (var n in categoryNames) {
                Console.WriteLine(n);
            }
        }
        
        [Category("集合运算符")]
        [Title("Union - 1")]
        [Description("此示例使用 Union 创建一个序列，其中包含" +
                     "来自两个数组的唯一值。")]
        public void Linq48() {
            int[] numbersA = { 0, 2, 4, 5, 6, 8, 9 };
            int[] numbersB = { 1, 3, 5, 7, 8 };
            
            var uniqueNumbers = numbersA.Union(numbersB);
            
            Console.WriteLine("Unique numbers from both arrays:");
            foreach (var n in uniqueNumbers) {
                Console.WriteLine(n);
            }
        }
        
        [Category("集合运算符")]
        [Title("Union - 2")]
        [Description("此示例使用 Union 方法创建一个序列，其中包含" +
                     "产品名和客户名中唯一的首字母。Union 只能通过方法语法使用。")]
        public void Linq49() {
            List<Product> products = GetProductList();
            List<Customer> customers = GetCustomerList();
            
            var productFirstChars =
                from prod in products
                select prod.ProductName[0];
            var customerFirstChars =
                from cust in customers
                select cust.CompanyName[0];
            
            var uniqueFirstChars = productFirstChars.Union(customerFirstChars);
            
            Console.WriteLine("Unique first letters from Product names and Customer names:");
            foreach (var ch in uniqueFirstChars) {
                Console.WriteLine(ch);
            }
        }
        
        [Category("集合运算符")]
        [Title("Intersect - 1")]
        [Description("此示例使用 Intersect 创建一个序列，其中包含" +
                    "两个数组所共有的值。")]
        public void Linq50() {
            int[] numbersA = { 0, 2, 4, 5, 6, 8, 9 };
            int[] numbersB = { 1, 3, 5, 7, 8 };
            
            var commonNumbers = numbersA.Intersect(numbersB);
            
            Console.WriteLine("Common numbers shared by both arrays:");
            foreach (var n in commonNumbers) {
                Console.WriteLine(n);
            }
        }
        
        [Category("集合运算符")]
        [Title("Intersect - 2")]
        [Description("此示例使用 Intersect 创建一个序列，其中包含" +
                     "产品名和客户名所共有的首字母。")]
        public void Linq51() {
            List<Product> products = GetProductList();
            List<Customer> customers = GetCustomerList();
            
            var productFirstChars =
                from prod in products
                select prod.ProductName[0];
            var customerFirstChars =
                from cust in customers
                select cust.CompanyName[0];
            
            var commonFirstChars = productFirstChars.Intersect(customerFirstChars);
            
            Console.WriteLine("Common first letters from Product names and Customer names:");
            foreach (var ch in commonFirstChars) {
                Console.WriteLine(ch);
            }
        }
        
        [Category("集合运算符")]
        [Title("Except - 1")]
        [Description("此示例使用 Except 创建一个序列，其中包含 numbersA 数据表中有" +
                     "但 numbersB 中没有的值。")]
        public void Linq52() {
            int[] numbersA = { 0, 2, 4, 5, 6, 8, 9 };
            int[] numbersB = { 1, 3, 5, 7, 8 };
            
            IEnumerable<int> aOnlyNumbers = numbersA.Except(numbersB);
            
            Console.WriteLine("Numbers in first array but not second array:");
            foreach (var n in aOnlyNumbers) {
                Console.WriteLine(n);
            }
        }
    
        [Category("集合运算符")]
        [Title("Except - 2")]
        [Description("此示例使用 Except 创建一个序列，其中包含" +
                     "并非也是客户名首字母的产品名首字母。")]
        public void Linq53() {
            List<Product> products = GetProductList();
            List<Customer> customers = GetCustomerList();
            
            var productFirstChars =
                from prod in products
                select prod.ProductName[0];
            var customerFirstChars =
                from cust in customers
                select cust.CompanyName[0];
            
            var productOnlyFirstChars = productFirstChars.Except(customerFirstChars);
            
            Console.WriteLine("First letters from Product names, but not from Customer names:");
            foreach (var ch in productOnlyFirstChars) {
                Console.WriteLine(ch);
            }
        }
        
        [Category("转换运算符")]
        [Title("ToArray")]
        [Description("此示例使用 ToArray 将序列直接计算为数组。")]
        public void Linq54() {
            double[] doubles = { 1.7, 2.3, 1.9, 4.1, 2.9 };
            
            var sortedDoubles =
                from d in doubles
                orderby d descending
                select d;
            var doublesArray = sortedDoubles.ToArray();
            
            Console.WriteLine("Every other double from highest to lowest:");
            for (int d = 0; d < doublesArray.Length; d += 2) {
                Console.WriteLine(doublesArray[d]);
            }             
        }
        
        [Category("转换运算符")]
        [Title("ToList")]
        [Description("此示例使用 ToList 将序列直接计算为 List<T>。")]
        public void Linq55() {
            string[] words = { "cherry", "apple", "blueberry" };
            
            var sortedWords =
                from w in words
                orderby w
                select w;
            var wordList = sortedWords.ToList();
            
            Console.WriteLine("The sorted word list:");
            foreach (var w in wordList) {
                Console.WriteLine(w);
            }             
        }
        
        [Category("转换运算符")]
        [Title("ToDictionary")]
        [Description("此示例使用 ToDictionary 将序列和" +
                    "相关的键表达式直接计算为字典。")]
        public void Linq56() {
            var scoreRecords = new [] { new {Name = "Alice", Score = 50},
                                        new {Name = "Bob"  , Score = 40},
                                        new {Name = "Cathy", Score = 45}
                                    };
            
            var scoreRecordsDict = scoreRecords.ToDictionary(sr => sr.Name);
            
            Console.WriteLine("Bob's score: {0}", scoreRecordsDict["Bob"]);
        }

        [Category("转换运算符")]
        [Title("OfType")]
        [Description("此示例使用 OfType 仅返回数组中 double 类型的元素。")]
        public void Linq57() {
            object[] numbers = { null, 1.0, "two", 3, "four", 5, "six", 7.0 };

            var doubles = numbers.OfType<double>();
            
            Console.WriteLine("Numbers stored as doubles:");
            foreach (var d in doubles) {
                Console.WriteLine(d);
            }       
        }

        [Category("元素运算符")]
        [Title("First - 简单用法")]
        [Description("此示例使用 First 将第一个匹配元素" +
                     "作为产品返回，而非作为包含产品的序列返回。")]
        public void Linq58() {
            List<Product> products = GetProductList();

            Product product12 = (
                from prod in products
                where prod.ProductID == 12
                select prod)
                .First();
        
            ObjectDumper.Write(product12);
        }
        
        [Category("元素运算符")]
        [Title("First - 条件")]
        [Description("此示例使用 First 查找数组中第一个以“o”开头的元素。")]
        public void Linq59() {
            string[] strings = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };

            string startsWithO = strings.First(s => s[0] == 'o');
        
            Console.WriteLine("A string starting with 'o': {0}", startsWithO);
        }
        
        [Category("元素运算符")]
        [Title("FirstOrDefault - 简单用法")]
        [Description("此示例使用 FirstOrDefault 尝试返回序列的第一个元素，" +
                     "如果没有元素，则返回该类型的" +
                     "默认值。FirstOrDefault 可用于创建外部连接。")]
        public void Linq61() {
            int[] numbers = {};

            int firstNumOrDefault = numbers.FirstOrDefault();
        
            Console.WriteLine(firstNumOrDefault);
        }
        
        [Category("元素运算符")]
        [Title("FirstOrDefault - 条件")]
        [Description("此示例使用 FirstOrDefault 将 ProductID 为 789  的第一种产品作为" +
                     "单个 Product 对象返回，如果没有匹配项，则返回 null。")]
        public void Linq62() {
            List<Product> products = GetProductList();

            Product product789 = products.FirstOrDefault(p => p.ProductID == 789);
        
            Console.WriteLine("Product 789 exists: {0}", product789 != null);
        }
             
        [Category("元素运算符")]
        [Title("ElementAt")]
        [Description("此示例使用 ElementAt 从数据表检索第二个" +
                     "的数字。")]
        public void Linq64() {
            int[] numbers = { 5, 4, 1, 3, 9, 8, 6, 7, 2, 0 };

            int fourthLowNum = (
                from num in numbers
                where num > 5
                select num )
                .ElementAt(1);  // 第二个数字的索引是 1，因为序列的索引从 0 开始
        
            Console.WriteLine("Second number > 5: {0}", fourthLowNum);
        }
        
        [Category("生成运算符")]
        [Title("Range")]
        [Description("此示例使用 Range 生成一个从 100 到 149 的数字序列， " +
                     "用于查找该范围内的哪些数字是奇数和偶数。")]
        public void Linq65() {
            var numbers =
                from n in Enumerable.Range(100, 50)
                select new {Number = n, OddEven = n % 2 == 1 ? "odd" : "even"};
            
            foreach (var n in numbers) {
                Console.WriteLine("The number {0} is {1}.", n.Number, n.OddEven);
            }
        }
        
        [Category("生成运算符")]
        [Title("Repeat")]
        [Description("此示例使用 Repeat 生成包含数字 7 十次的序列。")]
        public void Linq66() {
            var numbers = Enumerable.Repeat(7, 10);
            
            foreach (var n in numbers) {
                Console.WriteLine(n);
            }
        }
        
        
        [Category("数量词")]
        [Title("Any - 简单用法")]
        [Description("此示例使用 Any 确定数组中是否有任何单词" +
                     "包含子字符串“ei”。")]
        public void Linq67() {
            string[] words = { "believe", "relief", "receipt", "field" };
            
            bool iAfterE = words.Any(w => w.Contains("ei"));

            //DONE fixed typo in writeline
            Console.WriteLine("There is a word in the list that contains 'ei': {0}", iAfterE);
        }
        
        [Category("数量词")]
        [Title("Any - 分组")]
        [Description("此示例使用 Any 仅对至少有一种产品缺货的类别" +
                     "返回经过分组的产品列表。")]
        public void Linq69() {
            List<Product> products = GetProductList();

            var productGroups =
                from prod in products
                group prod by prod.Category into prodGroup
                where prodGroup.Any(p => p.UnitsInStock == 0)
                select new { Category = prodGroup.Key, Products = prodGroup };

            ObjectDumper.Write(productGroups, 1);
        }
        
        [Category("数量词")]
        [Title("All - 简单用法")]
        [Description("此示例使用 All 确定数组是否仅包含" +
                     "奇数。")]
        public void Linq70() {
            int[] numbers = { 1, 11, 3, 19, 41, 65, 19 };
            
            bool onlyOdd = numbers.All(n => n % 2 == 1);

            Console.WriteLine("The list contains only odd numbers: {0}", onlyOdd);
        }
                
        [Category("数量词")]
        [Title("All - 分组")]
        [Description("此示例使用 All 仅对所有产品都有货的类别" +
                     "返回经过分组的产品列表。")]
        public void Linq72() {
            List<Product> products = GetProductList();

            var productGroups =
                from prod in products
                group prod by prod.Category into prodGroup
                where prodGroup.All(p => p.UnitsInStock > 0)
                select new { Category = prodGroup.Key, Products = prodGroup };

            ObjectDumper.Write(productGroups, 1);
        }

        [Category("聚合运算符")]
        [Title("Count - 简单用法")]
        [Description("此示例使用 Count 获取 300 的唯一素因子的数量。")]
        public void Linq73() {
            int[] primeFactorsOf300 = { 2, 2, 3, 5, 5 };
            
            int uniqueFactors = primeFactorsOf300.Distinct().Count();

            Console.WriteLine("300 有 {0} 个唯一素因子。", uniqueFactors);
        }

        [Category("聚合运算符")]
        [Title("Count - 条件")]
        [Description("此示例使用 Count 获取数组中奇数整数的数量。")]
        public void Linq74() {
            int[] numbers = { 5, 4, 1, 3, 9, 8, 6, 7, 2, 0 };
            
            int oddNumbers = numbers.Count(n => n % 2 == 1);
            
            Console.WriteLine("There are {0} odd numbers in the list.", oddNumbers);
        }

        [Category("聚合运算符")]
        [Title("Count - 嵌套")]
        [Description("此示例使用 Count 返回客户和每个客户所下订单数" +
                     "的列表。")]
        public void Linq76() {
            List<Customer> customers = GetCustomerList();
            
            var orderCounts =
                from cust in customers
                select new {cust.CustomerID, OrderCount = cust.Orders.Count()};
        
            ObjectDumper.Write(orderCounts);
        }
        
        [Category("聚合运算符")]
        [Title("Count - 分组")]
        [Description("此示例使用 Count 返回类别和每个类别所具有产品数" +
                     "的列表。")]
        public void Linq77() {
            List<Product> products = GetProductList();

            var categoryCounts =
                from prod in products
                group prod by prod.Category into prodGroup
                select new {Category = prodGroup.Key, ProductCount = prodGroup.Count()};
            
            ObjectDumper.Write(categoryCounts);
        }
        
        //DONE Changed "get the total of" to "add all"
        [Category("聚合运算符")]
        [Title("Sum - 简单用法")]
        [Description("此示例使用 Sum 将所有数字添加到一个数组中。")]
        public void Linq78() {
            int[] numbers = { 5, 4, 1, 3, 9, 8, 6, 7, 2, 0 };
            
            double numSum = numbers.Sum();
            
            Console.WriteLine("The sum of the numbers is {0}.", numSum);
        }

        [Category("聚合运算符")]
        [Title("Sum - 投影")]
        [Description("此示例使用 Sum 获取数组中所有单词的" +
                     "总字符数。")]
        public void Linq79() {
            string[] words = { "cherry", "apple", "blueberry" };
            
            double totalChars = words.Sum(w => w.Length);
            
            Console.WriteLine("There are a total of {0} characters in these words.", totalChars);
        }

        
        
        [Category("聚合运算符")]
        [Title("Sum - 分组")]
        [Description("此示例使用 Sum 获取每个产品类别的总库存量。")]
        public void Linq80() {
            List<Product> products = GetProductList();

            var categories =
                from prod in products
                group prod by prod.Category into prodGroup
                select new {Category = prodGroup.Key, TotalUnitsInStock = prodGroup.Sum(p => p.UnitsInStock)};
        
            ObjectDumper.Write(categories);
        }
        
        [Category("聚合运算符")]
        [Title("Min - 简单用法")]
        [Description("此示例使用 Min 获取数组中最小的数字。")]
        public void Linq81() {
            int[] numbers = { 5, 4, 1, 3, 9, 8, 6, 7, 2, 0 };
            
            int minNum = numbers.Min();
            
            Console.WriteLine("The minimum number is {0}.", minNum);
        }

        [Category("聚合运算符")]
        [Title("Min - 投影")]
        [Description("此示例使用 Min 获取数组中最短单词的长度。")]
        public void Linq82() {
            string[] words = { "cherry", "apple", "blueberry" };
            
            int shortestWord = words.Min(w => w.Length);
            
            Console.WriteLine("The shortest word is {0} characters long.", shortestWord);
        }
        
        [Category("聚合运算符")]
        [Title("Min - 分组")]
        [Description("此示例使用 Min 获取每个类别中产品的最低价。")]
        public void Linq83() {
            List<Product> products = GetProductList();

            var categories =
                from prod in products
                group prod by prod.Category into prodGroup
                select new {Category = prodGroup.Key, CheapestPrice = prodGroup.Min(p => p.UnitPrice)};
        
            ObjectDumper.Write(categories);
        }
        
        [Category("聚合运算符")]
        [Title("Min - 元素")]
        [Description("此示例使用 Min 获取每个类别中最低价的产品。")]
        public void Linq84() {
            List<Product> products = GetProductList();

            var categories =
                from prod in products
                group prod by prod.Category into prodGroup
                let minPrice = prodGroup.Min(p => p.UnitPrice)
                select new {Category = prodGroup.Key, CheapestProducts = prodGroup.Where(p => p.UnitPrice == minPrice)};
        
            ObjectDumper.Write(categories, 1);
        }
        
        [Category("聚合运算符")]
        [Title("Max - 简单用法")]
        [Description("此示例使用 Max 获取数组中的最高值。注意，该方法返回单个值。")]
        public void Linq85() {
            int[] numbers = { 5, 4, 1, 3, 9, 8, 6, 7, 2, 0 };
            
            int maxNum = numbers.Max();
            
            Console.WriteLine("The maximum number is {0}.", maxNum);
        }

        [Category("聚合运算符")]
        [Title("Max - 投影")]
        [Description("此示例使用 Max 获取数组中最长单词的长度。")]
        public void Linq86() {
            string[] words = { "cherry", "apple", "blueberry" };
            
            int longestLength = words.Max(w => w.Length);
            
            Console.WriteLine("The longest word is {0} characters long.", longestLength);
        }
        
        [Category("聚合运算符")]
        [Title("Max - 分组")]
        [Description("此示例使用 Max 获取每个类别中产品的最高价。")]
        public void Linq87() {
            List<Product> products = GetProductList();

            var categories =
                from prod in products
                group prod by prod.Category into prodGroup
                select new {Category = prodGroup.Key, MostExpensivePrice = prodGroup.Max(p => p.UnitPrice)};
        
            ObjectDumper.Write(categories);
        }
        
        [Category("聚合运算符")]
        [Title("Max - 元素")]
        [Description("此示例使用 Max 获取每个类别中最高价的产品。")]
        public void Linq88() {
            List<Product> products = GetProductList();

            var categories =
                from prod in products
                group prod by prod.Category into prodGroup
                let maxPrice = prodGroup.Max(p => p.UnitPrice)
                select new {Category = prodGroup.Key, MostExpensiveProducts = prodGroup.Where(p => p.UnitPrice == maxPrice)};
        
            ObjectDumper.Write(categories, 1);
        }
        
        [Category("聚合运算符")]
        [Title("Average - 简单用法")]
        [Description("此示例使用 Average 获取数组中所有数字的平均值。")]
        public void Linq89() {
            int[] numbers = { 5, 4, 1, 3, 9, 8, 6, 7, 2, 0 };
            
            double averageNum = numbers.Average();
            
            Console.WriteLine("The average number is {0}.", averageNum);
        }

        [Category("聚合运算符")]
        [Title("Average - 投影")]
        [Description("此示例使用 Average 获取数组中单词的平均长度。")]
        public void Linq90() {
            string[] words = { "cherry", "apple", "blueberry" };
            
            double averageLength = words.Average(w => w.Length);
            
            Console.WriteLine("The average word length is {0} characters.", averageLength);
        }
        
        [Category("聚合运算符")]
        [Title("Average - 分组")]
        [Description("此示例使用 Average 获取每个类别中产品的平均价格。")]
        public void Linq91() {
            List<Product> products = GetProductList();

            var categories =
                from prod in products
                group prod by prod.Category into prodGroup
                select new {Category = prodGroup.Key, AveragePrice = prodGroup.Average(p => p.UnitPrice)};
        
            ObjectDumper.Write(categories);
        }

        [Category("聚合运算符")]
        [Title("Aggregate - 简单用法")]
        [Description("此示例使用 Aggregate 创建数组的连乘，" +
                     "计算所有元素的总乘积。")]
        public void Linq92() {
            double[] doubles = { 1.7, 2.3, 1.9, 4.1, 2.9 };
            
            double product = doubles.Aggregate((runningProduct, nextFactor) => runningProduct * nextFactor);
            
            Console.WriteLine("Total product of all numbers: {0}", product);
        }
        
        [Category("聚合运算符")]
        [Title("Aggregate - 种子")]
        [Description("此示例使用 Aggregate 创建一个流水账余额， " +
                     "从最初余额 100 减去每次取出的金额，直到" +
                     "余额减少到 0 以下为止。")]
        public void Linq93() {
            double startBalance = 100.0;
            
            int[] attemptedWithdrawals = { 20, 10, 40, 50, 10, 70, 30 };
            
            double endBalance = 
                attemptedWithdrawals.Aggregate(startBalance,
                    (balance, nextWithdrawal) =>
                        ( (nextWithdrawal <= balance) ? (balance - nextWithdrawal) : balance ) );
            
            Console.WriteLine("Ending balance: {0}", endBalance);
        }
        
        [Category("杂项运算符")]
        [Title("Concat - 1")]
        [Description("此示例使用 Concat 创建一个序列，其中依次包含" +
                     "每个数组的值。")]
        public void Linq94() {
            int[] numbersA = { 0, 2, 4, 5, 6, 8, 9 };
            int[] numbersB = { 1, 3, 5, 7, 8 };
            
            var allNumbers = numbersA.Concat(numbersB);
            
            Console.WriteLine("All numbers from both arrays:");
            foreach (var n in allNumbers) {
                Console.WriteLine(n);
            }
        }
        
        [Category("杂项运算符")]
        [Title("Concat - 2")]
        [Description("此示例使用 Concat 创建一个含有" +
                     "所有客户名和产品名的序列，包括任何重复项。")]
        public void Linq95() {
            List<Customer> customers = GetCustomerList();
            List<Product> products = GetProductList();
            
            var customerNames =
                from cust in customers
                select cust.CompanyName;
            var productNames =
                from prod in products
                select prod.ProductName;
            
            var allNames = customerNames.Concat(productNames);
            
            Console.WriteLine("Customer and product names:");
            foreach (var n in allNames) {
                Console.WriteLine(n);
            }
        }
        
        [Category("杂项运算符")]
        [Title("EqualAll - 1")]
        [Description("此示例使用 SequenceEquals 查看两个序列中所有元素是否" +
                     "以相同顺序匹配。")]
        public void Linq96() {
            var wordsA = new string[] { "cherry", "apple", "blueberry" };
            var wordsB = new string[] { "cherry", "apple", "blueberry" };
            
            bool match = wordsA.SequenceEqual(wordsB);
            
            Console.WriteLine("The sequences match: {0}", match);
        }
        
        [Category("杂项运算符")]
        [Title("EqualAll - 2")]
        [Description("此示例使用 SequenceEqual 查看两个序列中所有元素是否" +
                     "以相同顺序匹配。")]
        public void Linq97() {
            var wordsA = new string[] { "cherry", "apple", "blueberry" };
            var wordsB = new string[] { "apple", "blueberry", "cherry" };

            bool match = wordsA.SequenceEqual(wordsB);
            
            Console.WriteLine("The sequences match: {0}", match);
        }

        [Category("查询执行")]
        [Title("延迟执行")]
        [Description("以下示例显示如何将查询延迟到" +
                     "在 foreach 语句中枚举该查询后。")]
        public void Linq99() {
            
            // 查询不会执行，直到您枚举完它们。
            int[] numbers = new int[] { 5, 4, 1, 3, 9, 8, 6, 7, 2, 0 };
            
            int i = 0;
            var simpleQuery =
                from num in numbers
                select ++i;

            // 局部变量“i”不会递增，
            // 直到在 foreach 循环中执行了查询。
            Console.WriteLine("The current value of i is {0}", i); //i is still zero

            foreach (var item in simpleQuery) {
                Console.WriteLine("v = {0}, i = {1}", item, i); // 现在 i 将会递增         
            }  
        }
        
        [Category("查询执行")]
        [Title("立即执行")]
        [Description("以下示例显示如何才能用 ToList() 这样的方法立即执行" +
                    " 查询，并将结果存储在内存中。")]
        public void Linq100() {

            // ToList()、Max() 和 Count() 这样的方法会导致查询
            // 立即执行。          
            int[] numbers = new int[] { 5, 4, 1, 3, 9, 8, 6, 7, 2, 0 };        
            
            int i = 0;
            var immediateQuery = (
                from num in numbers
                select ++i )
                .ToList();

            Console.WriteLine("The current value of i is {0}", i); //i has been incremented
            
            foreach (var item in immediateQuery) {
                Console.WriteLine("v = {0}, i = {1}", item, i);
            }  
        }

        [Category("查询执行")]
        [Title("查询重用")]
        [Description("以下示例显示由于延迟执行，如何才能在" +
                     "数据更改后再次使用查询以及随后查询将如何对新数据产生作用。")]
        public void Linq101() {

            // 使用延迟执行可以只定义查询一次，
            // 以后可以以多种方式重新使用它。
            int[] numbers = new int[] { 5, 4, 1, 3, 9, 8, 6, 7, 2, 0 };
            var lowNumbers =
                from num in numbers
                where num <= 3
                select num;

            Console.WriteLine("First run numbers <= 3:");
            foreach (int n in lowNumbers) {
                Console.WriteLine(n);
            }

            // 查询原始查询。
            var lowEvenNumbers =
                from num in lowNumbers
                where num % 2 == 0
                select num;

            Console.WriteLine("Run lowEvenNumbers query:");
            foreach (int n in lowEvenNumbers)
            {
                Console.WriteLine(n);
            }

            // 修改源数据。
            for (int i = 0; i < 10; i++) {
                numbers[i] = -numbers[i];
            }

            // 第二次运行过程中，相同的查询对象
            // lowNumbers 将循环访问
            // numbers[] 的新状态，从而产生不同的结果:
            Console.WriteLine("Second run numbers <= 3:");
            foreach (int n in lowNumbers) {
                Console.WriteLine(n);
            }
        }

        [Category("联接运算符")]
        [Title("内部联接")]
        [Description("此示例显示如何对两个序列执行简单的内部联接，" +
            "以生成一个平面结果集，其中包含每个在客户中有匹配元素的供应商" +
            "元素。")]
        public void Linq102() {

            List<Customer> customers = GetCustomerList();
            List<Supplier> suppliers = GetSupplierList();

            var custSupJoin = 
                from sup in suppliers
                join cust in customers on sup.Country equals cust.Country
                select new { Country = sup.Country, SupplierName = sup.SupplierName, CustomerName = cust.CompanyName };

            foreach (var item in custSupJoin) {
                Console.WriteLine("Country = {0}, Supplier = {1}, Customer = {2}", item.Country, item.SupplierName, item.CustomerName);
            }
        }      

        [Category("联接运算符")]
        [Title("分组联接")]
        [Description("分组联接生成一个分层序列。以下查询是" +
                    " 生成对象序列的内部联接，其中的每个对象都有一个键和一个包含所有匹配元素的内部序列。")]
        public void Linq103() {
            
               
            List<Customer> customers = GetCustomerList();
            List<Supplier> suppliers = GetSupplierList();

            var custSupQuery =
                from sup in suppliers
                join cust in customers on sup.Country equals cust.Country into cs
                select new { Key = sup.Country, Items = cs };

           
            foreach (var item in custSupQuery) {
                Console.WriteLine(item.Key + ":");
                foreach (var element in item.Items) 
                {
                    Console.WriteLine("   " + element.CompanyName); 
                }
            }
        }

        [Category("联接运算符")]
        [Title("交叉联接与分组联接")]
        [Description("Group Join 运算符比 Join 应用更广泛，正如交叉联接示例的" +
            "这个略显冗长的版本所示。")]
        public void Linq104() {
            string[] categories = new string[]{ 
                "Beverages", 
                "Condiments", 
                "Vegetables", 
                "Dairy Products", 
                "Seafood" };
               
            List<Product> products = GetProductList();

            var prodByCategory = 
                from cat in categories
                join prod in products on cat equals prod.Category into ps
                from p in ps   
                select new { Category = cat, p.ProductName };

            foreach (var item in prodByCategory) {
                Console.WriteLine(item.ProductName + ": " + item.Category);
            }
        }
        [Category("联接运算符")]
        [Title("左外部联接")]
        [Description("左外部联接会生成一个结果集，其中至少包括一次所有左侧的元素，" + 
            "即使它们不匹配任何右侧的元素。")]
        public void Linq105() {
            List<Customer> customers = GetCustomerList();
            List<Supplier> suppliers = GetSupplierList();

            var supplierCusts = 
                from sup in suppliers
                join cust in customers on sup.Country equals cust.Country into cs
                from c in cs.DefaultIfEmpty()  // DefaultIfEmpty 会保留在右侧没有匹配项的左侧元素
                orderby sup.SupplierName
                select new { Country = sup.Country, CompanyName = c == null ? "(No customers)" : c.CompanyName,
                             SupplierName = sup.SupplierName};

            foreach (var item in supplierCusts) {
                Console.WriteLine("{0} ({1}): {2}", item.SupplierName, item.Country, item.CompanyName);
            }
        }

        [Category("联接运算符")]
        [Title("左外部连接 2")]
        [Description("对于客户表中的每个客户，此查询会返回" +
                     "来自同一国家的所有供应商，或返回一个字符串，指示未找到来自该国的供应商。")]
        public void Linq106()
        {

            List<Customer> customers = GetCustomerList();
            List<Supplier> suppliers = GetSupplierList();

            var custSuppliers =
                from cust in customers
                join sup in suppliers on cust.Country equals sup.Country into ss
                from s in ss.DefaultIfEmpty()
                orderby cust.CompanyName
                select new { Country = cust.Country, CompanyName = cust.CompanyName,
                             SupplierName = s == null ? "(No suppliers)" : s.SupplierName };

            foreach (var item in custSuppliers) {
                Console.WriteLine("{0} ({1}): {2}", item.CompanyName, item.Country, item.SupplierName);
            }
        }

        [Category("联接运算符")]
        [Title("左外部联接和复合键")]
        [Description("对于供应商表中的每个供应商，此查询会返回" +
                     "来自同一城市和国家的所有供应商，或返回一个字符串指示未找到来自该城市/国家的客户。" +
                     "注意，使用匿名类型封装了多个键值。")]
        public void Linq107()
        {
            List<Customer> customers = GetCustomerList();
            List<Supplier> suppliers = GetSupplierList();

            var supplierCusts =
                from sup in suppliers
                join cust in customers on new { sup.City, sup.Country } equals new { cust.City, cust.Country } into cs
                from c in cs.DefaultIfEmpty() //移除 DefaultIfEmpty 方法调用可以使之成为内部联接
                orderby sup.SupplierName
                select new { Country = sup.Country, 
                             City = sup.City,
                             SupplierName = sup.SupplierName,
                             CompanyName = c == null ? "(No customers)" : c.CompanyName
                           };

            foreach (var item in supplierCusts)
            {
                Console.WriteLine("{0} ({1}, {2}): {3}", item.SupplierName, item.City, item.Country, item.CompanyName);
            }
        }

        [Category("* Sample Data *")]
        [Title("CustomerList / ProductList / Supplier List")]
        [Description("此方法显示上面的查询所使用的示例数据。还可以看到" +
                     "构造列表的以下方法。ProductList 和 SupplierList 是使用" +
                     "集合初始值设定项生成的，CustomerList 使用 XLinq 将它的值" +
                     "从 XML 文档读入内存中。")]
        [LinkedMethod("GetProductList")]
        [LinkedMethod("GetSupplierList")]
        [LinkedMethod("GetCustomerList")]
        [LinkedMethod("createLists")]
        public void Linq115() {
            ObjectDumper.Write(GetCustomerList(), 1);

            Console.WriteLine();

            ObjectDumper.Write(GetProductList());
        }



        public List<Product> GetProductList() {
            if (productList == null)
                createLists();
            
            return productList;
        }

        public List<Supplier> GetSupplierList()
        {
            if (supplierList == null)
                createLists();

            return supplierList;
        }

        public List<Customer> GetCustomerList() {
            if (customerList == null)
                createLists();
            
            return customerList;
        }

        private void createLists() {
            // 使用集合初始值设定项在内存中创建的产品数据:
            productList =
                new List<Product> {
                    new Product { ProductID = 1, ProductName = "Chai", Category = "Beverages", UnitPrice = 18.0000M, UnitsInStock = 39 },
                    new Product { ProductID = 2, ProductName = "Chang", Category = "Beverages", UnitPrice = 19.0000M, UnitsInStock = 17 },
                    new Product { ProductID = 3, ProductName = "Aniseed Syrup", Category = "Condiments", UnitPrice = 10.0000M, UnitsInStock = 13 },
                    new Product { ProductID = 4, ProductName = "Chef Anton's Cajun Seasoning", Category = "Condiments", UnitPrice = 22.0000M, UnitsInStock = 53 },
                    new Product { ProductID = 5, ProductName = "Chef Anton's Gumbo Mix", Category = "Condiments", UnitPrice = 21.3500M, UnitsInStock = 0 },
                    new Product { ProductID = 6, ProductName = "Grandma's Boysenberry Spread", Category = "Condiments", UnitPrice = 25.0000M, UnitsInStock = 120 },
                    new Product { ProductID = 7, ProductName = "Uncle Bob's Organic Dried Pears", Category = "Produce", UnitPrice = 30.0000M, UnitsInStock = 15 },
                    new Product { ProductID = 8, ProductName = "Northwoods Cranberry Sauce", Category = "Condiments", UnitPrice = 40.0000M, UnitsInStock = 6 },
                    new Product { ProductID = 9, ProductName = "Mishi Kobe Niku", Category = "Meat/Poultry", UnitPrice = 97.0000M, UnitsInStock = 29 },
                    new Product { ProductID = 10, ProductName = "Ikura", Category = "Seafood", UnitPrice = 31.0000M, UnitsInStock = 31 },
                    new Product { ProductID = 11, ProductName = "Queso Cabrales", Category = "Dairy Products", UnitPrice = 21.0000M, UnitsInStock = 22 },
                    new Product { ProductID = 12, ProductName = "Queso Manchego La Pastora", Category = "Dairy Products", UnitPrice = 38.0000M, UnitsInStock = 86 },
                    new Product { ProductID = 13, ProductName = "Konbu", Category = "Seafood", UnitPrice = 6.0000M, UnitsInStock = 24 },
                    new Product { ProductID = 14, ProductName = "Tofu", Category = "Produce", UnitPrice = 23.2500M, UnitsInStock = 35 },
                    new Product { ProductID = 15, ProductName = "Genen Shouyu", Category = "Condiments", UnitPrice = 15.5000M, UnitsInStock = 39 },
                    new Product { ProductID = 16, ProductName = "Pavlova", Category = "Confections", UnitPrice = 17.4500M, UnitsInStock = 29 },
                    new Product { ProductID = 17, ProductName = "Alice Mutton", Category = "Meat/Poultry", UnitPrice = 39.0000M, UnitsInStock = 0 },
                    new Product { ProductID = 18, ProductName = "Carnarvon Tigers", Category = "Seafood", UnitPrice = 62.5000M, UnitsInStock = 42 },
                    new Product { ProductID = 19, ProductName = "Teatime Chocolate Biscuits", Category = "Confections", UnitPrice = 9.2000M, UnitsInStock = 25 },
                    new Product { ProductID = 20, ProductName = "Sir Rodney's Marmalade", Category = "Confections", UnitPrice = 81.0000M, UnitsInStock = 40 },
                    new Product { ProductID = 21, ProductName = "Sir Rodney's Scones", Category = "Confections", UnitPrice = 10.0000M, UnitsInStock = 3 },
                    new Product { ProductID = 22, ProductName = "Gustaf's Knäckebröd", Category = "Grains/Cereals", UnitPrice = 21.0000M, UnitsInStock = 104 },
                    new Product { ProductID = 23, ProductName = "Tunnbröd", Category = "Grains/Cereals", UnitPrice = 9.0000M, UnitsInStock = 61 },
                    new Product { ProductID = 24, ProductName = "Guaraná Fantástica", Category = "Beverages", UnitPrice = 4.5000M, UnitsInStock = 20 },
                    new Product { ProductID = 25, ProductName = "NuNuCa Nuß-Nougat-Creme", Category = "Confections", UnitPrice = 14.0000M, UnitsInStock = 76 },
                    new Product { ProductID = 26, ProductName = "Gumbär Gummibärchen", Category = "Confections", UnitPrice = 31.2300M, UnitsInStock = 15 },
                    new Product { ProductID = 27, ProductName = "Schoggi Schokolade", Category = "Confections", UnitPrice = 43.9000M, UnitsInStock = 49 },
                    new Product { ProductID = 28, ProductName = "Rössle Sauerkraut", Category = "Produce", UnitPrice = 45.6000M, UnitsInStock = 26 },
                    new Product { ProductID = 29, ProductName = "Thüringer Rostbratwurst", Category = "Meat/Poultry", UnitPrice = 123.7900M, UnitsInStock = 0 },
                    new Product { ProductID = 30, ProductName = "Nord-Ost Matjeshering", Category = "Seafood", UnitPrice = 25.8900M, UnitsInStock = 10 },
                    new Product { ProductID = 31, ProductName = "Gorgonzola Telino", Category = "Dairy Products", UnitPrice = 12.5000M, UnitsInStock = 0 },
                    new Product { ProductID = 32, ProductName = "Mascarpone Fabioli", Category = "Dairy Products", UnitPrice = 32.0000M, UnitsInStock = 9 },
                    new Product { ProductID = 33, ProductName = "Geitost", Category = "Dairy Products", UnitPrice = 2.5000M, UnitsInStock = 112 },
                    new Product { ProductID = 34, ProductName = "Sasquatch Ale", Category = "Beverages", UnitPrice = 14.0000M, UnitsInStock = 111 },
                    new Product { ProductID = 35, ProductName = "Steeleye Stout", Category = "Beverages", UnitPrice = 18.0000M, UnitsInStock = 20 },
                    new Product { ProductID = 36, ProductName = "Inlagd Sill", Category = "Seafood", UnitPrice = 19.0000M, UnitsInStock = 112 },
                    new Product { ProductID = 37, ProductName = "Gravad lax", Category = "Seafood", UnitPrice = 26.0000M, UnitsInStock = 11 },
                    new Product { ProductID = 38, ProductName = "Côte de Blaye", Category = "Beverages", UnitPrice = 263.5000M, UnitsInStock = 17 },
                    new Product { ProductID = 39, ProductName = "Chartreuse verte", Category = "Beverages", UnitPrice = 18.0000M, UnitsInStock = 69 },
                    new Product { ProductID = 40, ProductName = "Boston Crab Meat", Category = "Seafood", UnitPrice = 18.4000M, UnitsInStock = 123 },
                    new Product { ProductID = 41, ProductName = "Jack's New England Clam Chowder", Category = "Seafood", UnitPrice = 9.6500M, UnitsInStock = 85 },
                    new Product { ProductID = 42, ProductName = "Singaporean Hokkien Fried Mee", Category = "Grains/Cereals", UnitPrice = 14.0000M, UnitsInStock = 26 },
                    new Product { ProductID = 43, ProductName = "Ipoh Coffee", Category = "Beverages", UnitPrice = 46.0000M, UnitsInStock = 17 },
                    new Product { ProductID = 44, ProductName = "Gula Malacca", Category = "Condiments", UnitPrice = 19.4500M, UnitsInStock = 27 },
                    new Product { ProductID = 45, ProductName = "Rogede sild", Category = "Seafood", UnitPrice = 9.5000M, UnitsInStock = 5 },
                    new Product { ProductID = 46, ProductName = "Spegesild", Category = "Seafood", UnitPrice = 12.0000M, UnitsInStock = 95 },
                    new Product { ProductID = 47, ProductName = "Zaanse koeken", Category = "Confections", UnitPrice = 9.5000M, UnitsInStock = 36 },
                    new Product { ProductID = 48, ProductName = "Chocolade", Category = "Confections", UnitPrice = 12.7500M, UnitsInStock = 15 },
                    new Product { ProductID = 49, ProductName = "Maxilaku", Category = "Confections", UnitPrice = 20.0000M, UnitsInStock = 10 },
                    new Product { ProductID = 50, ProductName = "Valkoinen suklaa", Category = "Confections", UnitPrice = 16.2500M, UnitsInStock = 65 },
                    new Product { ProductID = 51, ProductName = "Manjimup Dried Apples", Category = "Produce", UnitPrice = 53.0000M, UnitsInStock = 20 },
                    new Product { ProductID = 52, ProductName = "Filo Mix", Category = "Grains/Cereals", UnitPrice = 7.0000M, UnitsInStock = 38 },
                    new Product { ProductID = 53, ProductName = "Perth Pasties", Category = "Meat/Poultry", UnitPrice = 32.8000M, UnitsInStock = 0 },
                    new Product { ProductID = 54, ProductName = "Tourtière", Category = "Meat/Poultry", UnitPrice = 7.4500M, UnitsInStock = 21 },
                    new Product { ProductID = 55, ProductName = "Pâté chinois", Category = "Meat/Poultry", UnitPrice = 24.0000M, UnitsInStock = 115 },
                    new Product { ProductID = 56, ProductName = "Gnocchi di nonna Alice", Category = "Grains/Cereals", UnitPrice = 38.0000M, UnitsInStock = 21 },
                    new Product { ProductID = 57, ProductName = "Ravioli Angelo", Category = "Grains/Cereals", UnitPrice = 19.5000M, UnitsInStock = 36 },
                    new Product { ProductID = 58, ProductName = "Escargots de Bourgogne", Category = "Seafood", UnitPrice = 13.2500M, UnitsInStock = 62 },
                    new Product { ProductID = 59, ProductName = "Raclette Courdavault", Category = "Dairy Products", UnitPrice = 55.0000M, UnitsInStock = 79 },
                    new Product { ProductID = 60, ProductName = "Camembert Pierrot", Category = "Dairy Products", UnitPrice = 34.0000M, UnitsInStock = 19 },
                    new Product { ProductID = 61, ProductName = "Sirop d'érable", Category = "Condiments", UnitPrice = 28.5000M, UnitsInStock = 113 },
                    new Product { ProductID = 62, ProductName = "Tarte au sucre", Category = "Confections", UnitPrice = 49.3000M, UnitsInStock = 17 },
                    new Product { ProductID = 63, ProductName = "Vegie-spread", Category = "Condiments", UnitPrice = 43.9000M, UnitsInStock = 24 },
                    new Product { ProductID = 64, ProductName = "Wimmers gute Semmelknödel", Category = "Grains/Cereals", UnitPrice = 33.2500M, UnitsInStock = 22 },
                    new Product { ProductID = 65, ProductName = "Louisiana Fiery Hot Pepper Sauce", Category = "Condiments", UnitPrice = 21.0500M, UnitsInStock = 76 },
                    new Product { ProductID = 66, ProductName = "Louisiana Hot Spiced Okra", Category = "Condiments", UnitPrice = 17.0000M, UnitsInStock = 4 },
                    new Product { ProductID = 67, ProductName = "Laughing Lumberjack Lager", Category = "Beverages", UnitPrice = 14.0000M, UnitsInStock = 52 },
                    new Product { ProductID = 68, ProductName = "Scottish Longbreads", Category = "Confections", UnitPrice = 12.5000M, UnitsInStock = 6 },
                    new Product { ProductID = 69, ProductName = "Gudbrandsdalsost", Category = "Dairy Products", UnitPrice = 36.0000M, UnitsInStock = 26 },
                    new Product { ProductID = 70, ProductName = "Outback Lager", Category = "Beverages", UnitPrice = 15.0000M, UnitsInStock = 15 },
                    new Product { ProductID = 71, ProductName = "Flotemysost", Category = "Dairy Products", UnitPrice = 21.5000M, UnitsInStock = 26 },
                    new Product { ProductID = 72, ProductName = "Mozzarella di Giovanni", Category = "Dairy Products", UnitPrice = 34.8000M, UnitsInStock = 14 },
                    new Product { ProductID = 73, ProductName = "Röd Kaviar", Category = "Seafood", UnitPrice = 15.0000M, UnitsInStock = 101 },
                    new Product { ProductID = 74, ProductName = "Longlife Tofu", Category = "Produce", UnitPrice = 10.0000M, UnitsInStock = 4 },
                    new Product { ProductID = 75, ProductName = "Rhönbräu Klosterbier", Category = "Beverages", UnitPrice = 7.7500M, UnitsInStock = 125 },
                    new Product { ProductID = 76, ProductName = "Lakkalikööri", Category = "Beverages", UnitPrice = 18.0000M, UnitsInStock = 57 },
                    new Product { ProductID = 77, ProductName = "Original Frankfurter grüne Soße", Category = "Condiments", UnitPrice = 13.0000M, UnitsInStock = 32 }
                };

            supplierList = new List<Supplier>(){
                    new Supplier {SupplierName = "Exotic Liquids", Address = "49 Gilbert St.", City = "London", Country = "UK"},
                    new Supplier {SupplierName = "New Orleans Cajun Delights", Address = "P.O. Box 78934", City = "New Orleans", Country = "USA"},
                    new Supplier {SupplierName = "Grandma Kelly's Homestead", Address = "707 Oxford Rd.", City = "Ann Arbor", Country = "USA"},
                    new Supplier {SupplierName = "Tokyo Traders", Address = "9-8 Sekimai Musashino-shi", City = "Tokyo", Country = "Japan"},
                    new Supplier {SupplierName = "Cooperativa de Quesos 'Las Cabras'", Address = "Calle del Rosal 4", City = "Oviedo", Country = "Spain"},
                    new Supplier {SupplierName = "Mayumi's", Address = "92 Setsuko Chuo-ku", City = "Osaka", Country = "Japan"},
                    new Supplier {SupplierName = "Pavlova, Ltd.", Address = "74 Rose St. Moonie Ponds", City = "Melbourne", Country = "Australia"},
                    new Supplier {SupplierName = "Specialty Biscuits, Ltd.", Address = "29 King's Way", City = "Manchester", Country = "UK"},
                    new Supplier {SupplierName = "PB Knäckebröd AB", Address = "Kaloadagatan 13", City = "Göteborg", Country = "Sweden"},
                    new Supplier {SupplierName = "Refrescos Americanas LTDA", Address = "Av. das Americanas 12.890", City = "Sao Paulo", Country = "Brazil"},
                    new Supplier {SupplierName = "Heli Süßwaren GmbH & Co. KG", Address = "Tiergartenstraße 5", City = "Berlin", Country = "Germany"},
                    new Supplier {SupplierName = "Plutzer Lebensmittelgroßmärkte AG", Address = "Bogenallee 51", City = "Frankfurt", Country = "Germany"},
                    new Supplier {SupplierName = "Nord-Ost-Fisch Handelsgesellschaft mbH", Address = "Frahmredder 112a", City = "Cuxhaven", Country = "Germany"},
                    new Supplier {SupplierName = "Formaggi Fortini s.r.l.", Address = "Viale Dante, 75", City = "Ravenna", Country = "Italy"},
                    new Supplier {SupplierName = "Norske Meierier", Address = "Hatlevegen 5", City = "Sandvika", Country = "Norway"},
                    new Supplier {SupplierName = "Bigfoot Breweries", Address = "3400 - 8th Avenue Suite 210", City = "Bend", Country = "USA"},
                    new Supplier {SupplierName = "Svensk Sjöföda AB", Address = "Brovallavägen 231", City = "Stockholm", Country = "Sweden"},
                    new Supplier {SupplierName = "Aux joyeux ecclésiastiques", Address = "203, Rue des Francs-Bourgeois", City = "Paris", Country = "France"},
                    new Supplier {SupplierName = "New England Seafood Cannery", Address = "Order Processing Dept. 2100 Paul Revere Blvd.", City = "Boston", Country = "USA"},
                    new Supplier {SupplierName = "Leka Trading", Address = "471 Serangoon Loop, Suite #402", City = "Singapore", Country = "Singapore"},
                    new Supplier {SupplierName = "Lyngbysild", Address = "Lyngbysild Fiskebakken 10", City = "Lyngby", Country = "Denmark"},
                    new Supplier {SupplierName = "Zaanse Snoepfabriek", Address = "Verkoop Rijnweg 22", City = "Zaandam", Country = "Netherlands"},
                    new Supplier {SupplierName = "Karkki Oy", Address = "Valtakatu 12", City = "Lappeenranta", Country = "Finland"},
                    new Supplier {SupplierName = "G'day, Mate", Address = "170 Prince Edward Parade Hunter's Hill", City = "Sydney", Country = "Australia"},
                    new Supplier {SupplierName = "Ma Maison", Address = "2960 Rue St. Laurent", City = "Montréal", Country = "Canada"},
                    new Supplier {SupplierName = "Pasta Buttini s.r.l.", Address = "Via dei Gelsomini, 153", City = "Salerno", Country = "Italy"},
                    new Supplier {SupplierName = "Escargots Nouveaux", Address = "22, rue H. Voiron", City = "Montceau", Country = "France"},
                    new Supplier {SupplierName = "Gai pâturage", Address = "Bat. B 3, rue des Alpes", City = "Annecy", Country = "France"},
                    new Supplier {SupplierName = "Forêts d'érables", Address = "148 rue Chasseur", City = "Ste-Hyacinthe", Country = "Canada"},
                };           
        
        
            // 使用 XLinq 将客户/订单数据从 XML 文件中读入内存:
            string customerListPath = Path.GetFullPath(Path.Combine(dataPath, "customers.xml"));

            customerList = (
                from e in XDocument.Load(customerListPath).
                          Root.Elements("customer")
                select new Customer {
                    CustomerID = (string)e.Element("id"),
                    CompanyName = (string)e.Element("name"),
                    Address = (string)e.Element("address"),
                    City = (string)e.Element("city"),
                    Region = (string)e.Element("region"),
                    PostalCode = (string)e.Element("postalcode"),
                    Country = (string)e.Element("country"),
                    Phone = (string)e.Element("phone"),
                    Fax = (string)e.Element("fax"),
                    Orders = (
                        from o in e.Elements("orders").Elements("order")
                        select new Order {
                            OrderID = (int)o.Element("id"),
                            OrderDate = (DateTime)o.Element("orderdate"),
                            Total = (decimal)o.Element("total") } )
                        .ToArray() } )
                .ToList();
        }
    }
}
