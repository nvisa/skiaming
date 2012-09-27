// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
using System;
using System.Collections.Generic;
using LinqToTerraServerProvider.TerraServerReference;

[assembly: CLSCompliant(true)]
namespace LinqToTerraServerProvider
{
    internal static class WebServiceHelper
    {
        private static int numResults = 200;
        private static bool mustHaveImage = false;

        internal static Place[] GetPlacesFromTerraServer(List<string> locations)
        {
            // 限制 Web 服务调用的总数。
            if (locations.Count > 5)
                throw new InvalidQueryException("This query requires more than five separate calls to the Web service. Please decrease the number of locations in your query.");

            List<Place> allPlaces = new List<Place>();

            // 对于每个位置，调用 Web 方法以获取数据。
            foreach (string location in locations)
            {
                Place[] places = CallGetPlaceListMethod(location);
                allPlaces.AddRange(places);
            }

            return allPlaces.ToArray();
        }

        private static Place[] CallGetPlaceListMethod(string location)
        {
            TerraServiceSoapClient client = new TerraServiceSoapClient();
            PlaceFacts[] placeFacts = null;

            try
            {
                // 调用 Web 服务方法“GetPlaceList”。
                placeFacts = client.GetPlaceList(location, numResults, mustHaveImage);

                // 如果恰好有“numResults”个结果，它们可能会被截断。
                if (placeFacts.Length == numResults)
                    throw new InvalidQueryException("The results have been truncated by the Web service and would not be complete. Please try a different query.");

                // 根据 Web 服务返回的 PlaceFacts 对象创建 Place 对象。
                Place[] places = new Place[placeFacts.Length];
                for (int i = 0; i < placeFacts.Length; i++)
                {
                    places[i] = new Place(
                        placeFacts[i].Place.City,
                        placeFacts[i].Place.State,
                        placeFacts[i].PlaceTypeId);
                }

                // 关闭 WCF 客户端。
                client.Close();

                return places;
            }
            catch (TimeoutException)
            {
                client.Abort();
                throw;
            }
            catch (System.ServiceModel.CommunicationException)
            {
                client.Abort();
                throw;
            }
        }
    }
}
