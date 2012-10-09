// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using UserInterface.Gateways;
using UserInterface.AdventureWorksService;


namespace UserInterface
{
    /// <summary>
    /// ProductList.xaml 的交互逻辑
    /// </summary>
    public partial class ProductList : Window
    {

        ProductGateway gateway;


	/// <summary>
        /// 启动时启动输入窗体
        /// </summary>
        public ProductList()
        {
            InitializeComponent();
            gateway = new ProductGateway();
            ProductsListView.MouseDoubleClick += new System.Windows.Input.MouseButtonEventHandler(ProductsListView_MouseDoubleClick);     
        }

	/// <summary>
        /// 将 gateway.GetCategories() 的结果绑定到窗体顶部的“产品类别”组合框。
        /// </summary>
        private void BindCategories()
        {
            CategoryComboBox.ItemsSource = gateway.GetCategories();
            CategoryComboBox.SelectedIndex = 0;
        }

	/// <summary>
        /// 将 gateway.GetProducts(string ProductName, ProductCategory p) 的结果绑定到 ListView 控件。
        /// </summary>
        private void BindProducts()
        {
            if (CategoryComboBox.SelectedIndex > -1)
            {
                ProductsListView.ItemsSource = gateway.GetProducts(NameTextBox.Text, CategoryComboBox.SelectedItem as ProductCategory);
            }
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            BindCategories();            
        }

        private void ProductsListView_MouseDoubleClick(object sender, System.Windows.Input.MouseButtonEventArgs e)
        {
            Product p = ProductsListView.SelectedItem as Product;
            ProductView window = new ProductView(gateway);
            window.Closed += new EventHandler(window_Closed);
            window.UpdateProduct(p);
            window.Show();
        }

	/// <summary>
        /// 单击“搜索”按钮时调用 BindProducts()。
        /// </summary>
        private void btnSearch_Click(object sender, RoutedEventArgs e)
        {
            BindProducts();
        }

        private void btnNewProduct_Click(object sender, RoutedEventArgs e)
        {
            ProductView window = new ProductView(gateway);
            window.Closed += new EventHandler(window_Closed);
            window.Show();
        }

	/// <summary>
        /// 调用 gateway.DeleteProduct() 可启动删除所选产品的过程，如果产品无法删除，则 gateway.DeleteProduct 
	/// 不会返回 null，将通过 MessageBox 向用户显示响应。
        /// </summary>
        private void btnDeleteProduct_Click(object sender, RoutedEventArgs e)
        {
            Product p = ProductsListView.SelectedItem as Product;
            if (p != null)
            {                
                string returned = gateway.DeleteProduct(p);
                if (returned != null)
                {
                    MessageBox.Show(returned);
                }
                BindProducts();
            }
        }

	/// <summary>
        /// 选择新类别时刷新列表
        /// </summary>
        private void CategoryComboBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            BindProducts();
        } 

        void window_Closed(object sender, EventArgs e)
        {
            BindCategories();           
        }


    }
}
