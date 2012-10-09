// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。

using System;
using System.ComponentModel;
using System.ComponentModel.Design;
using System.Collections;
using System.Drawing;
using System.Linq;
using System.Workflow.ComponentModel.Compiler;
using System.Workflow.ComponentModel.Serialization;
using System.Workflow.ComponentModel;
using System.Workflow.ComponentModel.Design;
using System.Workflow.Runtime;
using System.Workflow.Activities;
using System.Workflow.Activities.Rules;
using Microsoft.SharePoint;
using Microsoft.SharePoint.Workflow;
using Microsoft.SharePoint.WorkflowActions;

namespace SequentialWorkflow.Workflow1
{
    public sealed partial class Workflow1 : SequentialWorkflowActivity
    {
        public Workflow1()
        {
            InitializeComponent();
        }

        public Guid workflowId = default(System.Guid);
        public Guid taskId1 = default(System.Guid);
        public SPWorkflowActivationProperties workflowProperties = new SPWorkflowActivationProperties();
        public SPWorkflowTaskProperties taskProperties = new Microsoft.SharePoint.Workflow.SPWorkflowTaskProperties();
        public SPWorkflowTaskProperties afterProperties = new Microsoft.SharePoint.Workflow.SPWorkflowTaskProperties();
        public SPWorkflowTaskProperties beforeProperties1 = new Microsoft.SharePoint.Workflow.SPWorkflowTaskProperties();
        private bool taskCompleted;

        private void createTask1_MethodInvoking(object sender, EventArgs e)
        {
            //任务必须具有 GUID
            taskId1 = Guid.NewGuid();
            //设置基本任务属性
            taskProperties.PercentComplete = (float)0.0;
            taskProperties.AssignedTo = System.Threading.Thread.CurrentPrincipal.Identity.Name;
            //这在合并 InfoPath 窗体时非常有用
            taskProperties.TaskType = 0;
            taskProperties.DueDate = DateTime.Now.AddDays(7);
            taskProperties.StartDate = DateTime.Now;
            taskProperties.Title = "SharePoint Workflow Task";
        }

        private void notCompleted(object sender, ConditionalEventArgs e)
        {
            //要完成任务则结果必须为 1.0
            e.Result = !taskCompleted;
        }

        private void onTaskChanged1_Invoked(object sender, ExternalDataEventArgs e)
        {
            //更改后检查任务属性。
            //查找 1.0 以反映已完成的任务。
            if (afterProperties.PercentComplete == 1.0)
            {
                taskCompleted = true;
            }
        }
    }
}
