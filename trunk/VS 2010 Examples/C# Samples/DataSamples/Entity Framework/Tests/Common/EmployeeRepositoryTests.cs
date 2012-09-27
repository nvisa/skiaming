// 版权所有(C) Microsoft Corporation。保留所有权利。

namespace Tests.Common
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using EmployeeTracker.Common;
    using EmployeeTracker.Fakes;
    using EmployeeTracker.Model;
    using Microsoft.VisualStudio.TestTools.UnitTesting;

    /// <summary>
    /// 测试从 EmployeeObjectSetRepository 的数据检索
    /// </summary>
    [TestClass]
    public class EmployeeRepositoryTests
    {
        /// <summary>
        /// 验证 GetAllEmployees 是否从基 ObjectSet 返回所有数据
        /// </summary>
        [TestMethod]
        public void GetAllEmployees()
        {
            Employee e1 = new Employee();
            Employee e2 = new Employee();
            Employee e3 = new Employee();

            using (FakeEmployeeContext ctx = new FakeEmployeeContext(new Employee[] { e1, e2, e3 }, new Department[] { }))
            {
                EmployeeRepository rep = new EmployeeRepository(ctx);

                IEnumerable<Employee> result = rep.GetAllEmployees();

                Assert.IsNotInstanceOfType(
                    result,
                    typeof(IQueryable),
                    "Repositories should not return IQueryable as this allows modification of the query that gets sent to the store. ");

                Assert.AreEqual(3, result.Count());
                Assert.IsTrue(result.Contains(e1));
                Assert.IsTrue(result.Contains(e2));
                Assert.IsTrue(result.Contains(e3));
            }
        }

        /// <summary>
        /// 验证 GetAllEmployees 是否在不存在数据时返回空 IEnumerable
        /// </summary>
        [TestMethod]
        public void GetAllEmployeesEmpty()
        {
            using (FakeEmployeeContext ctx = new FakeEmployeeContext())
            {
                EmployeeRepository rep = new EmployeeRepository(ctx);

                IEnumerable<Employee> result = rep.GetAllEmployees();
                Assert.AreEqual(0, result.Count());
            }
        }

        /// <summary>
        /// 验证 GetLongestServingEmployees 是否正确地筛选和排序数据
        /// </summary>
        [TestMethod]
        public void GetLongestServingEmployees()
        {
            Employee e1 = new Employee { HireDate = new DateTime(2003, 1, 1) };
            Employee e2 = new Employee { HireDate = new DateTime(2001, 1, 1) };
            Employee e3 = new Employee { HireDate = new DateTime(2000, 1, 1) };
            Employee e4 = new Employee { HireDate = new DateTime(2002, 1, 1) };

            // 以下雇员验证 GetLongestServingEmployees 不返回已离职的雇员。
            Employee e5 = new Employee { HireDate = new DateTime(1999, 1, 1), TerminationDate = DateTime.Today };

            using (FakeEmployeeContext ctx = new FakeEmployeeContext(new Employee[] { e1, e2, e3, e4, e5 }, new Department[] { }))
            {
                EmployeeRepository rep = new EmployeeRepository(ctx);

                // 选择子集
                List<Employee> result = rep.GetLongestServingEmployees(2).ToList();
                Assert.AreEqual(2, result.Count, "Expected two items in result.");
                Assert.AreSame(e3, result[0], "Incorrect item at position 0.");
                Assert.AreSame(e2, result[1], "Incorrect item at position 1.");

                // 所选项多于现有项
                result = rep.GetLongestServingEmployees(50).ToList();
                Assert.AreEqual(4, result.Count, "Expected four items in result.");
            }
        }

        /// <summary>
        /// 验证在指定无效 null 参数时，是否引发 ArgumentNullException
        /// </summary>
        [TestMethod]
        public void NullArgumentChecks()
        {
            Utilities.CheckNullArgumentException(() => { new EmployeeRepository(null); }, "context", "ctor");
        }
    }
}
