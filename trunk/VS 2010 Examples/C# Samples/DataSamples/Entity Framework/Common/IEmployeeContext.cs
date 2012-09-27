// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。


namespace EmployeeTracker.Common
{
    using System;
    using System.Data.Objects;
    using EmployeeTracker.Model;

    /// <summary>
    /// 包含 EmployeeTracker 模型数据的数据上下文
    /// </summary>
    public interface IEmployeeContext : IDisposable
    {
        /// <summary>
        /// 在数据上下文中获取雇员
        /// </summary>
        IObjectSet<Employee> Employees { get; }

        /// <summary>
        /// 在数据上下文中获取部门
        /// </summary>
        IObjectSet<Department> Departments { get; }

        /// <summary>
        /// 在数据上下文中获取联系人详细信息
        /// </summary>
        IObjectSet<ContactDetail> ContactDetails { get; }

        /// <summary>
        /// 将所有挂起更改保存到数据上下文
        /// </summary>
        void Save();

        /// <summary>
        /// 创建指定对象类型的新实例
        /// 注意: 针对 Entity Framework 运行时，使用此模式可以
        ///       允许使用更改跟踪代理。
        /// </summary>
        /// <typeparam name="T">要创建的类型</typeparam>
        /// <returns>新创建的对象</returns>
        T CreateObject<T>() where T : class;

        /// <summary>
        /// 检查是否在此数据上下文中跟踪所提供的对象
        /// </summary>
        /// <param name="obj">要检查的对象</param>
        /// <returns>如果跟踪该对象，则为 true，否则为 false</returns>
        bool IsObjectTracked(object obj);
    }
}
