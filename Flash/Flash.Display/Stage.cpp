#pragma once
#include "StdAfx.h"

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
//Stage 类代表主绘图区。 
//对于在浏览器中（使用 Flash® Player）运行的 SWF 内容，Stage 表示显示 Flash 内容的整个区域。
//对于在 AIR 中运行的内容，每个 NativeWindow 对象都有一个相应的 Stage 对象。
//无法以全局方式访问 Stage 对象。而是需要利用 DisplayObject 实例的 stage 属性进行访问。
	class	Stage : public  DisplayObjectContainer
	{
	private:
		String align; //一个 StageAlign 类中指定舞台在 Flash Player 或浏览器中的对齐方式的值。 Stage 
		String colorCorrection;	//控制显示效果的 Flash Player 颜色校正。 Stage 
		String colorCorrectionSupport;	//[只读] 指定 Flash Player 当前所在的操作系统是否支持颜色校正，以及 Flash Player 是否能够读取和理解主监视器的颜色配置文件。 Stage 
		String displayState;	//用于指定要使用哪个显示状态的 StageDisplayState 类的值。 Stage 
		InteractiveObject focus;	//具有键盘焦点的交互式对象；如果没有设置焦点，或者具有焦点的对象属于调用对象无权访问的安全沙箱，则为 null。 Stage 
		Number frameRate;	//获取并设置舞台的帧速率。 Stage 
		uint fullScreenHeight;	//[只读] 返回变为全屏大小时使用的显示器高度（如果立即进入该状态）。 Stage 
		Rectangle fullScreenSourceRect;	//设置 Flash Player 以将特定的舞台区域放大到全屏模式。 Stage 
		uint fullScreenWidth;	//[只读] 返回变为全屏大小时使用的显示器宽度（如果立即进入该状态）。 Stage 
		Number height;	//[override] 指示显示对象的高度，以像素为单位。 Stage 
		Boolean mouseChildren;	//[override] 确定对象的子项是否支持鼠标。 Stage 
		NativeWindow nativeWindow;	//[只读] 对包含此舞台的 NativeWindow 对象的引用。 Stage 
		int numChildren;	//[override] [只读] 返回此对象的子项数目。 Stage 
		String quality;	//StageQuality 类中的一个用于指定使用哪种呈现品质的值。 Stage 
		String scaleMode;	//一个 StageScaleMode 类中指定要使用哪种缩放模式的值。 Stage 
		Boolean showDefaultContextMenu;	//指定显示或隐藏 Flash Player 上下文菜单中的默认项。 Stage 
		Boolean stageFocusRect;	//指定对象在具有焦点时是否显示加亮的边框。 Stage 
		int stageHeight;	//舞台的当前高度（以像素为单位）。 Stage 
		int stageWidth;	//指定舞台的当前宽度（以像素为单位）。 Stage 
		Boolean tabChildren;	//[override] 确定对象的子项是否支持 Tab 键。 Stage 
		TextSnapshot textSnapshot;	//[override] [只读] 返回此 DisplayObjectContainer 实例的 TextSnapshot 对象。 Stage 
		Number width;	//[override] 指示显示对象的宽度，以像素为单位。 Stage 
		Boolean wmodeGPU;	//[只读] 指示 GPU 合成是否可用及是否正在使用中。 Stage 
	};
}