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
using System.Windows.Shapes;
using UserInterface.AdventureWorksService;
using UserInterface.Gateways;

namespace UserInterface
{
    /// <summary>
    /// ProductView.xaml 的交互逻辑
    /// </summary>
    public partial class ProductView : Window
    {


        ProductGateway gateway;


	/// <summary>
        /// 启动时启动输入窗体
        /// </summary>
        public ProductView(ProductGateway gateway)
        {
            InitializeComponent();
            this.gateway = gateway;
        }

        /// <summary>
        /// 如果为 true，则表示正在使用 ProductView 窗口创建/添加新产品。
        /// 如果为 false，则表示正在使用 ProductView 窗口编辑现有产品。
        /// </summary>
        private bool _FormCreateMode = true;

        private bool FormCreateMode
        {
            get
            {
                return _FormCreateMode;
            }
            set
            {
                _FormCreateMode = value;
            }
        }

        /// <summary>
        /// 正在编辑或创建的产品实例。
        /// </summary>
        private Product product { get; set; }


        public void UpdateProduct(Product product)
        {
            this.product = gateway.GetProducts(product.Name, product.ProductCategory)[0];
            FormCreateMode = false;
            this.Title = "Edit " + product.Name;
        }


        private void BtnCancel_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            BindCategories();
            if (FormCreateMode)
            {
                product = new Product();
            }
            BindProduct();
        }

        /// <summary>
        /// 将正在更新/创建的产品实例的属性绑定到相应的 TextBox。
        /// </summary>
        private void BindProduct()
        {
            txtProductNumber.DataContext = product;
            txtName.DataContext = product;
            txtListPrice.DataContext = product;
            txtColor.DataContext = product;
            CategoryComboBoxProductDetail.DataContext = product;
            txtModifiedDate.DataContext = product;
            txtSellStartDate.DataContext = product;
            txtStandardCost.DataContext = product;
        }

        /// <summary>
        /// 查询类别列表并绑定到 ComboBox
        /// </summary>
        private void BindCategories()
        {
            CategoryComboBoxProductDetail.ItemsSource = gateway.GetCategories();
            CategoryComboBoxProductDetail.SelectedIndex = 0;
        }


        private void BtnSave_Click(object sender, RoutedEventArgs e)
        {
            if (FormCreateMode)
            {
                product.ProductCategory = (ProductCategory)CategoryComboBoxProductDetail.SelectedItem;
                gateway.AddProduct(product);
            }
            else
            {
                product.ProductCategory = (ProductCategory)CategoryComboBoxProductDetail.SelectedItem;
                gateway.UpdateProduct(product);
            }
            this.Close();
        }
    }
}
