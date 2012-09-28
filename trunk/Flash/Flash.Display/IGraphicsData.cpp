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
	//接口类
	//实现器 GraphicsBitmapFill, GraphicsEndFill, GraphicsGradientFill, GraphicsPath, GraphicsShaderFill, 
	//GraphicsSolidFill, GraphicsStroke, GraphicsTrianglePath 
	class	IGraphicsData: public Object
	{
	
	};
}