// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Text;
using System.Globalization;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;
using Microsoft.VisualStudio.DebuggerVisualizers;
using System.Data.Linq.SqlClient;
using System.Windows.Forms;
using System.Linq.Expressions;
using System.Data.Linq.Provider;
using System.Linq;
using System.Data;
using System.Data.Linq;

[assembly: System.Diagnostics.DebuggerVisualizer(typeof(LinqToSqlQueryVisualizer.DialogChooser),
    typeof(LinqToSqlQueryVisualizer.SourceChooser),
    TargetTypeName = "System.Data.Linq.DataQuery`1, System.Data.Linq",
    Description = "Linq to SQL 调试器可视化工具")]

namespace LinqToSqlQueryVisualizer {

    internal struct ParameterText {
        public string Name;
        public string Value;
        public string SqlType;
    }

    internal struct SqlQueryText {
        public string Text;
        public ParameterText[] Params;
    }

    class SqlQueryInfo {
        SqlQueryText[] queries;

        public SqlQueryInfo() { 
        }

        public SqlQueryInfo(SqlQueryText[] queries) {
            this.queries = queries;
        }

        public SqlQueryText[] Queries {
            get { return this.queries; }
        }

        public void serialize(Stream stream) {
            BinaryFormatter formatter = new BinaryFormatter();
            formatter.Serialize(stream, this.queries.Length);
            foreach (SqlQueryText query in this.queries) {
                formatter.Serialize(stream, query.Text);
                formatter.Serialize(stream, query.Params.Length);
                foreach (ParameterText param in query.Params) {
                    formatter.Serialize(stream, param.Name);
                    formatter.Serialize(stream, param.Value);
                    formatter.Serialize(stream, param.SqlType);
                }
            }
        }

        public static SqlQueryInfo deserialize(Stream stream) {
            SqlQueryInfo result = new SqlQueryInfo();
            BinaryFormatter formatter = new BinaryFormatter();
            int nQueries = (int) formatter.Deserialize(stream);
            result.queries = new SqlQueryText[nQueries];
            for (int i=0; i<nQueries; i++) {
                SqlQueryText query;
                query.Text = (string)formatter.Deserialize(stream);
                int nParams = (int)formatter.Deserialize(stream);
                query.Params = new ParameterText[nParams];
                for (int j = 0; j < nParams; j++) {
                    ParameterText p;
                    p.Name = (string) formatter.Deserialize(stream);
                    p.Value = (string)formatter.Deserialize(stream);
                    p.SqlType = (string)formatter.Deserialize(stream);
                    query.Params[j] = p;
                }
                result.Queries[i] = query;
            }
            return result;
        }
    }

    public class Visualizer {

        private static SqlQueryText[] GetFullQueryInfo(DataContext dataContext, IQueryable query) {
            System.Data.Common.DbCommand dbCommand = dataContext.GetCommand(query);

            SqlQueryText[] result = new SqlQueryText[1];
            for (int i = 0, n = 1; i < n; i++) {
                result[i].Text = dbCommand.CommandText;
                int nParams = dbCommand.Parameters.Count ;
                result[i].Params = new ParameterText[nParams];
                for (int j = 0; j < nParams; j++) {
                    ParameterText param = new ParameterText();
                    System.Data.Common.DbParameter pInfo = dbCommand.Parameters[j];
                    param.Name = pInfo.ParameterName;
                    param.SqlType = pInfo.DbType.ToString();
                    object paramValue = pInfo.Value;
                    if (paramValue == null) {
                        param.Value = null;
                    } else {
                        param.Value = pInfo.Value.ToString();
                    }
                    result[i].Params[j] = param;
                }
            }
            return result;
        }

        /// <summary>
        /// 从 QueryVisualizer 调用此方法可将以下数据复制到流:
        /// 1. 字符串形式的查询表达式
        /// 2. SQL 查询文本/参数
        /// 3. 连接字符串
        /// </summary>
        /// <param name="query"> 要可视化的查询字符串 </param>
        /// <param name="outgoingData"> 用于封送到可视化工具的流 </param>
        /// 
        public static void StreamQueryInfo(DataContext dataContext, IQueryable query, Stream outgoingData) {
            BinaryFormatter formatter = new BinaryFormatter();
            if (dataContext == null) {
                formatter.Serialize(outgoingData, "None");
                formatter.Serialize(outgoingData, "No datacontext provided.");
                return;
            }
            Expression expr = query.Expression;
            if (expr == null) {
                formatter.Serialize(outgoingData, "None");
                formatter.Serialize(outgoingData, "Expression of the query is empty.");
                return;
            }
            formatter.Serialize(outgoingData, expr.ToString());

            try {
                SqlQueryInfo qi = new SqlQueryInfo(GetFullQueryInfo(dataContext, query));
                qi.serialize(outgoingData);
            } catch (Exception ex) {
                outgoingData.Position = 0;
                formatter.Serialize(outgoingData, "None");
                formatter.Serialize(outgoingData, string.Format(CultureInfo.CurrentUICulture, "Exception while serializing the query:\r\n{0}", ex.Message));
                return;
            }

            IDbConnection conn = dataContext.Connection;
            string connectionString = conn.ConnectionString;
            //需要检查连接字符串中的 |DataDirectory| 标记并替换为绝对路径，以允许
            if (connectionString.Contains("|DataDirectory|")) {
                connectionString = conn.ConnectionString.Replace(@"|DataDirectory|\", AppDomain.CurrentDomain.BaseDirectory);
            }
            // Linq To Sql 查询可视化工具使用相同的连接字符串。
            formatter.Serialize(outgoingData, connectionString);
        }

        /// <summary>
        /// 此方法是从常规查询可视化工具调用的。
        /// 它从流读取查询数据，
        ///在 QueryVisualizerFrom 中设置对应字段并显示查询数据。
        /// </summary>
        /// <param name="windowService">用于显示可视化工具对话框</param>
        /// <param name="rawStream">从提供程序/可视化工具代理发送的查询数据</param>
        public static void Display(IDialogVisualizerService windowService,Stream rawStream) {
            BinaryFormatter formatter = new BinaryFormatter();
            string expression = (string)formatter.Deserialize(rawStream);

            SqlQueryInfo qi = SqlQueryInfo.deserialize(rawStream);
            SqlQueryText[] infos = qi.Queries;

            string connectionString = (string)formatter.Deserialize(rawStream);

            QueryVisualizerForm form = new QueryVisualizerForm();
            form.SetTexts(expression, infos, connectionString);
            windowService.ShowDialog(form);
        }
    }
}
