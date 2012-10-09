// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。

using System;
using System.Collections;
using System.Collections.Generic;
using System.Data;
using System.Windows.Forms;
using System.ComponentModel;
using System.Globalization;
using System.Text;

namespace DataAnalysisExcel
{
    public partial class OperationsBaseData : System.Data.DataSet
    {
        // 此方法在下面的 OperationsData 类中被重写。
        protected virtual void OnSalesInventoryChanged(DataColumnChangeEventArgs e)
        {
        }

        public partial class SalesDataTable : System.Data.TypedTableBase<SalesRow>, System.Collections.IEnumerable 
        {
            protected override void OnColumnChanged(DataColumnChangeEventArgs e)
            {
                OperationsBaseData dataset = this.DataSet as OperationsBaseData;

                if (dataset != null && e.Column == this.InventoryColumn)
                {
                    dataset.OnSalesInventoryChanged(e);
                }
                base.OnColumnChanged(e);
            }
        }
    }

    internal class OperationsData : OperationsBaseData
    {
        internal class OperationsView : DataView
        {

            internal DateTime? Date
            {
                get
                {
                    return date;
                }
                set
                {
                    date = value;
                    SetRowFilter();
                }
            }

            internal string Flavor
            {
                get
                {
                    return flavor;
                }
                set
                {
                    flavor = value;
                    SetRowFilter();
                }
            }

            internal new OperationsBaseData.SalesDataTable Table
            {
                get
                {
                    return (OperationsBaseData.SalesDataTable)base.Table;
                }
            }

            private Nullable<DateTime> date = null;

            private string flavor;

            bool boundToList = false;

            private void SetRowFilter()
            {

                System.Collections.Generic.List<string> conditions = new List<string>(2);

                if (date != null)
                {
                    conditions.Add(
                        String.Format(CultureInfo.InvariantCulture, "Date=#{0:d}#", this.date));
                }

                if (flavor != null)
                {
                    conditions.Add("Flavor='" + this.flavor.Replace("'", "''") + "'");
                }

                this.RowFilter = string.Join(" AND ", conditions.ToArray());
            }

            internal OperationsView() : base() { }

            internal OperationsView(DataTable dt) : base(dt) { }

            internal void BindToProtectedList(Microsoft.Office.Tools.Excel.ListObject list, params string[] mappedColumns)
            {
                try
                {
                    Globals.ThisWorkbook.MakeReadWrite();

                    list.SetDataBinding(this, "", mappedColumns);
                    boundToList = true;
                }
                finally
                {
                    Globals.ThisWorkbook.MakeReadOnly();
                }
            }


            protected override void OnListChanged(System.ComponentModel.ListChangedEventArgs e)
            {
                if (boundToList)
                {
                    Globals.ThisWorkbook.MakeReadWrite();
                    base.OnListChanged(e);
                    Globals.ThisWorkbook.MakeReadOnly();
                }
                else
                {
                    base.OnListChanged(e);
                }
            }

        }

        internal OperationsView CreateView()
        {
            OperationsView view = new OperationsView(this.Sales);

            return view;
        }

        private OperationsView lastDaysView;

        internal OperationsData()
            :base()
        {
        }

        internal void Load()
        {
            Load(ThisWorkbook.GetAbsolutePath(@"."));
        }

        internal void Load(string folder)
        {
            try
            {
                this.Pricing.ReadXml(System.IO.Path.Combine(folder, "PricingData.xml"));
                this.Sales.ReadXml(System.IO.Path.Combine(folder, "SalesData.xml"));
                this.Inventory.ReadXml(System.IO.Path.Combine(folder, "InventoryData.xml"));
                ComputeSoldColumn();

                lastDaysView = CreateView();

                if (Sales.Count != 0)
                {
                    lastDaysView.Date = MaxDate;
                }
            }
            catch (Exception ex)
            {
                System.Diagnostics.Debug.WriteLine(ex.ToString());
                throw;
            }
        }

        internal void Save()
        {
            Save(ThisWorkbook.GetAbsolutePath(@"."));
        }

        internal void Save(string folder)
        {
            this.Sales.WriteXml(System.IO.Path.Combine(folder, "SalesData.xml"), false);
        }

