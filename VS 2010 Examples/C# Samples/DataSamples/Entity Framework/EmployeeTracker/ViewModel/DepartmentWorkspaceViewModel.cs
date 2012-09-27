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
    /// 用于管理公司部门的 ViewModel
    /// </summary>
    public class DepartmentWorkspaceViewModel : ViewModelBase
    {
        /// <summary>
        /// 当前在工作区中选择的部门
        /// </summary>
        private DepartmentViewModel currentDepartment;

        /// <summary>
        /// 用于管理更改的 UnitOfWork
        /// </summary>
        private IUnitOfWork unitOfWork;

        /// <summary>
        /// 初始化 DepartmentWorkspaceViewModel 类的新实例。
        /// </summary>
        /// <param name="departments">要管理的部门</param>
        /// <param name="unitOfWork">用于管理更改的 UnitOfWork</param>
        public DepartmentWorkspaceViewModel(ObservableCollection<DepartmentViewModel> departments, IUnitOfWork unitOfWork)
        {
            if (departments == null)
            {
                throw new ArgumentNullException("departments");
            }

            if (unitOfWork == null)
            {
                throw new ArgumentNullException("unitOfWork");
            }

            this.unitOfWork = unitOfWork;
            this.AllDepartments = departments;
            this.CurrentDepartment = this.AllDepartments.Count > 0 ? this.AllDepartments[0] : null;

            // 响应从此 ViewModel 外部进行的任何更改
            this.AllDepartments.CollectionChanged += (sender, e) =>
            {
                if (e.OldItems != null && e.OldItems.Contains(this.CurrentDepartment))
                {
                    this.CurrentDepartment = null;
                }
            };

            this.AddDepartmentCommand = new DelegateCommand((o) => this.AddDepartment());
            this.DeleteDepartmentCommand = new DelegateCommand((o) => this.DeleteCurrentDepartment(), (o) => this.CurrentDepartment != null);
        }

        /// <summary>
        /// 获取添加新部门的命令
        /// </summary>
        public ICommand AddDepartmentCommand { get; private set; }

        /// <summary>
        /// 获取删除当前部门的命令
        /// </summary>
        public ICommand DeleteDepartmentCommand { get; private set; }

        /// <summary>
        /// 获取公司中的所有部门
        /// </summary>
        public ObservableCollection<DepartmentViewModel> AllDepartments { get; private set; }

        /// <summary>
        /// 获取或设置当前在工作区中选择的部门
        /// </summary>
        public DepartmentViewModel CurrentDepartment
        {
            get
            {
                return this.currentDepartment;
            }

            set
            {
                this.currentDepartment = value;
                this.OnPropertyChanged("CurrentDepartment");
            }
        }

        /// <summary>
        /// 处理向工作区和模型添加新部门的操作
        /// </summary>
        private void AddDepartment()
        {
            Department dep = this.unitOfWork.CreateObject<Department>();
            this.unitOfWork.AddDepartment(dep);

            DepartmentViewModel vm = new DepartmentViewModel(dep);
            this.AllDepartments.Add(vm);
            this.CurrentDepartment = vm;
        }

        /// <summary>
        /// 处理删除当前部门的操作
        /// </summary>
        private void DeleteCurrentDepartment()
        {
            this.unitOfWork.RemoveDepartment(this.CurrentDepartment.Model);
            this.AllDepartments.Remove(this.CurrentDepartment);
            this.CurrentDepartment = null;
        }
    }
}
