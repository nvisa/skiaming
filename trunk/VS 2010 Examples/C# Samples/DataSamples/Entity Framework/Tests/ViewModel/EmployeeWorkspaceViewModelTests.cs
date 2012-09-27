// 版权所有(C) Microsoft Corporation。保留所有权利。

namespace Tests.ViewModel
{
    using System.Collections.Generic;
    using System.Collections.ObjectModel;
    using System.Linq;
    using EmployeeTracker.Common;
    using EmployeeTracker.Fakes;
    using EmployeeTracker.Model;
    using EmployeeTracker.ViewModel;
    using Microsoft.VisualStudio.TestTools.UnitTesting;
    using Tests;

    /// <summary>
    /// EmployeeWorkspaceViewModel 的单元测试
    /// </summary>
    [TestClass]
    public class EmployeeWorkspaceViewModelTests
    {
        /// <summary>
        /// 验证在没有数据的情况下创建工作区
        /// </summary>
        [TestMethod]
        public void InitializeWithEmptyData()
        {
            using (FakeEmployeeContext ctx = new FakeEmployeeContext())
            {
                UnitOfWork unit = new UnitOfWork(ctx);
                ObservableCollection<DepartmentViewModel> departments = new ObservableCollection<DepartmentViewModel>();
                ObservableCollection<EmployeeViewModel> employees = new ObservableCollection<EmployeeViewModel>();
                EmployeeWorkspaceViewModel vm = new EmployeeWorkspaceViewModel(employees, departments, unit);

                Assert.AreSame(employees, vm.AllEmployees, "ViewModel should expose the same instance of the collection so that changes outside the ViewModel are reflected.");
                Assert.IsNull(vm.CurrentEmployee, "Current employee should not be set if there are no department.");
                Assert.IsNotNull(vm.AddEmployeeCommand, "AddEmployeeCommand should be initialized");
                Assert.IsNotNull(vm.DeleteEmployeeCommand, "DeleteEmployeeCommand should be initialized");
            }
        }

        /// <summary>
        /// 验证在存在数据的情况下创建工作区
        /// </summary>
        [TestMethod]
        public void InitializeWithData()
        {
            Employee e1 = new Employee();
            Employee e2 = new Employee();

            Department d1 = new Department();
            Department d2 = new Department();

            using (FakeEmployeeContext ctx = new FakeEmployeeContext(new Employee[] { e1, e2 }, new Department[] { d1, d2 }))
            {
                UnitOfWork unit = new UnitOfWork(ctx);
                ObservableCollection<DepartmentViewModel> departments = new ObservableCollection<DepartmentViewModel>(ctx.Departments.Select(d => new DepartmentViewModel(d)));
                ObservableCollection<EmployeeViewModel> employees = new ObservableCollection<EmployeeViewModel>();
                foreach (var e in ctx.Employees)
                {
                    employees.Add(new EmployeeViewModel(e, employees, departments, unit));
                }

                EmployeeWorkspaceViewModel vm = new EmployeeWorkspaceViewModel(employees, departments, unit);

                Assert.IsNotNull(vm.CurrentEmployee, "Current employee should be set if there are departments.");
                Assert.AreSame(employees, vm.AllEmployees, "ViewModel should expose the same instance of the Employee collection so that changes outside the ViewModel are reflected.");
                Assert.AreSame(employees, vm.AllEmployees[0].ManagerLookup, "ViewModel should expose the same instance of the Employee collection to children so that changes outside the ViewModel are reflected.");
                Assert.AreSame(departments, vm.AllEmployees[0].DepartmentLookup, "ViewModel should expose the same instance of the Department collection to children so that changes outside the ViewModel are reflected.");
            }
        }

        /// <summary>
        /// 验证在 null 无效时，是否引发 NullArgumentExceptions
        /// </summary>
        [TestMethod]
        public void NullArgumentChecks()
        {
            using (FakeEmployeeContext ctx = new FakeEmployeeContext())
            {
                UnitOfWork unit = new UnitOfWork(ctx);

                Utilities.CheckNullArgumentException(() => { new EmployeeWorkspaceViewModel(null, new ObservableCollection<DepartmentViewModel>(), unit); }, "employees", "ctor");
                Utilities.CheckNullArgumentException(() => { new EmployeeWorkspaceViewModel(new ObservableCollection<EmployeeViewModel>(), null, unit); }, "departmentLookup", "ctor");
                Utilities.CheckNullArgumentException(() => { new EmployeeWorkspaceViewModel(new ObservableCollection<EmployeeViewModel>(), new ObservableCollection<DepartmentViewModel>(), null); }, "unitOfWork", "ctor");
            }
        }

