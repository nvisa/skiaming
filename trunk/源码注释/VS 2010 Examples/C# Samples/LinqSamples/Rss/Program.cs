// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
//版权所有(C) Microsoft Corporation。保留所有权利。

//用户可能需要具有管理员身份才能运行此应用程序
using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Xml;
using System.Linq;
using System.Xml.Linq;
using System.Net;

// 有关其他信息，请参阅 ReadMe.html
class app {
    const string feedUrl = "http://+:8086/csharpfeeds/";

    static IEnumerable<XElement> GetItems() {
        string[] feeds = {
            "http://blogs.msdn.com/ericlippert/rss.aspx",
            "http://blogs.msdn.com/wesdyer/rss.aspx",
            "http://blogs.msdn.com/charlie/rss.aspx",            
            "http://blogs.msdn.com/cyrusn/rss.aspx",
            "http://blogs.msdn.com/mattwar/rss.aspx",
            "http://blogs.msdn.com/lucabol/rss.aspx",
            "http://www.pluralsight.com/blogs/dbox/rss.aspx",
            "http://blogs.msdn.com/jomo_fisher/rss.aspx"
        };
        foreach (var str in feeds) {
            var feed = XDocument.Load(str);
            var items = feed.Root.Element("channel").Elements("item");
            foreach (var item in items)
                yield return item;
        }
    }

    static XElement GetReplyBody() {
        return new XElement("rss",
            new XAttribute("version", "2.0"),
            new XElement("channel",
              new XElement("title", "C# Geeks"),
              new XElement("link", feedUrl),
              new XElement("description", "C# Team Members"),
              new XElement("generator", "LinqToXml-based RSS aggregator"),
              GetItems().ToArray()
              ));

    }

    //用户可能需要具有管理员身份才能运行此应用程序
    static void Main() {
        var listener = new HttpListener();

        listener.Prefixes.Add("http://+:8086/csharpfeeds/");
        listener.Start();

        // 打开指向将为其提供服务的源的浏览器。
        string uri = @"http://localhost:8086/csharpfeeds/";
        System.Diagnostics.Process browser = new System.Diagnostics.Process();
        browser.StartInfo.FileName = "iexplore.exe";
        browser.StartInfo.Arguments = uri;
        browser.Start();

        // 为请求提供服务。
        while (true) {
            var context = listener.GetContext();
            var body = GetReplyBody();
            context.Response.ContentType = "text/xml";
            using (XmlWriter writer = new XmlTextWriter(context.Response.OutputStream, Encoding.UTF8)) 
                body.WriteTo(writer);

        }
    }
}