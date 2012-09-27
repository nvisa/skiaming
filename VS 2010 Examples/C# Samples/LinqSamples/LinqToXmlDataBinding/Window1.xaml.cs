// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
//
using System;
using System.IO;
using System.Net;
using System.Windows;
using System.Windows.Input;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Navigation;
using System.ComponentModel;
using System.Xml.Linq;

namespace LinqToXmlDataBinding {
    public partial class Window1 : Window {
        private Brush previousBrush;

        public Window1() {
            this.InitializeComponent();
        }

        /// <summary>
        /// 关闭时保存 MyFavorites 列表。
        /// </summary>
        protected override void OnClosing(CancelEventArgs args) {
            XElement myFavorites = (XElement)((ObjectDataProvider)Resources["MyFavoritesList"]).Data;
            myFavorites.Save(@"..\..\data\MyFavorites.xml");
        }

        /// <summary>
        /// 播放按钮事件处理程序
        /// </summary>
        void OnPlay(object sender, EventArgs e) {
            videoImage.Visibility = Visibility.Hidden;
            mediaElement.Play();
        }

        /// <summary>
        /// 停止按钮事件处理程序
        /// </summary>
        void OnStop(object sender, EventArgs e) {
            mediaElement.Stop();
            videoImage.Visibility = Visibility.Visible;
        }

        /// <summary>
        /// 添加按钮事件处理程序，用于将当前选中的视频添加到 MyFavorites 中
        /// </summary>
        void OnAdd(object sender, EventArgs e) {
            XElement itemsList = (XElement)((ObjectDataProvider)Resources["MyFavoritesList"]).Data;
            itemsList.Add(videoListBox1.SelectedItem as XElement);
        }

        /// <summary>
        /// 删除按钮事件处理程序，用于从 MyFavorites 中删除当前选中的视频
        /// </summary>
        void OnDelete(object sender, EventArgs e) {
            XElement selectedItem = (XElement)videoListBox2.SelectedItem;
            if (selectedItem != null) {
                if (selectedItem.PreviousNode != null)
                    this.videoListBox2.SelectedItem = selectedItem.PreviousNode;
                else if (selectedItem.NextNode != null)
                    this.videoListBox2.SelectedItem = selectedItem.NextNode;
                selectedItem.Remove();
            }
        }

        /// <summary>
        /// 搜索框事件处理程序，用于按用户指定的输入搜索视频
        /// </summary>
        private void OnKeyUp(object sender, KeyEventArgs e) {
            if (e.Key.Equals(Key.Enter)) {
                ObjectDataProvider objectDataProvider = Resources["MsnVideosList"] as ObjectDataProvider;
                objectDataProvider.MethodParameters[0] = @"http://soapbox.msn.com/rss.aspx?searchTerm=" + searchBox.Text;
                objectDataProvider.Refresh();
            }
        }

        /// <summary>
        /// 搜索选项的事件处理程序列在第一页，只须更新静态资源
        /// 用新参数执行“MsnVideosList”，然后对其进行刷新。
        /// </summary>
        private void OnMouseUp(object sender, System.Windows.Input.MouseButtonEventArgs e) {
            string content = (string)((Label)sender).Content;
            ObjectDataProvider objectDataProvider = Resources["MsnVideosList"] as ObjectDataProvider;

            switch (content) {
                case "Most Viewed":
                    objectDataProvider.MethodParameters[0] = @"http://soapbox.msn.com/rss.aspx?listId=MostPopular";
                    objectDataProvider.Refresh();
                    break;
                case "Most Recent":
                    objectDataProvider.MethodParameters[0] = @"http://soapbox.msn.com/rss.aspx?listId=MostRecent";
                    objectDataProvider.Refresh();
                    break;
                case "Top Favorites":
                    objectDataProvider.MethodParameters[0] = @"http://soapbox.msn.com/rss.aspx?listId=TopFavorites";
                    objectDataProvider.Refresh();
                    break;
                case "Top Rated":
                    objectDataProvider.MethodParameters[0] = @"http://soapbox.msn.com/rss.aspx?listId=TopRated";
                    objectDataProvider.Refresh();
                    break;
                case "My Favorites":
                    XElement msn = (XElement)objectDataProvider.Data;
                    XElement favorites = (XElement)((ObjectDataProvider)Resources["MyFavoritesList"]).Data;
                    msn.ReplaceAll(favorites.Elements("item"));
                    break;
            }
        }

        /// <summary>
        /// 鼠标进入或离开时更改颜色或搜索链接，以表示
        /// 它们是可点击的
        /// </summary>
        private void OnMouseEnter(object sender, System.Windows.Input.MouseEventArgs e) {
            Label myLabel = sender as Label;
            previousBrush = myLabel.Foreground;
            myLabel.Foreground = Brushes.Blue;
        }

        private void OnMouseLeave(object sender, System.Windows.Input.MouseEventArgs e) {
            Label myLabel = sender as Label;
            myLabel.Foreground = previousBrush;
        }
    }
}