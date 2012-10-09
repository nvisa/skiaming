// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。

using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using Office = Microsoft.Office;

namespace UiManagerOutlookAddIn
{
    public class TaskPaneConnector : Office.Core.ICustomTaskPaneConsumer
    {
        private Office.Core.ICTPFactory _ctpFactory;

        internal Microsoft.Office.Core.CustomTaskPane CreateTaskPane(string id, string title, object parentWindow)
        {
            if (_ctpFactory != null)
                return _ctpFactory.CreateCTP(id, title, parentWindow);

            return null;
        }
        
        
        // 此方法由于其 Office 参数的缘故不是 CLSCompliant。
        [CLSCompliant(false)]
        public void CTPFactoryAvailable(
            Office.Core.ICTPFactory CTPFactoryInst)
        {
            // 我们在此只需缓存 CTPFactory 对象， 
            // 以便今后能够创建自定义任务窗格。
            _ctpFactory = CTPFactoryInst;
        }
    }
}
