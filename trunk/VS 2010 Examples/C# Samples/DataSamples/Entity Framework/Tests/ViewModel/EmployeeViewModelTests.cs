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

    /// <summary>
    /// EmployeeViewModel 的单元测试
    /// </summary>
    [TestClass]
    public class EmployeeViewModelTests
    {
        /// <summary>
        /// 验证 ViewModel 上的 getter 和 setter 是否影响基础数据和通知更改
        /// </summary>
        [TestMethod]
        public void Initialization()
        {
            using (FakeEmployeeContext ctx = BuildContextWithData())
            {
                EmployeeViewModel vm = BuildViewModel(ctx);

                Assert.IsNotNull(vm.ManagerLookup, "Manager lookup should be initialized.");
                Assert.IsTrue(vm.ManagerLookup.Contains(vm), "ViewModel must be capable of containing itself in the manager lookup.");

                Assert.IsNotNull(vm.DepartmentLookup, "Department lookup should be initialized.");
                Assert.IsNotNull(vm.AddAddressCommand, "AddAddressCommand should be initialized.");
                Assert.IsNotNull(vm.AddEmailAddressCommand, "AddEmailAddressCommand should be initialized.");
                Assert.IsNotNull(vm.AddPhoneNumberCommand, "AddPhoneNumberCommand should be initialized.");
                Assert.IsNotNull(vm.DeleteContactDetailCommand, "DeleteContactDetailCommand should be initialized.");
            }
        }

        /// <summary>
        /// 验证 getter 是否反映模型中的更改
        /// </summary>
        [TestMethod]
        public void ReferencesGetAndSet()
        {
            // Scalar 属性继承自 BasicEmployeeViewModel 并且已经测试
            Department d1 = new Department();
            Department d2 = new Department();

            Employee e1 = new Employee();
            Employee e2 = new Employee();
            Employee employee = new Employee { Department = d1, Manager = e1 };
            employee.ContactDetails.Add(new Phone());
            employee.ContactDetails.Add(new Email());

            using (FakeEmployeeContext ctx = new FakeEmployeeContext(new Employee[] { e1, e2, employee }, new Department[] { d1, d2 }))
            {
                UnitOfWork unit = new UnitOfWork(ctx);

                DepartmentViewModel dvm1 = new DepartmentViewModel(d1);
                DepartmentViewModel dvm2 = new DepartmentViewModel(d2);
                ObservableCollection<DepartmentViewModel> departments = new ObservableCollection<DepartmentViewModel> { dvm1, dvm2 };

                ObservableCollection<EmployeeViewModel> employees = new ObservableCollection<EmployeeViewModel>();
                EmployeeViewModel evm1 = new EmployeeViewModel(e1, employees, departments, unit);
                EmployeeViewModel evm2 = new EmployeeViewModel(e2, employees, departments, unit);
                EmployeeViewModel employeeViewModel = new EmployeeViewModel(employee, employees, departments, unit);
                employees.Add(evm1);
                employees.Add(evm2);
                employees.Add(employeeViewModel);

                // 测试初始引用显示在 ViewModel 中
                Assert.AreEqual(evm1, employeeViewModel.Manager, "ViewModel did not return ViewModel representing current manager.");
                Assert.AreEqual(e1, employeeViewModel.Manager.Model, "ViewModel did not return ViewModel representing current manager.");
                Assert.AreEqual(dvm1, employeeViewModel.Department, "ViewModel did not return ViewModel representing current department.");
                Assert.AreEqual(d1, employeeViewModel.Department.Model, "ViewModel did not return ViewModel representing current department.");
                Assert.AreEqual(2, employeeViewModel.ContactDetails.Count, "Contact details have not been populated on ViewModel.");

                // 更改属性的测试将更新模型并引发 PropertyChanged
                string lastProperty;
                employeeViewModel.PropertyChanged += (sender, e) => { lastProperty = e.PropertyName; };

                lastProperty = null;
                employeeViewModel.Department = dvm2;
                Assert.AreEqual("Department", lastProperty, "Setting Department property did not raise correct PropertyChanged event.");
                Assert.AreEqual(d2, employee.Department, "Setting Department property in ViewModel is not reflected in Model.");

                lastProperty = null;
                employeeViewModel.Manager = evm2;
                Assert.AreEqual("Manager", lastProperty, "Setting Manager property did not raise correct PropertyChanged event.");
                Assert.AreEqual(e2, employee.Manager, "Setting Manager property in ViewModel is not reflected in Model.");

                // 测试 ViewModel 返回模型的当前值
                employee.Manager = e1;
                Assert.AreEqual(evm1, employeeViewModel.Manager, "ViewModel did not return correct manager when model was updated outside of ViewModel.");
                employee.Department = d1;
                Assert.AreEqual(dvm1, employeeViewModel.Department, "ViewModel did not return correct department when model was updated outside of ViewModel.");

                // 当设置为 null 时，测试 ViewModel 返回模型的当前值
                employee.Manager = null;
                Assert.AreEqual(null, employeeViewModel.Manager, "ViewModel did not return correct manager when model was updated outside of ViewModel.");
                employee.Department = null;
                Assert.AreEqual(null, employeeViewModel.Department, "ViewModel did not return correct department when model was updated outside of ViewModel.");
            }
        }

        /// <summary>
        /// 验证是否可以添加新的电子邮件地址
        /// </summary>
        [TestMethod]
        public void AddEmail()
        {
            using (FakeEmployeeContext ctx = BuildContextWithData())
            {
                EmployeeViewModel vm = BuildViewModel(ctx);
                List<ContactDetailViewModel> originalDetails = vm.ContactDetails.ToList();

                Assert.IsTrue(vm.AddEmailAddressCommand.CanExecute(null), "AddEmailAddressCommand should always be enabled.");
                vm.AddEmailAddressCommand.Execute(null);

                Assert.IsNotNull(vm.CurrentContactDetail, "New email should be selected.");
                Assert.IsFalse(originalDetails.Contains(vm.CurrentContactDetail), "New email should be selected.");
                Assert.IsInstanceOfType(vm.CurrentContactDetail, typeof(EmailViewModel), "New contact should be an email.");
                Assert.IsTrue(ctx.IsObjectTracked(vm.CurrentContactDetail.Model), "New email should have been added to context.");
                Assert.AreEqual(originalDetails.Count + 1, vm.ContactDetails.Count, "New email should have been added to AllContactDetails property.");
            }
        }

        /// <summary>
        /// 验证是否可以添加新的电话号码
        /// </summary>
        [TestMethod]
        public void AddPhone()
        {
            using (FakeEmployeeContext ctx = BuildContextWithData())
            {
                EmployeeViewModel vm = BuildViewModel(ctx);
                List<ContactDetailViewModel> originalDetails = vm.ContactDetails.ToList();

                Assert.IsTrue(vm.AddPhoneNumberCommand.CanExecute(null), "AddPhoneNumberCommand should always be enabled.");
                vm.AddPhoneNumberCommand.Execute(null);

                Assert.IsNotNull(vm.CurrentContactDetail, "New phone should be selected.");
                Assert.IsFalse(originalDetails.Contains(vm.CurrentContactDetail), "New phone should be selected.");
                Assert.IsInstanceOfType(vm.CurrentContactDetail, typeof(PhoneViewModel), "New contact should be a phone.");
                Assert.IsTrue(ctx.IsObjectTracked(vm.CurrentContactDetail.Model), "New phone should have been added to context.");
                Assert.AreEqual(originalDetails.Count + 1, vm.ContactDetails.Count, "New phone should have been added to AllContactDetails property.");
            }
        }

        /// <summary>
        /// 验证是否可以添加新的地址
        /// </summary>
        [TestMethod]
        public void AddAddress()
        {
            using (FakeEmployeeContext ctx = BuildContextWithData())
            {
                EmployeeViewModel vm = BuildViewModel(ctx);
                List<ContactDetailViewModel> originalDetails = vm.ContactDetails.ToList();

                Assert.IsTrue(vm.AddAddressCommand.CanExecute(null), "AddAddressCommand should always be enabled.");
                vm.AddAddressCommand.Execute(null);

                Assert.IsNotNull(vm.CurrentContactDetail, "New address should be selected.");
                Assert.IsFalse(originalDetails.Contains(vm.CurrentContactDetail), "New address should be selected.");
                Assert.IsInstanceOfType(vm.CurrentContactDetail, typeof(AddressViewModel), "New contact should be an address.");
                Assert.IsTrue(ctx.IsObjectTracked(vm.CurrentContactDetail.Model), "New address should have been added to context.");
                Assert.AreEqual(originalDetails.Count + 1, vm.ContactDetails.Count, "New address should have been added to AllContactDetails property.");
            }
        }

        /// <summary>
        /// 验证是否仅在选中联系人时才能进行删除
        /// </summary>
        [TestMethod]
        public void DeleteContactDetailOnlyAvailableWhenDetailIsSelected()
        {
            using (FakeEmployeeContext ctx = BuildContextWithData())
            {
                EmployeeViewModel vm = BuildViewModel(ctx);
                List<ContactDetailViewModel> originalDetails = vm.ContactDetails.ToList();


                vm.CurrentContactDetail = null;
                Assert.IsFalse(vm.DeleteContactDetailCommand.CanExecute(null), "DeleteContactDetailCommand should be disabled when no detail is selected.");

                vm.CurrentContactDetail = vm.ContactDetails.First();
                Assert.IsTrue(vm.DeleteContactDetailCommand.CanExecute(null), "DeleteContactDetailCommand should be enabled when a detail is selected.");
            }
        }

        /// <summary>
        /// 验证是否可以删除联系人详细信息
        /// </summary>
        [TestMethod]
        public void DeleteContactDetail()
        {
            using (FakeEmployeeContext ctx = BuildContextWithData())
            {
                EmployeeViewModel vm = BuildViewModel(ctx);
                List<ContactDetailViewModel> originalDetails = vm.ContactDetails.ToList();


                ContactDetailViewModel toDelete = vm.ContactDetails.First();
                vm.CurrentContactDetail = toDelete;
                vm.DeleteContactDetailCommand.Execute(null);

                Assert.IsNull(vm.CurrentContactDetail, "No detail should be selected after deleting.");
                Assert.IsFalse(vm.ContactDetails.Contains(toDelete), "Detail should be removed from ContactDetails property.");
                Assert.IsFalse(ctx.IsObjectTracked(toDelete), "Detail should be deleted from context.");
            }
        }

        /// <summary>
        /// 验证是否已反映对部门集合的添加操作
        /// </summary>
        [TestMethod]
        public void ExternalAddToDepartmentLookup()
        {
            using (FakeEmployeeContext ctx = BuildContextWithData())
            {
                EmployeeViewModel vm = BuildViewModel(ctx);

                DepartmentViewModel currentDepartment = vm.Department;
                DepartmentViewModel newDepartment = new DepartmentViewModel(new Department());

                vm.DepartmentLookup.Add(newDepartment);
                Assert.IsTrue(vm.DepartmentLookup.Contains(newDepartment), "New department should have been added to DepartmentLookup.");
                Assert.AreSame(currentDepartment, vm.Department, "Assigned Department should not have changed.");
                Assert.IsFalse(ctx.IsObjectTracked(newDepartment.Model), "ViewModel is not responsible for adding departments created externally.");
            }
        }

        /// <summary>
        /// 在当前部门保留在集合中时，
        /// 验证是否已反映对部门集合的移除操作
        /// </summary>
        [TestMethod]
        public void ExternalRemoveDepartmentLookup()
        {
            using (FakeEmployeeContext ctx = BuildContextWithData())
            {
                EmployeeViewModel vm = BuildViewModel(ctx);

                DepartmentViewModel currentDepartment = vm.DepartmentLookup.First();
                DepartmentViewModel toDelete = vm.DepartmentLookup.Skip(1).First();
                vm.Department = currentDepartment;

                vm.DepartmentLookup.Remove(toDelete);
                Assert.IsFalse(vm.DepartmentLookup.Contains(toDelete), "Department should have been removed from DepartmentLookup.");
                Assert.AreSame(currentDepartment, vm.Department, "Assigned Department should not have changed.");
                Assert.IsTrue(ctx.IsObjectTracked(toDelete.Model), "ViewModel is not responsible for deleting departments removed externally.");
            }
        }

        /// <summary>
        /// 验证是否已反映对部门集合的移除操作
        /// 在当前部门被移除时
        /// </summary>
        [TestMethod]
        public void ExternalRemoveDepartmentLookupSelectedDepartment()
        {
            using (FakeEmployeeContext ctx = BuildContextWithData())
            {
                EmployeeViewModel vm = BuildViewModel(ctx);

                DepartmentViewModel currentDepartment = vm.Department;

                string lastProperty = null;
                vm.PropertyChanged += (sender, e) => { lastProperty = e.PropertyName; };

                vm.DepartmentLookup.Remove(currentDepartment);
                Assert.IsFalse(vm.DepartmentLookup.Contains(currentDepartment), "Department should have been removed from DepartmentLookup.");
                Assert.IsNull(vm.Department, "Assigned Department should have been nulled as it was removed from the collection.");
                Assert.AreEqual("Department", lastProperty, "Department should have raised a PropertyChanged.");
                Assert.IsTrue(ctx.IsObjectTracked(currentDepartment.Model), "ViewModel is not responsible for deleting departments removed externally.");
            }
        }

        /// <summary>
        /// 验证是否已反映对雇员集合的添加操作
        /// </summary>
        [TestMethod]
        public void ExternalAddToManagerLookup()
        {
            using (FakeEmployeeContext ctx = BuildContextWithData())
            {
                UnitOfWork unit = new UnitOfWork(ctx);
                EmployeeViewModel vm = BuildViewModel(ctx, unit);

                EmployeeViewModel currentManager = vm.Manager;
                EmployeeViewModel newManager = new EmployeeViewModel(new Employee(), vm.ManagerLookup, vm.DepartmentLookup, unit);

                vm.ManagerLookup.Add(newManager);
                Assert.IsTrue(vm.ManagerLookup.Contains(newManager), "New department should have been added to ManagerLookup.");
                Assert.AreSame(currentManager, vm.Manager, "Assigned Manager should not have changed.");
                Assert.IsFalse(ctx.IsObjectTracked(newManager.Model), "ViewModel is not responsible for adding Employees created externally.");
            }
        }

        /// <summary>
        /// 验证是否已反映对雇员集合的移除操作
        /// 在当前经理保留在集合中时
        /// </summary>
        [TestMethod]
        public void ExternalRemoveManagerLookup()
        {
            using (FakeEmployeeContext ctx = BuildContextWithData())
            {
                EmployeeViewModel vm = BuildViewModel(ctx);

                EmployeeViewModel currentManager = vm.ManagerLookup.First();
                EmployeeViewModel toDelete = vm.ManagerLookup.Skip(1).First();
                vm.Manager = currentManager;

                vm.ManagerLookup.Remove(toDelete);
                Assert.IsFalse(vm.ManagerLookup.Contains(toDelete), "Employee should have been removed from ManagerLookup.");
                Assert.AreSame(currentManager, vm.Manager, "Assigned Manager should not have changed.");
                Assert.IsTrue(ctx.IsObjectTracked(toDelete.Model), "ViewModel is not responsible for deleting Employees removed externally.");
            }
        }

        /// <summary>
        /// 验证是否已反映对雇员集合的移除操作
        /// 在当前经理被移除时
        /// </summary>
        [TestMethod]
        public void ExternalRemoveManagerLookupSelectedManager()
        {
            using (FakeEmployeeContext ctx = BuildContextWithData())
            {
                EmployeeViewModel vm = BuildViewModel(ctx);

                EmployeeViewModel currentManager = vm.Manager;

                string lastProperty = null;
                vm.PropertyChanged += (sender, e) => { lastProperty = e.PropertyName; };

                vm.ManagerLookup.Remove(currentManager);
                Assert.IsFalse(vm.ManagerLookup.Contains(currentManager), "Employee should have been removed from ManagerLookup.");
                Assert.IsNull(vm.Manager, "Assigned Manager should have been nulled as it was removed from the collection.");
                Assert.AreEqual("Manager", lastProperty, "Manager should have raised a PropertyChanged.");
                Assert.IsTrue(ctx.IsObjectTracked(currentManager.Model), "ViewModel is not responsible for deleting Employees removed externally.");
            }
        }

        /// <summary>
        /// 创建一个包含种子数据的虚设上下文
        /// </summary>
        /// <returns>虚设上下文</returns>
        private static FakeEmployeeContext BuildContextWithData()
        {
            Department d1 = new Department();
            Department d2 = new Department();

            Employee e1 = new Employee { Department = d1 };
            Employee e2 = new Employee { Department = d1 };

            e1.Manager = e2;

            e1.ContactDetails.Add(new Phone());
            e1.ContactDetails.Add(new Email());
            e1.ContactDetails.Add(new Address());
            e2.ContactDetails.Add(new Phone());

            return new FakeEmployeeContext(new Employee[] { e1, e2 }, new Department[] { d1, d2 });
        }

        /// <summary>
        /// 创建基于虚设上下文的 ViewModel
        /// </summary>
        /// <param name="ctx">视图模型基于的上下文</param>
        /// <returns>新的 ViewModel</returns>
        private static EmployeeViewModel BuildViewModel(FakeEmployeeContext ctx)
        {
            return BuildViewModel(ctx, new UnitOfWork(ctx));
        }

        /// <summary>
        /// 使用现有工作单元创建基于虚设上下文的 ViewModel
        /// </summary>
        /// <param name="ctx">视图模型基于的上下文</param>
        /// <param name="unit">当前工作单元</param>
        /// <returns>新的 ViewModel</returns>
        private static EmployeeViewModel BuildViewModel(FakeEmployeeContext ctx, UnitOfWork unit)
        {
            ObservableCollection<DepartmentViewModel> departments = new ObservableCollection<DepartmentViewModel>(ctx.Departments.Select(d => new DepartmentViewModel(d)));
            ObservableCollection<EmployeeViewModel> employees = new ObservableCollection<EmployeeViewModel>();
            foreach (var e in ctx.Employees)
            {
                employees.Add(new EmployeeViewModel(e, employees, departments, unit));
            }

            return employees[0];
        }
    }
}