        /// <summary>
        /// 验证当前雇员 getter 和 setter
        /// </summary>
        [TestMethod]
        public void CurrentEmployee()
        {
            using (FakeEmployeeContext ctx = BuildContextWithData())
            {
                EmployeeWorkspaceViewModel vm = BuildViewModel(ctx);

                string lastProperty;
                vm.PropertyChanged += (sender, e) => { lastProperty = e.PropertyName; };

                lastProperty = null;
                vm.CurrentEmployee = null;
                Assert.IsNull(vm.CurrentEmployee, "CurrentEmployee should have been nulled.");
                Assert.AreEqual("CurrentEmployee", lastProperty, "CurrentEmployee should have raised a PropertyChanged when set to null.");

                lastProperty = null;
                var employee = vm.AllEmployees.First();
                vm.CurrentEmployee = employee;
                Assert.AreSame(employee, vm.CurrentEmployee, "CurrentEmployee has not been set to specified value.");
                Assert.AreEqual("CurrentEmployee", lastProperty, "CurrentEmployee should have raised a PropertyChanged when set to a value.");
            }
        }

        /// <summary>
        /// 验证是否已反映对雇员集合的添加操作
        /// </summary>
        [TestMethod]
        public void ExternalAddToEmployeeCollection()
        {
            using (FakeEmployeeContext ctx = BuildContextWithData())
            {
                UnitOfWork unit = new UnitOfWork(ctx);
                EmployeeWorkspaceViewModel vm = BuildViewModel(ctx, unit);

                EmployeeViewModel currentEmployee = vm.CurrentEmployee;
                EmployeeViewModel newEmployee = new EmployeeViewModel(new Employee(), vm.AllEmployees, new ObservableCollection<DepartmentViewModel>(), unit);

                vm.AllEmployees.Add(newEmployee);
                Assert.IsTrue(vm.AllEmployees.Contains(newEmployee), "New employee should have been added to AllEmployees.");
                Assert.AreSame(currentEmployee, vm.CurrentEmployee, "CurrentEmployee should not have changed.");
                Assert.IsFalse(ctx.IsObjectTracked(newEmployee.Model), "ViewModel is not responsible for adding employees created externally.");
            }
        }

        /// <summary>
        /// 验证是否已反映对雇员集合的移除操作
        /// 在当前雇员保留在集合中时
        /// </summary>
        [TestMethod]
        public void ExternalRemoveFromEmployeeCollection()
        {
            using (FakeEmployeeContext ctx = BuildContextWithData())
            {
                UnitOfWork unit = new UnitOfWork(ctx);
                EmployeeWorkspaceViewModel vm = BuildViewModel(ctx, unit);

                EmployeeViewModel current = vm.AllEmployees.First();
                EmployeeViewModel toDelete = vm.AllEmployees.Skip(1).First();
                vm.CurrentEmployee = current;

                vm.AllEmployees.Remove(toDelete);
                Assert.IsFalse(vm.AllEmployees.Contains(toDelete), "Employee should have been removed from AllDepartments.");
                Assert.AreSame(current, vm.CurrentEmployee, "CurrentEmployee should not have changed.");
                Assert.IsTrue(ctx.IsObjectTracked(toDelete.Model), "ViewModel is not responsible for deleting employees removed externally.");
            }
        }

        /// <summary>
        /// 验证是否已反映对雇员集合的移除操作
        /// 在当前雇员被移除时
        /// </summary>
        [TestMethod]
        public void ExternalRemoveSelectedEmployeeFromCollection()
        {
            using (FakeEmployeeContext ctx = BuildContextWithData())
            {
                UnitOfWork unit = new UnitOfWork(ctx);
                EmployeeWorkspaceViewModel vm = BuildViewModel(ctx, unit);
                EmployeeViewModel current = vm.CurrentEmployee;

                string lastProperty = null;
                vm.PropertyChanged += (sender, e) => { lastProperty = e.PropertyName; };

                vm.AllEmployees.Remove(current);
                Assert.IsFalse(vm.AllEmployees.Contains(current), "Employee should have been removed from AllEmployees.");
                Assert.IsNull(vm.CurrentEmployee, "CurrentEmployee should have been nulled as it was removed from the collection.");
                Assert.AreEqual("CurrentEmployee", lastProperty, "CurrentEmployee should have raised a PropertyChanged.");
                Assert.IsTrue(ctx.IsObjectTracked(current.Model), "ViewModel is not responsible for deleting employees removed externally.");
            }
        }

        /// <summary>
        /// 验证是否仅在选中雇员时才能使用部门删除命令
        /// </summary>
        [TestMethod]
        public void DeleteCommandOnlyAvailableWhenEmployeeSelected()
        {
            using (FakeEmployeeContext ctx = BuildContextWithData())
            {
                EmployeeWorkspaceViewModel vm = BuildViewModel(ctx);

                vm.CurrentEmployee = null;
                Assert.IsFalse(vm.DeleteEmployeeCommand.CanExecute(null), "Delete command should be disabled when no employee is selected.");

                vm.CurrentEmployee = vm.AllEmployees.First();
                Assert.IsTrue(vm.DeleteEmployeeCommand.CanExecute(null), "Delete command should be enabled when employee is selected.");
            }
        }

