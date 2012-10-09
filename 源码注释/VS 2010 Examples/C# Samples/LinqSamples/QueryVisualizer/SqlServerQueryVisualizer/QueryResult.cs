// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
//版权所有(C) Microsoft Corporation。保留所有权利。

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace LinqToSqlQueryVisualizer {
    public partial class QueryResult : Form {

        public QueryResult() {
            InitializeComponent();
        }

        public void SetDataSet(DataSet ds) {
            this.dataGridView1.DataSource = ds.Tables[0];
        }
    }
}