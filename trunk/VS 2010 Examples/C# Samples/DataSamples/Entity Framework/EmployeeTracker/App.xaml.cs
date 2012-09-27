// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。


namespace EmployeeTracker
{
    using System.Diagnostics.CodeAnalysis;
    using System.Windows;
    using EmployeeTracker.Common;
    using EmployeeTracker.EntityFramework;
    using EmployeeTracker.Fakes;
    using EmployeeTracker.Model.Interfaces;
    using EmployeeTracker.View;
    using EmployeeTracker.ViewModel;

    /// <summary>
    /// App.xaml 的交互逻辑
    /// </summary>
    [System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Design", "CA1001:TypesThatOwnDisposableFieldsShouldBeDisposable", Justification = "Context is disposed when app exits.")]
    public partial class App : Application
    {
        /// <summary>
        /// 用于协调应用程序更改的工作单元
        /// </summary>
        private IEmployeeContext context;

        /// <summary>
        /// 如果为 true，则将使用虚设的内存中的上下文
        /// 如果为 false，则将使用 ADO.Net Entity Framework 上下文
        /// </summary>
        private bool useFakes = false;

        /// <summary>
        /// 启动时启动输入窗体
        /// </summary>
        /// <param name="e">startup 事件的参数</param>
        protected override void OnStartup(StartupEventArgs e)
        {
            base.OnStartup(e);

            if (this.useFakes)
            {
                this.context =  Generation.BuildFakeSession();
            }
            else
            {
                //注意: 如果 .\SQLEXPRESS 中没有 Microsoft SQL Server Express 实例， 
                //      您将需要更新 App.config 中的“EmployeeEntities”连接字符串
                this.context = new EmployeeEntities();
            }

            IDepartmentRepository departmentRepository = new DepartmentRepository(this.context);
            IEmployeeRepository employeeRepository = new EmployeeRepository(this.context);
            IUnitOfWork unit = new UnitOfWork(this.context);

            MainViewModel main = new MainViewModel(unit, departmentRepository, employeeRepository);
            MainView window = new View.MainView { DataContext = main };
            window.Show();
        }

        /// <summary>
        /// 退出时清理所有资源
        /// </summary>
        /// <param name="e">exit 事件的参数</param>
        protected override void OnExit(ExitEventArgs e)
        {
            this.context.Dispose();

            base.OnExit(e);
        }
    }
}
