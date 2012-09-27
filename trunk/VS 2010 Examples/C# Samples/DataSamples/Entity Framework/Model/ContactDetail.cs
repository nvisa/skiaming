// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。


namespace EmployeeTracker.Model
{
    using System.Collections.Generic;

    /// <summary>
    /// 表示雇员的联系人详细信息的基类
    /// </summary>
    public abstract class ContactDetail
    {
        /// <summary>
        /// 获取对 usage 属性有效的值
        /// </summary>
        public abstract IEnumerable<string> ValidUsageValues { get; }

        /// <summary>
        /// 获取或设置此 ContactDetail 的 ID
        /// </summary>
        public virtual int ContactDetailId { get; set; }

        /// <summary>
        /// 获取或设置此 ContactDetail 所属的雇员的 ID
        /// </summary>
        public virtual int EmployeeId { get; set; }

        /// <summary>
        /// 获取或设置此联系人详细信息的用途，例如家庭/商务等。
        /// </summary>
        public virtual string Usage { get; set; }
    }
}
