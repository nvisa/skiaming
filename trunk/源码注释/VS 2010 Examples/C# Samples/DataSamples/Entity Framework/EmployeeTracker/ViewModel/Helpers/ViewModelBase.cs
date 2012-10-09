// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。


namespace EmployeeTracker.ViewModel.Helpers
{
    using System.ComponentModel;

    /// <summary>
    /// 用于合并所有 ViewModel 的常用功能的抽象基类
    /// </summary>
    public abstract class ViewModelBase : INotifyPropertyChanged
    {
        /// <summary>
        /// 当此对象上的某个属性具有新值时引发
        /// </summary>
        public event PropertyChangedEventHandler PropertyChanged;

        /// <summary>
        /// 引发此 ViewModels PropertyChanged 事件
        /// </summary>
        /// <param name="propertyName">具有新值的属性的名称</param>
        protected void OnPropertyChanged(string propertyName)
        {
            this.OnPropertyChanged(new PropertyChangedEventArgs(propertyName));
        }

        /// <summary>
        /// 引发此 ViewModels PropertyChanged 事件
        /// </summary>
        /// <param name="e">详细描述更改的参数</param>
        protected virtual void OnPropertyChanged(PropertyChangedEventArgs e)
        {
            var handler = this.PropertyChanged;
            if (handler != null)
            {
                handler(this, e);
            }
        }
    }
}
