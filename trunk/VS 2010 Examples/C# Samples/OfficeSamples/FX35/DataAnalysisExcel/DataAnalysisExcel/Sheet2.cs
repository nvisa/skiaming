// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。

using System;
using System.Data;
using System.Drawing;
using System.Windows.Forms;
using Excel = Microsoft.Office.Interop.Excel;

namespace DataAnalysisExcel
{
    /// <summary>
    /// 此工作表显示某种口味的冰淇淋的历史销售额数据。
    /// </summary>
    public partial class Sheet2
    {
        /// <summary>
        /// 该数据视图基于 Sales 表生成并且按口味进行筛选。
        /// </summary>
        private OperationsData.OperationsView view;

        /// <summary>
        /// 已显示其历史记录的口味。
        /// </summary>
        private string flavor = null;

        /// <summary>
        /// 口味字段的访问器和转变器。
        /// 修改属性时，也会对视图进行相应的更改。
        /// </summary>
        /// <value>当前的口味。</value>
        public string Flavor
        {
            get
            {
                return flavor;
            }
            set
            {
                flavor = value;

                if (FlavorChanged != null)
                {
                    FlavorChanged(this, new System.ComponentModel.PropertyChangedEventArgs("Flavor"));
                }

                if (view != null)
                {
                    view.Flavor = flavor;
                }
            }
        }

        /// <summary>
        /// 当 Flavor 发生更改时，将引发事件。使用 Flavor 属性
        /// 进行数据绑定时，PropertyManager 侦听此事件。
        /// </summary>
        public event EventHandler FlavorChanged;

        private void Sheet2_Startup(object sender, System.EventArgs e)
        {
            this.Sheet2_TitleLabel.Value2 = Properties.Resources.Sheet2Title;
            this.Name = Properties.Resources.Sheet2Name;
            this.IceCreamLabel.Value2 = Properties.Resources.IceCreamHeader;
            
            this.Chart_1.ChartTitle.Text = Properties.Resources.ProfitHeader;
            ((Excel.Axis)this.Chart_1.Axes(Excel.XlAxisType.xlValue, Excel.XlAxisGroup.xlPrimary)).AxisTitle.Text = Properties.Resources.ProfitHeader;
            ((Excel.Axis)this.Chart_1.Axes(Excel.XlAxisType.xlCategory, Excel.XlAxisGroup.xlPrimary)).AxisTitle.Text = Properties.Resources.DateHeader;

            this.view = Globals.DataSet.CreateView();

            if (this.Flavor != null)
            {
                view.Flavor = this.Flavor;
            }
            else if (view.Count != 0)
            {
                this.Flavor = (string)view[0].Row["Flavor"];
            }

            this.FlavorNamedRange.DataBindings.Add("Value2", this, "Flavor");

            this.History.SetDataBinding(view, "", "Date", "Inventory", "Sold", "Profit");

            this.History.ListColumns[1].Name = Properties.Resources.DateHeader;
            this.History.ListColumns[2].Name = Properties.Resources.InventoryHeader;
            this.History.ListColumns[3].Name = Properties.Resources.SoldHeader;
            this.History.ListColumns[4].Name = Properties.Resources.ProfitHeader;            
        }

        private void Sheet2_Shutdown(object sender, System.EventArgs e)
        {
        }

        #region VSTO 设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 请勿
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InternalStartup()
        {
            this.Startup += new System.EventHandler(Sheet2_Startup);
            this.Shutdown += new System.EventHandler(Sheet2_Shutdown);
        }

        #endregion

    }
}
