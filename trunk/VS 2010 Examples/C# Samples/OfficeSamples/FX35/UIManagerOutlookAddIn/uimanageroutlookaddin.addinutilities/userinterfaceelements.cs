// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。


using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using Office = Microsoft.Office;
using Outlook = Microsoft.Office.Interop.Outlook;

namespace UiManagerOutlookAddIn.AddinUtilities
{
    public class UserInterfaceElements
    {

        #region 初始化

        private List<UserInterfaceContainer> _items;

        public UserInterfaceElements()
        {
            _items = new List<UserInterfaceContainer>();
        }

        #endregion


        #region 集合更新

        public void Add(UserInterfaceContainer uiContainer)
        {
            _items.Add(uiContainer);
            uiContainer.InspectorClose += 
                new EventHandler(uiContainer_InspectorClose);
        }

        // 当检查器关闭时，窗体区域也会关闭，所以我们需要 
        // 将此实例从集合中移除。
        void uiContainer_InspectorClose(object sender, EventArgs e)
        {
            _items.Remove(sender as UserInterfaceContainer);
        }

        public bool Remove(UserInterfaceContainer uiContainer)
        {
            return _items.Remove(uiContainer);
        }

        // 通过附加给定的 FormRegionControls 对象，更新
        // 给定检查器指示的集合中的 UI 容器对象。
        // 此方法由于其 Office 参数的缘故不符合 CLS。
        [CLSCompliant(false)]
        public bool AttachFormRegion(
            Outlook.Inspector inspector, 
            IFormRegionControls formRegionControls)
        {
            bool updateOK = false;

            // 在容器的集合中查找此检查器。
            UserInterfaceContainer uiContainer = 
                GetUIContainerForInspector(inspector);
            if (uiContainer != null)
            {
                uiContainer.FormRegionControls = formRegionControls;
                updateOK = true;
            }
            return updateOK;
        }

        #endregion


        #region 集合搜索

        // 在给定检查器的情况下，查找匹配的 UI 容器对象。
        // 此方法由于其 Office 参数的缘故不符合 CLS。
        [CLSCompliant(false)]
        public UserInterfaceContainer GetUIContainerForInspector(
            Outlook.Inspector inspector)
        {
            UserInterfaceContainer uiContainer = null;

            foreach (UserInterfaceContainer uic in _items)
            {
                if (uic.Inspector == inspector)
                {
                    uiContainer = uic;
                    break;
                }
            }
            return uiContainer;
        }

        // 在给定检查器的情况下，返回匹配的任务窗格。
        // 此方法由于其 Office 参数的缘故不符合 CLS。
        [CLSCompliant(false)]
        public Office.Core.CustomTaskPane GetTaskPaneForInspector(
            Outlook.Inspector inspector)
        {
            Office.Core.CustomTaskPane taskpane = null;

            foreach (UserInterfaceContainer uic in _items)
            {
                if (uic.Inspector == inspector)
                {
                    taskpane = uic.TaskPane;
                    break;
                }
            }
            return taskpane;
        }

        // 在给定检查器的情况下，返回匹配的功能区。
        // 此方法由于其 Office 参数的缘故不符合 CLS。
        [CLSCompliant(false)]
        public IRibbonConnector GetRibbonForInspector(
            Outlook.Inspector inspector)
        {
            IRibbonConnector ribbonConnector = null;

            foreach (UserInterfaceContainer uic in _items)
            {
                if (uic.Inspector == inspector)
                {
                    ribbonConnector = uic.RibbonConnector;
                    break;
                }
            }
            return ribbonConnector;
        }

        // 在给定 UserControl 的情况下，返回匹配的功能区。
        // 此方法由于其返回类型的缘故不符合 CLS。
        [CLSCompliant(false)]
        public IRibbonConnector GetRibbonForUserControl(
            UserControl userControl)
        {
            IRibbonConnector ribbonConnector = null;

            foreach (UserInterfaceContainer uic in _items)
            {
                if (uic.TaskPane.ContentControl == userControl)
                {
                    ribbonConnector = uic.RibbonConnector;
                    break;
                }
            }
            return ribbonConnector;
        }

        // 在给定 UserControl 的情况下，返回匹配的 UI 容器对象。
        public UserInterfaceContainer GetUIContainerForUserControl(
            UserControl userControl)
        {
            UserInterfaceContainer uiContainer = null;

            foreach (UserInterfaceContainer uic in _items)
            {
                if (uic.TaskPane.ContentControl == userControl)
                {
                    uiContainer = uic;
                    break;
                }
            }
            return uiContainer;
        }

        #endregion

    }
}
