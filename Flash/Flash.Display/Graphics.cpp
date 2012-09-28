#include "Graphics.h"
#include "SkCanvas.h"
Graphics::Graphics()
{
	m_pCanvas = new SkCanvas();
}
Graphics::~Graphics()
{
	if(m_pCanvas)
		delete m_pCanvas;
	m_pCanvas = NULL;
}
//用位图图像填充绘图区。
//bitmap:包含要显示的位的透明或不透明位图图像。 
//matrix: 一个 matrix 对象（属于 flash.geom.Matrix 类），您可以使用它在位图上定义转换。
//例如，可以使用以下矩阵将位图旋转 45 度（pi/4 弧度）： matrix = new flash.geom.Matrix();matrix.rotate(Math.PI / 4);
//repeat: 如果为 true，则位图图像按平铺模式重复。如果为 false，位图图像不会重复，
//并且位图边缘将用于所有扩展出位图的填充区域。
//当 repeat 设置为 true 时（如下例所示），位图填充将重复位图：
//repeat 设置为false 时，位图填充将对位图外部的填充区域使用边缘像素：
//smooth:如果为 false，则使用最近邻点算法来呈现放大的位图图像，而且该图像看起来是像素化的。
//如果为 true，则使用双线性算法来呈现放大的位图图像。使用最近邻点算法呈现较快。 
void beginBitmapFill(const BitmapData &bitmap, const Matrix &matrix = null, Boolean repeat = true, Boolean smooth = false)
{
	
}

/*指定一种简单的单一颜色填充，在绘制时该填充将在随后对其他Graphics 方法（如 lineTo() 或 drawCircle()）的调用中使用
该填充将保持有效，直到您调用 beginFill()、beginBitmapFill()、beginGradientFill() 或 beginShaderFill() 方法。
调用 clear() 方法会清除填充。
只要绘制 3 个或更多个点，或者调用 endFill() 方法时，应用程序就会呈现填充*/
//color:填充的颜色 (0xRRGGBB)。  
//alpha:填充的 Alpha 值（从 0.0 到 1.0）。  
void beginFill(const uint color, const Number alpha = 1.0);

/*指定一种渐变填充，用于随后调用对象的其他 Graphics 方法（如 lineTo() 或 drawCircle()）。
该填充将保持有效，直到您调用 beginFill()、beginBitmapFill()、beginGradientFill() 或 beginShaderFill() 方法。
调用 clear() 方法会清除填充。 
只要绘制 3 个或更多个点，或者调用 endFill() 方法时，应用程序就会呈现填充。*/
//type:用于指定要使用哪种渐变类型的 GradientType 类的值：GradientType.LINEAR 或 GradientType.RADIAL。  
//colors:渐变中使用的 RGB 十六进制颜色值的数组（例如，红色为 0xFF0000，蓝色为 0x0000FF，等等）。可以至多指定 15 种颜色。对于每种颜色，请在 alphas 和 ratios 参数中指定对应值。  
//alphas:colors 数组中对应颜色的 alpha 值数组；有效值为 0 到 1。如果值小于 0，则默认值为 0。如果值大于 1，则默认值为 1。  
//ratios:颜色分布比率的数组；有效值为 0 到 255。该值定义 100% 采样的颜色所在位置的宽度百分比。值 0 表示渐变框中的左侧位置，255 表示渐变框中的右侧位置。  
//matrix: 一个由 flash.geom.Matrix 类定义的转换矩阵。flash.geom.Matrix 类包括 createGradientBox() 方法，
//通过该方法可以方便地设置矩阵，以便与 beginGradientFill() 方法一起使用。  
//spreadMethod:用于指定要使用哪种 spread 方法的 SpreadMethod 类的值：
//SpreadMethod.PAD、SpreadMethod.REFLECT 或 SpreadMethod.REPEAT。  
//interpolationMethod:String (default = "rgb") — 用于指定要使用哪个值的 InterpolationMethod 类的值：
//InterpolationMethod.LINEAR_RGB 或 InterpolationMethod.RGB 
//focalPointRatio:一个控制渐变的焦点位置的数字。0 表示焦点位于中心。1 表示焦点位于渐变圆的一条边界上。
//-1 表示焦点位于渐变圆的另一条边界上。小于 -1 或大于 1 的值将舍入为 -1 或 1。 
void beginGradientFill(const String type, const vector<long> &colors, const vector<double> &alphas, const vector<short> &ratios, const Matrix matrix = null, 
	const String &spreadMethod = "pad", const String &interpolationMethod = "rgb", Number focalPointRatio = 0);

