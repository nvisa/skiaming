// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
//版权所有(C) Microsoft Corporation。保留所有权利。
using System;
using System.Collections.Generic;
using System.Data.Linq;
using System.IO;
using System.Linq;
using System.Windows.Forms;

namespace WinFormsDataBinding {
    static class Program 
    {
        // 以下示例假定已安装 DATA 示例
        // 项目，且 Northwind.MDF 位于该 Data 目录中。
        private readonly static string dbPath = Path.GetFullPath(Path.Combine(Application.StartupPath, @"..\..\..\Data\NORTHWND.MDF"));
        private const string sqlServerInstance = @".\SQLEXPRESS";
        public readonly static string connString = "AttachDBFileName='" + dbPath + "';Server='" + sqlServerInstance + "';user instance=true;Integrated Security=SSPI;Connection Timeout=60";

        //此外，已修改 SQLMetal 生成的 Northwind.cs 文件以
        //包含 Employee 实体的重写 ToString 方法，这使 DataGridView 的
        //ReportsToEmployee 列可以显示一个合理的值。
        [STAThread]
        static void Main() {
            Application.EnableVisualStyles();
            Application.Run(new EmployeeForm());
        }
    }
}