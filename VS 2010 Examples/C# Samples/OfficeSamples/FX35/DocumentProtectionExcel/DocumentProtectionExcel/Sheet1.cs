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
    public partial class Sheet1
    {
        #region 属性
        /// <summary>
        /// 返回工作表是否受到保护。
        /// </summary>
        /// <value>
        /// 如果工作表受到保护，则返回 true；
        /// 否则返回 false。
        /// </value>
        internal bool IsProtected
        {
            get
            {
                return this.ProtectContents;
            }
        }
        #endregion

        #region 方法
        /// <summary>
        /// 保护工作表但不设置任何密码。
        /// </summary>
        internal void ProtectSheet()
        {
            // 确保工作表尚未受到保护。
            if (this.IsProtected)
                throw new InvalidOperationException();

            // 保护工作表，使其为只读，并且 
            // 不用任何密码即可取消保护。
            this.Protect(missing, missing, missing, missing,
                        missing, missing, missing, missing,
                        missing, missing, missing, missing,
                        missing, missing, missing, missing);
        }

        /// <summary>
        /// 不使用密码取消对工作表的保护。
        /// </summary>
        internal void UnprotectSheet()
        {
            // 确保工作表尚未取消保护。
            if (!this.IsProtected)
                throw new InvalidOperationException();

            // 不使用密码取消对工作表的保护。
            this.Unprotect(missing);
        }

        #endregion

        /// <summary>
        /// 处理工作表的 Startup 事件。当此事件激发时， 
        /// 将首先取消对工作表的保护，然后将 customerListObject 
        /// 绑定到 customerBindingSource，随后再保护 
        /// 工作表。
        /// </summary>
        /// <param name="sender">未使用。</param>
        /// <param name="e">未使用。</param>
        private void Sheet1_Startup(object sender, System.EventArgs e)
        {
            try
            {
                // 取消对工作表的保护
                this.UnprotectSheet();

                // 创建 ListObject 并绑定到 BindingSource。
                customerListObject.AutoSetDataBoundColumnHeaders = true;
                customerListObject.SetDataBinding(Globals.ThisWorkbook.custBindingSource, "", "firstName", "lastName", "userName");
            }
            finally
            {
                // 保护工作表
                this.ProtectSheet();
            }
        }

        private void Sheet1_Shutdown(object sender, System.EventArgs e)
        {
        }

        #region VSTO 设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 请勿
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InternalStartup()
        {
            this.Startup += new System.EventHandler(Sheet1_Startup);
            this.Shutdown += new System.EventHandler(Sheet1_Shutdown);
        }

        #endregion

    }
}
