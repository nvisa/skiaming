// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。

using System;
using System.Windows.Forms;
using Excel = Microsoft.Office.Interop.Excel;
using System.Globalization;

namespace DataAnalysisExcel
{
    internal class OrderingSheet
    {
        object defaultParameter = System.Type.Missing;

        internal enum StatHeadings
        {
            DailySales = 0,
            Required,
            CurrentInventory,
            ProjectInventory,
            OrderQuanity
        }

        private string[] headers = {
            Properties.Resources.MaxDailySalesHeader, 
            Properties.Resources.ProjectedSalesHeader, 
            Properties.Resources.CurrentInventoryHeader,
            Properties.Resources.ProjectedInventoryHeader,
            Properties.Resources.OrderQuantityHeader
        };

        DateTime deliveryDate;

        DateTime nextScheduledDeliveryDate;

        DateTime orderDate;

        Excel.Worksheet worksheet;

        const string orderDateAddress = "$B$4";
        const string pivotTableAddress = "$B$10";

        internal OrderingSheet(bool isUnscheduled)
        {
            if (!Globals.DataSet.IsLastDayComplete())
            {
                throw new ApplicationException(Globals.ThisWorkbook.IncompleteDataMessage);
            }

            this.orderDate = Globals.DataSet.MaxDate;

            string worksheetName;

            if (isUnscheduled)
            {
                worksheetName = ExcelHelpers.CreateValidWorksheetName(
                    String.Format(
                        CultureInfo.CurrentUICulture, 
                        Properties.Resources.UnscheduledOrderSheetName,
                        this.orderDate.ToShortDateString()));
            }
            else
            {
                worksheetName = ExcelHelpers.CreateValidWorksheetName(
                    String.Format(
                        CultureInfo.CurrentUICulture,
                        Properties.Resources.WeeklyOrderSheetName,
                        this.orderDate.ToShortDateString()));
            }
            Excel.Worksheet worksheet = null;

            // 如果该名称已经存在，则在创建工作表时将引发异常。
            try
            {
                worksheet = Globals.ThisWorkbook.CreateWorksheet(worksheetName);
            }
            catch (Exception ex)
            {
                string message;

                if (isUnscheduled)
                {
                    message = String.Format(
                        CultureInfo.CurrentUICulture,
                        Properties.Resources.UnscheduledOrderSheetCreationError,
                        worksheetName);
                }
                else
                {
                    message = String.Format(
                        CultureInfo.CurrentUICulture,
                        Properties.Resources.WeeklyOrderSheetCreationError,
                        worksheetName);
                }

                throw new ApplicationException(message, ex);
            }

            this.worksheet = worksheet;

            CreateOrder(isUnscheduled);
        }

        internal OrderingSheet(Excel.Worksheet worksheet, DateTime orderDate, bool isUnscheduled)
        {
            this.orderDate = orderDate;
            this.worksheet = worksheet;

            CreateOrder(isUnscheduled);
        }

        private DateTime ComputeUnscheduledDeliveryDate()
        {
            return this.orderDate.AddDays(1).Date;
        }

        private DateTime ComputeWeeklyDeliveryDate()
        {
            return Globals.DataSet.NextWeeklyDeliveryDate;
        }

        private void CreateOrder(bool isUnscheduled)
        {
            if (isUnscheduled)
            {
                this.deliveryDate = ComputeUnscheduledDeliveryDate();
                this.nextScheduledDeliveryDate = ComputeWeeklyDeliveryDate();
            }
            else
            {
                this.deliveryDate = ComputeWeeklyDeliveryDate();
                this.nextScheduledDeliveryDate = this.deliveryDate.AddDays(7);
            }

            // 这会创建一个数据透视表，其中包含 
            // 与冰淇淋的销售量有关的信息。
            this.PopulateDateInformation(this.orderDate);

            Excel.PivotTable pivotTable = this.CreatePivotTable();

            this.AddCalculations(pivotTable);
        }

