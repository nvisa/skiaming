// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。


using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using UiManagerOutlookAddIn.AddinUtilities;

namespace UiManagerOutlookAddIn
{
    [ComVisible(true)]
    [ProgId("UiManager.SimpleControl")]
    [Guid("E2F1F0E8-254A-4ddc-A500-273D6EFB172B")]
    public partial class SimpleControl : UserControl
    {
        public SimpleControl()
        {
            InitializeComponent();
        }

        private const String _mailServiceGroup = "mailServiceGroup";

        private void closeCoffeeList_Click(object sender, EventArgs e)
        {
            // 清除并隐藏列表框。
            this._coffeeList.Items.Clear();
            this._coffeeGroup.Visible = false;

            // 令外接程序服务功能区按钮再次不可见。
            UserInterfaceContainer uiContainer =
                Globals.ThisAddIn._uiElements.GetUIContainerForUserControl(
                this);
            uiContainer.HideRibbonControl(_mailServiceGroup);
        }
    }
}
