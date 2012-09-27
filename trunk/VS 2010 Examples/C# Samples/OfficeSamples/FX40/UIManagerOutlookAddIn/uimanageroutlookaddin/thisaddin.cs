// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。


using System;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using Microsoft.VisualStudio.Tools.Applications.Runtime;
using Outlook = Microsoft.Office.Interop.Outlook;
using System.Collections;
using System.Collections.Generic;
using Office = Microsoft.Office;
using UiManagerOutlookAddIn.AddinUtilities;

namespace UiManagerOutlookAddIn
{
    // 此类由于其基类的缘故不是 CLSCompliant。
    [CLSCompliant(false)]
    public partial class ThisAddIn
    {

        #region 标准操作

        private void ThisAddIn_Shutdown(object sender, System.EventArgs e)
        {
        }

        private void InternalStartup()
        {
            this.Startup += new System.EventHandler(ThisAddIn_Startup);
            this.Shutdown += new System.EventHandler(ThisAddIn_Shutdown);
        }

        #endregion


        #region 字段

        internal TaskPaneConnector _taskPaneConnector;
        internal RibbonConnector _ribbonConnector;
        private FormRegionConnector _formRegionConnector;
        private Outlook.Inspectors _inspectors;
        private const String _controlProgId = "UiManager.SimpleControl";
        private const String _controlTitle = "SimpleControl";
        internal UserInterfaceElements _uiElements;

        #endregion


        #region 请求服务

        // 我们重写 RequestService 以便为
        // 我们实现的每个新扩展接口返回合适的对象。
        protected override object RequestService(Guid serviceGuid)
        {
            if (serviceGuid ==
                typeof(Office.Core.ICustomTaskPaneConsumer).GUID)
            {
                if (_taskPaneConnector == null)
                {
                    _taskPaneConnector = new TaskPaneConnector();
                }
                return _taskPaneConnector;
            }

            else if (serviceGuid ==
                typeof(Office.Core.IRibbonExtensibility).GUID)
            {
                if (_ribbonConnector == null)
                {
                    _ribbonConnector = new RibbonConnector();
                }
                return _ribbonConnector;
            }

            else if (serviceGuid ==
                typeof(Outlook.FormRegionStartup).GUID)
            {
                if (_formRegionConnector == null)
                {
                    _formRegionConnector = new FormRegionConnector();
                }
                return _formRegionConnector;
            }

            return base.RequestService(serviceGuid);
        }

        #endregion


        #region 启动

        private void ThisAddIn_Startup(object sender, System.EventArgs e)
        {
            System.Windows.Forms.Application.EnableVisualStyles();

            try
            {
                // 初始化 UI 元素集合，并挂钩 
                // NewInspector 事件，以便在创建每个检查器时能够将检查器 
                // 添加到集合。
                _uiElements = new UserInterfaceElements();
                _inspectors = this.Application.Inspectors;
                _inspectors.NewInspector +=
                    new Outlook.InspectorsEvents_NewInspectorEventHandler(
                    inspectors_NewInspector);
            }
            catch (COMException ex)
            {
                System.Diagnostics.Debug.WriteLine(ex.ToString());
            }
        }

        #endregion


        #region NewInspector

        // 新检查器打开时，创建任务窗格并将其附加到 
        // 此检查器。
        void inspectors_NewInspector(Outlook.Inspector Inspector)
        {
            CreateTaskPane(Inspector);
        }

        // 我们让公共方法具有此行为，以便 
        // 能够独立于 NewInspector 事件调用该行为。
        // 目的是为了允许争用条件，
        // 在此条件下可以在挂钩 NewInspector 事件之前进行
        // 功能区回调。
        public Office.Core.CustomTaskPane CreateTaskPane(
            Outlook.Inspector inspector)
        {
            Office.Core.CustomTaskPane taskpane = null;

            try
            {
                // 创建一个新的任务窗格，并将其宽度设置为与 
                // SimpleControl 宽度匹配。
                taskpane = _taskPaneConnector.CreateTaskPane(
                        _controlProgId, _controlTitle, inspector);
                if (taskpane != null)
                {
                    
                    taskpane.Width = 230;

                    // 将任务窗格映射到检查器，并将其缓存 
                    // 在集合中。
                    _uiElements.Add(new UserInterfaceContainer(
                        inspector, taskpane, _ribbonConnector));
                }
            }
            catch (COMException ex)
            {
                System.Diagnostics.Debug.WriteLine(ex.ToString());
            }

            return taskpane;
        }


        #endregion

    }
}
