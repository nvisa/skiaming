// 版权所有(C) Microsoft Corporation。保留所有权利。

namespace Tests.ViewModel
{
    using System.Collections.Generic;
    using EmployeeTracker.Model;
    using EmployeeTracker.ViewModel;
    using Microsoft.VisualStudio.TestTools.UnitTesting;

    /// <summary>
    /// ContactDetailViewModel 的单元测试
    /// </summary>
    [TestClass]
    public class ContactDetailViewModelTests
    {
        /// <summary>
        /// 验证 BuildViewModel 是否可以创建所有联系人详细信息类型
        /// </summary>
        [TestMethod]
        public void BuildViewModel()
        {
            Phone p = new Phone();
            Email e = new Email();
            Address a = new Address();

            var pvm = ContactDetailViewModel.BuildViewModel(p);
            Assert.IsInstanceOfType(pvm, typeof(PhoneViewModel), "Factory method created wrong ViewModel type.");
            Assert.AreEqual(p, pvm.Model, "Underlying model object on ViewModel is not correct.");

            var evm = ContactDetailViewModel.BuildViewModel(e);
            Assert.IsInstanceOfType(evm, typeof(EmailViewModel), "Factory method created wrong ViewModel type.");
            Assert.AreEqual(e, evm.Model, "Underlying model object on ViewModel is not correct.");

            var avm = ContactDetailViewModel.BuildViewModel(a);
            Assert.IsInstanceOfType(avm, typeof(AddressViewModel), "Factory method created wrong ViewModel type.");
            Assert.AreEqual(a, avm.Model, "Underlying model object on ViewModel is not correct.");
        }

        /// <summary>
        /// 验证当 BuildViewModel 处理无法识别的类型时不会引发
        /// </summary>
        [TestMethod]
        public void BuildViewModelUnknownType()
        {
            var f = new FakeContactDetail();
            var fvm = ContactDetailViewModel.BuildViewModel(f);
            Assert.IsNull(fvm, "BuildViewModel should return null when it doesn't know how to handle a type.");
        }

        /// <summary>
        /// 验证在 null 无效时，是否引发 NullArgumentExceptions
        /// </summary>
        [TestMethod]
        public void CheckNullArgumentExceptions()
        {
            Utilities.CheckNullArgumentException(() => { ContactDetailViewModel.BuildViewModel(null); }, "detail", "BuildViewModel");
        }

        /// <summary>
        /// 用于测试 BuildViewModelUnknownType 的虚设联系人类型
        /// </summary>
        private class FakeContactDetail : ContactDetail
        {
            /// <summary>
            /// 获取 usage 字段的有效值
            /// 存根实现，仅返回 null
            /// </summary>
            public override IEnumerable<string> ValidUsageValues
            {
                get { return null; }
            }
        }
    }
}
