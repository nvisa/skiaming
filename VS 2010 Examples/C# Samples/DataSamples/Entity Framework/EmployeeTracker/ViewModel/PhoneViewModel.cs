// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。


namespace EmployeeTracker.ViewModel
{
    using System;
    using EmployeeTracker.Model;

    /// <summary>
    /// 单个电话的 ViewModel
    /// </summary>
    public class PhoneViewModel : ContactDetailViewModel
    {
        /// <summary>
        /// 支持此 ViewModel 的 Phone 对象
        /// </summary>
        private Phone phone;

        /// <summary>
        /// 初始化 PhoneViewModel 类的新实例。
        /// </summary>
        /// <param name="detail">此 ViewModel 基于的基础电话</param>
        public PhoneViewModel(Phone detail)
        {
            if (detail == null)
            {
                throw new ArgumentNullException("detail");
            }

            this.phone = detail;
        }

        /// <summary>
        /// 此 ViewModel 基于的基础电话
        /// </summary>
        public override ContactDetail Model
        {
            get { return this.phone; }
        }

        /// <summary>
        /// 获取或设置实际号码
        /// </summary>
        public string Number
        {
            get
            {
                return this.phone.Number;
            }

            set
            {
                this.phone.Number = value;
                this.OnPropertyChanged("Number");
            }
        }

        /// <summary>
        /// 获取或设置此电话号码的分机
        /// </summary>
        public string Extension
        {
            get
            {
                return this.phone.Extension;
            }

            set
            {
                this.phone.Extension = value;
                this.OnPropertyChanged("Extension");
            }
        }
    }
}
