// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
//版权所有(C) Microsoft Corporation。保留所有权利。

using System;

class NullableOperator
{
    static int? GetNullableInt()
    {
        return null;
    }

    static string GetStringValue()
    {
        return null;
    }

    static void Main()
    {
        // ?? 运算符示例。
        int? x = null;

        // y = x，只有当 x 为 null 时，y = -1。
        int y = x ?? -1;
        Console.WriteLine("y == " + y);                          

        // 将方法的返回值赋给 i，
        // 仅当返回值为 null 时，
        // 将默认的 int 值赋给 i。
        int i = GetNullableInt() ?? default(int);
        Console.WriteLine("i == " + i);                          

        // ?? 也适用于引用类型。
        string s = GetStringValue();
        // 显示 s 的内容，仅当 s 为 null 时，
        // 显示“未指定”。
        Console.WriteLine("s = {0}", s ?? "null");
    }
}
