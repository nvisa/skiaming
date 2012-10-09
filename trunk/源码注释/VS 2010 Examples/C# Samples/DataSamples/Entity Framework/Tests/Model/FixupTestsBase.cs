// 版权所有(C) Microsoft Corporation。保留所有权利。

namespace Tests.Model
{
    using EmployeeTracker.Model;
    using Microsoft.VisualStudio.TestTools.UnitTesting;

    /// <summary>
    /// 用于验证对象之间的链接地址信息行为的测试的基类
    /// 它用于测试 Pure POCO 和 Entity Framework 代理对象
    /// 以确保它们具有相同的行为。
    /// </summary>
    [TestClass]
    public abstract class FixupTestsBase
    {
        #region 部门 - 雇员

        /// <summary>
        /// 将没有分配部门的雇员添加到新的部门雇员集合
        /// </summary>
        [TestMethod]
        public void AddUnassignedEmployeeToDepartment()
        {
            Department dep = CreateObject<Department>();
            Employee emp = CreateObject<Employee>();

            dep.Employees.Add(emp);
            Assert.IsTrue(dep.Employees.Contains(emp), "Employee was not added to collection on department.");
            Assert.AreSame(dep, emp.Department, "Department was not set on employee.");
        }

        /// <summary>
        /// 将属于某个现有部门的雇员添加到新的部门雇员集合
        /// </summary>
        [TestMethod]
        public void AddAssignedEmployeeToDepartment()
        {
            Employee emp = CreateObject<Employee>();
            Department depOriginal = CreateObject<Department>(); 
            Department depNew = CreateObject<Department>();
            depOriginal.Employees.Add(emp);

            depNew.Employees.Add(emp);
            Assert.IsFalse(depOriginal.Employees.Contains(emp), "Employee was not removed from collection on old department.");
            Assert.IsTrue(depNew.Employees.Contains(emp), "Employee was not added to collection on CreateObject<department.");
            Assert.AreSame(depNew, emp.Department, "Department was not set on employee.");
        }

        /// <summary>
        /// 将雇员从部门雇员集合中移除
        /// </summary>
        [TestMethod]
        public void RemoveEmployeeFromDepartment()
        {
            Department dep = CreateObject<Department>(); 
            Employee emp = CreateObject<Employee>();
            dep.Employees.Add(emp);

            dep.Employees.Remove(emp);
            Assert.IsFalse(dep.Employees.Contains(emp), "Employee was not removed from collection on department.");
            Assert.IsNull(emp.Department, "Department was not nulled on employee.");
        }

        /// <summary>
        /// 将雇员添加到他们目前所属的部门
        /// </summary>
        [TestMethod]
        public void AddEmployeeToSameDepartment()
        {
            Department dep = CreateObject<Department>(); 
            Employee emp = CreateObject<Employee>();
            dep.Employees.Add(emp);

            dep.Employees.Add(emp);
            Assert.IsTrue(dep.Employees.Contains(emp), "Employee is not in collection on department.");
            Assert.AreSame(dep, emp.Department, "Department is not set on employee.");
        }

        /// <summary>
        /// 为没有分配部门的雇员设置部门
        /// </summary>
        [TestMethod]
        public void SetDepartmentOnUnassignedEmployee()
        {
            Department dep = CreateObject<Department>(); 
            Employee emp = CreateObject<Employee>();

            emp.Department = dep;
            Assert.IsTrue(dep.Employees.Contains(emp), "Employee was not added to collection on department.");
            Assert.AreSame(dep, emp.Department, "Department was not set on employee.");
        }

        /// <summary>
        /// 为分配到其他部门的雇员设置部门
        /// </summary>
        [TestMethod]
        public void SetDepartmentOnAssignedEmployee()
        {
            Employee emp = CreateObject<Employee>();
            Department depOriginal = CreateObject<Department>();
            Department depNew = CreateObject<Department>();
            emp.Department = depOriginal;

            emp.Department = depNew;
            Assert.IsFalse(depOriginal.Employees.Contains(emp), "Employee was not removed from collection on old department.");
            Assert.IsTrue(depNew.Employees.Contains(emp), "Employee was not added to collection on CreateObject<department.");
            Assert.AreSame(depNew, emp.Department, "Department was not set on employee.");
        }

        /// <summary>
        /// 清除雇员的部门
        /// </summary>
        [TestMethod]
        public void NullDepartmentOnAssignedEmployee()
        {
            Department dep = CreateObject<Department>();
            Employee emp = CreateObject<Employee>();
            emp.Department = dep;

            emp.Department = null;
            Assert.IsFalse(dep.Employees.Contains(emp), "Employee was not removed from collection on department.");
            Assert.IsNull(emp.Department, "Department was not nulled on employee.");
        }

        /// <summary>
        /// 将雇员的 department 属性设置为同一部门
        /// </summary>
        [TestMethod]
        public void SetSameDepartmentOnEmployee()
        {
            Department dep = CreateObject<Department>();
            Employee emp = CreateObject<Employee>();
            emp.Department = dep;

            emp.Department = dep;
            Assert.IsTrue(dep.Employees.Contains(emp), "Employee is not in collection on department.");
            Assert.AreEqual(1, dep.Employees.Count, "Employee has been added again to collection on department.");
            Assert.AreSame(dep, emp.Department, "Department is not set on employee.");
        }