        private void AddCalculations(Excel.PivotTable pivotTable)
        {
            // 获取构成数据透视表的范围。
            Excel.Range tableRange = pivotTable.TableRange1;
            Excel.Range dataRange = pivotTable.DataBodyRange;

            // 获取需要添加到数据透视表后面的
            // 每个列。
            System.Array values = Enum.GetValues(typeof(StatHeadings));

            // 确定数据透视表的左上角单元格。
            Excel.Range tableStartCell = ExcelHelpers.GetCellFromRange(tableRange, 1, 1);

            // 获取数据透视表末尾相应行中的
            // 第一个可用单元格。
            Excel.Range nextHeader = tableStartCell.get_End(Excel.XlDirection.xlDown).get_End(Excel.XlDirection.xlToRight).get_End(Excel.XlDirection.xlUp).Next;

            // 确定构成当前列的计算字段的
            // 边界单元格。
            Excel.Range colStart = ExcelHelpers.GetCellFromRange(nextHeader, 2, 1);

            Excel.Range colEnd = colStart.get_Offset(dataRange.Rows.Count - 1, 0);

            // 对于需要添加的每一列，
            // 填充其统计信息和标题。

            foreach (int i in values)
            {
                nextHeader.Value2 = this.headers[i];
                this.PopulateStatColumn(i, colStart, colEnd);
                nextHeader = nextHeader.Next;
                colStart = colStart.Next;
                colEnd = colEnd.Next;
            }
        }

        private void PopulateStatColumn(int column, Excel.Range start, Excel.Range end)
        {
            try
            {
                // 确定需要用数据填充的范围。
                Excel.Range twoLines = start.get_Resize(2, 1);

                twoLines.Merge(System.Type.Missing);

                Excel.Range fillRange = this.worksheet.get_Range(start, end);
                end.Select();

                switch (column)
                {
                    case (int)StatHeadings.DailySales:
                        // 填充日销售额列。
                        // 获取包含标准偏差和
                        // 平均值的单元格的地址。
                        Excel.Range average = start.Previous;
                        string averageAddress = average.get_Address(false, false, Excel.XlReferenceStyle.xlA1, defaultParameter, defaultParameter);
                        Excel.Range standardDev = average.get_Offset(1, 0);
                        string standardDevAddress = standardDev.get_Address(false, false, Excel.XlReferenceStyle.xlA1, defaultParameter, defaultParameter);

                        // 设置该列的公式。
                        start.Formula = "=" + averageAddress + "+ (2*" + standardDevAddress + ")";

                        // 格式“0.00”- 两个小数位。
                        start.NumberFormat = "0.00";
                        twoLines.AutoFill(fillRange, Excel.XlAutoFillType.xlFillDefault);
                        break;

                    case (int)StatHeadings.Required:
                        // 填充所需的列。
                        // 确定包含预期销售额的
                        // 单元格的地址。
                        Excel.Range expectedSales = start.Previous;
                        string salesAddress = expectedSales.get_Address(false, false, Excel.XlReferenceStyle.xlA1, defaultParameter, defaultParameter);

                        // 确定交货前需要多少 
                        // 库存。
                        // 确定交货前的天数。
                        int waitDays = this.GetDaysToDelivery();

                        start.Formula = "=" + waitDays + "*" + salesAddress;

                        // 格式“0.00”- 两个小数位。
                        start.NumberFormat = "0.00";
                        twoLines.AutoFill(fillRange, Excel.XlAutoFillType.xlFillDefault);
                        break;

                    case (int)StatHeadings.CurrentInventory:
                        // 填充当前库存列。
                        // 从日记中获取上一天的范围。
                        int count = (end.Row - start.Row + 1) / 2;
                        Excel.Range currentCell = start;

                        for (int row = 0; row < count; row += 1)
                        {
                            Excel.Range flavorCell = currentCell.get_Offset(0, 0 - 5);


                            string flavor = ExcelHelpers.GetValueAsString(flavorCell);
                            int inventory = Globals.DataSet.Sales.FindByDateFlavor(Globals.DataSet.MaxDate, flavor).Inventory;

                            currentCell.Value2 = inventory;

                            if (row != 0)
                            {
                                Excel.Range twoCells = currentCell.get_Resize(2, 1);

                                twoCells.Merge(System.Type.Missing);
                                currentCell = twoCells;
                            }

                            currentCell = currentCell.get_Offset(1, 0);
                        }

                        break;

                    case (int)StatHeadings.ProjectInventory:

                        // 获取预计销售额和
                        // 当前库存的地址。
                        Excel.Range currentInventory = start.Previous;
                        Excel.Range required = currentInventory.Previous;
                        string currentInventoryAddress = currentInventory.get_Address(false, false, Excel.XlReferenceStyle.xlA1, defaultParameter, defaultParameter);
                        string requiredAddress = required.get_Address(false, false, Excel.XlReferenceStyle.xlA1, defaultParameter, defaultParameter);

                        // 确定交货日期的 
                        // 预计库存。
                        start.Formula = "=MAX(0," + currentInventoryAddress + "-" + requiredAddress + ")";

                        // 格式“0.00”- 两个小数位。
                        start.NumberFormat = "0.00";
                        twoLines.AutoFill(fillRange, Excel.XlAutoFillType.xlFillDefault);
                        break;

                    case (int)StatHeadings.OrderQuanity:
                        // 确定预计库存和
                        // 所需库存量的地址。
                        Excel.Range projectedInventory = start.Previous;
                        Excel.Range needed = projectedInventory.Previous.Previous;
                        string projectedInventoryAddress = projectedInventory.get_Address(false, false, Excel.XlReferenceStyle.xlA1, defaultParameter, defaultParameter);
                        string neededAddress = needed.get_Address(false, false, Excel.XlReferenceStyle.xlA1, defaultParameter, defaultParameter);

                        // 确定每一项所需的订货量。
                        start.Formula = "=" + neededAddress + "-" + projectedInventoryAddress;

                        // 格式“0.00”- 两个小数位。
                        start.NumberFormat = "0.00";
                        twoLines.AutoFill(fillRange, Excel.XlAutoFillType.xlFillDefault);
                        break;

                    default:
                        break;
                }
            }
            catch (Exception ex)
            {
                System.Diagnostics.Debug.WriteLine(ex.ToString());
                throw;
            }
        }

