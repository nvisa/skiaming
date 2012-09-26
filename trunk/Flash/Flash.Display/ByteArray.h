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

	class	ByteArray: public Object
	{
	public:
		ByteArray();	//创建一个表示填充的字节数组的 ByteArray 实例，以便使用此类中的方法和属性来优化数据存储和数据流
	private:
		uint bytesAvailable;	//[只读] 可从字节数组的当前位置到数组末尾读取的数据的字节数。 ByteArray 
		uint defaultObjectEncoding;		//[静态] 指示用于新 ByteArray 实例的 ByteArray 类的默认对象编码。 ByteArray 
		String endian;	//更改或读取数据的字节顺序；Endian.BIG_ENDIAN 或 Endian.LITTLE_ENDIAN。 ByteArray 
		uint length;	//ByteArray 对象的长度（以字节为单位）。 ByteArray 
		uint objectEncoding;		//用于确定在写入或读取 ByteArray 实例时应使用 ActionScript 3.0、ActionScript 2.0 还是 ActionScript 1.0 格式。 ByteArray 
		uint position;	//将文件指针的当前位置（以字节为单位）移动或返回到 ByteArray 对象中。 ByteArray 
	};
}