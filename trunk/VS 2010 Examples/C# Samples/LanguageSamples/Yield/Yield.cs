// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
//版权所有(C) Microsoft Corporation。保留所有权利。

using System;
using System.Collections.Generic;
using System.Text;

namespace Yield
{
    class Yield
    {
        public static class NumberList
        {
            // 创建一个整数数组。
            public static int[] ints = { 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377 };

            // 定义一个仅返回偶数的属性。
            public static IEnumerable<int> GetEven()
            {
                // 使用 yield 返回列表中的偶数。
                foreach (int i in ints)
                    if (i % 2 == 0)
                        yield return i;
            }

            // 定义一个仅返回偶数的属性。
            public static IEnumerable<int> GetOdd()
            {
                // 使用 yield 仅返回奇数。
                foreach (int i in ints)
                    if (i % 2 == 1)
                        yield return i;
            }
        }

        static void Main(string[] args)
        {

            // 显示偶数。
            Console.WriteLine("Even numbers");
            foreach (int i in NumberList.GetEven())
                Console.WriteLine(i);

            // 显示奇数。
            Console.WriteLine("Odd numbers");
            foreach (int i in NumberList.GetOdd())
                Console.WriteLine(i);
        }
    }
}

