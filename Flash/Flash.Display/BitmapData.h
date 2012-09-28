#pragma once
#include "StdAfx.h"
#include "Object.h"
#include "Rectangle.h"
#include <vector>
#include <string>
#include "SKBitmap.h"
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

/*使用 BitmapData 类可以处理 Bitmap 对象的位图图像的数据（像素）。可以使用 BitmapData 类的方法创建任意大小的透明或不透明
位图图像，并在运行时采用多种方式操作这些图像。也可以访问使用 flash.display.Loader 类加载的位图图像的 BitmapData。 
此类允许您将位图呈现操作与 Flash Player 的内部显示更新例程分隔开来。通过直接操作 BitmapData 对象，
您可以创建复杂的图像，不会因连续重新绘制矢量数据的内容而产生每帧开销。
BitmapData 类的方法支持通过可用于非位图显示对象的滤镜无法得到的效果。
BitmapData 对象包含像素数据的数组。此数据可以表示完全不透明的位图，或表示包含 Alpha 通道数据的透明位图。
以上任一类型的 BitmapData 对象都作为 32 位整数的缓冲区进行存储。每个 32 位整数确定位图中单个像素的属性。
每个 32 位整数都是四个 8 位通道值（从 0 到 255）的组合，这些值描述像素的 Alpha 透明度以及红色、绿色、蓝色 (ARGB) 值。
（对于 ARGB 值，最高有效字节代表 Alpha 通道值，其后的有效字节分别代表红色、绿色和蓝色通道值。）
将这四个通道（Alpha、红色、绿色和蓝色）与 BitmapData.copyChannel() 方法或 
DisplacementMapFilter.componentX 及 DisplacementMapFilter.componentY 属性一起使用时，
这些通道以数字形式表示，并且这些数字在 BitmapDataChannel 类中由以下常量表示：
BitmapDataChannel.ALPHA 
BitmapDataChannel.RED 
BitmapDataChannel.GREEN 
BitmapDataChannel.BLUE 
通过使用 Bitmap 对象的 bitmapData 属性，可以将 BitmapData 对象附加到 Bitmap 对象。
可以使用 Graphics.beginBitmapFill() 方法用 BitmapData 对象填充 Graphics 对象。
如果 BitmapData 对象无效（例如，如果它的 height == 0 且 width == 0），或者已通过 dispose() 处理了该对象，
则对 BitmapData 对象的任何方法或属性的调用都会引发 ArgumentError 错误。 */
	class	BitmapData: public Object
	{
	private:
		SkBitmap m_pBitmap;
	public:
		/*创建一个具有指定的宽度和高度的 BitmapData 对象。如果为 fillColor 参数指定一个值，则位图中的每个像素都将
		设置为该颜色。 
		默认情况下，将位图创建为透明位图，除非您为 transparent 参数传递值 false。创建了不透明位图后，
		将无法将其更改为透明位图。不透明位图中的每个像素仅使用 24 位的颜色通道信息。如果将位图定义为透明，
		则每个像素将使用 32 位的颜色通道信息，其中包括 Alpha 透明度通道。*/
		// width:int — 位图图像的宽度，以像素为单位。  
		// height:int — 位图图像的高度，以像素为单位。  
		// transparent:Boolean (default = true) — 指定位图图像是否支持每个像素具有不同的透明度。默认值为 true（透明）。
		// 要创建完全透明的位图，请将 transparent 参数的值设置为 true，将 fillColor 参数的值设置为 0x00000000（或设置为 0）。
		// 将 transparent 属性设置为 false 可以略微提升呈现性能。  
		// fillColor:uint (default = 0xFFFFFFFF) — 用于填充位图图像区域的 32 位 ARGB 颜色值。默认值为 0xFFFFFFFF（纯白色）。
		BitmapData(int width,int  height,bool transparent= true, unsigned int fillColor= 0xFFFFFFFF);

		/*取得一个源图像和一个滤镜对象，并生成过滤的图像;
		此方法依赖于内置滤镜对象的行为，这些对象确定受输入源矩形影响的目标矩形。;
		应用滤镜后，结果图像可能会大于输入图像。;
		如果 sourceBitmapData 参数的 sourceRect 参数是内部区域,则滤镜会使用 sourceRect 参数外部的源像素来生成目标矩形。;
		如果 BitmapData 对象和指定为 sourceBitmapData 参数的对象是同一对象，应用程序将使用该对象的临时副本来执行滤镜。;
		为了获得最佳性能，请避免这种情况。*/
		// sourceBitmapData:要使用的输入位图图像。源图像可以是另一个 BitmapData 对象，也可以引用当前 BitmapData 实例;
		// sourceRect:Rectangle — 定义要用作输入的源图像区域的矩形;
		// destPoint:Point — 目标图像（当前 BitmapData 实例）中与源矩形的左上角对应的点;
		// filter:BitmapFilter — 用于执行过滤操作的滤镜对象。每种滤镜都有某些要求，如下所示： 
		// BlurFilter — 此滤镜可使用不透明或透明的源图像和目标图像。如果这两种图像的格式不匹配;
		// 则在过滤过程中生成的源图像副本将与目标图像的格式匹配。 
		// BevelFilter、DropShadowFilter、GlowFilter、ChromeFilter — 这些滤镜的目标图像必须是透明图像。
		// 调用 DropShadowFilter 或 GlowFilter 会创建包含投影或发光的 Alpha 通道数据的图像。
		// 它不会在目标图像上创建投影。如果将这些滤镜中的任何滤镜用于不透明的目标图像，将会引发异常。 
		// ConvolutionFilter — 此滤镜可使用不透明或透明的源图像和目标图像;
		// ColorMatrixFilter — 此滤镜可使用不透明或透明的源图像和目标图像。 
		// DisplacementMapFilter — 此滤镜可使用不透明或透明的源图像和目标图像，但源图像和目标图像的格式必须相同。
		void    applyFilter(BitmapData sourceBitmapData,Rectangle  sourceRect,Point  destPoint,BitmapFilter  filter);

		//返回一个新的 BitmapData 对象，它是对原始实例的克隆，包含与原始实例所含位图完全相同的副本。 BitmapData
		BitmapData clone();
		//使用 ColorTransform 对象调整位图图像的指定区域中的颜色值。 BitmapData
		void    colorTransform(Rectangle rect,flash.geom:ColorTransform  colorTransform);
		//比较两个 BitmapData 对象。 BitmapData
		Object    compare(BitmapData otherBitmapData);
		//将数据从另一个 BitmapData 对象或当前 BitmapData 对象的一个通道传输到当前 BitmapData 对象的某个通道中。 BitmapData
		void    copyChannel(BitmapData sourceBitmapData,Rectangle  sourceRect,Point  destPoint,uint  sourceChannel,uint  destChannel);
		//为没有拉伸、旋转或色彩效果的图像之间的像素处理提供一个快速例程。 BitmapData
		void    copyPixels(BitmapData sourceBitmapData,Rectangle  sourceRect,Point  destPoint,BitmapData   alphaBitmapData= null,Point   alphaPoint= null,Boolean   mergeAlpha= false);
		//释放用来存储 BitmapData 对象的内存。 BitmapData
		void    dispose( );
		//使用 Flash Player 或 AIR 矢量渲染器在位图图像上绘制 source 显示对象。 BitmapData
		void    draw(IBitmapDrawable source,Matrix   matrix= null,flash.geom:ColorTransform   colorTransform= null,String   blendMode= null,Rectangle   clipRect= null,Boolean   smoothing= false);
		//使用指定的 ARGB 颜色填充一个矩形像素区域。 BitmapData
		void    fillRect(Rectangle rect,uint  color);
		//对图像执行倾倒填充操作，从 (x, y) 坐标开始，填充一种特定的颜色。 BitmapData
		void    floodFill(int x,int  y,uint  color);
		//已知 BitmapData 对象、源矩形和滤镜对象，确定 applyFilter() 方法调用所影响的目标矩形。 BitmapData
		Rectangle    generateFilterRect(Rectangle sourceRect,BitmapFilter  filter);
		//确定矩形区域是将位图图像中指定颜色的所有像素完全包括起来（如果将 findColor 参数设置为 true），还是将不包括指定颜色的所有像素完全包括起来（如果将 findColor 参数设置为 false）。 BitmapData
		Rectangle    getColorBoundsRect(uint mask,uint  color,Boolean   findColor= true);
		//返回一个整数，它表示 BitmapData 对象中在特定点 (x, y) 处的 RGB 像素值。 BitmapData
		uint    getPixel(int x,int  y);
		//返回一个 ARGB 颜色值，它包含 Alpha 通道数据和 RGB 数据。 BitmapData
		uint    getPixel32(int x,int  y);
		//从像素数据的矩形区域生成一个字节数组。 BitmapData
		ByteArray    getPixels(Rectangle rect);
		//从像素数据的矩形区域生成一个矢量数组。 BitmapData
		vector<uint>    getVector(Rectangle rect);
		//计算 BitmapData 对象的 256 值二进制数直方图。 BitmapData
		vector<vector<Number>>    histogram(Rectangle  hRect= null);
		//在一个位图图像与一个点、矩形或其他位图图像之间执行像素级的点击检测。 BitmapData
		Boolean    hitTest(Point firstPoint,uint  firstAlphaThreshold,Object  secondObject,Point   secondBitmapDataPoint= null,uint   secondAlphaThreshold= 1);
		//锁定图像，以使引用 BitmapData 对象的任何对象（如 Bitmap 对象）在此 BitmapData 对象更改时不会更新。 BitmapData
		void    lock( );
		//对每个通道执行从源图像向目标图像的混合。 BitmapData
		void    merge(BitmapData sourceBitmapData,Rectangle  sourceRect,Point  destPoint,uint  redMultiplier,uint  greenMultiplier,uint  blueMultiplier,uint  alphaMultiplier);
		//使用表示随机杂点的像素填充图像。 BitmapData
		void    noise(int randomSeed,uint   low= 0,uint   high= 255,uint   channelOptions= 7,Boolean   grayScale= false);
		//重新映射一个具有最多四组调色板数据（每个通道一组）的图像中的颜色通道值。 BitmapData
		void    paletteMap(BitmapData sourceBitmapData,Rectangle  sourceRect,Point  destPoint,Array   redArray= null,Array   greenArray= null,Array   blueArray= null,Array   alphaArray= null);
		//生成 Perlin 杂点图像。 BitmapData
		void    perlinNoise(Number baseX,Number  baseY,uint  numOctaves,int  randomSeed,Boolean  stitch,Boolean  fractalNoise,uint   channelOptions= 7,Boolean   grayScale= false,Array   offsets= null);
		//执行源图像到目标图像的像素溶解，或使用同一图像执行像素溶解。 BitmapData
		int    pixelDissolve(BitmapData sourceBitmapData,Rectangle  sourceRect,Point  destPoint,int   randomSeed= 0,int   numPixels= 0,uint   fillColor= 0);
		//按某一 (x, y) 像素量滚动图像。 BitmapData
		void    scroll(int x,int  y);
		//设置 BitmapData 对象的单个像素。 BitmapData
		void    setPixel(int x,int  y,uint  color);
		//设置 BitmapData 对象单个像素的颜色和 Alpha 透明度值。 BitmapData
		void    setPixel32(int x,int  y,uint  color);
		//将字节数组转换为像素数据的矩形区域。 BitmapData
		void    setPixels(Rectangle rect,ByteArray  inputByteArray);
		//将 Vector 转换为像素数据的矩形区域。 BitmapData
		void    setVector(Rectangle rect,vector<uint>  inputVector);
		//根据指定的阈值测试图像中的像素值，并将通过测试的像素设置为新的颜色值。 BitmapData
		uint threshold(BitmapData sourceBitmapData,Rectangle  sourceRect,Point  destPoint,String  operation,uint  threshold,uint   color= 0,uint   mask= 0xFFFFFFFF,Boolean   copySource= false);
		//解除锁定图像，以使引用 BitmapData 对象的任何对象（如 Bitmap 对象）在此 BitmapData 对象更改时更新。 BitmapData
		void    unlock(Rectangle  changeRect= null);
	private:
		//[只读] 位图图像的高度，以像素为单位。 BitmapData
		int height;
		//[只读] 定义位图图像大小和位置的矩形。矩形的顶部和左侧为零；宽度和高度等于 BitmapData 对象的宽度和高度(以像素为单位) BitmapData
		Rectangle rect;
		//[只读] 定义位图图像是否支持每个像素具有不同的透明度.只有当通过为构造函数的 transparent 参数传入 true 来构造 BitmapData 对象时，才能设置此值 BitmapData
		Boolean transparent;
		//[只读] 位图图像的宽度，以像素为单位。 BitmapData
		int width;
	};
}