/*为对象指定着色器填充，供随后调用其他 Graphics 方法（如 lineTo() 或 drawCircle()）时使用。
该填充将保持有效，直到您调用 beginFill()、beginBitmapFill()、beginGradientFill() 或 beginShaderFill() 方法。
调用 clear() 方法会清除填充。 
只要绘制 3 个或更多个点，或者调用 endFill() 方法时，应用程序就会呈现填充。*/
//shader:要用于填充的着色器。此 Shader 实例无需指定图像输入。但是，如果在着色器中指定图像输入，则必须手动提供输入。
//要指定输入，请设置 Shader.data 属性的对应 ShaderInput 属性的 input 属性。 
//传递 Shader 实例作为参数时，会在内部复制着色器。绘图填充操作将使用该内部副本，而不是对原始着色器的引用。
//对着色器进行的任何更改（比如更改参数值、输入或字节代码）不会应用于所复制的用于填充的着色器。
//matrix:一个 matrix 对象（属于 flash.geom.Matrix 类），可用于对着色器定义转换。
//例如，可以使用以下矩阵将着色器旋转 45 度（pi/4 弧度）: matrix = new flash.geom.Matrix(); matrix.rotate(Math.PI / 4);
//着色器中收到的坐标基于为 matrix 参数指定的矩阵。对于默认 (null) 矩阵，着色器中的坐标是可用于对输入采样的局部像素坐标。
void beginShaderFill(cosnt Shader &shader, cosnt Matrix &matrix = null);

//清除绘制到此 Graphics 对象的图形，并重置填充和线条样式设置。 
void clear();
		
//将源 Graphics 对象中的所有绘画命令复制到执行调用的 Graphics 对象中。 Graphics 
//sourceGraphics: 从中复制绘画命令的 Graphics 对象
void	copyFrom(const Graphics &sourceGraphics);	

/*通过由 (controlX, controlY) 指定的控制点,使用当前线条样式绘制一条从当前绘画位置开始到 (anchorX, anchorY) 结束的曲线。
当前绘画位置随后设置为 (anchorX, anchorY)。如果正在其中绘制的影片剪辑包含用 Flash 绘画工具创建的内容，
则调用 curveTo() 方法将在该内容下面进行绘制。如果在调用 moveTo() 方法之前调用了 curveTo() 方法，
则当前绘画位置的默认值为 (0, 0)。如果缺少任何一个参数，则此方法将失败，并且当前绘画位置不改变。 
绘制的曲线是二次贝塞尔曲线。二次贝塞尔曲线包含两个锚点和一个控制点。该曲线内插这两个锚点，并向控制点弯曲。 */
// controlX:一个数字，指定控制点相对于父显示对象注册点的水平位置。
// controlY:一个数字，指定控制点相对于父显示对象注册点的垂直位置。  
// anchorX:一个数字，指定下一个锚点相对于父显示对象注册点的水平位置。
// anchorY:一个数字，指定下一个锚点相对于父显示对象注册点的垂直位置。  
void	curveTo(Number controlX, Number controlY, Number anchorX, Number anchorY);

/*绘制一个圆。在调用 drawCircle() 方法之前，通过调用 linestyle()、lineGradientStyle()、beginFill()、
beginGradientFill() 或 beginBitmapFill() 方法来设置线条样式或/和填充。*/ 
// x:圆心相对于父显示对象注册点的 x 位置（以像素为单位）。  
// y:相对于父显示对象注册点的圆心的 y 位置（以像素为单位）。  
// radius:圆的半径（以像素为单位）。  
void	drawCircle(Number x, Number y, Number radius);
		
