// 版权所有(C) Microsoft Corporation。保留所有权利。

namespace Tests.Fakes
{
    using System;
    using System.Collections.Generic;
    using System.Diagnostics.CodeAnalysis;
    using System.Globalization;
    using System.Linq;
    using System.Text;
    using EmployeeTracker.Fakes;
    using EmployeeTracker.Model;
    using Microsoft.VisualStudio.TestTools.UnitTesting;

    /// <summary>
    /// 测试 FakeObjectSet 中的 IObjectSet 实现
    /// </summary>
    [TestClass]
    public class FakeObjectSetTests
    {
        /// <summary>
        /// 验证在构造函数中传递的数据在枚举器中是否可用
        /// </summary>
        [TestMethod]
        public void InitializationWithTestData()
        {
            Employee emp = new Employee();
            FakeObjectSet<Employee> set = new FakeObjectSet<Employee>(new Employee[] { emp });
            Assert.IsTrue(set.Contains(emp), "Constructor did not add supplied Employees to public Enumerator.");
        }

        /// <summary>
        /// 验证对象是否可以添加到集合并返回
        /// </summary>
        [TestMethod]
        public void AddObject()
        {
            Employee emp = new Employee();
            FakeObjectSet<Employee> set = new FakeObjectSet<Employee>();
            set.AddObject(emp);
            Assert.IsTrue(set.Contains(emp), "AddObject did not add supplied Employees to public Enumerator.");
        }

        /// <summary>
        /// 验证对象是否可以附加到集合并返回
        /// </summary>
        [TestMethod]
        public void Attach()
        {
            Employee emp = new Employee();
            FakeObjectSet<Employee> set = new FakeObjectSet<Employee>();
            set.Attach(emp);
            Assert.IsTrue(set.Contains(emp), "Attach did not add supplied Employees to public Enumerator.");
        }

        /// <summary>
        /// 验证对象是否可以从集合中删除并不再返回
        /// </summary>
        [TestMethod]
        public void DeleteObject()
        {
            Employee emp = new Employee();
            FakeObjectSet<Employee> set = new FakeObjectSet<Employee>(new Employee[] { emp });
            set.DeleteObject(emp);
            Assert.IsFalse(set.Contains(emp), "DeleteObject did not remove supplied Employees to public Enumerator.");
        }

        /// <summary>
        /// 验证对象是否可以从集合中分离并不再返回
        /// </summary>
        [TestMethod]
        public void Detach()
        {
            Employee emp = new Employee();
            FakeObjectSet<Employee> set = new FakeObjectSet<Employee>(new Employee[] { emp });
            set.Detach(emp);
            Assert.IsFalse(set.Contains(emp), "Detach did not remove supplied Employees to public Enumerator.");
        }

        /// <summary>
        /// 验证在 null 无效时，是否引发 NullArgumentExceptions
        /// </summary>
        [TestMethod]
        public void NullArgumentChecks()
        {
            Utilities.CheckNullArgumentException(() => { new FakeObjectSet<Employee>(null); }, "testData", "ctor");

            FakeObjectSet<Employee> set = new FakeObjectSet<Employee>();
            Utilities.CheckNullArgumentException(() => { set.AddObject(null); }, "entity", "AddObject");
            Utilities.CheckNullArgumentException(() => { set.DeleteObject(null); }, "entity", "DeleteObject");
            Utilities.CheckNullArgumentException(() => { set.Attach(null); }, "entity", "Attach");
            Utilities.CheckNullArgumentException(() => { set.Detach(null); }, "entity", "Detach");
        }
    }
}
