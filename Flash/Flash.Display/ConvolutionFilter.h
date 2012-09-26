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

/*ConvolutionFilter 类应用矩阵盘绕滤镜效果。卷积将输入图像的像素与相邻的像素合并以生成图像。
通过卷积，可以实现大量的图像效果，包括模糊、边缘检测、锐化、浮雕和斜角。
您可以将滤镜应用于任何显示对象（即，从 DisplayObject 类继承的对象），例如 MovieClip、SimpleButton、
TextField 和 Video 对象，以及 BitmapData 对象。 
要创建卷积滤镜，请使用语法 new ConvolutionFilter()。滤镜的具体使用取决于要应用滤镜的对象：
要对影片剪辑、文本字段、按钮和视频应用滤镜，请使用 filters 属性（继承自 DisplayObject）。
设置对象的 filters 属性不会修改相应的对象，而清除 filters 属性可以删除相应的滤镜。 
要对 BitmapData 对象应用滤镜，请使用 BitmapData.applyFilter() 方法。
对 BitmapData 对象调用 applyFilter() 会取得源 BitmapData 对象和滤镜对象，并最终生成一个过滤图像。 
如果对显示对象应用滤镜，则该对象的 cacheAsBitmap 属性值将设置为 true。
如果清除所有滤镜，将恢复 cacheAsBitmap 的原始值。
如果所得图像超过最大尺寸，则不应用滤镜。*/



	class ConvolutionFilter: public BitmapFilter
	{
	public:
		//用指定参数初始化 ConvolutionFilter 实例。 ConvolutionFilter
		ConvolutionFilter(Number  matrixX= 0,Number   matrixY= 0,Array   matrix= null,Number   divisor= 1.0,Number   bias= 0.0,Boolean   preserveAlpha= true,Boolean   clamp= true,uint   color= 0,Number   alpha= 0.0);
		//[override] 返回此滤镜对象的副本。 ConvolutionFilter
		BitmapFilter    clone( );
	private:
		//替换颜色的 Alpha 透明度值。 ConvolutionFilter
		Number alpha;
		//要添加到矩阵转换结果中的偏差量。 ConvolutionFilter
		Number bias;
		//指示是否应锁定图像。 ConvolutionFilter
		Boolean clamp;
		//要替换源图像之外的像素的十六进制颜色。 ConvolutionFilter
		uint color;
		//矩阵转换中使用的除数。 ConvolutionFilter
		Number divisor;
		//用于矩阵转换的值的数组。 ConvolutionFilter
		Array matrix;
		//矩阵的 x 维度（矩阵中列的数目）。 ConvolutionFilter
		Number matrixX;
		//矩阵的 y 维度（矩阵中行的数目）。 ConvolutionFilter
		Number matrixY;
		//指示是否已保留 Alpha 通道并且不使用滤镜效果，或是否对 Alpha 通道以及颜色通道应用卷积滤镜。 ConvolutionFilter
		Boolean preserveAlpha;

	};
}
