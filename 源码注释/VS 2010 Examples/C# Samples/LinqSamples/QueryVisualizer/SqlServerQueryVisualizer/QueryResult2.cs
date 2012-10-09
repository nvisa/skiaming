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
    public partial class QueryResult2 : Form {
        public QueryResult2() {
            InitializeComponent();
        }

        public void SetDataSets(DataSet ds1, DataSet ds2) {
            this.dataGridView1.DataSource = ds1.Tables[0];
            this.dataGridView2.DataSource = ds2.Tables[0];
        }
    }
}