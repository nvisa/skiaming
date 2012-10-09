// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
//版权所有(C) Microsoft Corporation。保留所有权利。

using System;
using System.Reflection;
using System.Resources;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

//
// 有关程序集的常规信息通过下列特性集
// 控制。更改这些特性值可修改
// 与程序集关联的信息。
//
[assembly: AssemblyTitle("")]
[assembly: AssemblyDescription("")]
[assembly: AssemblyConfiguration("")]
[assembly: AssemblyCompany("")]
[assembly: AssemblyProduct("")]
[assembly: AssemblyCopyright("")]
[assembly: AssemblyTrademark("")]
[assembly: AssemblyCulture("")]

//
// 程序集的版本信息由下面四个值组成:
//
//      主版本
//      次版本
//      修订号
//      内部版本号
//
// 您可以指定所有值，也可以使用“修订号”和“内部版本号”的默认值
// 方法是按如下所示使用“*”:

[assembly: AssemblyVersion("1.0.*")]

//
// 要对程序集进行签名，必须指定要使用的密钥。有关程序集签名的更多信息，请参考
// Microsoft .NET Framework 文档。
//
// 使用以下特性控制用于签名的密钥。
//
// 注意: 
//   (*) 如果未指定任何密钥，则无法对程序集签名。
//   (*) KeyName 是指计算机上的加密服务
//       提供程序(CSP)中已经安装的密钥。
//   (*) 如果密钥文件和密钥名称特性都已指定，则
//       按如下方式进行处理:
//       (1) 如果可在 CSP 中找到 KeyName，则使用该密钥。
//       (2) 如果 KeyName 不存在而 KeyFile 存在，
//           则在 CSP 中安装并使用该文件中的密钥。
//   (*)“延迟签名”是一个高级选项，有关它的详细信息，
//       请参阅 Microsoft .NET Framework 文档。
//
[assembly: AssemblyDelaySign(false)]
[assembly: AssemblyKeyFile("")]
[assembly: AssemblyKeyName("")]

[assembly: CLSCompliant(false)]

//代码分析禁止显示
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Performance", "CA1800:DoNotCastUnnecessarily", Scope = "member", Target = "PasteXmlAsLinq.Converter.#WriteNewElement(System.Xml.Linq.XElement)")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Performance", "CA1800:DoNotCastUnnecessarily", Scope = "member", Target = "PasteXmlAsLinq.Converter.#IsSingleLineText(System.Xml.Linq.XElement)")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Performance", "CA1804:RemoveUnusedLocals", MessageId = "commandBarControl", Scope = "member", Target = "PasteXmlAsLinq.Connect.#OnConnection(System.Object,Extensibility.ext_ConnectMode,System.Object,System.Array&)")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Security", "CA2122:DoNotIndirectlyExposeMethodsWithLinkDemands", Scope = "member", Target = "PasteXmlAsLinq.Converter.#FindNamespaces()")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Usage", "CA2209:AssembliesShouldDeclareMinimumSecurity")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Design", "CA2210:AssembliesShouldHaveValidStrongNames")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Design", "CA1031:DoNotCatchGeneralExceptionTypes", Scope = "member", Target = "PasteXmlAsLinq.Connect.#Exec(System.String,EnvDTE.vsCommandExecOption,System.Object&,System.Object&,System.Boolean&)")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Design", "CA1031:DoNotCatchGeneralExceptionTypes", Scope = "member", Target = "PasteXmlAsLinq.Connect.#OnConnection(System.Object,Extensibility.ext_ConnectMode,System.Object,System.Array&)")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Design", "CA1031:DoNotCatchGeneralExceptionTypes", Scope = "member", Target = "PasteXmlAsLinq.Converter.#CanConvert(System.String)")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Globalization", "CA1300:SpecifyMessageBoxOptions", Scope = "member", Target = "PasteXmlAsLinq.Connect.#Exec(System.String,EnvDTE.vsCommandExecOption,System.Object&,System.Object&,System.Boolean&)")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Design", "CA1017:MarkAssembliesWithComVisible")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Performance", "CA1824:MarkAssembliesWithNeutralResourcesLanguage")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Design", "CA1001:TypesThatOwnDisposableFieldsShouldBeDisposable", Scope = "type", Target = "PasteXmlAsLinq.Converter")]