        private void ComputeSoldColumn()
        {
            System.Collections.Generic.Dictionary<string, int> lastInventory = new System.Collections.Generic.Dictionary<string, int>();
            DateTime maxDate = this.MaxDate;

            foreach (OperationsBaseData.SalesRow row in this.Sales)
            {
                if (lastInventory.ContainsKey(row.Flavor))
                {
                    int received;
                    int lastInventoryValue = lastInventory[row.Flavor];
                    OperationsBaseData.InventoryRow[] inventoryRows = row.GetInventoryRows();

                    if (inventoryRows == null || inventoryRows.Length == 0)
                    {
                        received = 0;
                    }
                    else
                    {
                        received = inventoryRows[0].Received;
                    }

                    if (!row.IsInventoryNull())
                    {
                        row.Sold = lastInventoryValue - row.Inventory + received;

                        lastInventory[row.Flavor] = row.Inventory;
                        
                        // 更新最后一天所在行的估计值和推荐值。
                        // 估计值和推荐值可能不在数据中，或者
                        // 推荐值所用语言有误。
                        if (row.Date == maxDate)
                        {
                            double sellingSpeed = ComputeAverageSellingSpeed(row.Flavor);
                            EstimateInventory(row, sellingSpeed);
                        }
                    }
                }
                else
                {
                    lastInventory.Add(row.Flavor, row.Inventory);

                    row.SetSoldNull();
                }
            }
        }

        private void ComputeSoldColumn(OperationsBaseData.SalesRow row)
        {
            SalesRow previousDaysRow = this.Sales.FindByDateFlavor(row.Date.AddDays(-1), row.Flavor);

            if (previousDaysRow == null)
            {
                row.SetSoldNull();
            }
            else
            {
                int lastInventory = previousDaysRow.Inventory;
                int received;

                OperationsBaseData.InventoryRow[] inventoryRows = row.GetInventoryRows();

                if (inventoryRows == null || inventoryRows.Length == 0)
                {
                    received = 0;
                }
                else
                {
                    received = inventoryRows[0].Received;
                }

                row.Sold = lastInventory - row.Inventory + received;
            }
        }

        internal DateTime MinDate
        {
            get
            {
                return (DateTime)this.Sales.Compute("MIN(Date)", String.Empty);
            }
        }

        internal DateTime MaxDate
        {
            get
            {
                return (DateTime)this.Sales.Compute("MAX(Date)", String.Empty);
            }
        }

        internal DateTime NextWeeklyDeliveryDate
        {
            get
            {
                DateTime lastDate = this.MaxDate;
                DayOfWeek lastDay = lastDate.DayOfWeek;
                DateTime deliveryDate;
                const int oneWeek = 7;

                if (lastDay <= DayOfWeek.Tuesday)
                {
                    deliveryDate = lastDate.AddDays(DayOfWeek.Thursday - lastDay);
                }
                else
                {
                    deliveryDate = lastDate.AddDays(DayOfWeek.Thursday - lastDay + oneWeek);
                }

                return deliveryDate;
            }
        }

        internal int ComputeAverageSellingSpeed(string flavor)
        {
            try
            {
                object average = this.Sales.Compute(
                    "AVG(Sold)",
                    String.Format(CultureInfo.CurrentUICulture, "Flavor = '{0}'", flavor));

                return (int)average;
            }
            catch (Exception ex)
            {
                System.Diagnostics.Debug.WriteLine(ex.ToString());
                throw;
            }
        }

        internal bool IsLastDayComplete()
        {
            try
            {
                object average = this.Sales.Compute("Count(Inventory)", "Date=MAX(Date)");

                return (int)average == this.Pricing.Count;
            }
            catch (Exception ex)
            {
                System.Diagnostics.Debug.WriteLine(ex.ToString());
                throw;
            }
        }

        private void EstimateInventory(OperationsBaseData.SalesRow row, double sellingSpeed)
        {
            double estimatedInventory = row.Inventory - sellingSpeed * (NextWeeklyDeliveryDate - row.Date).Days;
            row.Estimated_Inventory = estimatedInventory;

            if (estimatedInventory < 0)
            {
                row.Recommendation = Properties.Resources.CreateUnscheduledOrderRecommendation;
            }
            else
            {
                row.SetRecommendationNull();
            }
        }

        protected override void OnSalesInventoryChanged(DataColumnChangeEventArgs e)
        {
            SalesRow row = (SalesRow)e.Row;

            // 更改库存意味着更改当日和次日的销售额。
            if (row.RowState == DataRowState.Modified || row.RowState == DataRowState.Added)
            {
                ComputeSoldColumn(row);
                double sellingSpeed = ComputeAverageSellingSpeed(row.Flavor);

                SalesRow nextDay = this.Sales.FindByDateFlavor(row.Date.AddDays(1), row.Flavor);

                if (nextDay != null)
                {
                    ComputeSoldColumn(nextDay);
                    EstimateInventory(nextDay, sellingSpeed);
                }

                // 所有相关销售额所在列计算完毕后，
                // 便可以估计库存。
                EstimateInventory(row, sellingSpeed);
            }
        }
    }
}
