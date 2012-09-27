// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
//版权所有(C) Microsoft Corporation。保留所有权利。

// structconversion.cs
using System;

struct RomanNumeral
{
    public RomanNumeral(int value) 
    {
        this.value = value; 
    }
    static public implicit operator RomanNumeral(int value)
    {
        return new RomanNumeral(value);
    }
    static public implicit operator RomanNumeral(BinaryNumeral binary)
    {
        return new RomanNumeral((int)binary);
    }
    static public explicit operator int(RomanNumeral roman)
    {
         return roman.value;
    }
    static public implicit operator string(RomanNumeral roman) 
    {
        return("Conversion not yet implemented");
    }
    private int value;
}

struct BinaryNumeral
{
    public BinaryNumeral(int value) 
    {
        this.value = value;
    }
    static public implicit operator BinaryNumeral(int value)
    {
        return new BinaryNumeral(value);
    }
    static public implicit operator string(BinaryNumeral binary)
    {
        return("Conversion not yet implemented");
    }
    static public explicit operator int(BinaryNumeral binary)
    {
        return(binary.value);
    }

    private int value;
}

class Test
{
    static public void Main()
    {
        RomanNumeral roman;
        roman = 10;
        BinaryNumeral binary;
        // 执行从 RomanNumeral 到
        // BinaryNumeral 的转换：
        binary = (BinaryNumeral)(int)roman;
        // 执行从 BinaryNumeral 到 RomanNumeral 的转换。
        // 不需要任何强制转换：
        roman = binary;
        Console.WriteLine((int)binary);
        Console.WriteLine(binary);
    }
}

