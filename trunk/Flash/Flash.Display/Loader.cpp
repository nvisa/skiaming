#pragma once
#include "StdAfx.h"
#include "DisplayObjectContainer.h"
#include "LoaderInfo.h"
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
//Loader 类可用于加载 SWF 文件或图像（JPG、PNG 或 GIF）文件。使用 load() 方法来启动加载。
//被加载的显示对象将作为 Loader 对象的子级添加。
//使用 URLLoader 类加载文本或二进制数据。
	class	Loader : public  DisplayObjectContainer 
	{
	public:
		//创建一个可用于加载文件（如 SWF、JPEG、GIF 或 PNG 文件）的 Loader 对象。 Loader
		Loader( );
		//取消当前正在对 Loader 实例执行的 load() 方法操作。 Loader
		void    close( );
		//将 SWF、JPEG、渐进式 JPEG、非动画 GIF 或 PNG 文件加载到此 Loader 对象的子对象中。 Loader
		void    load(URLRequest request,LoaderContext   context= null);
		//从 ByteArray 对象中所存储的二进制数据中加载。 Loader
		void    loadBytes(ByteArray bytes,LoaderContext   context= null);
		//删除此 Loader 对象中使用 load() 方法加载的子项。 Loader
		void    unload( );
		//尝试卸载子 SWF 文件内容并停止执行已加载的 SWF 文件中的命令。 Loader
		void    unloadAndStop(Boolean  gc= true);
		
	private:
		//[只读] 包含使用 load() 或 loadBytes() 方法加载的 SWF 文件或图像（JPG、PNG 或 GIF）文件的根显示对象。 Loader
		DisplayObject content;
		//[只读] 返回与正在加载的对象相对应的 LoaderInfo 对象。 Loader
		LoaderInfo contentLoaderInfo;

	};
}