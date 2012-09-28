#pragma once
#include "StdAfx.h"

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

/*LoaderInfo 类可提供有关已加载的 SWF 文件或图像文件（JPEG、GIF 或 PNG）的信息。
LoaderInfo 对象可用于任何显示对象。提供的信息包括加载进度、加载程序的 URL 和
加载内容、媒体的字节总数以及媒体的标示的高度和宽度。 
flash.display.Loader 对象的 contentLoaderInfo 属性 - contentLoaderInfo 属性始终
可用于任何 Loader 对象。对于尚未调用 load() 或 loadBytes() 方法，或者尚未充分
加载的 Loader 对象，在尝试访问 contentLoaderInfo 属性的多个属性时，将引发错误。 
显示对象的 loaderInfo 属性。 
Loader 对象的 contentLoaderInfo 属性提供有关 Loader 对象正在加载的内容的信息，
而 DisplayObject 的 loaderInfo 属性提供有关该显示对象的根 SWF 文件的信息。 
当使用 Loader 对象加载显示对象（如 SWF 文件或位图）时，显示对象的 loaderInfo 属性
与 Loader 对象 (DisplayObject.loaderInfo = Loader.contentLoaderInfo) 的 
contentLoaderInfo 属性相同。由于 SWF 文件的主类的实例没有 Loader 对象，
因此 loaderInfo 属性是访问 SWF 文件主类实例的 LoaderInfo 的唯一方法。*/


	class	LoaderInfo: public  EventDispatcher
	{
	public:
		//[静态] 返回与定义为对象的 SWF 文件相关联的 LoaderInfo 对象。 LoaderInfo
		LoaderInfo getLoaderInfoByDefinition(Object object);
	private:
		//[只读] 被加载的 SWF 文件的 ActionScript 版本。 LoaderInfo
		uint actionScriptVersion;
		//[只读] 加载外部 SWF 文件后，包含在已加载类中的所有 ActionScript 3.0 定义将存储在 applicationDomain 属性中。 LoaderInfo
		ApplicationDomain applicationDomain;
		//[只读] 与 LoaderInfo 对象相关联的字节数。 LoaderInfo
		ByteArray bytes;
		//[只读] 媒体已加载的字节数。 LoaderInfo
		uint bytesLoaded;
		//[只读] 整个媒体文件中压缩的字节数。 LoaderInfo
		uint bytesTotal;
		//[只读] 表示内容（子级）对加载者（父级）的信任关系。 LoaderInfo
		Boolean childAllowsParent;
		//一个对象，它可以通过所加载内容的代码进行设置以公开可以由 Loader 对象的沙箱中的代码访问的属性和方法。 LoaderInfo
		Object childSandboxBridge;
		//[只读] 与此 LoaderInfo 对象关联的已加载对象。 LoaderInfo
		DisplayObject content;
		//[只读] 被加载文件的 MIME 类型。 LoaderInfo
		String contentType;
		//[只读] 被加载的 SWF 文件的标示的帧速率，以每秒帧数为单位。 LoaderInfo
		Number frameRate;
		//[只读] 加载文件的标示的高度。 LoaderInfo
		int height;
		//[只读] 与此 LoaderInfo 对象关联的 Loader 对象。 LoaderInfo
		Loader loader;
		//[只读] SWF 文件的 URL，该 SWF 文件启动对此 LoaderInfo 对象所描述的媒体的加载。 LoaderInfo
		String loaderURL;
		//[只读] 包含名称-值对的对象，表示为被加载的 SWF 文件提供的参数。 LoaderInfo
		Object parameters;
		//[只读] 表示加载者（父级）对内容（子级）的信任关系。 LoaderInfo
		Boolean parentAllowsChild;
		//一个对象，它可以在 Loader 对象的沙箱中通过代码进行设置以公开可以由所加载内容的代码访问的属性和方法。 LoaderInfo
		Object parentSandboxBridge;
		//[只读] 表示加载者和内容之间的域关系：如果它们具有相同的原始域，则为 true；否则为 false。 LoaderInfo
		Boolean sameDomain;
		//[只读] EventDispatcher 实例，可用于跨安全边界交换事件。 LoaderInfo
		EventDispatcher sharedEvents;
		//[只读] 已加载的 SWF 文件的文件格式版本。 LoaderInfo
		uint swfVersion;
		//[只读] 所加载媒体的 URL。 LoaderInfo
		String url;
		//[只读] 被加载内容的标示的宽度。 LoaderInfo
		int width;
	};
}