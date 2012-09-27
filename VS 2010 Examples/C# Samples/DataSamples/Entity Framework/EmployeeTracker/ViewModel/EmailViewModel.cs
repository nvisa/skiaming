// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。


namespace EmployeeTracker.ViewModel
{
    using System;
    using EmployeeTracker.Model;

    /// <summary>
    /// 单个电子邮件的 ViewModel
    /// </summary>
    public class EmailViewModel : ContactDetailViewModel
    {
        /// <summary>
        /// 支持此 ViewModel 的 Email 对象
        /// </summary>
        private Email email;

        /// <summary>
        /// 初始化 EmailViewModel 类的新实例。
        /// </summary>
        /// <param name="detail">此 ViewModel 基于的基础电子邮件</param>
        public EmailViewModel(Email detail)
        {
            if (detail == null)
            {
                throw new ArgumentNullException("detail");
            }

            this.email = detail;
        }

        /// <summary>
        /// 获取此 ViewModel 基于的基础电子邮件
        /// </summary>
        public override ContactDetail Model
        {
            get { return this.email; }
        }

        /// <summary>
        /// 获取或设置实际电子邮件地址
        /// </summary>
        public string Address
        {
            get
            {
                return this.email.Address;
            }

            set
            {
                this.email.Address = value;
                this.OnPropertyChanged("Address");
            }
        }
    }
}
