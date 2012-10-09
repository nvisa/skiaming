// 版权所有(C) Microsoft Corporation。保留所有权利。

namespace Tests.EntityFramework
{
    using System.Data.Objects.DataClasses;
    using EmployeeTracker.EntityFramework;
    using EmployeeTracker.Model;
    using Microsoft.VisualStudio.TestTools.UnitTesting;

    /// <summary>
    /// 测试已添加到 EF 上下文的功能
    /// </summary>
    [TestClass]
    public class EmployeeEntitiesTests
    {
        /// <summary>
        /// 验证 EF 是否可以代理模型中的所有类
        /// </summary>
        [TestMethod]
        public void AllEntitiesBecomeChangeTrackingProxies()
        {
            using (EmployeeEntities ctx = new EmployeeEntities())
            {
                object entity = ctx.CreateObject<Department>();
                Assert.IsInstanceOfType(entity, typeof(IEntityWithChangeTracker), "Department did not get proxied.");

                entity = ctx.CreateObject<Employee>();
                Assert.IsInstanceOfType(entity, typeof(IEntityWithChangeTracker), "Employee did not get proxied.");

                entity = ctx.CreateObject<Email>();
                Assert.IsInstanceOfType(entity, typeof(IEntityWithChangeTracker), "Email did not get proxied.");

                entity = ctx.CreateObject<Phone>();
                Assert.IsInstanceOfType(entity, typeof(IEntityWithChangeTracker), "Phone did not get proxied.");

                entity = ctx.CreateObject<Address>();
                Assert.IsInstanceOfType(entity, typeof(IEntityWithChangeTracker), "Address did not get proxied.");
            }
        }

        /// <summary>
        /// 验证所有实体类型的 IsObjectTracked
        /// </summary>
        [TestMethod]
        public void IsObjectTracked()
        {
            using (EmployeeEntities ctx = new EmployeeEntities())
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
