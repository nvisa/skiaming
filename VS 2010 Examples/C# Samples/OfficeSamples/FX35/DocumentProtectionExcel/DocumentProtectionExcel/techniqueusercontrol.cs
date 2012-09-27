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
using System.Globalization;

namespace DocumentProtectionExcel
{
    /// <summary>
    /// “操作”窗格的用户控件，它允许
    /// 用户操作文档中显示的数据。
    /// </summary>
    public partial class TechniqueUserControl : UserControl
    {
        /// <summary>
        /// 初始化组件并将 dataDataGridView 绑定到数据源。
        /// </summary>
        public TechniqueUserControl()
        {
            InitializeComponent();
            // 将 dataDataGridView 控件绑定到数据源。
            this.dataDataGridView.DataSource = Globals.ThisWorkbook.custBindingSource;
        }

        /// <summary>
        /// 将值写入 dateDateTimePicker 控件，将值写入
        /// 只读的 dateTextBox，方法是将该控件的 ReadOnly 属性更改为 False，随后 
        /// 设置 Text 属性并还原属性值。
        /// </summary>
        /// <param name="sender">未使用。</param>
        /// <param name="e">未使用。</param>
        private void dateDateTimePicker_ValueChanged(object sender, EventArgs e)
        {
            try
            {
                // 将 dateDateTimePicker 值写入 dateNamedRange 
                Globals.Sheet1.dateNamedRange.Value2 = dateDateTimePicker.Value;

                try
                {
                    // 取消对 Sheet1 上的 TextBox 值的保护。
                    Globals.Sheet1.dateTextBox.ReadOnly = false;
                    // 将 dateDateTimePicker 值以 ShortDatePattern 模式写入 dateTextBox。
                    Globals.Sheet1.dateTextBox.Text = dateDateTimePicker.Value.ToString("d", DateTimeFormatInfo.CurrentInfo);
                }
                finally
                {
                    // 保护 Sheet1 上的 TextBox 值。
                    Globals.Sheet1.dateTextBox.ReadOnly = true;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message,
                        "Error changing dateNamedRange or dateTextBox value.",
                        MessageBoxButtons.OK,
                        MessageBoxIcon.Error,
                        MessageBoxDefaultButton.Button1);
            }

        }
    }
}
