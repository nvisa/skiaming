// 版权所有(C) Microsoft Corporation。保留所有权利。

namespace Tests.EntityFramework
{
    using System.Collections.Generic;
    using System.Linq;
    using EmployeeTracker.Common;
    using EmployeeTracker.Fakes;
    using EmployeeTracker.Model;
    using Microsoft.VisualStudio.TestTools.UnitTesting;

    /// <summary>
    /// 测试从 DepartmentObjectSetRepository 的数据检索
    /// </summary>
    [TestClass]
    public class DepartmentRepositoryTests
    {
        /// <summary>
        /// 验证 GetAllDepartments 是否从基 ObjectSet 返回所有数据
        /// </summary>
        [TestMethod]
        public void GetAllDepartments()
        {
            Department d1 = new Department();
            Department d2 = new Department();
            Department d3 = new Department();

            using (FakeEmployeeContext ctx = new FakeEmployeeContext(new Employee[] { }, new Department[] { d1, d2, d3 }))
            {
                DepartmentRepository rep = new DepartmentRepository(ctx);

                IEnumerable<Department> result = rep.GetAllDepartments();

                Assert.IsNotInstanceOfType(
                    result,
                    typeof(IQueryable),
                    "Repositories should not return IQueryable as this allows modification of the query that gets sent to the store. ");

                Assert.AreEqual(3, result.Count());
                Assert.IsTrue(result.Contains(d1));
                Assert.IsTrue(result.Contains(d2));
                Assert.IsTrue(result.Contains(d3));
            }
        }

        /// <summary>
        /// 验证 GetAllDepartments 是否在不存在数据时返回空 IEnumerable
        /// </summary>
        [TestMethod]
        public void GetAllDepartmentsEmpty()
        {
            using (FakeEmployeeContext ctx = new FakeEmployeeContext())
            {
                DepartmentRepository rep = new DepartmentRepository(ctx);

                IEnumerable<Department> result = rep.GetAllDepartments();
                Assert.AreEqual(0, result.Count());
            }
        }

        /// <summary>
        /// 验证在指定无效 null 参数时，是否引发 ArgumentNullException
        /// </summary>
        [TestMethod]
        public void NullArgumentChecks()
        {
            Utilities.CheckNullArgumentException(() => { new DepartmentRepository(null); }, "context", "ctor");
        }
    }
}
