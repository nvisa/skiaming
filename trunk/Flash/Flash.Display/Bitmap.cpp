#include "Bitmap.h"
#include "BitmapData.h"
#include "SkBitmap.h"
Bitmap::Bitmap(const BitmapData& bitmapData, LX_String sPixelSnapping, LX_BOOL bSmoothing)
	:m_sPixelSnapping(sPixelSnapping),
	m_bSmoothing(bSmoothing)
{
	m_pBitmap = new SkBitmap();
}
