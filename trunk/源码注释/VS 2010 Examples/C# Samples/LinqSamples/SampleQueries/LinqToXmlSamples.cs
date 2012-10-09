// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
//版权所有(C) Microsoft Corporation。保留所有权利。

using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Xml.Linq;
using SampleSupport;
using System.Xml;
using System.Text.RegularExpressions;
using System.Globalization;
using System.IO;
using System.Windows.Forms;

namespace SampleQueries {
    [Title("101+ Linq To Xml 查询示例")]
    [Prefix("XLinq")]
    public class LinqToXmlSamples : SampleHarness {
        public string dataPath = Path.GetFullPath(Path.Combine(Application.StartupPath, @"..\..\Data\"));

        [Category("加载")]
        [Title("从文件加载文档")]
        [Description("从文件加载 XML 文档")]
        public void XLinq1() {
            XDocument doc = XDocument.Load(dataPath + "bib.xml");
            Console.WriteLine(doc);
        }

        [Category("加载")]
        [Title("从字符串加载文档")]
        [Description("从字符串加载文档")]
        public void XLinq2() {
            string xml = "<book price='100' isbn='1002310'>" +
                            "<title>XClarity Samples</title>" +
                            "<author>Matt</author>" +
                         "</book>";
            XDocument doc = XDocument.Parse(xml);
            Console.WriteLine(doc);

        }

        //从 XmlReader 加载 XML 文档
        [Category("加载")]
        [Title("从 XmlReader 加载文档")]
        [Description("从 XmlReader 加载 XML 文档")]
        public void XLinq3() {
            XmlReader reader = XmlReader.Create(dataPath + "bib.xml");
            XDocument doc = XDocument.Load(reader);
            Console.WriteLine(doc);

        }

        [Category("加载")]
        [Title("来自 XmlReader 的元素 - 1")]
        [Description("从在元素上放置的 XmlReader 构造 XElement")]
        public void XLinq4() {
            XmlReader reader = XmlReader.Create(dataPath + "nw_customers.xml");
            reader.Read();// 移动到根级别
            reader.Read(); // 移动到第一个客户
            XElement c = (XElement)XNode.ReadFrom(reader);
            Console.WriteLine(c);

        }

        [Category("加载")]
        [Title("来自 XmlReader 的元素 - 2 ")]
        [Description("从 XmlReader 读取 XElement 内容")]
        public void XLinq5() {
            XmlReader reader = XmlReader.Create(dataPath + "config.xml");
            //文件开头有注释和空白
            reader.Read();
            reader.Read();
            XElement config = new XElement("appSettings",
                                           "This content will be replaced");
            config.RemoveAll();
            while (!reader.EOF)
                config.Add(XNode.ReadFrom(reader));
            Console.WriteLine(config);
        }

        [Category("构造")]
        [Title("从字符串构造 XElement")]
        [Description("从字符串构造 XElement")]
        public void XLinq6() {
            string xml = "<purchaseOrder price='100'>" +
                            "<item price='50'>Motor</item>" +
                            "<item price='50'>Cable</item>" +
                          "</purchaseOrder>";
            XElement po = XElement.Parse(xml);
            Console.WriteLine(po);

        }

        [Category("构造")]
        [Title("向文档添加 XML 声明")]
        [Description("向文档添加 XML 声明")]
        public void XLinq7() {
            XDocument doc = new XDocument(new XDeclaration("1.0", "UTF-16", "Yes"),
                                          new XElement("foo"));
            StringWriter sw = new StringWriter();
            doc.Save(sw);
            Console.WriteLine(sw);

        }

        [Category("构造")]
        [Title("计算得到的元素名称")]
        [Description("计算得到的元素名称")]
        public void XLinq8() {
            XDocument customers = XDocument.Load(dataPath + "nw_customers.xml");
            string name = (string)customers.Elements("Root")
                                           .Elements("Customers")
                                           .First()
                                           .Attribute("CustomerID");
            XElement result = new XElement(name,
                                            "Element with a computed name");
            Console.WriteLine(result);

        }
        [Category("Construction")]
        [Title("Document creation")]
        [Description("Create a simple config file")]
        public void XLinq9() {
            XDocument myDocument =
            new XDocument(
              new XElement("configuration",
                new XElement("system.web",
                  new XElement("membership",
                    new XElement("providers",
                      new XElement("add",
                        new XAttribute("name",
                                       "WebAdminMembershipProvider"),
                        new XAttribute("type",
                                       "System.Web.Administration.WebAdminMembershipProvider")))),
                  new XElement("httpModules",
                    new XElement("add",
                      new XAttribute("name",
                                      "WebAdminModule"),
                      new XAttribute("type",
                                      "System.Web.Administration.WebAdminModule"))),
                  new XElement("authentication",
                    new XAttribute("mode", "Windows")),
                  new XElement("authorization",
                    new XElement("deny",
                      new XAttribute("users", "?"))),
                  new XElement("identity",
                    new XAttribute("impersonate", "true")),
                  new XElement("trust",
                    new XAttribute("level", "full")),
                  new XElement("pages",
                    new XAttribute("validationRequest", "true")))));

            Console.WriteLine(myDocument);

        }

        // <xsd:schema xmlns:xsd="http://www.w3.org/2001/XMLSchema" 
        //             xmlns:sql="urn:schemas-microsoft-com:mapping-schema">

        // <xsd:element name="root" sql:is-constant="1">
        // <xsd:complexType>
        // <xsd:sequence>
        // <xsd:element name="Customers" minOccurs="100" maxOccurs="unbounded">
        //     <xsd:complexType>
        //     <xsd:sequence>
        //         <xsd:element name="CompanyName" type="xsd:string" /> 
        //         <xsd:element name="ContactName" type="xsd:string" /> 
        //         <xsd:element name="ContactTitle" type="xsd:string" /> 
        //         <xsd:element name="Phone" type="xsd:string" /> 
        //         <xsd:element name="Fax" type="xsd:string"/> 
        //         <xsd:element ref="FullAddress" maxOccurs="3"/>
        //         <xsd:element name="Date" type="xsd:date"/>
        //     </xsd:sequence>
        //     <xsd:attribute name="CustomerID" type="xsd:integer" /> 
        //     </xsd:complexType>
        // </xsd:element>
        // </xsd:sequence>
        // </xsd:complexType>
        // </xsd:element>
        // <xsd:element name="FullAddress" sql:relation="Customers" sql:relationship="CustAdd" sql:key-fields="CustomerID" >
        //     <xsd:complexType>
        //     <xsd:sequence>
        //         <xsd:element name="Address" type="xsd:string" /> 
        //         <xsd:element name="City" type="xsd:string" /> 
        //         <xsd:element name="Region" type="xsd:string" /> 
        //         <xsd:element name="PostalCode" type="xsd:string" /> 
        //         <xsd:element name="Country" type="xsd:string" /> 
        //     </xsd:sequence>
        //     </xsd:complexType>
        // </xsd:element>       
        //</xsd:schema>

        [Category("构造")]
        [Title("创建 XmlSchema")]
        [Description("创建 XmlSchema")]
        public void XLinq10() {
            XNamespace XSD = "http://www.w3.org/2001/XMLSchema";
            XNamespace SQL = "urn:schemas-microsoft-com:mapping-schema";
            XElement result =
                new XElement(XSD + "schema",
                        new XAttribute(XNamespace.Xmlns + "xsd", "http://www.w3.org/2001/XMLSchema"),
                        new XAttribute(XNamespace.Xmlns + "sql", "urn:schemas-microsoft-com:mapping-schema"),
                        new XElement(XSD + "element",
                            new XAttribute("name", "root"),
                            new XAttribute(SQL + "is-constant", "1"),
                            new XElement(XSD + "complexType",
                                new XElement(XSD + "sequence",
                                    new XElement(XSD + "element",
                                        new XAttribute("name", "Customers"),
                                        new XAttribute("minOccurs", "100"),
                                        new XAttribute("maxOccurs", "unbounded"),
                                        new XElement(XSD + "complexType",
                                            new XElement(XSD + "sequence",
                                                new XElement(XSD + "element",
                                                    new XAttribute("name", "CompanyName"),
                                                    new XAttribute("type", "xsd:string")),
                                                new XElement(XSD + "element",
                                                    new XAttribute("name", "ContactName"),
                                                    new XAttribute("type", "xsd:string")),
                                                new XElement(XSD + "element",
                                                    new XAttribute("name", "ContactTitle"),
                                                    new XAttribute("type", "xsd:string")),
                                                new XElement(XSD + "element",
                                                    new XAttribute("name", "Phone"),
                                                    new XAttribute("type", "xsd:string")),
                                                new XElement(XSD + "element",
                                                    new XAttribute("name", "Fax"),
                                                    new XAttribute("type", "xsd:string")),
                                                new XElement(XSD + "element",
                                                    new XAttribute("ref", "FullAddress"),
                                                    new XAttribute("maxOccurs", "3")),
                                                new XElement(XSD + "element",
                                                    new XAttribute("name", "Date"),
                                                    new XAttribute("type", "xsd:date"))),
                                            new XElement(XSD + "attribute",
                                                    new XAttribute("name", "CustomerID"),
                                                    new XAttribute("type", "xsd:integer"))))))),
                        new XElement(XSD + "element",
                                new XAttribute("name", "FullAddress"),
                                new XAttribute(SQL + "relation", "Customers"),
                                new XAttribute(SQL + "relationship", "CustAdd"),
                                new XAttribute(SQL + "key-fields", "CustomerID"),
                                new XElement(XSD + "complexType",
                                    new XElement(XSD + "sequence",
                                        new XElement(XSD + "element",
                                            new XAttribute("name", "Address"),
                                            new XAttribute("type", "xsd:string")),
                                        new XElement(XSD + "element",
                                            new XAttribute("name", "City"),
                                            new XAttribute("type", "xsd:string")),
                                        new XElement(XSD + "element",
                                            new XAttribute("name", "Region"),
                                            new XAttribute("type", "xsd:string")),
                                        new XElement(XSD + "element",
                                            new XAttribute("name", "PostalCode"),
                                            new XAttribute("type", "xsd:string")),
                                        new XElement(XSD + "element",
                                            new XAttribute("name", "Country"),
                                            new XAttribute("type", "xsd:string"))))));

            Console.WriteLine(result);

        }

        [Category("构造")]
        [Title("构造 PI")]
        [Description("创建带有 XSLT PI 的 XML 文档")]
        public void XLinq11() {
            XDocument result = new XDocument(
                                new XProcessingInstruction("xml-stylesheet",
                                                           "type='text/xsl' href='diff.xsl'"),
                                new XElement("foo"));
            Console.WriteLine(result);
        }

        [Category("构造")]
        [Title("XML 注释构造")]
        [Description("XML 注释构造")]
        public void XLinq12() {
            XDocument result =
              new XDocument(
                new XComment("My phone book"),
                new XElement("phoneBook",
                  new XComment("My friends"),
                  new XElement("Contact",
                    new XAttribute("name", "Ralph"),
                    new XElement("homephone", "425-234-4567"),
                    new XElement("cellphone", "206-345-75656")),
                  new XElement("Contact",
                    new XAttribute("name", "Dave"),
                    new XElement("homephone", "516-756-9454"),
                    new XElement("cellphone", "516-762-1546")),
                  new XComment("My family"),
                  new XElement("Contact",
                    new XAttribute("name", "Julia"),
                    new XElement("homephone", "425-578-1053"),
                    new XElement("cellphone", "")),
                  new XComment("My team"),
                  new XElement("Contact",
                    new XAttribute("name", "Robert"),
                    new XElement("homephone", "345-565-1653"),
                    new XElement("cellphone", "321-456-2567"))));

            Console.WriteLine(result);
        }

        [Category("构造")]
        [Title("创建 CData 节")]
        [Description("创建 CData 节")]
        public void XLinq13() {
            XElement e = new XElement("Dump",
                          new XCData("<dump>this is some xml</dump>"),
                          new XText("some other text"));
            Console.WriteLine("Element Value: {0}", e.Value);
            Console.WriteLine("Text nodes collapsed!: {0}", e.Nodes().First());
            Console.WriteLine("CData preserved on serialization: {0}", e);
        }

        [Category("构造")]
        [Title("创建节点序列")]
        [Description("创建客户元素的序列")]
        public void XLinq14() {
            var cSequence = new[] {
                    new XElement("customer",
                                 new XAttribute("id","x"),"new customer"),
                    new XElement("customer",
                                 new XAttribute("id","y"),"new customer"),
                    new XElement("customer",
                                 new XAttribute("id","z"),"new customer")};
            foreach (var c in cSequence)
                Console.WriteLine(c);

        }

        [Category("写入")]
        [Title("将 XElement 写入 XmlWriter")]
        [Description("使用 WriteTo 方法将 XElement 写入 XmlWriter")]
        public void XLinq15() {
            XElement po1 = new XElement("PurchaseOrder",
                            new XElement("Item", "Motor",
                              new XAttribute("price", "100")));

            XElement po2 = new XElement("PurchaseOrder",
                            new XElement("Item", "Cable",
                              new XAttribute("price", "10")));

            XElement po3 = new XElement("PurchaseOrder",
                            new XElement("Item", "Switch",
                              new XAttribute("price", "10")));

            StringWriter sw = new StringWriter();
            XmlWriterSettings settings = new XmlWriterSettings();
            settings.Indent = true;
            XmlWriter w = XmlWriter.Create(sw, settings);
            w.WriteStartElement("PurchaseOrders");

            po1.WriteTo(w);
            po2.WriteTo(w);
            po3.WriteTo(w);

            w.WriteEndElement();
            w.Close();
            Console.WriteLine(sw.ToString());
        }


        [Category("写入")]
        [Title("将 XDocument 的内容写入 XmlWriter")]
        [Description("使用 WriteTo 方法将 XDocument 的内容写入 XmlWriter")]
        public void XLinq16() {
            XDocument doc1 = new XDocument(
              new XElement("PurchaseOrders",
                new XElement("PurchaseOrder",
                  new XElement("Item", "Motor",
                    new XAttribute("price", "100"))),
                new XElement("PurchaseOrder",
                  new XElement("Item", "Cable",
                    new XAttribute("price", "10")))));
            XDocument doc2 = new XDocument(
              new XElement("PurchaseOrders",
                new XElement("PurchaseOrder",
                  new XElement("Item", "Switch",
                    new XAttribute("price", "10")))));

            StringWriter sw = new StringWriter();

            XmlWriter w = XmlWriter.Create(sw);

            w.WriteStartDocument();
            w.WriteStartElement("AllPurchaseOrders");
            doc1.Root.WriteTo(w);
            doc2.Root.WriteTo(w);
            w.WriteEndElement();
            w.WriteEndDocument();
            w.Close();
            Console.WriteLine(sw.ToString());
        }


        [Category("写入")]
        [Title("保存 XDocument")]
        [Description("使用 XmlWriter/TextWriter/File 保存 XDocument")]
        public void XLinq17() {
            XDocument doc = new XDocument(
                new XElement("PurchaseOrders",
                    new XElement("PurchaseOrder",
                      new XElement("Item",
                        "Motor",
                        new XAttribute("price", "100"))),
                    new XElement("PurchaseOrder",
                      new XElement("Item",
                        "Switch",
                        new XAttribute("price", "10"))),
                    new XElement("PurchaseOrder",
                      new XElement("Item",
                        "Cable",
                        new XAttribute("price", "10")))));

            StringWriter sw = new StringWriter();
            //保存到 XmlWriter
            XmlWriterSettings settings = new XmlWriterSettings();
            settings.Indent = true;
            XmlWriter w = XmlWriter.Create(sw, settings);
            doc.Save(w);
            w.Close();
            Console.WriteLine(sw.ToString());

            //保存到文件
            doc.Save("out.xml");

        }

        [Category("查询")]
        [Title("查询子元素")]
        [Description("选择 xml 文档中的所有客户")]
        public void XLinq18() {
            XDocument doc = XDocument.Load(dataPath + "nw_customers.xml");
            foreach (XElement result in doc.Elements("Root")
                                           .Elements("Customers"))
                Console.WriteLine(result);

        }

        [Category("查询")]
        [Title("查询所有子元素")]
        [Description("选择第一个客户的所有子元素")]
        public void XLinq19() {
            XDocument doc = XDocument.Load(dataPath + "nw_customers.xml");
            var query = doc.Element("Root")
                           .Element("Customers")
                           .Elements();
            foreach (XElement result in query)
                Console.WriteLine(result);
        }

        [Category("查询")]
        [Title("查询第一个子元素 - 1")]
        [Description("选择文档中的第一个客户")]
        public void XLinq20() {
            XDocument doc = XDocument.Load(dataPath + "nw_customers.xml");
            var result = doc.Element("Root")
                            .Element("Customers");
            Console.WriteLine(result);
        }

        [Category("查询")]
        [Title("查询第一个子元素 - 2")]
        [Description("查询元素序列上的一个子元素")]
        public void XLinq21() {
            XDocument doc = XDocument.Load(dataPath + "nw_customers.xml");
            var result = doc.Elements()
                            .Elements("Customers")
                            .First()
                            .Element("CompanyName");
            Console.WriteLine(result);
        }

        [Category("查询")]
        [Title("查询特性")]
        [Description("选择 xml 文档中的所有 CustomerID")]
        public void XLinq22() {
            XDocument doc = XDocument.Load(dataPath + "nw_customers.xml");
            var query = doc.Element("Root")
                           .Elements("Customers")
                           .Attributes("CustomerID");
            foreach (XAttribute result in query)
                Console.WriteLine(result.Name + " = " + result.Value);

        }

        [Category("查询")]
        [Title("将特性强制转换为数字")]
        [Description("查找价格大于 100 的订单")]
        public void XLinq23() {
            string xml = "<order >" +
                            "<item price='150'>Motor</item>" +
                            "<item price='50'>Cable</item>" +
                            "<item price='50'>Modem</item>" +
                            "<item price='250'>Monitor</item>" +
                            "<item price='10'>Mouse</item>" +
                        "</order>";
            XElement order = XElement.Parse(xml);
            var query =
                from
                    i in order.Elements("item")
                where
                    (int)i.Attribute("price") > 100
                select i;
            foreach (var result in query)
                Console.WriteLine("Expensive Item {0} costs {1}",
                                  (string)result,
                                  (string)result.Attribute("price"));
        }

        [Category("查询")]
        [Title("获取文档的根元素")]
        [Description("获取文档的根元素")]
        public void XLinq24() {
            XElement root = XDocument.Load(dataPath + "config.xml")
                                     .Root;
            Console.WriteLine("Name of root element is {0}", root.Name);
        }

        [Category("查询")]
        [Title("使用 where 筛选查询结果")]
        [Description("使用 where 筛选查询结果")]
        public void XLinq25() {
            XDocument doc = XDocument.Load(dataPath + "nw_customers.xml");
            var query =
                    from
                        c in doc.Element("Root")
                                .Elements("Customers")
                    where
                        c.Element("FullAddress")
                         .Element("Country")
                         .Value == "Germany"
                    select c;

            foreach (XElement result in query)
                Console.WriteLine(result);
        }

        [Category("查询")]
        [Title("选择元素的所有子代")]
        [Description("选择文档中的所有 ContactName 元素")]
        public void XLinq26() {
            XDocument doc = XDocument.Load(dataPath + "nw_customers.xml");
            var query = doc.Descendants("ContactName");
            foreach (XElement result in query)
                Console.WriteLine(result);
        }

        [Category("查询")]
        [Title("选择给定类型的所有子代")]
        [Description("选择文档中的所有文本")]
        public void XLinq27() {
            XDocument doc = XDocument.Load(dataPath + "nw_customers.xml");
            var query = doc.DescendantNodes().OfType<XText>().Select(t => t.Value);
            foreach (string result in query)
                Console.WriteLine(result);
        }

        [Category("查询")]
        [Title("选择所有上级")]
        [Description("检查两个节点是否属于同一文档")]
        public void XLinq28() {
            XDocument doc = XDocument.Load(dataPath + "nw_customers.xml");
            XElement element1 = doc.Element("Root");
            XElement element2 = doc.Descendants("Customers")
                                .ElementAt(3);
            var query = from a in element1.AncestorsAndSelf()
                        from b in element2.AncestorsAndSelf()
                        where a == b
                        select a;
            Console.WriteLine(query.Any());
        }

        [Category("查询")]
        [Title("查询父级")]
        [Description("查询元素的父级")]
        public void XLinq29() {
            XElement item = new XElement("item-01",
                                         "Computer");
            XElement order = new XElement("order", item);
            XElement p = item.Parent;
            Console.WriteLine(p.Name);
        }

        [Category("查询")]
        [Title("联接两个序列")]
        [Description("向第一个客户的订单添加客户公司信息")]
        public void XLinq30() {
            XDocument customers = XDocument.Load(dataPath + "nw_customers.xml");
            XDocument orders = XDocument.Load(dataPath + "nw_orders.xml");

            var query =
                from customer in customers.Descendants("Customers").Take(1)
                join order in orders.Descendants("Orders")
                           on (string)customer.Attribute("CustomerID") equals
                              (string)order.Element("CustomerID")
                select
                    new XElement("Order",
                                order.Nodes(),
                                customer.Element("CompanyName"));

            foreach (var result in query)
                Console.WriteLine(result);

        }

        [Category("查询")]
        [Title("查询类型的内容")]
        [Description("查询给定类型的现有元素的内容")]
        public void XLinq31() {
            XElement elem =
              new XElement("customer",
                           new XElement("name",
                                        "jack"),
                           "some text",
                           new XComment("new customer"),
                           new XAttribute("id",
                                          "abc"));

            //字符串内容
            foreach (XText s in elem.Nodes().OfType<XText>())
                Console.WriteLine("String content: {0}", s);

            //元素内容
            foreach (XElement e in elem.Elements())
                Console.WriteLine("Element content: {0}", e);

            //注释内容
            foreach (XComment c in elem.Nodes().OfType<XComment>())
                Console.WriteLine("Comment content: {0}", c);

        }

        [Category("查询")]
        [Title("使用 XStreamingElement 进行查询")]
        [Description("查询所有瑞典客户订单以及运费大于 250 的瑞典订单")]
        [LinkedMethod("GetSwedishFreightProfile")]
        [LinkedMethod("GetSwedishCustomerOrders")]
        [LinkedMethod("AddNewOrder")]
        public void XLinq32() {
            XDocument customers = XDocument.Load(dataPath + "nw_customers.xml");
            XDocument orders = XDocument.Load(dataPath + "nw_orders.xml");
            XStreamingElement summary = new XStreamingElement("Summary",
                new XAttribute("Country", "Sweden"),
                new XStreamingElement("SwedishCustomerOrders", GetSwedishCustomerOrders(customers, orders)),
                new XStreamingElement("Orders", GetSwedishFreightProfile(orders)));

            Console.WriteLine(summary);
            //DML 操作，该操作添加客户 BERGS 运费 > 250 的新订单  
            AddNewOrder(orders);
            Console.WriteLine("****XStreaming Output after DML reflects new order added!!****");
            Console.WriteLine(summary);
        }

        static void AddNewOrder(XDocument orders) {
            string order = @"<Orders>
                                   <CustomerID>BERGS</CustomerID>
                                   <ShipInfo ShippedDate='1997-12-09T00:00:00'>
                                   <Freight>301</Freight>
                                   <ShipCountry>Sweden</ShipCountry>
                                   </ShipInfo>
                                   </Orders>";
            XElement newOrder = XElement.Parse(order);
            orders.Root.Add(newOrder);
        }

        private static IEnumerable<XElement> GetSwedishFreightProfile(XDocument orders) {
            return
               from
                order in orders.Descendants("Orders")
               where
                (string)order.Element("ShipInfo").Element("ShipCountry") == "Sweden"
                  && (float)order.Element("ShipInfo").Element("Freight") > 250
               select
                  new XElement("Order",
                  new XAttribute("Freight",
                                 (string)order.Element("ShipInfo").Element("Freight")));

        }

        private static IEnumerable<XElement> GetSwedishCustomerOrders(XDocument customers, XDocument orders) {
            return
               from
                customer in customers.Descendants("Customers")
               where
                (string)customer.Element("FullAddress").Element("Country") == "Sweden"
               select
                 new XElement("Customer",
                 new XAttribute("Name",
                                (string)customer.Element("CompanyName")),
                 new XAttribute("OrderCount",
                                (from
                                  order in orders.Descendants("Orders")
                                 where
                                   (string)order.Element("CustomerID") == (string)customer.Attribute("CustomerID")
                                 select
                                   order).Count()));

        }

        [Category("查询")]
        [Title("位置谓词")]
        [Description("查询文档中的第三个客户")]
        public void XLinq33() {
            XDocument doc = XDocument.Load(dataPath + "nw_customers.xml");
            var c = doc.Descendants("Customers")
                       .ElementAt(2);
            Console.WriteLine(c);
        }

        [Category("查询")]
        [Title("联合两个节点序列")]
        [Description("联合 Serge 和 Peter 两位作者所著的书")]
        public void XLinq34() {
            XDocument doc = XDocument.Load(dataPath + "bib.xml");
            var b1 = doc.Descendants("book")
                        .Where(b => b.Elements("author")
                                     .Elements("first")
                                     .Any(f => (string)f == "Serge"));
            var b2 = doc.Descendants("book")
                        .Where(b => b.Elements("author")
                                     .Elements("first")
                                     .Any(f => (string)f == "Peter"));
            var books = b1.Union(b2);
            foreach (var b in books)
                Console.WriteLine(b);
        }

        [Category("查询")]
        [Title("求两个节点序列的交集")]
        [Description("求两位作者共同创作的书的交集")]
        public void XLinq35() {
            XDocument doc = XDocument.Load(dataPath + "bib.xml");
            var b1 = doc.Descendants("book")
                        .Where(b => b.Elements("author")
                                        .Elements("first")
                                        .Any(f => (string)f == "Serge"));
            var b2 = doc.Descendants("book")
                        .Where(b => b.Elements("author")
                                        .Elements("first")
                                        .Any(f => (string)f == "Peter"));
            var books = b1.Intersect(b2);
            foreach (var b in books)
                Console.WriteLine(b);
        }

        [Category("查询")]
        [Title("存在于序列 1 中但不存在于序列 2 中的所有节点")]
        [Description("查找 Peter 所著而 Serge 不是合著者的书")]
        public void XLinq36() {
            XDocument doc = XDocument.Load(dataPath + "bib.xml");
            var b1 = doc.Descendants("book")
                        .Where(b => b.Elements("author")
                                     .Elements("first")
                                     .Any(f => (string)f == "Serge"));
            var b2 = doc.Descendants("book")
                        .Where(b => b.Elements("author")
                                     .Elements("first")
                                     .Any(f => (string)f == "Peter"));
            var books = b2.Except(b1);
            foreach (var b in books)
                Console.WriteLine(b);
        }

        [Category("查询")]
        [Title("反转序列中节点的顺序")]
        [Description("显示节点的路径")]
        [LinkedMethod("PrintPath")]
        public void XLinq37() {
            XDocument doc = XDocument.Load(dataPath + "bib.xml");
            XElement e = doc.Descendants("last")
                            .First();
            PrintPath(e);
        }

        static void PrintPath(XElement e) {
            var nodes = e.AncestorsAndSelf()
                            .Reverse();
            foreach (var n in nodes)
                Console.Write(n.Name + (n == e ? "" : "->"));
        }


        [Category("查询")]
        [Title("序列是否相等")]
        [Description("检查 2 个节点序列是否相等。" +
                     "所有的书是否均由 Serge 和 Peter 二人合著?")]
        public void XLinq38() {
            XDocument doc = XDocument.Load(dataPath + "bib.xml");
            var b1 = doc.Descendants("book")
                        .Where(b => b.Elements("author")
                                        .Elements("first")
                                        .Any(f => (string)f == "Serge"));
            var b2 = doc.Descendants("book")
                        .Where(b => b.Elements("author")
                                        .Elements("first")
                                        .Any(f => (string)f == "Peter"));
            bool result = b2.SequenceEqual(b1);
            Console.WriteLine(result);
        }


        [Category("查询")]
        [Title("TakeWhile 运算符")]
        [Description("List books until total price is less that $150")]
        public void XLinq39() {
            XDocument doc = XDocument.Load(dataPath + "bib.xml");
            double sum = 0;
            var query = doc.Descendants("book")
                           .TakeWhile(c => (sum += (double)c.Element("price")) <= 150);
            foreach (var result in query)
                Console.WriteLine(result);
        }

        [Category("查询")]
        [Title("创建数字列表")]
        [Description("创建 ID 各异的 5 个新客户")]
        public void XLinq40() {
            var query = from
                           i in Enumerable.Range(1, 5)
                        select
                            new XElement("Customer",
                                         new XAttribute("id", i),
                                         "New customer");
            foreach (var result in query)
                Console.WriteLine(result);
        }

        [Category("查询")]
        [Title("Repeat 运算符")]
        [Description("初始化新订单及商品")]
        public void XLinq41() {
            var orders = new XElement[] {
                new XElement("order", new XAttribute("itemCount",5)),
                new XElement("order", new XAttribute("itemCount",2)),
                new XElement("order", new XAttribute("itemCount",3))};

            //添加空项
            foreach (var order in orders)
                order.Add(Enumerable.Repeat(new XElement("item", "New item"),
                                          (int)order.Attribute("itemCount")));

            foreach (var o in orders)
                Console.WriteLine(o);

        }

        [Category("查询")]
        [Title("Any 运算符")]
        [Description("检查阿根廷是否有客户")]
        public void XLinq42() {
            XDocument doc = XDocument.Load(dataPath + "nw_Customers.xml");
            if (doc.Descendants("Country").Any(c => (string)c == "Argentina"))
                Console.WriteLine("There are cusotmers in Argentina");
            else
                Console.WriteLine("There are no cusotmers in Argentina");
        }

        [Category("查询")]
        [Title("All 运算符")]
        [Description("检查是否所有书都至少有一位作者")]
        public void XLinq43() {
            XDocument doc = XDocument.Load(dataPath + "bib.xml");
            bool query = doc.Descendants("book")
                            .All(b => b.Descendants("author").Count() > 0);
            if (query)
                Console.WriteLine("All books have authors");
            else
                Console.WriteLine("Some books dont have authors");
        }

        [Category("查询")]
        [Title("Count 运算符")]
        [Description("查找某个客户的订单数")]
        public void XLinq44() {
            XDocument doc = XDocument.Load(dataPath + "nw_Orders.xml");
            var query = doc.Descendants("Orders")
                           .Where(o => (string)o.Element("CustomerID") == "VINET");
            Console.WriteLine("Customer has {0} orders", query.Count());
        }

        [Category("查询")]
        [Title("聚合运算符")]
        [Description("得到订单上的税款")]
        [LinkedMethod("Tax")]
        public void XLinq45() {
            string xml = "<order >" +
                            "<item price='150'>Motor</item>" +
                            "<item price='50'>Cable</item>" +
                         "</order>";

            XElement order = XElement.Parse(xml);
            double tax = order.Elements("item")
                              .Aggregate((double)0, Tax);

            Console.WriteLine("The total tax on the order @10% is ${0}", tax);

        }
        static double Tax(double seed, XElement item) {
            return seed + (double)item.Attribute("price") * 0.1;
        }

        [Category("查询")]
        [Title("Distinct 运算符")]
        [Description("查找有客户的所有国家/地区")]
        public void XLinq46() {
            XDocument doc = XDocument.Load(dataPath + "nw_Customers.xml");
            var countries = doc.Descendants("Country")
                               .Select(c => (string)c)
                               .Distinct()
                               .OrderBy(c => c);
            foreach (var c in countries)
                Console.WriteLine(c);
        }

        [Category("查询")]
        [Title("Concat 运算符")]
        [Description("列出 Serge 和 Peter 所著的所有书，合著的书会重复列出")]
        public void XLinq47() {
            XDocument doc = XDocument.Load(dataPath + "bib.xml");
            var b1 = doc.Descendants("book")
                        .Where(b => b.Elements("author")
                                     .Elements("first")
                                     .Any(f => (string)f == "Serge"));
            var b2 = doc.Descendants("book")
                        .Where(b => b.Elements("author")
                                     .Elements("first")
                                     .Any(f => (string)f == "Peter"));
            var books = b1.Concat(b2);
            foreach (var b in books)
                Console.WriteLine(b);

        }
        [Category("查询")]
        [Title("Take 运算符")]
        [Description("查询前两个客户")]
        public void XLinq48() {
            XDocument doc = XDocument.Load(dataPath + "nw_Customers.xml");
            var customers = doc.Descendants("Customers").Take(2);
            foreach (var c in customers)
                Console.WriteLine(c);
        }

        [Category("查询")]
        [Title("Skip 运算符")]
        [Description("跳过前 3 本书")]
        public void XLinq49() {
            XDocument doc = XDocument.Load(dataPath + "bib.xml");
            var books = doc.Descendants("book").Skip(3);
            foreach (var b in books)
                Console.WriteLine(b);
        }

        [Category("查询")]
        [Title("基于条件跳过节点")]
        [Description("打印不适合预算的项")]
        public void XLinq50() {
            string xml = "<order >" +
                            "<item price='150'>Motor</item>" +
                            "<item price='50'>Cable</item>" +
                            "<item price='50'>Modem</item>" +
                            "<item price='250'>Monitor</item>" +
                            "<item price='10'>Mouse</item>" +
                        "</order>";
            XElement order = XElement.Parse(xml);
            int sum = 0;
            var items = order.Descendants("item")
                             .SkipWhile(i => (sum += (int)i.Attribute("price")) < 300);
            foreach (var i in items)
                Console.WriteLine("{0} does not fit in you budget", (string)i);
        }

        [Category("查询")]
        [Title("SelectMany 运算符")]
        [Description("获取 Serge 和 Peter 所著的所有书")]
        [LinkedMethod("GetBooks")]
        public void XLinq51() {
            string[] authors = { "Serge", "Peter" };
            var books = authors.SelectMany(a => GetBooks(a));
            foreach (var b in books)
                Console.WriteLine(b);

        }

        public IEnumerable<XElement> GetBooks(string author) {
            XDocument doc = XDocument.Load(dataPath + "bib.xml");
            var query = doc.Descendants("book")
                            .Where(b => b.Elements("author")
                                         .Elements("first")
                                         .Any(f => (string)f == author));

            return query;
        }

        [Category("查询")]
        [Title("容器文档")]
        [Description("查找元素的容器文档")]
        public void XLinq52() {
            XElement c = XDocument.Load(dataPath + "bib.xml").Descendants("book").First();
            XDocument container = c.Document;
            Console.WriteLine(container);
        }

        [Category("分组")]
        [Title("按客户对订单进行分组")]
        [Description("按客户对订单进行分组")]
        public void XLinq53() {
            XDocument doc = XDocument.Load(dataPath + "nw_orders.xml");
            var query =
                from
                    o in doc.Descendants("Orders")
                group o by
                    (string)o.Element("CustomerID") into oGroup
                select
                    oGroup;
            foreach (var result in query.SelectMany(g => g))
                Console.WriteLine(result);
        }

        [Category("分组")]
        [Title("按国家/地区和城市对客户进行分组")]
        [Description("创建按国家/地区和城市分组的客户目录")]
        public void XLinq54() {
            XDocument customers = XDocument.Load(dataPath + "nw_customers.xml");
            XElement directory =
             new XElement("directory",
                from customer in customers.Descendants("Customers")
                from country in customer.Elements("FullAddress").Elements("Country")
                group customer by (string)country into countryGroup
                let country = countryGroup.Key
                select
                    new XElement("Country",
                                 new XAttribute("name",
                                                country),
                                 new XAttribute("numberOfCustomers",
                                                countryGroup.Count()),
                                 from customer in countryGroup
                                 from city in customer.Descendants("City")
                                 group customer by (string)city into cityGroup
                                 let city = cityGroup.Key
                                 select
                                    new XElement("City",
                                                 new XAttribute("name",
                                                                city),
                                                 new XAttribute("numberOfCustomers",
                                                                cityGroup.Count()),
                                                                cityGroup.Elements("ContactName"))));
            Console.WriteLine(directory);

        }

        [Category("分组")]
        [Title("按客户对订单进行分组")]
        [Description("按客户对订单进行分组，并返回具有 25 个以上订单的所有客户(+ 订单)")]
        public void XLinq55() {
            XDocument customers = XDocument.Load(dataPath + "nw_customers.xml");
            XDocument orders = XDocument.Load(dataPath + "nw_orders.xml");
            XElement custOrder = new XElement("CustomerOrders",
                from
                    order in orders.Descendants("Orders")
                group order by
                    order.Element("CustomerID") into cust_orders
                where
                    cust_orders.Count() > 25
                select
                    new XElement("Customer",
                        new XAttribute("CustomerID", cust_orders.Key.Value),
                        from
                            customer in customers.Descendants("Customers")
                        where
                            (string)customer.Attribute("CustomerID") == (string)cust_orders.Key.Value
                        select
                            customer.Nodes(),
                        cust_orders));

            Console.WriteLine(custOrder);
        }

        [Category("排序")]
        [Title("按名称对客户进行排序")]
        [Description("按名称以升序对客户进行排序")]
        public void XLinq56() {
            XDocument doc = XDocument.Load(dataPath + "nw_customers.xml");
            var query =
                from
                    customer in doc.Descendants("Customers")
                orderby
                    (string)customer.Elements("ContactName").First()
                select
                    customer.Element("ContactName");
            XElement result =
                new XElement("SortedCustomers", query);
            Console.WriteLine(result);
        }

        [Category("排序")]
        [Title("按日期对订单进行排序")]
        [Description("按日期以升序对订单进行排序")]
        public void XLinq57() {
            XDocument doc = XDocument.Load(dataPath + "nw_orders.xml");
            var query =
                from order in doc.Descendants("Orders")
                let date = (DateTime)order.Element("OrderDate")
                orderby date
                select
                    new XElement("Order",
                                 new XAttribute("date",
                                                date),
                                 new XAttribute("custid",
                                                (string)order.Element("CustomerID")));
            XElement result = new XElement("SortedOrders", query);
            Console.WriteLine(result);

        }

        [Category("排序")]
        [Title("降序")]
        [Description("按名称以降序对客户进行排序")]
        public void XLinq58() {
            XDocument doc = XDocument.Load(dataPath + "nw_Customers.xml");
            var query =
                from
                    customer in doc.Descendants("Customers")
                orderby
                    (string)customer.Elements("ContactName").First() descending
                select
                    customer.Element("ContactName");
            foreach (var result in query)
                Console.WriteLine(result);

        }

        [Category("排序")]
        [Title("多个排序键")]
        [Description("按国家/地区和城市对客户进行排序")]
        public void XLinq59() {
            XDocument doc = XDocument.Load(dataPath + "nw_Customers.xml");
            var query =
                from
                    customer in doc.Descendants("Customers")
                orderby
                    (string)customer.Descendants("Country").First(),
                    (string)customer.Descendants("City").First()
                select
                    customer;
            foreach (var result in query)
                Console.WriteLine(result);

        }
        [Category("DML")]
        [Title("将元素作为最后一个子元素添加")]
        [Description("将元素作为最后一个子元素添加")]
        public void XLinq60() {
            XDocument doc = XDocument.Load(dataPath + "config.xml");
            XElement config = doc.Element("config");
            config.Add(new XElement("logFolder", "c:\\log"));
            Console.WriteLine(config);

        }

        [Category("DML")]
        [Title("将元素作为第一个子元素添加")]
        [Description("将元素作为第一个子元素添加")]
        public void XLinq61() {
            XDocument doc = XDocument.Load(dataPath + "config.xml");
            XElement config = doc.Element("config");
            config.AddFirst(new XElement("logFolder", "c:\\log"));
            Console.WriteLine(config);

        }

        [Category("DML")]
        [Title("添加多个元素作为子级")]
        [Description("添加多个元素作为子级")]
        public void XLinq62() {
            XDocument doc = XDocument.Load(dataPath + "config.xml");
            XElement[] first = { 
                new XElement("logFolder", "c:\\log"), 
                new XElement("resultsFolders", "c:\\results")};
            XElement[] last = { 
                new XElement("mode", "client"), 
                new XElement("commPort", "2")};
            XElement config = doc.Element("config");
            config.AddFirst(first);
            config.Add(last);
            Console.WriteLine(config);
        }


        [Category("DML")]
        [Title("向元素添加特性")]
        [Description("向元素添加特性")]
        public void XLinq63() {
            XElement elem = new XElement("customer",
                                         "this is an XElement",
                                         new XAttribute("id", "abc"));
            Console.WriteLine("Original element {0}", elem);

            elem.Add(new XAttribute("name", "Jack"));
            Console.WriteLine("Updated element {0}", elem);
        }


        [Category("DML")]
        [Title("向现有元素添加内容")]
        [Description("添加特性和元素")]
        public void XLinq64() {
            XElement elem = new XElement("customer",
                                         "this is an XElement",
                                         new XAttribute("id", "abc"));
            Console.WriteLine("Original element {0}", elem);

            object[] additionalContent = { 
                new XElement("phone", "555-555-5555"), 
                new XComment("new customer"), 
                new XAttribute("name", "Jack")};

            elem.Add(additionalContent);
            Console.WriteLine("Updated element {0}", elem);
        }

        [Category("DML")]
        [Title("替换容器(元素或文档)的内容")]
        [Description("将内容替换为现有元素")]
        public void XLinq65() {
            XElement elem = new XElement("customer",
                                         "this is an XElement",
                                         new XAttribute("id", "abc"));
            Console.WriteLine("Original element {0}", elem);

            elem.ReplaceNodes("this is a coustomer element");
            Console.WriteLine("Updated element {0}", elem);

            object[] newContent = { 
                "this is a customer element", 
                new XElement("phone", "555-555-5555"), 
                new XComment("new customer"), 
                new XAttribute("name", "Jack") };

            elem.ReplaceNodes(newContent);
            Console.WriteLine("Updated element {0}", elem);

        }

        [Category("DML")]
        [Title("移除元素的内容")]
        [Description("移除元素的内容")]
        public void XLinq66() {
            XElement elem = new XElement("customer",
                                         "this is an XElement",
                                         new XAttribute("id", "abc"));
            Console.WriteLine("Original element {0}", elem);

            elem.RemoveNodes();
            Console.WriteLine("Updated element {0}", elem);

        }

        [Category("DML")]
        [Title("移除所有内容")]
        [Description("移除元素的所有内容和特性")]
        public void XLinq67() {
            XElement elem = new XElement("customer",
                                         new XElement("name", "jack"),
                                         "this is an XElement",
                                         new XComment("new customer"),
                                         new XAttribute("id", "abc"));
            Console.WriteLine("Original element {0}", elem);

            elem.RemoveAll();
            Console.WriteLine("Stripped element {0}", elem);
        }

        [Category("DML")]
        [Title("移除所有特性")]
        [Description("移除元素的所有特性")]
        public void XLinq68() {
            XElement elem = new XElement("customer",
                                         new XAttribute("name", "jack"),
                                         "this is an XElement",
                                         new XComment("new customer"),
                                         new XAttribute("id", "abc"));
            Console.WriteLine("Original element {0}", elem);

            elem.RemoveAttributes();
            Console.WriteLine("Stripped element {0}", elem);

        }

        [Category("DML")]
        [Title("移除元素的某个特性")]
        [Description("移除元素的某个特性")]
        public void XLinq69() {
            XElement elem = new XElement("customer",
                                         new XAttribute("name", "jack"),
                                         "this is an XElement",
                                         new XComment("new customer"),
                                         new XAttribute("id", "abc"));
            Console.WriteLine("Original element {0}", elem);

            elem.SetAttributeValue("id", null);
            Console.WriteLine("Updated element {0}", elem);

        }

        [Category("DML")]
        [Title("更新特性")]
        [Description("更新特性的值")]
        public void XLinq70() {
            XElement elem = new XElement("customer",
                                         new XAttribute("name", "jack"),
                                         "this is an XElement",
                                         new XComment("new customer"),
                                         new XAttribute("id", "abc"));
            Console.WriteLine("Original element {0}", elem);

            elem.SetAttributeValue("name", "David");
            Console.WriteLine("Updated attribute {0}", elem);

        }


        [Category("DML")]
        [Title("按名称删除元素")]
        [Description("按名称移除子元素")]
        public void XLinq71() {
            XElement elem = new XElement("customer",
                                         new XElement("name", "jack"),
                                         "this is an XElement",
                                         new XComment("new customer"),
                                         new XAttribute("id", "abc"));
            Console.WriteLine("Original element {0}", elem);

            elem.SetElementValue("name", null);
            Console.WriteLine("Updated element {0}", elem);
        }

        [Category("DML")]
        [Title("按名称更新子元素")]
        [Description("按名称更新子元素")]
        public void XLinq72() {
            XElement elem = new XElement("customer",
                                         new XElement("name", "jack"),
                                         "this is an XElement",
                                         new XComment("new customer"),
                                         new XAttribute("id", "abc"));
            Console.WriteLine("Original element {0}", elem);

            elem.SetElementValue("name", "David");
            Console.WriteLine("Updated element {0}", elem);
        }

        [Category("DML")]
        [Title("移除元素列表")]
        [Description("移除元素列表")]
        public void XLinq73() {
            XDocument doc = XDocument.Load(dataPath + "nw_customers.xml");
            var elems = doc.Descendants("Customers");
            Console.WriteLine("Before count {0}", elems.Count());

            elems.Take(15).Remove();
            Console.WriteLine("After count {0}", elems.Count());
        }

        [Category("DML")]
        [Title("移除特性列表")]
        [Description("移除特性列表")]
        public void XLinq74() {
            XDocument doc = XDocument.Load(dataPath + "nw_customers.xml");
            var attrs = doc.Descendants("Customers")
                           .Attributes();
            Console.WriteLine("Before count {0}", attrs.Count());

            attrs.Take(15).Remove();
            Console.WriteLine("After count {0}", attrs.Count());
        }


        [Category("DML")]
        [Title("向元素添加无父级元素")]
        [Description("向元素添加无父级元素")]
        public void XLinq75() {
            XElement e = new XElement("foo",
                                      "this is an element");
            Console.WriteLine("Parent : " +
                (e.Parent == null ? "null" : e.Parent.Value));

            XElement p = new XElement("bar", e); //添加到文档
            Console.WriteLine("Parent : " +
                (e.Parent == null ? "null" : e.Parent.Name));
        }

        [Category("DML")]
        [Title("向文档添加有父级元素")]
        [Description("向其他容器添加有父级元素时将克隆该元素")]
        public void XLinq76() {
            XElement e = new XElement("foo",
                                      "this is an element");
            XElement p1 = new XElement("p1", e);
            Console.WriteLine("Parent : " + e.Parent.Name);

            XElement p2 = new XElement("p2", e);
            Console.WriteLine("Parent : " + e.Parent.Name);
        }

        [Category("转换")]
        [Title("创建客户表")]
        [Description("生成带编号的客户列表的 html 代码")]
        public void XLinq77() {
            XDocument doc = XDocument.Load(dataPath + "nw_customers.xml");

            var header = new[]{                 
                    new XElement("th","#"),
                    new XElement("th",
                                 "customer id"),
                    new XElement("th",
                                 "contact name")};
            int index = 0;
            var rows =
                from
                    customer in doc.Descendants("Customers")
                select
                    new XElement("tr",
                                 new XElement("td",
                                              ++index),
                                 new XElement("td",
                                              (string)customer.Attribute("CustomerID")),
                                 new XElement("td",
                                              (string)customer.Element("ContactName")));

            XElement html = new XElement("html",
                                  new XElement("body",
                                    new XElement("table",
                                      header,
                                      rows)));
            Console.Write(html);
        }

        [Category("转换")]
        [Title("创建书表的 html 代码")]
        [Description("按作者生成书表的 html 代码")]
        [LinkedMethod("GetBooksTable")]
        public void XLinq78() {
            XDocument doc = XDocument.Load(dataPath + "bib.xml");
            var content =
                from b in doc.Descendants("book")
                from a in b.Elements("author")
                group b by (string)a.Element("first") + " " + (string)a.Element("last") into authorGroup
                select new XElement("p", "Author: " + authorGroup.Key,
                                           GetBooksTable(authorGroup));

            XElement result =
                new XElement("html",
                            new XElement("body",
                             content));
            Console.WriteLine(result);
        }

        static XElement GetBooksTable(IEnumerable<XElement> books) {
            var header = new XElement[]{
                            new XElement("th","Title"), 
                            new XElement("th", "Year")};
            var rows =
                from
                    b in books
                select
                    new XElement("tr",
                                 new XElement("td",
                                              (string)b.Element("title")),
                                 new XElement("td",
                                              (string)b.Attribute("year")));

            return new XElement("table",
                                header,
                                rows);

        }
        [Category("语言集成")]
        [Title("查找列表中客户的所有订单")]
        [Description("查找列表中客户的所有订单")]
        [LinkedMethod("SomeMethodToGetCustomers")]
        [LinkedClass("Customer")]
        public void XLinq79() {
            XDocument doc = XDocument.Load(dataPath + "nw_orders.xml");
            List<Customer> customers = SomeMethodToGetCustomers();
            var result =
                from customer in customers
                from order in doc.Descendants("Orders")
                where
                    customer.id == (string)order.Element("CustomerID")
                select
                    new { custid = (string)customer.id, orderdate = (string)order.Element("OrderDate") };
            foreach (var tuple in result)
                Console.WriteLine("Customer id = {0}, Order Date = {1}",
                                    tuple.custid, tuple.orderdate);

        }
        class Customer {
            public Customer(string id) { this.id = id; }
            public string id;
        }
        static List<Customer> SomeMethodToGetCustomers() {
            List<Customer> customers = new List<Customer>();
            customers.Add(new Customer("VINET"));
            customers.Add(new Customer("TOMSP"));
            return customers;
        }

        [Category("语言集成")]
        [Title("查找购物车中的货款总额")]
        [Description("查找购物车中的货款总额")]
        [LinkedMethod("GetShoppingCart")]
        [LinkedClass("Item")]
        public void XLinq80() {
            XDocument doc = XDocument.Load(dataPath + "inventory.xml");
            List<Item> cart = GetShoppingCart();
            var subtotal =
                from item in cart
                from inventory in doc.Descendants("item")
                where item.id == (string)inventory.Attribute("id")
                select (double)item.quantity * (double)inventory.Element("price");
            Console.WriteLine("Total payment = {0}", subtotal.Sum());
        }
        class Item {
            public Item(string id, int quantity) {
                this.id = id;
                this.quantity = quantity;
            }
            public int quantity;
            public string id;
        }
        static List<Item> GetShoppingCart() {
            List<Item> items = new List<Item>();
            items.Add(new Item("1", 10));
            items.Add(new Item("5", 5));
            return items;
        }

        [Category("语言集成")]
        [Title("使用配置文件")]
        [Description("加载并使用配置文件")]
        [LinkedMethod("Initialize")]
        public void XLinq81() {
            XElement config = XDocument.Load(dataPath + "config.xml").Element("config");
            Initialize((string)config.Element("rootFolder"),
                       (int)config.Element("iterations"),
                       (double)config.Element("maxMemory"),
                       (string)config.Element("tempFolder"));

        }
        static void Initialize(string root, int iter, double mem, string temp) {
            Console.WriteLine("Application initialized to root folder: " +
                              "{0}, iterations: {1}, max memory {2}, temp folder: {3}",
                              root, iter, Convert.ToString(mem, CultureInfo.InvariantCulture), temp);
        }

        [Category("语言集成")]
        [Title("将节点序列转换为数组")]
        [Description("将节点序列转换为数组")]
        public void XLinq82() {
            XDocument doc = XDocument.Load(dataPath + "nw_Customers.xml");
            XElement[] custArray = doc.Descendants("Customers").ToArray();
            foreach (var c in custArray)
                Console.WriteLine(c);
        }

        [Category("语言集成")]
        [Title("将节点序列转换为列表")]
        [Description("将节点序列转换为列表")]
        public void XLinq83() {
            XDocument doc = XDocument.Load(dataPath + "nw_Customers.xml");
            List<XElement> clist = doc.Descendants("Customers").ToList();
            foreach (var c in clist)
                Console.WriteLine(c);
        }

        [Category("语言集成")]
        [Title("创建客户字典")]
        [Description("创建客户字典")]
        public void XLinq84() {
            XDocument doc = XDocument.Load(dataPath + "nw_Customers.xml");
            var dictionary = doc.Descendants("Customers")
                                .ToDictionary(c => (string)c.Attribute("CustomerID"));
            Console.WriteLine(dictionary["ALFKI"]);
        }


        [Category("语言集成")]
        [Title("使用匿名类型")]
        [Description("对所有国家/地区进行编号，并将其列出")]
        public void XLinq85() {
            XDocument doc = XDocument.Load(dataPath + "nw_Customers.xml");
            var countries = doc.Descendants("Country")
                                .Select(c => (string)c)
                                .Distinct()
                                .Select((c, index) => new { i = index, name = c });
            foreach (var c in countries)
                Console.WriteLine(c.i + " " + c.name);

        }

        [Category("XName")]
        [Title("在命名空间中创建元素和特性")]
        [Description("在命名空间中创建元素和特性")]
        public void XLinq86() {
            XNamespace ns = "http://myNamespace";
            XElement result = new XElement(ns + "foo",
                                           new XAttribute(ns + "bar", "attribute"));
            Console.WriteLine(result);
        }

        [Category("XName")]
        [Title("查询命名空间中的元素")]
        [Description("查找名称为 FullAddress 的 xsd:element")]
        public void XLinq87() {
            XDocument doc = XDocument.Load(dataPath + "nw_customers.xsd");
            XNamespace XSD = "http://www.w3.org/2001/XMLSchema";
            XElement result = doc.Descendants(XSD + "element")
                                 .Where(e => (string)e.Attribute("name") == "FullAddress")
                                 .First();
            Console.WriteLine(result);
        }

        [Category("XName")]
        [Title("创建命名空间前缀声明")]
        [Description("创建命名空间前缀声明")]
        public void XLinq88() {
            XNamespace myNS = "http://myNamespace";
            XElement result = new XElement("myElement",
                                           new XAttribute(XNamespace.Xmlns + "myPrefix", myNS));
            Console.WriteLine(result);
        }

        [Category("XName")]
        [Title("本地名称和命名空间")]
        [Description("获取元素的本地名称和命名空间")]
        public void XLinq89() {
            XNamespace ns = "http://myNamespace";
            XElement e = new XElement(ns + "foo");

            Console.WriteLine("Local name of element: {0}", e.Name.LocalName);
            Console.WriteLine("Namespace of element : {0}", e.Name.Namespace.NamespaceName);

        }

        [Category("杂项")]
        [Title("获取节点的外部 XML")]
        [Description("获取节点的外部 XML")]
        public void XLinq90() {
            string xml = "<order >" +
                            "<item price='150'>Motor</item>" +
                            "<item price='50'>Cable</item>" +
                            "<item price='50'>Modem</item>" +
                            "<item price='250'>Monitor</item>" +
                            "<item price='10'>Mouse</item>" +
                         "</order>";
            XElement order = XElement.Parse(xml);
            Console.WriteLine(order.ToString(SaveOptions.DisableFormatting));
        }

        [Category("杂项")]
        [Title("获取节点的内部文本")]
        [Description("获取节点的内部文本")]
        public void XLinq91() {
            string xml = "<order >" +
                            "<item price='150'>Motor</item>" +
                            "<item price='50'>Cable</item>" +
                            "<item price='50'>Modem</item>" +
                            "<item price='250'>Monitor</item>" +
                            "<item price='10'>Mouse</item>" +
                         "</order>";
            XElement order = XElement.Parse(xml);
            Console.WriteLine(order.Value);

        }

        [Category("杂项")]
        [Title("检查元素是否具有特性")]
        [Description("检查元素是否具有特性")]
        public void XLinq92() {
            XDocument doc = XDocument.Load(dataPath + "nw_customers.xml");
            XElement e = doc.Element("Root")
                            .Element("Customers");
            Console.WriteLine("Customers has attributes? {0}", e.HasAttributes);

        }

        [Category("杂项")]
        [Title("检查元素是否具有元素子级")]
        [Description("检查元素是否具有元素子级")]
        public void XLinq93() {
            XDocument doc = XDocument.Load(dataPath + "nw_customers.xml");
            XElement e = doc.Element("Root")
                            .Element("Customers");
            Console.WriteLine("Customers has elements? {0}", e.HasElements);

        }

        [Category("杂项")]
        [Title("检查元素是否为空")]
        [Description("检查元素是否为空")]
        public void XLinq94() {
            XDocument doc = XDocument.Load(dataPath + "nw_customers.xml");
            XElement e = doc.Element("Root")
                            .Element("Customers");
            Console.WriteLine("Customers element is empty? {0}", e.IsEmpty);

        }

        [Category("杂项")]
        [Title("获取元素的名称")]
        [Description("获取元素的名称")]
        public void XLinq95() {
            XDocument doc = XDocument.Load(dataPath + "nw_customers.xml");
            XElement e = doc.Elements()
                            .First();
            Console.WriteLine("Name of element {0}", e.Name);
        }

        [Category("杂项")]
        [Title("获取特性的名称")]
        [Description("获取特性的名称")]
        public void XLinq96() {
            XDocument doc = XDocument.Load(dataPath + "nw_customers.xml");
            XAttribute a = doc.Element("Root")
                              .Element("Customers")
                              .Attributes().First();
            Console.WriteLine("Name of attribute {0}", a.Name);
        }

        [Category("杂项")]
        [Title("获取 XML 声明")]
        [Description("获取 XML 声明")]
        public void XLinq97() {
            XDocument doc = XDocument.Load(dataPath + "config.xml");
            Console.WriteLine("Version {0}", doc.Declaration.Version);
            Console.WriteLine("Encoding {0}", doc.Declaration.Encoding);
            Console.WriteLine("Standalone {0}", doc.Declaration.Standalone);
        }


        [Category("杂项")]
        [Title("查找节点的类型")]
        [Description("查找节点的类型")]
        public void XLinq98() {
            XNode o = new XElement("foo");
            Console.WriteLine(o.NodeType);
        }

        [Category("杂项")]
        [Title("验证电话号码")]
        [Description("验证 xxx-xxx-xxxx 格式的电话号码")]
        [LinkedMethod("CheckPhone")]
        public void XLinq99() {
            XDocument doc = XDocument.Load(dataPath + "nw_customers.xml");
            var query =
                from customer in doc.Descendants("Customers")
                select
                    new XElement("customer",
                                 customer.Attribute("CustomerID"),
                                 customer.Descendants("Phone").First(),
                                 CheckPhone((string)customer.Descendants("Phone").First()));
            foreach (var result in query)
                Console.WriteLine(result);

        }
        static XElement CheckPhone(string phone) {
            Regex regex = new Regex("([0-9]{3}-)|('('[0-9]{3}')')[0-9]{3}-[0-9]{4}");
            return new XElement("isValidPhone", regex.IsMatch(phone));
        }

        [Category("杂项")]
        [Title("快速验证")]
        [Description("验证文件结构")]
        [LinkedMethod("VerifyCustomer")]
        public void XLinq100() {
            XDocument doc = XDocument.Load(dataPath + "nw_customers.xml");
            foreach (XElement customer in doc.Descendants("Customers")) {
                string err = VerifyCustomer(customer);
                if (err != "")
                    Console.WriteLine("Cusotmer {0} is invalid. Missing {1}",
                                        (string)customer.Attribute("CustomerID"), err);
            }

        }
        static string VerifyCustomer(XElement c) {
            if (c.Element("CompanyName") == null)
                return "CompanyName";
            if (c.Element("ContactName") == null)
                return "ContactName";
            if (c.Element("ContactTitle") == null)
                return "ContactTitle";
            if (c.Element("Phone") == null)
                return "Phone";
            if (c.Element("Fax") == null)
                return "Fax";
            if (c.Element("FullAddress") == null)
                return "FullAddress";
            return "";
        }


        [Category("杂项")]
        [Title("聚合函数")]
        [Description("计算所有订单运费的总额、平均值、最小值和最大值")]
        public void XLinq101() {
            XDocument doc = XDocument.Load(dataPath + "nw_orders.xml");
            var query =
                from
                    order in doc.Descendants("Orders")
                where
                    (string)order.Element("CustomerID") == "VINET" &&
                    order.Elements("ShipInfo").Elements("Freight").Any()
                select
                    (double)order.Element("ShipInfo").Element("Freight");

            double sum = query.Sum();
            double average = query.Average();
            double min = query.Min();
            double max = query.Max();

            Console.WriteLine("Sum: {0}, Average: {1}, Min: {2}, Max: {3}", Convert.ToString(sum, CultureInfo.InvariantCulture),
                Convert.ToString(average, CultureInfo.InvariantCulture), Convert.ToString(min, CultureInfo.InvariantCulture),
                Convert.ToString(max, CultureInfo.InvariantCulture));
        }

        [Category("事件")]
        [Title("添加/移除事件")]
        [Description("将事件侦听器附加到根元素并添加/移除子元素")]
        [LinkedMethod("OnChanging")]
        [LinkedMethod("OnChanged")]
        public void XLinq102() {
            string xml = "<order >" +
                            "<item price='150'>Motor</item>" +
                            "<item price='50'>Cable</item>" +
                            "<item price='50'>Modem</item>" +
                            "<item price='250'>Monitor</item>" +
                            "<item price='10'>Mouse</item>" +
                         "</order>";
            XDocument order = XDocument.Parse(xml);
            // 将事件侦听器添加到订单
            order.Changing += new EventHandler<XObjectChangeEventArgs>(OnChanging);
            order.Changed += new EventHandler<XObjectChangeEventArgs>(OnChanged);
            // 将新商品添加到订单
            Console.WriteLine("Original Order:");
            Console.WriteLine("{0}", order.ToString(SaveOptions.None));
            order.Root.Add(new XElement("item", new XAttribute("price", 350), "Printer"));
            Console.WriteLine("After Add:");
            Console.WriteLine("{0}", order.ToString(SaveOptions.None));
            order.Root.Element("item").Remove();
            Console.WriteLine("After Remove:");
            Console.WriteLine("{0}", order.ToString(SaveOptions.None));
            // 移除事件侦听器
            order.Changing -= new EventHandler<XObjectChangeEventArgs>(OnChanging);
            order.Changed -= new EventHandler<XObjectChangeEventArgs>(OnChanged);
            // 添加其他元素，不应引发事件
            order.Root.Add(new XElement("item", new XAttribute("price", 350), "Printer"));
        }

        [Category("事件")]
        [Title("名称/值更改事件")]
        [Description("将事件侦听器附加到根元素并更改元素名称/值")]
        [LinkedMethod("OnChanging")]
        [LinkedMethod("OnChanged")]
        public void XLinq103() {
            string xml = "<order >" +
                            "<item price='150'>Motor</item>" +
                            "<item price='50'>Cable</item>" +
                            "<item price='50'>Modem</item>" +
                            "<item price='250'>Monitor</item>" +
                            "<item price='10'>Mouse</item>" +
                         "</order>";
            XElement order = XElement.Parse(xml);
            order.Changing += new EventHandler<XObjectChangeEventArgs>(OnChanging);
            order.Changed += new EventHandler<XObjectChangeEventArgs>(OnChanged);
            Console.WriteLine("Original Order:");
            Console.WriteLine("{0}", order.ToString(SaveOptions.None));
            order.Name = "newOrder";
            Console.WriteLine("After Name Change:");
            Console.WriteLine("{0}", order.ToString(SaveOptions.None));
            order.Element("item").Value = "New Item";
            Console.WriteLine("After Value Change:");
            Console.WriteLine("{0}", order.ToString(SaveOptions.None));
        }

        [Category("事件")]
        [Title("多个事件处理程序")]
        [Description("将事件侦听器附加到树中的多个元素")]
        [LinkedMethod("OnChanging")]
        [LinkedMethod("OnChanged")]
        public void XLinq104() {
            string xml = "<order >" +
                            "<item price='150'>Motor</item>" +
                            "<item price='50'>Cable</item>" +
                            "<item price='50'>Modem</item>" +
                            "<item price='250'>Monitor</item>" +
                            "<item price='10'>Mouse</item>" +
                         "</order>";
            XDocument order = XDocument.Parse(xml);
            order.Changing += new EventHandler<XObjectChangeEventArgs>(OnChanging);
            order.Changed += new EventHandler<XObjectChangeEventArgs>(OnChanged);
            order.Root.Changing += new EventHandler<XObjectChangeEventArgs>(OnChanging);
            order.Root.Changed += new EventHandler<XObjectChangeEventArgs>(OnChanged);
            // 此元素不应收到任何事件，因为将对
            // 根元素进行更改
            order.Root.Element("item").Changing += new EventHandler<XObjectChangeEventArgs>(OnChanging);
            order.Root.Element("item").Changed += new EventHandler<XObjectChangeEventArgs>(OnChanged);
            Console.WriteLine("Original Order:");
            Console.WriteLine("{0}", order.ToString(SaveOptions.None));
            // 这不应引发“order.Root.Element("item")”的任何事件
            order.Root.Add(new XElement("item", "Printer"));
            Console.WriteLine("After Add:");
            Console.WriteLine("{0}", order.ToString(SaveOptions.None));
        }

        public void OnChanging(object sender, XObjectChangeEventArgs e) {
            Console.WriteLine();
            Console.WriteLine("OnChanging:");
            Console.WriteLine("EventType: {0}", e.ObjectChange);
            Console.WriteLine("Object: {0}", ((XNode)sender).ToString(SaveOptions.None));
        }

        public void OnChanged(object sender, XObjectChangeEventArgs e) {
            Console.WriteLine();
            Console.WriteLine("OnChanged:");
            Console.WriteLine("EventType: {0}", e.ObjectChange);
            Console.WriteLine("Object: {0}", ((XNode)sender).ToString(SaveOptions.None));
            Console.WriteLine();
        }

        [Category("事件")]
        [Title("订单日志")]
        [Description("添加订单时对其进行记录")]
        public void XLinq105() {
            string xml = "<order >" +
                            "<item price='150'>Motor</item>" +
                            "<item price='50'>Cable</item>" +
                            "<item price='50'>Modem</item>" +
                            "<item price='250'>Monitor</item>" +
                            "<item price='10'>Mouse</item>" +
                         "</order>";
            XElement order = XElement.Parse(xml);
            int orderCount = 0;
            StringWriter log = new StringWriter();

            order.Changed += new EventHandler<XObjectChangeEventArgs>(
                    delegate(object sender, XObjectChangeEventArgs e) {
                        orderCount++;
                        log.WriteLine(((XNode)sender).ToString(SaveOptions.None));
                    });

            for (int i = 0; i < 100; i++) {
                order.Add(new XElement("item", new XAttribute("price", 350), "Printer"));
            }

            Console.WriteLine("Orders Received: {0}", orderCount);
            Console.WriteLine("Orders Log:");
            Console.WriteLine(log.ToString());
        }
    }
}