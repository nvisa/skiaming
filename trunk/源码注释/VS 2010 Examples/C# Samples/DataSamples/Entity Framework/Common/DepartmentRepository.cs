// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。


namespace EmployeeTracker.Common
{
    using System;
    using System.Collections.Generic;
    using System.Data.Objects;
    using System.Linq;
    using EmployeeTracker.Model;
    using EmployeeTracker.Model.Interfaces;

    /// <summary>
    /// 用于从 IObjectSet 检索部门数据的存储库
    /// </summary>
    public class DepartmentRepository : IDepartmentRepository
    {
        /// <summary>
        /// 从其中检索数据的基础 ObjectSet
        /// </summary>
        private IObjectSet<Department> objectSet;

        /// <summary>
        /// 初始化 DepartmentRepository 类的新实例。
        /// </summary>
        /// <param name="context">从其中检索数据的上下文</param>
        public DepartmentRepository(IEmployeeContext context)
        {
            if (context == null)
            {
                throw new ArgumentNullException("context");
            }

            this.objectSet = context.Departments;
        }

        /// <summary>
        /// 公司的所有部门
        /// </summary>
        /// <returns>所有部门的可枚举集合</returns>
        public IEnumerable<Department> GetAllDepartments()
        {
            // 注意: 在实现数据访问方法的过程中，要考虑一些问题:
            //    -  使用 ToList 可以确保在执行此方法的过程中而不是在枚举数据时
            //       引发任何与数据访问相关的异常。
            //    -  返回 IEnumerable 而不是 IQueryable 可以确保存储库完全控制
            //       从存储检索数据的方式，返回 IQueryable 将允许使用者
            //       添加更多操作符并影响发送到存储的查询。
            return this.objectSet.ToList();
        }
    }
}
