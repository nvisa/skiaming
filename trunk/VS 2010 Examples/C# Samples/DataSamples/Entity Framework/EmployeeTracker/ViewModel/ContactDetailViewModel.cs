// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。


namespace EmployeeTracker.ViewModel
{
    using System;
    using System.Collections.Generic;
    using EmployeeTracker.Model;
    using EmployeeTracker.ViewModel.Helpers;

    /// <summary>
    /// 单个 ContactDetail 的 ViewModel 的常用功能
    /// </summary>
    public abstract class ContactDetailViewModel : ViewModelBase
    {
        /// <summary>
        /// 获取可分配给此 ViewModel 的 Usage 属性的值
        /// </summary>
        public IEnumerable<string> ValidUsageValues
        {
            get { return this.Model.ValidUsageValues; }
        }

        /// <summary>
        /// 获取此 ViewModel 基于的基础 ContactDetail
        /// </summary>
        public abstract ContactDetail Model { get; }

        /// <summary>
        /// 获取或设置此详细信息的用途，例如家庭/商务等。
        /// ValidUsageValues 属性提供了可能的值
        /// </summary>
        public string Usage
        {
            get
            {
                return this.Model.Usage;
            }

            set
            {
                this.Model.Usage = value;
                this.OnPropertyChanged("Usage");
            }
        }

        /// <summary>
        /// 构造视图模型以表示所提供的 ContactDetail
        /// </summary>
        /// <param name="detail">要为其生成 ViewModel 的详细信息</param>
        /// <returns>构造的 ViewModel，如果无法生成则为 null</returns>
        public static ContactDetailViewModel BuildViewModel(ContactDetail detail)
        {
            if (detail == null)
            {
                throw new ArgumentNullException("detail");
            }

            Email e = detail as Email;
            if (e != null)
            {
                return new EmailViewModel(e);
            }

            Phone p = detail as Phone;
            if (p != null)
            {
                return new PhoneViewModel(p);
            }

            Address a = detail as Address;
            if (a != null)
            {
                return new AddressViewModel(a);
            }

            return null;
        }
    }
}
