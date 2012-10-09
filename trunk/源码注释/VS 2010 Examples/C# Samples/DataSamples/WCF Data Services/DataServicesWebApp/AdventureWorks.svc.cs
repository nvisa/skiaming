// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
using System;
using System.Collections.Generic;
using System.Data.Services;
using System.Linq;
using System.ServiceModel.Web;
using System.Web;

namespace DataServicesWebApp
{
    public class AdventureWorks : DataService<AdventureWorksLTEntities>
    {
        /// <summary>
        /// 仅调用此方法一次以初始化涉及服务范围的策略。
        /// </summary>
        public static void InitializeService(IDataServiceConfiguration config)
        {
            // TODO: 设置规则以指明哪些实体集和服务操作是可见的、可更新的，等等。
            // 示例:
            // config.SetEntitySetAccessRule("MyEntityset", EntitySetRights.AllRead);
            // config.SetServiceOperationAccessRule("MyServiceOperation", ServiceOperationRights.All);

            // 针对测试目的，请使用“*”表示所有实体集/服务操作。
            //不应在生产系统中使用“*”。
            // 此示例仅公开我们生成的应用程序所需要的实体集。
            // 此示例使用 EntitySetRight.All，它允许对实体集进行读写访问。
            config.SetEntitySetAccessRule("Products", EntitySetRights.All);
            config.SetEntitySetAccessRule("ProductCategories", EntitySetRights.All);
            config.SetEntitySetAccessRule("ProductDescriptions", EntitySetRights.All);
            config.SetEntitySetAccessRule("ProductModelProductDescriptions", EntitySetRights.All);
            config.SetEntitySetAccessRule("ProductModels", EntitySetRights.All);
        }
    }
}
