// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
//版权所有(C) Microsoft Corporation。保留所有权利。

// logfont.cs
// 编译时使用：/target:module
using System;
using System.Runtime.InteropServices;

[StructLayout(LayoutKind.Sequential)]
public class LOGFONT 
{ 
    public const int LF_FACESIZE = 32;
    public int lfHeight; 
    public int lfWidth; 
    public int lfEscapement; 
    public int lfOrientation; 
    public int lfWeight; 
    public byte lfItalic; 
    public byte lfUnderline; 
    public byte lfStrikeOut; 
    public byte lfCharSet; 
    public byte lfOutPrecision; 
    public byte lfClipPrecision; 
    public byte lfQuality; 
    public byte lfPitchAndFamily;
    [MarshalAs(UnmanagedType.ByValTStr, SizeConst=LF_FACESIZE)]
    public string lfFaceName; 
}

