// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
//版权所有(C) Microsoft Corporation。保留所有权利。

using System;

class NullableBoxing
{
    static void Main()
    {
        int? a;
        object oa;

        // 为 a 赋值 Nullable<int> (value = default(int), hasValue = false)。
        a = null;

        // 为 oa 赋值 null（因为 x==null），而不是装箱的“int?”。
        oa = a;

        Console.WriteLine("Testing 'a' and 'boxed a' for null...");
        // 可以将可以为 null 的变量与 null 进行比较。
        if (a == null)
        {
            Console.WriteLine("  a == null");
        }

        // 可以将装箱的可以为 null 的变量与 null 进行比较，
        // 因为对 HasValue==false 的可以为 null 的变量进行装箱
        // 将把引用设置为 null。
        if (oa == null)
        {
            Console.WriteLine("  oa == null");
        }

        Console.WriteLine("Unboxing a nullable type...");
        int? b = 10;
        object ob = b;

        // 装箱的可以为 null 的类型可以取消装箱
        int? unBoxedB = (int?)ob;
        Console.WriteLine("  b={0}, unBoxedB={0}", b, unBoxedB);

        // 如果是取消装箱为可以为 null 的类型，则可以对设置为 null 的可以为 null 的类型
        // 进行取消装箱。
        int? unBoxedA = (int?)oa;
        if (oa == null && unBoxedA == null)
        {
            Console.WriteLine("  a and unBoxedA are null");
        }

        Console.WriteLine("Attempting to unbox into non-nullable type...");
        // 如果是取消装箱为不可以为 null 的类型，则对设置为 null 的可以为 null 的类型
        //取消装箱将引发异常。
        try
        {
            int unBoxedA2 = (int)oa;
        }
        catch (Exception e)
        {
            Console.WriteLine("  {0}", e.Message);
        }
    }

}
