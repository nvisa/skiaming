#pragma once
#include "StdAfx.h"
#include "Object.h"
#include "AccessibilityProperties.h"
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
	class	DisplayObject: public EventDispatcher
	{
	private:
		AccessibilityProperties accessibilityProperties;	//此显示对象的当前辅助功能选项。 DisplayObject
		Number alpha;		//指示指定对象的 Alpha 透明度值。 DisplayObject 
		String blendMode;	//BlendMode 类中的一个值，用于指定要使用的混合模式。 DisplayObject 
		Shader blendShader;		 //[只写] 设置用于混合前景和背景的着色器。 DisplayObject 
		Boolean cacheAsBitmap;	//如果设置为 true，则 Flash Player 或 Adobe AIR 将缓存显示对象的内部位图表示形式。 DisplayObject 
		Array filters;		//包含当前与显示对象关联的每个滤镜对象的索引数组。 DisplayObject 
		Number height;	//指示显示对象的高度，以像素为单位。 DisplayObject 
		LoaderInfo loaderInfo;	//[只读] 返回一个 LoaderInfo 对象，其中包含加载此显示对象所属的文件的相关信息。 DisplayObject 
		DisplayObject mask;		//调用显示对象被指定的 mask 对象遮罩。 DisplayObject 
		Number mouseX;		//[只读] 指示鼠标位置的 x 坐标，以像素为单位。 DisplayObject 
		Number mouseY;		//[只读] 指示鼠标位置的 y 坐标，以像素为单位。 DisplayObject 
		String name;			//指示 DisplayObject 的实例名称。 DisplayObject 
		Object opaqueBackground;	//指定显示对象是否由于具有某种背景颜色而不透明。 DisplayObject 
		DisplayObjectContainer parent;		//[只读] 指示包含此显示对象的 DisplayObjectContainer 对象。 DisplayObject 
		DisplayObject root;	//[只读] 对于加载的 SWF 文件中的显示对象，root 属性是此 SWF 文件所表示的显示列表树结构部分中的顶级显示对象。 DisplayObject 
		Number rotation;		//指示 DisplayObject 实例距其原始方向的旋转程度，以度为单位。 DisplayObject 
		Number rotationX;	//指示 DisplayObject 实例相对于 3D 父容器距离其原始方向的 x 轴旋转（以度为单位）。 DisplayObject 
		Number rotationY;	//指示 DisplayObject 实例相对于 3D 父容器距离其原始方向的 y 轴旋转（以度为单位）。 DisplayObject 
		Number rotationZ;	//指示 DisplayObject 实例相对于 3D 父容器距离其原始方向的 z 轴旋转（以度为单位）。 DisplayObject 
		Rectangle scale9Grid;	//当前有效的缩放网格。 DisplayObject 
		Number scaleX;		//指示从注册点开始应用的对象的水平缩放比例（百分比）。 DisplayObject 
		Number scaleY;		//指示从对象注册点开始应用的对象的垂直缩放比例（百分比）。 DisplayObject 
		Number scaleZ;	//指示从对象的注册点开始应用的对象的深度缩放比例（百分比）。 DisplayObject 
		Rectangle scrollRect;		//显示对象的滚动矩形范围。 DisplayObject 
		Stage stage;		//[只读] 显示对象的舞台。 DisplayObject 
		Transform transform;	//一个对象，具有与显示对象的矩阵、颜色转换和像素范围有关的属性。 DisplayObject 
		Boolean visible;			//显示对象是否可见。 DisplayObject 
		Number width;		//指示显示对象的宽度，以像素为单位。 DisplayObject 
		Number x;		//指示 DisplayObject 实例相对于父级 DisplayObjectContainer 本地坐标的 x 坐标。 DisplayObject 
		Number y;		//指示 DisplayObject 实例相对于父级 DisplayObjectContainer 本地坐标的 y 坐标。 DisplayObject 
		Number z;			//指示 DisplayObject 实例相对于 3D 父容器沿 z 轴的 z 坐标位置。 
	};
}