// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
//版权所有(C) Microsoft Corporation。保留所有权利。

using Microsoft.VisualStudio.DebuggerVisualizers;
using System;
using System.Collections.Generic;
using System.Text;
using System.Data;
using System.Data.Linq;
using System.Data.Linq.SqlClient;
using System.Data.Linq.Provider;
using System.Data.SqlClient;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Runtime.Serialization.Formatters.Binary;
using System.Windows.Forms;


namespace LinqToSqlQueryVisualizer {


    /// <summary>
    /// 常规查询可视化工具的可视化工具代理
    /// 它负责将查询序列化为流
    /// 它将此任务委托给相关的特定于提供程序的查询可视化工具帮助器
    /// </summary>
    public class SourceChooser : VisualizerObjectSource {
        public override object CreateReplacementObject(object target, Stream incomingData) {
            return base.CreateReplacementObject(target, incomingData);
        }
        public override void TransferData(object target, Stream incomingData, Stream outgoingData) {
            base.TransferData(target, incomingData, outgoingData);
        }

        /// <summary>
        /// 此方法需要将有关要可视化的对象的信息写入流，
        /// 而该流随后将发送到可视化工具。
        /// 此实现可从查询中检索提供程序，并查找 QueryVisualizer 特性。
        /// 该特性包含特定于提供程序的查询可视化工具帮助器的程序集和类名。
        /// 将这些数据写入流，然后加载并调用此类，以便对查询执行
        /// 实际序列化操作。
        /// </summary>
        /// <param name="target"> 要序列化的对象，应为查询</param>
        /// <param name="outgoingData">接收有关查询的信息的流</param>
        public override void GetData(object target, Stream outgoingData) {
            SerializeTheQuery(target, outgoingData);
        }

        private static void Error(Stream str, string message) {
            BinaryFormatter formatter = new BinaryFormatter();
            formatter.Serialize(str, "None");
            formatter.Serialize(str, message);
            return;
        }

        /// <summary>
        /// 单元测试将使用此静态版本
        /// </summary>
        /// <param name="target"></param>
        /// <param name="outgoingData"></param>
        public static void SerializeTheQuery(object target, Stream stream) {
            // 获取查询
            IQueryable query = target as IQueryable;
            if (query == null) {
                Error(stream, "Query visualizer invoked on non-IQueryable target.");
                return;
            }

            //获取提供程序
            Type tQueryImpl = query.GetType();
            FieldInfo fiContext = tQueryImpl.GetField("context", BindingFlags.NonPublic | BindingFlags.Instance);
            if (fiContext == null) {
                Error(stream, "Query field 'context' not found in type " + tQueryImpl.ToString() + ".");
                return;
            }

            Object objProvider = fiContext.GetValue(query);
            if (objProvider == null) {
                Error(stream, "Query field 'context' returned null.");
                return;
            }

            System.Data.Linq.DataContext dataContext = objProvider as System.Data.Linq.DataContext;
            if (dataContext == null) {
                Error(stream, "Query is not against a DataContext.");
                return;
            }

            //调用可视化工具以序列化查询信息
            Visualizer.StreamQueryInfo(dataContext, query, stream);
        }
    }


    /// <summary>
    /// 应定义可视化工具 UI/行为的类
    /// 其实现将它委托给特定于提供程序的查询可视化工具
    /// </summary>
    public class DialogChooser : DialogDebuggerVisualizer {

        /// <summary>
        /// 查询信息的格式和所需的 UI 通常取决于
        /// 该查询使用的 Linq to SQLq 提供程序。
        /// 因此，在此常规查询可视化工具中，我们只从流读取特定查询
        /// 可视化工具的程序集和类，并调用此类上的方法“Display”，然后该方法将
        /// 读取查询信息，并显示 UI。
        /// </summary>
        /// <param name="windowService"> 用于显示 UI </param>
        /// <param name="objectProvider"> 用于从可视化工具代理检索数据(以流的形式) </param>
        protected override void Show(IDialogVisualizerService windowService, IVisualizerObjectProvider objectProvider) {
            Stream rawStream = objectProvider.GetData();

            Visualizer.Display(windowService, rawStream);
        }
        public static void TestShow(object elementToVisualize) {
            VisualizerDevelopmentHost visualizerHost = new VisualizerDevelopmentHost(elementToVisualize, typeof(DialogChooser), typeof(SourceChooser));
            visualizerHost.ShowVisualizer();
        }

    }

    internal static class Utils {

        internal static string QuoteString(string raw) {
            return "'" + raw.Replace("'", "''") + "'";
        }

        /// <summary>
        /// 将 sql 查询文本(其中包含参数名)
        /// 和有关参数(SqlType 和 .ToString() 提供的值)的信息
        /// 转换成一个 sql 字符串(其中包含值的文本表示形式)。
        /// 执行该字符串应与执行原始查询相同，但在
        /// 个别情况下除外(例如，字符串中包含参数名，给定的小数精度过高)
        /// </summary>
        /// <param name="qt">查询文本和有关参数的信息</param>
        /// <returns>要执行的 sql 字符串</returns>
        internal static string GetQueryTextWithParams(SqlQueryText qt) {
            string s = qt.Text;
            for (int i=qt.Params.Length-1; i >= 0; i--){
                ParameterText param = qt.Params[i];
                string val;
                switch (param.SqlType.ToString()) {
                    case "String":
                    case "Guid":
                    case "DateTime":
                        val = QuoteString(param.Value);
                        break;
                    case "Boolean":
                        if (param.Value == "True") {
                            val = "1";
                        } else if (param.Value == "False") {
                            val = "0";
                        } else {
                            throw new ArgumentException("Boolean value other than True or False");
                        }
                        break;
                    case "Time":
                        TimeSpan ts = TimeSpan.Parse(param.Value);
                        val = ts.Ticks.ToString(CultureInfo.CurrentUICulture);
                        break;
                    default:
                        val = param.Value;
                        break;
                }
                s = s.Replace(param.Name, val);
            }
            return s;
        }
    }

