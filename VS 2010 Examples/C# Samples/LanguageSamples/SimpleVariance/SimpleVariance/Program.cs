// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SimpleVariance
{
    class Animal { }
    class Cat: Animal { }

    class Program
    {
        // 要了解新的协变和逆变代码能够为您实现的功能
        // 尝试从以下两行代码中添加或删除这些内容:
        delegate T Func1<out T>();
        delegate void Action1<in T>(T a);
        
        static void Main(string[] args)
        {
            Func1<Cat> cat = () => new Cat();
            Func1<Animal> animal = cat;

            Action1<Animal> act1 = (ani) => { Console.WriteLine(ani); };
            Action1<Cat> cat1 = act1;

            Console.WriteLine(animal());
            cat1(new Cat());
        }

        
    }
}