        private int GetDaysToDelivery()
        {
            // 此方法确定距离下一个
            // 计划交货日期的天数。
            // 这是估计已订货天数所需的。

            TimeSpan difference = this.nextScheduledDeliveryDate - this.deliveryDate;

            return difference.Days;
        }

        Excel.PivotTable CreatePivotTable()
        {
            TextFileGenerator generator = new TextFileGenerator(Globals.DataSet.Sales);

            try
            {
                Excel.Range destination = this.worksheet.get_Range(pivotTableAddress, defaultParameter);
                Excel.PivotTable pivotTable;

                pivotTable = Globals.ThisWorkbook.CreateSalesPivotTable(destination, generator.FullPath);

                // 调整新的数据透视表的属性 
                pivotTable.ColumnGrand = false;
                pivotTable.RowGrand = false;

                // 在数据透视表中，添加所需的 
                // 行和列。
                pivotTable.AddFields("Flavor", defaultParameter, defaultParameter, defaultParameter);

                Excel.PivotField soldField = pivotTable.AddDataField(pivotTable.PivotFields("Sold"), Properties.Resources.AverageOfUnitsSold, Excel.XlConsolidationFunction.xlAverage);

                // 在数据透视表中设置所需数据的视图。
                // 格式“0.0”- 一个小数位。
                soldField.NumberFormat = "0.0";

                Excel.PivotField profitField = pivotTable.AddDataField(pivotTable.PivotFields("Sold"), Properties.Resources.StdDevOfUnitsSold, Excel.XlConsolidationFunction.xlStDev);

                // 在数据透视表中设置所需数据的视图。
                // 格式“0.00”- 两个小数位。
                profitField.NumberFormat = "0.00";

                // 隐藏创建数据透视表时添加的两个浮动栏。
                Globals.ThisWorkbook.ShowPivotTableFieldList = false;
                Globals.ThisWorkbook.Application.CommandBars["PivotTable"].Visible = false;

                return pivotTable;
            }
            catch (Exception ex)
            {
                System.Diagnostics.Debug.WriteLine(ex.ToString());
                throw;
            }
            finally
            {
                generator.Dispose();
            }

        }


        private void PopulateDateInformation(DateTime selectedDate)
        {
            // 此方法用下一个订货日期及其相应的 
            // 交货日期来填充工作表。
            // 获取下一个订货日期并填充该日期。
            Excel.Range orderDateCell = worksheet.get_Range(orderDateAddress, defaultParameter);

            orderDateCell.Value2 = Properties.Resources.OrderDateHeader;
            orderDateCell.Next.Value2 = selectedDate.ToShortDateString();

            Excel.Range deliveryDateCell = ExcelHelpers.GetCellFromRange(orderDateCell, 2, 1);

            deliveryDateCell.Value2 = Properties.Resources.DeliveryDateHeader;
            deliveryDateCell.Next.Value2 = this.deliveryDate.ToShortDateString();
        }

    }
}