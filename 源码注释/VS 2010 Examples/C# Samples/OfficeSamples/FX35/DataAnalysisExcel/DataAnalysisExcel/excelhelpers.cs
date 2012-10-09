// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。

using System;
using Microsoft.Office.Core;
using System.Data;
using System.Data.OleDb;
using System.Data.SqlClient;
using Excel = Microsoft.Office.Interop.Excel;

namespace DataAnalysisExcel
{
    /// <summary>
    /// ExcelHelper 的摘要说明。
    /// </summary>
    internal class ExcelHelpers
    {
        #region "与工作表相关的函数"

        /// <summary>
        /// 对名称中的特殊字符进行转义和截断，以使其
        /// 可以作为 Excel 中的工作表名称。该名称被截断为 31 个
        /// 字符；字符“:”、“\”、“/”、“?”、“*”、“[”和“]”将替换为
        /// “_”。
        /// </summary>
        /// <param name="name">原始名称。</param>
        /// <returns>转义名称。</returns>
        static internal string CreateValidWorksheetName(string name)
        {
            // 工作表名称不能超过 31 个字符。
            System.Text.StringBuilder escapedString;

            if (name.Length <= 31)
            {
                escapedString = new System.Text.StringBuilder(name);
            }
            else
            {
                escapedString = new System.Text.StringBuilder(name, 0, 31, 31);
            }

            for (int i = 0; i < escapedString.Length; i++)
            {
                if (escapedString[i] == ':' ||
                    escapedString[i] == '\\' ||
                    escapedString[i] == '/' ||
                    escapedString[i] == '?' ||
                    escapedString[i] == '*' ||
                    escapedString[i] == '[' ||
                    escapedString[i] == ']')
                {
                    escapedString[i] = '_';
                }
            }

            return escapedString.ToString();
        }

        /// <summary>
        /// 返回给定名称的工作表。
        /// </summary>
        /// <param name="workbook">包含该工作表的工作簿。</param>
        /// <param name="name">所需工作表的名称。</param>
        /// <returns>工作簿中具有给定名称的工作表。</returns>
        static internal Excel.Worksheet GetWorksheet(Excel.Workbook workbook, string name)
        {
            return workbook.Worksheets[name] as Excel.Worksheet;
        }

        /// <summary>
        /// 返回给定索引处的工作表。
        /// </summary>
        /// <param name="workbook">包含该工作表的工作簿。</param>
        /// <param name="index">所需工作表的索引。</param>
        /// <returns>工作簿中具有给定名称的工作表。</returns>
        static internal Excel.Worksheet GetWorksheet(Excel.Workbook workbook, int index)
        {
            return workbook.Worksheets[index] as Excel.Worksheet;
        }

        /// <summary>
        /// 从工作簿中返回活动工作表。
        /// </summary>
        /// <param name="workbook">包含该工作表的工作簿。</param>
        /// <returns>给定工作簿中的活动工作表。</returns>
        static internal Excel.Worksheet GetActiveSheet(Excel.Workbook workbook)
        {
            return workbook.ActiveSheet as Excel.Worksheet;
        }

        /// <summary>
        /// 返回工作表或图表的名称。
        /// </summary>
        /// <param name="item">工作表或图表。</param>
        /// <returns>工作表或图表的名称。</returns>
        static internal string GetName(object item)
        {
            string itemName;

            Excel.Worksheet sheet = item as Excel.Worksheet;
            if (sheet != null)
            {
                itemName = sheet.Name;
            }
            else
            {
                Excel.Chart chart = item as Excel.Chart;

                if (chart != null)
                {
                    itemName = chart.Name;
                }
                else
                {
                    itemName = null;
                }
            }

            return itemName;
        }

      #endregion
        #region "与范围相关的函数"

