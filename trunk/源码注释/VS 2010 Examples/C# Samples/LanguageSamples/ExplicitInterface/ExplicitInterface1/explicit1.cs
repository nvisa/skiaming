// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
//  Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
//版权所有(C) Microsoft Corporation。保留所有权利。

// explicit1.cs
interface IDimensions 
{
   float Length();
   float Width();
}

class Box : IDimensions 
{
   float lengthInches;
   float widthInches;

   public Box(float length, float width) 
   {
      lengthInches = length;
      widthInches = width;
   }
   // 显式接口成员实现：
   float IDimensions.Length() 
   {
      return lengthInches;
   }
   // 显式接口成员实现：
   float IDimensions.Width() 
   {
      return widthInches;      
   }

   public static void Main() 
   {
      // 声明类实例“myBox”：
      Box myBox = new Box(30.0f, 20.0f);
      // 声明接口实例“myDimensions”：
      IDimensions myDimensions = (IDimensions) myBox;
      // 打印出盒子的尺寸：
      /* 下列注释行将产生编译 
         错误，因为这些行尝试从类实例访问显式实现的
         接口成员：                    */
      //System.Console.WriteLine("Length: {0}", myBox.Length());
      //System.Console.WriteLine("Width: {0}", myBox.Width());
      /* 从接口的实例调用方法，
         以打印出盒子的尺寸：                         */
      System.Console.WriteLine("Length: {0}", myDimensions.Length());
      System.Console.WriteLine("Width: {0}", myDimensions.Width());
   }
}

