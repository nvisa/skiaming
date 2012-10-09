// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。


namespace Tests
{
    using System;
    using System.Globalization;
    using Microsoft.VisualStudio.TestTools.UnitTesting;

    /// <summary>
    /// 用于单元测试的静态 helper 方法
    /// </summary>
    public static class Utilities
    {
        /// <summary>
        /// 验证所提供操作是否引发 ArgumentNullException
        /// 在未引发异常时执行 Assert.Fail
        /// </summary>
        /// <param name="call">应引发的操作</param>
        /// <param name="parameter">应在异常中确定的参数</param>
        /// <param name="method">用于日志记录用途的方法名称</param>
        public static void CheckNullArgumentException(Action call, string parameter, string method)
        {
            if (call == null)
            {
                throw new ArgumentNullException("call");
            }

            if (parameter == null)
            {
                throw new ArgumentNullException("parameter");
            }

            if (method == null)
            {
                throw new ArgumentNullException("method");
            }

            try
            {
                call();
                Assert.Fail(string.Format(CultureInfo.InvariantCulture, "Supplying null '{0}' argument to '{1}' did not throw.", parameter, method));
            }
            catch (ArgumentNullException ex)
            {
                Assert.AreEqual(parameter, ex.ParamName, string.Format(CultureInfo.InvariantCulture, "'ArgumentNullException.ParamName' wrong when supplying null '{0}' argument to '{1}'.", parameter, method));
            }
        }
    }
}
