// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。

using System;
using Microsoft.VisualStudio.SharePoint;

namespace Contoso.SharePointProjectItems.CustomAction
{
    internal partial class CustomActionProvider
    {
        private const string designerMenuItemText = "View Custom Action Designer";

        private void ProjectItemMenuItemsRequested(
            object sender, SharePointProjectItemMenuItemsRequestedEventArgs e)
        {
            e.ViewMenuItems.Add(designerMenuItemText).Click += MenuItemClick;
        }

        private void MenuItemClick(object sender, MenuItemEventArgs e)
        {
            ISharePointProjectItem projectItem = (ISharePointProjectItem)e.Owner;
            string message = String.Format("You clicked the menu on the {0} item. " +
                "You could perform some related task here, such as displaying a designer " +
                "for the custom action.", projectItem.Name);
            System.Windows.Forms.MessageBox.Show(message, "Contoso Custom Action");
        }
    }
}