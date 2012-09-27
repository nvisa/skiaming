// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
// 版权所有(C) Microsoft Corporation。保留所有权利。

using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;

namespace Generics_CSharp
{
    // 尖括号中的类型参数 T。
    public class MyList<T> : IEnumerable<T>
    {
        protected Node head;
        protected Node current = null;

        // 嵌套类型也是 T 上的泛型
        protected class Node
        {
            public Node next;
            // T 作为私有成员数据类型。
            private T data;
            // 在非泛型构造函数中使用的 T。
            public Node(T t)
            {
                next = null;
                data = t;
            }
            public Node Next
            {
                get { return next; }
                set { next = value; }
            }
            // T 作为属性的返回类型。
            public T Data
            {
                get { return data; }
                set { data = value; }
            }
        }

        public MyList()
        {
            head = null;
        }

        // T 作为方法参数类型。
        public void AddHead(T t)
        {
            Node n = new Node(t);
            n.Next = head;
            head = n;
        }

        // 实现 GetEnumerator 以返回 IEnumerator<T>，从而启用列表的
        // foreach 迭代。请注意，在 C# 2.0 中， 
        // 不需要实现 Current 和 MoveNext。
        // 编译器将创建实现 IEnumerator<T> 的类。
        public IEnumerator<T> GetEnumerator()
        {
            Node current = head;

            while (current != null)
            {
                yield return current.Data;
                current = current.Next;
            }
        }

        // 必须实现此方法，因为
        // IEnumerable<T> 继承 IEnumerable
        IEnumerator IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
        }
    }


    public class SortedList<T> : MyList<T> where T : IComparable<T>
    {
        // 一个未优化的简单排序算法，
        // 该算法从低到高对列表元素排序：
        public void BubbleSort()
        {
            if (null == head || null == head.Next)
                return;

            bool swapped;
            do
            {
                Node previous = null;
                Node current = head;
                swapped = false;

                while (current.next != null)
                {
                    // 由于需要调用此方法，因此，SortedList
                    // 类在 IEnumerable<T> 上是受约束的
                    if (current.Data.CompareTo(current.next.Data) > 0)
                    {
                        Node tmp = current.next;
                        current.next = current.next.next;
                        tmp.next = current;

                        if (previous == null)
                        {
                            head = tmp;
                        }
                        else
                        {
                            previous.next = tmp;
                        }
                        previous = tmp;
                        swapped = true;
                    }

                    else
                    {
                        previous = current;
                        current = current.next;
                    }

                }// end while
            } while (swapped);
        }
    }

    // 一个将自身作为类型参数来实现 IComparable<T> 的简单类，
    // 是对象中的
    // 常用设计模式，这些对象
    // 存储在泛型列表中。
    public class Person : IComparable<Person>
    {
        string name;
        int age;

        public Person(string s, int i)
        {
            name = s;
            age = i;
        }

        // 这会使列表元素
        // 按 age 值排序。
        public int CompareTo(Person p)
        {
            return age - p.age;
        }

        public override string ToString()
        {
            return name + ":" + age;
        }

        // 必须实现 Equals。
        public bool Equals(Person p)
        {
            return (this.age == p.age);
        }
    }

    class Generics
    {
        static void Main(string[] args)
        {
            // 声明并实例化一个新的范型 SortedList 类。
            // Person 是类型参数。
            SortedList<Person> list = new SortedList<Person>();

            // 创建 name 和 age 值以初始化 Person 对象。
            string[] names = new string[] { "Franscoise", "Bill", "Li", "Sandra", "Gunnar", "Alok", "Hiroyuki", "Maria", "Alessandro", "Raul" };
            int[] ages = new int[] { 45, 19, 28, 23, 18, 9, 108, 72, 30, 35 };

            // 填充列表。
            for (int x = 0; x < names.Length; x++)
            {
                list.AddHead(new Person(names[x], ages[x]));
            }

            Console.WriteLine("Unsorted List:");
            // 打印出未排序的列表。
            foreach (Person p in list)
            {
                Console.WriteLine(p.ToString());
            }

            // 对列表进行排序。
            list.BubbleSort();

            Console.WriteLine(String.Format("{0}Sorted List:", Environment.NewLine));
            // 打印出排序的列表。
            foreach (Person p in list)
            {
                Console.WriteLine(p.ToString());
            }

            Console.WriteLine("Done");
        }
    }

}
