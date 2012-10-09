// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
//版权所有(C) Microsoft Corporation。保留所有权利。

using System;
using System.Collections.Generic;
using System.Text;

namespace AnonymousDelegate_Sample
{

    // 定义委托方法。
    delegate decimal CalculateBonus(decimal sales);

    // 定义一个 Employee 类型。
    class Employee
    {
        public string name;
        public decimal sales;
        public decimal bonus;
        public CalculateBonus calculation_algorithm;
    }

    class Program
    {

        // 此类将定义两个执行计算的委托。
        // 第一个是命名方法，第二个是匿名委托。

        // 首先是命名方法。
        // 该方法定义“奖金计算”算法的一个可能实现。

        static decimal CalculateStandardBonus(decimal sales)
        {
            return sales / 10;
        }

        static void Main(string[] args)
        {

            // 奖金计算中用到的值。
            // 注意: 此局部变量将变为“捕获的外部变量”。
            decimal multiplier = 2;

            // 将此委托定义为命名方法。
            CalculateBonus standard_bonus = new CalculateBonus(CalculateStandardBonus);

            // 此委托是匿名的，没有命名方法。
            // 它定义了一个备选的奖金计算算法。
            CalculateBonus enhanced_bonus = delegate(decimal sales) { return multiplier * sales / 10; };

            // 声明一些 Employee 对象。
            Employee[] staff = new Employee[5];

            // 填充 Employees 数组。
            for (int i = 0; i < 5; i++)
                staff[i] = new Employee();

            // 将初始值赋给 Employees。
            staff[0].name = "Mr Apple";
            staff[0].sales = 100;
            staff[0].calculation_algorithm = standard_bonus;

            staff[1].name = "Ms Banana";
            staff[1].sales = 200;
            staff[1].calculation_algorithm = standard_bonus;

            staff[2].name = "Mr Cherry";
            staff[2].sales = 300;
            staff[2].calculation_algorithm = standard_bonus;

            staff[3].name = "Mr Date";
            staff[3].sales = 100;
            staff[3].calculation_algorithm = enhanced_bonus;

            staff[4].name = "Ms Elderberry";
            staff[4].sales = 250;
            staff[4].calculation_algorithm = enhanced_bonus;

            // 计算所有 Employee 的奖金
            foreach (Employee person in staff)
                PerformBonusCalculation(person);

            // 显示所有 Employee 的详细信息
            foreach (Employee person in staff)
                DisplayPersonDetails(person);


        }

        public static void PerformBonusCalculation(Employee person)
        {

            // 此方法使用存储在 person 对象中的委托
            // 来进行计算。
            // 注意: 此方法能够识别乘数局部变量，尽管
            // 该变量在此方法的范围之外。
            //该乘数变量是一个“捕获的外部变量”。
            person.bonus = person.calculation_algorithm(person.sales);
        }

        public static void DisplayPersonDetails(Employee person)
        {
            Console.WriteLine(person.name);
            Console.WriteLine(person.bonus);
            Console.WriteLine("---------------");
        }
    }
}


