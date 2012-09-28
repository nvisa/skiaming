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

/*可使用 BevelFilter 类对显示对象添加斜角效果。斜角效果使对象（如按钮）具有三维外观。
您可以利用不同的加亮颜色和阴影颜色、斜角上的模糊量、斜角的角度、斜角的位置和挖空效果来自定义斜角的外观。
您可以将滤镜应用于任何显示对象（即，从 DisplayObject 类继承的对象），例如 MovieClip、SimpleButton、TextField 
和 Video 对象，以及 BitmapData 对象。 
要创建新滤镜，请使用构造函数 new BevelFilter()。滤镜的具体使用取决于要应用滤镜的对象：
要对影片剪辑、文本字段、按钮和视频应用滤镜，请使用 filters 属性（继承自 DisplayObject）。
设置对象的 filters 属性不会修改相应的对象，而清除 filters 属性可以删除相应的滤镜。 
要对 BitmapData 对象应用滤镜，请使用 BitmapData.applyFilter() 方法。
对 BitmapData 对象调用 applyFilter() 会取得源 BitmapData 对象和滤镜对象，并最终生成一个过滤图像。 
如果对显示对象应用滤镜，则该对象的 cacheAsBitmap 属性值将设置为 true。
如果删除所有滤镜，将恢复 cacheAsBitmap 的原始值。
此滤镜支持舞台缩放。但是，它不支持常规缩放、旋转和倾斜。如果对象本身进行了缩放（如果 scaleX 和 scaleY 属性未被
设置为 100%），则滤镜不进行缩放。只有用户在舞台上进行放大时它才会缩放。
如果所得图像超过最大尺寸，则不应用滤镜。*/
	class    BevelFilter: public BitmapFilter
	{
	public:
		BevelFilter(Number  distance= 4.0,Number   angle= 45,uint   highlightColor= 0xFFFFFF,Number   highlightAlpha= 1.0,uint   shadowColor= 0x000000,Number   shadowAlpha= 1.0,Number   blurX= 4.0,Number   blurY= 4.0,Number   strength= 1,int   quality= 1,String   type= "inner",Boolean   knockout= false);
		//[override] 返回此滤镜对象的副本。 BevelFilter
		BitmapFilter    clone( );
	private:
		//斜角的角度。 BevelFilter
		Number angle;
		//水平模糊量，以像素为单位。 BevelFilter
		Number blurX;
		//垂直模糊量，以像素为单位。 BevelFilter
		Number blurY;
		//斜角的偏移距离。 BevelFilter
		Number distance;
		//加亮颜色的 Alpha 透明度值。 BevelFilter
		Number highlightAlpha;
		//斜角的加亮颜色。 BevelFilter
		uint highlightColor;
		//应用挖空效果 (true)，这将有效地使对象的填色变为透明，并显示文档的背景颜色。 BevelFilter
		Boolean knockout;
		//应用滤镜的次数。 BevelFilter
		int quality;
		//阴影颜色的 Alpha 透明度值。 BevelFilter
		Number shadowAlpha;
		//斜角的阴影颜色。 BevelFilter
		uint shadowColor;
		//印记或跨页的强度。 BevelFilter
		Number strength;
		//斜角在对象上的位置。 BevelFilter
		String type;
		//用指定参数初始化新的 BevelFilter 实例。 BevelFilter

	};
}
