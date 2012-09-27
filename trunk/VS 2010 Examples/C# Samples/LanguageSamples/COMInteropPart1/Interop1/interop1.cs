// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
//版权所有(C) Microsoft Corporation。保留所有权利。

// interop1.cs
// 用“csc /R:QuartzTypeLib.dll interop1.cs”生成
using System;
class MainClass 
{ 
	/************************************************************ 
	摘要:此方法收集要显示的 AVI 的文件名，
	然后创建 Quartz COM 对象的实例。
	为了显示 AVI，程序对 IMediaControl 调用 RenderFile 和 Run。 
	Quartz 使用自己的线程和窗口显示 
	AVI。主线程阻塞在 ReadLine 上，直到用户按
	Enter 键为止。
		输入参数:要显示的 avi 文件的位置。
		返回值:void
	**************************************************************/ 
	public static void Main(string[] args) 
	{ 
		// 检查用户是否传入了文件名 
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

		string filename = args[0]; 

		// 检查文件是否存在
		if (!System.IO.File.Exists(filename))
		{
			Console.WriteLine("File " + filename + " not found.");
			DisplayUsage();
			return;
		}
    
		// 创建 Quartz 的实例
		// (Calls CoCreateInstance(E436EBB3-524F-11CE-9F53-0020AF0BA770,
		// NULL, CLSCTX_ALL, IID_IUnknown, &graphManager).): 

		try
		{
			QuartzTypeLib.FilgraphManager graphManager = 
				new QuartzTypeLib.FilgraphManager();

			// IMediaControl 接口的 QueryInterface:
			QuartzTypeLib.IMediaControl mc =
				(QuartzTypeLib.IMediaControl)graphManager;

			// 对 COM 接口调用某些方法 
			// 将文件传递给 COM 对象的 RenderFile 方法。 
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
		// 显示用法:
		Console.WriteLine("VideoPlayer: Plays AVI files."); 
		Console.WriteLine("Usage: VIDEOPLAYER.EXE filename"); 
		Console.WriteLine("where filename is the full path and"); 
		Console.WriteLine("file name of the AVI to display."); 
	} 
}

