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
//BitmapFilterQuality 类中包含的值用于设置 BitmapFilter 对象的呈现品质。 


	class    BitmapFilterQuality: public Object
	{
	public:
		// [静态] 定义高品质滤镜设置。 BitmapFilterQuality 
		int HIGH = 3
		//[静态] 定义低品质滤镜设置。 BitmapFilterQuality 
		int LOW = 1
		//[静态] 定义中等品质滤镜设置。 
		int MEDIUM = 2
	};
}
