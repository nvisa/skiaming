// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
using System;
using System.Collections.Generic;
using System.Text;
using System.Linq;
using System.Configuration;
using UserInterface.AdventureWorksService;
using System.Data.Services.Client;

namespace UserInterface.Gateways
{

    public class ProductGateway : IProductGateway
    {

        /// <summary>
        /// 表示数据服务的运行时上下文的 DataServiceContext 对象。
        /// </summary>
        AdventureWorksLTEntities context;

        /// <summary>
        /// 表示服务入口点的 URI
        /// </summary>
        Uri serviceUri;

        /// <summary>
        /// 初始化 DataServiceContext
        /// </summary>
        public ProductGateway()
        {
            serviceUri = new Uri("http://localhost:50000/AdventureWorks.svc");
            context = new AdventureWorksLTEntities(serviceUri);
            context.MergeOption = MergeOption.OverwriteChanges;
        }

        /// <summary>
        /// 如果没有指定产品名称，则返回具有指定 categoryId 的所有产品；否则，仅返回具有指定 categoryId 和产品名称的产品。
        /// </summary>
 	/// <param name="productName">用于查询产品的产品名称</param>
        /// <param name="category">用于查询产品的类别</param>
        public IList<Product> GetProducts(string productName, ProductCategory category)
        {
            IEnumerable<Product> query;
            
            int categoryId = category.ProductCategoryID;
            if (!String.IsNullOrEmpty(productName))
            {
                query = from p in context.Products.Expand("ProductCategory")
                        where p.ProductCategory.ProductCategoryID == categoryId && p.Name == productName
                        select p;
            }
            else
            {
                query = from p in context.Products.Expand("ProductCategory")
                        where p.ProductCategory.ProductCategoryID == categoryId
                        select p;
            }

            try
            {
                List<Product> productSet = query.ToList();
                return productSet;
            }catch(Exception)
            {
                return null;
            }
        }

        /// <summary>
        /// 返回所有产品类别
        /// </summary>
        public IList<ProductCategory> GetCategories()
        {
            return context.ProductCategories.ToList();
        }

        /// <summary>
        /// 尝试删除指定产品，如果该产品无法删除，则返回错误消息“无法删除产品”
        /// </summary>
	/// <param name="product">要删除的产品</param>
        public string DeleteProduct(Product product)
        {
            context.DeleteObject(product);
            
            try
            {
                context.SaveChanges();
            }
            catch (DataServiceRequestException)
            {
                return "Product Cannot be Deleted";
            }
            return null;
        }

 	/// <summary>
        /// 此方法假定所有字段都已更改，并更新整个实体，包括与 ProductCategory 的关联。
        /// 使用 SaveChangesOptions.Batch 将更改发送到服务器，以便所有操作都在单个 HTTP 请求中发送。
	/// </summary>
	/// <param name="product">要更新的产品</param>
        public void UpdateProduct(Product product)
        {
            ProductCategory newCategory = product.ProductCategory;
            context.SetLink(product, "ProductCategory", newCategory);
            context.UpdateObject(product);
            context.SaveChanges(SaveChangesOptions.Batch);
        }

 	/// <summary>
        /// 向 DataServiceContext 添加新产品对象，并将该对象与现有 ProductCategory 关联。
        /// 使用 SaveChangesOptions.Batch 将更改发送到服务器，以便所有操作都在单个 HTTP 请求中发送。
	/// </summary>
	/// <param name="product">要添加的产品</param>
        public void AddProduct(Product product)
        {
            product.rowguid = Guid.NewGuid();
            context.AddObject("Products", product);
            context.SetLink(product, "ProductCategory", product.ProductCategory);
            context.SaveChanges(SaveChangesOptions.Batch);
        }

    }
}
