using System;
using System.Security.Permissions;
using Microsoft.SharePoint;
using Microsoft.SharePoint.Security;
using Microsoft.SharePoint.Utilities;
using Microsoft.SharePoint.Workflow;
using System.Diagnostics;
// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
namespace Donation.DonationDeleting
{
    /// <summary>
    /// 列表项事件
    /// </summary>
    public class DonationDeleting : SPItemEventReceiver
    {
       /// <summary>
        /// 示例 EventHandler，可以防止用户在捐赠列表中删除金额大于零的项
       /// </summary>
       public override void ItemDeleting(SPItemEventProperties properties)
       {
           try
           {
               double amount = (double)properties.ListItem["Amount"];
               if (amount > 0)
               {
                   properties.ErrorMessage = "You cannot delete donations with an amount greater than 0. We want to keep the money!";
                   properties.Cancel = true;
               }
           }
           catch (Exception ex)
           {
               EventLog.WriteEntry("SP Event Handler", ex.Message);
           }
       }


    }
}
