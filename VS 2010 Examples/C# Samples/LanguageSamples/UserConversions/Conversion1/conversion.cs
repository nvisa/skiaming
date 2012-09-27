// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
//版权所有(C) Microsoft Corporation。保留所有权利。

// conversion.cs
using System;

struct RomanNumeral
{
    public RomanNumeral(int value) 
    { 
       this.value = value; 
    }
    // 声明从 int 到 RomanNumeral 的转换。请注意
    // operator 关键字的使用。这是名为 
    // RomanNumeral 的转换运算符：
    static public implicit operator RomanNumeral(int value) 
    {
       // 请注意，由于 RomanNumeral 声明为结构，
       // 因此对该结构调用 new 只是调用构造函数
       // 而不是在堆上分配对象：
       return new RomanNumeral(value);
    }
    // 声明从 RomanNumeral 到 int 的显式转换：
    static public explicit operator int(RomanNumeral roman)
    {
       return roman.value;
    }
    // 声明从 RomanNumeral 到
    // string 的隐式转换：
    static public implicit operator string(RomanNumeral roman)
    {
       return("Conversion not yet implemented");
    }
    private int value;
}

class Test
{
    static public void Main()
    {
        RomanNumeral numeral;

        numeral = 10;

// 调用从 numeral 到 int 的显式转换。由于是显式转换，
// 因此必须使用强制转换：
        Console.WriteLine((int)numeral);

// 调用到 string 的隐式转换。由于没有
// 强制转换，到 string 的隐式转换是可以考虑的
// 唯一转换：
        Console.WriteLine(numeral);
 
// 调用从 numeral 到 int 的显式转换，
// 然后调用从 int 到 short 的显式转换：
        short s = (short)numeral;

        Console.WriteLine(s);
    }
}

