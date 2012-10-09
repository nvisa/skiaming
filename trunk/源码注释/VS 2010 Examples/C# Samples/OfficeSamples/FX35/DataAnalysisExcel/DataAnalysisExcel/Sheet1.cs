// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。

using System;
using System.Data;
using System.Drawing;
using System.Windows.Forms;
using System.IO;
using System.ComponentModel;
using System.Globalization;
using Excel = Microsoft.Office.Interop.Excel;

namespace DataAnalysisExcel
{
    public partial class Sheet1
    {
        /// <summary>
        /// 将在此处创建数据透视表。
        /// </summary>        
        private const string pivotTableAddress = "$B$22";

        /// <summary>
        /// Sales 列表的数据源。此视图基于 Globals.DataSet 的 Sales 表， 
        /// 是为显示一天的数据而筛选出来的。
        /// </summary>
        private OperationsData.OperationsView dayView;

        /// <summary>
        /// 包含销售额统计信息的数据透视表。
        /// </summary>
        private Excel.PivotTable pivotTable;

        /// <summary>
        /// 如果当前选定的日期是最后一个有数据的日期，
        /// 则还将显示另外两列，即“Estimated Inventory”和“Recommendation”，
        /// 并且 columnsAdded 设置为 true。否则将设置为 false。
        /// </summary>
        private bool columnsAdded;

        private void Sheet1_Startup(object sender, System.EventArgs e)
        {

            try
            {
                this.Sheet1_TitleLabel.Value2 = Properties.Resources.Sheet1Title;
                this.Name = Properties.Resources.Sheet1Name;

                this.newDateButton.Text = Properties.Resources.AddNewDateButton;
                this.saveButton.Text = Properties.Resources.SaveDataButton;
   
                this.dayView = Globals.DataSet.CreateView();

                if (Globals.DataSet.Sales.Count != 0)
                {
                    this.DateSelector.MinDate = Globals.DataSet.MinDate;
                    this.DateSelector.MaxDate = Globals.DataSet.MaxDate;
                    this.DateSelector.Value = this.DateSelector.MaxDate;
                }

                using (TextFileGenerator textFile = new TextFileGenerator(Globals.DataSet.Sales))
                {
                    this.pivotTable = CreatePivotTable(textFile.FullPath);
                }

                Globals.DataSet.Sales.SalesRowChanged += new OperationsBaseData.SalesRowChangeEventHandler(Sales_SalesRowChanged);
                UnscheduledOrderControl smartPaneControl = new UnscheduledOrderControl();
                smartPaneControl.Dock = DockStyle.Fill;
                smartPaneControl.View = this.dayView;

                Globals.ThisWorkbook.ActionsPane.Controls.Add(smartPaneControl);

                this.Activate();
            }
            catch (Exception ex)
            {
                System.Diagnostics.Debug.WriteLine(ex.ToString());
                MessageBox.Show(ex.Message);
            }
        }

        private void Sheet1_Shutdown(object sender, System.EventArgs e)
        {
        }

