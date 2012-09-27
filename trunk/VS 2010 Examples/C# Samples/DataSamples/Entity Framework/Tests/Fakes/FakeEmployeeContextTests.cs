// 版权所有(C) Microsoft Corporation。保留所有权利。

namespace Tests.Fakes
{
    using System.Collections.Generic;
    using System.Linq;
    using EmployeeTracker.Fakes;
    using EmployeeTracker.Model;
    using Microsoft.VisualStudio.TestTools.UnitTesting;

    /// <summary>
    /// 测试 FakeEmployeeContextTests 的功能
    /// </summary>
    [TestClass]
    public class FakeEmployeeContextTests
    {
        /// <summary>
        /// 验证在 null 无效时，是否引发 NullArgumentExceptions
        /// </summary>
        [TestMethod]
        public void NullArgumentChecks()
        {
            using (FakeEmployeeContext ctx = new FakeEmployeeContext())
            {
                Utilities.CheckNullArgumentException(() => { var c = new FakeEmployeeContext(null, new Department[0]); c.Dispose(); }, "employees", "ctor");
                Utilities.CheckNullArgumentException(() => { var c = new FakeEmployeeContext(new Employee[0], null); c.Dispose(); }, "departments", "ctor");
                Utilities.CheckNullArgumentException(() => { ctx.IsObjectTracked(null); }, "entity", "IsObjectTracked");
            }
        }

        /// <summary>
        /// 验证默认构造函数是否初始化 ObjectSet
        /// </summary>
        [TestMethod]
        public void Initialization()
        {
            using (FakeEmployeeContext ctx = new FakeEmployeeContext())
            {
                Assert.IsNotNull(ctx.Employees, "Constructor did not not initialize Employees ObjectSet.");
                Assert.IsNotNull(ctx.Departments, "Constructor did not initialize Departments ObjectSet.");
                Assert.IsNotNull(ctx.ContactDetails, "Constructor did not initialize ContactDetails ObjectSet.");
            }
        }

        /// <summary>
        /// 验证提供给构造函数的数据是否在 ObjectSet 中可用
        /// </summary>
        [TestMethod]
        public void InitializationWithSuppliedCollections()
        {
            Department dep = new Department();
            ContactDetail det = new Phone();
            Employee emp = new Employee { ContactDetails = new List<ContactDetail> { det } };

            using (FakeEmployeeContext ctx = new FakeEmployeeContext(new Employee[] { emp }, new Department[] { dep }))
            {
                Assert.IsTrue(ctx.Employees.Contains(emp), "Constructor did not add supplied Employees to public ObjectSet.");
                Assert.IsTrue(ctx.Departments.Contains(dep), "Constructor did not add supplied Departments to public ObjectSet.");
                Assert.IsTrue(ctx.ContactDetails.Contains(det), "Constructor did not add supplied ContactDetails to public ObjectSet.");
            }
        }

        /// <summary>
        /// 验证 CreateObject 是否返回类型的新实例
        /// </summary>
        [TestMethod]
        public void CreateObject()
        {
            // 虚设上下文应该创建实际基类型，而不是从其派生的类型
            using (FakeEmployeeContext ctx = new FakeEmployeeContext())
            {
                object entity = ctx.CreateObject<Department>();
                Assert.AreEqual(typeof(Department), entity.GetType(), "Department did not get created.");

                entity = ctx.CreateObject<Employee>();
                Assert.AreEqual(typeof(Employee), entity.GetType(), "Employee did not get created.");

                entity = ctx.CreateObject<Email>();
                Assert.AreEqual(typeof(Email), entity.GetType(), "Email did not get created.");

                entity = ctx.CreateObject<Phone>();
                Assert.AreEqual(typeof(Phone), entity.GetType(), "Phone did not get created.");

                entity = ctx.CreateObject<Address>();
                Assert.AreEqual(typeof(Address), entity.GetType(), "Address did not get created.");
            }
        }

        /// <summary>
        /// 验证在保存上下文时是否引发 SaveCalled 事件
        /// </summary>
        [TestMethod]
        public void SaveCalled()
        {
            using (FakeEmployeeContext ctx = new FakeEmployeeContext())
            {
                bool called = false;
                ctx.SaveCalled += (sender, e) => { called = true; };
                ctx.Save();
                Assert.IsTrue(called, "Save did not raise SaveCalled event.");
            }
        }

        /// <summary>
        /// 验证在释放上下文时是否引发 DisposedCalled 事件
        /// </summary>
        [TestMethod]
        public void DisposeCalled()
        {
            bool called = false;
            using (FakeEmployeeContext ctx = new FakeEmployeeContext())
            {
                ctx.DisposeCalled += (sender, e) => { called = true; };
            }

            Assert.IsTrue(called, "Dispose did not raise DisposeCalled event.");
        }

        /// <summary>
        /// 验证所有实体类型的 IsObjectTracked
        /// </summary>
        [TestMethod]
        public void IsObjectTracked()
        {
            using (FakeEmployeeContext ctx = new FakeEmployeeContext())
            {
                Employee e = new Employee();
                Assert.IsFalse(ctx.IsObjectTracked(e), "IsObjectTracked should be false when entity is not in added.");
                ctx.Employees.AddObject(e);
                Assert.IsTrue(ctx.IsObjectTracked(e), "IsObjectTracked should be true when entity is added.");

                Department d = new Department();
                Assert.IsFalse(ctx.IsObjectTracked(d), "IsObjectTracked should be false when entity is not in added.");
                ctx.Departments.AddObject(d);
                Assert.IsTrue(ctx.IsObjectTracked(d), "IsObjectTracked should be true when entity is added.");

                ContactDetail c = new Phone();
                Assert.IsFalse(ctx.IsObjectTracked(c), "IsObjectTracked should be false when entity is not in added.");
                ctx.ContactDetails.AddObject(c);
                Assert.IsTrue(ctx.IsObjectTracked(c), "IsObjectTracked should be true when entity is added.");
            }
        }
    }
}
