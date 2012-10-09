// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
using System;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Expressions;

namespace LinqToTerraServerProvider
{
    class TerraServerQueryContext
    {
        private TerraServerQueryContext() { }

        // 执行传递给它的表达式树。
        internal static object Execute(Expression expression, bool IsEnumerable)
        {
            // 表达式必须代表对数据源的查询。
            if (!IsQueryOverDataSource(expression))
                throw new InvalidProgramException("No query over the data source was specified.");

            // 找到对 Where() 的调用，并获取 lambda 表达式谓词。
            InnermostWhereFinder whereFinder = new InnermostWhereFinder();
            MethodCallExpression whereExpression = whereFinder.GetInnermostWhere(expression);
            LambdaExpression lambdaExpression = (LambdaExpression)((UnaryExpression)(whereExpression.Arguments[1])).Operand;

            // 通过分部计算器发送 lambda 表达式。
            lambdaExpression = (LambdaExpression)Evaluator.PartialEval(lambdaExpression);

            // 获取要用于查询 Web 服务的位置名称。
            LocationFinder lf = new LocationFinder(lambdaExpression.Body);
            List<string> locations = lf.Locations;
            if (locations.Count == 0)
                throw new InvalidQueryException("You must specify at least one place name in your query.");

            // 调用 Web 服务并获取结果。
            Place[] places = WebServiceHelper.GetPlacesFromTerraServer(locations);

            // 将 IEnumerable 位置复制到 IQueryable。
            IQueryable<Place> queryablePlaces = places.AsQueryable<Place>();

            // 复制传入的表达式，只更改
            // 最内侧 MethodCallExpression 的第一个参数。
            ExpressionTreeModifier treeCopier = new ExpressionTreeModifier(queryablePlaces);
            Expression newExpressionTree = treeCopier.CopyAndModify(expression);

            // 此步骤将创建一个 IQueryable，它通过用可枚举方法替代可查询方法方法执行。
            if (IsEnumerable)
                return queryablePlaces.Provider.CreateQuery(newExpressionTree);
            else
                return queryablePlaces.Provider.Execute(newExpressionTree);
        }

        private static bool IsQueryOverDataSource(Expression expression)
        {
            // 如果表达式代表未查询的 IQueryable 数据源实例，
            // 则表达式的类型为 ConstantExpression，而不是 MethodCallExpression。
            return (expression is MethodCallExpression);
        }
    }
}
