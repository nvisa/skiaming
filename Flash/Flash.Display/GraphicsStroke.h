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
/*
定义线条样式或笔触。 
将 GraphicsStroke 对象与 Graphics.drawGraphicsData() 方法一起使用。
绘制 GraphicsStroke 对象与调用设置线条样式的 Graphics 类的方法之一
（例如 Graphics.lineStyle() 方法、Graphics.lineBitmapStyle() 方法或 
Graphics.lineGradientStyle() 方法）是等效的。 */


	class	GraphicsStroke: public Object	//OK
	{
	public:
		//创建新的 GraphicsStroke 对象。 GraphicsStroke
		GraphicsStroke(Number  thickness= NaN,Boolean   pixelHinting= false,String   scaleMode= "normal",String   caps= "none",String   joints= "round",Number   miterLimit= 3.0,IGraphicsFill   fill= null);
	private:
		//指定线条结尾处的端点的类型。 GraphicsStroke
		String caps;
		//指定包含用于填充笔触的数据的实例。 GraphicsStroke
		IGraphicsFill fill;
		//指定拐角处使用的连接外观的类型。 GraphicsStroke
		String joints;
		//指示将在哪个限制位置切断尖角。 GraphicsStroke
		Number miterLimit;
		//指定是否提示笔触采用完整像素。 GraphicsStroke
		Boolean pixelHinting;
		//指定笔触粗细缩放。 GraphicsStroke
		String scaleMode;
		//指示以磅为单位的线条粗细；有效值为 0 到 255。 GraphicsStroke
		Number thickness;

	};
}