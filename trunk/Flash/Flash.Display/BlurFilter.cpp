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

/*可使用 BlurFilter 类将模糊视觉效果应用于显示对象。模糊效果可以柔化图像的细节。
您可以生成一些模糊效果，范围从创建一个柔化的、未聚焦的外观到高斯模糊（就像通过半透明玻璃查看图像一样的朦胧的外观）。
当此滤镜的 quality 属性设置为低时，结果为柔化的、未聚焦的外观。当 quality 属性设置为高时，该属性接近高斯模糊滤镜。
您可以将滤镜应用于任何显示对象（即，从 DisplayObject 类继承的对象），例如 MovieClip、SimpleButton、TextField 和 
Video 对象，以及 BitmapData 对象。 
要创建新的滤镜，请使用构造函数 new BlurFilter()。滤镜的具体使用取决于要应用滤镜的对象：
要对影片剪辑、文本字段、按钮和视频应用滤镜，请使用 filters 属性（继承自 DisplayObject）。
设置对象的 filters 属性不会修改相应的对象，而清除 filters 属性可以删除相应的滤镜。 
要对 BitmapData 对象应用滤镜，请使用 BitmapData.applyFilter() 方法。
对 BitmapData 对象调用 applyFilter() 会取得源 BitmapData 对象和滤镜对象，并最终生成一个过滤图像。 
如果对显示对象应用滤镜，显示对象的 cacheAsBitmap 属性将设置为 true。
如果删除所有滤镜，将恢复 cacheAsBitmap 的原始值。
此滤镜支持舞台缩放。但是，它不支持常规缩放、旋转和倾斜。如果对象本身进行了缩放（scaleX 和 scaleY 未设置为 100%），
滤镜效果将不进行缩放。只有用户在舞台上进行放大时它才会缩放。
如果所得图像超过最大尺寸，则不应用滤镜。*/

	class    BlurFilter: public BitmapFilter
	{
	public:
		//用指定参数初始化滤镜。 BlurFilter
		BlurFilter(Number  blurX= 4.0,Number   blurY= 4.0,int   quality= 1);
		//[override] 返回此滤镜对象的副本。 BlurFilter
		BitmapFilter    clone( );
	private:
		//水平模糊量。 BlurFilter
		Number blurX;
		//垂直模糊量。 BlurFilter
		Number blurY;
		//执行模糊的次数。 BlurFilter
		int quality;
		
		

	};
}
