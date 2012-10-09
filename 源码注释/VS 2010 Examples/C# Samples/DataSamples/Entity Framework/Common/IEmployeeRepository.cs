// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。


namespace EmployeeTracker.Model.Interfaces
{
    using System.Collections.Generic;
    using EmployeeTracker.Model;

    /// <summary>
    /// 用于检索雇员数据的存储库
    /// </summary>
    public interface IEmployeeRepository
    {
        /// <summary>
        /// 公司的所有雇员
        /// </summary>
        /// <returns>所有雇员的可枚举集合</returns>  
        IEnumerable<Employee> GetAllEmployees();

        /// <summary>
        /// 获取在职时间最长的雇员
        /// </summary>
        /// <param name="quantity">要返回的雇员数量</param>
        /// <returns>在职时间最长的雇员的可枚举集合</returns>
        IEnumerable<Employee> GetLongestServingEmployees(int quantity);
    }
}
