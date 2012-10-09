// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。


namespace EmployeeTracker.ViewModel.Helpers
{
    using System;
    using System.Diagnostics;
    using System.Windows.Input;

    /// <summary>
    /// 基于委托的 ICommand 实现
    /// </summary>
    public class DelegateCommand : ICommand
    {
        /// <summary>
        /// 执行此命令时要执行的操作
        /// </summary>
        private Action<object> executionAction;

        /// <summary>
        /// 确定命令是否可执行的谓词
        /// </summary>
        private Predicate<object> canExecutePredicate;

        /// <summary>
        /// 初始化 DelegateCommand 类的新实例。
        /// 始终可以执行该命令。
        /// </summary>
        /// <param name="execute">要在执行时调用的委托</param>
        public DelegateCommand(Action<object> execute)
            : this(execute, null)
        {
        }

        /// <summary>
        /// 初始化 DelegateCommand 类的新实例。
        /// </summary>
        /// <param name="execute">要在执行时调用的委托</param>
        /// <param name="canExecute">确定命令是否可执行的谓词</param>
        public DelegateCommand(Action<object> execute, Predicate<object> canExecute)
        {
            if (execute == null)
            {
                throw new ArgumentNullException("execute");
            }

            this.executionAction = execute;
            this.canExecutePredicate = canExecute;
        }

        /// <summary>
        /// 更改 CanExecute 时引发
        /// </summary>
        public event EventHandler CanExecuteChanged
        {
            add { CommandManager.RequerySuggested += value; }
            remove { CommandManager.RequerySuggested -= value; }
        }

        /// <summary>
        /// 执行支持此 DelegateCommand 的委托
        /// </summary>
        /// <param name="parameter">要传递给谓词的参数</param>
        /// <returns>如果命令可执行，则为 true</returns>
        public bool CanExecute(object parameter)
        {
            return this.canExecutePredicate == null ? true : this.canExecutePredicate(parameter);
        }

        /// <summary>
        /// 执行支持此 DelegateCommand 的委托
        /// </summary>
        /// <param name="parameter">要传递给委托的参数</param>
        /// <exception cref="InvalidOperationException">如果 CanExecute 返回 false，则引发异常</exception>
        public void Execute(object parameter)
        {
            if (!this.CanExecute(parameter))
            {
                throw new InvalidOperationException("The command is not valid for execution, check the CanExecute method before attempting to execute.");
            }

            this.executionAction(parameter);
        }
    }
}
