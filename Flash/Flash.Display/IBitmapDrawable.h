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
	//利用 AccessibilityProperties 类可控制 Flash 对象辅助功能（如屏幕阅读器）演示。
	//可以将 AccessibilityProperties 对象附加到任何显示对象，
	//但是 Flash Player 只会读取以下某些类型的对象的 AccessibilityProperties 对象：
	//所有 SWF 文件（以 DisplayObject.root 形式表示）、容器对象（ DisplayObjectContainer 和子类）、
	//按钮（SimpleButton 和子类）以及文本（ TextField 和子类）。


	class    IBitmapDrawable: public Object
	{

	};
}
