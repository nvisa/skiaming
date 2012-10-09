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
    /// 表示公司中的一个部门
    /// </summary>
    public class Department
    {
        /// <summary>
        /// 属于此部门的雇员
        /// </summary>
        private ICollection<Employee> employees;

        /// <summary>
        /// 初始化 Department 类的新实例。
        /// </summary>
        public Department()
        {
            // 连接雇员集合以同步引用
            // 注意: 使用更改跟踪代理针对 Entity Framework 运行时，将不执行此逻辑，
            //       因为 Employees 属性将被 EntityCollection<Employee> 覆盖和替换。
            //       EntityCollection 将改为执行此链接地址信息。
            ObservableCollection<Employee> emps = new ObservableCollection<Employee>();
            this.employees = emps;
            emps.CollectionChanged += (sender, e) =>
            {
                // 设置对添加到此部门的所有雇员的引用
                if (e.NewItems != null)
                {
                    foreach (Employee item in e.NewItems)
                    {
                        if (item.Department != this)
                        {
                            item.Department = this;
                        }
                    }
                }

                // 清除对正在移除但仍指向此部门的所有雇员的引用
                if (e.OldItems != null)
                {
                    foreach (Employee item in e.OldItems)
                    {
                        if (item.Department == this)
                        {
                            item.Department = null;
                        }
                    }
                }
            };
        }

        /// <summary>
        /// 获取或设置此部门的 ID
        /// </summary>
        public virtual int DepartmentId { get; set; }

        /// <summary>
        /// 获取或设置此部门的名称
        /// </summary>
        public virtual string DepartmentName { get; set; }

        /// <summary>
        /// 获取或设置此部门的代码
        /// </summary>
        public virtual string DepartmentCode { get; set; }

        /// <summary>
        /// 获取或设置此部门上次审核的日期
        /// </summary>
        public virtual DateTime? LastAudited { get; set; }

        /// <summary>
        /// 获取或设置属于此部门的雇员
        /// 添加或移除操作将修复受影响的雇员的 department 属性
        /// </summary>
        public virtual ICollection<Employee> Employees
        {
            get { return this.employees; }
            set { this.employees = value; }
        }
    }
}
