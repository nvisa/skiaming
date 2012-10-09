// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。

using Microsoft.VisualStudio.SharePoint;
using System;
using System.Collections.Generic;
using System.ComponentModel;

namespace Contoso.SharePointProjectItems.CustomAction
{
    internal partial class CustomActionProvider
    {
        private void ProjectItemPropertiesRequested(object sender,
            SharePointProjectItemPropertiesRequestedEventArgs e)
        {
            CustomActionProperties properties;

            // 如果项目对象已经存在，请从项目项的注释获取它。
            if (!e.ProjectItem.Annotations.TryGetValue(out properties))
            {
                // 否则，请创建一个新的属性对象，并将其添加到注释。
                properties = new CustomActionProperties(e.ProjectItem);
                e.ProjectItem.Annotations.Add(properties);
            }

            e.PropertySources.Add(properties);
        }
    }

    internal class CustomActionProperties
    {
        private ISharePointProjectItem projectItem;
        private const string testPropertyId = "Contoso.CustomActionTestProperty";
        private const string propertyDefaultValue = "This is a test value.";

        internal CustomActionProperties(ISharePointProjectItem projectItem)
        {
            this.projectItem = projectItem;
        }

        // 获取或设置一个简单的字符串属性。该属性值存储于该项目项的 ExtensionData 属性
        // 中。当该项目关闭时，ExtensionData 属性中的数据会保留。
        [DisplayName("Custom Action Property")]
        [DescriptionAttribute("This is a test property for the Contoso Custom Action project item.")]
        [DefaultValue(propertyDefaultValue)]
        public string TestProperty
        {
            get
            {
                string propertyValue;

                // 获取当前属性值(如果它已经存在)；否则，返回一个默认值。
                if (!projectItem.ExtensionData.TryGetValue(testPropertyId, out propertyValue))
                {
                    propertyValue = propertyDefaultValue;
                }
                return propertyValue;
            }
            set
            {
                if (value != propertyDefaultValue)
                {
                    projectItem.ExtensionData[testPropertyId] = value;
                }
                else
                {
                    // 请勿保存默认值。
                    projectItem.ExtensionData.Remove(testPropertyId);
                }
            }
        }
    }
}