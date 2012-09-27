// 版权所有(C) Microsoft Corporation。保留所有权利。

namespace Tests.ViewModel
{
    using EmployeeTracker.Model;
    using EmployeeTracker.ViewModel;
    using Microsoft.VisualStudio.TestTools.UnitTesting;

    /// <summary>
    /// PhoneViewModel 的单元测试
    /// </summary>
    [TestClass]
    public class PhoneViewModelTests
    {
        /// <summary>
        /// 验证 ViewModel 上的 getter 和 setter 是否影响基础数据和通知更改
        /// </summary>
        [TestMethod]
        public void PropertyGetAndSet()
        {
            // 测试初始属性显示在 ViewModel 中
            Phone ph = new Phone { Number = "NUMBER", Extension = "EXTENSION" };
            PhoneViewModel vm = new PhoneViewModel(ph);
            Assert.AreEqual(ph, vm.Model, "Bound object property did not return object from model.");
            Assert.AreEqual(ph.ValidUsageValues, vm.ValidUsageValues, "ValidUsageValues property did not return value from model.");
            Assert.AreEqual("NUMBER", vm.Number, "Number property did not return value from model.");
            Assert.AreEqual("EXTENSION", vm.Extension, "Extension property did not return value from model.");

            // 更改属性的测试将更新模型并引发 PropertyChanged
            string lastProperty;
            vm.PropertyChanged += (sender, e) => { lastProperty = e.PropertyName; };

            lastProperty = null;
            vm.Number = "NEW_NUMBER";
            Assert.AreEqual("Number", lastProperty, "Setting Number property did not raise correct PropertyChanged event.");
            Assert.AreEqual("NEW_NUMBER", ph.Number, "Setting Number property did not update model.");

            lastProperty = null;
            vm.Extension = "NEW_EXTENSION";
            Assert.AreEqual("Extension", lastProperty, "Setting Extension property did not raise correct PropertyChanged event.");
            Assert.AreEqual("NEW_EXTENSION", ph.Extension, "Setting Extension property did not update model.");
        }

        /// <summary>
        /// 验证 getter 是否反映模型中的更改
        /// </summary>
        [TestMethod]
        public void ModelChangesFlowToProperties()
        {
            // 测试 ViewModel 返回模型的当前值
            Phone ph = new Phone { Number = "NUMBER", Extension = "EXTENSION" };
            PhoneViewModel vm = new PhoneViewModel(ph);

            ph.Number = "NEW_NUMBER";
            ph.Extension = "NEW_EXTENSION";
            Assert.AreEqual("NEW_NUMBER", vm.Number, "Number property is not fetching the value from the model.");
            Assert.AreEqual("NEW_EXTENSION", vm.Extension, "Extension property is not fetching the value from the model.");
        }

        /// <summary>
        /// 验证在 null 无效时，是否引发 NullArgumentExceptions
        /// </summary>
        [TestMethod]
        public void CheckNullArgumentExceptions()
        {
            Utilities.CheckNullArgumentException(() => { new PhoneViewModel(null); }, "detail", "ctor");
        }
    }
}
