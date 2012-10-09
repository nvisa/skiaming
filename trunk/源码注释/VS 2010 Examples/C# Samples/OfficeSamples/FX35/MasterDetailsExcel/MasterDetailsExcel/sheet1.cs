// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。

using System;
using System.Data;
using System.Drawing;
using System.Windows.Forms;
using Microsoft.VisualStudio.Tools.Applications.Runtime;
using Excel = Microsoft.Office.Interop.Excel;
using Office = Microsoft.Office.Core;
using System.Diagnostics;

namespace MasterDetailsRelationships
{
    public partial class Sheet1
    {
        private string[] productListColumnHeaders = { "ProductName", "Quantity", "Inventory" };

        private const int productNameColumn = 1;
        private const int quantityOrderedColumn = 2;
        private const int currentInventoryColumn = 3;
        private const string quantityOrderedChartSeries = "=\"Quantity Ordered\"";
        private const string inventoryChartSeries = "=\"Inventory\"";
        private const string noOrderSelectedTitle = "No Order Selected";
        private const string canFulfillOrderTitle = "Order Can Be Fulfilled";
        private const string cannotFulfillOrderTitle = "Order Not Ready for Fulfillment";

        private void Sheet1_Startup(object sender, System.EventArgs e)
        {
            // 设置 ProductList 的列标题。
            this.ProductList.HeaderRowRange.Value2 = productListColumnHeaders;

            // 设置图表的标题。
            ((Excel.Series)this.OrdersChart.SeriesCollection(1)).Name = quantityOrderedChartSeries;
            ((Excel.Series)this.OrdersChart.SeriesCollection(2)).Name = inventoryChartSeries;
            this.OrdersChart.ChartTitle.Text = noOrderSelectedTitle;

            // 将 ProductList 绑定到当前选定订单的订单详细信息。
            this.ProductList.SetDataBinding(Globals.ThisWorkbook.OrderDetailsBindingSource,
                null, productListColumnHeaders);

            // 将“Status”命名范围绑定到当前选定订单的状态。
            this.Status.DataBindings.Add("Value2", Globals.ThisWorkbook.StatusBindingSource, "Status");
        }

        void ProductList_Change(Microsoft.Office.Interop.Excel.Range targetRange, Microsoft.Office.Tools.Excel.ListRanges changedRanges)
        {
            this.UpdateChart();
        }

        /// <summary>
        /// 根据当前选定订单的详细信息，更新图表的 
        /// 标题。
        /// </summary>
        private void UpdateChart()
        {
            if (Globals.ThisWorkbook.CustomerOrdersBindingSource.Count == 0)
                this.OrdersChart.ChartTitle.Text = noOrderSelectedTitle;
            else if (this.CanFulfillOrder())
                this.OrdersChart.ChartTitle.Text = canFulfillOrderTitle;
            else
                this.OrdersChart.ChartTitle.Text = cannotFulfillOrderTitle;
        }

        /// <summary>
        /// 确定是否有履行当前选定订单的 
        /// 足够产品库存。
        /// </summary>
        /// <returns></returns>
        private bool CanFulfillOrder()
        {
            Excel.Range listRange = this.ProductList.DataBodyRange;

            for (int i = 1; i <= listRange.Rows.Count; i++)
            {
                // 获取 ListRow 中的值。
                object[,] values = (object[,])((Excel.Range)listRange.Rows[i, missing]).Value2;

                // 确定该行表示哪种产品。
                if (values[1, productNameColumn] == null)
                    continue;
                string product = values[1, productNameColumn].ToString();

                // 如果该行中有一种产品，请确定该产品的可用数量。
                if (!String.IsNullOrEmpty(product))
                {
                    int quantity = Convert.ToInt32(values[1, quantityOrderedColumn]);
                    CompanyData.ProductsRow productRow = Globals.ThisWorkbook.CurrentCompanyData.Products.FindByName(product);

                    // 检查是否有足够的库存满足订购的数量。
                    if ((productRow.Inventory - quantity) < 0)
                        return false;
                }
            }

            return true;
        }

        private void Status_Change(Microsoft.Office.Interop.Excel.Range Target)
        {
            // 获取在“Status”命名范围上设置的状态的 StatusID。
            Debug.Assert((Globals.ThisWorkbook.CustomerOrdersBindingSource.Current as DataRowView) != null);
            DataRowView currentRow = (DataRowView)Globals.ThisWorkbook.CustomerOrdersBindingSource.Current;
            Debug.Assert((currentRow.Row as CompanyData.OrdersRow) != null);
            CompanyData.OrdersRow orderRow = (CompanyData.OrdersRow)currentRow.Row;
            int newStatus = Globals.ThisWorkbook.CurrentCompanyData.Status.FindByStatus(
                this.Status.Value2.ToString()).StatusID;

            // 检查当订单未能真正履行时，状态是否设置为“已满足”。
            // 如果是这样，提醒用户订单无法履行。
            if (newStatus == 0 && orderRow.StatusID !=0 && !this.CanFulfillOrder())
            {
                MessageBox.Show("Order cannot be fulfilled with current inventory levels.");
                this.Status.Value2 = orderRow.StatusRow.Status;
                return;
            }
            else if (newStatus == 0 && orderRow.StatusID != 0)
            {
                // 订单更改为将要履行，因此库存需要
                // 更新以移除发货的数量。
                this.UpdateInventory();
            }

            // 更新订单以反映新状态。
            orderRow.StatusID = newStatus;
        }

        /// <summary>
        /// 根据履行的当前订单，更新产品的可用库存。
        /// </summary>
        private void UpdateInventory()
        {
            Excel.Range listRange = this.ProductList.DataBodyRange;

            for (int i = 1; i <= listRange.Rows.Count; i++)
            {
                // 获取 ListRow 中的值。
                object[,] values = (object[,])((Excel.Range)listRange.Rows[i, missing]).Value2;
                if (values[1, productNameColumn] == null)
                    continue;

                // 确定该行表示哪种产品。
                string product = values[1, productNameColumn].ToString();

                // 如果该行中有一种产品，请确定该产品的可用数量。
                if (!String.IsNullOrEmpty(product))
                {
                    int quantity = Convert.ToInt32(values[1, quantityOrderedColumn]);
                    CompanyData.ProductsRow productRow = Globals.ThisWorkbook.CurrentCompanyData.Products.FindByName(product);

                    // 更新 ProductRow 以反映新的库存水平。
                    productRow.Inventory = productRow.Inventory - quantity;
                }
            }

            // 保存对数据集的更改。
            Globals.ThisWorkbook.CurrentCompanyData.AcceptChanges();
        }


        private void Sheet1_Shutdown(object sender, System.EventArgs e)
        {
        }

        #region VSTO 设计器生成的代码


        /// <summary>
        /// 设计器支持所需的方法 - 请勿
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InternalStartup()
        {
            this.Shutdown += new System.EventHandler(this.Sheet1_Shutdown);
            this.Startup += new System.EventHandler(this.Sheet1_Startup);
            this.ProductList.Change += new Microsoft.Office.Tools.Excel.ListObjectChangeHandler(ProductList_Change);
            this.Status.Change += new Microsoft.Office.Interop.Excel.DocEvents_ChangeEventHandler(Status_Change);
        }
        #endregion
    }
}
