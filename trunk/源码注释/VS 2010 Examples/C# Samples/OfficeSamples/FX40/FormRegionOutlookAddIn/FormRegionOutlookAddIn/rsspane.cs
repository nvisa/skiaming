// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Office = Microsoft.Office.Core;
using Outlook = Microsoft.Office.Interop.Outlook;

namespace FormRegionOutlookAddIn
{
    partial class RssPane
    {
        #region 窗体区域工厂

        [Microsoft.Office.Tools.Outlook.FormRegionMessageClass(Microsoft.Office.Tools.Outlook.FormRegionMessageClassAttribute.PostRss)]
        [Microsoft.Office.Tools.Outlook.FormRegionName("FormRegionOutlookAddIn.RssPane")]
        public partial class RssPaneFactory
        {
            // 在初始化窗体区域之前发生。
            // 若要阻止窗体区域出现，请将 e.Cancel 设置为 true。
            // 使用 e.OutlookItem 获取对当前 Outlook 项的引用。
            private void RssPaneFactory_FormRegionInitializing(object sender, Microsoft.Office.Tools.Outlook.FormRegionInitializingEventArgs e)
            {
            }
        }

        #endregion

        // 在显示窗体区域之前发生。
        // 使用 this.OutlookItem 获取对当前 Outlook 项的引用。
        // 使用 this.OutlookFormRegion 获取对窗体区域的引用。
        private void RssPane_FormRegionShowing(object sender, System.EventArgs e)
        {
            Outlook.PostItem rssItem = (Outlook.PostItem)this.OutlookItem;

            this.webBrowserRss.Navigate(Helper.ParseUrl(rssItem));
        }

        // 在关闭窗体区域时发生。
        // 使用 this.OutlookItem 获取对当前 Outlook 项的引用。
        // 使用 this.OutlookFormRegion 获取对窗体区域的引用。
        private void RssPane_FormRegionClosed(object sender, System.EventArgs e)
        {
        }
    }
}
