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

/*
一组绘图命令及这些命令的坐标参数。 
将 GraphicsPath 对象与 Graphics.drawGraphicsData() 方法一起使用。
绘制 GraphicsPath 对象与调用 Graphics.drawPath() 方法是等效的。 
GraphicsPath 还具有一组自己的方法（curveTo()、lineTo()、moveTo()、wideLineTo() 
和 wideMoveTo()），这些方法与 Graphics 类中用于调整 GraphicsPath.commands 
和 GraphicsPath.data 矢量数组的方法类似。*/


	class	GraphicsPath : public Object		//OK
	{
	public:
		//创建新的 GraphicsPath 对象。 GraphicsPath
		GraphicsPath(vector<int>  commands= null,vector<Number>   data= null,String   winding= "evenOdd");
		//将新的“curveTo”命令添加到 commands 矢量，并将新坐标添加到 data 矢量。 GraphicsPath
		void    curveTo(Number controlX,Number  controlY,Number  anchorX,Number  anchorY);
		//将新的“lineTo”命令添加到 commands 矢量，并将新坐标添加到 data 矢量。 GraphicsPath
		void    lineTo(Number x,Number  y);
		//将新的“moveTo”命令添加到 commands 矢量，并将新坐标添加到 data 矢量。 GraphicsPath
		void    moveTo(Number x,Number  y);
		//将新的“wideLineTo”命令添加到 commands 矢量，并将新坐标添加到 data 矢量。 GraphicsPath
		void    wideLineTo(Number x,Number  y);
		//将新的“wideMoveTo”命令添加到 commands 矢量，并将新坐标添加到 data 矢量。 GraphicsPath
		void    wideMoveTo(Number x,Number  y);
	private:
		//由绘画命令构成的矢量，其中的整数表示路径。 GraphicsPath
		vector<int> commands;
		//由数字构成的矢量，其中包含与绘图命令一起使用的参数。 GraphicsPath
		vector<Number> data;
		//使用 GraphicsPathWinding 类中定义的值指定缠绕规则。 GraphicsPath
		String winding;

	};
}