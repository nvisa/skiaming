using System.Reflection;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Security;
using Microsoft.Office.Tools.Excel;

// 有关程序集的常规信息通过以下特性集 
// 控制。更改这些特性值可修改
// 与程序集关联的信息。
[assembly: AssemblyTitle("RibbonControlsExcelWorkbook")]
[assembly: AssemblyDescription("")]
[assembly: AssemblyConfiguration("")]
[assembly: AssemblyCompany("Microsoft")]
[assembly: AssemblyProduct("RibbonControlsExcelWorkbook")]
[assembly: AssemblyCopyright("Copyright © Microsoft 2007")]
[assembly: AssemblyTrademark("")]
[assembly: AssemblyCulture("")]

// 将 ComVisible 设置为 false 会使此程序集中的类型 
// 对 COM 组件不可见。如果需要从 COM 访问此程序集中的某个类型，
// 请将该类型上的 ComVisible 特性设置为 true。
[assembly: ComVisible(false)]

// 如果此项目向 COM 公开，则以下 GUID 用作类型库的 ID
[assembly: Guid("962463d0-c18e-48d4-a415-65a8c472939c")]

// 程序集的版本信息由下列四个值组成:
//
//      主版本
//      次版本 
//      内部版本号
//      修订号
//
// 可以指定所有这些值，也可以使用“内部版本号”和“修订号”的默认值，
// 方法是按如下方式使用“*”:
// [assembly: AssemblyVersion("1.0.*")]
[assembly: AssemblyVersion("1.0.0.0")]
[assembly: AssemblyFileVersion("1.0.0.0")]

// 
// ExcelLocale1033 特性用于控制传递给 Excel 对象模型的区域设置。
// 将 ExcelLocale1033 设置为 true 会使 Excel 对象模型在 
// 所有区域设置下采取同一行为，该行为与 Visual Basic for Applications 
// 的行为相符。将 ExcelLocale1033 设置为 false 会使 Excel 对象模型
// 的行为随用户区域设置的不同而不同，该行为 
// 与 Visual Studio Tools for Office 版本 2003 的行为相符。这会导致 
// 区分区域设置的信息(如公式名和日期格式)中出现意外结果。
// 
[assembly: ExcelLocale1033(true)]

[assembly: SecurityTransparent()]