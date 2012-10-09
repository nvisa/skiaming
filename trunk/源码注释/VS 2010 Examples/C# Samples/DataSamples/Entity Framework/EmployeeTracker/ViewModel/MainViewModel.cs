// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。


namespace EmployeeTracker.ViewModel
{
    using System;
    using System.Collections.Generic;
    using System.Collections.ObjectModel;
    using System.Windows.Input;
    using EmployeeTracker.Common;
    using EmployeeTracker.Model.Interfaces;
    using EmployeeTracker.ViewModel.Helpers;

    /// <summary>
    /// 用于访问公司所有数据的 ViewModel
    /// </summary>
    public class MainViewModel : ViewModelBase
    {
        /// <summary>
        /// 用于协调更改的 UnitOfWork
        /// </summary>
        private IUnitOfWork unitOfWork;

        /// <summary>
        /// 初始化 MainViewModel 类的新实例。
        /// </summary>
        /// <param name="unitOfWork">用于协调更改的 UnitOfWork</param>
        /// <param name="departmentRepository">用于查询部门数据的存储库</param>
        /// <param name="employeeRepository">用于查询雇员数据的存储库</param>
        public MainViewModel(IUnitOfWork unitOfWork, IDepartmentRepository departmentRepository, IEmployeeRepository employeeRepository)
        {
            if (unitOfWork == null)
            {
                throw new ArgumentNullException("unitOfWork");
            }

            if (departmentRepository == null)
            {
                throw new ArgumentNullException("departmentRepository");
            }

            if (employeeRepository == null)
            {
                throw new ArgumentNullException("employeeRepository");
            }

            this.unitOfWork = unitOfWork;

            // 生成数据结构以填充应用程序图面的区域
            ObservableCollection<EmployeeViewModel> allEmployees = new ObservableCollection<EmployeeViewModel>();
            ObservableCollection<DepartmentViewModel> allDepartments = new ObservableCollection<DepartmentViewModel>();

            foreach (var dep in departmentRepository.GetAllDepartments())
            {
                allDepartments.Add(new DepartmentViewModel(dep));
            }

            foreach (var emp in employeeRepository.GetAllEmployees())
            {
                allEmployees.Add(new EmployeeViewModel(emp, allEmployees, allDepartments, this.unitOfWork));
            }

            this.DepartmentWorkspace = new DepartmentWorkspaceViewModel(allDepartments, unitOfWork);
            this.EmployeeWorkspace = new EmployeeWorkspaceViewModel(allEmployees, allDepartments, unitOfWork);

            // 生成在职时间较长的雇员的非交互列表
            List<BasicEmployeeViewModel> longServingEmployees = new List<BasicEmployeeViewModel>();
            foreach (var emp in employeeRepository.GetLongestServingEmployees(5))
            {
                longServingEmployees.Add(new BasicEmployeeViewModel(emp));
            }

            this.LongServingEmployees = longServingEmployees;

            this.SaveCommand = new DelegateCommand((o) => this.Save());
        }

        /// <summary>
        /// 获取保存当前会话 UnitOfWork 中所做更改的命令
        /// </summary>
        public ICommand SaveCommand { get; private set; }

        /// <summary>
        /// 获取用于管理公司雇员的工作区
        /// </summary>
        public EmployeeWorkspaceViewModel EmployeeWorkspace { get; private set; }

        /// <summary>
        /// 获取用于管理公司部门的工作区
        /// </summary>
        public DepartmentWorkspaceViewModel DepartmentWorkspace { get; private set; }

        /// <summary>
        /// 获取忠诚榜上的雇员的列表
        /// </summary>
        public IEnumerable<BasicEmployeeViewModel> LongServingEmployees { get; private set; }

        /// <summary>
        /// 保存在当前会话 UnitOfWork 中所做的全部更改
        /// </summary>
        private void Save()
        {
            this.unitOfWork.Save();
        }
    }
}