/*绘制一个椭圆。在调用 drawEllipse() 方法之前，通过调用 linestyle()、lineGradientStyle()、beginFill()、
beginGradientFill() 或 beginBitmapFill() 方法来设置线条样式或/和填充。*/
// x:Number — 椭圆边框左上角相对于父显示对象注册点的 x 位置（以像素为单位）。  
// y:Number — 椭圆边框左上角相对于父显示对象注册点的 y 位置（以像素为单位）。  
// width:Number — 椭圆的宽度（以像素为单位）。  
// height:Number — 椭圆的高度（以像素为单位）。  
void	drawEllipse(Number x, Number y, Number width, Number height);
		
/*提交一系列 IGraphicsData 实例来进行绘图。此方法接受一个包含对象（包括路径、填充和笔触）的矢量，
这些对象实现 IGraphicsData 接口。包含 IGraphicsData 实例的矢量可以引用形状的一部分，
或引用一组完整定义的复杂数据以呈现完整的形状。
图形路径可以包含其他图形路径。如果 graphicsData 矢量包括路径，则在此操作期间将呈现该路径及其所有子路径。 */
//graphicsData:一个包含图形对象的矢量，其中的每个对象都必须实现 IGraphicsData 接口
void	drawGraphicsData(const vector<IGraphicsData> &graphicsData);
		
/*提交一系列绘制命令。drawPath() 方法使用矢量数组来将各个 moveTo()、lineTo() 和 curveTo() 绘图命令并入到一个调用中。
drawPath() 方法参数将绘图命令与 x 和 y 坐标值对以及绘图方向合并起来。绘图命令为 GraphicsPathCommand 类中的值。
x 和 y 坐标值对是数组中的数字，其中的每对数字定义一个坐标位置。绘图方向为 GraphicsPathWinding 类中的值。 
通常，与使用一系列单个 lineTo() 和 curveTo() 方法相比，使用 drawPath() 呈现绘图的速度会更快。 
drawPath() 方法使用浮动计算，因此形状的旋转和缩放更准确，可以获得更好的结果。但是，
通过使用 drawPath() 方法提交的曲线在与 lineTo() 和 curveTo() 方法结合使用时，可能会存在小的子像素对齐误差。
drawPath() 方法还使用稍有不同的规则进行填充和绘制线条。这些规则是： 
在应用填充以呈现路径时： 不呈现少于 3 个点的子路径。（但请注意，笔触呈现仍将发生，并与下面的笔触规则相一致。） 
隐式闭合未闭合的子路径（结束点不等于开始点）。 
在应用笔触以呈现路径时： 子路径可以由任何数量的点组成。 	从不隐式闭合子路径。*/ 
//commands: 一个由整数构成的矢量，表示由 GraphicsPathCommand 类定义的命令。
//GraphicsPathCommand 类将命令映射到此矢量数组的数字标识符。  
//data:一个由数字构成的矢量，其中的每一对数字将被视为一个坐标位置（一个 x, y 对）。
//x 和 y 坐标值对不是 Point 对象；data 矢量是一系列数字，其中的每个由两个数字构成的组表示一个坐标位置。  
//winding:使用 GraphicsPathWinding 类中定义的值指定缠绕规则。  
void	drawPath(const vector<int> &commands, const vector<Number> &data, const String &winding = "evenOdd");
		
/*绘制一个矩形。在调用 drawRect() 方法之前，通过调用 linestyle()、lineGradientStyle()、beginFill()、
beginGradientFill() 或 beginBitmapFill() 方法来设置线条样式或/和填充。 */
//x:Number — 一个表示相对于父显示对象注册点的水平位置的数字（以像素为单位）。  
// y:Number — 一个表示相对于父显示对象注册点的垂直位置的数字（以像素为单位）。  
// width:Number — 矩形的宽度（以像素为单位）。  
// height:Number — 矩形的高度（以像素为单位）。  	
void	drawRect(Number x, Number y, Number width, Number height);
		
