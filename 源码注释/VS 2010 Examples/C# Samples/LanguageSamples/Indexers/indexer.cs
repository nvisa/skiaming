// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
//版权所有(C) Microsoft Corporation。保留所有权利。

// indexer.cs
// 参数：indexer.txt
using System;
using System.IO;

// 将大文件当作字节数组
// 访问的类。
public class FileByteArray
{
    Stream stream;      // 包含用于访问
                        // 该文件的基础流。
// 创建封装特定文件的新 FileByteArray。
    public FileByteArray(string fileName)
    {
        stream = new FileStream(fileName, FileMode.Open);
    }

    // 关闭流。这应是
    // 结束前的最后一个操作。
    public void Close()
    {
        stream.Close();
        stream = null;
    }

    // 提供对文件的读/写访问的索引器。
    public byte this[long index]   // long 是 64 位整数
    {
        // 在偏移量 index 处读取一个字节，然后将其返回。
        get 
        {
            byte[] buffer = new byte[1];
            stream.Seek(index, SeekOrigin.Begin);
            stream.Read(buffer, 0, 1);
            return buffer[0];
        }
        // 在偏移量 index 处写入一个字节，然后将其返回。
        set 
        {
            byte[] buffer = new byte[1] {value};
            stream.Seek(index, SeekOrigin.Begin);
            stream.Write(buffer, 0, 1);
        }
    }

    // 获取文件的总长度。
    public long Length 
    {
        get 
        {
            return stream.Seek(0, SeekOrigin.End);
        }
    }
}

// 演示 FileByteArray 类。
// 反转文件中的字节。
public class Reverse 
{
    public static void Main(String[] args) 
    {
		// 检查参数。
		if (args.Length != 1)
		{
			Console.WriteLine("Usage : Indexer <filename>");
			return;
		}

		// 检查文件是否存在
		if (!System.IO.File.Exists(args[0]))
		{
			Console.WriteLine("File " + args[0] + " not found.");
			return;
		}

		FileByteArray file = new FileByteArray(args[0]);
		long len = file.Length;

		// 交换文件中的字节以对其进行反转。
		for (long i = 0; i < len / 2; ++i) 
		{
			byte t;

			// 请注意，为“file”变量建立索引会调用
			//  FileByteStream 类上的索引器，该索引器在文件中读取
			// 和写入字节。
			t = file[i];
			file[i] = file[len - i - 1];
			file[len - i - 1] = t;
		}

		file.Close();
    } 
}

