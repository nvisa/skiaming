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

/*定义位图填充。可对位图进行平滑处理、重复位图或平铺位图以填充区域，
或使用转换矩阵处理位图。 
将 GraphicsBitmapFill 对象与 Graphics.drawGraphicsData() 方法一起使用。
绘制 GraphicsBitmapFill 对象与调用 Graphics.beginBitmapFill() 方法是等效的。*/

	class	GraphicsBitmapFill : public Object	//OK
	{
	public:
		//创建新的 GraphicsBitmapFill 对象。 GraphicsBitmapFill
		GraphicsBitmapFill(BitmapData  bitmapData= null,Matrix   matrix= null,Boolean   repeat= true,Boolean   smooth= false);
	private:
		//透明的或不透明的位图图像。 GraphicsBitmapFill
		BitmapData bitmapData;
		//一个用于定义位图上的转换的 Matrix 对象（属于 flash.geom.Matrix 类）。 GraphicsBitmapFill
		Matrix matrix;
		//指定是否以平铺模式重复位图图像。 GraphicsBitmapFill
		Boolean repeat;
		//指定是否将平滑处理算法应用于位图图像。 GraphicsBitmapFill
		Boolean smooth;

	};
}