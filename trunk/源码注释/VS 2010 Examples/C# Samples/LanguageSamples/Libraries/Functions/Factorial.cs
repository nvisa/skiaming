// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
//版权所有(C) Microsoft Corporation。保留所有权利。

// Factorial.cs
// 编译时使用：/target:library
using System; 

// 声明命名空间。需要根据
// 库的命名空间打包库，以便 .NET 运行时可以正确地加载类。
namespace Functions 
{ 
    public class Factorial 
    { 
// “Calc”静态方法为传入的指定整数
// 计算阶乘值：
        public static int Calc(int i) 
        { 
            return((i <= 1) ? 1 : (i * Calc(i-1))); 
        } 
    }
}