//绘制一个圆角矩形。在调用 drawRoundRect() 方法之前，通过调用 linestyle()、lineGradientStyle()、beginFill()、
//beginGradientFill() 或 beginBitmapFill() 方法来设置线条样式或/和填充。 
// x:Number — 一个表示相对于父显示对象注册点的水平位置的数字（以像素为单位）。
// y:Number — 一个表示相对于父显示对象注册点的垂直位置的数字（以像素为单位）。  
// width:Number — 圆角矩形的宽度（以像素为单位）。  
// height:Number — 圆角矩形的高度（以像素为单位）。  
// ellipseWidth:Number — 用于绘制圆角的椭圆的宽度（以像素为单位）。  
// ellipseHeight:Number (default = NaN) — 用于绘制圆角的椭圆的高度（以像素为单位）。
//（可选）如果未指定值，则默认值与为 ellipseWidth 参数提供的值相匹配。  
void drawRoundRect(Number x, Number y, Number width, Number height, 
Number ellipseWidth, Number ellipseHeight = NaN);
		
/*呈现一组三角形（通常用于扭曲位图），并为其指定三维外观。
drawTriangles() 方法使用一组 (u,v) 坐标将当前填充或位图填充映射到三角形面。 
可以使用任何类型的填充，但如果填充有转换矩阵，则将忽略该转换矩阵。 
在使用位图填充时，uvtData 参数可改善纹理映射。 */
// vertices:一个由数字构成的矢量，其中的每一对数字将被视为一个坐标位置（一个 x, y 对）。 vertices 参数是必需的。
// indices: 一个由整数或索引构成的矢量，其中每三个索引定义一个三角形。如果 indexes 参数为 null，
// 则每三个顶点（vertices 矢量中的 6 对 x,y）定义一个三角形。否则，每个索引将引用一个顶点，
// 即 vertices 矢量中的一对数字。例如，indexes[1] 引用 (vertices[2], vertices[3])。indexes 参数是可选的，
// 但 indexes 通常会减少提交的数据量和计算的数据量。  
// uvtData:由用于应用纹理映射的标准坐标构成的矢量。每个坐标引用用于填充的位图上的一个点。
// 每个顶点必须具有一个 UV 或一个 UVT 坐标。对于 UV 坐标，(0,0) 是位图的左上角，(1,1) 是位图的右下角。 
// 如果此矢量的长度是 vertices 矢量长度的两倍，则使用标准坐标而不进行透视校正。 
// 如果此矢量的长度是 vertices 矢量长度的三倍，则将第三个坐标解释为“t”（即在视角空间中从视点到纹理的距离）。
// 这有助于呈现引擎在三维中映射纹理时正确应用透视。
// 如果 uvtData 参数为 null，则将应用普通填充规则（和任何填充类型）。
// culling:指定是否呈现面向指定方向的三角形。此参数可防止呈现在当前视图中看不见的三角形。
// 此参数可设置为由 TriangleCulling 类定义的任何值。  
void drawTriangles(const vector<Number> &vertices, const vector<int> &indices = null, const vector<Number> &uvtData = null, 
const String &culling = "none");
		
/*对从上一次调用 beginFill()、beginGradientFill() 或 beginBitmapFill() 方法之后添加的直线和曲线应用填充。
Flash 使用的是对 beginFill()、beginGradientFill() 或 beginBitmapFill() 方法的先前调用中指定的填充。
如果当前绘画位置不等于 moveTo() 方法中指定的上一个位置，而且定义了填充，则用线条闭合该路径，然后进行填充。*/ 
void endFill();
		
/*指定一个位图，用于绘制线条时的线条笔触。 
位图线条样式将用于随后对 lineTo() 或 drawCircle() 等 Graphics 方法的调用。
线条样式仍然有效，直到您使用不同的参数调用 lineStyle() 或 lineGradientStyle() 方法或再次调用 lineBitmapStyle() 方法。 
可以在绘制路径的中间调用 lineBitmapStyle() 方法以为路径中的不同线段指定不同的样式。 
请在调用 lineBitmapStyle() 方法之前调用 lineStyle() 方法以启用笔触，否则线条样式的值将为 undefined。
调用 clear() 方法会将线条样式设置回 undefined。*/ 
//bitmap 用于线条笔触的位图。  
// matrix: 一个由 flash.geom.Matrix 类定义的可选转换矩阵。
//该矩阵可用于在将位图应用于线条样式之前缩放位图或以其他方式处理位图。 
// repeat: 是否以平铺方式重复位图。  
// smooth:是否应对位图应用平滑处理。   	
void	lineBitmapStyle(const BitmapData &bitmap, const Matrix *matrix = null, Boolean repeat = true, Boolean smooth = false);
		

