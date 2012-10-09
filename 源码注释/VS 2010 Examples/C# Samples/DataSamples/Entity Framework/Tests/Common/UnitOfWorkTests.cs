// 版权所有(C) Microsoft Corporation。保留所有权利。

namespace Tests.Common
{
    using System;
    using System.Linq;
    using EmployeeTracker.Common;
    using EmployeeTracker.Fakes;
    using EmployeeTracker.Model;
    using Microsoft.VisualStudio.TestTools.UnitTesting;

    /// <summary>
    /// 验证 UnitOfWork 的更改跟踪功能
    /// </summary>
    [TestClass]
    public class UnitOfWorkTests
    {
        /// <summary>
        /// 验证在 null 无效时，是否引发 NullArgumentExceptions
        /// </summary>
        [TestMethod]
        public void NullArgumentChecks()
        {
            using (FakeEmployeeContext ctx = new FakeEmployeeContext())
            {
                UnitOfWork unit = new UnitOfWork(ctx);

                Utilities.CheckNullArgumentException(() => { new UnitOfWork(null); }, "context", "ctor");

                Utilities.CheckNullArgumentException(() => { unit.AddEmployee(null); }, "employee", "AddEmployee");
                Utilities.CheckNullArgumentException(() => { unit.AddDepartment(null); }, "department", "AddDepartment");
                Utilities.CheckNullArgumentException(() => { unit.AddContactDetail(new Employee(), null); }, "detail", "AddContactDetail");
                Utilities.CheckNullArgumentException(() => { unit.AddContactDetail(null, new Phone()); }, "employee", "AddContactDetail");

                Utilities.CheckNullArgumentException(() => { unit.RemoveEmployee(null); }, "employee", "RemoveEmployee");
                Utilities.CheckNullArgumentException(() => { unit.RemoveDepartment(null); }, "department", "RemoveDepartment");
                Utilities.CheckNullArgumentException(() => { unit.RemoveContactDetail(null, new Phone()); }, "employee", "RemoveContactDetail");
                Utilities.CheckNullArgumentException(() => { unit.RemoveContactDetail(new Employee(), null); }, "detail", "RemoveContactDetail");
            }
        }

        /// <summary>
        /// 验证 CreateObject 是否为模型中的类型返回有效对象
        /// </summary>
        [TestMethod]
        public void CreateObject()
        {
            using (FakeEmployeeContext ctx = new FakeEmployeeContext())
            {
                UnitOfWork unit = new UnitOfWork(ctx);

                object entity = unit.CreateObject<Department>();
                Assert.IsInstanceOfType(entity, typeof(Department), "Department did not get created.");

                entity = unit.CreateObject<Employee>();
                Assert.IsInstanceOfType(entity, typeof(Employee), "Employee did not get created.");

                entity = unit.CreateObject<Email>();
                Assert.IsInstanceOfType(entity, typeof(Email), "Email did not get created.");

                entity = unit.CreateObject<Phone>();
                Assert.IsInstanceOfType(entity, typeof(Phone), "Phone did not get created.");

                entity = unit.CreateObject<Address>();
                Assert.IsInstanceOfType(entity, typeof(Address), "Address did not get created.");
            }
        }

        /// <summary>
        /// 验证部门是否已添加到基础上下文
        /// </summary>
        [TestMethod]
        public void AddDepartment()
        {
            using (FakeEmployeeContext ctx = new FakeEmployeeContext())
            {
                UnitOfWork unit = new UnitOfWork(ctx);

                Department dep = new Department();
                unit.AddDepartment(dep);
                Assert.IsTrue(ctx.Departments.Contains(dep), "Department was not added to underlying context.");
            }
        }

        /// <summary>
        /// 验证当添加已存在于基础上下文中的部门时引发的异常
        /// </summary>
        [TestMethod]
        public void AddDepartmentAlreadyInUnitOfWork()
        {
            using (FakeEmployeeContext ctx = new FakeEmployeeContext())
            {
                UnitOfWork unit = new UnitOfWork(ctx);

                Department dep = new Department();
                unit.AddDepartment(dep);

                try
                {
                    unit.AddDepartment(dep);
                    Assert.Fail("Adding an Department that was already added did not throw.");
                }
                catch (InvalidOperationException ex)
                {
                    Assert.AreEqual("The supplied Department is already part of this Unit of Work.", ex.Message);
                }
            }
        }

        /// <summary>
        /// 验证雇员是否已添加到基础上下文
        /// </summary>
        [TestMethod]
        public void AddEmployee()
        {
            using (FakeEmployeeContext ctx = new FakeEmployeeContext())
            {
                UnitOfWork unit = new UnitOfWork(ctx);

                Employee emp = new Employee();
                unit.AddEmployee(emp);
                Assert.IsTrue(ctx.Employees.Contains(emp), "Employee was not added to underlying context.");
            }
        }

