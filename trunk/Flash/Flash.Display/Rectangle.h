#pragma once
#include "splght.h"
#include <vector>
#include <string>
namespace splght{
typedef struct
{
	LX_float x;
	LX_float y;
}Point, *PPOINT;
//Rectangle 对象是按其位置（由它左上角的点 (x, y) 确定）以及宽度和高度定义的区域。 
//Rectangle 类的 x、y、width 和 height 属性相互独立；更改一个属性的值不会影响其他属性。
//但是，right 和 bottom 属性与这四个属性是整体相关的。例如，如果更改 right 属性的值，则 width 属性的值将发生变化；
//如果更改 bottom 属性，则 height 属性的值将发生变化。 

	class	Rectangle/*: public Object*/
	{
	public:
		//创建一个新 Rectangle 对象，其左上角由 x 和 y 参数指定，并具有指定的 width 和 height 参数。 Rectangle
		Rectangle(LX_float x= 0, LX_float y= 0, LX_float width= 0, LX_float height= 0);
		//返回一个新的 Rectangle 对象，其 x、y、width 和 height 属性的值与原始 Rectangle 对象的对应值相同。 Rectangle
		//Rectangle    clone( );
		//确定由此 Rectangle 对象定义的矩形区域内是否包含指定的点。 Rectangle
		//Boolean    contains(Number x,Number  y);
		//确定由此 Rectangle 对象定义的矩形区域内是否包含指定的点。 Rectangle
		//Boolean    containsPoint(Point point);
		//确定此 Rectangle 对象内是否包含由 rect 参数指定的 Rectangle 对象。 Rectangle
		//Boolean    containsRect(Rectangle rect);
		//确定在 toCompare 参数中指定的对象是否等于此 Rectangle 对象。 Rectangle
		//Boolean    equals(Rectangle toCompare);
		//按指定量增加 Rectangle 对象的大小（以像素为单位）。 Rectangle
		//void    inflate(Number dx,Number  dy);
		//增加 Rectangle 对象的大小。 Rectangle
		//void    inflatePoint(Point point);
		//如果在 toIntersect 参数中指定的 Rectangle 对象与此 Rectangle 对象相交，则返回交集区域作为 Rectangle 对象。 Rectangle
		//Rectangle    intersection(Rectangle toIntersect);
		//确定在 toIntersect 参数中指定的对象是否与此 Rectangle 对象相交。 Rectangle
		//Boolean    intersects(Rectangle toIntersect);
		//确定此 Rectangle 对象是否为空。 Rectangle
		//Boolean    isEmpty( );
		//按指定量调整 Rectangle 对象的位置（由其左上角确定）。 Rectangle
		//void    offset(Number dx,Number  dy);
		//将 Point 对象用作参数来调整 Rectangle 对象的位置。 Rectangle
		//void    offsetPoint(Point point);
		//将 Rectangle 对象的所有属性设置为 0。 Rectangle
		//void    setEmpty( );
		//生成并返回一个字符串，该字符串列出 Rectangle 对象的水平位置和垂直位置以及高度和宽度。 Rectangle
		//String    toString( );
		//通过填充两个矩形之间的水平和垂直空间，将这两个矩形组合在一起以创建一个新的 Rectangle 对象。 Rectangle
		//Rectangle GetUnion(Rectangle toUnion);
	private:
		//y 和 height 属性的和。 Rectangle
		//LX_float m_fBottom;
		//由 right 和 bottom 属性的值确定的 Rectangle 对象的右下角的位置。 Rectangle
		//Point m_bottomRight;
		//矩形的高度（以像素为单位）。 Rectangle
		LX_float m_fHeight;
		//矩形左上角的 x 坐标。 Rectangle
		//LX_float m_fLeft;
		//x 和 width 属性的和。 Rectangle
		//LX_float m_fRight;
		//Rectangle 对象的大小，该对象表示为具有 width 和 height 属性的值的 Point 对象。 Rectangle
		//Point size;
		//矩形左上角的 y 坐标。 Rectangle
		//LX_float top;
		//由该点的 x 和 y 坐标确定的 Rectangle 对象左上角的位置。 Rectangle
		//Point topLeft;
		//矩形的宽度（以像素为单位）。 Rectangle
		LX_float m_fWidth;
		//矩形左上角的 x 坐标。 Rectangle
		LX_float m_fX;
		//矩形左上角的 y 坐标。 Rectangle
		LX_float m_fY;
	
	};
}