// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。

using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Xml.Linq;
using Microsoft.VisualStudio.Tools.Applications.Runtime;
using Excel = Microsoft.Office.Interop.Excel;
using Office = Microsoft.Office.Core;

namespace DocumentProtectionExcel
{
    public partial class Sheet2
    {
        /// <summary>
        /// 一个字符串，用于存储 usernameNamedRange 控件中的 
        /// 原始值。
        /// </summary>
        private string userName;

        /// <summary>
        /// 处理工作表的 Startup 事件。当此事件激发时， 
        /// 将检索 usernameNamedRange 控件的值
        /// 并将其保存到 userName 字段中。
        /// </summary>
        /// <param name="sender">未使用。</param>
        /// <param name="e">未使用。</param>
        private void Sheet2_Startup(object sender, System.EventArgs e)
        {
            // 获取 userNameNamedRange 初始值
            userName = this.usernameNamedRange.Value2.ToString();
        }

        private void Sheet2_Shutdown(object sender, System.EventArgs e)
        {
        }

        /// <summary>
        /// 处理 NamedRange 更改事件。当此事件激发时， 
        /// 将还原 NamedRange 控件的原始值， 
        /// 并将显示一个消息框，指示用户无权 
        /// 更改该值。
        /// </summary>
        /// <param name="sender">未使用。</param>
        /// <param name="e">未使用。</param>
        private void usernameNamedRange_Change(Microsoft.Office.Interop.Excel.Range Target)
        {
            try
            {
                // 关闭事件处理程序 
                this.usernameNamedRange.Change -= new Microsoft.Office.Interop.Excel.DocEvents_ChangeEventHandler(this.usernameNamedRange_Change);
                this.usernameNamedRange.Value2 = userName;

                MessageBox.Show("You are not authorized to change this value.",
                    "Document Protection Techniques - Excel",
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Information,
                    MessageBoxDefaultButton.Button1);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message,
                    "Error handling NamedRange change event.",
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Error,
                    MessageBoxDefaultButton.Button1);
            }
            finally
            {
                // 打开事件处理程序
                this.usernameNamedRange.Change += new Microsoft.Office.Interop.Excel.DocEvents_ChangeEventHandler(this.usernameNamedRange_Change);
            }

        }


        #region VSTO 设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 请勿
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InternalStartup()
        {
            this.usernameNamedRange.Change += new Microsoft.Office.Interop.Excel.DocEvents_ChangeEventHandler(this.usernameNamedRange_Change);
            this.Startup += new System.EventHandler(Sheet2_Startup);
            this.Shutdown += new System.EventHandler(Sheet2_Shutdown);
        }

        #endregion

    }
}
