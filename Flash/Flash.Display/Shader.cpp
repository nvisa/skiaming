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
//Shader 实例表示 ActionScript 中的 Pixel Bender 着色器内核。
//要在应用程序中使用着色器，请为它创建一个 Shader 实例。然后，根据要创造的效果，按适当的方式使用该 Shader 实例。
//例如，要将着色器用作滤镜，可将 Shader 实例赋予 ShaderFilter 对象的 shader 属性。
	class	Shader: public Object	//OK
	{
	public:
		Shader(ByteArray code = null);		//创建一个新的 Shader 实例。
	private:
		ByteArray byteCode;		//[只写] 此 Shader 实例的原始着色器字节代码。 Shader 
		ShaderData data;		//提供对 Shader 实例的参数、输入图像和元数据的访问。 Shader 
		String precisionHint;		//着色器所执行数学运算的精度。 
	};
}