        /// <summary>
        /// 返回范围的并集。
        /// </summary>
        /// <param name="range1">要联合的第一个范围。</param>
        /// <param name="range2">要联合的第二个范围。</param>
        /// <param name="ranges">要联合的一系列范围。</param>
        /// <returns>返回一个范围，其中包含所有已传入范围的并集。</returns>
        static internal Excel.Range Union(Excel.Range range1,
           Excel.Range range2,
           params Excel.Range[] ranges)
        {
            // 除前两个以外的所有范围。
            object[] overflowParameters = new object[28];


            ranges.CopyTo(overflowParameters, 0);

            for (int i = ranges.Length;
               i < overflowParameters.Length;
               i++)
            {
                overflowParameters[i] = Type.Missing;
            }

            return range1.Application.Union(
               range1,
               range2,
               overflowParameters[0],
               overflowParameters[1],
               overflowParameters[2],
               overflowParameters[3],
               overflowParameters[4],
               overflowParameters[5],
               overflowParameters[6],
               overflowParameters[7],
               overflowParameters[8],
               overflowParameters[9],
               overflowParameters[10],
               overflowParameters[11],
               overflowParameters[12],
               overflowParameters[13],
               overflowParameters[14],
               overflowParameters[15],
               overflowParameters[16],
               overflowParameters[17],
               overflowParameters[18],
               overflowParameters[19],
               overflowParameters[20],
               overflowParameters[21],
               overflowParameters[22],
               overflowParameters[23],
               overflowParameters[24],
               overflowParameters[25],
               overflowParameters[26],
               overflowParameters[27]
               );
        }


        /// <summary>
        /// 返回范围的交集。
        /// </summary>
        /// <param name="range1">要相交的第一个范围。</param>
        /// <param name="range2">要相交的第二个范围。</param>
        /// <param name="ranges">要相交的一系列范围。</param>
        /// <returns>返回一个范围，其中包含所有已传入范围的交集。</returns>
        static internal Excel.Range Intersect(Excel.Range range1,
           Excel.Range range2,
         params Excel.Range[] ranges)
        {
            // 除前两个以外的所有范围。
            object[] overflowParameters = new object[28];


            ranges.CopyTo(overflowParameters, 0);

            for (int i = ranges.Length;
               i < overflowParameters.Length;
               i++)
            {
                overflowParameters[i] = Type.Missing;
            }

            return range1.Application.Intersect(
               range1,
               range2,
               overflowParameters[0],
               overflowParameters[1],
               overflowParameters[2],
               overflowParameters[3],
               overflowParameters[4],
               overflowParameters[5],
               overflowParameters[6],
               overflowParameters[7],
               overflowParameters[8],
               overflowParameters[9],
               overflowParameters[10],
               overflowParameters[11],
               overflowParameters[12],
               overflowParameters[13],
               overflowParameters[14],
               overflowParameters[15],
               overflowParameters[16],
               overflowParameters[17],
               overflowParameters[18],
               overflowParameters[19],
               overflowParameters[20],
               overflowParameters[21],
               overflowParameters[22],
               overflowParameters[23],
               overflowParameters[24],
               overflowParameters[25],
               overflowParameters[26],
               overflowParameters[27]
               );
        }

        /// <summary>
        /// 从工作簿中返回具有给定名称的范围。
        /// </summary>
        /// <param name="workbook">包含命名范围的工作簿。</param>
        /// <param name="name">所需范围的名称。</param>
        /// <returns>工作簿中具有给定名称的范围。</returns>
        internal static Excel.Range GetNamedRange(Excel.Workbook workbook, string name)
        {
            Excel.Name nameObject = workbook.Names.Item(
               name,
               Type.Missing,
               Type.Missing);

            return nameObject.RefersToRange;
        }

        /// <summary>
        /// 从给定工作表中返回具有给定名称的范围。
        /// </summary>
        /// <param name="worksheet">包含命名范围的工作表。</param>
        /// <param name="name">所需范围的名称。</param>
        /// <returns>给定工作表中具有给定名称的范围。</returns>
        internal static Excel.Range GetNamedRange(Excel.Worksheet worksheet, string name)
        {
            return worksheet.get_Range(name, Type.Missing);
        }

        /// <summary>
        /// 返回一个包含列的范围，其中的列在该范围的指定索引处。
        /// </summary>
        /// <param name="rowRange">包含所需列的范围。</param>
        /// <param name="column">该范围中所需列的索引。</param>
        /// <returns>包含给定范围中指定列的范围。</returns>
        internal static Excel.Range GetColumnFromRange(Excel.Range rowRange, int column)
        {
            return rowRange.Columns[column, Type.Missing] as Excel.Range;
        }

