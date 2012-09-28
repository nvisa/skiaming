#pragma once
#include "StdAfx.h"
#include "Object.h"
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
	
	class    Scene: public Object
	{
			Array labels;	 //[只读] 一个由场景的 FrameLabel 对象组成的数组。 Scene 
			String name;	//[只读] 场景的名称。 Scene 
			int numFrames;		//[只读] 场景中的帧数。 Scene 
	};
}
