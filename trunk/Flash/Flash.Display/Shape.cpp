#pragma once
#include "StdAfx.h"
#include "Object.h"
#include "BitmapData.h"
#include "DisplayObject.h"
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

/*此类用于使用 ActionScript 绘图应用程序编程接口 (API) 创建简单形状。
Shape 类包括 graphics 属性，该属性使您可以从 Graphics 类访问方法。 
Sprite 类也包括 graphics 属性，并且它包括不可用于 Shape 类的其他功能。
例如，Sprite 对象是显示对象容器，而 Shape 对象不是（并且不能包含子显示对象）。
由于此原因，Shape 对象会比包含相同图形的 Sprite 对象消耗的内存少。
但是，Sprite 对象支持鼠标单击事件，而 Shape 对象不支持。*/


	class	Shape: public DisplayObject	//OK
	{
	public:	
		//创建新的 Shape 对象。 Shape
		Shape( );
	private:
		//[只读] 指定属于该 Shape 对象的 Graphics 对象，可通过此对象执行矢量绘画命令。 Shape
		Graphics graphics;
	};
}