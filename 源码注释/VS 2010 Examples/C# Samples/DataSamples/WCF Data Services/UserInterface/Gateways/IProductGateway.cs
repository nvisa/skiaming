// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UserInterface.AdventureWorksService;


namespace UserInterface.Gateways
{
    public interface IProductGateway
    {
        IList<Product> GetProducts(string productName, ProductCategory category);
        IList<ProductCategory> GetCategories();
        string DeleteProduct(Product product);
        void UpdateProduct(Product product);
        void AddProduct(Product product);
    }
}