        /// <summary>
        /// 返回一个包含行的范围，其中的行在该范围的指定索引处。
        /// </summary>
        /// <param name="columnRange">包含所需行的范围。</param>
        /// <param name="row">该范围中所需行的索引。</param>
        /// <returns>包含给定范围中指定行的范围。</returns>
        internal static Excel.Range GetRowFromRange(Excel.Range columnRange, int row)
        {
            return columnRange.Rows[row, Type.Missing] as Excel.Range;
        }

        /// <summary>
        /// 返回一个由单元格组成的范围，其中的单元格在指定行和列上。
        /// </summary>
        /// <param name="range">包含所需单元格的范围。</param>
        /// <param name="row">包含所需单元格的行的索引。</param>
        /// <param name="column">包含所需单元格的列的索引。</param>
        /// <returns></returns>
        internal static Excel.Range GetCellFromRange(Excel.Range range, int row, int column)
        {
            return range.Cells[row, column] as Excel.Range;
        }

        /// <summary>
        /// 以对象形式返回给定范围的值。
        /// </summary>
        /// <param name="range">要从中获取值的范围。</param>
        /// <param name="address">要从中提取值的子范围的本地地址。</param>
        /// <returns>返回由该地址指定的子范围中单元格的值。</returns>
        internal static Object GetValue(Excel.Range range, string address)
        {
            return range.get_Range(address, Type.Missing).Value2;
        }

        /// <summary>
        /// 以双精度形式返回给定范围的值。
        /// </summary>
        /// <param name="range">要从中获取值的范围。</param>
        /// <returns>以双精度形式返回该范围的值。</returns>
        internal static double GetValueAsDouble(Excel.Range range)
        {
            if (range.Value2 is double)
            {
                return (double)range.Value2;
            }

            return double.NaN;
        }

        /// <summary>
        /// 以双精度形式返回指定索引处的单元格的值。
        /// </summary>
        /// <param name="sheet">包含所需单元格的工作表。</param>
        /// <param name="row">包含该单元格的工作表中的行。</param>
        /// <param name="column">包含该单元格的工作表中的列。</param>
        /// <returns>以双精度形式返回给定索引处的单元格的值。</returns>
        internal static double GetValueAsDouble(Excel.Worksheet sheet, int row, int column)
        {
            Excel.Range subRange = ((Excel.Range)sheet.Cells[row, column]);

            return GetValueAsDouble(subRange);
        }

        /// <summary>
        /// 以双精度形式返回指定索引处的单元格的值。
        /// </summary>
        /// <param name="range">包含所需单元格的范围。</param>
        /// <param name="row">包含该单元格的范围中的行。</param>
        /// <param name="column">包含该单元格的范围中的列。</param>
        /// <returns>以双精度形式返回指定索引处的单元格的值。</returns>
        internal static double GetValueAsDouble(Excel.Range range, int row, int column)
        {
            Excel.Range subRange = ((Excel.Range)range.Cells[row, column]);

            return GetValueAsDouble(subRange);
        }

        /// <summary>
        /// 以字符串形式返回给定范围的值。
        /// </summary>
        /// <param name="range">要从中获取值的范围。</param>
        /// <returns>以字符串形式返回给定范围的值。</returns>
        internal static string GetValueAsString(Excel.Range range)
        {
            if (!(range.Value2 == null))
            {
                return range.Value2.ToString();
            }

            return null;
        }

        /// <summary>
        /// 以字符串形式返回指定索引处的单元格的值。
        /// </summary>
        /// <param name="range">包含所需单元格的范围。</param>
        /// <param name="row">包含该单元格的范围中的行。</param>
        /// <param name="column">包含该单元格的范围中的列。</param>
        /// <returns>以字符串形式返回指定索引处的单元格的值。</returns>
        internal static string GetValueAsString(Excel.Range range, int row, int column)
        {
            Excel.Range subRange = ((Excel.Range)range.Cells[row, column]);

            return GetValueAsString(subRange);
        }

