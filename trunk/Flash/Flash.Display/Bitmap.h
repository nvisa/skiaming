#pragma once
#include "splght.h"
class BitmapData;
namespace splght{
//Bitmap 类表示用于表示位图图像的显示对象。这些图像可以是使用 flash.display.Loader 类加载的图像，
//也可以是使用 Bitmap() 构造函数创建的图像。
//利用 Bitmap() 构造函数，可以创建包含对 BitmapData 对象的引用的 Bitmap 对象。
//创建了 Bitmap 对象后，使用父 DisplayObjectContainer 实例的 addChild() 或 addChildAt() 方法将位图放在显示列表中。

	class	Bitmap/*: public DisplayObject*/	//OK
	{
	public:
		//初始化 Bitmap 对象以引用指定的 BitmapData 对象。 Bitmap
		Bitmap(const BitmapData& bitmapData, LX_String sPixelSnapping= "auto", LX_BOOL bSmoothing= false);
		~Bitmap();
	private:
		//被引用的 BitmapData 对象。 Bitmap
		BitmapData bitmapData;
		//控制 Bitmap 对象是否贴紧至最近的像素。 Bitmap
		LX_String m_sPixelSnapping;
		//控制在缩放时是否对位图进行平滑处理。 Bitmap
		LX_BOOL m_bSmoothing;
	};
}