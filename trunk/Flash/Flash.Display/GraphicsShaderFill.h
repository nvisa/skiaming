#pragma once
#include "StdAfx.h"
#include "Object.h"
#include "Shader.h"
#include "Matrix.h"
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



/*定义着色器填充。 
将 GraphicsShaderFill 对象与 Graphics.drawGraphicsData() 方法一起使用。
绘制 GraphicsShaderFill 对象与调用 Graphics.beginShaderFill() 方法是等效的。 */
	class	GraphicsShaderFill : public Object	//OK
	{
	public:
		//创建新的 GraphicsShaderFill 对象。 GraphicsShaderFill
		GraphicsShaderFill(Shader  shader= null,Matrix   matrix= null);
	private:
		//一个 matrix 对象（属于 flash.geom.Matrix 类），可用于对着色器定义转换。 GraphicsShaderFill
		Matrix matrix;
		//要用于填充的着色器。 GraphicsShaderFill
		Shader shader;

	};
}