        /// <summary>
        /// 当 department 属性已经为 null 时，将其设置为 null
        /// </summary>
        [TestMethod]
        public void NullDepartmentOnUnassignedEmployee()
        {
            Employee emp = CreateObject<Employee>();

            emp.Department = null;
            Assert.IsNull(emp.Department, "Department is not null on employee.");
        }

        #endregion

        #region 经理 - 报告

        /// <summary>
        /// 将没有分配经理的雇员添加到新的经理报告集合
        /// </summary>
        [TestMethod]
        public void AddUnassignedEmployeeToManager()
        {
            Employee man = CreateObject<Employee>();
            Employee emp = CreateObject<Employee>();

            man.Reports.Add(emp);
            Assert.IsTrue(man.Reports.Contains(emp), "Employee was not added to collection on manager.");
            Assert.AreSame(man, emp.Manager, "Manager was not set on employee.");
        }

        /// <summary>
        /// 将已分配了经理的雇员添加到新的经理报告集合
        /// </summary>
        [TestMethod]
        public void AddAssignedEmployeeToManager()
        {
            Employee man = CreateObject<Employee>();
            Employee manOrig = CreateObject<Employee>();
            Employee emp = CreateObject<Employee>();
            manOrig.Reports.Add(emp);

            man.Reports.Add(emp);
            Assert.IsFalse(manOrig.Reports.Contains(emp), "Employee was not removed from collection on old manager.");
            Assert.IsTrue(man.Reports.Contains(emp), "Employee was not added to collection on manager.");
            Assert.AreSame(man, emp.Manager, "Manager was not set on employee.");
        }

        /// <summary>
        /// 将雇员从经理报告集合中移除
        /// </summary>
        [TestMethod]
        public void RemoveEmployeeFromManager()
        {
            Employee man = CreateObject<Employee>();
            Employee emp = CreateObject<Employee>();
            man.Reports.Add(emp);

            man.Reports.Remove(emp);
            Assert.IsFalse(man.Reports.Contains(emp), "Employee was not removed from collection on old manager.");
            Assert.IsNull(emp.Manager, "Manager was not nulled on employee.");
        }

        /// <summary>
        /// 将雇员添加到已为他们分配的经理
        /// </summary>
        [TestMethod]
        public void AddEmployeeToSameManager()
        {
            Employee man = CreateObject<Employee>();
            Employee emp = CreateObject<Employee>();
            man.Reports.Add(emp);

            man.Reports.Add(emp);
            Assert.IsTrue(man.Reports.Contains(emp), "Employee is not in collection on manager.");
            Assert.AreSame(man, emp.Manager, "Manager is not set on employee.");
        }

        /// <summary>
        /// 为没有分配经理的雇员设置经理
        /// </summary>
        [TestMethod]
        public void SetManagerOnUnassignedEmployee()
        {
            Employee man = CreateObject<Employee>();
            Employee emp = CreateObject<Employee>();

            emp.Manager = man;
            Assert.IsTrue(man.Reports.Contains(emp), "Employee was not added to collection on manager.");
            Assert.AreSame(man, emp.Manager, "Manager was not set on employee.");
        }

        /// <summary>
        /// 为分配到其他经理的雇员设置经理
        /// </summary>
        [TestMethod]
        public void SetManagerOnAssignedEmployee()
        {
            Employee man = CreateObject<Employee>();
            Employee manOrig = CreateObject<Employee>();
            Employee emp = CreateObject<Employee>();
            emp.Manager = manOrig;

            emp.Manager = man;
            Assert.IsFalse(manOrig.Reports.Contains(emp), "Employee was not removed from collection on old manager.");
            Assert.IsTrue(man.Reports.Contains(emp), "Employee was not added to collection on manager.");
            Assert.AreSame(man, emp.Manager, "Manager was not set on employee.");
        }

        /// <summary>
        /// 清除雇员的经理
        /// </summary>
        [TestMethod]
        public void NullManagerOnAssignedEmployee()
        {
            Employee man = CreateObject<Employee>();
            Employee emp = CreateObject<Employee>();
            emp.Manager = man;

            emp.Manager = null;
            Assert.IsFalse(man.Reports.Contains(emp), "Employee was not removed from collection on manager.");
            Assert.IsNull(emp.Manager, "Manager was not nulled on employee.");
        }

        /// <summary>
        /// 将雇员的 manager 属性设置为同一个经理
        /// </summary>
        [TestMethod]
        public void SetSameManagerOnEmployee()
        {
            Employee man = CreateObject<Employee>();
            Employee emp = CreateObject<Employee>();
            emp.Manager = man;

            emp.Manager = man;
            Assert.IsTrue(man.Reports.Contains(emp), "Employee is not in collection on manager.");
            Assert.AreEqual(1, man.Reports.Count, "Employee has been added again to collection on manager.");
            Assert.AreSame(man, emp.Manager, "Manager is not set on employee.");
        }

        /// <summary>
        /// 当 manager 属性已经为 null 时，将其设置为 null
        /// </summary>
        [TestMethod]
        public void NullManagerOnUnassignedEmployee()
        {
            Employee emp = CreateObject<Employee>();

            emp.Manager = null;
            Assert.IsNull(emp.Manager, "Manager is not null on employee.");
        }

        #endregion

        /// <summary>
        /// 为即将运行的测试创建类型为 T 的对象
        /// </summary>
        /// <typeparam name="T">要创建的对象的类型</typeparam>
        /// <returns>T 的实例或派生自 T 的类型</returns>
        protected abstract T CreateObject<T>() where T : class;
    }
}
