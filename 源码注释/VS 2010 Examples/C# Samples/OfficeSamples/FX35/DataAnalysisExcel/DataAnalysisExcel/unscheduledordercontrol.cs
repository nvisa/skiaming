// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。

using System;
using System.Collections;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Windows.Forms;
using Excel = Microsoft.Office.Interop.Excel;
using Office = Microsoft.Office.Core;
using System.Globalization;

namespace DataAnalysisExcel
{
    /// <summary>
    /// 这是在“操作”窗格中显示的控件。
    /// 该控件允许创建未计划的冰淇淋订单，允许查看冰淇淋的销售历史记录。
    /// </summary>
    public partial class UnscheduledOrderControl : UserControl
    {
        /// <summary>
        /// 未计划订单的成本。
        /// </summary>
        const double unscheduledDeliveryCost = 25;

        /// <summary>
        /// 获取或设置当前日期的视图。
        /// </summary>
        /// <value></value>
        internal OperationsData.OperationsView View
        {
            get
            {
                return this.view;
            }
            set
            {
                if (this.view != null)
                {
                    this.view.ListChanged -= new ListChangedEventHandler(view_ListChanged);
                }

                this.view = value;

                if (this.view != null)
                {
                    this.view.ListChanged += new ListChangedEventHandler(view_ListChanged);
                    UpdateRecommendationLabel();
                }
            }
        }

        public UnscheduledOrderControl()
        {
            this.InitializeComponent();

            System.ComponentModel.ComponentResourceManager resources = 
                new System.ComponentModel.ComponentResourceManager(typeof(UnscheduledOrderControl));
            resources.ApplyResources(this.selectorLabel, "selectorLabel", CultureInfo.CurrentUICulture);
            resources.ApplyResources(this.flavorComboBox, "flavorComboBox", CultureInfo.CurrentUICulture);
            resources.ApplyResources(this.highLabel, "highLabel", CultureInfo.CurrentUICulture);
            resources.ApplyResources(this.lowLabel, "lowLabel", CultureInfo.CurrentUICulture);
            resources.ApplyResources(this.highList, "highList", CultureInfo.CurrentUICulture);
            resources.ApplyResources(this.lowList, "lowList", CultureInfo.CurrentUICulture);
            resources.ApplyResources(this.recommendationGroup, "recommendationGroup", CultureInfo.CurrentUICulture);
            resources.ApplyResources(this.createOrderButton, "createOrderButton", CultureInfo.CurrentUICulture);
            resources.ApplyResources(this.orderLabel, "orderLabel", CultureInfo.CurrentUICulture);
            resources.ApplyResources(this.recommendationLabel, "recommendationLabel", CultureInfo.CurrentUICulture);
            resources.ApplyResources(this, "$this", CultureInfo.CurrentUICulture);

            // 将口味组合框的数据绑定到定价表。
            this.flavorComboBox.DataSource = Globals.DataSet.Pricing;
            this.flavorComboBox.DisplayMember = "Flavor";
        }

