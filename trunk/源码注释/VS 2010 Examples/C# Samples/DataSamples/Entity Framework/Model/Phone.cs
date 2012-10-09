// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。


namespace EmployeeTracker.Model
{
    using System.Collections.Generic;

    /// <summary>
    /// 表示雇员电话号码
    /// </summary>
    public class Phone : ContactDetail
    {
        /// <summary>
        /// 对电话号码有效的 Usage 值
        /// </summary>
        private static string[] validUsageValues = new string[] { "Business", "Home", "Cell" };

        /// <summary>
        /// 获取对电话号码有效的 usage 值的列表
        /// </summary>
        public override IEnumerable<string> ValidUsageValues
        {
            get { return validUsageValues; }
        }

        /// <summary>
        /// 获取或设置实际电话号码
        /// </summary>
        public virtual string Number { get; set; }

        /// <summary>
        /// 获取或设置与此电话号码关联的分机
        /// </summary>
        public virtual string Extension { get; set; }
    }
}
