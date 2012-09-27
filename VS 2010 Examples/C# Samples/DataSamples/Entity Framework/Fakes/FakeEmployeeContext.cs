// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。


namespace EmployeeTracker.Fakes
{
    using System;
    using System.Collections.Generic;
    using System.Data.Objects;
    using System.Diagnostics.CodeAnalysis;
    using System.Globalization;
    using System.Linq;
    using EmployeeTracker.Common;
    using EmployeeTracker.Model;
    using EmployeeTracker.Model.Interfaces;

    /// <summary>
    /// IEmployeeContext 在内存中的实现
    /// </summary>
    public sealed class FakeEmployeeContext : IEmployeeContext
    {
        /// <summary>
        /// 初始化 FakeEmployeeContext 类的新实例。
        /// 上下文包含空初始数据。
        /// </summary>
        public FakeEmployeeContext()
        {
            this.Employees = new FakeObjectSet<Employee>();
            this.Departments = new FakeObjectSet<Department>();
            this.ContactDetails = new FakeObjectSet<ContactDetail>();
        }

        /// <summary>
        /// 初始化 FakeEmployeeContext 类的新实例。
        /// 上下文包含所提供的初始数据。
        /// </summary>
        /// <param name="employees">要包括在上下文中的雇员</param>
        /// <param name="departments">要包括在上下文中的部门</param>
        public FakeEmployeeContext(IEnumerable<Employee> employees, IEnumerable<Department> departments)
        {
            if (employees == null)
            {
                throw new ArgumentNullException("employees");
            }

            if (departments == null)
            {
                throw new ArgumentNullException("departments");
            }

            this.Employees = new FakeObjectSet<Employee>(employees);
            this.Departments = new FakeObjectSet<Department>(departments);

            // 从提供的雇员数据派生联系人详细信息
            this.ContactDetails = new FakeObjectSet<ContactDetail>();
            foreach (var emp in employees)
            {
                foreach (var det in emp.ContactDetails)
                {
                    this.ContactDetails.AddObject(det);
                }
            }
        }

        /// <summary>
        /// 每当调用 Save() 时引发
        /// </summary>
        public event EventHandler<EventArgs> SaveCalled;

        /// <summary>
        /// 每当调用 Dispose() 时引发
        /// </summary>
        public event EventHandler<EventArgs> DisposeCalled;

        /// <summary>
        /// 获取此上下文跟踪的所有雇员
        /// </summary>
        public IObjectSet<Employee> Employees { get; private set; }

        /// <summary>
        /// 获取此上下文跟踪的所有部门
        /// </summary>
        public IObjectSet<Department> Departments { get; private set; }

        /// <summary>
        /// 获取此上下文跟踪的所有联系人详细信息
        /// </summary>
        public IObjectSet<ContactDetail> ContactDetails { get; private set; }

        /// <summary>
        /// 保存此上下文中的所有挂起更改
        /// </summary>
        public void Save()
        {
            this.OnSaveCalled(EventArgs.Empty);
        }

        /// <summary>
        /// 释放此上下文使用的全部资源
        /// </summary>
        public void Dispose()
        {
            this.OnDisposeCalled(EventArgs.Empty);
        }

        /// <summary>
        /// 创建指定对象类型的新实例
        /// 注意: 针对 Entity Framework 运行时，使用此模式可以
        ///       允许使用更改跟踪代理。
        /// </summary>
        /// <typeparam name="T">要创建的类型</typeparam>
        /// <returns>新创建的对象</returns>
        public T CreateObject<T>() where T : class
        {
            return Activator.CreateInstance<T>();
        }

        /// <summary>
        /// 检查此上下文是否跟踪指定对象
        /// </summary>
        /// <param name="entity">要搜索的对象</param>
        /// <returns>如果跟踪该对象，则为 true，否则为 false</returns>
        public bool IsObjectTracked(object entity)
        {
            if (entity == null)
            {
                throw new ArgumentNullException("entity");
            }

            return this.Employees.Contains(entity) 
                || this.Departments.Contains(entity) 
                || this.ContactDetails.Contains(entity);
        }

        /// <summary>
        /// 引发 SaveCalled 事件
        /// </summary>
        /// <param name="e">事件的参数</param>
        private void OnSaveCalled(EventArgs e)
        {
            var handler = this.SaveCalled;
            if (handler != null)
            {
                handler(this, e);
            }
        }

        /// <summary>
        /// 引发 DisposeCalled 事件
        /// </summary>
        /// <param name="e">事件的参数</param>
        private void OnDisposeCalled(EventArgs e)
        {
            var handler = this.DisposeCalled;
            if (handler != null)
            {
                handler(this, e);
            }
        }
    }
}
