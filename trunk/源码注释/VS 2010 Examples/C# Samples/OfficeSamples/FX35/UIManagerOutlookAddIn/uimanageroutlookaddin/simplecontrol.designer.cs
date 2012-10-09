// 版权所有(C) Microsoft Corporation。保留所有权利。
// 此代码的发布遵从
// Microsoft 公共许可(MS-PL，http://opensource.org/licenses/ms-pl.html)的条款。


namespace UiManagerOutlookAddIn
{
    partial class SimpleControl
    {
        /// <summary> 
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(SimpleControl));
            this._coffeePicture = new System.Windows.Forms.PictureBox();
            this._coffeeList = new System.Windows.Forms.ListBox();
            this._coffeeGroup = new System.Windows.Forms.GroupBox();
            this._closeCoffeeList = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this._coffeePicture)).BeginInit();
            this._coffeeGroup.SuspendLayout();
            this.SuspendLayout();
            // 
            // _coffeePicture
            // 
            this._coffeePicture.Image = global::UiManagerOutlookAddIn.Properties.Resources.espressoCup_tall;
            resources.ApplyResources(this._coffeePicture, "_coffeePicture");
            this._coffeePicture.Name = "_coffeePicture";
            this._coffeePicture.TabStop = false;
            // 
            // _coffeeList
            // 
            resources.ApplyResources(this._coffeeList, "_coffeeList");
            this._coffeeList.FormattingEnabled = true;
            this._coffeeList.Name = "_coffeeList";
            // 
            // _coffeeGroup
            // 
            this._coffeeGroup.Controls.Add(this._closeCoffeeList);
            this._coffeeGroup.Controls.Add(this._coffeeList);
            this._coffeeGroup.ForeColor = System.Drawing.SystemColors.ControlLightLight;
            resources.ApplyResources(this._coffeeGroup, "_coffeeGroup");
            this._coffeeGroup.Name = "_coffeeGroup";
            this._coffeeGroup.TabStop = false;
            // 
            // _closeCoffeeList
            // 
            this._closeCoffeeList.ForeColor = System.Drawing.SystemColors.ControlText;
            resources.ApplyResources(this._closeCoffeeList, "_closeCoffeeList");
            this._closeCoffeeList.Name = "_closeCoffeeList";
            this._closeCoffeeList.UseVisualStyleBackColor = true;
            this._closeCoffeeList.Click += new System.EventHandler(this.closeCoffeeList_Click);
            // 
            // SimpleControl
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ControlText;
            this.Controls.Add(this._coffeeGroup);
            this.Controls.Add(this._coffeePicture);
            this.Name = "SimpleControl";
            ((System.ComponentModel.ISupportInitialize)(this._coffeePicture)).EndInit();
            this._coffeeGroup.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.PictureBox _coffeePicture;
        internal System.Windows.Forms.ListBox _coffeeList;
        internal System.Windows.Forms.GroupBox _coffeeGroup;
        internal System.Windows.Forms.Button _closeCoffeeList;

    }
}
