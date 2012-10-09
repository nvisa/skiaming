// 版权所有(C) Microsoft Corporation。保留所有权利。

namespace Tests.EntityFramework
{
    using System.Diagnostics.CodeAnalysis;
    using System.Globalization;
    using EmployeeTracker.EntityFramework;
    using EmployeeTracker.Model;
    using Microsoft.VisualStudio.TestTools.UnitTesting;
    using Tests.Model;

    /// <summary>
    /// 测试附加到 ObjectContext 的模型中的对象代理版本的修复行为
    /// </summary>
    [TestClass]
    [SuppressMessage("Microsoft.Design", "CA1001:TypesThatOwnDisposableFieldsShouldBeDisposable", Justification = "Context is disposed in test cleanup.")]
    public class AttachedProxyFixupTests : FixupTestsBase
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
        /// 返回从 T 派生并附加到 ObjectContext 的更改跟踪代理
        /// </summary>
        /// <typeparam name="T">要创建的类型</typeparam>
        /// <returns>类型 T 的新实例</returns>
        protected override T CreateObject<T>()
        {
            T obj = this.context.CreateObject<T>();

            Employee e = obj as Employee;
            if (e != null)
            {
                this.context.Employees.AddObject(e);
                return obj;
            }

            Department d = obj as Department;
            if (d != null)
            {
                this.context.Departments.AddObject(d);
                return obj;
            }

            ContactDetail c = obj as ContactDetail;
            if (c != null)
            {
                this.context.ContactDetails.AddObject(c);
                return obj;
            }
           
            Assert.Fail(string.Format(CultureInfo.InvariantCulture, "Need to update AttachedProxyFixupTests.CreateObject to be able to attach objects of type {0}.", obj.GetType().Name));
            return null;
        }
    }
}
