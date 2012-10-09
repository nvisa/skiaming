// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。


namespace EmployeeTracker.Model
{
    using System.Collections.Generic;

    /// <summary>
    /// 表示雇员地址
    /// </summary>
    public class Address : ContactDetail
    {
        /// <summary>
        /// 对地址有效的 Usage 值
        /// </summary>
        private static string[] validUsageValues = new string[] { "Business", "Home", "Mailing" };

        /// <summary>
        /// 获取对地址有效的 usage 值的列表
        /// </summary>
        public override IEnumerable<string> ValidUsageValues
        {
            get { return validUsageValues; }
        }

        /// <summary>
        /// 获取或设置此地址的第一行
        /// </summary>
        public virtual string LineOne { get; set; }

        /// <summary>
        /// 获取或设置此地址的第二行
        /// </summary>
        public virtual string LineTwo { get; set; }

        /// <summary>
        /// 获取或设置此地址的城市
        /// </summary>
        public virtual string City { get; set; }

        /// <summary>
        /// 获取或设置此地址的省/市/自治区
        /// </summary>
        public virtual string State { get; set; }

        /// <summary>
        /// 获取或设置此地址的邮政编码
        /// </summary>
        public virtual string ZipCode { get; set; }

        /// <summary>
        /// 获取或设置此地址的国家/地区
        /// </summary>
        public virtual string Country { get; set; }
    }
}
