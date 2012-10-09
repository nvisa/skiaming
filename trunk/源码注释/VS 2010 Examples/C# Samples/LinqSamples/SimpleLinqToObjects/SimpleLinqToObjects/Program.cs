// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SimpleLinqToObjects
{
    class SimpleLinqToObjects
    {

        /// <summary>
        /// 本示例演示基本要素 LINQ to Objeects
        /// 程序。请注意，using 子句中包含
        /// “using System.Linq”。此代码中包含下列各项的示例:
        ///     
        ///     * 集合初始值设定项
        ///     * 查询表达式
        ///     * 类型推理
        /// </summary>
        /// <param name="args"></param>
        static void Main()
        {
            // C# 3.0 集合初始值设定项
            List<int> numberList = new List<int> { 1, 2, 3, 4 };

            // 此查询表达式中的 var 关键字演示
            // 如何使用类型推理。请将游标置于
            // var 一词上，以便查看由标识符调用的查询的类型。
            var query = from i in numberList
                        where i < 4
                        select i;

            // 循环访问由查询返回的 IEnumerable 类型。
            foreach (var number in query)
            {
                Console.WriteLine(number);
            }
            Console.ReadLine();
        }
    }
}