        /// <summary>
        /// 验证当添加已存在于基础上下文中的雇员时引发的异常
        /// </summary>
        [TestMethod]
        public void AddEmployeeAlreadyInUnitOfWork()
        {
            using (FakeEmployeeContext ctx = new FakeEmployeeContext())
            {
                UnitOfWork unit = new UnitOfWork(ctx);

                Employee emp = new Employee();
                unit.AddEmployee(emp);

                try
                {
                    unit.AddEmployee(emp);
                    Assert.Fail("Adding an Employee that was already added did not throw.");
                }
                catch (InvalidOperationException ex)
                {
                    Assert.AreEqual("The supplied Employee is already part of this Unit of Work.", ex.Message);
                }
            }
        }

        /// <summary>
        /// 验证联系人详细信息是否已添加到基础上下文
        /// 通过在类上调用构造函数创建的联系人详细信息
        /// </summary>
        [TestMethod]
        public void AddContactDetailFromDefaultConstructor()
        {
            using (FakeEmployeeContext ctx = new FakeEmployeeContext())
            {
                UnitOfWork unit = new UnitOfWork(ctx);
                Employee emp = new Employee();
                unit.AddEmployee(emp);

                ContactDetail cd = new Address();
                unit.AddContactDetail(emp, cd);
                Assert.IsTrue(ctx.ContactDetails.Contains(cd), "ContactDetail was not added to underlying context.");
            }
        }

        /// <summary>
        /// 验证当添加已存在于基础上下文中的联系人详细信息时引发的异常
        /// </summary>
        [TestMethod]
        public void AddContactDetailAlreadyInUnitOfWork()
        {
            using (FakeEmployeeContext ctx = new FakeEmployeeContext())
            {
                UnitOfWork unit = new UnitOfWork(ctx);

                Employee emp = new Employee();
                ContactDetail detail = new Phone();
                unit.AddEmployee(emp);
                unit.AddContactDetail(emp, detail);

                try
                {
                    unit.AddContactDetail(emp, detail);
                    Assert.Fail("Adding an ContactDetail that was already added did not throw.");
                }
                catch (InvalidOperationException ex)
                {
                    Assert.AreEqual("The supplied Phone is already part of this Unit of Work.", ex.Message);
                }
            }
        }

        /// <summary>
        /// 验证当为不在基础上下文中的雇员添加联系人详细信息时引发的异常
        /// </summary>
        [TestMethod]
        public void AddContactDetailToEmployeeOutsideUnitOfWork()
        {
            using (FakeEmployeeContext ctx = new FakeEmployeeContext())
            {
                UnitOfWork unit = new UnitOfWork(ctx);
                Employee emp = new Employee();
                ContactDetail detail = new Email();

                try
                {
                    unit.AddContactDetail(emp, detail);
                    Assert.Fail("Adding a contact detail to an employee outside the Unit of Work did not throw.");
                }
                catch (InvalidOperationException ex)
                {
                    Assert.AreEqual("The supplied Employee is not part of this Unit of Work.", ex.Message);
                }
            }
        }

        /// <summary>
        /// 验证部门是否可从基础上下文移除
        /// </summary>
        [TestMethod]
        public void RemoveDepartment()
        {
            using (FakeEmployeeContext ctx = new FakeEmployeeContext())
            {
                UnitOfWork unit = new UnitOfWork(ctx);
                Department dep = new Department();
                unit.AddDepartment(dep);

                unit.RemoveDepartment(dep);
                Assert.IsFalse(ctx.Departments.Contains(dep), "Department was not removed from underlying context.");
            }
        }

        /// <summary>
        /// 验证当雇员的部门被删除时，是否清除其部门信息
        /// </summary>
        [TestMethod]
        public void RemoveDepartmentWithEmployees()
        {
            using (FakeEmployeeContext ctx = new FakeEmployeeContext())
            {
                UnitOfWork unit = new UnitOfWork(ctx);
                Department dep = new Department();
                Employee emp = new Employee();
                unit.AddDepartment(dep);
                unit.AddEmployee(emp);
                emp.Department = dep;

                unit.RemoveDepartment(dep);
                Assert.IsFalse(ctx.Departments.Contains(dep), "Department was not removed from underlying context.");
                Assert.IsNull(emp.Department, "Employee.Department property has not been nulled when deleting department.");
                Assert.IsNull(emp.DepartmentId, "Employee.DepartmentId property has not been nulled when deleting department.");
                Assert.AreEqual(0, dep.Employees.Count, "Department.Employees collection was not cleared when deleting department.");
            }
        }

