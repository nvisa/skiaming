// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
//版权所有(C) Microsoft Corporation。保留所有权利。

// pinvoke.cs
// 编译时使用：/addmodule:logfont.netmodule
// csc pinvoke.cs /addmodule:logfont.netmodule
using System;
using System.Runtime.InteropServices;

class PlatformInvokeTest
{   
	[DllImport("gdi32.dll", CharSet=CharSet.Auto)]
	public static extern IntPtr CreateFontIndirect(
		[In, MarshalAs(UnmanagedType.LPStruct)]
		LOGFONT lplf   // 特征
		);

	[DllImport("gdi32.dll")]
	public static extern bool DeleteObject(
		IntPtr handle
		);

	public static void Main() 
	{
		LOGFONT lf = new LOGFONT();
		lf.lfHeight = 9;
		lf.lfFaceName = "Arial";
		IntPtr handle = CreateFontIndirect(lf);

		if (IntPtr.Zero == handle)
		{
			Console.WriteLine("Can't creates a logical font.");
		}
		else
		{
			
			if (IntPtr.Size == 4)
				Console.WriteLine("{0:X}", handle.ToInt32());
			else
				Console.WriteLine("{0:X}", handle.ToInt64());		

			// 删除所创建的逻辑字体。
			if (!DeleteObject(handle))
				Console.WriteLine("Can't delete the logical font");

		}
		
	}
}

