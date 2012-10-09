// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。


namespace EmployeeTracker.ViewModel
{
    using System;
    using EmployeeTracker.Model;

    /// <summary>
    /// 单个地址的 ViewModel
    /// </summary>
    public class AddressViewModel : ContactDetailViewModel
    {
        /// <summary>
        /// 支持此 ViewModel 的 Address 对象
        /// </summary>
        private Address address;
        
        /// <summary>
        /// 初始化 AddressViewModel 类的新实例。
        /// </summary>
        /// <param name="detail">此 ViewModel 基于的基础地址</param>
        public AddressViewModel(Address detail)
        {
            if (detail == null)
            {
                throw new ArgumentNullException("detail");
            }

            this.address = detail;
        }

        /// <summary>
        /// 此 ViewModel 基于的基础地址
        /// </summary>
        public override ContactDetail Model
        {
            get { return this.address; }
        }

        /// <summary>
        /// 获取或设置第一个地址行
        /// </summary>
        public string LineOne
        {
            get
            {
                return this.address.LineOne;
            }

            set
            {
                this.address.LineOne = value;
                this.OnPropertyChanged("LineOne");
            }
        }

        /// <summary>
        /// 获取或设置第二个地址行
        /// </summary>
        public string LineTwo
        {
            get
            {
                return this.address.LineTwo;
            }

            set
            {
                this.address.LineTwo = value;
                this.OnPropertyChanged("LineTwo");
            }
        }

        /// <summary>
        /// 获取或设置此地址的城市
        /// </summary>
        public string City
        {
            get
            {
                return this.address.City;
            }

            set
            {
                this.address.City = value;
                this.OnPropertyChanged("City");
            }
        }

        /// <summary>
        /// 获取或设置此地址的省/市/自治区
        /// </summary>
        public string State
        {
            get
            {
                return this.address.State;
            }

            set
            {
                this.address.State = value;
                this.OnPropertyChanged("State");
            }
        }

        /// <summary>
        /// 获取或设置此地址的邮政编码
        /// </summary>
        public string ZipCode
        {
            get
            {
                return this.address.ZipCode;
            }

            set
            {
                this.address.ZipCode = value;
                this.OnPropertyChanged("ZipCode");
            }
        }

        /// <summary>
        /// 获取或设置此地址的国家/地区
        /// </summary>
        public string Country
        {
            get
            {
                return this.address.Country;
            }

            set
            {
                this.address.Country = value;
                this.OnPropertyChanged("Country");
            }
        }
    }
}