/*指定一种渐变，用于绘制线条时的笔触。 
渐变线条样式将用于随后对 lineTo() 或 drawCircle() 等 Graphics 方法的调用。线条样式仍然有效，
直到您使用不同的参数调用 lineStyle() 或 lineBitmapStyle() 方法或再次调用 lineGradientStyle() 方法。 
可以在绘制路径的中间调用 lineGradientStyle() 方法以为路径中的不同线段指定不同的样式。 
请在调用 lineGradientStyle() 方法之前调用 lineStyle() 方法以启用笔触，否则线条样式的值将为 undefined。
调用 clear() 方法会将线条样式设置回 undefined。 */
// type:String — 用于指定要使用哪种渐变类型的 GradientType 类的值：GradientType.LINEAR 或 GradientType.RADIAL。  
// colors:Array — 要在渐变中使用的 RGB 十六进制颜色值数组（例如，红色为 0xFF0000，蓝色为 0x0000FF 等等）。  
// alphascolors 数组中对应颜色的 alpha 值数组;有效值为 0 到 1。如果值小于 0,则默认值为 0。如果值大于 1,则默认值为 1。  
// ratios:颜色分布比率的数组;有效值为 0 到 255。该值定义 100% 采样的颜色所在位置的宽度百分比。
// 值 0 表示渐变框中的左侧位置，255 表示渐变框中的右侧位置。此值表示渐变框中的位置，而不是最终渐变的坐标空间，
// 最终渐变可能会比渐变框更宽或更窄。为 colors 参数中的每个值指定一个值。  
// matrix:一个由 flash.geom.Matrix 类定义的转换矩阵。flash.geom.Matrix 类包括 createGradientBox() 方法，
// 通过该方法可以方便地设置矩阵，以便与 lineGradientStyle() 方法一起使用。  
// spreadMethod:String (default = "pad") — 用于指定要使用哪种 spread 方法的 SpreadMethod 类的值：  
// interpolationMethod:String (default = "rgb") — InterpolationMethod 类中用于指定要使用的值的值。
// focalPointRatio:Number (default = 0) — 一个控制渐变的焦点位置的数字。值 0 表示焦点位于中心。
// 值 1 表示焦点位于渐变圆的一条边界上。值 -1 表示焦点位于渐变圆的另一条边界上。小于 -1 或大于 1 的值将舍入为 -1 或 1。
void lineGradientStyle(const String &type, const Array &colors, Array alphas, Array ratios, const Matrix matrix = null, 
String spreadMethod = "pad", String interpolationMethod = "rgb", Number focalPointRatio = 0);
		

/*指定一个着色器以用于绘制线条时的线条笔触。 
着色器线条样式将用于随后对 lineTo() 或 drawCircle() 等 Graphics 方法的调用。线条样式仍然有效，
直到您使用不同的参数调用 lineStyle() 或 lineGradientStyle() 方法或再次调用 lineBitmapStyle() 方法。 
可以在绘制路径的中间调用 lineShaderStyle() 方法，以便为路径中的不同线段指定不同的样式。 
请在调用 lineShaderStyle() 方法之前调用 lineStyle() 方法以启用笔触，否则线条样式的值将为 undefined。
调用 clear() 方法会将线条样式设置回 undefined。*/ 
// shader:Shader — 用于线条笔触的着色器。  
// matrix:Matrix (default = null) — 一个由 flash.geom.Matrix 类定义的可选转换矩阵。
// 该矩阵可用于在将位图应用于线条样式之前缩放位图或以其他方式处理位图。  	
void	lineShaderStyle(Shader shader, Matrix matrix = null);
		

