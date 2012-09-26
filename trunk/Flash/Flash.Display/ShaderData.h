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
/*Shader 实例表示 ActionScript 中的 Pixel Bender 着色器内核。
要在应用程序中使用着色器，请为它创建一个 Shader 实例。然后，
根据要创造的效果，按适当的方式使用该 Shader 实例。例如，
要将着色器用作滤镜，可将 Shader 实例赋予 ShaderFilter 对象的 
shader 属性。 
着色器定义对图像中的所有像素执行的函数（一次一个像素）。
对该函数的每次调用的结果都是图像中该像素坐标处的输出颜色。
着色器可以指定一个或多个输入图像，这些图像的内容可
用于确定函数的输出。着色器还可以指定一个或多个参数，
这些参数是可用于计算函数输出的输入值。在单一着色器
执行中，输入和参数值是常量。唯一发生变化的是
像素（其颜色是函数结果）的坐标。针对多个输出像素
坐标的着色器函数调用将并行执行，以改进着色器执行性能。*/


	class	ShaderData: public Object
	{
	public:
		ShaderData(ByteArray byteCode);		//创建 ShaderData 实例。
	private:
	};
}