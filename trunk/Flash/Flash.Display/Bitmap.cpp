#include "Bitmap.h"
#include "BitmapData.h"
Bitmap::Bitmap(BitmapData bitmapData, String pixelSnapping= "auto", Boolean smoothing= false)
{
	m_pBitmap = new SkBitmap();

}
