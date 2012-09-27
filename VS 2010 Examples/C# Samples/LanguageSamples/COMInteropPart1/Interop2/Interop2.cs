// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
//版权所有(C) Microsoft Corporation。保留所有权利。

// interop2.cs
// 编译时使用 “csc interop2.cs”  
using System;
using System.Runtime.InteropServices;

namespace QuartzTypeLib 
{
	// 将 IMediaControl 声明为一个从 IDispatch 接口派生的 
	// COM 接口:
	[Guid("56A868B1-0AD4-11CE-B03A-0020AF0BA770"), 
	InterfaceType(ComInterfaceType.InterfaceIsDual)] 
	interface IMediaControl   // 此处不能列出任何基接口
	{ 
		// 注意 IUnknown 接口成员未在此处列出:

		void Run();

		void Pause();

		void Stop();

		void GetState( [In] int msTimeout, [Out] out int pfs);

		void RenderFile(
			[In, MarshalAs(UnmanagedType.BStr)] string strFilename);

		void AddSourceFilter( 
			[In, MarshalAs(UnmanagedType.BStr)] string strFilename, 
			[Out, MarshalAs(UnmanagedType.Interface)]
			out object ppUnk);

		[return: MarshalAs(UnmanagedType.Interface)] 
		object FilterCollection();

		[return: MarshalAs(UnmanagedType.Interface)] 
		object RegFilterCollection();
            
		void StopWhenReady(); 
	}
	// 将 FilgraphManager 声明为 COM 组件类:
	[ComImport, Guid("E436EBB3-524F-11CE-9F53-0020AF0BA770")] 
	class FilgraphManager   // 此处不能有基类或
		// 接口列表。
	{ 
		// 此处不能有任何成员
		// 注意，C# 编译器将为您添加默认构造函数
		//（不带参数）。
	}
}

class MainClass 
{ 
	/********************************************************** 
	摘要:此方法收集要显示的 AVI 的文件名，
	然后创建 Quartz COM 对象的实例。 
	为了显示 AVI，程序对
	IMediaControl 调用 RenderFile 和 Run。Quartz 使用自己的线程和窗口来显示 
	AVI。主线程阻塞在 ReadLine 上，直到用户按
	Enter 键为止。
		输入参数:要显示的 avi 文件的位置
		返回值:void
	*************************************************************/ 

	public static void Main(string[] args) 
	{ 
		// 检查用户是否传入了文件名:
		if (args.Length != 1) 
		{ 
			DisplayUsage();
			return;
		} 

		if (args[0] == "/?") 
		{ 
			DisplayUsage(); 
			return;
		}

		String filename = args[0]; 

		// 检查文件是否存在
		if (!System.IO.File.Exists(filename))
		{
			Console.WriteLine("File " + filename + " not found.");
			DisplayUsage();
			return;
		}

		// 创建 Quartz 的实例
		// (Calls CoCreateInstance(E436EBB3-524F-11CE-9F53-0020AF0BA770, 
		//  NULL, CLSCTX_ALL, IID_IUnknown, 
		//  &graphManager).):
		try
		{
			QuartzTypeLib.FilgraphManager graphManager =
				new QuartzTypeLib.FilgraphManager();

			// IMediaControl 接口的 QueryInterface:
			QuartzTypeLib.IMediaControl mc = 
				(QuartzTypeLib.IMediaControl)graphManager;

			// 对 COM 接口调用某些方法。
			// 将文件传递给 COM 对象上的 RenderFile 方法。
			mc.RenderFile(filename);
        
			// 显示文件。 
			mc.Run();
		}
		catch(Exception ex)
		{
			Console.WriteLine("Unexpected COM exception: " + ex.Message);
		}
		// 等待完成。 
		Console.WriteLine("Press Enter to continue."); 
		Console.ReadLine();
	}

	private static void DisplayUsage() 
	{ 
		// 用户未提供足够的参数。 
		// 显示用法。
		Console.WriteLine("VideoPlayer: Plays AVI files."); 
		Console.WriteLine("Usage: VIDEOPLAYER.EXE filename"); 
		Console.WriteLine("where filename is the full path and");
		Console.WriteLine("file name of the AVI to display."); 
	} 
}

