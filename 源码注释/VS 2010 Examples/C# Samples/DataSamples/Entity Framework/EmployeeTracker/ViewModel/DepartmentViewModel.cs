// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。


namespace EmployeeTracker.ViewModel
{
    using System;
    using EmployeeTracker.Model;
    using EmployeeTracker.ViewModel.Helpers;

    /// <summary>
    /// 单个部门的 ViewModel
    /// </summary>
    public class DepartmentViewModel : ViewModelBase
    {
        /// <summary>
        /// 初始化 DepartmentViewModel 类的新实例。
        /// </summary>
        /// <param name="department">此 ViewModel 基于的基础部门</param>
        public DepartmentViewModel(Department department)
        {
            if (department == null)
            {
                throw new ArgumentNullException("department");
            }

            this.Model = department;
        }

        /// <summary>
        /// 获取此 ViewModel 基于的基础部门
        /// </summary>
        public Department Model { get; private set; }

        /// <summary>
        /// 获取或设置此部门的名称
        /// </summary>
        public string DepartmentName
        {
            get
            {
                return this.Model.DepartmentName;
            }

            set
            {
                this.Model.DepartmentName = value;
                this.OnPropertyChanged("DepartmentName");
            }
        }

        /// <summary>
        /// 获取或设置此部门的代码
        /// </summary>
        public string DepartmentCode
        {
            get
            {
                return this.Model.DepartmentCode;
            }

            set
            {
                this.Model.DepartmentCode = value;
                this.OnPropertyChanged("DepartmentCode");
            }
        }

        /// <summary>
        /// 获取或设置此部门上次审核的日期
        /// </summary>
        public DateTime? LastAudited
        {
            get
            {
                return this.Model.LastAudited;
            }

            set
            {
                this.Model.LastAudited = value;
                this.OnPropertyChanged("LastAudited");
            }
        }
    }
}
