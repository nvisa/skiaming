// 版权所有(C) Microsoft Corporation。保留所有权利。

namespace Tests.ViewModel
{
    using EmployeeTracker.Model;
    using EmployeeTracker.ViewModel;
    using Microsoft.VisualStudio.TestTools.UnitTesting;
    using Tests;

    /// <summary>
    /// DepartmentViewModel 的单元测试
    /// </summary>
    [TestClass]
    public class DepartmentViewModelTests
    {
        /// <summary>
        /// 验证 ViewModel 上的 getter 和 setter 是否影响基础数据和通知更改
        /// </summary>
        [TestMethod]
        public void PropertyGetAndSet()
        {
            // 测试初始属性显示在 ViewModel 中
            Department dep = new Department { DepartmentName = "DepartmentName", DepartmentCode = "DepartmentCode" };
            DepartmentViewModel vm = new DepartmentViewModel(dep);
            Assert.AreEqual(dep, vm.Model, "Bound object property did not return object from model.");
            Assert.AreEqual("DepartmentName", vm.DepartmentName, "DepartmentName property did not return value from model.");
            Assert.AreEqual("DepartmentCode", vm.DepartmentCode, "DepartmentCode property did not return value from model.");

            // 更改属性的测试将更新模型并引发 PropertyChanged
            string lastProperty;
            vm.PropertyChanged += (sender, e) => { lastProperty = e.PropertyName; };

            lastProperty = null;
            vm.DepartmentName = "DepartmentName_NEW";
            Assert.AreEqual("DepartmentName", lastProperty, "Setting DepartmentName property did not raise correct PropertyChanged event.");
            Assert.AreEqual("DepartmentName_NEW", dep.DepartmentName, "Setting DepartmentName property did not update model.");

            lastProperty = null;
            vm.DepartmentCode = "DepartmentCode_NEW";
            Assert.AreEqual("DepartmentCode", lastProperty, "Setting DepartmentName property did not raise correct PropertyChanged event.");
            Assert.AreEqual("DepartmentCode_NEW", dep.DepartmentCode, "Setting DepartmentCode property did not update model.");
        }

        /// <summary>
        /// 验证 getter 是否反映模型中的更改
        /// </summary>
        [TestMethod]
        public void ModelChangesFlowToProperties()
        {
            // 测试 ViewModel 返回模型的当前值
            Department dep = new Department { DepartmentName = "DepartmentName", DepartmentCode = "DepartmentCode" };
            DepartmentViewModel vm = new DepartmentViewModel(dep);

            vm.DepartmentName = "DepartmentName_NEW";
            Assert.AreEqual("DepartmentName_NEW", dep.DepartmentName, "DepartmentName property is not fetching the value from the model.");
            vm.DepartmentCode = "DepartmentCode_NEW";
            Assert.AreEqual("DepartmentCode_NEW", dep.DepartmentCode, "DepartmentCode property is not fetching the value from the model.");
        }

        /// <summary>
        /// 验证在 null 无效时，是否引发 NullArgumentExceptions
        /// </summary>
        [TestMethod]
        public void CheckNullArgumentExceptions()
        {
            Utilities.CheckNullArgumentException(() => { new DepartmentViewModel(null); }, "department", "ctor");
        }
    }
}
