// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
//版权所有(C) Microsoft Corporation。保留所有权利。

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Data.Linq.SqlClient;
using System.Drawing;
using System.Globalization;
using System.Text;
using System.Windows.Forms;

namespace LinqToSqlQueryVisualizer {
   
    public partial class QueryVisualizerForm : Form {

        private SqlQueryText[] queryInfos;
        private string connection;
        private bool uiInitialized;
        private bool twoQueries;
        private string sql1; // 用于查询 1 的 Sql 文本(可由用户修改)
        private string sql2; // 用于查询 2 的 Sql 文本(可由用户修改)

        // 用于当前选定查询的 sql 文本
        private string currentSql {
            get { 
                return this.radioQuery1.Checked ? sql1 : sql2; 
            }
            set {
                if (this.radioQuery1.Checked) {
                    sql1 = value;
                } else {
                    sql2 = value;
                }
            }
        }

        // 用于其他查询的 sql 文本
        private string otherSql {
            get { 
                return this.radioQuery1.Checked ? sql2 : sql1; 
            }
            set {
                if (this.radioQuery1.Checked) {
                    sql2 = value;
                } else {
                    sql1 = value;
                }
            }
        }

        public QueryVisualizerForm() {
            InitializeComponent();
        }

        /// <summary>
        /// 使用查询的数据设置此窗体
        /// </summary>
        /// <param name="expression">表达式文本形式的查询</param>
        /// <param name="infos">查询的 Sql 文本和参数说明</param>
        /// <param name="connectionString">connectionString 字符串</param>
        internal void SetTexts(string expression, SqlQueryText[] infos, string connectionString) {
            this.txtExpression.Text = expression;
          
            this.queryInfos = infos;
            this.connection = connectionString;
            this.radioQuery1.Checked = true;
            if (this.queryInfos.Length > 1) {
                this.twoQueries = true;
                this.radioQuery1.Visible = true;
                this.radioQuery2.Visible = true;
            } else {
                this.twoQueries = false;
            }
            this.chkUseOriginal.Checked = false;
            this.btnQuery.Visible = true;
            this.InitSqlTexts();
            this.FillSqlText();
            this.uiInitialized = true;
        }


        /// <summary>
        /// 使用原始 sql 文本填充 sql1 和 sql2
        /// </summary>
        private void InitSqlTexts() {
            SqlQueryText qt1 = this.queryInfos[0];
            this.sql1 = Utils.GetQueryTextWithParams(qt1);
            if (twoQueries) {
                SqlQueryText qt2 = this.queryInfos[1];
                this.sql2 = Utils.GetQueryTextWithParams(qt2);
            }
        }

        /// <summary>
        /// 填充 UI 字段 txtSql
        /// 如果选中“原始查询”:
        ///   使用相应的查询文本填充字段 txtSql.Text，并添加参数
        /// 否则:
        ///   使用 sql 填充文本字段 txtSql.Text
        /// </summary>
        private void FillSqlText() {
            if (this.chkUseOriginal.Checked) {
                SqlQueryText qt = this.queryInfos[0];
                if (this.radioQuery2.Checked) {
                    qt = this.queryInfos[1];
                }
                String s = qt.Text + "\r\n";
                s += "-------------------------------";
                for (int i = 0; i < qt.Params.Length; i++) {
                    ParameterText param = qt.Params[i];
                    if (param.SqlType == "String") {
                        s += "\r\n" + param.Name + " [" + param.SqlType + "]: " + Utils.QuoteString(param.Value);
                    } else {
                        s += "\r\n" + param.Name + " [" + param.SqlType + "]: " + param.Value;
                    }
                }
                this.txtSql.Text = s;
            } else {
                this.txtSql.Text = this.currentSql;
            }
        }

        private void btnQuery_Click(object sender, EventArgs e) {
            this.Cursor = Cursors.WaitCursor;
            
            // 保存当前查询
            if (!this.chkUseOriginal.Checked) {
                this.currentSql = this.txtSql.Text;
            }

            // 为查询结果准备 DataSet
            DataSet ds1 = new DataSet() { Locale = CultureInfo.CurrentUICulture };
            DataSet ds2 = new DataSet() { Locale = CultureInfo.CurrentUICulture };

            if (chkUseOriginal.Checked) {
                QueryExecution.ExecuteOriginalQueries(ds1, ds2, this.queryInfos, this.connection);
            } else if (this.twoQueries) {
                QueryExecution.ExecuteQueries(ds1, ds2, this.sql1, this.sql2, this.connection);
            } else {
                QueryExecution.ExecuteQuery(ds1, this.sql1, this.connection);
            }

            if (this.twoQueries) {
                QueryResult2 form = new QueryResult2();
                form.SetDataSets(ds1, ds2);
                this.Cursor = Cursors.Default;
                form.ShowDialog();
            } else {
                QueryResult form = new QueryResult();
                form.SetDataSet(ds1);
                this.Cursor = Cursors.Default;
                form.ShowDialog();
            }
        }

        private void chkIncludeParams_CheckedChanged(object sender, EventArgs e) {
            if (!uiInitialized) return;
            // “新建模式”为“使用原始”时保存更改
            if (this.chkUseOriginal.Checked) {
                this.currentSql = this.txtSql.Text;
            }
            this.txtSql.ReadOnly = this.chkUseOriginal.Checked;
            this.FillSqlText();
        }

        private void radioQuery1_CheckedChanged(object sender, EventArgs e) {
            if (!uiInitialized) return;
            // 保存查询文本
            if (!this.chkUseOriginal.Checked) {
                this.otherSql = this.txtSql.Text;
            }
            this.FillSqlText();
        }

    }
}