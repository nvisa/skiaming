// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Word = Microsoft.Office.Interop.Word;
using System.Runtime.InteropServices;

namespace TaskPaneWordAddIn
{
    public partial class SimpleControl : UserControl
    {
        public SimpleControl()
        {
            InitializeComponent();
        }

        private void insertButton_Click(object sender, EventArgs e)
        {
            try
            {
                if (!String.IsNullOrEmpty(insertTextBox.Text))
                {
                    Word.Document document = Globals.ThisAddIn.Application.ActiveDocument;
                    object start = 0;
                    object end = 0;
                    Word.Range range = (Word.Range)document.Range(ref start, ref end);
                    range.InsertAfter(insertTextBox.Text);
                }
            }
            catch (COMException ex)
            {
                System.Diagnostics.Debug.WriteLine(ex.ToString());
            }
        }
    }
}
