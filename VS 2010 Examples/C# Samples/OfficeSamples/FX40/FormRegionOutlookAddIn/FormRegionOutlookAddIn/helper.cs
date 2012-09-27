// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。


using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Outlook = Microsoft.Office.Interop.Outlook;

namespace FormRegionOutlookAddIn
{
    static class Helper
    {
        // 返回出现在 RSS 项的标题中的“View article”链接的 URL。 
        public static string ParseUrl(Outlook.PostItem item)
        {
            const string lookUpText = "HYPERLINK";
            const string articleStr = "View article";
            string body = item.Body;

            int index = body.IndexOf(lookUpText, 0, body.Length);
            int end = 0;
            // 在正文中查找“HYPERLINKS”并将范围缩小到“View article...”链接。
            while (true)
            {
                end = body.IndexOf(articleStr, index, body.Length - index);
                int nextIndex = body.IndexOf(lookUpText, index + 1, body.Length - (index + 1));

                if (nextIndex > index && nextIndex < end)
                {
                    index = nextIndex;
                }
                else
                    break;
            }
            // 获取文章的链接。
            string url = body.Substring(index + lookUpText.Length + 1, end - index - (lookUpText.Length + 1));

            url = url.Trim('"');

            return url;
        }
    }
}
