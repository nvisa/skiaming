// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
//版权所有(C) Microsoft Corporation。保留所有权利。

using System;
using System.Collections;
using System.Collections.Generic;
using System.Data.Linq.Mapping;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Windows.Forms;


using nwind;
[assembly: CLSCompliant(true)]
[assembly: AssemblyVersion("1.0.0.0")]
[assembly: ComVisible(false)]

namespace LinqToNorthwind {
    class Program
    {
        [STAThread()]
        static void Main()
        {
            // 编写以下代码时假定:
            // 1. 计算机中已安装了 SQL Server 2005 Express
            // 2. 安装含有 Northwind 的 Data Sample 目录。
            // 或者，如果已安装 Northwind，则需要将连接字符串改为
            // Northwind db = new Northwind("Server=.\\SQLExpress;Database=Northwind;Trusted_Connection=True");
            // 必须编辑路径，使其指向您计算机上的 mdf 文件
            // Northwind db = new Northwind("c:\\northwind\\northwnd.mdf");

            string dbPath = Path.GetFullPath(Path.Combine(Application.StartupPath, @"..\..\..\Data\NORTHWND.MDF"));
            string sqlServerInstance = @".\SQLEXPRESS";
            string connString = "AttachDBFileName='" + dbPath + "';Server='" + sqlServerInstance + "';user instance=true;Integrated Security=SSPI; Pooling=false; Connection Timeout=60";

            Northwind db = new Northwind(connString);
            db.Log = Console.Out;
            Samples.Sample1(db);
            Console.ReadLine();
        }
    }
}
