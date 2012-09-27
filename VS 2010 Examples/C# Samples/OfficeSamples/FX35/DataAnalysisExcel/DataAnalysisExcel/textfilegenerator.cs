// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。

using System;
using System.Text;
using System.Data;
using System.IO;

namespace DataAnalysisExcel
{
    /// <summary>
    /// 此类构造用制表符分隔的 Unicode 文本文件，其中包含 Sales
    /// 数据表中的数据。首先，在当前用户的 temp 文件夹 
    /// 下创建一个随机命名的文件夹。 
    /// 然后，在该文件夹中创建一个名为 data.txt 的文件。
    /// 在该文件夹中创建另一个名为 schema.ini 的文件，其中包含
    /// 用于创建数据透视表的设置。通过共享数据文件的文件夹，
    /// 此文件可以由数据透视表自动发现。
    /// </summary>
    internal class TextFileGenerator : IDisposable
    {
        /// <summary>
        /// 已创建的临时文件的完整路径。
        /// </summary>
        private string fullPath;

        /// <summary>
        /// 已创建的顶级文件夹的完整路径。
        /// </summary>
        private string rootPath;

        /// <summary>
        /// 用来指示此对象创建的所有文件和目录已被删除
        /// (例如，DeleteCreatedFiles() 已被调用)的字段。
        /// </summary>
        private bool disposed;

        /// <summary>
        /// data.txt 文件的完整路径。
        /// </summary>
        /// <value>data.txt 文件的完整路径。</value>
        internal string FullPath
        {
            get
            {
                return fullPath;
            }
        }

        /// <summary>
        /// 构造函数。创建临时文件夹、data.txt 文件和 schema.ini 文件。
        /// </summary>
        /// <param name="dt">Sales 表。</param>
        internal TextFileGenerator(DataTable dt)
        {
            string directoryName;
            string rootName;
            
            GenerateSecureTempFolder(out directoryName, out rootName);

            this.rootPath = rootName;
            this.fullPath = Path.Combine(directoryName, "data.txt");

            Encoding textEncoding;

            textEncoding = Encoding.Unicode;

            System.IO.Directory.CreateDirectory(directoryName);
            using (StreamWriter writer = new StreamWriter(this.fullPath, false, textEncoding, 512))
            {
                int remaining = dt.Columns.Count;

                foreach (DataColumn column in dt.Columns)
                {
                    writer.Write(QuoteString(column.ColumnName));

                    if (--remaining != 0)
                    {
                        writer.Write('\t');
                    }
                }

                writer.Write("\r\n");
                foreach (DataRow row in dt.Rows)
                {
                    int remainingItems = row.ItemArray.Length;

                    foreach (object item in row.ItemArray)
                    {
                        writer.Write(QuoteString(item.ToString()));

                        if (--remainingItems != 0)
                        {
                            writer.Write('\t');
                        }
                    }
                    writer.Write("\r\n");
                }
            }

            CreateSchemaIni();
        }

        ~TextFileGenerator()
        {
            InternalDispose();
        }

        /// <summary>
        /// 为数据透视表配置创建 schema.ini 文件。
        /// </summary>
        private void CreateSchemaIni()
        {
            string contentsFormat = @"[{0}]
ColNameHeader=True
Format=TabDelimited
MaxScanRows=0
CharacterSet=Unicode
Col1=Date Char Width 255
Col2=Flavor Char Width 255
Col3=Inventory Integer
Col4=Sold Integer
Col5=Estimated Float
Col6=Recommendation Char Width 255
Col7=Profit Float
";
            string fileName = Path.Combine(Path.GetDirectoryName(this.fullPath), "schema.ini");

            using (StreamWriter writer = new StreamWriter(fileName, false, Encoding.Default, contentsFormat.Length + this.fullPath.Length))
            {
                writer.Write(contentsFormat, Path.GetFileName(this.fullPath));
            }
        }

        /// <summary>
        // 实现 IDisposable。
        // 不要使此方法成为虚拟方法。
        // 派生类不应重写此方法。
        public void Dispose()
        {
            InternalDispose();

            // 此对象将由 Dispose 方法清除。
            // 因此，您应当调用 GC.SupressFinalize，
            // 以便将此对象从终止队列中删除 
            // 并防止再次执行此对象的
            // 终止代码。
            GC.SuppressFinalize(this);
        }

        private void InternalDispose()
        {
            // 查看是否已调用了 Dispose。
            if (!this.disposed)
            {
                // 调用相应的方法，以便在此处 
                // 清除非托管资源。
                // 如果 disposing 为 false， 
                // 则将仅执行以下代码。
                DeleteCreatedFiles();
            }
            disposed = true;
        }

        /// 删除已创建的文件夹及其内容。
        /// </summary>
        private void DeleteCreatedFiles()
        {
            if (this.rootPath != null)
            {
                System.IO.Directory.Delete(rootPath, true);
                this.rootPath = null;
            }
        }

        /// <summary>
        /// 用来生成安全的目录结构文件名的 Helper
        /// 方法。
        /// </summary>
        /// <param name="createdFolder">
        /// 随机的安全路径。
        /// </param>
        /// <param name="createdRoot">
        /// 创建的顶级路径。 
        /// </param>
        private static void GenerateSecureTempFolder(out string createdFolder, out string createdRoot)
        {
            string directoryName = Path.Combine(Path.GetTempPath(), GenerateRandomName());
            createdRoot = directoryName;
            directoryName = Path.Combine(directoryName, GenerateRandomName());
            createdFolder = directoryName;
        }

        /// <summary>
        /// 用来生成随机文件名的 Helper 
        /// 方法。
        /// </summary>
        /// <returns>随机的安全目录名。</returns>
        private static string GenerateRandomName()
        {
            byte[] data = new byte[9];
            StringBuilder randomString;

            // 检索一些随机字节。
            new System.Security.Cryptography.RNGCryptoServiceProvider().GetBytes(data);

            // 将字节转换为字符串。这将生成一个 12 个字符的字符串。
            randomString = new StringBuilder(System.Convert.ToBase64String(data));

            // 转换为 8.3 文件名格式
            randomString[8] = '.';

            // 替换任何非法的文件名字符。
            randomString = randomString.Replace('/', '-');
            randomString = randomString.Replace('+', '_');

            // 返回字符串。
            return randomString.ToString();
        }

        /// <summary>
        /// 将字符串放在引号(")内。字符串内的所有引号都是双引号。
        /// </summary>
        /// <param name="s"></param>
        /// <returns></returns>
        private static string QuoteString(string s)
        {
            StringBuilder sb = new StringBuilder("\"", s.Length + 2);

            sb.Append(s.Replace("\"", "\"\""));
            sb.Append('"');
            return sb.ToString();
        }
    }
}
