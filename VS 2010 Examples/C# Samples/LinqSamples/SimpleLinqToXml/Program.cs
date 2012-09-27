// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
//版权所有(C) Microsoft Corporation。保留所有权利。

using System;
using System.Xml;
using System.Xml.Linq;

// 有关其他信息，请参阅 Readme.html 文件
namespace Samples
{
    public class Program
    {
        public static void Main()
        {
            // 使用类似 XML DOM 的方法
            // 构造预定义文档
            XDocument document = CreateDocumentVerbose();

            // 在控制台中显示文档
            Console.WriteLine(document);

            // 将所有节点转储到控制台
            DumpNode(document);

            // 使用起作用的方法
            // 再次构造预定义文档
            document = CreateDocumentConcise();
            
            // 在控制台中显示文档
            Console.WriteLine(document);

            // 将所有节点转储到控制台
            DumpNode(document);

            Console.ReadLine();
        }

        // <?xml version="1.0"?>
        // <?order alpha ascending?>
        // <art xmlns='urn:art-org:art'>
        //   <period name='Renaissance' xmlns:a='urn:art-org:artists'>
        //     <a:artist>Leonardo da Vinci</a:artist>
        //     <a:artist>Michelangelo</a:artist>
        //     <a:artist><![CDATA[Donatello]]></a:artist>
        //   </period>
        //   <!-- 在此处插入 period -->
        // </art>
        public static XDocument CreateDocumentVerbose()
        {
            XNamespace nsArt = "urn:art-org:art";
            XNamespace nsArtists = "urn:art-org:artists";

            // 创建文档
            XDocument document = new XDocument();

            // 创建 xml 声明，并在
            // 文档中对其进行设置
            document.Declaration = new XDeclaration("1.0", null, null);

            // 创建 art 元素，并将其
            // 添加到文档中
            XElement art = new XElement(nsArt + "art");
            document.Add(art);

            // 创建顺序处理指令，并将其
            // 添加到 art 元素之前
            XProcessingInstruction pi = new XProcessingInstruction("order", "alpha ascending");
            art.AddBeforeSelf(pi);

            // 创建 period 元素，并将其
            // 添加到 art 元素中
            XElement period = new XElement(nsArt + "period");
            art.Add(period);

            // 向 period 元素中添加 name 特性
            period.SetAttributeValue("name", "Renaissance");

            // 创建命名空间声明 xmlns:a，并将其
            // 添加到 period 元素中
            XAttribute nsdecl = new XAttribute(XNamespace.Xmlns + "a", nsArtists);
            period.Add(nsdecl);

            // 创建 artist 元素和
            // 基础文本节点
            period.SetElementValue(nsArtists + "artist", "Michelangelo");

            XElement artist = new XElement(nsArtists + "artist", "Leonardo ", "da ", "Vinci");
            period.AddFirst(artist);

            artist = new XElement(nsArtists + "artist");
            period.Add(artist);
            XText cdata = new XText("Donatello");
            artist.Add(cdata);

            // 创建注释，并将其
            // 添加到 art 元素中
            XComment comment = new XComment("insert period here");
            art.Add(comment);

            return document;
        }

        // <?xml version="1.0"?>
        // <?order alpha ascending?>
        // <art xmlns='urn:art-org:art'>
        //   <period name='Renaissance' xmlns:a='urn:art-org:artists'>
        //     <a:artist>Leonardo da Vinci</a:artist>
        //     <a:artist>Michelangelo</a:artist>
        //     <a:artist><![CDATA[Donatello]]></a:artist>
        //   </period>
        //   <!-- 在此处插入 period -->
        // </art>
        public static XDocument CreateDocumentConcise()
        {
            XNamespace nsArt = "urn:art-org:art";
            XNamespace nsArtists = "urn:art-org:artists";

            // 一次完成文档创建
            return new XDocument(
                        new XDeclaration("1.0", null, null),
                        new XProcessingInstruction("order", "alpha ascending"),
                        new XElement(nsArt + "art",
                            new XElement(nsArt + "period",
                                new XAttribute("name", "Renaissance"),
                                new XAttribute(XNamespace.Xmlns + "a", nsArtists),
                                new XElement(nsArtists + "artist", "Leonardo da Vinci"),
                                new XElement(nsArtists + "artist", "Michelangelo"),
                                new XElement(nsArtists + "artist", 
                                    new XText("Donatello"))),
                            new XComment("insert period here")));                        
        }

        public static void DumpNode(XNode node) 
        {
            switch (node.NodeType)
            {
                case XmlNodeType.Document:
                    XDocument document = (XDocument)node;
                    Console.WriteLine("StartDocument");
                    XDeclaration declaration = document.Declaration;
                    if (declaration != null)
                    {
                        Console.WriteLine("XmlDeclaration: {0} {1} {2}", declaration.Version, declaration.Encoding, declaration.Standalone);
                    }
                    foreach (XNode n in document.Nodes())
                    {
                        DumpNode(n);
                    }
                    Console.WriteLine("EndDocument");
                    break;
                case XmlNodeType.Element:
                    XElement element = (XElement)node;
                    Console.WriteLine("StartElement: {0}", element.Name);
                    if (element.HasAttributes) 
                    {
                        foreach (XAttribute attribute in element.Attributes())
                        {
                            Console.WriteLine("Attribute: {0} = {1}", attribute.Name, attribute.Value);
                        }
                    }
                    if (!element.IsEmpty)
                    {
                        foreach (XNode n in element.Nodes())
                        {
                            DumpNode(n);
                        }
                    }
                    Console.WriteLine("EndElement: {0}", element.Name);
                    break;
                case XmlNodeType.Text:
                    XText text = (XText)node;
                    Console.WriteLine("Text: {0}", text.Value); 
                    break;
                case XmlNodeType.ProcessingInstruction:
                    XProcessingInstruction pi = (XProcessingInstruction)node;
                    Console.WriteLine("ProcessingInstruction: {0} {1}", pi.Target, pi.Data);
                    break;
                case XmlNodeType.Comment:
                    XComment comment = (XComment)node;
                    Console.WriteLine("Comment: {0}", comment.Value);
                    break;
                case XmlNodeType.DocumentType:
                    XDocumentType documentType = (XDocumentType)node;
                    Console.WriteLine("DocumentType: {0} {1} {2} {3}", documentType.Name, documentType.PublicId, documentType.SystemId, documentType.InternalSubset);
                    break;
                default:
                    break;
            }
        }
    }
}
