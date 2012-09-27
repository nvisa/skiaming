// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
//版权所有(C) Microsoft Corporation。保留所有权利。

// readfile.cs
// 编译时使用：/unsafe
// 参数：readfile.txt

// 使用该程序读并显示文本文件。
using System;
using System.Runtime.InteropServices;
using System.Text;

class FileReader
{
	const uint GENERIC_READ = 0x80000000;
	const uint OPEN_EXISTING = 3;
	IntPtr handle;

	[DllImport("kernel32", SetLastError=true)]
	static extern unsafe IntPtr CreateFile(
		string FileName,				// 文件名
		uint DesiredAccess,				// 访问模式
		uint ShareMode,					// 共享模式
		uint SecurityAttributes,		// 安全特性
		uint CreationDisposition,		// 如何创建
		uint FlagsAndAttributes,		// 文件特性
		int hTemplateFile				// 模板文件的句柄
		);



	[DllImport("kernel32", SetLastError=true)]
	static extern unsafe bool ReadFile(
		IntPtr hFile,					// 文件句柄
		void* pBuffer,				// 数据缓冲区
		int NumberOfBytesToRead,	// 要读取的字节数
		int* pNumberOfBytesRead,		// 已读取的字节数
		int Overlapped				// 重叠缓冲区
		);


	[DllImport("kernel32", SetLastError=true)]
	static extern unsafe bool CloseHandle(
		IntPtr hObject   // 对象句柄
		);
	
	public bool Open(string FileName)
	{
		// 打开现有文件进行读取
		
		handle = CreateFile(
			FileName,
			GENERIC_READ,
			0, 
			0, 
			OPEN_EXISTING,
			0,
			0);
	
		if (handle != IntPtr.Zero)
			return true;
		else
			return false;
	}

	public unsafe int Read(byte[] buffer, int index, int count) 
	{
		int n = 0;
		fixed (byte* p = buffer) 
		{
			if (!ReadFile(handle, p + index, count, &n, 0))
				return 0;
		}
		return n;
	}

	public bool Close()
	{
		// 关闭文件句柄
		return CloseHandle(handle);
	}
}

class Test
{
	public static int Main(string[] args)
	{
		if (args.Length != 1)
		{
			Console.WriteLine("Usage : ReadFile <FileName>");
			return 1;
		}
		
		if (! System.IO.File.Exists(args[0]))
		{
			Console.WriteLine("File " + args[0] + " not found."); 
			return 1;
		}

		byte[] buffer = new byte[128];
		FileReader fr = new FileReader();
		
		if (fr.Open(args[0]))
		{
			
			// 假定正在读取 ASCII 文件
			ASCIIEncoding Encoding = new ASCIIEncoding();
			
			int bytesRead;
			do 
			{
				bytesRead = fr.Read(buffer, 0, buffer.Length);
				string content = Encoding.GetString(buffer,0,bytesRead);
				Console.Write("{0}", content);
			}
			while ( bytesRead > 0);
			
			fr.Close();
			return 0;
		}
		else
		{
			Console.WriteLine("Failed to open requested file");
			return 1;
		}
	}
}
