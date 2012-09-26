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

/*定义渐变填充。 
将 GraphicsGradientFill 对象与 Graphics.drawGraphicsData() 方法一起使用。
绘制 GraphicsGradientFill 对象与调用 Graphics.beginGradientFill() 方法是等效的。 */
	class	GraphicsGradientFill : public Object	//OK
	{
	public:
		//创建新的 GraphicsGradientFill 对象。 GraphicsGradientFill
		GraphicsGradientFill(String  type= "linear",Array   colors= null,Array   alphas= null,Array   ratios= null,*   matrix= null,*   spreadMethod= pad,String   interpolationMethod= "rgb",Number   focalPointRatio= 0.0);
	private:
		//colors 数组中的对应颜色的 Alpha 值的数组。 GraphicsGradientFill
		Array alphas;
		//渐变中使用的 RGB 十六进制颜色值数组。 GraphicsGradientFill
		Array colors;
		//一个控制渐变的焦点位置的数字。 GraphicsGradientFill
		Number focalPointRatio;
		//InterpolationMethod 类中用于指定要使用的值的值。 GraphicsGradientFill
		String interpolationMethod;
		//一个由 Matrix 类定义的转换矩阵。 GraphicsGradientFill
		Matrix matrix;
		//颜色分布比例的数组。 GraphicsGradientFill
		Array ratios;
		//SpreadMethod 类中用于指定要使用的扩展方法的值。 GraphicsGradientFill
		String spreadMethod;
		//GradientType 类中用于指定要使用的渐变类型的值。 GraphicsGradientFill
		String type;

	};
}