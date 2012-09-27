// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
using System;
using System.Linq;
using LinqToTerraServerProvider;

[assembly: CLSCompliant(true)]
namespace ClientApp
{
    public sealed class Program
    {
        static void Main()
        {
            QueryableTerraServerData<Place> terraPlaces = new QueryableTerraServerData<Place>();

            // 第一个查询。
            var query1 = from place in terraPlaces
                        where place.Name== "Redmond"
                        select place.State;

            Console.WriteLine("States that have a place named \"Redmond\":");
            foreach (string name in query1)
                Console.WriteLine(name);

            // 第二个查询。
            var count = (from place in terraPlaces
                         where place.Name.StartsWith("Lond")
                         select place).Count();

            Console.WriteLine("\nNumber of places whose names start with \"Lond\": " + count + "\n");

            // 第三个查询。
            string[] places = { "Johannesburg", "Yachats", "Seattle" };

            var query3 = from place in terraPlaces
                        where places.Contains(place.Name)
                        orderby place.State
                        select new { place.Name, place.State };

            Console.WriteLine("Places, ordered by state, whose name is either \"Johannesburg\", \"Yachats\", or \"Seattle\":");
            foreach (var obj in query3)
                Console.WriteLine(obj);

            Console.ReadLine();
        }

        private Program() { }
    }
}
