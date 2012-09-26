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

/*ShaderFilter 类通过对应用了滤镜的对象执行着色器来应用滤镜。应用了滤镜的对象将用作着色器输入，
而着色器输出将用作滤镜效果。 
要创建新的滤镜，请使用构造函数 new ShaderFilter()。滤镜的具体使用取决于要应用滤镜的对象：
要对影片剪辑、文本字段、按钮和视频应用滤镜，请使用 filters 属性（继承自 DisplayObject）。
设置对象的 filters 属性不会修改相应的对象，而清除 filters 属性可以删除相应的滤镜。 
要对 BitmapData 对象应用滤镜，请使用 BitmapData.applyFilter() 方法。对 BitmapData 对象调用 applyFilter() 会
取得源 BitmapData 对象和滤镜对象，并最终生成一个过滤图像。 
如果对显示对象应用滤镜，则该对象的 cacheAsBitmap 属性值将设置为 true。如果删除所有滤镜，
将恢复 cacheAsBitmap 的原始值。
此滤镜支持舞台缩放。但是，它不支持常规缩放、旋转和倾斜。如果对象本身进行了缩放（如果 scaleX 和 scaleY 属性
未被设置为 100%），则滤镜不进行缩放。只有用户在舞台上进行放大时它才会缩放。
如果所得图像超过最大尺寸，则不应用滤镜。
要指定将 Shader 实例用于滤镜，请将 Shader 实例作为参数传递到 ShaderFilter() 构造函数，或将其设置为 shader 属性的值。
要允许着色器输出超出已过滤对象的范围，请使用 leftExtension、rightExtension、topExtension 和 bottomExtension 属性。*/
	class ShaderFilter: public BitmapFilter
	{
	public:
		//创建新的着色器滤镜。 ShaderFilter
		ShaderFilter(Shader  shader= null);
	private:
		//目标对象底部的增大量（以像素为单位）。 ShaderFilter
		int bottomExtension;
		//目标对象左侧的增大量（以像素为单位）。 ShaderFilter
		int leftExtension;
		//目标对象右侧的增大量（以像素为单位）。 ShaderFilter
		int rightExtension;
		//要为此滤镜使用的着色器。 ShaderFilter
		Shader shader;
		//目标对象顶部的增大量（以像素为单位）。 ShaderFilter
		int topExtension;
	};
}
