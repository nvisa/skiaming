// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。


namespace EmployeeTracker.Common
{
    using System;
    using System.Globalization;
    using System.Linq;
    using EmployeeTracker.Model;

    /// <summary>
    /// 封装对 EmployeeContext 中存储的基础数据的更改
    /// </summary>
    public class UnitOfWork : IUnitOfWork
    {
        /// <summary>
        /// 用于跟踪更改的基础上下文
        /// </summary>
        private IEmployeeContext underlyingContext;

        /// <summary>
        /// 初始化 UnitOfWork 类的新实例。
        /// 在 UnitOfWork 中注册的更改将记录在所提供的上下文中
        /// </summary>
        /// <param name="context">此 UnitOfWork 的基础上下文</param>
        public UnitOfWork(IEmployeeContext context)
        {
            if (context == null)
            {
                throw new ArgumentNullException("context");
            }

            this.underlyingContext = context;
        }

        /// <summary>
        /// 保存此 UnitOfWork 中的所有挂起更改
        /// </summary>
        public void Save()
        {
            this.underlyingContext.Save();
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
            return this.underlyingContext.CreateObject<T>();
        }

        /// <summary>
        /// 注册添加新部门
        /// </summary>
        /// <param name="department">要添加的部门</param>
        /// <exception cref="InvalidOperationException">如果部门已添加到 UnitOfWork，则引发异常</exception>
        public void AddDepartment(Department department)
        {
            if (department == null)
            {
                throw new ArgumentNullException("department");
            }
            
            this.CheckEntityDoesNotBelongToUnitOfWork(department);
            this.underlyingContext.Departments.AddObject(department);
        }

        /// <summary>
        /// 注册添加新雇员
        /// </summary>
        /// <param name="employee">要添加的雇员</param>
        /// <exception cref="InvalidOperationException">如果雇员已添加到 UnitOfWork，则引发异常</exception>
        public void AddEmployee(Employee employee)
        {
            if (employee == null)
            {
                throw new ArgumentNullException("employee");
            }

            this.CheckEntityDoesNotBelongToUnitOfWork(employee);
            this.underlyingContext.Employees.AddObject(employee);
        }

        /// <summary>
        /// 注册添加新的联系人详细信息
        /// </summary>
        /// <param name="employee">要添加联系人详细信息的雇员</param>
        /// <param name="detail">要添加的联系人详细信息</param>
        /// <exception cref="InvalidOperationException">如果此 UnitOfWork 未跟踪雇员，则引发异常</exception>
        /// <exception cref="InvalidOperationException">如果联系人详细信息已添加到 UnitOfWork，则引发异常</exception>
        public void AddContactDetail(Employee employee, ContactDetail detail)
        {
            if (employee == null)
            {
                throw new ArgumentNullException("employee");
            }

            if (detail == null)
            {
                throw new ArgumentNullException("detail");
            }

            this.CheckEntityDoesNotBelongToUnitOfWork(detail);
            this.CheckEntityBelongsToUnitOfWork(employee);

            this.underlyingContext.ContactDetails.AddObject(detail);
            employee.ContactDetails.Add(detail);
        }

        /// <summary>
        /// 注册移除现有部门
        /// </summary>
        /// <param name="department">要移除的部门</param>
        /// <exception cref="InvalidOperationException">如果此 UnitOfWork 未跟踪部门，则引发异常</exception>
        public void RemoveDepartment(Department department)
        {
            if (department == null)
            {
                throw new ArgumentNullException("department");
            }

            this.CheckEntityBelongsToUnitOfWork(department);
            foreach (var emp in department.Employees.ToList())
            {
                emp.Department = null;
            }

            this.underlyingContext.Departments.DeleteObject(department);
        }

        /// <summary>
        /// 注册移除现有雇员
        /// </summary>
        /// <param name="employee">要移除的雇员</param>
        /// <exception cref="InvalidOperationException">如果此 UnitOfWork 未跟踪雇员，则引发异常</exception>
        public void RemoveEmployee(Employee employee)
        {
            if (employee == null)
            {
                throw new ArgumentNullException("employee");
            }

            this.CheckEntityBelongsToUnitOfWork(employee);
            employee.Manager = null;
            foreach (var e in employee.Reports.ToList())
            {
                e.Manager = null;
            }

            this.underlyingContext.Employees.DeleteObject(employee);
        }

        /// <summary>
        /// 注册移除现有联系人详细信息
        /// </summary>
        /// <param name="employee">要移除联系人详细信息的雇员</param>
        /// <param name="detail">要移除的联系人详细信息</param>
        /// <exception cref="InvalidOperationException">如果此 UnitOfWork 未跟踪雇员，则引发异常</exception>
        /// <exception cref="InvalidOperationException">如果此 UnitOfWork 未跟踪联系人详细信息，则引发异常</exception>
        public void RemoveContactDetail(Employee employee, ContactDetail detail)
        {
            if (employee == null)
            {
                throw new ArgumentNullException("employee");
            }

            if (detail == null)
            {
                throw new ArgumentNullException("detail");
            }

            this.CheckEntityBelongsToUnitOfWork(detail);
            this.CheckEntityBelongsToUnitOfWork(employee);
            if (!employee.ContactDetails.Contains(detail))
            {
                throw new InvalidOperationException("The supplied ContactDetail does not belong to the supplied Employee");
            }

            employee.ContactDetails.Remove(detail);
            this.underlyingContext.ContactDetails.DeleteObject(detail);
        }

        /// <summary>
        /// 验证在此 UnitOfWork 中跟踪了指定实体
        /// </summary>
        /// <param name="entity">要搜索的对象</param>
        /// <exception cref="InvalidOperationException">如果此 UnitOfWork 未跟踪对象，则引发异常</exception>
        private void CheckEntityBelongsToUnitOfWork(object entity)
        {
            if (!this.underlyingContext.IsObjectTracked(entity))
            {
                throw new InvalidOperationException(string.Format(CultureInfo.InvariantCulture, "The supplied {0} is not part of this Unit of Work.", entity.GetType().Name));
            }
        }

        /// <summary>
        /// 验证在此 UnitOfWork 中未跟踪指定实体
        /// </summary>
        /// <param name="entity">要搜索的对象</param>
        /// <exception cref="InvalidOperationException">如果此 UnitOfWork 跟踪对象，则引发异常</exception>
        private void CheckEntityDoesNotBelongToUnitOfWork(object entity)
        {
            if (this.underlyingContext.IsObjectTracked(entity))
            {
                throw new InvalidOperationException(string.Format(CultureInfo.InvariantCulture, "The supplied {0} is already part of this Unit of Work.", entity.GetType().Name));
            }
        }
    }
}
