// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
//版权所有(C) Microsoft Corporation。保留所有权利。

// OleDbSample.cs
// 若要从命令行生成此示例，请使用命令：
// csc oledbsample.cs

using System;
using System.Data;
using System.Data.OleDb;
using System.Xml.Serialization;

public class MainClass 
{
	public static void Main ()
	{
		// 设置访问连接并选择字符串。
		// 如果从命令行生成此示例，
		// 则必须更改 BugTypes.MDB 的路径：
#if USINGPROJECTSYSTEM
		string strAccessConn = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=..\\..\\BugTypes.MDB";
#else
		string strAccessConn = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=BugTypes.MDB";
#endif
		string strAccessSelect = "SELECT * FROM Categories";

		// 创建数据集并向其中添加 Categories 表：
		DataSet myDataSet = new DataSet();
		OleDbConnection myAccessConn = null;
		try
		{
			myAccessConn = new OleDbConnection(strAccessConn);
		}
		catch(Exception ex)
		{
			Console.WriteLine("Error: Failed to create a database connection. \n{0}", ex.Message);
			return;
		}

		try
		{
		
			OleDbCommand myAccessCommand = new OleDbCommand(strAccessSelect,myAccessConn);
			OleDbDataAdapter myDataAdapter = new OleDbDataAdapter(myAccessCommand);

			myAccessConn.Open();
			myDataAdapter.Fill(myDataSet,"Categories");

		}
		catch (Exception ex)
		{
			Console.WriteLine("Error: Failed to retrieve the required data from the DataBase.\n{0}", ex.Message);
			return;
		}
		finally
		{
			myAccessConn.Close();
		}

		// 一个数据集可以包含多个表，因此可以将这些表都放入
		// 一个数组中：
		DataTableCollection dta = myDataSet.Tables;
		foreach (DataTable dt in dta)
		{
			Console.WriteLine("Found data table {0}", dt.TableName);
		}
	    
		// 下面两行显示两种不同方法，可用于获取数据集中
		// 的表计数：
		Console.WriteLine("{0} tables in data set", myDataSet.Tables.Count);
		Console.WriteLine("{0} tables in data set", dta.Count);
		// 下面几行显示如何按名称
		// 从数据集中获取特定表的信息：
		Console.WriteLine("{0} rows in Categories table", myDataSet.Tables["Categories"].Rows.Count);
		// 列信息自动从数据库中提取，因此
		// 可以在此处看到这些信息：
		Console.WriteLine("{0} columns in Categories table", myDataSet.Tables["Categories"].Columns.Count);
		DataColumnCollection drc = myDataSet.Tables["Categories"].Columns;
		int i = 0;
		foreach (DataColumn dc in drc)
		{
			// 打印列下标，然后打印列的名称及其
			// 数据类型：
			Console.WriteLine("Column name[{0}] is {1}, of type {2}",i++ , dc.ColumnName, dc.DataType);
		}
		DataRowCollection dra = myDataSet.Tables["Categories"].Rows;
		foreach (DataRow dr in dra)
		{
			// 打印 CategoryID 作为下标，然后打印 CategoryName：
			Console.WriteLine("CategoryName[{0}] is {1}", dr[0], dr[1]);
		}
      
	}
}