        /// <summary>
        /// 验证雇员是否可以删除
        /// </summary>
        [TestMethod]
        public void DeleteEmployee()
        {
            using (FakeEmployeeContext ctx = BuildContextWithData())
            {
                EmployeeWorkspaceViewModel vm = BuildViewModel(ctx);

                EmployeeViewModel toDelete = vm.CurrentEmployee;
                int originalCount = vm.AllEmployees.Count;

                string lastProperty = null;
                vm.PropertyChanged += (sender, e) => { lastProperty = e.PropertyName; };

                vm.DeleteEmployeeCommand.Execute(null);

                Assert.AreEqual(originalCount - 1, vm.AllEmployees.Count, "One employee should have been removed from the AllEmployees property.");
                Assert.IsFalse(vm.AllEmployees.Contains(toDelete), "The selected employee should have been removed.");
                Assert.IsFalse(ctx.IsObjectTracked(toDelete.Model), "The selected employee has not been removed from the context.");
                Assert.IsNull(vm.CurrentEmployee, "No employee should be selected after deletion.");
                Assert.AreEqual("CurrentEmployee", lastProperty, "CurrentEmployee should have raised a PropertyChanged.");
            }
        }

        /// <summary>
        /// 验证是否可在选中一个雇员时添加新雇员
        /// </summary>
        [TestMethod]
        public void AddWhenEmployeeSelected()
        {
            using (FakeEmployeeContext ctx = BuildContextWithData())
            {
                EmployeeWorkspaceViewModel vm = BuildViewModel(ctx);

                vm.CurrentEmployee = vm.AllEmployees.First();
                TestAddEmployee(ctx, vm);
            }
        }

        /// <summary>
        /// 验证是否可在未选中任何雇员时添加新雇员
        /// </summary>
        [TestMethod]
        public void AddWhenEmployeeNotSelected()
        {
            using (FakeEmployeeContext ctx = BuildContextWithData())
            {
                EmployeeWorkspaceViewModel vm = BuildViewModel(ctx);

                vm.CurrentEmployee = null;
                TestAddEmployee(ctx, vm);
            }
        }

        /// <summary>
        /// 验证向工作区和工作单元添加雇员的操作
        /// </summary>
        /// <param name="unitOfWork">应将雇员添加到的上下文</param>
        /// <param name="vm">要将雇员添加到的工作区</param>
        private static void TestAddEmployee(FakeEmployeeContext ctx, EmployeeWorkspaceViewModel vm)
        {
            List<EmployeeViewModel> originalEmployees = vm.AllEmployees.ToList();

            string lastProperty = null;
            vm.PropertyChanged += (sender, e) => { lastProperty = e.PropertyName; };

            Assert.IsTrue(vm.AddEmployeeCommand.CanExecute(null), "Add command should always be enabled.");
            vm.AddEmployeeCommand.Execute(null);

            Assert.AreEqual(originalEmployees.Count + 1, vm.AllEmployees.Count, "One new employee should have been added to the AllEmployees property.");
            Assert.IsFalse(originalEmployees.Contains(vm.CurrentEmployee), "The new employee should be selected.");
            Assert.IsNotNull(vm.CurrentEmployee, "The new employee should be selected.");
            Assert.AreEqual("CurrentEmployee", lastProperty, "CurrentEmployee should have raised a PropertyChanged.");
            Assert.IsTrue(ctx.IsObjectTracked(vm.CurrentEmployee.Model), "The new employee has not been added to the context.");
        }

        /// <summary>
        /// 创建一个包含种子数据的虚设上下文
        /// </summary>
        /// <returns>虚设上下文</returns>
        private static FakeEmployeeContext BuildContextWithData()
        {
            Employee e1 = new Employee();
            Employee e2 = new Employee();

            Department d1 = new Department();
            Department d2 = new Department();

            return new FakeEmployeeContext(new Employee[] { e1, e2 }, new Department[] { d1, d2 });
        }

        /// <summary>
        /// 创建基于虚设上下文的 ViewModel
        /// </summary>
        /// <param name="ctx">视图模型基于的上下文</param>
        /// <returns>新的 ViewModel</returns>
        private static EmployeeWorkspaceViewModel BuildViewModel(FakeEmployeeContext ctx)
        {
            return BuildViewModel(ctx, new UnitOfWork(ctx));
        }

        /// <summary>
        /// 使用现有工作单元创建基于虚设上下文的 ViewModel
        /// </summary>
        /// <param name="ctx">视图模型基于的上下文</param>
        /// <param name="unit">当前工作单元</param>
        /// <returns>新的 ViewModel</returns>
        private static EmployeeWorkspaceViewModel BuildViewModel(FakeEmployeeContext ctx, UnitOfWork unit)
        {
            ObservableCollection<DepartmentViewModel> departments = new ObservableCollection<DepartmentViewModel>(ctx.Departments.Select(d => new DepartmentViewModel(d)));
            ObservableCollection<EmployeeViewModel> employees = new ObservableCollection<EmployeeViewModel>();
            foreach (var e in ctx.Employees)
            {
                employees.Add(new EmployeeViewModel(e, employees, departments, unit));
            }

            return new EmployeeWorkspaceViewModel(employees, departments, unit);
        }
    }
}
