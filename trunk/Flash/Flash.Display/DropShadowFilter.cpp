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

/*可使用 DropShadowFilter 类向显示对象添加投影。阴影算法基于模糊滤镜使用的同一个框型滤镜。投影样式有多个选项，
包括内侧或外侧阴影和挖空模式。您可以将滤镜应用于任何显示对象（即，从 DisplayObject 类继承的对象),
例如 MovieClip、SimpleButton、TextField 和 Video 对象，以及 BitmapData 对象。 
滤镜的具体使用取决于要应用滤镜的对象：
要对显示对象应用滤镜，请使用 filters 属性（继承自 DisplayObject）。设置对象的 filters 属性不会修改相应的对象，
而清除 filters 属性可以删除相应的滤镜。 
要对 BitmapData 对象应用滤镜，请使用 BitmapData.applyFilter() 方法。对 BitmapData 对象调用 applyFilter() 会取得
源 BitmapData 对象和滤镜对象，并最终生成一个过滤图像。 
如果对显示对象应用滤镜，则该显示对象的 cacheAsBitmap 属性值将设置为 true。如果清除所有滤镜，
将恢复 cacheAsBitmap 的原始值。
此滤镜支持舞台缩放。但是，它不支持常规缩放、旋转和倾斜。如果对象本身进行了缩放（如果将 scaleX 和 scaleY 
设置为除 1.0 以外的其他值），滤镜将不进行缩放。只有用户在舞台上进行放大时它才会缩放。
如果所得图像超过最大尺寸，则不应用滤镜。*/


	class    DropShadowFilter: public BitmapFilter
	{
	public:
		//用指定参数创建新的 DropShadowFilter 实例。 DropShadowFilter
		DropShadowFilter(Number  distance= 4.0,Number   angle= 45,uint   color= 0,Number   alpha= 1.0,Number   blurX= 4.0,Number   blurY= 4.0,Number   strength= 1.0,int   quality= 1,Boolean   inner= false,Boolean   knockout= false,Boolean   hideObject= false);
		//[override] 返回此滤镜对象的副本。 DropShadowFilter
		BitmapFilter    clone( );
	private:
		//阴影颜色的 Alpha 透明度值。 DropShadowFilter
		Number alpha;
		//阴影的角度。 DropShadowFilter
		Number angle;
		//水平模糊量。 DropShadowFilter
		Number blurX;
		//垂直模糊量。 DropShadowFilter
		Number blurY;
		//阴影的颜色。 DropShadowFilter
		uint color;
		//阴影的偏移距离，以像素为单位。 DropShadowFilter
		Number distance;
		//表示是否隐藏对象。 DropShadowFilter
		Boolean hideObject;
		//表示阴影是否为内侧阴影。 DropShadowFilter
		Boolean inner;
		//应用挖空效果 (true)，这将有效地使对象的填色变为透明，并显示文档的背景颜色。 DropShadowFilter
		Boolean knockout;
		//应用滤镜的次数。 DropShadowFilter
		int quality;
		//印记或跨页的强度。 DropShadowFilter
		Number strength;

	};
}
