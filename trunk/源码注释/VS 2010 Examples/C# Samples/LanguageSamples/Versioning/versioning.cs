// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
//版权所有(C) Microsoft Corporation。保留所有权利。

// versioning.cs
// 需要 CS0114
public class MyBase 
{
   public virtual string Meth1() 
   {
      return "MyBase-Meth1";
   }
   public virtual string Meth2() 
   {
      return "MyBase-Meth2";
   }
   public virtual string Meth3() 
   {
      return "MyBase-Meth3";
   }
}

class MyDerived : MyBase 
{
   // 使用 override 关键字重写虚方法 Meth1：
   public override string Meth1() 
   {
      return "MyDerived-Meth1";
   }
   // 使用 new 关键字显式隐藏
   // 虚方法 Meth2：
   public new string Meth2() 
   {
      return "MyDerived-Meth2";
   }
   // 由于下面声明中没有指定任何关键字，
   // 因此将发出一个警告来提醒程序员
   // 该方法隐藏了继承的成员 MyBase.Meth3()：
   public string Meth3() 
   {
      return "MyDerived-Meth3";
   }

   public static void Main() 
   {
      MyDerived mD = new MyDerived();
      MyBase mB = (MyBase) mD;

      System.Console.WriteLine(mB.Meth1());
      System.Console.WriteLine(mB.Meth2());
      System.Console.WriteLine(mB.Meth3());
   }
}