        /// <summary>
        /// 创建一个新的订单工作表。
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void CreateOrderButton_Click(object sender, System.EventArgs e)
        {
            try
            {
                new OrderingSheet(true);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        /// <summary>
        /// 口味组合框 SelectedIndexChanged 事件的处理程序。
        /// 在口味历史记录工作表中显示选定的口味。
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void flavorComboBox_SelectedIndexChanged(object sender, System.EventArgs e)
        {
            DataRowView selectedItem = (DataRowView)((ComboBox)sender).SelectedItem;
            DisplayFlavorHistory(((OperationsBaseData.PricingRow)selectedItem.Row).Flavor);
        }

        /// <summary>
        /// 该视图的 ListChanged 事件的处理程序。对该视图进行更改以显示
        /// 不是最近日期的日期时，显示的控件只有口味组合框及其标签。
        /// 在该视图中更改库存数据时，以下三个控件将进行更新:
        /// 低库存列表、高库存列表和建议标签。
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void view_ListChanged(object sender, ListChangedEventArgs e)
        {
            if (this.View.Date == Globals.DataSet.MaxDate)
            {
                if (e.ListChangedType == ListChangedType.Reset)
                {
                    ShowLastDayControls(true);
                }
                else if (e.ListChangedType == ListChangedType.ItemChanged)
                {
                    double estimatedInventory = (double)this.View[e.NewIndex]["Estimated Inventory"];
                    string flavor = (string)this.View[e.NewIndex]["Flavor"];

                    if (estimatedInventory < 0)
                    {
                        ShowAsLowInventory(flavor);
                    }
                    else
                    {
                        double todaysInventory;
                        todaysInventory = ((OperationsBaseData.SalesRow)this.view[e.NewIndex].Row).Inventory;

                        double idealInventory;
                        idealInventory = todaysInventory - estimatedInventory;

                        // 如果大于 10%，则表示超过上一个销售额
                        if (todaysInventory > idealInventory * 1.1)
                        {
                            ShowAsHighInventory(flavor);
                        }
                        else
                        {
                            ShowAsAdequateInventory(flavor);
                        }
                    }

                    UpdateRecommendationLabel();
                }
            }
            else
            {
                if (e.ListChangedType == ListChangedType.Reset)
                {
                    ShowLastDayControls(false);
                }
            }
        }

        /// <summary>
        /// 将口味显示为低库存项。
        /// </summary>
        /// <param name="flavor">要显示的口味。</param>
        void ShowAsLowInventory(string flavor)
        {
            if (!this.lowList.Items.Contains(flavor))
            {
                this.lowList.Items.Add(flavor);

                if (this.highList.Items.Contains(flavor))
                {
                    this.highList.Items.Remove(flavor);
                }
            }
        }

        /// <summary>
        /// 将口味显示为高库存项。
        /// </summary>
        /// <param name="flavor">要显示的口味。</param>
        void ShowAsHighInventory(string flavor)
        {
            if (!this.highList.Items.Contains(flavor))
            {
                this.highList.Items.Add(flavor);

                if (this.lowList.Items.Contains(flavor))
                {
                    this.lowList.Items.Remove(flavor);
                }
            }
        }

        /// <summary>
        /// 分别从高库存列表和低库存列表中移除口味。
        /// </summary>
        /// <param name="flavor">要从列表中移除的口味。</param>
        void ShowAsAdequateInventory(string flavor)
        {
            if (this.highList.Items.Contains(flavor))
            {
                this.highList.Items.Remove(flavor);
            }

            if (this.lowList.Items.Contains(flavor))
            {
                this.lowList.Items.Remove(flavor);
            }
        }

        /// <summary>
        /// 显示或隐藏低/高库存列表框、 
        /// 列表框的标签和建议分组框。
        /// </summary>
        /// <param name="show">如果为 true，则显示；如果为 false，则隐藏。</param>
        private void ShowLastDayControls(bool show)
        {
            Control[] dynamicControls = new Control[] {
                this.highLabel, this.highList, this.lowLabel, this.lowList, this.recommendationGroup
            };

            if (show)
            {
                foreach (Control c in dynamicControls)
                {
                    c.Show();
                }
            }
            else
            {
                foreach (Control c in dynamicControls)
                {
                    c.Hide();
                }
            }
        }

        /// <summary>
        /// 单击高库存列表和低库存列表的事件处理程序。
        /// 显示所单击口味冰淇淋的销售历史记录。
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void inventoryList_Click(object sender, EventArgs e)
        {
            string flavor = (string)(((ListBox)sender).SelectedItem);
            if (flavor != null)
            {
                DisplayFlavorHistory(flavor);
            }
        }

        /// <summary>
        /// 在口味历史记录工作表中显示某种口味冰淇淋的销售历史记录。
        /// </summary>
        /// <param name="flavor">已显示其历史记录的口味。</param>
        private static void DisplayFlavorHistory(string flavor)
        {
            Globals.Sheet2.Flavor = flavor;
            Globals.Sheet2.Activate();
        }

        /// <summary>
        /// 根据订购的冰淇淋计算可能的利润。
        /// </summary>
        /// <returns>可能的利润。</returns>
        private double CalculatePotentialProfit()
        {
            double profit = 0 - unscheduledDeliveryCost;

            foreach (DataRowView rowView in this.view)
            {
                OperationsBaseData.SalesRow row = (OperationsBaseData.SalesRow)rowView.Row;

                if (!row.IsEstimated_InventoryNull() && row.Estimated_Inventory < 0)
                {
                    OperationsBaseData.PricingRow pricing = (OperationsBaseData.PricingRow)row.GetParentRow("Pricing_Sales");
                    double flavorProfit = (pricing.Price - pricing.Cost) * (0 - row.Estimated_Inventory);

                    profit += flavorProfit;
                }
            }

            return profit;
        }

        /// <summary>
        /// 计算订购推荐值并在 recommendationLabel 中显示该值。
        /// </summary>
        void UpdateRecommendationLabel()
        {
            double profit = CalculatePotentialProfit();

            if (profit > 0)
            {
                this.recommendationLabel.Text = string.Format(
                    CultureInfo.CurrentUICulture,
                    Properties.Resources.UnscheduledOrderRecommended, 
                    profit);
            }
            else
            {
                this.recommendationLabel.Text = string.Format(
                    CultureInfo.CurrentUICulture,
                    Properties.Resources.UnscheduledOrderNotRecommended, 
                    0 - profit);
            }
        }
    }
}
