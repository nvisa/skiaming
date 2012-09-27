// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
//------------------------------------------------------------------------------
//扩展现有 Northwind 类的分部类。
//------------------------------------------------------------------------------

namespace nwind {
    using System.Data.Linq;
    using System.Data.Linq.Mapping;
    using System.Data;
    using System.Collections.Generic;
    using System.Reflection;
    using System.Linq;
    using System.Linq.Expressions;
    using System.ComponentModel;
    using System;

    public partial class Northwind {


        // 用于 CUD 重写示例
        partial void InsertRegion(Region instance)
        {
            // 此分部方法将调用 ExecuteDynamicInsert 来插入 Region 实例。
            // 如果不调用 ExecuteDynameicInsert 方法，还可以在此处调用存储过程
            // 接受参数，并将某个实例插入该表中。
            Console.WriteLine("***** Executing InsertRegion Override ******");
            Console.WriteLine("Calling up ExecuteDynamicInsert on a Region instance");
            this.ExecuteDynamicInsert(instance);
        }

        // 用于加载重写示例
        private IEnumerable<Product> LoadProducts(Category category)
        {
            // 此分部方法将调用 LinqToSql 查询加载某个类别的产品
            // 如果不调用 LinqToSQL 查询，这里还可以调用存储过程以加载产品
            Console.WriteLine("******** Using LinqToSQL query to load products belong to category that are not discontinued. ******");
            return this.Products.Where(p => p.CategoryID == category.CategoryID).Where(p=>!p.Discontinued);
        }



    }
    // 用于可扩展分部方法
    public partial class Order {

        [System.Diagnostics.DebuggerNonUserCode]
        partial void OnValidate(System.Data.Linq.ChangeAction action)
        {
            switch (action)
            {
                case ChangeAction.Delete:
                    break;
                case ChangeAction.Insert:
                    break;
                case ChangeAction.Update:
                    if (this.ShipVia > 100)
                        throw new Exception("Exception: ShipVia cannot be bigger than 100");
                    break;
                case ChangeAction.None:
                    break;

                default:
                    break;
            }

        }
    }
}
