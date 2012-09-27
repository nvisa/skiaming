// 版权所有(C) Microsoft Corporation。保留所有权利。

namespace Tests.ViewModel
{
    using System.Diagnostics.CodeAnalysis;
    using EmployeeTracker.Model;
    using EmployeeTracker.ViewModel;
    using Microsoft.VisualStudio.TestTools.UnitTesting;
    using Tests;

    /// <summary>
    /// EmailViewModel 的单元测试
    /// </summary>
    [TestClass]
    public class EmailViewModelTests
    {
        /// <summary>
        /// 验证 ViewModel 上的 getter 和 setter 是否影响基础数据和通知更改
        /// </summary>
        [TestMethod]
        public void PropertyGetAndSet()
        {
            // 测试初始属性显示在 ViewModel 中
            Email em = new Email { Address = "EMAIL" };
            EmailViewModel vm = new EmailViewModel(em);
            Assert.AreEqual(em, vm.Model, "Bound object property did not return object from model.");
            Assert.AreEqual(em.ValidUsageValues, vm.ValidUsageValues, "ValidUsageValues property did not return value from model.");
            Assert.AreEqual("EMAIL", vm.Address, "Address property did not return value from model.");

            // 更改属性的测试将更新模型并引发 PropertyChanged
            string lastProperty;
            vm.PropertyChanged += (sender, e) => { lastProperty = e.PropertyName; };

            lastProperty = null;
            vm.Address = "NEW_EMAIL";
            Assert.AreEqual("Address", lastProperty, "Setting Address property did not raise correct PropertyChanged event.");
            Assert.AreEqual("NEW_EMAIL", em.Address, "Setting Address property did not update model.");
        }

        /// <summary>
        /// 验证 getter 是否反映模型中的更改
        /// </summary>
        [TestMethod]
        public void ModelChangesFlowToProperties()
        {
            // 测试 ViewModel 返回模型的当前值
            Email em = new Email { Address = "EMAIL" };
            EmailViewModel vm = new EmailViewModel(em);

            em.Address = "NEW_EMAIL";
            Assert.AreEqual("NEW_EMAIL", vm.Address, "Address property is not fetching the value from the model.");
        }

        /// <summary>
        /// 验证在 null 无效时，是否引发 NullArgumentExceptions
        /// </summary>
        [TestMethod]
        public void CheckNullArgumentExceptions()
        {
            Utilities.CheckNullArgumentException(() => { new EmailViewModel(null); }, "detail", "ctor");
        }
    }
}
