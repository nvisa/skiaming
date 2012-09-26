#pragma once
#include "StdAfx.h"
#include "Object.h"
#include <vector>
#include <string>
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
//所有 SWF 文件（以 DisplayObject.root 形式表示）、容器对象（DisplayObjectContainer 和子类）、
//按钮（SimpleButton 和子类）以及文本（TextField 和子类）。


	class	AccessibilityProperties: public Object
	{
	private:
		String description;		//在呈现辅助功能时为该显示对象提供一个说明。 AccessibilityProperties 
		Boolean forceSimple;		//如果为 true，则会导致 Flash Player 从辅助演示中排除该显示对象内的子对象。 AccessibilityProperties 
		String name;		//在呈现辅助功能时为该显示对象提供一个名称。 AccessibilityProperties 
		Boolean noAutoLabeling;		//如果为 true，则禁用 Flash Player 的默认自动标签系统。 AccessibilityProperties 
		String shortcut;		//指出与该显示对象关联的快捷键。 AccessibilityProperties 
		Boolean silent;		//如果为 true，则在呈现辅助功能时排除该显示对象。 AccessibilityProperties 
	};
}