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
            DataGridViewParent = new DataGridView();
            DataGridViewChild = new DataGridView();
            parentLabel = new Label();
            childLabel = new Label();
            button1 = new Button();
            ((System.ComponentModel.ISupportInitialize)DataGridViewParent).BeginInit();
            ((System.ComponentModel.ISupportInitialize)DataGridViewChild).BeginInit();
            SuspendLayout();
            // 
            // DataGridViewParent
            // 
            DataGridViewParent.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            DataGridViewParent.Location = new Point(22, 41);
            DataGridViewParent.Name = "DataGridViewParent";
            DataGridViewParent.RowHeadersWidth = 62;
            DataGridViewParent.RowTemplate.Height = 33;
            DataGridViewParent.SelectionMode = DataGridViewSelectionMode.ColumnHeaderSelect;
            DataGridViewParent.Size = new Size(569, 225);
            DataGridViewParent.TabIndex = 0;
            DataGridViewParent.SelectionChanged += DataGridViewParent_SelectionChanged;
            // 
            // DataGridViewChild
            // 
            DataGridViewChild.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            DataGridViewChild.Location = new Point(22, 311);
            DataGridViewChild.Name = "DataGridViewChild";
            DataGridViewChild.RowHeadersWidth = 62;
            DataGridViewChild.RowTemplate.Height = 33;
            DataGridViewChild.Size = new Size(891, 225);
            DataGridViewChild.TabIndex = 1;
            DataGridViewChild.DataError += DataGridViewChild_DataError;
            // 
            // parentLabel
            // 
            parentLabel.AutoSize = true;
            parentLabel.Location = new Point(22, 9);
            parentLabel.Name = "parentLabel";
            parentLabel.Size = new Size(61, 25);
            parentLabel.TabIndex = 2;
            parentLabel.Text = "Parent";
            // 
            // childLabel
            // 
            childLabel.AutoSize = true;
            childLabel.Location = new Point(22, 283);
            childLabel.Name = "childLabel";
            childLabel.Size = new Size(52, 25);
            childLabel.TabIndex = 3;
            childLabel.Text = "Child";
            // 
            // button1
            // 
            button1.Location = new Point(801, 50);
            button1.Name = "button1";
            button1.Size = new Size(112, 34);
            button1.TabIndex = 4;
            button1.Text = "update";
            button1.UseVisualStyleBackColor = true;
            button1.Click += button1_Click;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(10F, 25F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(986, 548);
            Controls.Add(button1);
            Controls.Add(childLabel);
            Controls.Add(parentLabel);
            Controls.Add(DataGridViewChild);
            Controls.Add(DataGridViewParent);
            Name = "Form1";
            Text = "TeaShop";
            Load += Form1_Load_1;
            ((System.ComponentModel.ISupportInitialize)DataGridViewParent).EndInit();
            ((System.ComponentModel.ISupportInitialize)DataGridViewChild).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private DataGridView DataGridViewParent;
        private DataGridView DataGridViewChild;
        private Label parentLabel;
        private Label childLabel;
        private Button button1;
    }
}