namespace DataAnalysisExcel
{
    partial class UnscheduledOrderControl
    {
        /// <summary> 
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 带有完整风味的列表的组合框。
        /// </summary>
        private System.Windows.Forms.ComboBox flavorComboBox;

        /// <summary>
        /// 高库存项的列表。
        /// </summary>
        private System.Windows.Forms.ListBox highList;

        /// <summary>
        /// 低库存项的列表。
        /// </summary>
        private System.Windows.Forms.ListBox lowList;

        /// <summary>
        ///  基于 Sales 表的数据视图，表示当前日。
        /// </summary>
        private OperationsData.OperationsView view;

        private System.Windows.Forms.Label selectorLabel;

        private System.Windows.Forms.Label highLabel;

        private System.Windows.Forms.Label lowLabel;

        private System.Windows.Forms.GroupBox recommendationGroup;

        /// <summary>
        /// 这显示有关是否应创建非计划
        /// 订单的建议。 
        /// </summary>
        private System.Windows.Forms.Label recommendationLabel;

        private System.Windows.Forms.Label orderLabel;

        /// <summary>
        /// 用于创建非计划订单的按钮。
        /// </summary>
        private System.Windows.Forms.Button createOrderButton;

        /// <summary> 
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，则为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region 组件设计器生成的代码

        /// <summary> 
        /// 设计器支持所需的方法 - 请勿 
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(UnscheduledOrderControl));
            this.selectorLabel = new System.Windows.Forms.Label();
            this.flavorComboBox = new System.Windows.Forms.ComboBox();
            this.highLabel = new System.Windows.Forms.Label();
            this.lowLabel = new System.Windows.Forms.Label();
            this.highList = new System.Windows.Forms.ListBox();
            this.lowList = new System.Windows.Forms.ListBox();
            this.recommendationGroup = new System.Windows.Forms.GroupBox();
            this.createOrderButton = new System.Windows.Forms.Button();
            this.orderLabel = new System.Windows.Forms.Label();
            this.recommendationLabel = new System.Windows.Forms.Label();
            this.recommendationGroup.SuspendLayout();
            this.SuspendLayout();
            // 
            // selectorLabel
            // 
            resources.ApplyResources(this.selectorLabel, "selectorLabel");
            this.selectorLabel.Name = "selectorLabel";
            // 
            // flavorComboBox
            // 
            this.flavorComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.flavorComboBox.FormattingEnabled = true;
            resources.ApplyResources(this.flavorComboBox, "flavorComboBox");
            this.flavorComboBox.Name = "flavorComboBox";
            this.flavorComboBox.SelectedIndexChanged += new System.EventHandler(this.flavorComboBox_SelectedIndexChanged);
            // 
            // highLabel
            // 
            resources.ApplyResources(this.highLabel, "highLabel");
            this.highLabel.Name = "highLabel";
            // 
            // lowLabel
            // 
            resources.ApplyResources(this.lowLabel, "lowLabel");
            this.lowLabel.Name = "lowLabel";
            // 
            // highList
            // 
            this.highList.FormattingEnabled = true;
            resources.ApplyResources(this.highList, "highList");
            this.highList.Name = "highList";
            this.highList.Click += new System.EventHandler(this.inventoryList_Click);
            // 
            // lowList
            // 
            this.lowList.FormattingEnabled = true;
            resources.ApplyResources(this.lowList, "lowList");
            this.lowList.Name = "lowList";
            this.lowList.Click += new System.EventHandler(this.inventoryList_Click);
            // 
            // recommendationGroup
            // 
            this.recommendationGroup.Controls.Add(this.createOrderButton);
            this.recommendationGroup.Controls.Add(this.orderLabel);
            this.recommendationGroup.Controls.Add(this.recommendationLabel);
            resources.ApplyResources(this.recommendationGroup, "recommendationGroup");
            this.recommendationGroup.Name = "recommendationGroup";
            this.recommendationGroup.TabStop = false;
            // 
            // createOrderButton
            // 
            resources.ApplyResources(this.createOrderButton, "createOrderButton");
            this.createOrderButton.Name = "createOrderButton";
            this.createOrderButton.Click += new System.EventHandler(this.CreateOrderButton_Click);
            // 
            // orderLabel
            // 
            resources.ApplyResources(this.orderLabel, "orderLabel");
            this.orderLabel.Name = "orderLabel";
            // 
            // recommendationLabel
            // 
            resources.ApplyResources(this.recommendationLabel, "recommendationLabel");
            this.recommendationLabel.Name = "recommendationLabel";
            // 
            // UnscheduledOrderControl
            // 
            this.Controls.Add(this.recommendationGroup);
            this.Controls.Add(this.lowList);
            this.Controls.Add(this.highList);
            this.Controls.Add(this.lowLabel);
            this.Controls.Add(this.highLabel);
            this.Controls.Add(this.flavorComboBox);
            this.Controls.Add(this.selectorLabel);
            this.Name = "UnscheduledOrderControl";
            resources.ApplyResources(this, "$this");
            this.recommendationGroup.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

    }
}
