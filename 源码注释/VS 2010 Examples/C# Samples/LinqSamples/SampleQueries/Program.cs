// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
//版权所有(C) Microsoft Corporation。保留所有权利。

using System;
using System.Collections.Generic;
using System.Windows.Forms;
using SampleSupport;
using SampleQueries;
using System.IO;
using DataSetSampleQueries;

// 有关其他信息，请参阅 ReadMe.html
namespace SampleQueries
{
    static class Program
    {
        /// <summary>
        /// 应用程序的主入口点。
        /// </summary>
        [STAThread]
        static void Main(string[] args)
        {
            List<SampleHarness> harnesses = new List<SampleHarness>();

            // LinqSamples:
            LinqSamples linqHarness = new LinqSamples();
            harnesses.Add(linqHarness);

            // Linq To SQL 示例:
            LinqToSqlSamples linqToSqlHarness = new LinqToSqlSamples();
            harnesses.Add(linqToSqlHarness);

            // LinqToXmlSamples:
            LinqToXmlSamples linqToXmlHarness = new LinqToXmlSamples();
            harnesses.Add(linqToXmlHarness);

            // DataSetLinqSamples:
            DataSetLinqSamples dsLinqSamples = new DataSetLinqSamples();
            harnesses.Add(dsLinqSamples);
            
            // XQueryUseCases:
            XQueryUseCases xqueryHarness = new XQueryUseCases();
            harnesses.Add(xqueryHarness);

            if (args.Length >= 1 && args[0] == "/runall") {
                foreach (SampleHarness harness in harnesses)
                {
                    harness.RunAllSamples();
                }
            }
            else {
                Application.EnableVisualStyles();
                
                using (SampleForm form = new SampleForm("LINQ Project Sample Query Explorer", harnesses))
                {
                    form.ShowDialog();
                }
            }
        }
    }
}