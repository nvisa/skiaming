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
    // 使用 partial 关键字可以在其他 .cs 文件中定义
    // 此类的附加方法、字段和属性。
    // 此文件包含 CharValues 定义的公共方法。
    partial class CharValues
    {
        public static int CountAlphabeticChars(string str)
        {
            int count = 0;
            foreach (char ch in str)
            {
                // IsAlphabetic 是在 CharTypesPrivate.cs 中定义的
                if (IsAlphabetic(ch))
                    count++;
            }
            return count;
        }
        public static int CountNumericChars(string str)
        {
            int count = 0;
            foreach (char ch in str)
            {
                // IsNumeric 是在 CharTypesPrivate.cs 中定义的
                if (IsNumeric(ch))
                    count++;
            }
            return count;
        }

    }
}

