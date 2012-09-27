// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。


namespace EmployeeTracker.Model
{
    using System.Collections.Generic;

    /// <summary>
    /// 表示雇员电子邮件地址
    /// </summary>
    public class Email : ContactDetail
    {
        /// <summary>
        /// 对电子邮件地址有效的 Usage 值
        /// </summary>
        private static string[] validUsageValues = new string[] { "Business", "Personal" };
        
        /// <summary>
        /// 获取对电子邮件地址有效的 usage 值的列表
        /// </summary>
        public override IEnumerable<string> ValidUsageValues
        {
            get { return validUsageValues; }
        }

        /// <summary>
        /// 获取或设置实际电子邮件地址
        /// </summary>
        public virtual string Address { get; set; }
    }
}
