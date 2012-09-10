#include "SampleCode.h"
#include "SkView.h"
#include "SkCanvas.h"
#include "SkGradientShader.h"
#include "SkPath.h"
#include "SkRegion.h"
#include "SkShader.h"
#include "SkUtils.h"
#include "Sk1DPathEffect.h"
#include "SkCornerPathEffect.h"
#include "SkPathMeasure.h"
#include "SkRandom.h"
#include "SkColorPriv.h"
#include "SkColorFilter.h"
#include "SkDither.h"

/*
  SampleFilter = 滤镜样子 ： 滤镜的作用与效果 见 百度百科
  流程 : FilterView() -> make_bm() ->
         onDrawContent() ->  draw_row() -> draw_set() -> draw_bm()
*/
static void make_bm(SkBitmap* bm) {
    const SkColor colors[] = {
        SK_ColorRED, SK_ColorGREEN,
        SK_ColorBLUE, SK_ColorWHITE
    };
    //颜色表 存储4个颜色
    SkColorTable* ctable = new SkColorTable(colors, 4);
    //bitmap设置格式 为一个像素8位, 共2*2个像素
    bm->setConfig(SkBitmap::kIndex8_Config, 2, 2);
    //bitmap分配实际内存, 按照以上格式
    bm->allocPixels(ctable);

    //颜色表的引用值-1 ：见到0时释放, 
    ctable->unref();
    
    /*获取kIndex8_Config的bitmap的 (0,0)像素内存位置, 赋值0, 为索引0的颜色..
      依次将红, 绿, 蓝, 白赋值给4个像素 ： 见结果图样式. */
    *bm->getAddr8(0, 0) = 0;
    *bm->getAddr8(1, 0) = 1;
    *bm->getAddr8(0, 1) = 2;
    *bm->getAddr8(1, 1) = 3;
}

static SkScalar draw_bm(SkCanvas* canvas, const SkBitmap& bm,
                        SkScalar x, SkScalar y, SkPaint* paint) {
#if 1
    //将bitmap 按照paint格式 画到canvas的x, y位置.
    canvas->drawBitmap(bm, x, y, paint);
    return SkIntToScalar(bm.width()) * 5/4;
#else
    SkAutoCanvasRestore acr(canvas, true);
    canvas->translate(x, y);

    SkScalar w = SkIntToScalar(bm.width());
    SkScalar h = SkIntToScalar(bm.height());
    SkShader* s = SkShader::CreateBitmapShader(bm, SkShader::kRepeat_TileMode,
                                               SkShader::kRepeat_TileMode);
    paint->setShader(s)->unref();
    canvas->drawRect(SkRect::MakeWH(w, h), *paint);
    paint->setShader(NULL);
    return w * 5/4;
#endif
}

static SkScalar draw_set(SkCanvas* c, const SkBitmap& bm, SkScalar x, SkPaint* p) {
    //正常的
    x += draw_bm(c, bm, x, 0, p);

    //开启滤镜 ： 见百度百科
    p->setFilterBitmap(true);
    x += draw_bm(c, bm, x, 0, p);

    //开启抗抖动 ：见百度百科
    p->setDither(true);//抖动
    return x + draw_bm(c, bm, x, 0, p);
}

/*行头文字*/
static const char* gConfigNames[] = {
  "unknown config",
  "A1",
  "A8",
  "Index8",
  "565",
  "4444",
  "8888"
};

static SkScalar draw_row(SkCanvas* canvas, const SkBitmap& bm) {
    //此为canvas的save操作
	//在超过了作用域之后，会自动调用restore函数
    SkAutoCanvasRestore acr(canvas, true);

    SkPaint paint;
    SkScalar x = 0;
    const int scale = 64;

    //开启抗锯齿　：　见百度百科
    paint.setAntiAlias(true); 
    //绘制行首文字 ： 见结果图每行行头文字
    const char* name = gConfigNames[bm.config()];
    canvas->drawText(name, strlen(name), x, SkIntToScalar(bm.height())*scale*5/8,
                     paint);

    //平移到(48, 0)？？？为何是48--牛群
    canvas->translate(SkIntToScalar(192), 0);
    //缩放 ： x,y轴乘各乘以一个系数, 进行放大或缩小.：　此处因为４个像素很小,所以进行了放大.
    canvas->scale(SkIntToScalar(scale), SkIntToScalar(scale));
    
    /*逐个画每行的6个方块*/
    //画前三个, 正常的, 滤镜的, 滤镜+防抖动的.
    x += draw_set(canvas, bm, 0, &paint);
    //画笔复原
    paint.reset();
    /*开启透明, 画后三个, 正常的, 滤镜的, 滤镜+防抖动的. */
    paint.setAlpha(0x80);
    draw_set(canvas, bm, x, &paint);
    return x * scale / 3;
}

class FilterView : public SampleView {
public:
    SkBitmap    fBM8, fBM4444, fBM16, fBM32;

	FilterView() {
        /*做一张bitmap, kIndex8_Config格式的2行2列
          依次转换成 其他3种格式的bitmap : 见结果图, 对应4行.*/
        make_bm(&fBM8);
        fBM8.copyTo(&fBM4444, SkBitmap::kARGB_4444_Config);
        fBM8.copyTo(&fBM16, SkBitmap::kRGB_565_Config);
        fBM8.copyTo(&fBM32, SkBitmap::kARGB_8888_Config);
        
        //设置背景色 为 灰色 : 见结果图
        this->setBGColor(0xFFDDDDDD);
    }

protected:
    // overrides from SkEventSink
    virtual bool onQuery(SkEvent* evt) {
        if (SampleCode::TitleQ(*evt)) {
            SampleCode::TitleR(evt, "Filter");
            return true;
        }
        return this->INHERITED::onQuery(evt);
    }
    
    virtual void onDrawContent(SkCanvas* canvas) {        
		SkScalar x = SkIntToScalar(10);
        SkScalar y = SkIntToScalar(10);
        
        /*依次用四种格式的bitmap画四行, 一行6个方块*/
        //平移到（10, 10）开始画.
        //y依次下移
        canvas->translate(x, y);
        y = draw_row(canvas, fBM8);
        canvas->translate(0, y);
        y = draw_row(canvas, fBM4444);
        canvas->translate(0, y);
        y = draw_row(canvas, fBM16);
        canvas->translate(0, y);
        draw_row(canvas, fBM32);
    }
    
private:
    typedef SampleView INHERITED;
};

//////////////////////////////////////////////////////////////////////////////

static SkView* MyFactory() { return new FilterView; }
static SkViewRegister reg(MyFactory);

