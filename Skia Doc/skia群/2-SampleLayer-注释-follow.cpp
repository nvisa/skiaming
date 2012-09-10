#include "SampleCode.h"
#include "SkView.h"
#include "SkCanvas.h"
#include "SkBlurMaskFilter.h"
#include "SkCamera.h"
#include "SkColorFilter.h"
#include "SkColorPriv.h"
#include "SkDevice.h"
#include "SkGradientShader.h"
#include "SkImageDecoder.h"
#include "SkInterpolator.h"
#include "SkMaskFilter.h"
#include "SkPath.h"
#include "SkRegion.h"
#include "SkShader.h"
#include "SkTime.h"
#include "SkTypeface.h"
#include "SkUtils.h"
#include "SkKey.h"
#include "SkXfermode.h"
#include "SkDrawFilter.h"
/*本节部分内容还不清晰, 有疑议请提出讨论*/


/** Layers层     -----------------   可以参考photoshop中图层的应用与效果哦～
基本使用流程 : 1. saveLayer -> 绘制 -> restore
               2. saveLayer, saveLayer, saveLayer -> 绘制 -> restore, restore, restore
基本原理 : saveLayer创建层 -> 之后可以在该层设置若干属性, 进行绘制 -> restore会递归的将本层内容, 逐一画到没有释放的layer与源canvas中.
基本理解 : 1. 创建不同区域的layer, 可以形成canvas上 不同区域呈现不同的属性, 
            当你用canvas.draw(全局, 椭圆), restore所有层后, 你将看到一个在不同区域呈现不同属性的椭圆(透明效果等)
           2. 有些效果只有layer上能使用, 或者在layer上更方便运用.
            例如: (1) 例子中做了一个实验, 在没有layer时, setXfermodeMode的效果是无法生效的
                  (2) 结合层来绘制出 例5的 上下渐变的椭圆,,,如果不用层～你如何办到`?
*/
/*例子流程 : onDraw(包含例1-例5) -> test_fade(例4) */
static void make_paint(SkPaint* paint) {
    /*??????????????????????CreateLiner各参数及其作用????*/
    //建立阴影区域
    SkColor colors[] = { 0, SK_ColorWHITE};
    SkPoint pts[] = { { 0, 0 }, { 0, SK_Scalar1*20}};
    SkShader* s = SkGradientShader::CreateLinear(pts, colors, NULL, 2, SkShader::kClamp_TileMode);
    //把阴影 加到画笔上
    paint->setShader(s)->unref();
    /*重点
    按照Dst图像区域的属性 进行混合
    把该句注释掉, 结果图中 可以看到 :
    Dst是 上下两片 由内到外的 灰色渐变矩形.
    Src是 之前绘制的红圆
    kDstIn_Mode ： 主体为src&dst相交的dst部分, 但
                   要把src图层融合进来, 这里src是个透明渐变层.
    */
    paint->setXfermodeMode(SkXfermode::kDstIn_Mode);
}

static void dump_layers(const char label[], SkCanvas* canvas) {
    SkDebugf("Dump Layers(%s)\n", label);

    SkCanvas::LayerIter iter(canvas, true);
    int index = 0;
    while (!iter.done()) {
        const SkBitmap& bm = iter.device()->accessBitmap(false);
        const SkIRect& clip = iter.clip().getBounds();
        SkDebugf("Layer[%d] bitmap [%d %d] X=%d Y=%d clip=[%d %d %d %d] alpha=%d\n", index++,
                 bm.width(), bm.height(), iter.x(), iter.y(),
                 clip.fLeft, clip.fTop, clip.fRight, clip.fBottom,
                 iter.paint().getAlpha());
        iter.next();
    }
}

