#pragma once
#include "StdAfx.h"
#include "Object.h"
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
	/*Matrix 类表示一个转换矩阵，它确定如何将点从一个坐标空间映射到另一个坐标空间。
	您可以对一个显示对象执行不同的图形转换，方法是设置 Matrix 对象的属性，
	将该 Matrix 对象应用于 Transform 对象的 matrix 属性，然后应用该 Transform 对象作为显示对象的 transform 属性。
	这些转换函数包括平移（x 和 y 重新定位）、旋转、缩放和倾斜。 */

	class	Matrix: public Object	//OK
	{
	public:
		//使用指定参数创建新的 Matrix 对象。 Matrix
		Matrix(Number  a= 1,Number   b= 0,Number   c= 0,Number   d= 1,Number   tx= 0,Number   ty= 0);
		//返回一个新的 Matrix 对象，它是此矩阵的克隆，带有与所含对象完全相同的副本。 Matrix
		Matrix    clone( );
		//将某个矩阵与当前矩阵连接，从而将这两个矩阵的几何效果有效地结合在一起。 Matrix
		void    concat(Matrix m);
		//包括用于缩放、旋转和转换的参数。 Matrix
		void    createBox(Number scaleX,Number  scaleY,Number   rotation= 0,Number   tx= 0,Number   ty= 0);
		//创建 Graphics 类的 beginGradientFill() 和 lineGradientStyle() 方法所需的矩阵的特定样式。 Matrix
		void    createGradientBox(Number width,Number  height,Number   rotation= 0,Number   tx= 0,Number   ty= 0);
		//如果给定预转换坐标空间中的点，则此方法返回发生转换后该点的坐标。 Matrix
		Point    deltaTransformPoint(Point point);
		//为每个矩阵属性设置一个值，该值将导致 null 转换。 Matrix
		void    identity( );
		//执行原始矩阵的逆转换。 Matrix
		void    invert( );
		//对 Matrix 对象应用旋转转换。 Matrix
		void    rotate(Number angle);
		//对矩阵应用缩放转换。 Matrix
		void    scale(Number sx,Number  sy);
		//返回列出该 Matrix 对象属性的文本值。 Matrix
		String    toString( );
		//返回将 Matrix 对象表示的几何转换应用于指定点所产生的结果。 Matrix
		Point    transformPoint(Point point);
		//沿 x 和 y 轴平移矩阵，由 dx 和 dy 参数指定。 Matrix
		void    translate(Number dx,Number  dy);
	private:
		//缩放或旋转图像时影响像素沿 x 轴定位的值。 Matrix
		Number a;
		//旋转或倾斜图像时影响像素沿 y 轴定位的值。 Matrix
		Number b;
		//旋转或倾斜图像时影响像素沿 x 轴定位的值。 Matrix
		Number c;
		//缩放或旋转图像时影响像素沿 y 轴定位的值。 Matrix
		Number d;
		//沿 x 轴平移每个点的距离。 Matrix
		Number tx;
		//沿 y 轴平移每个点的距离。 Matrix
		Number ty;

	};
}