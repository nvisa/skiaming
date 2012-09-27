// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
//版权所有(C) Microsoft Corporation。保留所有权利。

// explicit2.cs
// 声明英制单位接口：
interface IEnglishDimensions 
{
   float Length();
   float Width();
}
// 声明公制单位接口：
interface IMetricDimensions 
{
   float Length();
   float Width();
}
// 声明实现以下两个接口的“Box”类：
// IEnglishDimensions 和 IMetricDimensions：
class Box : IEnglishDimensions, IMetricDimensions 
{
   float lengthInches;
   float widthInches;
   public Box(float length, float width) 
   {
      lengthInches = length;
      widthInches = width;
   }
// 显式实现 IEnglishDimensions 的成员：
   float IEnglishDimensions.Length() 
   {
      return lengthInches;
   }
   float IEnglishDimensions.Width() 
   {
      return widthInches;      
   }
// 显式实现 IMetricDimensions 的成员：
   float IMetricDimensions.Length() 
   {
      return lengthInches * 2.54f;
   }
   float IMetricDimensions.Width() 
   {
      return widthInches * 2.54f;
   }
   public static void Main() 
   {
      // 声明类实例“myBox”：
      Box myBox = new Box(30.0f, 20.0f);
      // 声明英制单位接口的实例：
      IEnglishDimensions eDimensions = (IEnglishDimensions) myBox;
      // 声明公制单位接口的实例：
      IMetricDimensions mDimensions = (IMetricDimensions) myBox;
      // 以英制单位打印尺寸：
      System.Console.WriteLine("Length(in): {0}", eDimensions.Length());
      System.Console.WriteLine("Width (in): {0}", eDimensions.Width());
      // 以公制单位打印尺寸：
      System.Console.WriteLine("Length(cm): {0}", mDimensions.Length());
      System.Console.WriteLine("Width (cm): {0}", mDimensions.Width());
   }
}

