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

/*使用 ColorMatrixFilter 类可以将 4 x 5 矩阵转换应用于输入图像上的每个像素的 RGBA 颜色和 Alpha 值，
以生成具有一组新的 RGBA 颜色和 Alpha 值的结果。该类允许饱和度更改、色相旋转、亮度为 Alpha 以及各种其他效果。
您可以将滤镜应用于任何显示对象（即，从 DisplayObject 类继承的对象），例如 MovieClip、SimpleButton、
TextField 和 Video 对象，以及 BitmapData 对象。 
注意：对于 RGBA 值，最高有效字节代表红色通道值，其后的有效字节分别代表绿色、蓝色和 Alpha 通道值。
要创建新的颜色矩阵滤镜，请使用 new ColorMatrixFilter() 语法。滤镜的具体使用取决于要应用滤镜的对象：
要对影片剪辑、文本字段、按钮和视频应用滤镜，请使用 filters 属性（继承自 DisplayObject）。
设置对象的 filters 属性不会修改相应的对象，而清除 filters 属性可以删除相应的滤镜。 
要对 BitmapData 对象应用滤镜，请使用 BitmapData.applyFilter() 方法。
对 BitmapData 对象调用 applyFilter() 会取得源 BitmapData 对象和滤镜对象，并最终生成一个过滤图像。 
如果对显示对象应用滤镜，显示对象的 cacheAsBitmap 属性将设置为 true。
如果删除所有滤镜，将恢复 cacheAsBitmap 的原始值。
如果所得图像超过最大尺寸，则不应用滤镜。*/

	class    ColorMatrixFilter: public BitmapFilter
	{
	public:
		//用指定参数初始化新的 ColorMatrixFilter 实例。 ColorMatrixFilter
		ColorMatrixFilter(Array  matrix= null);
		//[override] 返回此滤镜对象的副本。 ColorMatrixFilter
		BitmapFilter    clone( );
	private:
		//由 20 个项目组成的数组，适用于 4 x 5 颜色转换。 ColorMatrixFilter
		Array matrix;

	};
}