// test drawing with strips of fading gradient above and below
static void test_fade(SkCanvas* canvas) {
    /*SkAutoCanvasRestore
      建立了2个SkAutoCanvasRestore, 
      因为后面会创建两个layer, 都没有手动restore释放, 
      而是在退出函数时, 通过这两个SkAutoCanvasRestore的析构函数自动restore释放.
      
      为什么要有SkAutoCanvasRestore?
      因为 savelayer在任意处,         resotre只能回复到 savelayer时的状态,
      在函数开始处使用SkAutoCanvasRestore, 可以使回复到 函数进入时的状态, 而非savelayer时刻的状态.--------有待商榷，我会尽快跟一下，然后把save跟restore的内容做一次讨论--牛群
      更干净的清除状态.
    */
    SkAutoCanvasRestore ar(canvas, true);

    SkRect r;
    
    SkPaint p;
    p.setAlpha(0x88);

    SkAutoCanvasRestore(canvas, false);

    // create the layers
    r.set(0, 0, SkIntToScalar(100), SkIntToScalar(100));
    /*重点1 : 剪裁区域(限制区域) : 使可绘制区域限制成clipRect设置的大小.
      取消clip方法
      1. 不适用clipRect(r)
      2. canvas.restore()一次, 回复到之前无clip状态
      3. ???????????????????有函数直接取消单个clipRect属性吗?-------目前没有看到取消clip的函数，但是clip也是一次链表，应该可以读取到之前的clip大小，并进行设置。restore的作用是可以将一套数据进行恢复，不仅仅是clip。类似于中断中的现场保护与恢复--牛群
    */
    canvas->clipRect(r);
    /*新增 : 实验clip的代码.*/
    if(false) {
      SkRect r2;
      r2.set(0, 0, SkIntToScalar(200), SkIntToScalar(200));
      SkPaint p2;
      p2.setColor(SK_ColorBLUE);
      p2.setAntiAlias(true);
      canvas->drawOval(r2, p2);
    }

    //建立层1, 上半矩形
    r.fBottom = SkIntToScalar(20);
    r.fRight = SkIntToScalar(100);
    canvas->saveLayer(&r, NULL, (SkCanvas::SaveFlags)(SkCanvas::kHasAlphaLayer_SaveFlag | SkCanvas::kFullColorLayer_SaveFlag));

    //建立层2, 下半矩形
    r.fTop = SkIntToScalar(80);
    r.fBottom = SkIntToScalar(100);
    canvas->saveLayer(&r, NULL, (SkCanvas::SaveFlags)(SkCanvas::kHasAlphaLayer_SaveFlag | SkCanvas::kFullColorLayer_SaveFlag));


    /*以下两段区别 :
      前者 利用layer,     画了一个透明圆
      后者 直接在canvase, 画了一个纯色圆
    */
    if (false) {
        r.set(0, 0, SkIntToScalar(100), SkIntToScalar(100));
        canvas->saveLayerAlpha(&r, 0x80);

        SkPaint p;
        p.setColor(SK_ColorRED);
        p.setAntiAlias(true);
        canvas->drawOval(r, p);

        dump_layers("inside layer alpha", canvas);
        canvas->restore();
    } else {
        r.set(0, 0, SkIntToScalar(100), SkIntToScalar(100));
        
        SkPaint p;
        p.setColor(SK_ColorRED);
        p.setAntiAlias(true);
        canvas->drawOval(r, p);
    }
    
    dump_layers("outside layer alpha", canvas);

    //制作画笔
    SkPaint paint;
    make_paint(&paint);
    r.set(0, 0, SkIntToScalar(100), SkIntToScalar(20));

//SkDebugf("--------- draw top grad\n");

    //画上半圆
    canvas->drawRect(r, paint);

    SkMatrix m;
    //修改阴影
    SkShader* s = paint.getShader();
    /*在(0，0) - (0， 100)范围内, 以x为轴竖直反转. 
     (结果图为 : 从上到下渐变的阴影, 变为了从下到上渐变的阴影)*/    //---这个不能叫做阴影，叫做渐变
    m.setScale(SK_Scalar1, -SK_Scalar1);
    m.postTranslate(0, SkIntToScalar(100));
    s->setLocalMatrix(m);
    
    r.fTop = SkIntToScalar(80);
    r.fBottom = SkIntToScalar(100);
//  SkDebugf("--------- draw bot grad\n");
    //画下半圆
    canvas->drawRect(r, paint);

    //退出函数时自动释放两次restore， 将两层saveLayer绘制到canvas，形成结果.
}

