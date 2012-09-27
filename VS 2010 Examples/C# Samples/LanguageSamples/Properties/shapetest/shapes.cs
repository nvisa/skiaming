// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
//版权所有(C) Microsoft Corporation。保留所有权利。

// shapes.cs
// 编译时使用：/target:library /reference:abstractshape.dll
public class Square : Shape
{
   private int mySide;

   public Square(int side, string id) : base(id)
   {
      mySide = side;
   }

   public override double Area
   {
      get
      {
         // 已知边长，返回正方形的面积：
         return mySide * mySide;
      }
   }
}

public class Circle : Shape
{
   private int myRadius;

   public Circle(int radius, string id) : base(id)
   {
      myRadius = radius;
   }

   public override double Area
   {
      get
      {
         // 已知半径，返回圆的面积：
         return myRadius * myRadius * System.Math.PI;
      }
   }
}

public class Rectangle : Shape
{
   private int myWidth;
   private int myHeight;

   public Rectangle(int width, int height, string id) : base(id)
   {
      myWidth  = width;
      myHeight = height;
   }

   public override double Area
   {
      get
      {
         // 已知宽度和高度，返回矩形的面积：
         return myWidth * myHeight;
      }
   }
}

