// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。


namespace EmployeeTracker.ViewModel
{
    using System;
    using System.Globalization;
    using EmployeeTracker.Model;
    using EmployeeTracker.ViewModel.Helpers;

    /// <summary>
    /// 无关联的单个雇员的 ViewModel
    /// 如果需要显示或编辑关联，则应使用 EmployeeViewModel
    /// </summary>
    public class BasicEmployeeViewModel : ViewModelBase
    {
        /// <summary>
        /// 初始化 BasicEmployeeViewModel 类的新实例。
        /// </summary>
        /// <param name="employee">此 ViewModel 基于的基础雇员</param>
        public BasicEmployeeViewModel(Employee employee)
        {
            if (employee == null)
            {
                throw new ArgumentNullException("employee");
            }

            this.Model = employee;
        }

        /// <summary>
        /// 获取此 ViewModel 基于的基础雇员
        /// </summary>
        public Employee Model { get; private set; }

        /// <summary>
        /// 获取或设置此雇员的名字
        /// </summary>
        public string FirstName
        {
            get
            {
                return this.Model.FirstName;
            }

            set
            {
                this.Model.FirstName = value;
                this.OnPropertyChanged("FirstName");
            }
        }

        /// <summary>
        /// 获取或设置此雇员的职务
        /// </summary>
        public string Title
        {
            get
            {
                return this.Model.Title;
            }

            set
            {
                this.Model.Title = value;
                this.OnPropertyChanged("Title");
            }
        }

        /// <summary>
        /// 获取或设置此雇员的姓氏
        /// </summary>
        public string LastName
        {
            get
            {
                return this.Model.LastName;
            }

            set
            {
                this.Model.LastName = value;
                this.OnPropertyChanged("LastName");
            }
        }

        /// <summary>
        /// 获取或设置此雇员在公司中担任的职位
        /// </summary>
        public string Position
        {
            get
            {
                return this.Model.Position;
            }

            set
            {
                this.Model.Position = value;
                this.OnPropertyChanged("Position");
            }
        }

        /// <summary>
        /// 获取或设置此雇员的出生日期
        /// </summary>
        public DateTime BirthDate
        {
            get
            {
                return this.Model.BirthDate;
            }

            set
            {
                this.Model.BirthDate = value;
                this.OnPropertyChanged("BirthDate");
            }
        }

        /// <summary>
        /// 获取或设置公司雇用此雇员的日期
        /// </summary>
        public DateTime HireDate
        {
            get
            {
                return this.Model.HireDate;
            }

            set
            {
                this.Model.HireDate = value;
                this.OnPropertyChanged("HireDate");
            }
        }

        /// <summary>
        /// 获取或设置此雇员离开公司的日期
        /// </summary>
        public DateTime? TerminationDate
        {
            get
            {
                return this.Model.TerminationDate;
            }

            set
            {
                this.Model.TerminationDate = value;
                this.OnPropertyChanged("TerminationDate");
            }
        }

        /// <summary>
        /// 获取引用此雇员时要显示的文本
        /// </summary>
        public string DisplayName
        {
            get { return string.Format(CultureInfo.InvariantCulture, "{0}, {1}", this.Model.LastName, this.Model.FirstName); }
        }

        /// <summary>
        /// 获取为此雇员雇用日期的只读版本显示的文本
        /// </summary>
        public string DisplayHireDate
        {
            get { return this.Model.HireDate.ToShortDateString(); }
        }
    }
}
