// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。


namespace EmployeeTracker.ViewModel
{
    using System;
    using System.Collections.ObjectModel;
    using System.Windows.Input;
    using EmployeeTracker.Common;
    using EmployeeTracker.Model;
    using EmployeeTracker.ViewModel.Helpers;

    /// <summary>
    /// 用于管理公司雇员的 ViewModel
    /// </summary>
    public class EmployeeWorkspaceViewModel : ViewModelBase
    {
        /// <summary>
        /// 当前在此工作区中选择的雇员
        /// </summary>
        private EmployeeViewModel currentEmployee;

        /// <summary>
        /// 用于管理更改的 UnitOfWork
        /// </summary>
        private IUnitOfWork unitOfWork;

        /// <summary>
        /// 要用于查找的部门
        /// </summary>
        private ObservableCollection<DepartmentViewModel> departmentLookup;

        /// <summary>
        /// 初始化 EmployeeWorkspaceViewModel 类的新实例。
        /// </summary>
        /// <param name="employees">要管理的雇员</param>
        /// <param name="departmentLookup">要用于查找的部门</param>
        /// <param name="unitOfWork">用于管理更改的 UnitOfWork</param>
        public EmployeeWorkspaceViewModel(ObservableCollection<EmployeeViewModel> employees, ObservableCollection<DepartmentViewModel> departmentLookup, IUnitOfWork unitOfWork)
        {
            if (employees == null)
            {
                throw new ArgumentNullException("employees");
            }

            if (departmentLookup == null)
            {
                throw new ArgumentNullException("departmentLookup");
            }

            if (unitOfWork == null)
            {
                throw new ArgumentNullException("unitOfWork");
            }

            this.unitOfWork = unitOfWork;
            this.AllEmployees = employees;
            this.departmentLookup = departmentLookup;
            this.CurrentEmployee = employees.Count > 0 ? employees[0] : null;

            // 响应从此 ViewModel 外部进行的任何更改
            this.AllEmployees.CollectionChanged += (sender, e) =>
            {
                if (e.OldItems != null && e.OldItems.Contains(this.CurrentEmployee))
                {
                    this.CurrentEmployee = null;
                }
            };

            this.AddEmployeeCommand = new DelegateCommand((o) => this.AddEmployee());
            this.DeleteEmployeeCommand = new DelegateCommand((o) => this.DeleteCurrentEmployee(), (o) => this.CurrentEmployee != null);
        }

        /// <summary>
        /// 获取添加新雇员的命令
        /// </summary>
        public ICommand AddEmployeeCommand { get; private set; }

        /// <summary>
        /// 获取删除当前雇员的命令
        /// </summary>
        public ICommand DeleteEmployeeCommand { get; private set; }

        /// <summary>
        /// 获取公司中的所有雇员
        /// </summary>
        public ObservableCollection<EmployeeViewModel> AllEmployees { get; private set; }

        /// <summary>
        /// 获取或设置当前在此工作区中选择的雇员
        /// </summary>
        public EmployeeViewModel CurrentEmployee
        {
            get
            {
                return this.currentEmployee;
            }

            set
            {
                this.currentEmployee = value;
                this.OnPropertyChanged("CurrentEmployee");
            }
        }

        /// <summary>
        /// 处理向工作区和模型添加新雇员的操作
        /// </summary>
        private void AddEmployee()
        {
            Employee emp = this.unitOfWork.CreateObject<Employee>();
            this.unitOfWork.AddEmployee(emp);

            EmployeeViewModel vm = new EmployeeViewModel(emp, this.AllEmployees, this.departmentLookup, this.unitOfWork);
            this.AllEmployees.Add(vm);
            this.CurrentEmployee = vm;
        }

        /// <summary>
        /// 处理删除当前雇员的操作
        /// </summary>
        private void DeleteCurrentEmployee()
        {
            this.unitOfWork.RemoveEmployee(this.CurrentEmployee.Model);
            this.AllEmployees.Remove(this.CurrentEmployee);
            this.CurrentEmployee = null;
        }
    }
}
