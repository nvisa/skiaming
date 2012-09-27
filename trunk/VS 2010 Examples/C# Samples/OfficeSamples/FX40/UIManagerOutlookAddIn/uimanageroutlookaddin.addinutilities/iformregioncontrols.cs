// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。


using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;
using Outlook = Microsoft.Office.Interop.Outlook;


namespace UiManagerOutlookAddIn.AddinUtilities
{
    // 此接口由于其 Office 属性的缘故不符合 CLS。
    [ComVisible(true)]
    [InterfaceType(ComInterfaceType.InterfaceIsDual)]
    [Guid("53ED8FA5-DBAD-40c4-8068-F20E7858DEB6")]
    [CLSCompliant(false)]
    public interface IFormRegionControls
    {
        Outlook.Inspector Inspector
        {
            get;
            set;
        }

        void SetControlText(String controlName, String text);
    }
}
