// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Office = Microsoft.Office.Core;

namespace DataContentControls
{
    partial class ActionsPaneControl1 : UserControl
    {
        public ActionsPaneControl1()
        {
            InitializeComponent();
        }

        private void Button1_Click(object sender, EventArgs e)
        {
            Globals.ThisDocument.employeesBindingSource.MovePrevious();
        }

        private void Button2_Click(object sender, EventArgs e)
        {
            Globals.ThisDocument.employeesBindingSource.MoveNext();
        }

        private void Button3_Click(object sender, EventArgs e)
        {
            int currentIndex = Globals.ThisDocument.employeesBindingSource.Position;
            int foundIndex = Globals.ThisDocument.employeesBindingSource.Find("EmployeeID", TextBox1.Text);
            if (foundIndex < 0)
            {
                // 由于未能找到所输入的值，因此提示用户输入有效的 ID                
                MessageBox.Show("Please enter a valid ID!");
                Globals.ThisDocument.employeesBindingSource.Position = currentIndex;
            }
            else
                //移动至找到的记录
                Globals.ThisDocument.employeesBindingSource.Position = foundIndex;
    
        }

        private void Button4_Click(object sender, EventArgs e)
        {
            Globals.ThisDocument.plainTextContentControl4.DataBindings["Text"].WriteValue();
            Globals.ThisDocument.employeesBindingSource.EndEdit();
            Globals.ThisDocument.employeesTableAdapter.Update(Globals.ThisDocument.northwindDataSet.Employees);
            MessageBox.Show("Title Updated");
        }
    }
}
