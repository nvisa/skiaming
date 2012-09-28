#pragma once
#include "StdAfx.h"
#include "DisplayObject.h"
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
/*InteractiveObject 类是用户可以使用鼠标和键盘与之交互的所有显示对象的抽象基类。 
不能直接实例化 InteractiveObject 类。调用 new InteractiveObject() 构造函数会
引发 ArgumentError 异常。
InteractiveObject 类本身不包含任何用于在屏幕上呈现内容的 API。鉴于此原因，
如果要创建 InteractiveObject 类的一个自定义子类，您将需要扩展其中一个具有在屏幕
上显示内容的 API 的子类，如 Sprite、SimpleButton、TextField 或 MovieClip 类。*/


	class	InteractiveObject : public DisplayObject
	{
	public:
		InteractiveObject();	//调用新的 InteractiveObject() 构造函数会引发 ArgumentError 异常。
	private:
		NativeMenu contextMenu;	//指定与此对象相关联的上下文菜单。 InteractiveObject 
		Boolean doubleClickEnabled;	//指定此对象是否接收 doubleClick 事件。 InteractiveObject 
		Object focusRect;	//指定此对象是否显示焦点矩形。 InteractiveObject 
		Boolean tabEnabled;	//指定此对象是否遵循 Tab 键顺序。 InteractiveObject 
		int tabIndex;	//指定 SWF 文件中的对象按 Tab 键顺序排列。 InteractiveObject 
	};
}