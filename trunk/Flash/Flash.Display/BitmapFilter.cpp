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
	//BitmapFilter 类是所有图像滤镜效果的基类。 
	//BevelFilter、BlurFilter、ColorMatrixFilter、ConvolutionFilter、DisplacementMapFilter、DropShadowFilter、
	//GlowFilter、GradientBevelFilter 和 GradientGlowFilter 类都扩展了 BitmapFilter 类。
	//您可以将这些滤镜效果应用于任何显示对象。
	//不可以直接实例化或扩展 BitmapFilter。

	class	BitmapFilter: public Object
	{
	public:
		//返回 BitmapFilter 对象，它是与原始 BitmapFilter 对象完全相同的副本。 BitmapFilter 
		BitmapFilter clone();
			
	};
}