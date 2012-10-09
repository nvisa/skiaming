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
using Office = Microsoft.Office.Core;
using Word = Microsoft.Office.Interop.Word;

namespace DataContentControls
{
    public partial class ThisDocument
    {
        private ActionsPaneControl1 myActionsPane = new ActionsPaneControl1();
        private void ThisDocument_Startup(object sender, System.EventArgs e)
        {
            // TODO: 删除此代码行以移除“northwindDataSet.Employees”的默认 AutoFill。
            if (this.NeedsFill("northwindDataSet"))
            {
                this.employeesTableAdapter.Fill(this.northwindDataSet.Employees);
           }
            this.ActionsPane.Controls.Add(myActionsPane); 
        }

        private void ThisDocument_Shutdown(object sender, System.EventArgs e)
        {
        }

        #region VSTO 设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 请勿
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InternalStartup()
        {
            this.Shutdown += new System.EventHandler(this.ThisDocument_Shutdown);
            this.Startup += new System.EventHandler(this.ThisDocument_Startup);

        }

        #endregion
    }
}
