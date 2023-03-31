namespace DBMSLab1
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            DataGridViewTeaTypes = new DataGridView();
            DataGridViewTeas = new DataGridView();
            label1 = new Label();
            label2 = new Label();
            label3 = new Label();
            textBoxTeaId = new TextBox();
            label4 = new Label();
            label5 = new Label();
            label6 = new Label();
            label7 = new Label();
            label8 = new Label();
            textBoxTeaTypeId = new TextBox();
            textBoxName = new TextBox();
            textBoxQuantity = new TextBox();
            textBoxPrice = new TextBox();
            textBoxDistributorId = new TextBox();
            buttonAdd = new Button();
            buttonRemove = new Button();
            buttonUpdate = new Button();
            ((System.ComponentModel.ISupportInitialize)DataGridViewTeaTypes).BeginInit();
            ((System.ComponentModel.ISupportInitialize)DataGridViewTeas).BeginInit();
            SuspendLayout();
            // 
            // DataGridViewTeaTypes
            // 
            DataGridViewTeaTypes.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            DataGridViewTeaTypes.Location = new Point(22, 41);
            DataGridViewTeaTypes.Name = "DataGridViewTeaTypes";
            DataGridViewTeaTypes.RowHeadersWidth = 62;
            DataGridViewTeaTypes.RowTemplate.Height = 33;
            DataGridViewTeaTypes.SelectionMode = DataGridViewSelectionMode.ColumnHeaderSelect;
            DataGridViewTeaTypes.Size = new Size(426, 225);
            DataGridViewTeaTypes.TabIndex = 0;
            DataGridViewTeaTypes.SelectionChanged += DataGridViewTeaTypes_SelectionChanged;
            // 
            // DataGridViewTeas
            // 
            DataGridViewTeas.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            DataGridViewTeas.Location = new Point(22, 311);
            DataGridViewTeas.Name = "DataGridViewTeas";
            DataGridViewTeas.RowHeadersWidth = 62;
            DataGridViewTeas.RowTemplate.Height = 33;
            DataGridViewTeas.Size = new Size(426, 225);
            DataGridViewTeas.TabIndex = 1;
            DataGridViewTeas.SelectionChanged += DataGridViewTeas_SelectionChanged;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(22, 9);
            label1.Name = "label1";
            label1.Size = new Size(82, 25);
            label1.TabIndex = 2;
            label1.Text = "TeaTypes";
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(22, 283);
            label2.Name = "label2";
            label2.Size = new Size(45, 25);
            label2.TabIndex = 3;
            label2.Text = "Teas";
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Location = new Point(565, 41);
            label3.Name = "label3";
            label3.Size = new Size(53, 25);
            label3.TabIndex = 4;
            label3.Text = "TeaId";
            // 
            // textBoxTeaId
            // 
            textBoxTeaId.Location = new Point(733, 41);
            textBoxTeaId.Name = "textBoxTeaId";
            textBoxTeaId.Size = new Size(150, 31);
            textBoxTeaId.TabIndex = 5;
            // 
            // label4
            // 
            label4.AutoSize = true;
            label4.Location = new Point(565, 111);
            label4.Name = "label4";
            label4.Size = new Size(90, 25);
            label4.TabIndex = 6;
            label4.Text = "TeaTypeId";
            // 
            // label5
            // 
            label5.AutoSize = true;
            label5.Location = new Point(565, 176);
            label5.Name = "label5";
            label5.Size = new Size(59, 25);
            label5.TabIndex = 7;
            label5.Text = "Name";
            // 
            // label6
            // 
            label6.AutoSize = true;
            label6.Location = new Point(565, 241);
            label6.Name = "label6";
            label6.Size = new Size(80, 25);
            label6.TabIndex = 8;
            label6.Text = "Quantity";
            // 
            // label7
            // 
            label7.AutoSize = true;
            label7.Location = new Point(565, 311);
            label7.Name = "label7";
            label7.Size = new Size(49, 25);
            label7.TabIndex = 9;
            label7.Text = "Price";
            // 
            // label8
            // 
            label8.AutoSize = true;
            label8.Location = new Point(565, 376);
            label8.Name = "label8";
            label8.Size = new Size(113, 25);
            label8.TabIndex = 10;
            label8.Text = "DistributorId";
            // 
            // textBoxTeaTypeId
            // 
            textBoxTeaTypeId.Location = new Point(733, 111);
            textBoxTeaTypeId.Name = "textBoxTeaTypeId";
            textBoxTeaTypeId.Size = new Size(150, 31);
            textBoxTeaTypeId.TabIndex = 11;
            // 
            // textBoxName
            // 
            textBoxName.Location = new Point(733, 176);
            textBoxName.Name = "textBoxName";
            textBoxName.Size = new Size(150, 31);
            textBoxName.TabIndex = 12;
            // 
            // textBoxQuantity
            // 
            textBoxQuantity.Location = new Point(733, 241);
            textBoxQuantity.Name = "textBoxQuantity";
            textBoxQuantity.Size = new Size(150, 31);
            textBoxQuantity.TabIndex = 13;
            // 
            // textBoxPrice
            // 
            textBoxPrice.Location = new Point(733, 311);
            textBoxPrice.Name = "textBoxPrice";
            textBoxPrice.Size = new Size(150, 31);
            textBoxPrice.TabIndex = 14;
            // 
            // textBoxDistributorId
            // 
            textBoxDistributorId.Location = new Point(733, 373);
            textBoxDistributorId.Name = "textBoxDistributorId";
            textBoxDistributorId.Size = new Size(150, 31);
            textBoxDistributorId.TabIndex = 15;
            // 
            // buttonAdd
            // 
            buttonAdd.Location = new Point(555, 435);
            buttonAdd.Name = "buttonAdd";
            buttonAdd.Size = new Size(112, 34);
            buttonAdd.TabIndex = 16;
            buttonAdd.Text = "add";
            buttonAdd.UseVisualStyleBackColor = true;
            buttonAdd.Click += buttonAdd_Click;
            // 
            // buttonRemove
            // 
            buttonRemove.Location = new Point(702, 435);
            buttonRemove.Name = "buttonRemove";
            buttonRemove.Size = new Size(112, 34);
            buttonRemove.TabIndex = 17;
            buttonRemove.Text = "remove";
            buttonRemove.UseVisualStyleBackColor = true;
            buttonRemove.Click += buttonRemove_Click;
            // 
            // buttonUpdate
            // 
            buttonUpdate.Location = new Point(853, 435);
            buttonUpdate.Name = "buttonUpdate";
            buttonUpdate.Size = new Size(112, 34);
            buttonUpdate.TabIndex = 18;
            buttonUpdate.Text = "update";
            buttonUpdate.UseVisualStyleBackColor = true;
            buttonUpdate.Click += buttonUpdate_Click;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(10F, 25F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(986, 548);
            Controls.Add(buttonUpdate);
            Controls.Add(buttonRemove);
            Controls.Add(buttonAdd);
            Controls.Add(textBoxDistributorId);
            Controls.Add(textBoxPrice);
            Controls.Add(textBoxQuantity);
            Controls.Add(textBoxName);
            Controls.Add(textBoxTeaTypeId);
            Controls.Add(label8);
            Controls.Add(label7);
            Controls.Add(label6);
            Controls.Add(label5);
            Controls.Add(label4);
            Controls.Add(textBoxTeaId);
            Controls.Add(label3);
            Controls.Add(label2);
            Controls.Add(label1);
            Controls.Add(DataGridViewTeas);
            Controls.Add(DataGridViewTeaTypes);
            Name = "Form1";
            Text = "TeaShop";
            Load += Form1_Load_1;
            ((System.ComponentModel.ISupportInitialize)DataGridViewTeaTypes).EndInit();
            ((System.ComponentModel.ISupportInitialize)DataGridViewTeas).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        private void DataGridViewTeas_SelectionChanged1(object sender, EventArgs e)
        {
            throw new NotImplementedException();
        }

        #endregion

        private DataGridView DataGridViewTeaTypes;
        private DataGridView DataGridViewTeas;
        private Label label1;
        private Label label2;
        private Label label3;
        private TextBox textBoxTeaId;
        private Label label4;
        private Label label5;
        private Label label6;
        private Label label7;
        private Label label8;
        private TextBox textBoxTeaTypeId;
        private TextBox textBoxName;
        private TextBox textBoxQuantity;
        private TextBox textBoxPrice;
        private TextBox textBoxDistributorId;
        private Button buttonAdd;
        private Button buttonRemove;
        private Button buttonUpdate;
    }
}