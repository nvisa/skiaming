// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
//版权所有(C) Microsoft Corporation。保留所有权利。

using System;
using Extensibility;
using EnvDTE;
using EnvDTE80;
using Microsoft.VisualStudio.CommandBars;
using System.Resources;
using System.Reflection;
using System.Globalization;
using System.Windows.Forms;

namespace PasteXmlAsLinq {
    /// <summary>用于实现外接程序的对象。</summary>
    /// <seealso class='IDTExtensibility2' />
    public class Connect : Object, IDTExtensibility2, IDTCommandTarget {
        /// <summary>实现外接程序对象的构造函数。请将您的初始化代码置于此方法内。</summary>
        public Connect() {
        }

        /// <summary>实现 IDTExtensibility2 接口的 OnConnection 方法。接收正在加载外接程序的通知。</summary>
        /// <param term='Application'>宿主应用程序的根对象。</param>
        /// <param term='ConnectMode'>描述外接程序的加载方式。</param>
        /// <param term='AddInInst'>表示此外接程序的对象。</param>
        /// <seealso class='IDTExtensibility2' />
        public void OnConnection(object Application, ext_ConnectMode ConnectMode, object AddInInst, ref Array custom) {
            applicationObject = (DTE2)Application;
            addInInstance = (AddIn)AddInInst;
            if (ConnectMode == ext_ConnectMode.ext_cm_UISetup) {
                object[] contextGUIDS = new object[] { };
                Commands2 commands = (Commands2)applicationObject.Commands;

                try {
                    CommandBar menuBarCommandBar;
                    CommandBarControl toolsControl;
                    CommandBarPopup toolsPopup;
                    CommandBarControl commandBarControl;

                    //将一个命令添加到 Commands 集合:
                    Command command = commands.AddNamedCommand2(addInInstance, "PasteXmlAsLinq", "Paste XML as XElement", "Pastes the XML on the clipboard as C# Linq To Xml code", true, 59, ref contextGUIDS, (int)vsCommandStatus.vsCommandStatusSupported + (int)vsCommandStatus.vsCommandStatusEnabled, (int)vsCommandStyle.vsCommandStylePictAndText, vsCommandControlType.vsCommandControlTypeButton);

                    String editMenuName;

                    //查找 MenuBar 命令栏，该命令栏是容纳所有主菜单项的顶级命令栏:
                    menuBarCommandBar = ((CommandBars)applicationObject.CommandBars)["MenuBar"];

                    try {

                        //  此代码将获取区域性，将其追加到菜单项的名称中，
                        //  然后将此命令添加到菜单中。您可以在以下文件中看到全部顶级菜单的列表:
                        //  CommandBar.resx.
                        System.Resources.ResourceManager resourceManager = new System.Resources.ResourceManager("PasteXmlAsLinq.CommandBar", System.Reflection.Assembly.GetExecutingAssembly());
                        System.Threading.Thread thread = System.Threading.Thread.CurrentThread;
                        System.Globalization.CultureInfo cultureInfo = thread.CurrentUICulture;
                        editMenuName = resourceManager.GetString(String.Concat(cultureInfo.TwoLetterISOLanguageName, "Edit"));
                        toolsControl = menuBarCommandBar.Controls["Edit"];
                    }
                    catch (Exception) {
                        //  我们尝试查找 Edit 一词的本地化版本，但未能找到。
                        //  默认值为 en-US 一词，该值可能适用于当前区域性。
                        toolsControl = menuBarCommandBar.Controls["Edit"];
                    }

                    //将此命令置于“编辑”菜单上。
                    toolsPopup = (CommandBarPopup)toolsControl;
                    int pasteControlIndex = 1;

                    //查找“粘贴”控件，以便可在其后添加新的元素。
                    foreach (CommandBarControl commandBar in toolsPopup.CommandBar.Controls) {
                        if (String.Compare(commandBar.Caption, "&Paste", StringComparison.OrdinalIgnoreCase) == 0) {
                            pasteControlIndex = commandBar.Index + 1;
                            break;
                        }
                    }

                    //在 MenuBar 命令栏上查找相应的命令栏:
                    commandBarControl = (CommandBarControl)command.AddControl(toolsPopup.CommandBar, pasteControlIndex);
                }
                catch (Exception) {
                }
            }
        }

