// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。


namespace EmployeeTracker.Model.Interfaces
{
    using System.Collections.Generic;
    using EmployeeTracker.Model;

    /// <summary>
    /// 用于检索部门数据的存储库
    /// </summary>
    public interface IDepartmentRepository
    {
        /// <summary>
        /// 公司的所有部门
        /// </summary>
        /// <returns>所有部门的可枚举集合</returns>
        IEnumerable<Department> GetAllDepartments();
    }
}
