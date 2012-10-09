' 版权所有© Microsoft Corporation。  保留所有权利。
' 此代码的发布遵从
' Microsoft 公共许可（MS-PL，http://opensource.org/licenses/ms-pl.html）的条款。

此示例创建一个新的 SharePoint 列表 (DonationList)，以及附加了 EventReceiver 
(DonationDeleting) 的 ListInstance (DonationInstance)。 

运行示例 

- 将项目的站点 URL 属性更改为开发系统上的有效 SharePoint 站点（即 
  http://<计算机名称>）。

创建列表后，可以从 SharePoint 站点的快速启动菜单访问该列表。 创建一个金额大于 0 
的新捐款项。事件接收器会阻止您删除金额大于 0 的任何捐款项。

注意：如果您在同一台计算机上运行 VB 和 C# 
示例，则运行的第二个项目会与程序包和列表实例发生名称冲突。  
这种情况下，会显示一个对话框，提示您解决冲突。