class RedFilter : public SkDrawFilter {
public:
    virtual bool filter(SkCanvas*, SkPaint* p, SkDrawFilter::Type) {
        fColor = p->getColor();
        if (fColor == SK_ColorRED) {
            p->setColor(SK_ColorGREEN);
        }
        return true;
    }
    virtual void restore(SkCanvas*, SkPaint* p, SkDrawFilter::Type) {
        p->setColor(fColor);
    }
    
private:
    SkColor fColor;
};

class LayersView : public SkView {
public:
	LayersView() {}

protected:
    // overrides from SkEventSink
    virtual bool onQuery(SkEvent* evt) {
        if (SampleCode::TitleQ(*evt)) {
            SampleCode::TitleR(evt, "Layers");
            return true;
        }
        return this->INHERITED::onQuery(evt);
    }
    
    void drawBG(SkCanvas* canvas) {
        canvas->drawColor(SK_ColorGRAY);
    }
    
    virtual void onDraw(SkCanvas* canvas) {
        /*背景灰色*/
        this->drawBG(canvas);
        
        /*例1 : 层上画两个有重叠的图形, 最后在restore时一起绘制到canvas中.*/
        if (false) {
            /*建层A, 画上一个红矩形*/
            SkRect r;
			      r.set(SkIntToScalar(0), SkIntToScalar(0),
				      SkIntToScalar(220), SkIntToScalar(120));
            SkPaint p;
            canvas->saveLayer(&r, &p);
            canvas->drawColor(0xFFFF0000);
            
            /*在层A上, 以XfermodeMode模式, 画一个蓝椭圆*/
            p.setAlpha(100); 
            p.setColor(0xFF0000FF);
            //Xfermode各参数效果图见:  http://blog.csdn.net/wylwhd/article/details/6180272 
            p.setXfermodeMode(SkXfermode::kSrc_Mode);
            canvas->drawOval(r, p);

            /*释放层A : restore会将层A上的图案, 画到canvas唯一的bitmap上, 以及将与其他未释放的layer有重叠的部分画到各自layer的canvas上.*/
            canvas->restore();
            return;
        }
        
        /*例2 : 层上画一个图形, 在restore时绘制到canvas中, canvas再绘制一个有重叠的图形*/
        if (false) {
            SkRect r;
			      r.set(SkIntToScalar(0), SkIntToScalar(0),
				      SkIntToScalar(220), SkIntToScalar(120));
            SkPaint p;
            p.setAlpha(0x88);
            p.setAntiAlias(true);
            
            if (true) {
                canvas->saveLayer(&r, &p);
                p.setColor(0xFFFF0000);
                canvas->drawOval(r, p);
                canvas->restore();
            }

            p.setColor(0xFF0000FF);
            r.offset(SkIntToScalar(20), SkIntToScalar(50));
            canvas->drawOval(r, p);
        }

        /*例3 : 这里展示了 层 很重要的一个特性:  
          绘制过程 : 设置透明层 -> 跨层区域 与 原canvas区域 画一个圆 -> 层区域展示了层的属性, canvas区域展示了canvas的属性
          结论 : 层的建立, 只是使各区域 变得属性各异,
        */
        if (false) {
            SkPaint p;
            p.setAlpha(0x44);
            p.setAntiAlias(true);

            canvas->translate(SkIntToScalar(300), 0);

            SkRect r;
			      r.set(SkIntToScalar(0), SkIntToScalar(0),
				          SkIntToScalar(220), SkIntToScalar(60));
   
            canvas->saveLayer(&r, &p, (SkCanvas::SaveFlags)(SkCanvas::kHasAlphaLayer_SaveFlag | SkCanvas::kFullColorLayer_SaveFlag));
//            canvas->clipRect(r, SkRegion::kDifference_Op);
//            canvas->clipRect(r, SkRegion::kIntersect_Op);
            //后加代码 : 测试层的覆盖顺序 : 看不到这个红椭圆, 因为上一层在最后释放时, 重画的部分挡住了这个红椭圆
            if (true) {
              r.set(SkIntToScalar(0), SkIntToScalar(40),
                SkIntToScalar(220), SkIntToScalar(80));
              canvas->saveLayer(&r, &p);
              p.setColor(SK_ColorRED);
              canvas->drawOval(r, p);
              canvas->restore();
            }


			      r.set(SkIntToScalar(0), SkIntToScalar(0),
				          SkIntToScalar(220), SkIntToScalar(120));
            p.setColor(SK_ColorBLUE);
             canvas->drawOval(r, p);
            canvas->restore();
            return;
        }
        
        //canvas->translate(SkIntToScalar(20), SkIntToScalar(20));
        /*例4 : 画1个圆, 利用层将上下两部分变成渐变色.*/
         test_fade(canvas);
         return;
        //canvas->setDrawFilter(new RedFilter)->unref();
        
        /*例5 : canvas画一蓝色矩形-> 建层, 画一红椭圆-> 利用交集 将上半个椭圆画成透明 -> 释放层*/
        SkRect  r;
        SkPaint p;
        
        canvas->translate(SkIntToScalar(220), SkIntToScalar(20));
        
        //画一个蓝矩形
        p.setAntiAlias(true);
        r.set(SkIntToScalar(20), SkIntToScalar(20),
              SkIntToScalar(220), SkIntToScalar(120));
        
        p.setColor(SK_ColorBLUE);
        //模糊的滤镜效果
        //p.setMaskFilter(SkBlurMaskFilter::Create(SkIntToScalar(8), SkBlurMaskFilter::kNormal_BlurStyle))->unref();
        canvas->drawRect(r, p);
        //没有滤镜效果
        p.setMaskFilter(NULL);

        //取上一半矩形建个层
        SkRect bounds = r;
        bounds.fBottom = bounds.centerY();
        /*重点1 : 做个实验:
          去掉canvas->saveLayer(&bounds, NULL, SkCanvas::kARGB_NoClipLayer_SaveFlag);
          去掉canvas->restore();
          运行.
          你会发现 p.setAlpha(0x80)的透明效果没了
                   p.setXfermodeMode(SkXfermode::kSrcIn_Mode)的剪裁效果没了.-------关于这个的效果，本质上是与drawDevice中如何运用paint这个对象有关--牛群
          结论 : Alpha, XfermodeMode的效果要基于layer使用.
        */
        canvas->saveLayer(&bounds, NULL, SkCanvas::kARGB_NoClipLayer_SaveFlag);
        p.setColor(SK_ColorYELLOW);
        canvas->drawOval(r, p);

        p.setAlpha(0x00);
        p.setColor(SK_ColorRED);
        /*重点2 : p.setXfermodeMode(SkXfermode::kSrcIn_Mode)
                  谁是src? 谁是dst?
          结论 :  -> saveLayer
                  ->canvas->drawOval(r, p);
                  -> p.setXfermodeMode(SkXfermode::kSrcIn_Mode) 
                  -> canvas->drawRect(bounds, p);
                  -> restore
                 前一次draw是src, 后一次draw是dst.
                 必须在“一层”中有这样一个过程, 才能形成剪切.  //------这里仅仅是设置了相关的混合属性，不知与剪切有什么关系---牛群
          注意 : 1. 没有层不能剪切
                 2. 这个顺序在canvas->drawOval(r, p)不在层上时, 不能剪切, 
                     而以下顺序canvas->drawOval(r, p)在源canvase中
                 ->canvas->drawOval(r, p);
                 -> saveLayer
                 -> p.setXfermodeMode(SkXfermode::kSrcIn_Mode) 
                 -> canvas->drawRect(bounds, p);
                 -> restore
        */
        p.setXfermodeMode(SkXfermode::kSrcIn_Mode);
        canvas->drawRect(bounds, p);

        canvas->restore();
    }
    
    virtual SkView::Click* onFindClickHandler(SkScalar x, SkScalar y) {
        this->inval(NULL);
        
        return this->INHERITED::onFindClickHandler(x, y);
    }
    
    virtual bool onClick(Click* click) {
        return this->INHERITED::onClick(click);
    }

	virtual bool handleKey(SkKey key) {
        this->inval(NULL);
        return true;
    }

private:
    typedef SkView INHERITED;
};

//////////////////////////////////////////////////////////////////////////////

static SkView* MyFactory() { return new LayersView; }
static SkViewRegister reg(MyFactory);

