// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。


using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using Outlook = Microsoft.Office.Interop.Outlook;
using Office = Microsoft.Office.Core;
using Microsoft.Vbe.Interop.Forms;
using UiManagerOutlookAddIn.AddinUtilities;

namespace UiManagerOutlookAddIn
{
    // FormRegionControls 类包装对自定义窗体区域上
    // 的控件的引用。我们将为每个打开的自定义窗体区域
    // 实例化此类的新实例。这样，我们可以确保
    // 任何 UI 响应均特定于此实例(例如，当用户单击
    // 命令按钮时，我们可以获取同一实例的文本框文本)。
    public class FormRegionControls : IFormRegionControls
    {

        #region 字段

        private UserForm _form;
        private Outlook.Inspector _inspector;
        private Outlook.OlkListBox _coffeeList;
        private Microsoft.Vbe.Interop.Forms.TextBox _ordersText;
        private String[] _listItems = 
            {"Colombia Supremo", "Ethiopia Longberry Harrar", 
            "Sumatra Mandehling", "Mocha Java" , "Jamaica Blue Mountain", 
            "Costa Rica Tarrazu", "Monsooned Malabar" };
        private const String _formRegionListBoxName = "coffeeListBox";
        private const String _ordersTextBoxName = "ordersTextBox";
        private const String _mailServiceGroup = "mailServiceGroup";

        [CLSCompliant(false)]
        public Outlook.Inspector Inspector
        {
            get { return _inspector; }
            set { _inspector = value; }
        }

        #endregion


        // 此方法由于其 input 参数的缘故不是 CLSCompliant。
        [CLSCompliant(false)]
        public FormRegionControls(Outlook.FormRegion region)
        {
            if (region != null)
            {
                try
                {
                    // 缓存对此区域及其 
                    // 检查器以及此区域上的控件的引用。
                    _inspector = region.Inspector;
                    _form = region.Form as UserForm;
                    _ordersText = _form.Controls.Item(_ordersTextBoxName) 
                        as Microsoft.Vbe.Interop.Forms.TextBox;
                    _coffeeList = _form.Controls.Item(_formRegionListBoxName) 
                        as Outlook.OlkListBox;

                    // 使用任意字符串填充此列表框。
                    for (int i = 0; i < _listItems.Length; i++)
                    {
                        _coffeeList.AddItem(_listItems[i], i);
                    }
                    _coffeeList.Change += new
                        Outlook.OlkListBoxEvents_ChangeEventHandler(
                        _coffeeList_Change);
                }
                catch (COMException ex)
                {
                    System.Diagnostics.Debug.WriteLine(ex.ToString());
                }
            }
        }


        // 用户已经更改自定义窗体区域中列表框内的 
        // 选择。
        private void _coffeeList_Change()
        {
            UserInterfaceContainer uiContainer = 
                Globals.ThisAddIn._uiElements.GetUIContainerForInspector(
                _inspector);

            // 令外接程序服务功能区按钮可见。
            uiContainer.ShowRibbonControl(_mailServiceGroup);

            // 获取任务窗格中的用户控件，并将 
            // 在窗体区域的列表框中选择的项目的文本复制到任务窗格的
            // 列表框。
            SimpleControl sc = 
                (SimpleControl)uiContainer.TaskPane.ContentControl;
            sc._coffeeGroup.Visible = true;
            sc._coffeeList.Items.Add(_coffeeList.Text);
        }


        // 设置窗体区域中的订单 TextBox 的文本值。
        public void SetControlText(String controlName, String text)
        {
            switch (controlName)
            {
                case _ordersTextBoxName :
                    _ordersText.Text = text;
                    break;
            }
        }

    }
}
