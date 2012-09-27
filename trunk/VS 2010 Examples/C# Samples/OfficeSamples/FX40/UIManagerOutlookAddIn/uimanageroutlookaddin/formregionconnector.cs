// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。


using System;
using System.Runtime.InteropServices;
using Outlook = Microsoft.Office.Interop.Outlook;
using Microsoft.Vbe.Interop.Forms;
using System.Windows.Forms;
using System.Collections.Generic;
using System.Diagnostics;
using System.Reflection;

// 需要添加对 Microsoft.Vbe.Interop.Forms 的引用。
// COM 选项卡: Microsoft Forms 2.0 对象库(如有多个对象库，则为第一个)。
namespace UiManagerOutlookAddIn
{

    [ComVisible(true)]
    [Guid("38F28415-204F-479a-B9B2-A386A462F7DE")]
    [ProgId("UiManager.FormRegionConnector")]
    public class FormRegionConnector : Outlook.FormRegionStartup
    {

        #region 字段

        private const String _formRegionName = "SimpleFormRegion";

        #endregion


        #region FormRegionStartup 实现

        // 此方法由于其 Office 参数的缘故不是 CLSCompliant。
        [CLSCompliant(false)]
        public object GetFormRegionStorage(
            string FormRegionName, object Item, int LCID,
            Outlook.OlFormRegionMode FormRegionMode, 
            Outlook.OlFormRegionSize FormRegionSize)
        {
            Application.DoEvents();
            switch (FormRegionName)
            {
                case _formRegionName:
                    return Properties.Resources.SimpleFormRegionOfs;
                default:
                    return null;
            }
        }

        // 此方法由于其 Office 参数的缘故不是 CLSCompliant。
        [CLSCompliant(false)]
        public object GetFormRegionIcon(
            string FormRegionName, int LCID, Outlook.OlFormRegionIcon Icon)
        {
            return PictureConverter.ImageToPictureDisp(
                Properties.Resources.espressoCup);
        }

        public object GetFormRegionManifest(string FormRegionName, int LCID)
        {
            return Properties.Resources.SimpleFormRegionXml;
        }

        // 此方法由于其 Office 参数的缘故不是 CLSCompliant。
        [CLSCompliant(false)]
        public void BeforeFormRegionShow(Outlook.FormRegion FormRegion)
        {
            if (FormRegion != null)
            {
                // 为窗体区域控件创建新的包装， 
                // 并将其添加到我们的集合。
                Globals.ThisAddIn._uiElements.AttachFormRegion(
                    FormRegion.Inspector, new FormRegionControls(FormRegion));
            }
        }

        #endregion

    }
}