        /// <summary>
        /// 以字符串形式返回指定索引处的单元格的值。
        /// </summary>
        /// <param name="sheet">包含所需单元格的工作表。</param>
        /// <param name="row">包含该单元格的工作表中的行。</param>
        /// <param name="column">包含该单元格的工作表中的列。</param>
        /// <returns>以字符串形式返回给定索引处的单元格的值。</returns>
        internal static string GetValueAsString(Excel.Worksheet sheet, int row, int column)
        {
            Excel.Range subRange = ((Excel.Range)sheet.Cells[row, column]);

            return GetValueAsString(subRange);
        }

      #endregion
        #region "与形状相关的函数"
        /// <summary>
        /// 从活动工作表中获取具有给定名称的形状。
        /// </summary>
        /// <param name="workbook">包含该形状的工作簿。</param>
        /// <param name="name">该形状的名称。</param>
        /// <returns>从活动工作表中返回具有给定名称的形状。</returns>
        static internal Excel.Shape GetShape(Excel.Workbook workbook, string name)
        {
            return GetShape(GetActiveSheet(workbook), name);
        }

        /// <summary>
        /// 从活动工作表中获取给定索引处的形状。
        /// </summary>
        /// <param name="workbook">包含该形状的工作簿。</param>
        /// <param name="index">该形状的索引。</param>
        /// <returns>从活动工作表中返回给定索引处的形状。</returns>
        static internal Excel.Shape GetShape(Excel.Workbook workbook, int index)
        {
            return GetShape(GetActiveSheet(workbook), index);
        }

        /// <summary>
        /// 从给定工作表中获取具有给定名称的形状。
        /// </summary>
        /// <param name="worksheet">包含该形状的工作表。</param>
        /// <param name="name">该形状的名称。</param>
        /// <returns>从给定工作表中获取具有给定名称的形状。</returns>
        static internal Excel.Shape GetShape(Excel.Worksheet worksheet, string name)
        {
            return worksheet.Shapes._Default(name);
        }

        /// <summary>
        /// 从给定工作表中获取给定索引处的形状。
        /// </summary>
        /// <param name="worksheet">包含该形状的工作表。</param>
        /// <param name="index">该形状的索引。</param>
        /// <returns>从给定工作表中返回给定索引处的形状。</returns>
        static internal Excel.Shape GetShape(Excel.Worksheet worksheet, int index)
        {
            return worksheet.Shapes._Default(index);
        }
      #endregion
        #region "与日期相关的函数"
        // Excel 中的日期从 1900 年 1 月 1 日开始。
        // 使用 1899 年 12 月 30 日的原因有两个。
        // 一个原因是 1900 年 2 月 29 日在 Excel 中有效
        // (实际上，它是无效日期: 1900 年不是闰年)；
        // 另一个原因是 Excel 中的 0 与 1 月 0 日相对应。
        private readonly static DateTime timeOrigin =
           new DateTime(1899, 12, 30, 0, 0, 0, 0);

        /// <summary>
        /// 以 Excel 的十进制等效值返回日期。
        /// </summary>
        /// <param name="dateValue">要转换的日期。</param>
        /// <returns>Excel 中日期的十进制表示形式。</returns>
        internal static double GetSerialDate(DateTime dateValue)
        {
            TimeSpan since1900 = dateValue - timeOrigin;

            return since1900.Days;
        }

        /// <summary>
        /// 从 Excel 中日期的十进制表示形式返回 DateTime。
        /// </summary>
        /// <param name="serial">Excel 中的十进制日期值。</param>
        /// <returns>Excel 中十进制日期表示形式的 DateTime 等效值。</returns>
        internal static DateTime GetDateTime(double serial)
        {
            TimeSpan since1900 = new TimeSpan((int)serial, 0, 0, 0);

            return timeOrigin.Add(since1900);
        }

      #endregion


        public static stdole.IPictureDisp Convert(System.Drawing.Image image)
        {
            return ImageToPictureConverter.Convert(image);
        }

        /// <summary>
        /// 用于公开 AxHost 的受保护的方法 GetIPictureDispFromPicture
        /// 的类。
        /// </summary>
        sealed private class ImageToPictureConverter : System.Windows.Forms.AxHost
        {
            private ImageToPictureConverter()
                : base(null)
            {
            }

            public static stdole.IPictureDisp Convert(System.Drawing.Image image)
            {
                return (stdole.IPictureDisp)System.Windows.Forms.AxHost.GetIPictureDispFromPicture(image);
            }
        }
    }
}
