// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。


namespace EmployeeTracker.Common
{
    using System;
    using EmployeeTracker.Model;

    /// <summary>
    /// 封装对基础数据的更改
    /// </summary>
    public interface IUnitOfWork
    {
        /// <summary>
        /// 保存此 UnitOfWork 中的所有挂起更改
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
        /// 注册添加新部门
        /// </summary>
        /// <param name="department">要添加的部门</param>
        /// <exception cref="InvalidOperationException">如果部门已添加到 UnitOfWork，则引发异常</exception>
        void AddDepartment(Department department);

        /// <summary>
        /// 注册添加新雇员
        /// </summary>
        /// <param name="employee">要添加的雇员</param>
        /// <exception cref="InvalidOperationException">如果雇员已添加到 UnitOfWork，则引发异常</exception>
        void AddEmployee(Employee employee);

        /// <summary>
        /// 注册添加新的联系人详细信息
        /// </summary>
        /// <param name="employee">要添加联系人详细信息的雇员</param>
        /// <param name="detail">要添加的联系人详细信息</param>
        /// <exception cref="InvalidOperationException">如果此 UnitOfWork 未跟踪雇员，则引发异常</exception>
        /// <exception cref="InvalidOperationException">如果联系人详细信息已添加到 UnitOfWork，则引发异常</exception>
        void AddContactDetail(Employee employee, ContactDetail detail);

        /// <summary>
        /// 注册移除现有部门
        /// </summary>
        /// <param name="department">要移除的部门</param>
        /// <exception cref="InvalidOperationException">如果此 UnitOfWork 未跟踪部门，则引发异常</exception>
        void RemoveDepartment(Department department);

        /// <summary>
        /// 注册移除现有雇员
        /// </summary>
        /// <param name="employee">要移除的雇员</param>
        /// <exception cref="InvalidOperationException">如果此 UnitOfWork 未跟踪雇员，则引发异常</exception>
        void RemoveEmployee(Employee employee);

        /// <summary>
        /// 注册移除现有联系人详细信息
        /// </summary>
        /// <param name="employee">要移除联系人详细信息的雇员</param>
        /// <param name="detail">要移除的联系人详细信息</param>
        /// <exception cref="InvalidOperationException">如果此 UnitOfWork 未跟踪雇员，则引发异常</exception>
        /// <exception cref="InvalidOperationException">如果此 UnitOfWork 未跟踪联系人详细信息，则引发异常</exception>
        void RemoveContactDetail(Employee employee, ContactDetail detail);
    }
}
