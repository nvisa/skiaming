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


/*指示图形填充的结束。将 GraphicsEndFill 对象与 Graphics.drawGraphicsData() 
方法一起使用。 
绘制 GraphicsEndFill 对象与调用 Graphics.endFill() 方法是等效的。*/ 


	class	GraphicsEndFill : public Object	//OK
	{
	public:
		//创建与 Graphics.drawGraphicsData() 方法一起使用的对象，以显式结束填充。 GraphicsEndFill 
		GraphicsEndFill();
			
	};
}