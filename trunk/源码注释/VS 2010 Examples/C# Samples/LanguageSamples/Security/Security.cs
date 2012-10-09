// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
//版权所有(C) Microsoft Corporation。保留所有权利。
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Security;
using System.Security.Permissions;
using System.Runtime.InteropServices;

public class MainClass
{
    public static void Main() 
    {
        //创建文件 IO 读取权限
        FileIOPermission FileIOReadPermission = new FileIOPermission(PermissionState.None);
        FileIOReadPermission.AllLocalFiles = FileIOPermissionAccess.Read;

        //创建基本权限集
        PermissionSet BasePermissionSet = new PermissionSet(PermissionState.None); // PermissionState.Unrestricted 用于完全信任
        BasePermissionSet.AddPermission(new SecurityPermission(SecurityPermissionFlag.Execution));

        PermissionSet grantset = BasePermissionSet.Copy();
        grantset.AddPermission(FileIOReadPermission);

        //编写示例源文件以读取
        System.IO.File.WriteAllText("TEST.TXT", "File Content");

        //-------- 完全信任地调用方法 -------- 
        try
        {
            Console.WriteLine("App Domain Name: " + AppDomain.CurrentDomain.FriendlyName);
            ReadFileMethod();
        }
        catch (Exception ex)
        {
            Console.WriteLine(ex.Message);
        }

        //-------- 创建具有文件 IO 读取权限的 AppDomain -------- 
        AppDomain sandbox = AppDomain.CreateDomain("Sandboxed AppDomain With FileIO.Read permission", AppDomain.CurrentDomain.Evidence, AppDomain.CurrentDomain.SetupInformation, grantset, null);
        try
        {
            Console.WriteLine("App Domain Name: " + AppDomain.CurrentDomain.FriendlyName);
            sandbox.DoCallBack(new CrossAppDomainDelegate(ReadFileMethod));
        }
        catch (Exception ex)
        {
            Console.WriteLine(ex.Message);
        }
        

        //-------- 创建没有文件 IO 读取权限的 AppDomain -------- 
        //应当引发安全异常
        PermissionSet grantset2 = BasePermissionSet.Copy();
        AppDomain sandbox2 = AppDomain.CreateDomain("Sandboxed AppDomain Without FileIO.Read permission", AppDomain.CurrentDomain.Evidence, AppDomain.CurrentDomain.SetupInformation, grantset2, null);
        try
        {
            Console.WriteLine("App Domain Name: " + AppDomain.CurrentDomain.FriendlyName);
            sandbox2.DoCallBack(new CrossAppDomainDelegate(ReadFileMethod));
        }
        catch (Exception ex)
        {
            Console.WriteLine(ex.Message);
        }

        Console.WriteLine("");
        Console.WriteLine("Press any key to end.");
        Console.ReadKey();
    }

    static public void ReadFileMethod()
    {
        string S = System.IO.File.ReadAllText("TEST.TXT");
        Console.WriteLine("File Content: " + S);
        Console.WriteLine("");
    }

}



    