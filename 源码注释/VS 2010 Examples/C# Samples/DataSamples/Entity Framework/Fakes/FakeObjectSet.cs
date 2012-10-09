// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。


namespace EmployeeTracker.Fakes
{
    using System;
    using System.Collections;
    using System.Collections.Generic;
    using System.Data.Objects;
    using System.Linq;
    using System.Linq.Expressions;

    /// <summary>
    /// 基于内存中数据的 IObjectSet 实现
    /// </summary>
    /// <typeparam name="TEntity">要存储在集合中的数据的类型</typeparam>
    public sealed class FakeObjectSet<TEntity> : IObjectSet<TEntity> where TEntity : class
    {
        /// <summary>
        /// 此集合的基础数据
        /// </summary>
        private HashSet<TEntity> data;

        /// <summary>
        /// 基础数据的 IQueryable 版本
        /// </summary>
        private IQueryable query;

        /// <summary>
        /// 初始化 FakeObjectSet 类的新实例。
        /// 该实例不包含任何数据。
        /// </summary>
        public FakeObjectSet()
        {
            this.data = new HashSet<TEntity>();
            this.query = this.data.AsQueryable();
        }

        /// <summary>
        /// 初始化 FakeObjectSet 类的新实例。
        /// 实例包含所提供的数据。
        /// </summary>
        /// <param name="testData">要包括在集合中的数据</param>
        public FakeObjectSet(IEnumerable<TEntity> testData)
        {
            if (testData == null)
            {
                throw new ArgumentNullException("testData");
            }

            this.data = new HashSet<TEntity>(testData);
            this.query = this.data.AsQueryable();
        }

        /// <summary>
        /// 获取此集合中的元素的类型
        /// </summary>
        Type IQueryable.ElementType
        {
            get { return this.query.ElementType; }
        }

        /// <summary>
        /// 获取此集合的表达式树
        /// </summary>
        Expression IQueryable.Expression
        {
            get { return this.query.Expression; }
        }

        /// <summary>
        /// 获取此集合的查询提供程序
        /// </summary>
        IQueryProvider IQueryable.Provider
        {
            get { return this.query.Provider; }
        }

        /// <summary>
        /// 向此集合添加新项
        /// </summary>
        /// <param name="entity">要添加的项</param>
        public void AddObject(TEntity entity)
        {
            if (entity == null)
            {
                throw new ArgumentNullException("entity");
            }

            this.data.Add(entity);
        }

        /// <summary>
        /// 将新项从此集合中删除
        /// </summary>
        /// <param name="entity">要删除的项</param>
        public void DeleteObject(TEntity entity)
        {
            if (entity == null)
            {
                throw new ArgumentNullException("entity");
            }

            this.data.Remove(entity);
        }

        /// <summary>
        /// 向此集合附加新项
        /// </summary>
        /// <param name="entity">要附加的项</param>
        public void Attach(TEntity entity)
        {
            if (entity == null)
            {
                throw new ArgumentNullException("entity");
            }

            this.data.Add(entity);
        }

        /// <summary>
        /// 将新项从此集合分离
        /// </summary>
        /// <param name="entity">要分离的项</param>
        public void Detach(TEntity entity)
        {
            if (entity == null)
            {
                throw new ArgumentNullException("entity");
            }

            this.data.Remove(entity);
        }

        /// <summary>
        /// 获取此集合的枚举器
        /// </summary>
        /// <returns>返回此集合中的所有项的枚举器</returns>
        IEnumerator IEnumerable.GetEnumerator()
        {
            return this.data.GetEnumerator();
        }

        /// <summary>
        /// 获取此集合的类型化枚举器
        /// </summary>
        /// <returns>返回此集合中的所有项的枚举器</returns>
        IEnumerator<TEntity> IEnumerable<TEntity>.GetEnumerator()
        {
            return this.data.GetEnumerator();
        }
    }
}