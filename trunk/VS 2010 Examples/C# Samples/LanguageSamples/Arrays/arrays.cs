// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
//版权所有(C) Microsoft Corporation。保留所有权利。

// arrays.cs
using System;
class DeclareArraysSample
{
    public static void Main()
    {
        // 一维数组
        int[] numbers = new int[5];

        // 多维数组
        string[,] names = new string[5,4];

        // 数组的数组（交错数组）
        byte[][] scores = new byte[5][];

        // 创建交错数组
        for (int i = 0; i < scores.Length; i++)
        {
            scores[i] = new byte[i+3];
        }

        // 打印每行的长度
        for (int i = 0; i < scores.Length; i++)
        {
            Console.WriteLine("Length of row {0} is {1}", i, scores[i].Length);
        }
    }
}


