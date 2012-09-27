// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Office = Microsoft.Office.Core;
using Outlook = Microsoft.Office.Interop.Outlook;

namespace FormRegionOutlookAddIn
{
    partial class RssRegion
    {
        #region 窗体区域工厂

        [Microsoft.Office.Tools.Outlook.FormRegionMessageClass(Microsoft.Office.Tools.Outlook.FormRegionMessageClassAttribute.PostRss)]
        [Microsoft.Office.Tools.Outlook.FormRegionName("FormRegionOutlookAddIn.RssRegion")]
        public partial class RssRegionFactory
        {
            // 在初始化窗体区域之前发生。
            // 若要阻止窗体区域出现，请将 e.Cancel 设置为 true。
            // 使用 e.OutlookItem 获取对当前 Outlook 项的引用。
            private void RssRegionFactory_FormRegionInitializing(object sender, Microsoft.Office.Tools.Outlook.FormRegionInitializingEventArgs e)
            {
            }
        }

        #endregion

        // 在显示窗体区域之前发生。
        // 使用 this.OutlookItem 获取对当前 Outlook 项的引用。
        // 使用 this.OutlookFormRegion 获取对窗体区域的引用。
        private void RssRegion_FormRegionShowing(object sender, System.EventArgs e)
        {
            this.RssRegionSplitContainer.Panel2Collapsed = true;

            Outlook.PostItem rssItem = (Outlook.PostItem)this.OutlookItem;

            this.webBrowserRss.Navigate(Helper.ParseUrl(rssItem));
        }

        // 在关闭窗体区域时发生。
        // 使用 this.OutlookItem 获取对当前 Outlook 项的引用。
        // 使用 this.OutlookFormRegion 获取对窗体区域的引用。
        private void RssRegion_FormRegionClosed(object sender, System.EventArgs e)
        {
        }

        // 单击“SearchSimilarTopicsbutton”将在单独窗格中打开“webBrowserSearch”。
        private void searchSimilarTopicsButton_Click(object sender, EventArgs e)
        {
            Outlook.PostItem rssItem = (Outlook.PostItem)this.OutlookItem;

            this.searchSimilarTopicsButton.Visible = false;

            this.RssRegionSplitContainer.Panel2Collapsed = false;

            // 通过将标题放置在 "" 中搜索匹配标题。
            this.webBrowserSearch.Navigate(string.Concat("http://www.bing.com/search?q=\"", rssItem.Subject, "\""));

            this.RssRegionSplitContainer.SplitterDistance = (this.OutlookFormRegion.Inspector.Width / 2);

            this.searchWindowProgressBar.Visible = true;
        }

        // 在“View Article”窗格中向后定位到 Rss 文章。
        private void viewRssBackButton_Click(object sender, EventArgs e)
        {
            this.webBrowserRss.GoBack();
        }

        // 设置“ViewRssProgressBar”属性的事件。
        private void webBrowserRss_Navigating(object sender, WebBrowserNavigatingEventArgs e)
        {
            this.viewRssProgressBar.Visible = true;

            this.viewRssProgressBar.Value = 0;
        }

        private void webBrowserRss_ProgressChanged(object sender, WebBrowserProgressChangedEventArgs e)
        {
            // 在“Navigating”和“DocumentCompleted”事件中设置“viewRssProgressBar.Visible”
            // 以便保持其正确更新，协调这三个事件。

            if (this.viewRssProgressBar.Visible)
            {
                // -1 表示下载已完成。
                if (e.CurrentProgress == -1)
                {
                    this.viewRssProgressBar.Value = 100;
                }
                else
                {
                    this.viewRssProgressBar.Value = (int)((100 * e.CurrentProgress) / e.MaximumProgress);
                }
            }

        }

        // 设置“ViewRssProgressBar”属性的事件。
        private void webBrowserRss_DocumentCompleted(object sender, WebBrowserDocumentCompletedEventArgs e)
        {
            this.viewRssProgressBar.Visible = false;

            this.viewRssProgressBar.Value = 0;
        }

        // 隐藏“Search Results”并展开“View Article”窗格。
        private void hideSearchResultsButton_Click(object sender, EventArgs e)
        {
            this.RssRegionSplitContainer.Panel2Collapsed = true;

            this.searchSimilarTopicsButton.Visible = true;
        }

        // 向后定位到“Search Results”。
        private void searchResultsBackButton_Click(object sender, EventArgs e)
        {
            this.webBrowserSearch.GoBack();
        }

        // 设置“Search ProgressBar”属性的事件。
        private void webBrowserSearch_Navigating(object sender, WebBrowserNavigatingEventArgs e)
        {
            this.searchWindowProgressBar.Visible = true;

            this.searchWindowProgressBar.Value = 0;
        }

        private void webBrowserSearch_ProgressChanged(object sender, WebBrowserProgressChangedEventArgs e)
        {
            // 在“Navigating”和“DocumentCompleted”事件中设置“searchWindowProgressBar.Visible”
            // 以便保持其正确更新，协调这三个事件。

            if (this.searchWindowProgressBar.Visible)
            {
                // -1 表示下载已完成。
                if (e.CurrentProgress == -1)
                {
                    this.searchWindowProgressBar.Value = 100;
                }
                else
                {
                    this.searchWindowProgressBar.Value = (int)((100 * e.CurrentProgress) / e.MaximumProgress);
                }
            }
        }

        // 设置 ProgressBar 属性的事件。
        private void webBrowserSearch_DocumentCompleted(object sender, WebBrowserDocumentCompletedEventArgs e)
        {
            this.searchWindowProgressBar.Visible = false;

            this.searchWindowProgressBar.Value = 0;
        }
    }
}
