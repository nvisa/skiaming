// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
//版权所有(C) Microsoft Corporation。保留所有权利。

// DigitCounter.cs
// 编译时使用：/target:library
using System; 

// 声明与 Factorial.cs 中的命名空间相同的命名空间。这样仅允许将 
// 类型添加到同一个命名空间中。
namespace Functions 
{
    public class DigitCount 
    {
        // NumberOfDigits 静态方法计算
        // 传递的字符串中数字字符的数目：
        public static int NumberOfDigits(string theString) 
        {
            int count = 0; 
            for ( int i = 0; i < theString.Length; i++ ) 
            {
                if ( Char.IsDigit(theString[i]) ) 
                {
                    count++; 
                }
            }
            return count;
        }
    }
}

