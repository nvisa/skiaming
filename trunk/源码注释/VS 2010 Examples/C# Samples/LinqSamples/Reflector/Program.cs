// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
//版权所有(C) Microsoft Corporation。保留所有权利。

using System;
using System.Diagnostics;
using System.IO;
using System.Xml;
using System.Reflection;
using System.Xml.Linq;

// 有关其他信息，请参阅 ReadMe.html
namespace Samples
{
    public static class Program
    {
        const string HtmlFile = "System.Xml.Linq.html";
        
        public static void Main()
        {
            // 获取要反射的程序集的路径和名称
            XDocument attr = new XDocument();
            Assembly assembly = Assembly.GetAssembly(attr.GetType());
            String AssemblyFile = assembly.CodeBase;

            // 对程序集进行反射
            Reflector reflector = new Reflector();
            reflector.Reflect(AssemblyFile);
            
            // 生成 HTML 文档
            XmlWriterSettings settings = new XmlWriterSettings();
            settings.OmitXmlDeclaration = true;
            settings.Indent = true;
            XmlWriter writer = XmlWriter.Create(HtmlFile, settings);
            reflector.Transform(writer);
            writer.Close();
       
            // 显示 HTML 文档
            FileInfo fileInfo = new FileInfo(HtmlFile);
            if (fileInfo.Exists) Process.Start("iexplore.exe", fileInfo.FullName);
        }
    }
}