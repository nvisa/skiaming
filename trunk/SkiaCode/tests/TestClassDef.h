
/*
 * Copyright 2011 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
/*  This file is meant to be included by .cpp files, so it can spew out a
    customized class + global definition.
	*被cpp文件包含,所以可以定制一个类,并且为全局定义
    e.g.
    #include "TestClassDef.h"
    DEFINE_TESTCLASS("MyTest", MyTestClass, MyTestFunction)

    where MyTestFunction is declared as

        void MyTestFunction(skiatest::Reporter*)
*/
//定义类,并定义静态全局变量,静态全局变量只在本文件可见,文件外不可见,不会出现名字冲突
//使用Test子类的Factory函数指针构造静态全局对象
#define DEFINE_TESTCLASS(uiname, classname, function)                       \
    namespace skiatest {                                                    \
        class classname : public Test {                                     \
        public:                                                             \
            static Test* Factory(void*) { return SkNEW(classname); }        \
        protected:                                                          \
            virtual void onGetName(SkString* name) { name->set(uiname); }   \
            virtual void onRun(Reporter* reporter) { function(reporter); }  \
        };                                                                  \
        static TestRegistry gReg(classname::Factory);                       \
    }

#define DEFINE_GPUTESTCLASS(uiname, classname, function)                    \
    namespace skiatest {                                                    \
        class classname : public GpuTest {                                  \
        public:                                                             \
            static Test* Factory(void*) { return SkNEW(classname); }        \
        protected:                                                          \
            virtual void onGetName(SkString* name) { name->set(uiname); }   \
            virtual void onRun(Reporter* reporter) {                        \
                if (fContext) {                                             \
                    function(reporter, fContext);                           \
                }                                                           \
            }                                                               \
        };                                                                  \
        static TestRegistry gReg(classname::Factory);                       \
    }
