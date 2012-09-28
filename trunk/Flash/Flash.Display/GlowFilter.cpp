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

/*使用 GlowFilter 类可以对显示对象应用发光效果。有多个用于发光样式的选项，包括内侧发光或外侧发光以及挖空模式。
在投影滤镜的 distance 和 angle 属性设置为 0 时，发光滤镜与投影滤镜极为相似。您可以将滤镜应用于任何显示
对象（即，从 DisplayObject 类继承的对象），例如 MovieClip、SimpleButton、TextField 和 Video 对象，
以及 BitmapData 对象。 
滤镜的具体使用取决于要应用滤镜的对象：
要对显示对象应用滤镜，请使用 filters 属性（继承自 DisplayObject）。设置对象的 filters 属性不会修改相应的对象，
而清除 filters 属性可以删除相应的滤镜。 
要对 BitmapData 对象应用滤镜，请使用 BitmapData.applyFilter() 方法。对 BitmapData 对象调用 applyFilter() 会取得
源 BitmapData 对象和滤镜对象，并最终生成一个过滤图像。 
如果对显示对象应用滤镜，显示对象的 cacheAsBitmap 属性将设置为 true。
如果清除所有滤镜，将恢复 cacheAsBitmap 的原始值。
此滤镜支持舞台缩放。但是，它不支持常规缩放、旋转和倾斜。如果对象本身进行了缩放（如果将 scaleX 和 scaleY 
设置为除 1.0 以外的其他值），滤镜将不进行缩放。只有用户在舞台上进行放大时它才会缩放。
如果所得图像超过最大尺寸，则不应用滤镜*/



	class    GlowFilter: public BitmapFilter
	{
	public:
		//用指定参数初始化新的 GlowFilter 实例。 GlowFilter
		GlowFilter(uint  color= 0xFF0000,Number   alpha= 1.0,Number   blurX= 6.0,Number   blurY= 6.0,Number   strength= 2,int   quality= 1,Boolean   inner= false,Boolean   knockout= false);
		//[override] 返回此滤镜对象的副本。 GlowFilter
		BitmapFilter    clone( );
	private:
		//颜色的 Alpha 透明度值。 GlowFilter
		Number alpha;
		//水平模糊量。 GlowFilter
		Number blurX;
		//垂直模糊量。 GlowFilter
		Number blurY;
		//光晕颜色。 GlowFilter
		uint color;
		//指定发光是否为内侧发光。 GlowFilter
		Boolean inner;
		//指定对象是否具有挖空效果。 GlowFilter
		Boolean knockout;
		//应用滤镜的次数。 GlowFilter
		int quality;
		//印记或跨页的强度。 GlowFilter
		Number strength;

	};
}
