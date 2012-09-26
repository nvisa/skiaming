#pragma once
#include "StdAfx.h"
#include "DisplayObject.h"
#include "InteractiveObject.h"
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

/*DisplayObjectContainer 类是可用作显示列表中显示对象容器的所有对象的基类。
该显示列表管理在 Flash Player 或 Adobe AIR 中显示的所有对象。
使用 DisplayObjectContainer 类排列显示列表中的显示对象。每个 DisplayObjectContainer 
对象都有自己的子级列表，用于组织对象的 Z 轴顺序。Z 轴顺序是由前至后的顺序，
可确定哪个对象绘制在前，哪个对象绘制在后等。 
DisplayObject 是一种抽象基类；因此，不能直接调用 DisplayObject。
调用 new DisplayObject() 会引发 ArgumentError 异常。
DisplayObjectContainer 类是可以包含子对象的所有对象的抽象基类。
无法直接对其进行实例化；调用 new DisplayObjectContainer() 构造函数
会引发 ArgumentError 异常。*/
	class	DisplayObjectContainer : public  InteractiveObject 
	{
	public:
		//调用新的 DisplayObjectContainer() 构造函数会引发 ArgumentError 异常。 DisplayObjectContainer
		DisplayObjectContainer( );
		//将一个 DisplayObject 子实例添加到该 DisplayObjectContainer 实例中。 DisplayObjectContainer
		DisplayObject    addChild(DisplayObject child);
		//将一个 DisplayObject 子实例添加到该 DisplayObjectContainer 实例中。 DisplayObjectContainer
		DisplayObject    addChildAt(DisplayObject child,int  index);
		//指示安全限制是否会导致出现以下情况：在列表中忽略了使用指定 point 点调用 DisplayObjectContainer.getObjectsUnderPoint() 方法时返回的所有显示对象。 DisplayObjectContainer
		Boolean    areInaccessibleObjectsUnderPoint(Point point);
		//确定指定显示对象是 DisplayObjectContainer 实例的子项还是该实例本身。 DisplayObjectContainer
		Boolean    contains(DisplayObject child);
		//返回位于指定索引处的子显示对象实例。 DisplayObjectContainer
		DisplayObject    getChildAt(int index);
		//返回具有指定名称的子显示对象。 DisplayObjectContainer
		DisplayObject    getChildByName(String name);
		//返回 DisplayObject 的 child 实例的索引位置。 DisplayObjectContainer
		int    getChildIndex(DisplayObject child);
		//返回对象的数组，这些对象位于指定点下，并且是该 DisplayObjectContainer 实例的子项（或孙子项，依此类推）。 DisplayObjectContainer
		Array    getObjectsUnderPoint(Point point);
		//从 DisplayObjectContainer 实例的子列表中删除指定的 child DisplayObject 实例。 DisplayObjectContainer
		DisplayObject    removeChild(DisplayObject child);
		//从 DisplayObjectContainer 的子列表中指定的 index 位置删除子 DisplayObject。 DisplayObjectContainer
		DisplayObject    removeChildAt(int index);
		//更改现有子项在显示对象容器中的位置。 DisplayObjectContainer
		void    setChildIndex(DisplayObject child,int  index);
		//交换两个指定子对象的 Z 轴顺序（从前到后顺序）。 DisplayObjectContainer
		void    swapChildren(DisplayObject child1,DisplayObject  child2);
		//在子级列表中两个指定的索引位置，交换子对象的 Z 轴顺序（前后顺序）。 DisplayObjectContainer
		void    swapChildrenAt(int index1,int  index2);
	private:
		//确定对象的子项是否支持鼠标。 DisplayObjectContainer
		Boolean mouseChildren;
		//[只读] 返回此对象的子项数目。 DisplayObjectContainer
		int numChildren;
		//确定对象的子项是否支持 Tab 键。 DisplayObjectContainer
		Boolean tabChildren;
		//[只读] 返回此 DisplayObjectContainer 实例的 TextSnapshot 对象。 DisplayObjectContainer
		flash.text:TextSnapshot textSnapshot;

	};
}