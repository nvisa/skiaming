// 版权所有(C) Microsoft Corporation。保留所有权利。

namespace Tests.EntityFramework
{
    using System.Diagnostics.CodeAnalysis;
    using EmployeeTracker.EntityFramework;
    using Microsoft.VisualStudio.TestTools.UnitTesting;
    using Tests.Model;

    /// <summary>
    /// 测试当未附加到 ObjectContext 时模型中的对象代理版本的修复行为
    /// </summary>
    [TestClass]
    [SuppressMessage("Microsoft.Design", "CA1001:TypesThatOwnDisposableFieldsShouldBeDisposable", Justification = "Context is disposed in test cleanup.")]
    public class DetachedProxyFixupTests : FixupTestsBase
    {
        /// <summary>
        /// 用于创建代理的上下文
        /// </summary>
        private EmployeeEntities context;

        /// <summary>
        /// 创建此测试所需的资源
        /// </summary>
        [TestInitialize]
        public void Setup()
        {
            this.context = new EmployeeEntities();

            // 单元测试在没有数据库的情况下运行，因此我们需要关闭 LazyLoading
            this.context.ContextOptions.LazyLoadingEnabled = false;
        }

        /// <summary>
        /// 释放用于此测试运行的所有资源
        /// </summary>
        [TestCleanup]
        public void Teardown()
        {
            this.context.Dispose();
        }

        /// <summary>
        /// 返回从 T 派生的更改跟踪代理
        /// </summary>
        /// <typeparam name="T">要创建的类型</typeparam>
        /// <returns>类型 T 的新实例</returns>
        protected override T CreateObject<T>()
        {
            return this.context.CreateObject<T>();
        }
    }
}
