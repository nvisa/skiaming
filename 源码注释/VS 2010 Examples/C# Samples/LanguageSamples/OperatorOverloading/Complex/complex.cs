// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
//版权所有(C) Microsoft Corporation。保留所有权利。

// complex.cs
using System;

public struct Complex 
{
   public int real;
   public int imaginary;

   public Complex(int real, int imaginary) 
   {
      this.real = real;
      this.imaginary = imaginary;
   }

   // 声明要重载的运算符 (+)、
   // 可相加的类型（两个 Complex 对象）以及
   // return type (Complex):
   public static Complex operator +(Complex c1, Complex c2) 
   {
      return new Complex(c1.real + c2.real, c1.imaginary + c2.imaginary);
   }
   // 重写 ToString 方法，从而以适当的格式显示复数：
   public override string ToString()
   {
      return(String.Format("{0} + {1}i", real, imaginary));
   }

   public static void Main() 
   {
      Complex num1 = new Complex(2,3);
      Complex num2 = new Complex(3,4);

      // 通过重载的加号运算符
      // 将两个 Complex 对象（num1 和 num2）相加：
      Complex sum = num1 + num2;

     // 使用重写的 ToString 方法打印数字以及相加得到的和：
      Console.WriteLine("First complex number:  {0}",num1);
      Console.WriteLine("Second complex number: {0}",num2);
      Console.WriteLine("The sum of the two numbers: {0}",sum);
 
   }
}

