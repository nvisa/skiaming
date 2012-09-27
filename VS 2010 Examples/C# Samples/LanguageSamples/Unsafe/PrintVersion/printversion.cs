// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
//版权所有(C) Microsoft Corporation。保留所有权利。

// printversion.cs
// 编译时使用：/unsafe
using System;
using System.Reflection;
using System.Runtime.InteropServices;

// 为此程序集指定一个版本号：
[assembly:AssemblyVersion("4.3.2.1")]

public class Win32Imports 
{
	[DllImport("version.dll")]
	public static extern bool GetFileVersionInfo (string sFileName,
		int handle, int size, byte[] infoBuffer);
	[DllImport("version.dll")]
	public static extern int GetFileVersionInfoSize (string sFileName,
		out int handle);
   
	// 自动将第三个参数“out string pValue”从 Ansi
	// 封送处理为 Unicode：
	[DllImport("version.dll")]
	unsafe public static extern bool VerQueryValue (byte[] pBlock,
		string pSubBlock, out string pValue, out uint len);
	// 此 VerQueryValue 重载被标记为“unsafe”，因为
	// 它使用 short*：
	[DllImport("version.dll")]
	unsafe public static extern bool VerQueryValue (byte[] pBlock,
		string pSubBlock, out short *pValue, out uint len);
}

public class C 
{
	// Main 被标记为“unsafe”，因为它使用指针：
	unsafe public static int Main () 
	{
		try 
		{
			int handle = 0;
			// 确定有多少版本信息：
			int size =
				Win32Imports.GetFileVersionInfoSize("printversion.exe",
				out handle);

			if (size == 0) return -1;

			byte[] buffer = new byte[size];

			if (!Win32Imports.GetFileVersionInfo("printversion.exe", handle, size, buffer))
			{
				Console.WriteLine("Failed to query file version information.");
				return 1;
			}

			short *subBlock = null;
			uint len = 0;
			// 从版本信息获取区域设置信息：
			if (!Win32Imports.VerQueryValue (buffer, @"\VarFileInfo\Translation", out subBlock, out len))
			{
				Console.WriteLine("Failed to query version information.");
				return 1;
			}

			string spv = @"\StringFileInfo\" + subBlock[0].ToString("X4") + subBlock[1].ToString("X4") + @"\ProductVersion";

			byte *pVersion = null;
			// 获取此程序的 ProductVersion 值:
			string versionInfo;
			
			if (!Win32Imports.VerQueryValue (buffer, spv, out versionInfo, out len))
			{
				Console.WriteLine("Failed to query version information.");
				return 1;
			}

			Console.WriteLine ("ProductVersion == {0}", versionInfo);
		}
		catch (Exception e) 
		{
			Console.WriteLine ("Caught unexpected exception " + e.Message);
		}
      
		return 0;
	}
}