        /// <summary>
        /// DateTimePicker 的 ValueChanged 事件处理程序。更改
        /// dateView 可以显示选定日期。
        /// </summary>
        /// <param name="sender">事件的发送者。</param>
        /// <param name="e">事件参数。</param>
        private void DateSelector_ValueChanged(object sender, EventArgs e)
        {

            try
            {
                DateTimePicker control = (DateTimePicker)sender;

                dayView.Date = control.Value;

                DateTime lastDay = control.MaxDate;

                if (control.Value == lastDay)
                {
                    AddColumns();
                }
                else
                {
                    RemoveColumns();
                }

            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }

        /// <summary>
        /// 向工作表的列表对象中添加“Estimated Inventory”
        /// 和“Recommendation”两列。
        /// </summary>
        private void AddColumns()
        {
            if (!columnsAdded)
            {
                dayView.BindToProtectedList(this.DayInventory, "Flavor", "Inventory", "Sold", "Profit", "Estimated Inventory", "Recommendation");

                SetLocalizedColumnNames();
                columnsAdded = true;
            }
        }

        /// <summary>
        /// 从工作表的列表对象中移除“Estimated Inventory”
        /// 和“Recommendation”两列。
        /// </summary>
        private void RemoveColumns()
        {
            if (columnsAdded)
            {
                dayView.BindToProtectedList(this.DayInventory, "Flavor", "Inventory", "Sold", "Profit");
                SetLocalizedColumnNames();
                columnsAdded = false;
            }
        }

        /// <summary>
        /// 创建一个数据透视表，其中包含的数据来自用制表符分隔的文本文件。
        /// </summary>
        /// <param name="filePath">文本文件所在位置。</param>
        /// <returns>已创建的数据透视表。</returns>
        private Excel.PivotTable CreatePivotTable(string filePath)
        {
            // 如果该表已存在，
            // 则返回现有的表。
            string tableName = Properties.Resources.AveragesPivotTableName;            
            Excel.PivotTables tables = (Excel.PivotTables)this.PivotTables(missing);
            System.Collections.Generic.Queue<double> savedWidths = new System.Collections.Generic.Queue<double>();
            
            if (tables != null)
            { 
                int count = tables.Count;

                for (int i = 1; i <= count; i++)
                {
                    Excel.PivotTable table = tables.Item(i);

                    if (table.Name == tableName)
                    {
                        return table;
                    }
                }
            }
            
            
            try
            {
                // AddField 将调整列的大小。
                // 保存列宽，以便在添加数据透视字段之后还原
                foreach (Excel.Range column in DayInventory.HeaderRowRange.Cells)
                {
                    savedWidths.Enqueue((double)column.ColumnWidth);
                }
                
                // 创建数据透视表需要关闭保护功能。
                Globals.ThisWorkbook.MakeReadWrite();
               
                Excel.PivotTable table = Globals.ThisWorkbook.CreateSalesPivotTable(this.get_Range(pivotTableAddress, missing), filePath);
                table.Name = tableName;

                // 在数据透视表中，添加所需的 
                // 行和列。
                table.AddFields("Flavor", missing, missing, missing);
                
                Excel.PivotField soldField = table.AddDataField(table.PivotFields("Sold"), Properties.Resources.AverageSold, Excel.XlConsolidationFunction.xlAverage);

                // 在数据透视表中设置所需数据的视图。
                // 格式“0.0”- 一个小数位。
                soldField.NumberFormat = "0.0";

                Excel.PivotField profitField = table.AddDataField(table.PivotFields("Profit"), Properties.Resources.AverageProfit, Excel.XlConsolidationFunction.xlAverage);

                // 在数据透视表中设置所需数据的视图。
                // 格式“0.00”- 两个小数位。
                profitField.NumberFormat = "0.00";

                // 隐藏创建数据透视表时添加的两个浮动栏。
                Globals.ThisWorkbook.ShowPivotTableFieldList = false;
                Globals.ThisWorkbook.Application.CommandBars["PivotTable"].Visible = false;

                return table;
            }
            finally
            {
                // AddField 将调整列的大小。还原列宽。
                foreach (Excel.Range column in DayInventory.HeaderRowRange.Cells)
                {
                    column.ColumnWidth = savedWidths.Dequeue();
                }
                Globals.ThisWorkbook.MakeReadOnly();
            }
        }

        /// <summary>
        /// 将列表对象的列标题设置为资源表中的值。
        /// </summary>
        private void SetLocalizedColumnNames()
        {
            string[] localizedInventoryColumns = {
                Properties.Resources.IceCreamHeader, 
                Properties.Resources.EodInventoryHeader, 
                Properties.Resources.UnitsSoldHeader, 
                Properties.Resources.NetGainHeader, 
                Properties.Resources.EstimatedInventoryHeader, 
                Properties.Resources.RecommendationHeader
            };

            try
            {
                Globals.ThisWorkbook.MakeReadWrite();
                this.DayInventory.HeaderRowRange.Value2 = localizedInventoryColumns;
            }
            finally
            {
                Globals.ThisWorkbook.MakeReadOnly();
            }
        }

        /// <summary>
        /// 单击 newDateButton 的事件处理程序。在 Sales 表中
        /// 针对新日期插入新行，并为新数据项设置列表对象。
        /// </summary>
        /// <param name="sender">事件的发送者。</param>
        /// <param name="e">事件参数。</param>
        private void newDateButton_Click(object sender, EventArgs e)
        {
            try
            {
                if (!Globals.DataSet.IsLastDayComplete())
                {
                    MessageBox.Show(Globals.ThisWorkbook.IncompleteDataMessage);
                    return;
                }

                DateTime nextDate = Globals.DataSet.MaxDate.AddDays(1);

                foreach (OperationsBaseData.PricingRow row in Globals.DataSet.Pricing)
                {
                    OperationsBaseData.SalesRow newRow = (OperationsBaseData.SalesRow)this.dayView.Table.NewRow();
                    newRow.Flavor = row.Flavor;
                    newRow.Date = nextDate;
                    this.dayView.Table.AddSalesRow(newRow);
                }

                this.DateSelector.MaxDate = nextDate;
                this.DateSelector.Value = nextDate;
            }
            catch (Exception ex)
            {
                System.Diagnostics.Debug.WriteLine(ex.ToString());
                MessageBox.Show(ex.Message);
            }
        }

        /// <summary>
        /// 单击 saveButton 的事件处理程序。将数据写回 XML 文件。
        /// </summary>
        /// <param name="sender">事件的发送者。</param>
        /// <param name="e">事件参数。</param>
        private void saveButton_Click(object sender, EventArgs e)
        {
            Globals.DataSet.Save();
        }

        void Sales_SalesRowChanged(object sender, OperationsBaseData.SalesRowChangeEvent e)
        {
            if (e.Action == DataRowAction.Change)
            {
                Globals.ThisWorkbook.UpdateSalesPivotTable(this.pivotTable);
            }
        }

        #region VSTO 设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 请勿
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InternalStartup()
        {
            this.DateSelector.ValueChanged += new System.EventHandler(this.DateSelector_ValueChanged);
            this.newDateButton.Click += new System.EventHandler(this.newDateButton_Click);
            this.saveButton.Click += new System.EventHandler(this.saveButton_Click);
            this.Shutdown += new System.EventHandler(this.Sheet1_Shutdown);
            this.Startup += new System.EventHandler(this.Sheet1_Startup);

        }

        #endregion

    }
}
