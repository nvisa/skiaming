// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
//版权所有(C) Microsoft Corporation。保留所有权利。

using System;
using System.Collections.Generic;
using System.Text;

namespace PartialClassesExample
{
    class PartialClassesMain
    {
        static void Main(string[] args)
        {
            if (args.Length != 1)
            {
                Console.WriteLine("One argument required.");
                return;
            }

            // CharValues 是一个分部类 -- 该分部类有两个方法
            // 是在 CharTypesPublic.cs 中定义的，另有两个方法是在
            // CharTypesPrivate.cs 中定义的。
            int aCount = CharValues.CountAlphabeticChars(args[0]);
            int nCount = CharValues.CountNumericChars(args[0]);
            
            Console.Write("The input argument contains {0} alphabetic and {1} numeric characters", aCount, nCount);
        }
    }
}

