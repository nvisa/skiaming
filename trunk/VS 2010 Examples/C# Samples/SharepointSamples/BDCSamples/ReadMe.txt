' 版权所有© Microsoft Corporation。  保留所有权利。
' 此代码的发布遵从
' Microsoft 公共许可（MS-PL，http://opensource.org/licenses/ms-pl.html）的条款。

*************自述文件****************

应用于 VB 和 C# 示例项目。

这些 BDC 示例连接到用作外部数据源的 Northwind 数据库。 
在运行示例项目之前，请仔细阅读下面的说明，并确保您拥有 Northwind 数据库连接。


*****************
准备 Northwind DB
*****************

如果您已拥有 Northwind 数据库，则只需打开每个项目中的 Setting.setting 
文件，并使用您自己的连接字符串更新 NORTHWNDConnectionString。

否则，请执行以下步骤：

1. 执行这些步骤时，假定您已在计算机上安装了随 Visual Studio 和 SharePoint Server 
   免费提供的 SQL Express。 如果尚未安装，请先访问 
   http://www.microsoft.com/express/sql/download/ 并安装 SQL Express。

2. 创建“SampleNorthwind”DB。 为此，请打开 VS。转到“视图”->“服务器资源管理器”。 
   右击“服务器资源管理器”窗口中的“数据连接”节点，然后选择“创建新 SQL Server 
   数据库”。

3. 在提示对话框中，输入“localhost\sqlexpress”作为服务器名称，
   并提供新数据库名称“SampleNorthwind”。

   * 如果要使用 SharePoint Server 附带的 
     SQL Express，请将“localhost\sqlexpress”替换为“localhost\sharepoint”。

4. 启动命令提示符。

5. 在命令提示符处，键入以下命令并按 Enter： 

	sqlcmd -S localhost\sqlexpress -d samplenorthwind -i 
           <CreateSampleNorthwindDB.sql 文件的路径>
   
   * CreateSampleNorthwindDB.sql 与本自述文件位于同一文件夹中。 该文件会为您创建 
     Customer 表架构和数据。


*************
部署 BDC 模型
*************

现在可以打开示例项目。 您需要首先指定项目的站点 URL。 
为此，请单击项目节点，然后在“属性”窗口中，将“站点 URL”设置为“http://localhost”。 
此时按 F5 进行调试，或单击“生成”->“部署”来部署 BDC 模型。

* 请注意，如果您要同时处理两个示例项目，建议您创建另一个数据库表来连接第二个项目。

两个示例项目当前都连接到您刚刚创建的同一个 
DB，因此在运行时，可能只有一个项目正确连接到该数据库。 
为了避免发生任何数据冲突，强烈建议创建另一个表。 
为此，您可以再次执行上面的步骤，只不过要使用另一个表名称。 
完成此操作后，只需打开项目中的 Setting.setting 文件，将 NORTHWNDConnectionString 
更改为连接到新表。


*******************************
在 SharePoint 站点上创建外部列表
*******************************

成功部署 BDC 模型后，现在便可以在 SharePoint 站点上创建外部列表，以操作数据。 

为此，请执行以下操作： 

1. 转到 SharePoint 站点的主页。 通常为 Http://localhost。
2. 在站点的左上角处，选择“网站操作”->“更多选项”。 
3. 在“创建”页上，单击“外部列表”。
4. 在“新建”页上，提供列表的名称。在“数据源配置”部分，单击“选择外部内容类型”按钮。 
   在提示“外部内容类型选取器”时，选择刚刚部署的类型
  （BdcSampleCSharp.BdcModel1.Customer 或 BdcSampleVB.Customer）。

   *注意：如果您无法在“外部内容类型”选取器中看到任何类型，这可能是因为您未被授予访问 
    BDC 元数据存储区的权限。 若要授予此权限，请转到“SharePoint 
    管理中心”页，单击“管理服务应用程序”[Manage Service 
    applications]，然后单击“业务数据连接服务”。 在“查看外部内容类型”[View External 
    Content Types]页上，单击功能区中的“设置元数据存储区权限”[Set Metadata Store 
    Permissions]。 然后，在“设置元数据存储区权限”[Set Metadata Store 
    Permissions]对话框中添加您的用户名，并授予权限。

5. 在“新建”页上单击“确定”。

现在，应该可以在 SharePoint 页上看到客户列表，并且可以创建/更新/删除客户信息。 
更改将在数据库中实时进行。
