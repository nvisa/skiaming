// 版权所有(C) Microsoft Corporation。保留所有权利。

// cominteropPart2\COMClient.cpp
// 用下面的命令行生成示例的这一部分:
//  cl COMClient.cpp

#include <windows.h>
#include <stdio.h>

#pragma warning (disable: 4278)

// 若要使用类似 C# 服务器的托管代码服务器，
// 必须导入公共语言运行时:
#import <mscorlib.tlb> raw_interfaces_only

// 为简洁起见，我们将忽略服务器命名空间并使用命名的 GUID:
#if defined (USINGPROJECTSYSTEM)
#import "..\RegisterCSharpServerAndExportTLB\CSharpServer.tlb" no_namespace named_guids
#else  // 从命令行编译，所有文件均在同一目录中
#import "CSharpServer.tlb" no_namespace named_guids
#endif
int main(int argc, char* argv[])
{
    IManagedInterface *cpi = NULL;
    int retval = 1;

    // 初始化 COM 并创建 InterfaceImplementation 类的实例:
    CoInitialize(NULL);
    HRESULT hr = CoCreateInstance(CLSID_InterfaceImplementation,
                                  NULL,
                                  CLSCTX_INPROC_SERVER,
                                  IID_IManagedInterface,
                                  reinterpret_cast<void**>(&cpi));

    if (FAILED(hr))
    {
        printf("Couldn't create the instance!... 0x%x\n", hr);
    }
    else
    {
        if (argc > 1)
        {
            printf("Calling function.\n");
            // 现在，变量 cpi 保存指向        // 托管接口的接口指针。
            // 如果使用的操作系统在命令提示符下使用 ASCII 字符，          // 请注意对于 C# 代码，ASCII 字符 
            // 将自动封送为 Unicode。

            if (cpi->PrintHi(argv[1]) == 33)
                retval = 0;

            printf("Returned from function.\n");
        }
        else
            printf ("Usage:  COMClient <name>\n");
        cpi->Release();
        cpi = NULL;
    }

    // 请养成好习惯，清理 COM:
    CoUninitialize();
    return retval;
}

