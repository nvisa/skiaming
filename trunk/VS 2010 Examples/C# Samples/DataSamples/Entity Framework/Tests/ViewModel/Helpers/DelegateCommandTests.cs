// 版权所有(C) Microsoft Corporation。保留所有权利。

namespace Tests.ViewModel.Helpers
{
    using System;
    using EmployeeTracker.ViewModel.Helpers;
    using Microsoft.VisualStudio.TestTools.UnitTesting;

    /// <summary>
    /// DelegateCommand 的单元测试
    /// </summary>
    [TestClass]
    public class DelegateCommandTests
    {
        /// <summary>
        /// 没有为 CanExecute 指定任何谓词的构造命令
        /// 验证 CanExecute 始终为 true，并且该命令在指定 null 时执行
        /// </summary>
        [TestMethod]
        public void ExecuteNoPredicateWithNull()
        {
            bool called = false;
            DelegateCommand cmd = new DelegateCommand((o) => called = true);
            Assert.IsTrue(cmd.CanExecute(null), "Command should always be able to execute when no predicate is supplied.");
            cmd.Execute(null);
            Assert.IsTrue(called, "Command did not run supplied Action.");
        }

        /// <summary>
        /// 带有 null 谓词的构造命令
        /// </summary>
        [TestMethod]
        public void ConstructorAcceptsNullPredicate()
        {
            DelegateCommand cmd = new DelegateCommand((o) => { }, null);
            Assert.IsTrue(cmd.CanExecute(null), "Command with null specified for predicate should always be able to execute.");
        }

        /// <summary>
        /// 没有为 CanExecute 指定任何谓词的构造命令
        /// 验证 CanExecute 始终为 true，并且该命令在指定对象时执行
        /// </summary>
        [TestMethod]
        public void ExecuteNoPredicateWithArgument()
        {
            bool called = false;
            DelegateCommand cmd = new DelegateCommand((o) => called = true);
            Assert.IsTrue(cmd.CanExecute("x"), "Command should always be able to execute when no predicate is supplied.");
            cmd.Execute("x");
            Assert.IsTrue(called, "Command did not run supplied Action.");
        }

        /// <summary>
        /// 为 CanExecute 指定了“true”谓词的构造命令
        /// 验证 CanExecute 并验证该命令是否执行
        /// </summary>
        [TestMethod]
        public void ExecuteWithPredicate()
        {
            bool called = false;
            DelegateCommand cmd = new DelegateCommand((o) => called = true, (o) => true);
            Assert.IsTrue(cmd.CanExecute(null), "Command should be able to execute when predicate returns true.");
            cmd.Execute(null);
            Assert.IsTrue(called, "Command did not run supplied Action.");
        }

        /// <summary>
        /// 为 CanExecute 指定了“false”谓词的构造命令
        /// 验证 CanExecute 并验证是否正在尝试执行引发
        /// </summary>
        [TestMethod]
        public void AttemptExecuteWithFalsePredicate()
        {
            bool called = false;
            DelegateCommand cmd = new DelegateCommand((o) => called = true, (o) => false);
            Assert.IsFalse(cmd.CanExecute(null), "Command should not be able to execute when predicate returns false.");

            try
            {
                cmd.Execute(null);
            }
            catch (InvalidOperationException)
            {
            }

            Assert.IsFalse(called, "Command should not have run supplied Action.");
        }

        /// <summary>
        /// 验证在 null 无效的情况下是否引发 NullArgumentExceptions
        /// </summary>
        [TestMethod]
        public void CheckNullArgumentExceptions()
        {
            Utilities.CheckNullArgumentException(() => { new DelegateCommand(null); }, "execute", "ctor");
        }
    }
}
