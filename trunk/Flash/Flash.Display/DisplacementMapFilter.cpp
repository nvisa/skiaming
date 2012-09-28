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

/*DisplacementMapFilter 类使用指定的 BitmapData 对象（称为置换图图像）的像素值执行对象置换。
您可以使用此滤镜将扭曲或斑点效果应用于从 DisplayObject 类中继承的任何对象，例如 MovieClip、SimpleButton、
TextField 和 Video 对象，以及 BitmapData 对象。 
滤镜的具体使用取决于要应用滤镜的对象：
要将滤镜应用于显示对象，请使用显示对象的 filters 属性。设置对象的 filters 属性不会修改相应的对象，
而清除 filters 属性可以删除相应的滤镜。 
要对 BitmapData 对象应用滤镜，请使用 BitmapData.applyFilter() 方法。对 BitmapData 对象调用 applyFilter() 
会取得源 BitmapData 对象和滤镜对象，并生成一个过滤后的图像。 
如果对显示对象应用滤镜，则该显示对象的 cacheAsBitmap 属性值将设置为 true。
如果清除所有滤镜，将恢复 cacheAsBitmap 的原始值。
此滤镜使用以下公式：
dstPixel[x, y] = srcPixel[x + ((componentX(x, y) - 128) * scaleX) / 256, y + ((componentY(x, y) - 128) *scaleY) / 256)
其中，componentX(x, y) 从 mapBitmap 属性获得 (x - mapPoint.x ,y - mapPoint.y) 处的 componentX 属性颜色值。
滤镜使用的映射图像会进行缩放，以匹配舞台缩放比例。当对象自身呈一定的比例时，它不会进行缩放。
此滤镜支持舞台缩放。但不支持常规缩放、旋转和倾斜。如果对象本身进行了缩放（如果将 scaleX 和 scaleY 属性设置为
除 1.0 以外的其他值），滤镜效果将不进行缩放。只有用户在舞台上进行放大时它才会缩放。*/
	class    DisplacementMapFilter: public BitmapFilter
	{
	public:
		//用指定参数初始化 DisplacementMapFilter 实例。 DisplacementMapFilter
		DisplacementMapFilter(BitmapData  mapBitmap= null,Point   mapPoint= null,uint   componentX= 0,uint   componentY= 0,Number   scaleX= 0.0,Number   scaleY= 0.0,String   mode= "wrap",uint   color= 0,Number   alpha= 0.0);
		//[override] 返回此滤镜对象的副本。 DisplacementMapFilter
		BitmapFilter    clone( );
	private:
		//指定对于超出范围的替换应用的 Alpha 透明度值。 DisplacementMapFilter
		Number alpha;
		//指定对于超出范围的替换应用什么颜色。 DisplacementMapFilter
		uint color;
		//说明在映射图像中使用哪个颜色通道来置换 x 结果。 DisplacementMapFilter
		uint componentX;
		//说明在映射图像中使用哪个颜色通道来置换 y 结果。 DisplacementMapFilter
		uint componentY;
		//包含置换映射数据的 BitmapData 对象。 DisplacementMapFilter
		BitmapData mapBitmap;
		//一个值，它包含目标显示对象的左上角相对于映射图像左上角的偏移量。 DisplacementMapFilter
		Point mapPoint;
		//滤镜模式。 DisplacementMapFilter
		String mode;
		//用于缩放映射计算的 x 置换结果的乘数。 DisplacementMapFilter
		Number scaleX;
		//用于缩放映射计算的 y 置换结果的乘数。 DisplacementMapFilter
		Number scaleY;

	};
}
