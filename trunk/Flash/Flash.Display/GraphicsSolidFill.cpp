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

/*
定义实心填充。 
将 GraphicsSolidFill 对象与 Graphics.drawGraphicsData() 方法一起使用。
绘制 GraphicsSolidFill 对象与调用 Graphics.beginFill() 方法是等效的。*/

	class	GraphicsSolidFill : public Object	//OK
	{
		//创建新的 GraphicsSolidFill 对象。 GraphicsSolidFill
		GraphicsSolidFill(uint  color= 0,Number   alpha= 1.0);
		//指示填充的 Alpha 透明度值。 GraphicsSolidFill
		Number alpha = 1.0 ;
		//填充的颜色。 GraphicsSolidFill
		uint color = 0;
	};
}