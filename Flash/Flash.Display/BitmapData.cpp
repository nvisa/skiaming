#include "BitmapData.h"
namespace splght{
BitmapData::BitmapData(LX_int width, LX_int  height, LX_BOOL transparent, LX_UINT fillColor)
	:m_iWidth(width),
	m_iHeight(height),
	m_bTransparent(transparent)
{
}
}