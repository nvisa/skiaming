// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。


namespace EmployeeTracker.Model
{
    using System;
    using System.Collections.Generic;
    using System.Collections.ObjectModel;
    using System.Diagnostics.CodeAnalysis;

    /// <summary>
    /// 表示公司雇用的人员
    /// </summary>
    public class Employee
    {
        /// <summary>
        /// 属于此雇员的联系人详细信息
        /// </summary>
        private ICollection<ContactDetail> details;

        /// <summary>
        /// 此雇员的下属雇员
        /// </summary>
        private ICollection<Employee> reports;

        /// <summary>
        /// 此雇员所属的部门
        /// </summary>
        private Department department;

        /// <summary>
        /// 此雇员的经理
        /// </summary>
        private Employee manager;

        /// <summary>
        /// 初始化 Employee 类的新实例。
        /// </summary>
        public Employee()
        {
            // 注意: 由于这是单向导航，因此不需要修复
            this.details = new ObservableCollection<ContactDetail>();

            // 连接报告集合以同步引用
            // 注意: 使用更改跟踪代理针对 Entity Framework 运行时，将不执行此逻辑，
            //       因为 Reports 属性将被 EntityCollection<Employee> 覆盖和替换。
            //       EntityCollection 将改为执行此链接地址信息。
            ObservableCollection<Employee> reps = new ObservableCollection<Employee>();
            this.reports = reps;
            reps.CollectionChanged += (sender, e) =>
            {
                // 设置对添加到此经理的所有雇员的引用
                if (e.NewItems != null)
                {
                    foreach (Employee item in e.NewItems)
                    {
                        if (item.Manager != this)
                        {
                            item.Manager = this;
                        }
                    }
                }

                // 清除对正在移除但仍指向此经理的所有雇员的引用
                if (e.OldItems != null)
                {
                    foreach (Employee item in e.OldItems)
                    {
                        if (item.Manager == this)
                        {
                            item.Manager = null;
                        }
                    }
                }
            };
        }

        /// <summary>
        /// 获取或设置此雇员的 ID
        /// </summary>
        public virtual int EmployeeId { get; set; }

        /// <summary>
        /// 获取或设置此雇员的职务
        /// </summary>
        public virtual string Title { get; set; }

        /// <summary>
        /// 获取或设置此雇员的名字
        /// </summary>
        public virtual string FirstName { get; set; }

        /// <summary>
        /// 获取或设置此雇员的姓氏
        /// </summary>
        public virtual string LastName { get; set; }

        /// <summary>
        /// 获取或设置此雇员的职位
        /// </summary>
        public virtual string Position { get; set; }

        /// <summary>
        /// 获取或设置此雇员被雇用的日期
        /// </summary>
        public virtual DateTime HireDate { get; set; }

        /// <summary>
        /// 获取或设置此雇员离开公司的日期
        /// 如果雇员是当前雇员，则返回 null
        /// </summary>
        public virtual DateTime? TerminationDate { get; set; }

        /// <summary>
        /// 获取或设置此雇员的出生日期
        /// </summary>
        public virtual DateTime BirthDate { get; set; }

        /// <summary>
        /// 获取或设置此雇员所属的部门的 ID
        /// </summary>
        public virtual int? DepartmentId { get; set; }

        /// <summary>
        /// 获取或设置此雇员经理的 ID
        /// </summary>
        public virtual int? ManagerId { get; set; }

        /// <summary>
        /// 获取或设置此雇员的联系人详细信息
        /// 由于这是单向导航，因此不执行修复
        /// </summary>
        public virtual ICollection<ContactDetail> ContactDetails
        {
            get { return this.details; }
            set { this.details = value; }
        }

        /// <summary>
        /// 获取或设置此雇员的下属雇员
        /// 添加或移除操作将修复受影响的雇员的 manager 属性
        /// </summary>
        public virtual ICollection<Employee> Reports
        {
            get { return this.reports; }
            set { this.reports = value; }
        }

        /// <summary>
        /// 获取或设置此雇员所属的部门
        /// 设置此属性将修复原部门和新部门的集合
        /// </summary>
        public virtual Department Department
        {
            get
            {
                return this.department;
            }

            set
            {
                if (value != this.department)
                {
                    Department original = this.department;
                    this.department = value;

                    // 从旧集合中移除
                    if (original != null && original.Employees.Contains(this))
                    {
                        original.Employees.Remove(this);
                    }

                    // 添加到新集合
                    if (value != null && !value.Employees.Contains(this))
                    {
                        value.Employees.Add(this);
                    }
                }
            }
        }

        /// <summary>
        /// 获取或设置此雇员经理
        /// 设置此属性将修复原经理和新经理的集合
        /// </summary>
        public virtual Employee Manager
        {
            get
            {
                return this.manager;
            }

            set
            {
                if (value != this.manager)
                {
                    Employee original = this.manager;
                    this.manager = value;

                    // 从旧集合中移除
                    if (original != null && original.Reports.Contains(this))
                    {
                        original.Reports.Remove(this);
                    }

                    // 添加到新集合
                    if (value != null && !value.Reports.Contains(this))
                    {
                        value.Reports.Add(this);
                    }
                }
            }
        }
    }
}
