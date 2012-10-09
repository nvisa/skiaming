// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。


namespace EmployeeTracker.ViewModel
{
    using System;
    using System.Collections.ObjectModel;
    using System.Linq;
    using System.Windows.Input;
    using EmployeeTracker.Common;
    using EmployeeTracker.Model;
    using EmployeeTracker.ViewModel.Helpers;

    /// <summary>
    /// 单个 <see cref="Employee"/> 的 ViewModel
    /// </summary>
    public class EmployeeViewModel : BasicEmployeeViewModel
    {
        /// <summary>
        /// 当前为此雇员分配的部门
        /// </summary>
        private DepartmentViewModel department;

        /// <summary>
        /// 当前为此雇员分配的经理
        /// </summary>
        private EmployeeViewModel manager;

        /// <summary>
        /// 当前选择的联系人详细信息
        /// </summary>
        private ContactDetailViewModel currentContactDetail;

        /// <summary>
        /// 用于管理更改的 UnitOfWork
        /// </summary>
        private IUnitOfWork unitOfWork;

        /// <summary>
        /// 初始化 EmployeeViewModel 类的新实例。
        /// </summary>
        /// <param name="employee">此 ViewModel 基于的基础雇员</param>
        /// <param name="managerLookup">要用于查找经理的现有雇员集合</param>
        /// <param name="departmentLookup">要用于查找部门的现有部门集合</param>
        /// <param name="unitOfWork">用于管理更改的 UnitOfWork</param>
        public EmployeeViewModel(Employee employee, ObservableCollection<EmployeeViewModel> managerLookup, ObservableCollection<DepartmentViewModel> departmentLookup, IUnitOfWork unitOfWork)
            : base(employee)
        {
            if (employee == null)
            {
                throw new ArgumentNullException("employee");
            }

            this.unitOfWork = unitOfWork;
            this.ManagerLookup = managerLookup;
            this.DepartmentLookup = departmentLookup;

            // 生成联系人详细信息的数据结构
            this.ContactDetails = new ObservableCollection<ContactDetailViewModel>();
            foreach (var detail in employee.ContactDetails)
            {
                ContactDetailViewModel vm = ContactDetailViewModel.BuildViewModel(detail);
                if (vm != null)
                {
                    this.ContactDetails.Add(vm);
                }
            }

            // 响应从此 ViewModel 外部进行的任何更改
            this.DepartmentLookup.CollectionChanged += (sender, e) =>
            {
                if (e.OldItems != null && e.OldItems.Contains(this.Department))
                {
                    this.Department = null;
                }
            };
            this.ManagerLookup.CollectionChanged += (sender, e) =>
            {
                if (e.OldItems != null && e.OldItems.Contains(this.Manager))
                {
                    this.Manager = null;
                }
            };

            this.AddEmailAddressCommand = new DelegateCommand((o) => this.AddContactDetail<Email>());
            this.AddPhoneNumberCommand = new DelegateCommand((o) => this.AddContactDetail<Phone>());
            this.AddAddressCommand = new DelegateCommand((o) => this.AddContactDetail<Address>());
            this.DeleteContactDetailCommand = new DelegateCommand((o) => this.DeleteCurrentContactDetail(), (o) => this.CurrentContactDetail != null);
        }

        /// <summary>
        /// 获取添加新电子邮件地址的命令
        /// </summary>
        public ICommand AddEmailAddressCommand { get; private set; }

        /// <summary>
        /// 获取添加新电话号码的命令
        /// </summary>
        public ICommand AddPhoneNumberCommand { get; private set; }

        /// <summary>
        /// 获取添加新地址的命令
        /// </summary>
        public ICommand AddAddressCommand { get; private set; }

        /// <summary>
        /// 获取删除当前雇员的命令
        /// </summary>
        public ICommand DeleteContactDetailCommand { get; private set; }

        /// <summary>
        /// 获取或设置当前选择的联系人详细信息
        /// </summary>
        public ContactDetailViewModel CurrentContactDetail
        {
            get
            {
                return this.currentContactDetail;
            }

            set
            {
                this.currentContactDetail = value;
                this.OnPropertyChanged("CurrentContactDetail");
            }
        }
        
        /// <summary>
        /// 获取或设置当前分配给此雇员的部门
        /// </summary>
        public DepartmentViewModel Department
        {
            get
            {
                // 我们需要反映在模型中进行的任何更改，因而我们要在返回之前检查当前值
                if (this.Model.Department == null)
                {
                    return null;
                }
                else if (this.department == null || this.department.Model != this.Model.Department)
                {
                    this.department = this.DepartmentLookup.Where(d => d.Model == this.Model.Department).SingleOrDefault();
                }

                return this.department;
            }

            set
            {
                this.department = value;
                this.Model.Department = (value == null) ? null : value.Model;
                this.OnPropertyChanged("Department");
            }
        }

        /// <summary>
        /// 获取或设置当前为此雇员分配的经理
        /// </summary>
        public EmployeeViewModel Manager
        {
            get
            {
                // 我们需要反映在模型中进行的任何更改，因而我们要在返回之前检查当前值
                if (this.Model.Manager == null)
                {
                    return null;
                }
                else if (this.manager == null || this.manager.Model != this.Model.Manager)
                {
                    this.manager = this.ManagerLookup.Where(e => e.Model == this.Model.Manager).SingleOrDefault();
                }

                return this.manager;
            }

            set
            {
                this.manager = value;
                this.Model.Manager = (value == null) ? null : value.Model;
                this.OnPropertyChanged("Manager");
            }
        }

        /// <summary>
        /// 获取此雇员可以分配到的部门的集合
        /// </summary>
        public ObservableCollection<DepartmentViewModel> DepartmentLookup { get; private set; }

        /// <summary>
        /// 获取可以成为此雇员的经理的雇员集合
        /// </summary>
        public ObservableCollection<EmployeeViewModel> ManagerLookup { get; private set; }

        /// <summary>
        /// 获取为此雇员记录的联系人详细信息
        /// </summary>
        public ObservableCollection<ContactDetailViewModel> ContactDetails { get; private set; }

        /// <summary>
        /// 处理向此雇员添加新联系人详细信息的操作
        /// </summary>
        /// <typeparam name="T">要添加的联系人详细信息的类型</typeparam>
        private void AddContactDetail<T>() where T : ContactDetail
        {
            ContactDetail detail = this.unitOfWork.CreateObject<T>();
            this.unitOfWork.AddContactDetail(this.Model, detail);

            ContactDetailViewModel vm = ContactDetailViewModel.BuildViewModel(detail);
            this.ContactDetails.Add(vm);
            this.CurrentContactDetail = vm;
        }

        /// <summary>
        /// 处理删除当前雇员的操作
        /// </summary>
        private void DeleteCurrentContactDetail()
        {
            this.unitOfWork.RemoveContactDetail(this.Model, this.CurrentContactDetail.Model);
            this.ContactDetails.Remove(this.CurrentContactDetail);
            this.CurrentContactDetail = null;
        }
    }
}
