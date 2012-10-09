// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
//版权所有(C) Microsoft Corporation。保留所有权利。

using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Linq;
using System.Data.Linq;
using NorthwindMapping;

namespace WinFormsDataBinding {
    public partial class EmployeeForm : Form {
        private Northwind db;

        public EmployeeForm() {
            InitializeComponent();
            db = new Northwind(Program.connString);
            var employeeQuery = from employee in db.Employees 
                                orderby employee.LastName
                                select employee;
            var managerQuery =  from manager in db.Employees 
                                orderby manager.LastName
                                select manager;
            //ToBindingList 方法可将查询转换成支持 IBindingList 的结构。
            //需要将 Table<T> 转换成绑定列表，以便可以正确跟踪
            //实体的添加和删除情况。
            employeeBindingSource.DataSource = employeeQuery;
            managerBindingSource.DataSource = managerQuery.ToList();
       }

        private void submitChanges_Click(object sender, EventArgs e) {
            //使控件容器生效并结束编辑。
            this.Validate();
            db.SubmitChanges();
        }

        private void employeeDataGridView_CellParsing(object sender, DataGridViewCellParsingEventArgs e) {
            string s = e.Value as string;

             //需要提供 OfType，因为 employeeBindingSource 会返回类型对象的实例。
             Employee emp = (from employee in this.managerBindingSource.OfType<Employee>()
                            where employee.ToString()==s
                            select employee).FirstOrDefault();
            
            e.Value = emp;
            e.ParsingApplied = true;
        }

        private void launchEmployeeManager_Click(object sender, EventArgs e) {
            WinFormsDataBinding.EmployeeManagerGrids form = new EmployeeManagerGrids();
            form.Visible = true;
        }
    }
}