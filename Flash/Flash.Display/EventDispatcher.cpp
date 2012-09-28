#pragma once
#include "StdAfx.h"
#include "Object.h"
#include "BitmapData.h"
#include <vector>
#include <string>
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
	//DisplayObject 类是可放在显示列表中的所有对象的基类。
	//该显示列表管理在Flash Player 或 Adobe AIR 中显示的所有对象。
	//使用 DisplayObjectContainer 类排列显示列表中的显示对象。
	//DisplayObjectContainer 对象可以有子显示对象，而其他显示对象（如 Shape 和 TextField 对象）是“叶”节点，
	//只有父级和同级，没有子级。
	//DisplayObject 类支持基本功能（如对象的 x 和 y 位置），也支持更高级的对象属性（如它的转换矩阵）。
	//DisplayObject 是一种抽象基类；因此，不能直接调用DisplayObject。调用 new DisplayObject() 会引发 ArgumentError 异常。
	//所有显示对象都继承自 DisplayObject 类。
	class	EventDispatcher: public Object
	{
	private:
		//聚合 EventDispatcher 类的实例。 EventDispatcher
		EventDispatcher(IEventDispatcher  target= null);
		//使用 EventDispatcher 对象注册事件侦听器对象，以使侦听器能够接收事件通知。 EventDispatcher
		void    addEventListener(String type,Function  listener,Boolean   useCapture= false,int   priority= 0,Boolean   useWeakReference= false);
		//将事件分派到事件流中。 EventDispatcher
		Boolean    dispatchEvent(Event event);
		//检查 EventDispatcher 对象是否为特定事件类型注册了任何侦听器。 EventDispatcher
		Boolean    hasEventListener(String type);
		//从 EventDispatcher 对象中删除侦听器。 EventDispatcher
		void    removeEventListener(String type,Function  listener,Boolean   useCapture= false);
		//检查是否用此 EventDispatcher 对象或其任何始祖为指定事件类型注册了事件侦听器。 EventDispatcher
		Boolean    willTrigger(String type);

	};
}