        /// <summary>实现 IDTExtensibility2 接口的 OnDisconnection 方法。接收正在卸载外接程序的通知。</summary>
        /// <param term='RemoveMode'>描述外接程序的卸载方式。</param>
        /// <param term='custom'>特定于宿主应用程序的参数数组。</param>
        /// <seealso class='IDTExtensibility2' />
        public void OnDisconnection(ext_DisconnectMode RemoveMode, ref Array custom) {
        }

        /// <summary>实现 IDTExtensibility2 接口的 OnAddInsUpdate 方法。当外接程序集合已发生更改时接收通知。</summary>
        /// <param term='custom'>特定于宿主应用程序的参数数组。</param>
        /// <seealso class='IDTExtensibility2' />		
        public void OnAddInsUpdate(ref Array custom) {
        }

        /// <summary>实现 IDTExtensibility2 接口的 OnStartupComplete 方法。接收宿主应用程序已完成加载的通知。</summary>
        /// <param term='custom'>特定于宿主应用程序的参数数组。</param>
        /// <seealso class='IDTExtensibility2' />
        public void OnStartupComplete(ref Array custom) {
        }

        /// <summary>实现 IDTExtensibility2 接口的 OnBeginShutdown 方法。接收正在卸载宿主应用程序的通知。</summary>
        /// <param term='custom'>特定于宿主应用程序的参数数组。</param>
        /// <seealso class='IDTExtensibility2' />
        public void OnBeginShutdown(ref Array custom) {
        }

        /// <summary>实现 IDTCommandTarget 接口的 QueryStatus 方法。此方法在更新该命令的可用性时调用</summary>
        /// <param term='CmdName'>要确定其状态的命令的名称。</param>
        /// <param term='NeededText'>该命令所需的文本。</param>
        /// <param term='StatusOption'>该命令在用户界面中的状态。</param>
        /// <param term='CommandText'>NeededText 参数所要求的文本。</param>
        /// <seealso class='Exec' />
        public void QueryStatus(string CmdName, vsCommandStatusTextWanted NeededText, ref vsCommandStatus StatusOption, ref object CommandText) {
            if (NeededText == vsCommandStatusTextWanted.vsCommandStatusTextWantedNone) {
                if (CmdName == "PasteXmlAsLinq.Connect.PasteXmlAsLinq") {
                    StatusOption = (vsCommandStatus)vsCommandStatus.vsCommandStatusUnsupported;
                    if (applicationObject.ActiveDocument != null) {
                        string xml = (string)Clipboard.GetDataObject().GetData(typeof(string));
                        if (xml != null && Converter.CanConvert(xml.Trim())) {
                            StatusOption = (vsCommandStatus)vsCommandStatus.vsCommandStatusSupported | vsCommandStatus.vsCommandStatusEnabled;
                        }
                    }
                }
            }
        }

        /// <summary>实现 IDTCommandTarget 接口的 Exec 方法。此方法在调用该命令时调用。</summary>
        /// <param term='CmdName'>要执行的命令的名称。</param>
        /// <param term='ExecuteOption'>描述该命令应如何运行。</param>
        /// <param term='VariantIn'>从调用方传递到命令处理程序的参数。</param>
        /// <param term='VariantOut'>从命令处理程序传递到调用方的参数。</param>
        /// <param term='Handled'>通知调用方此命令是否已被处理。</param>
        /// <seealso class='Exec' />
        public void Exec(string CmdName, vsCommandExecOption ExecuteOption, ref object VariantIn, ref object VariantOut, ref bool Handled) {
            Handled = false;
            if (ExecuteOption == vsCommandExecOption.vsCommandExecOptionDoDefault) {
                if (CmdName == "PasteXmlAsLinq.Connect.PasteXmlAsLinq") {
                    Document doc = applicationObject.ActiveDocument;
                    if (doc != null) {
                        string xml = (string)Clipboard.GetDataObject().GetData(typeof(string));
                        if (xml != null) {
                            try {
                                string code = Converter.Convert(xml);
                                TextSelection s = (TextSelection)doc.Selection;
                                s.Insert(code, (int)vsInsertFlags.vsInsertFlagsContainNewText);
                                applicationObject.ExecuteCommand("Edit.FormatSelection", "");
                            }
                            catch (Exception e) {
                                MessageBox.Show("Clipboard does not contain valid XML.\r\n" + e.Message, "Error",
                                    MessageBoxButtons.OK, MessageBoxIcon.Error);
                            }
                        }
                    }
                    Handled = true;
                    return;
                }
            }
        }
        private DTE2 applicationObject;
        private AddIn addInInstance;
    }
}