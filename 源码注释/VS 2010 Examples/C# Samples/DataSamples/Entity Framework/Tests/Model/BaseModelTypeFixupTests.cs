// 版权所有(C) Microsoft Corporation。保留所有权利。

namespace Tests.Model
{
    using System;
    using Microsoft.VisualStudio.TestTools.UnitTesting;

    /// <summary>
    /// 测试模型中对象的 Pure POCO 版本的修复行为
    /// </summary>
    [TestClass]
    public class BaseModelTypeFixupTests : FixupTestsBase
    {
        /// <summary>
        /// 返回从默认构造函数创建的 T 的实例
        /// </summary>
        /// <typeparam name="T">要创建的类型</typeparam>
        /// <returns>类型 T 的新实例</returns>
        protected override T CreateObject<T>()
        {
            return Activator.CreateInstance<T>();
        }
    }
}
