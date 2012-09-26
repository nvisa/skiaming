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

/*可使用 ColorTransform 类调整显示对象的颜色值。可以将颜色调整或颜色转换应用于所有
四种通道：红色、绿色、蓝色和 Alpha 透明度。 
当 ColorTransform 对象应用于显示对象时，将按如下方法为每个颜色通道计算新值：
新红色值 = (旧红色值 * redMultiplier) + redOffset 
新绿色值 = (旧绿色值 * greenMultiplier) + greenOffset 
新蓝色值 = (旧蓝色值 * blueMultiplier) + blueOffset 
新 Alpha 值 = (旧 Alpha 值 * alphaMultiplier) + alphaOffset 
如果计算后任何一个颜色通道值大于 255，则该值将被设置为 255。如果该值小于 0，
它将被设置为 0。
可以通过下列方式使用 ColorTransform 对象：
在 BitmapData 类的 colorTransform() 方法的 colorTransform 参数中 
作为 Transform 对象（此对象可以用作显示对象的 transform 属性）的 colorTransform 属性 
必须使用 new ColorTransform() 构造函数创建 ColorTransform 对象后，
才能调用 ColorTransform 对象的方法。
颜色转换不会应用于影片剪辑（如加载的 SWF 对象）的背景色，它们仅应用于
附加到影片剪辑的图形和元件。*/


	class	ColorTransform: public Object	//OK
	{
	public:
		//用指定的颜色通道值和 Alpha 值为显示对象创建 ColorTransform 对象。 ColorTransform
		ColorTransform(Number  redMultiplier= 1.0,Number   greenMultiplier= 1.0,Number   blueMultiplier= 1.0,Number   alphaMultiplier= 1.0,Number   redOffset= 0,Number   greenOffset= 0,Number   blueOffset= 0,Number   alphaOffset= 0);
		//将 second 参数指定的 ColorTranform 对象与当前 ColorTransform 对象连接，并将当前对象设置为结果，即两个颜色转换的相加组合。 ColorTransform
		void    concat(flash.geom:ColorTransform second);
	private:
		//设置字符串格式并将其返回，该字符串描述 ColorTransform 对象的所有属性。 ColorTransform
		String    toString( );
		//与 Alpha 透明度通道值相乘的十进制值。 ColorTransform
		Number alphaMultiplier;
		//-255 到 255 之间的数字，它先与 alphaMultiplier 值相乘，再与 Alpha 透明度通道值相加。 ColorTransform
		Number alphaOffset;
		//与蓝色通道值相乘的十进制值。 ColorTransform
		Number blueMultiplier;
		//-255 到 255 之间的数字，它先与 blueMultiplier 值相乘，再与蓝色通道值相加。 ColorTransform
		Number blueOffset;
		//ColorTransform 对象的 RGB 颜色值。 ColorTransform
		uint color;
		//与绿色通道值相乘的十进制值。 ColorTransform
		Number greenMultiplier;
		//-255 到 255 之间的数字，它先与 greenMultiplier 值相乘，再与绿色通道值相加。 ColorTransform
		Number greenOffset;
		//与红色通道值相乘的十进制值。 ColorTransform
		Number redMultiplier;
		//-255 到 255 之间的数字，它先与 redMultiplier 值相乘，再与红色通道值相加。 ColorTransform
		Number redOffset;

	};
}