    internal static class QueryExecution {

        // 根据对象的 Clr 类型和值字符串(作为调用 ToString 方法的结果而
        // 获得)重新构造该对象
        private static object GetObject(string val, string sqlType) {

            DbType nnType = (DbType)Enum.Parse(typeof(DbType), sqlType.Trim());
            if (nnType == DbType.String) {
                return val;
            } else if (nnType == DbType.Int16) {
                return System.Int16.Parse(val, CultureInfo.CurrentUICulture);
            } else if (nnType == DbType.Int32) {
                return System.Int32.Parse(val, CultureInfo.CurrentUICulture);
            } else if (nnType == DbType.Int64) {
                return System.Int64.Parse(val, CultureInfo.CurrentUICulture);
            } else if (nnType == DbType.Byte) {
                return System.Byte.Parse(val, CultureInfo.CurrentUICulture);
            } else if (nnType == DbType.Double) {
                return System.Double.Parse(val, CultureInfo.CurrentUICulture);
            } else if (nnType == DbType.Single) {
                return System.Single.Parse(val, CultureInfo.CurrentUICulture);
            } else if (nnType == DbType.Decimal) {
                return System.Decimal.Parse(val, CultureInfo.CurrentUICulture);
            } else if (nnType == DbType.Boolean) {
                return System.Boolean.Parse(val);
            } else if (nnType == DbType.DateTime) {
                return System.DateTime.Parse(val, CultureInfo.CurrentUICulture);
            } else if (nnType == DbType.Time) {
                return System.TimeSpan.Parse(val);
            } else if (nnType == DbType.Guid) {
                return new Guid(val);
            } else {
                throw new NotSupportedException("Type " + sqlType + " is not supported for parameters in Linq to Sql Query Visualizer");
            }
        }



        /// <summary>
        ///通过根据 qt.Params 中的字符串创建参数
        /// 并使用 qt.Text 中的文本，创建 SqlCommand
        /// </summary>
        /// <param name="qt">SqlQueryText 输入</param>
        /// <param name="conn">与 SqlCommand 关联的 SqlConnection</param>
        /// <returns>SqlCommand</returns>
        private static SqlCommand GetSqlCommand(SqlQueryText qt, SqlConnection conn) {
            SqlCommand cmd = new SqlCommand(qt.Text, conn);
            foreach (ParameterText param in qt.Params) {
                System.Data.SqlClient.SqlParameter sqlParam = cmd.CreateParameter();
                sqlParam.ParameterName = param.Name;
                object val = GetObject(param.Value, param.SqlType);
                sqlParam.Value = val; 
                cmd.Parameters.Add(sqlParam);
            }
            return cmd;
        }

        // 使用有关该查询的原始信息执行查询
        // 此方法会构造查询和参数，构造方式如同 Linq to SQL
        // (不会将参数值用作 Sql 文本的一部分)
        internal static void ExecuteOriginalQueries(DataSet ds1, DataSet ds2, SqlQueryText[] infos, string connectionString) {
            SqlConnection conn = new SqlConnection(connectionString);

            // 检索数据
            using (conn) {
                conn.Open();

                SqlCommand cmd1 = GetSqlCommand(infos[0], conn);
                SqlDataAdapter adapter1 = new SqlDataAdapter(cmd1);
                adapter1.Fill(ds1);

                if (infos.Length > 1) {
                    SqlCommand cmd2 = GetSqlCommand(infos[1], conn);
                    SqlDataAdapter adapter2 = new SqlDataAdapter(cmd2);
                    adapter2.Fill(ds2);
                }
            }
        }

        // 以文本方式执行 Sql 命令
        internal static void ExecuteQuery(DataSet ds1, string cmd1, string connectionString) {
            SqlConnection conn = new SqlConnection(connectionString);
            using (conn) {
                conn.Open();
                SqlCommand sqlCmd1 = new SqlCommand(cmd1, conn);
                SqlDataAdapter adapter1 = new SqlDataAdapter(sqlCmd1);
                adapter1.Fill(ds1);
            }
        }

        // 以文本方式执行 Sql 命令
        internal static void ExecuteQueries(DataSet ds1, DataSet ds2, string cmd1, string cmd2, string connectionString) {
            SqlConnection conn = new SqlConnection(connectionString);
            using (conn) {
                conn.Open();
                SqlCommand sqlCmd1 = new SqlCommand(cmd1, conn);
                SqlDataAdapter adapter1 = new SqlDataAdapter(sqlCmd1);
                adapter1.Fill(ds1);

                SqlCommand sqlCmd2 = new SqlCommand(cmd2, conn);
                SqlDataAdapter adapter2 = new SqlDataAdapter(sqlCmd2);
                adapter2.Fill(ds2);
            }
        }
    }
}
