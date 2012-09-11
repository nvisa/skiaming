
/*
 * Copyright 2009 The Android Open Source Project
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */


#ifndef SkTRegistry_DEFINED
#define SkTRegistry_DEFINED

#include "SkTypes.h"

/** Template class that registers itself (in the constructor) into a linked-list
    and provides a function-pointer. This can be used to auto-register a set of
    services, e.g. a set of image codecs.
 */
template <typename T, typename P> 
class SkTRegistry : SkNoncopyable {
public:
    typedef T (*Factory)(P);

    SkTRegistry(Factory fact) {		//使用函数指针构造出来
#ifdef SK_BUILD_FOR_ANDROID
        // work-around for double-initialization bug
        {
            SkTRegistry* reg = gHead;
            while (reg) {
                if (reg == this) {
                    return;
                }
                reg = reg->fChain;
            }
        }
#endif
        fFact = fact;
        fChain = gHead;	//第一个的时候,fChain为0,
        gHead = this;
    }

    static const SkTRegistry* Head() { return gHead; }

    const SkTRegistry* next() const { return fChain; }
    Factory factory() const { return fFact; }

private:
    Factory      fFact;
    SkTRegistry* fChain;	//指向上一个元素
    static SkTRegistry* gHead;
};

// The caller still needs to declare an instance of this somewhere//静态成员变量初始化为0;必须的,
template <typename T, typename P> SkTRegistry<T, P>* SkTRegistry<T, P>::gHead;	

#endif
