#pragma once
#include "StdAfx.h"
#include "Object.h"
namespace splght{
#ifndef Boolean
#define Boolean bool
#endif

#ifndef unit
#define uint unsigned int
#endif

#ifndef NaN
#define NaN -1
#endif

	//#define BitmapData SkBitmap	
#ifndef null
#define null NULL
#endif

#ifndef String
#define String string
#endif

#ifndef Number
#define Number float
#endif
/*
URLRequest 类可捕获单个 HTTP 请求中的所有信息。URLRequest 对象将传递给 
Loader、URLStream 和 URLLoader 类的 load() 方法和其它加载操作，
以便启动 URL 下载。这些对象还将传递给 FileReference 类的 upload() 和 download() 方法。 
只能与本地文件系统内容交互的沙箱中的 SWF 文件无法加载网络沙箱中的资源所
包含的数据，也无法为该资源提供数据。 
默认情况下，执行调用的 SWF 文件和加载的 URL 必须在同一域中。
例如，位于 www.adobe.com 的 SWF 文件只能从同样位于 www.adobe.com 
的源中加载数据。要从不同的域中加载数据，请在承载数据的服务器上放置
一个 URL 策略文件。 
但在 Adobe AIR 中，应用程序安全沙箱中的内容（与 AIR 应用程序一起安装的内容）
不受这些安全限制的约束。对于在 Adobe AIR 中运行的内容，
应用程序安全沙箱中的文件可以访问使用以下任一 URL 方案的 URL：
应用程序安全域中的文件（随 AIR 应用程序一起安装的文件），
可以使用以下任一 URL 方案访问 URL：
http 和 https 
file 
app-storage 
app */

	class	URLRequest : public Object
	{
	public:
		//创建 URLRequest 对象。 URLRequest
		URLRequest(String  url= null);
	private:
		//指定是否应为此请求处理验证请求，如果是，则为 true，否则为 false。 URLRequest
		Boolean authenticate;
		//指定是否应为此请求缓存成功的响应数据。 URLRequest
		Boolean cacheResponse;
		//data 属性中内容的 MIME 内容类型。 URLRequest
		String contentType;
		//一个对象，它包含将随 URL 请求一起传输的数据。 URLRequest
		Object data;
		//唯一地标识将存储到 Flash Player 缓存中（或从中检索）的已签名 Adobe 平台组件的字符串。 URLRequest
		String digest;
		//指定是否要遵循重定向，如果是，则为 true，否则为 false。 URLRequest
		Boolean followRedirects;
		//指定 HTTP 协议堆栈是否应管理此请求的 cookie。 URLRequest
		Boolean manageCookies;
		//控制 HTTP 式提交方法。 URLRequest
		String method;
		//要追加到 HTTP 请求的 HTTP 请求标头的数组。 URLRequest
		Array requestHeaders;
		//所请求的 URL。 URLRequest
		String url;
		//指定在此 URLRequest 获取数据之前是否应查询本地缓存。 URLRequest
		Boolean useCache;
		//指定要在 HTTP 请求中使用的用户代理字符串。 URLRequest
		String userAgent;
	};
}