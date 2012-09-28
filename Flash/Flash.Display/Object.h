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

	class	Object
	{
	public:
		Object();
		bool hasOwnProperty(char* name);
		bool  isPrototypeOf(Object theClass);
		bool propertyIsEnumerable(char* name);
		void setPropertyIsEnumerable(char*name, bool isEnum = true);
		char* toLocaleString();
		Object valueOf();
		virtual String Prototypename();
	private:
		Object constructor;	//对类对象或给定对象实例的构造函数的引用。 Object 
		Object prototype;		//[静态] 对类或函数对象的原型对象的引用。 Object

	};
}