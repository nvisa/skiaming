' 版权所有© Microsoft Corporation。  保留所有权利。
' 此代码的发布遵从
' Microsoft 公共许可（MS-PL，http://opensource.org/licenses/ms-pl.html）的条款。


这是 Visual Studio 2010 扩展的示例，适用于新的 SharePoint 项目模板。  
该示例利用扩展性 API，这些 API 是 Visual Studio 2010 中新增的 SharePoint 
开发工具的组成部分。扩展是针对 SharePoint 自定义操作的。  
若要正常使用此示例，需要安装 Visual Studio 2010 SDK。  它可以从 
http://go.microsoft.com/fwlink/?LinkId=164562 下载。

该解决方案包含两个项目：
- 实现扩展的类库项目。
- 将扩展打包到 VSIX 文件中的 VSIX 项目。 该文件用于安装扩展。

若要运行此示例，请在 Visual Studio 2010 中打开 Visual Basic 或 C# 版本的 
CustomActionProjectItem 解决方案，然后按 F5。 将进行以下操作：
- 从 ProjectItemDefinition 项目生成扩展。
- 从 CustomActionProjectItem 项目创建 VSIX 程序包。
- 启动 Visual Studio 的实验实例，其中安装了 VSIX 程序包。

在 Visual Studio 的实验实例中，可以通过执行以下操作来测试自定义操作：
- 创建一个新的空 SharePoint 项目。 您在“新建项目”对话框的“SharePoint”节点下选择 
  2010 节点后，就可使用此项目模板。 使用与打开的 CustomActionProjectItem 
  项目版本相同的编程语言（Visual Basic 或 C#）。
- 在 SharePoint 自定义向导中，键入 SharePoint 站点在本地计算机上的站点 
  URL，然后单击“完成”。
- 创建项目后，在解决方案资源管理器中右击该项目节点，然后单击“添加”|“新建项...”。
- 在“添加新项”对话框中，单击“SharePoint”节点，选择“自定义操作”项，然后单击“添加”。

该自定义操作即添加到项目中。 您可以尝试执行以下任务：
- 在解决方案资源管理器中，右击“CustomAction”节点，
  然后单击“查看自定义操作设计器”菜单项。 此快捷菜单项由扩展添加。
- 在解决方案资源管理器中，选择“CustomAction”节点，然后打开“属性”窗口。 
  验证名为“Custom Action Property”（自定义操作属性）
  的自定义属性是否显示在“属性”窗口中。 此属性由扩展添加。 
- 编辑 CustomAction 项目项下的 Elements.xml 文件，然后按 F5 
  将该文件部署到在创建项目时指定的本地站点。



