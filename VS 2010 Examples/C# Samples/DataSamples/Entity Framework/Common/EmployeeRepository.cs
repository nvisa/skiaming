// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。


namespace EmployeeTracker.Common
{
    using System;
    using System.Collections.Generic;
    using System.Data.Objects;
    using System.Data.Objects.DataClasses;
    using System.Linq;
    using EmployeeTracker.Model;
    using EmployeeTracker.Model.Interfaces;

    /// <summary>
    /// 用于从 ObjectSet 检索雇员数据的存储库
    /// </summary>
    public class EmployeeRepository : IEmployeeRepository
    {
        /// <summary>
        /// 从其中检索数据的基础 ObjectSet
        /// </summary>
        private IObjectSet<Employee> objectSet;

        /// <summary>
        /// 初始化 EmployeeRepository 类的新实例。
        /// </summary>
        /// <param name="context">从其中检索数据的上下文</param>
        public EmployeeRepository(IEmployeeContext context)
        {
            if (context == null)
            {
                throw new ArgumentNullException("context");
            }

            this.objectSet = context.Employees;
        }

        /// <summary>
        /// 公司的所有雇员
        /// </summary>
        /// <returns>所有雇员的可枚举集合</returns>  
        public IEnumerable<Employee> GetAllEmployees()
        {
            // 注意: 在实现数据访问方法的过程中，要考虑一些问题:
            //    -  使用 ToList 可以确保在执行此方法的过程中而不是在枚举数据时
            //       引发任何与数据访问相关的异常。
            //    -  返回 IEnumerable 而不是 IQueryable 可以确保存储库完全控制
            //       从存储检索数据的方式，返回 IQueryable 将允许使用者
            //       添加更多操作符并影响发送到存储的查询。
            return this.objectSet.ToList();
        }

        /// <summary>
        /// 获取在职时间最长的雇员
        /// </summary>
        /// <param name="quantity">要返回的雇员数量</param>
        /// <returns>在职时间最长的雇员的可枚举集合</returns>
        public IEnumerable<Employee> GetLongestServingEmployees(int quantity)
        {
            // 注意: 针对虚设对象集运行时，在职时间的排序将在内存中进行
            //       当针对 EF 运行时，将使用在 EmployeeModel.edmx 中声明的模型定义函数，
            //       并在存储区中处理排序
            return this.objectSet
                .Where(e => e.TerminationDate == null)
                .OrderByDescending(e => GetTenure(e))
                .Take(quantity)
                .ToList();
        }

        /// <summary>
        /// 计算雇员在公司的在职时间
        /// </summary>
        /// <param name="employee">要计算在职时间的雇员</param>
        /// <returns>以年为单位表示的在职时间</returns>
        [EdmFunction("EmployeeTracker.EntityFramework", "GetTenure")]
        private static int GetTenure(Employee employee)
        {
            // 注意: 包括此方法体，以便针对内存中的虚设运行
            //       EF 不需要实现，请参见 GetLongestServingEmployees() 的说明
            DateTime endDate = employee.TerminationDate ?? DateTime.Today;
            return endDate.Subtract(employee.HireDate).Days / 365;
        }
    }
}
