// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。

using System;
using System.Diagnostics;
using System.ComponentModel;
using System.ComponentModel.Composition;
using Microsoft.VisualStudio.SharePoint;

namespace Contoso.SharePointProjectItems.CustomAction
{
    // 令 Visual Studio 可以发现和加载此扩展。
    [Export(typeof(ISharePointProjectItemTypeProvider))]

    // 为此项目项类型指定 ID。此字符串必须与 
    // 该项目项的 .spdata 文件中 ProjectItem 元素的 Type 特性的值相匹配。
    [SharePointProjectItemType("Contoso.CustomAction")]

    // 指定在解决方案资源管理器中要与此项目项一起显示的图标。
    [SharePointProjectItemIcon("ProjectItemDefinition.CustomAction_SolutionExplorer.ico")]

    // 定义项目项的一个新类型，该项目项可以用于在 SharePoint 站点上创建一个自定义操作。
    internal partial class CustomActionProvider : ISharePointProjectItemTypeProvider
    {
        private ISharePointProjectService projectService;

        // 实现 IProjectItemTypeProvider.InitializeType。配置该项目项类型的行为。
        public void InitializeType(ISharePointProjectItemTypeDefinition projectItemTypeDefinition)
        {
            projectItemTypeDefinition.Name = "CustomAction";
            projectItemTypeDefinition.SupportedDeploymentScopes =
                SupportedDeploymentScopes.Site | SupportedDeploymentScopes.Web;
            projectItemTypeDefinition.SupportedTrustLevels = SupportedTrustLevels.All;

            // 获取服务，以便此类中的其他代码可以使用它。
            projectService = projectItemTypeDefinition.ProjectService;

            // 处理某些项目项事件。
            projectItemTypeDefinition.ProjectItemInitialized += ProjectItemInitialized;
            projectItemTypeDefinition.ProjectItemNameChanged += ProjectItemNameChanged;
            projectItemTypeDefinition.ProjectItemDisposing += ProjectItemDisposing;

            // 处理事件以便为此项目项创建自定义属性和快捷菜单项。
            projectItemTypeDefinition.ProjectItemPropertiesRequested +=
                ProjectItemPropertiesRequested;
            projectItemTypeDefinition.ProjectItemMenuItemsRequested +=
                ProjectItemMenuItemsRequested;
        }

        private void ProjectItemInitialized(object sender, SharePointProjectItemEventArgs e)
        {
            // 处理项目事件。
            e.ProjectItem.Project.PropertyChanged += ProjectPropertyChanged;
        }

        private void ProjectItemNameChanged(object sender, NameChangedEventArgs e)
        {
            ISharePointProjectItem projectItem = (ISharePointProjectItem)sender;
            string message = String.Format("The name of the {0} item changed to: {1}",
                e.OldName, projectItem.Name);
            projectService.Logger.WriteLine(message, LogCategory.Message);
        }

        private void ProjectPropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            ISharePointProject project = (ISharePointProject)sender;
            string message = String.Format("The following property of the {0} project was changed: {1}",
                    project.Name, e.PropertyName);
            projectService.Logger.WriteLine(message, LogCategory.Message);
        }

        private void ProjectItemDisposing(object sender, SharePointProjectItemEventArgs e)
        {
            e.ProjectItem.Project.PropertyChanged -= ProjectPropertyChanged;
        }
    }
}