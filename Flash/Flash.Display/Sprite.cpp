#pragma once
#include "StdAfx.h"
#include "DisplayObjectContainer.h"
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

/*Sprite 类是基本显示列表构造块：一个可显示图形并且也可包含子项的显示列表节点。 
Sprite 对象与影片剪辑类似，但没有时间轴。Sprite 是不需要时间轴的对象的相应基类。
例如，Sprite 将是通常不使用时间轴的用户界面 (UI) 组件的逻辑基类。
Sprite 类是 ActionScript 3.0 中新引入的类。它提供了 MovieClip 类功能的替代功能，
此替代功能保留了 ActionScript 以前版本的所有功能以提供向后兼容性。*/


	class	Sprite : public  DisplayObjectContainer
	{
	public:
		//创建一个新的 Sprite 实例。 Sprite
		Sprite( );
		//允许用户拖动指定的 Sprite。 Sprite
		void    startDrag(Boolean  lockCenter= false,Rectangle   bounds= null);
		//结束 startDrag() 方法。 Sprite
		void    stopDrag( );
		//指定此 sprite 的按钮模式。 Sprite
	private:
		Boolean buttonMode;
		//[只读] 指定拖动 sprite 时经过的显示对象，或放置 sprite 的显示对象。 Sprite
		DisplayObject dropTarget;
		//[只读] 指定属于此 sprite 的 Graphics 对象，在此 sprite 中可执行矢量绘画命令。 Sprite
		Graphics graphics;
		//指定一个 sprite 用作另一个 sprite 的点击区域。 Sprite
		Sprite hitArea;
		//控制此 sprite 中的声音。 Sprite
		flash.media:SoundTransform soundTransform;
		//布尔值，指示当鼠标滑过其 buttonMode 属性设置为 true 的 sprite 时是否显示手指形（手形光标）。 Sprite
		Boolean useHandCursor;
	};
}