        /// <summary>
        /// 验证在移除不在当前基础上下文中的部门时引发的异常
        /// </summary>
        [TestMethod]
        public void RemoveDepartmentOutsideUnitOfWork()
        {
            using (FakeEmployeeContext ctx = new FakeEmployeeContext())
            {
                UnitOfWork unit = new UnitOfWork(ctx);
                try
                {
                    unit.RemoveDepartment(new Department());
                    Assert.Fail("Removing a Department that was not added to Unit of Work did not throw.");
                }
                catch (InvalidOperationException ex)
                {
                    Assert.AreEqual("The supplied Department is not part of this Unit of Work.", ex.Message);
                }
            }
        }

        /// <summary>
        /// 验证雇员是否可从基础上下文移除
        /// </summary>
        [TestMethod]
        public void RemoveEmployee()
        {
            using (FakeEmployeeContext ctx = new FakeEmployeeContext())
            {
                UnitOfWork unit = new UnitOfWork(ctx);
                Employee emp = new Employee();
                unit.AddEmployee(emp);

                unit.RemoveEmployee(emp);
                Assert.IsFalse(ctx.Employees.Contains(emp), "Employee was not removed from underlying context.");
            }
        }

        /// <summary>
        /// 验证雇员是否可从基础上下文移除
        /// 且未为该雇员分配经理
        /// </summary>
        [TestMethod]
        public void RemoveEmployeeWithManager()
        {
            using (FakeEmployeeContext ctx = new FakeEmployeeContext())
            {
                UnitOfWork unit = new UnitOfWork(ctx);
                Employee emp = new Employee();
                Employee man = new Employee();
                unit.AddEmployee(emp);
                unit.AddEmployee(man);
                emp.Manager = man;

                unit.RemoveEmployee(emp);
                Assert.IsFalse(ctx.Employees.Contains(emp), "Employee was not removed from underlying context.");
                Assert.AreEqual(0, man.Reports.Count, "Employee was not removed from managers reports.");
                Assert.IsNull(emp.Manager, "Manager property on Employee was not cleared.");
            }
        }

        /// <summary>
        /// 验证雇员是否可从基础上下文移除
        /// 且所有报告未分配
        /// </summary>
        [TestMethod]
        public void RemoveEmployeeWithReports()
        {
            using (FakeEmployeeContext ctx = new FakeEmployeeContext())
            {
                UnitOfWork unit = new UnitOfWork(ctx);
                Employee emp = new Employee();
                Employee man = new Employee();
                unit.AddEmployee(emp);
                unit.AddEmployee(man);
                emp.Manager = man;

                unit.RemoveEmployee(man);
                Assert.IsFalse(ctx.Employees.Contains(man), "Employee was not removed from underlying context.");
                Assert.AreEqual(0, man.Reports.Count, "Employee was not removed from managers reports.");
                Assert.IsNull(emp.Manager, "Manager property on Employee was not cleared.");
            }
        }

        /// <summary>
        /// 验证在移除不在当前基础上下文中的雇员时引发的异常
        /// </summary>
        [TestMethod]
        public void RemoveEmployeeOutsideUnitOfWork()
        {
            using (FakeEmployeeContext ctx = new FakeEmployeeContext())
            {
                UnitOfWork unit = new UnitOfWork(ctx);

                try
                {
                    unit.RemoveEmployee(new Employee());
                    Assert.Fail("Removing an Employee that was not added to Unit of Work did not throw.");
                }
                catch (InvalidOperationException ex)
                {
                    Assert.AreEqual("The supplied Employee is not part of this Unit of Work.", ex.Message);
                }
            }
        }

        /// <summary>
        /// 验证联系人详细信息是否可从基础上下文移除
        /// </summary>
        [TestMethod]
        public void RemoveContactDetail()
        {
            using (FakeEmployeeContext ctx = new FakeEmployeeContext())
            {
                UnitOfWork unit = new UnitOfWork(ctx);

                Employee emp = new Employee();
                ContactDetail detail = new Phone();
                unit.AddEmployee(emp);
                unit.AddContactDetail(emp, detail);

                unit.RemoveContactDetail(emp, detail);
                Assert.IsFalse(ctx.ContactDetails.Contains(detail), "ContactDetail was not removed from underlying context.");
                Assert.IsFalse(
                    emp.ContactDetails.Contains(detail),
                    "ContactDetail is still in collection on Employee after being removed via Unit of Work.");
            }
        }

        /// <summary>
        /// 验证在移除不在基础上下文中的联系人详细信息时引发的异常
        /// </summary>
        [TestMethod]
        public void RemoveContactDetailOutsideUnitOfWork()
        {
            using (FakeEmployeeContext ctx = new FakeEmployeeContext())
            {
                UnitOfWork unit = new UnitOfWork(ctx);
                try
                {
                    unit.RemoveContactDetail(new Employee(), new Address());
                    Assert.Fail("Removing a ContactDetail that was not added to Unit of Work did not throw.");
                }
                catch (InvalidOperationException ex)
                {
                    Assert.AreEqual("The supplied Address is not part of this Unit of Work.", ex.Message);
                }
            }
        }
    }
}
