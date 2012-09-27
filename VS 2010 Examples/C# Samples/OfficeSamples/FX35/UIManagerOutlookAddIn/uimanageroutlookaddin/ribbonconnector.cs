// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。


using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Text;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using Outlook = Microsoft.Office.Interop.Outlook;
using Office = Microsoft.Office;
using System.Globalization;
using UiManagerOutlookAddIn.AddinUtilities;

namespace UiManagerOutlookAddIn
{

    [ComVisible(true)]
    [Guid("66299133-E2CC-46c1-8C47-B73DA7203067")]
    [ProgId("UiManager.RibbonConnector")]
    public class RibbonConnector : 
        Office.Core.IRibbonExtensibility, IRibbonConnector 
    {

        #region 标准操作

        public RibbonConnector()
        {
        }

        // 此方法由于其 Office 参数的缘故不是 CLSCompliant。
        [CLSCompliant(false)]
        public void OnLoad(Office.Core.IRibbonUI ribbonUI)
        {
            this._ribbon = ribbonUI;
        }

        public string GetCustomUI(string RibbonID)
        {
            string xml = null;

            // 我们有两个不同的功能区自定义项: 一个用于任务
            // 检查器，另一个用于其他所有检查器。
            switch (RibbonID)
            {
                case _taskItemName:
                    xml = Properties.Resources.TaskRibbon;
                    break;
                default:
                    xml = Properties.Resources.SimpleRibbon;
                    break;
            }
            return xml;
        }

        // 功能区 XML 指定包含 sendList 控件的 addinServiceButtons 组
        // 在特定条件下可见。 
        // 此方法由于其 Office 参数的缘故不是 CLSCompliant。
        [CLSCompliant(false)]
        public bool GetVisible(Office.Core.IRibbonControl control)
        {
            if (control == null)
            {
                return false;
            }

            // 在集合中匹配此控件实例(取决于其检查器)，
            // 并返回缓存可见性状态的 
            // 当前值。
            Outlook.Inspector inspector = control.Context as Outlook.Inspector;
            UserInterfaceContainer uiContainer =
                Globals.ThisAddIn._uiElements.GetUIContainerForInspector(inspector);
            return uiContainer.IsControlVisible;
        }

        #endregion

        #region 字段

        private Office.Core.IRibbonUI _ribbon;


        private const String _taskItemName = "Microsoft.Outlook.Task";
        private const String _mailAddressee = "someone@example.com";
        private const String _orderName = "Coffee";
        private const String _ordersTextBoxName = "ordersTextBox";
        private static int _orderCount;

        #endregion


        #region OnToggleTaskPane

        // 此方法由于其 input 参数的缘故不是 CLSCompliant。
        [CLSCompliant(false)]
        public void OnToggleTaskPane(
            Office.Core.IRibbonControl control, bool isPressed)
        {
            // 切换自定义任务窗格的可见性。
            if (control != null)
            {
                // 查找此功能区的检查器，以便我们能够从集合中找到 
                // 对应的任务窗格。
                Outlook.Inspector inspector = 
                    (Outlook.Inspector)control.Context;
                Office.Core.CustomTaskPane taskpane =
                    Globals.ThisAddIn._uiElements.GetTaskPaneForInspector(
                    inspector);

                // 如果我们在有机会将此 
                // 检查器/任务窗格添加到集合中之前已被调用，则我们可以现在添加窗格。
                if (taskpane == null)
                {
                    taskpane = Globals.ThisAddIn.CreateTaskPane(inspector);
                }

                taskpane.Visible = isPressed;
            }
        }

        #endregion


        #region 按钮处理程序

        private String GetTextFromTaskPane(Outlook.Inspector inspector)
        {
            String coffeeText = null;

            if (inspector != null)
            {
                // 获取任务窗格中的用户控件。
                Office.Core.CustomTaskPane taskpane =
                    Globals.ThisAddIn._uiElements.GetTaskPaneForInspector(inspector);
                SimpleControl sc = (SimpleControl)taskpane.ContentControl;

                // 在任务窗格列表框中使用字符串撰写邮件正文。
                StringBuilder builder = new StringBuilder();
                foreach (string s in sc._coffeeList.Items)
                {
                    builder.AppendLine(s);
                }
                coffeeText = builder.ToString();
            }

            return coffeeText;
        }

        // 此方法由于其 Office 参数的缘故不是 CLSCompliant。
        [CLSCompliant(false)]
        public void OnSendList(Office.Core.IRibbonControl control)
        {
            if (control != null)
            {
                try
                {
                    Outlook.Inspector inspector =
                        (Outlook.Inspector)control.Context;
                    String coffeeText = GetTextFromTaskPane(inspector);

                    // 使用输入参数创建一个新的邮件，并发送该邮件。
                    Outlook._MailItem mi =
                        (Outlook._MailItem)
                        Globals.ThisAddIn.Application.CreateItem(
                        Outlook.OlItemType.olMailItem);
                    mi.Subject = _orderName;
                    mi.Body = coffeeText;
                    mi.To = _mailAddressee;
                    mi.Send();

                    // 更新窗体区域中的订单的计数。
                    UserInterfaceContainer uiContainer =
                        Globals.ThisAddIn._uiElements.GetUIContainerForInspector(
                        inspector);
                    CultureInfo cultureInfo = new CultureInfo("en-us");
                    uiContainer.FormRegionControls.SetControlText(
                        _ordersTextBoxName, (++_orderCount).ToString(cultureInfo));
                }
                catch (COMException ex)
                {
                    System.Diagnostics.Debug.WriteLine(ex.ToString());
                }
            }
        }

        #endregion


        #region IRibbonConnector 成员

        [CLSCompliant(false)]
        public Office.Core.IRibbonUI Ribbon
        {
            get { return _ribbon; }
            set { _ribbon = value; }
        }

        #endregion
    }
}