/*指定一种线条样式以用于随后对 lineTo() 或 drawCircle() 等 Graphics 方法的调用。
线条样式仍然有效，直到您使用不同的参数调用 lineGradientStyle() 方法、lineBitmapStyle() 方法或 lineStyle() 方法。 
可以在绘制路径的中间调用 lineStyle() 方法以为路径中的不同线段指定不同的样式。
注意：调用 clear() 方法会将线条样式设置回 undefined。*/
// thickness:一个整数，以磅为单位表示线条的粗细；有效值为 0 到 255。如果未指定数字，或者未定义该参数，则不绘制线条。
// 如果传递的值小于 0，则默认值为 0。值 0 表示极细的粗细；最大粗细为 255。如果传递的值大于 255，则默认值为 255。  
// color:uint (default = 0) — 线条的十六进制颜色值（例如，红色为 0xFF0000，蓝色为 0x0000FF 等）。
// 如果未指明值，则默认值为 0x000000（黑色）。可选。  
// alpha:Number (default = 1.0) — 表示线条颜色的 Alpha 值的数字；有效值为 0 到 1。如果未指明值，则默认值为 1（纯色）。
// 如果值小于 0，则默认值为 0。如果值大于 1，则默认值为 1。  
// pixelHinting:Boolean (default = false) — 用于指定是否提示笔触采用完整像素的布尔值。
// 它同时影响曲线锚点的位置以及线条笔触大小本身。在 pixelHinting 设置为 true 的情况下，线条宽度会调整到完整像素宽度。
// 在 pixelHinting 设置为 false 的情况下，对于曲线和直线可能会出现脱节.
// 如果未提供值，则线条不使用像素提示。
// scaleMode:String (default = "normal") — 用于指定要使用哪种缩放模式的 LineScaleMode 类的值： 
// LineScaleMode.NORMAL - 在缩放对象时总是缩放线条的粗细（默认值）。 
// LineScaleMode.NONE - 从不缩放线条粗细。 
// LineScaleMode.VERTICAL - 如果仅 垂直缩放对象，则不缩放线条粗细。
// LineScaleMode.HORIZONTAL - 如果仅 水平缩放对象，则不缩放线条粗细。
// caps:String (default = null) — 用于指定线条末端处端点类型的 CapsStyle 类的值。
// 有效值为：CapsStyle.NONE、CapsStyle.ROUND 和 CapsStyle.SQUARE。如果未指示值，则 Flash 使用圆头端点。  
// joints:String (default = null) — JointStyle 类的值，指定用于拐角的连接外观的类型。
// 有效值为：JointStyle.BEVEL、JointStyle.MITER 和 JointStyle.ROUND。如果未指示值，则 Flash 使用圆角连接。 
// miterLimit:Number (default = 3) — 一个表示将在哪个限制位置切断尖角的数字。
// 有效值的范围是 1 到 255（超出该范围的值将舍入为 1 或 255）。此值只可用于 jointStyle 设置为 "miter" 的情况下。
// miterLimit 值表示向外延伸的尖角可以超出角边相交所形成的结合点的长度。此值表示为线条 thickness 的因子。
void lineStyle(Number thickness = NaN, uint color = 0, Number alpha = 1.0, Boolean pixelHinting = false, 
String scaleMode = "normal", String caps = null, String joints = null, Number miterLimit = 3);
		
/*使用当前线条样式绘制一条从当前绘画位置开始到 (x, y) 结束的直线；当前绘画位置随后会设置为 (x, y)。
如果正在其中绘制的显示对象包含用 Flash 绘画工具创建的内容，则调用 lineTo() 方法将在该内容下面进行绘制。
如果在对 moveTo() 方法进行任何调用之前调用了 lineTo()，则当前绘画的默认位置为 (0, 0)。如果缺少任何一个参数，
则此方法将失败，并且当前绘画位置不改变。*/ 
// x:Number — 一个表示相对于父显示对象注册点的水平位置的数字（以像素为单位）。  
// y:Number — 一个表示相对于父显示对象注册点的垂直位置的数字（以像素为单位）。  
void	lineTo(Number x, Number y);
		
// 将当前绘画位置移动到 (x, y)。如果缺少任何一个参数，则此方法将失败，并且当前绘画位置不改变。 
// x:Number — 一个表示相对于父显示对象注册点的水平位置的数字（以像素为单位）。  
// y:Number — 一个表示相对于父显示对象注册点的垂直位置的数字（以像素为单位）。  
void	moveTo(Number x, Number y);