// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。


using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;


namespace UiManagerOutlookAddIn.AddinUtilities
{
    // 此接口由于其 Office 属性的缘故不符合 CLS。
    [ComVisible(true)]
    [InterfaceType(ComInterfaceType.InterfaceIsDual)]
    [Guid("43189577-8667-4c8f-8167-EBF23CC285CB")]
    [CLSCompliant(false)]
    public interface IRibbonConnector
    {
        Microsoft.Office.Core.IRibbonUI Ribbon
        {
            get;
            set;
        }
    }


    // Regasm 不会注册仅包含接口的程序集。
    // 我们需要定义 COM 可创建的类以便获取类型库。
    // 我们不希望将此类用于任何目的，因为我们
    // 要在另一个程序集中实现接口。
    [ComVisible(true)]
    [ClassInterface(ClassInterfaceType.None)]
    [CLSCompliant(false)]
    public class RibbonConnectorPlaceholder : IRibbonConnector 
    {
        public Microsoft.Office.Core.IRibbonUI Ribbon
        {
            get { return null; }
            set { }
        }
    }

}
