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

/*使用 GradientBevelFilter 类可以对显示对象应用渐变斜角效果。渐变斜角是位于对象外部、内部或顶部的使用渐变色增强
的有斜面	的边缘。有斜面的边缘使对象具有三维外观。您可以将滤镜应用于任何显示对象（即，从 DisplayObject 类继承
的对象），例如 MovieClip、SimpleButton、TextField 和 Video 对象，以及 BitmapData 对象。 
滤镜的具体使用取决于要应用滤镜的对象：
要对显示对象应用滤镜，请使用 filters 属性。设置对象的 filters 属性不会修改相应的对象，而清除 filters 属性可以删除相应的滤镜。 
要对 BitmapData 对象应用滤镜，请使用 BitmapData.applyFilter() 方法。对 BitmapData 对象
调用 applyFilter() 会取得源 BitmapData 对象和滤镜对象，并最终生成一个过滤图像。 
如果对显示对象应用滤镜，显示对象的 cacheAsBitmap 属性将设置为 true。如果清除所有滤镜，
将恢复 cacheAsBitmap 的原始值。
此滤镜支持舞台缩放。但是，它不支持常规缩放、旋转和倾斜；如果对象本身进行了缩放（如果
将 scaleX 和 scaleY 设置为除 1.0 以外的其他值），滤镜效果将不进行缩放。只有用户在舞台上进行放大时它才会缩放。
如果所得图像超过最大尺寸，则不应用滤镜。*/


	class GradientBevelFilter: public BitmapFilter
	{
	public:
		//用指定参数初始化滤镜。 GradientBevelFilter
		GradientBevelFilter(Number  distance= 4.0,Number   angle= 45,Array   colors= null,Array   alphas= null,Array   ratios= null,Number   blurX= 4.0,Number   blurY= 4.0,Number   strength= 1,int   quality= 1,String   type= "inner",Boolean   knockout= false);
		//[override] 返回此滤镜对象的副本。 GradientBevelFilter
		BitmapFilter    clone( );
	private:
		//colors 数组中对应颜色的 Alpha 透明度值的数组。 GradientBevelFilter
		Array alphas;
		//角度，以度为单位。 GradientBevelFilter
		Number angle;
		//水平模糊量。 GradientBevelFilter
		Number blurX;
		//垂直模糊量。 GradientBevelFilter
		Number blurY;
		//渐变中使用的 RGB 十六进制颜色值数组。 GradientBevelFilter
		Array colors;
		//偏移距离。 GradientBevelFilter
		Number distance;
		//指定对象是否具有挖空效果。 GradientBevelFilter
		Boolean knockout;
		//应用滤镜的次数。 GradientBevelFilter
		int quality;
		//对应于 colors 数组中颜色的一组颜色分布比率。 GradientBevelFilter
		Array ratios;
		//印记或跨页的强度。 GradientBevelFilter
		Number strength;
		//斜角效果的放置。 GradientBevelFilter
		String type;

	};
}
