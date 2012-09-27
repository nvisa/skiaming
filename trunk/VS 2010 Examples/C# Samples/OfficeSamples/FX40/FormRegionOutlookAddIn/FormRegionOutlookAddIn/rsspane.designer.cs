// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。

namespace FormRegionOutlookAddIn
{
    [System.ComponentModel.ToolboxItemAttribute(false)]
    partial class RssPane : Microsoft.Office.Tools.Outlook.FormRegionBase
    {
        public RssPane(Microsoft.Office.Interop.Outlook.FormRegion formRegion)
            : base(Globals.Factory, formRegion)
        {
            this.InitializeComponent();
        }

        /// <summary> 
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// 清理所有正在使用的资源。
        /// </summary>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region 组件设计器生成的代码

        /// <summary> 
        /// 设计器支持所需的方法 - 请勿 
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.webBrowserRss = new System.Windows.Forms.WebBrowser();
            this.SuspendLayout();
            // 
            // webBrowserRss
            // 
            this.webBrowserRss.Dock = System.Windows.Forms.DockStyle.Fill;
            this.webBrowserRss.Location = new System.Drawing.Point(0, 0);
            this.webBrowserRss.MinimumSize = new System.Drawing.Size(20, 20);
            this.webBrowserRss.Name = "webBrowserRss";
            this.webBrowserRss.Size = new System.Drawing.Size(725, 525);
            this.webBrowserRss.TabIndex = 0;
            // 
            // RssPane
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.webBrowserRss);
            this.Name = "RssPane";
            this.Size = new System.Drawing.Size(725, 525);
            this.FormRegionClosed += new System.EventHandler(this.RssPane_FormRegionClosed);
            this.FormRegionShowing += new System.EventHandler(this.RssPane_FormRegionShowing);
            this.ResumeLayout(false);
        }

        #endregion

        #region 窗体区域设计器生成的代码

        /// <summary> 
        /// 设计器支持所需的方法 - 请勿 
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private static void InitializeManifest(Microsoft.Office.Tools.Outlook.FormRegionManifest manifest)
        {
            manifest.FormRegionName = "RSS Article";
            manifest.FormRegionType = Microsoft.Office.Tools.Outlook.FormRegionType.Adjoining;
            manifest.ShowInspectorCompose = false;
            manifest.ShowInspectorRead = false;

        }

        #endregion

        private System.Windows.Forms.WebBrowser webBrowserRss;

        public partial class RssPaneFactory : Microsoft.Office.Tools.Outlook.IFormRegionFactory
        {
            public event Microsoft.Office.Tools.Outlook.FormRegionInitializingEventHandler FormRegionInitializing;

            private Microsoft.Office.Tools.Outlook.FormRegionManifest _Manifest;

            [System.Diagnostics.DebuggerNonUserCodeAttribute()]
            public RssPaneFactory()
            {
                this._Manifest = Globals.Factory.CreateFormRegionManifest();
                RssPane.InitializeManifest(this._Manifest);
                this.FormRegionInitializing += new Microsoft.Office.Tools.Outlook.FormRegionInitializingEventHandler(this.RssPaneFactory_FormRegionInitializing);
            }

            [System.Diagnostics.DebuggerNonUserCodeAttribute()]
            public Microsoft.Office.Tools.Outlook.FormRegionManifest Manifest
            {
                get
                {
                    return this._Manifest;
                }
            }

            [System.Diagnostics.DebuggerNonUserCodeAttribute()]
            Microsoft.Office.Tools.Outlook.IFormRegion Microsoft.Office.Tools.Outlook.IFormRegionFactory.CreateFormRegion(Microsoft.Office.Interop.Outlook.FormRegion formRegion)
            {
                RssPane form = new RssPane(formRegion);
                form.Factory = this;
                return form;
            }

            [System.Diagnostics.DebuggerNonUserCodeAttribute()]
            byte[] Microsoft.Office.Tools.Outlook.IFormRegionFactory.GetFormRegionStorage(object outlookItem, Microsoft.Office.Interop.Outlook.OlFormRegionMode formRegionMode, Microsoft.Office.Interop.Outlook.OlFormRegionSize formRegionSize)
            {
                throw new System.NotSupportedException();
            }

            [System.Diagnostics.DebuggerNonUserCodeAttribute()]
            bool Microsoft.Office.Tools.Outlook.IFormRegionFactory.IsDisplayedForItem(object outlookItem, Microsoft.Office.Interop.Outlook.OlFormRegionMode formRegionMode, Microsoft.Office.Interop.Outlook.OlFormRegionSize formRegionSize)
            {
                if (this.FormRegionInitializing != null)
                {
                    Microsoft.Office.Tools.Outlook.FormRegionInitializingEventArgs cancelArgs =
                        Globals.Factory.CreateFormRegionInitializingEventArgs(outlookItem, formRegionMode, formRegionSize, false);
                    this.FormRegionInitializing(this, cancelArgs);
                    return !cancelArgs.Cancel;
                }
                else
                {
                    return true;
                }
            }




            public Microsoft.Office.Tools.Outlook.FormRegionKindConstants Kind
            {
                get { return Microsoft.Office.Tools.Outlook.FormRegionKindConstants.WindowsForms; }
            }
        }
    }

    partial class WindowFormRegionCollection
    {
        internal RssPane RssPane
        {
            get
            {
                foreach (var item in this)
                {
                    if (item.GetType() == typeof (RssPane))
                        return (RssPane)item;
                }
                return null;
            }
        }
    }
}
