// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。

using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Xml.Linq;
using Microsoft.VisualStudio.Tools.Applications.Runtime;
using Excel = Microsoft.Office.Interop.Excel;
using Office = Microsoft.Office.Core;

namespace DocumentProtectionExcel
{
    public partial class ThisWorkbook
    {
        /// <summary>
        /// ActionsPane 上的 DataGridView 控件和 
        /// Sheet1 上的 ListObject 控件共享同一个 BindingSource。当 DataGridView 中的值 
        /// 更改时，ListObject 值也将相应地更改。但是， 
        /// 由于 Sheet1 受到保护，因此若要使 ListObject 的值能得以更改，需要取消对 Sheet1 的
        /// 保护。
        /// </summary>
        internal class CustomerBindingSource : BindingSource
        {
            protected override void OnListChanged(System.ComponentModel.ListChangedEventArgs e)
            {
                try
                {
                    try
                    {
                        // 取消对 Sheet1 的保护
                        Globals.Sheet1.UnprotectSheet();
                        base.OnListChanged(e);
                    }
                    finally
                    {
                        // 保护 Sheet1
                        Globals.Sheet1.ProtectSheet();
                    }
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message,
                        "Error protecting or unprotecting sheet",
                        MessageBoxButtons.OK,
                        MessageBoxIcon.Error,
                        MessageBoxDefaultButton.Button1);
                }
            }
        }

        /// <summary>
        /// 将添加到“操作”窗格的用户控件。
        /// </summary>
        private TechniqueUserControl techUserControl;
        /// <summary>
        /// 用于存储 ExcelSampleData XML 文件中的数据的数据集。
        /// </summary>
        internal DataSet customerDataSet = null;
        /// <summary>
        /// 用于将数据绑定到数据集的绑定源。
        /// </summary>
        internal CustomerBindingSource custBindingSource = null;

        #region 方法
        /// <summary>
        /// 使用 ExcelSampleData XML 文件中的数据加载 DataSet。
        /// </summary>
        private void LoadDataSet()
        {
            try
            {
                if (customerDataSet == null)
                    customerDataSet = new DataSet();
                // 获取架构文件位置
                string schemaFileLocation = System.IO.Path.Combine(Path, "ExcelSampleData.xsd");
                // 获取 XML 文件位置
                string xmlFileLocation = System.IO.Path.Combine(Path, "ExcelSampleData.xml");

                // 从架构和 XML 文件读取数据
                customerDataSet.ReadXmlSchema(schemaFileLocation);
                customerDataSet.ReadXml(xmlFileLocation);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message,
                                "Error loading data set.",
                                MessageBoxButtons.OK,
                                MessageBoxIcon.Error,
                                MessageBoxDefaultButton.Button1);
            }
        }
        #endregion

        /// <summary>
        /// 处理工作簿的 Startup 事件。当此事件激发时， 
        /// 将调用 LoadDataSet 方法将 XML 文件中的数据加载到
        /// customerDataSet，将 customerBindingSource 的 DataSource 属性设置  
        /// 为 customerDataSet，并将其 DataMember 属性设置为“Customers”。应创建 TechniqueUserControl
        /// 并将其附加到 ActionsPane。
        /// </summary>
        /// <param name="sender">未使用。</param>
        /// <param name="e">未使用。</param>
        private void ThisWorkbook_Startup(object sender, System.EventArgs e)
        {
            // 从 XML 文件加载数据集
            LoadDataSet();

            // 创建 BindingSource
            if (custBindingSource == null)
                custBindingSource = new CustomerBindingSource();
            custBindingSource.DataSource = customerDataSet;
            custBindingSource.DataMember = "Customer";

            //当 ListObject 尝试更改大小时，在数据网格中添加行将不会取消保护工作表，
            //这将导致发生异常。请将
            // AllowNew 属性设置为 false 可以强制数据集保持相同大小。
            custBindingSource.AllowNew = false;

            // 将用户控件添加到“操作”窗格。
            techUserControl = new TechniqueUserControl();
            ActionsPane.Controls.Add(techUserControl);
        }

        private void ThisWorkbook_Shutdown(object sender, System.EventArgs e)
        {
        }
        #region VSTO 设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 请勿
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InternalStartup()
        {
            this.Startup += new System.EventHandler(ThisWorkbook_Startup);
            this.Shutdown += new System.EventHandler(ThisWorkbook_Shutdown);
        }

        #endregion

    }
}
