// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。


using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using Outlook = Microsoft.Office.Interop.Outlook;
using Office = Microsoft.Office;

namespace UiManagerOutlookAddIn.AddinUtilities
{
    public class UserInterfaceContainer
    {
        
        #region 包含的 UI 元素

        private Outlook.InspectorEvents_10_Event _inspectorEvents;
        private Outlook.Inspector _inspector;
        private IFormRegionControls _formRegionControls;
        private IRibbonConnector _ribbonConnector;
        private Office.Core.CustomTaskPane _taskPane;
        private bool _isControlVisible;

        public event EventHandler InspectorClose;

        [CLSCompliant(false)]
        public Outlook.Inspector Inspector
        {
            get { return _inspector; }
            set { _inspector = value; }
        }

        [CLSCompliant(false)]
        public Office.Core.CustomTaskPane TaskPane
        {
            get { return _taskPane; }
            set { _taskPane = value; }
        }

        [CLSCompliant(false)]
        public IFormRegionControls FormRegionControls
        {
            get { return _formRegionControls; }
            set { _formRegionControls = value; }
        }


        [CLSCompliant(false)]
        public IRibbonConnector RibbonConnector
        {
            get { return _ribbonConnector; }
            set { _ribbonConnector = value; }
        }

        #endregion


        #region 功能区控件访问器

        public bool IsControlVisible
        {
            get { return _isControlVisible; }
        }

        public void ShowRibbonControl(String ribbonControlId)
        {
            _isControlVisible = true;
            _ribbonConnector.Ribbon.InvalidateControl(ribbonControlId);
        }

        public void HideRibbonControl(String ribbonControlId)
        {
            _isControlVisible = false;
            _ribbonConnector.Ribbon.InvalidateControl(ribbonControlId);
        }

        #endregion


        #region ctor

        // 此方法由于其 Office 参数的缘故不符合 CLS。
        [CLSCompliant(false)]
        public UserInterfaceContainer(
            Outlook.Inspector inspector, 
            Office.Core.CustomTaskPane taskPane, 
            IRibbonConnector ribbonConnector)
        {
            if (inspector != null)
            {
                _inspector = inspector;
                _taskPane = taskPane;
                _ribbonConnector = ribbonConnector;

                // 接收 InspectorClose 事件以便我们能够进行清理。
                _inspectorEvents = (Outlook.InspectorEvents_10_Event)_inspector;
                _inspectorEvents.Close +=
                    new Outlook.InspectorEvents_10_CloseEventHandler(
                    _inspectorEvents_Close);
            }
        }

        #endregion


        #region “检查器关闭”事件

        void _inspectorEvents_Close()
        {
            // 将我们自身从 UI 对象集合中移除， 
            // 解除挂钩关闭事件，然后清理所有引用。
            _inspectorEvents.Close -=
                new Outlook.InspectorEvents_10_CloseEventHandler(
                _inspectorEvents_Close);

            if (InspectorClose != null)
            {
                // 告诉所有侦听方我们正在关闭。
                InspectorClose(this, new EventArgs());
            }

            _inspector = null;
            _inspectorEvents = null;
            _taskPane = null;
            _formRegionControls = null;
            _ribbonConnector = null;
        }

        #endregion

    }
}
