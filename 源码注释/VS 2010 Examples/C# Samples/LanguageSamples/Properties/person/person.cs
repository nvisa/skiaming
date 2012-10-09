// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
//版权所有(C) Microsoft Corporation。保留所有权利。

// person.cs
using System;
class Person
{
    private string myName ="N/A";
    private int myAge = 0;

    // 声明 string 类型的 Name 属性：
    public string Name
    {
        get 
        {
           return myName; 
        }
        set 
        {
           myName = value; 
        }
    }

    // 声明 int 类型的 Age 属性：
    public int Age
    {
        get 
        { 
           return myAge; 
        }
        set 
        { 
           myAge = value; 
        }
    }

    public override string ToString()
    {
        return "Name = " + Name + ", Age = " + Age;
    }

    public static void Main()
    {
        Console.WriteLine("Simple Properties");

        // 创建新的 Person 对象：
        Person person = new Person();

        // 打印出与该对象关联的姓名和年龄：
        Console.WriteLine("Person details - {0}", person);

        // 设置 Person 对象的某些值：
        person.Name = "Joe";
        person.Age = 99;
        Console.WriteLine("Person details - {0}", person);

        // 递增 Age 属性：
        person.Age += 1;
        Console.WriteLine("Person details - {0}", person);
    }
}

