// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
//版权所有(C) Microsoft Corporation。保留所有权利。

using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;

static class Samples {
    static int[] numbers = new [] { 5, 4, 1, 3, 9, 8, 6, 7, 2, 0 };
    static string[] strings = new [] { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
    
    class Person {
      public string Name {get; set;}
      public int Level {get; set;}
    }
    
    static Person[] persons = new Person[] {
        new Person {Name="Jesper", Level=3},
        new Person {Name="Lene", Level=3},
        new Person {Name="Jonathan", Level=5},
        new Person {Name="Sagiv", Level=3},
        new Person {Name="Jacqueline", Level=3},
        new Person {Name="Ellen", Level=3},
        new Person {Name="Gustavo", Level=9}
        };
    
    public static void Sample1() {
        // 使用 Where() 筛选出符合特定条件的元素
        var fnums = numbers.Where(n => n < 5);
    
        Console.WriteLine("Numbers < 5");
        foreach(int x in fnums) {
            Console.WriteLine(x);
        }
    }    

    public static void Sample2() {
        // 使用 First() 查找一个符合特定条件的元素
        string v = strings.First(s => s[0] == 'o');
    
        Console.WriteLine("string starting with 'o': {0}", v);
    }        
    
    public static void Sample3() {
        // 使用 Select() 将每个元素都转换为新值
        var snums = numbers.Select(n => strings[n]);
        
        Console.WriteLine("Numbers");
        foreach(string s in snums) {
            Console.WriteLine(s);
        }           
    }
    
    public static void Sample4()
    {
        // 使用匿名类型构造函数即时构造多值结果
        var q = strings.Select(s => new {Head = s.Substring(0,1), Tail = s.Substring(1)});
        foreach(var p in q) {
            Console.WriteLine("Head = {0}, Tail = {1}", p.Head, p.Tail);
        }
    }
    
    public static void Sample5() { 
        // 结合使用 Select() 与 Where()，以进行完整的查询
        var q = numbers.Where(n => n < 5).Select(n => strings[n]);
        
        Console.WriteLine("Numbers < 5");
        foreach(var x in q) {
            Console.WriteLine(x);
        }       
    }
    
    public static void Sample6() {
        // 在您枚举序列运算符形式的一类查询之前，不会执行这些查询。
        int i = 0;
        var q = numbers.Select(n => ++i);
        // 请注意，在对每个元素进行计算之前，局部变量“i”不会递增(作为副作用)。
        foreach(var v in q) {
          Console.WriteLine("v = {0}, i = {1}", v, i);          
        }
        Console.WriteLine();
        
        // ToList() 这类方法会使查询立即执行，同时缓存结果
        int i2 = 0;
        var q2 = numbers.Select(n => ++i2).ToList();
        // 在循环访问结果前，局部变量 i2 已经完全递增
        foreach(var v in q2) {
          Console.WriteLine("v = {0}, i2 = {1}", v, i2);
        }        
    }
    
    public static void Sample7() {
        // 使用 GroupBy() 将相似元素分组以构造组分区
        var q = strings.GroupBy(s => s[0]); // <- 按每个字符串的第一个字符分组
        
        foreach(var g in q) {
          Console.WriteLine("Group: {0}", g.Key);
          foreach(string v in g) {
            Console.WriteLine("\tValue: {0}", v);
          }
        }
    }
    
    public static void Sample8() {
        // 使用 GroupBy() 和诸如 Count()、Min()、Max()、Sum()、Average() 等聚合函数来对分区计算值
        var q = strings.GroupBy(s => s[0]).Select(g => new {FirstChar = g.Key, Count = g.Count()});
        
        foreach(var v in q) {
          Console.WriteLine("There are {0} string(s) starting with the letter {1}", v.Count, v.FirstChar);
        }
    }
    
    public static void Sample9() {
        // 使用 OrderBy()/OrderByDescending() 对生成的序列进行排序
        var q = strings.OrderBy(s => s);  // 按字符串的名称对字符串进行排序
        
        foreach(string s in q) {
          Console.WriteLine(s);
        }
    }
    
    public static void Sample9a() {  
        // 使用 ThenBy()/ThenByDescending() 提供其他排序详细信息
        var q = persons.OrderBy(p => p.Level).ThenBy(p => p.Name);
        
        foreach(var p in q) {
          Console.WriteLine("{0}  {1}", p.Level, p.Name);
        }
    }
    
    public static void Sample10() {
        // 使用查询表达式进行简化
        var q = from p in persons 
                orderby p.Level, p.Name
                group p.Name by p.Level into g
                select new {Level = g.Key, Persons = g};
        
        foreach(var g in q) {
            Console.WriteLine("Level: {0}", g.Level);
            foreach(var p in g.Persons) {
                Console.WriteLine("Person: {0}", p);
            }
        }                
    }
}
