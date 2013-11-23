namespace ListViewTesting
{
    partial class EditSomeListViewDriver
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if(disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.txt_Name1 = new System.Windows.Forms.TextBox();
            this.txt_Name2 = new System.Windows.Forms.TextBox();
            this.txt_Name3 = new System.Windows.Forms.TextBox();
            this.btn_OK = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // txt_Name1
            // 
            this.txt_Name1.Location = new System.Drawing.Point(15,12);
            this.txt_Name1.Multiline = true;
            this.txt_Name1.Name = "txt_Name1";
            this.txt_Name1.Size = new System.Drawing.Size(259,48);
            this.txt_Name1.TabIndex = 0;
            this.txt_Name1.TextChanged += new System.EventHandler(this.txt_Name1_TextChanged);
            // 
            // txt_Name2
            // 
            this.txt_Name2.Location = new System.Drawing.Point(15,66);
            this.txt_Name2.Multiline = true;
            this.txt_Name2.Name = "txt_Name2";
            this.txt_Name2.Size = new System.Drawing.Size(259,48);
            this.txt_Name2.TabIndex = 1;
            this.txt_Name2.TextChanged += new System.EventHandler(this.txt_Name2_TextChanged);
            // 
            // txt_Name3
            // 
            this.txt_Name3.Location = new System.Drawing.Point(15,117);
            this.txt_Name3.Multiline = true;
            this.txt_Name3.Name = "txt_Name3";
            this.txt_Name3.Size = new System.Drawing.Size(259,48);
            this.txt_Name3.TabIndex = 2;
            this.txt_Name3.TextChanged += new System.EventHandler(this.txt_Name3_TextChanged);
            // 
            // btn_OK
            // 
            this.btn_OK.Location = new System.Drawing.Point(194,199);
            this.btn_OK.Name = "btn_OK";
            this.btn_OK.Size = new System.Drawing.Size(80,24);
            this.btn_OK.TabIndex = 3;
            this.btn_OK.Text = "OK";
            this.btn_OK.UseVisualStyleBackColor = true;
            this.btn_OK.Click += new System.EventHandler(this.btn_OK_Click);
            // 
            // EditSomeListViewDriver
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F,13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(286,235);
            this.Controls.Add(this.btn_OK);
            this.Controls.Add(this.txt_Name3);
            this.Controls.Add(this.txt_Name2);
            this.Controls.Add(this.txt_Name1);
            this.Name = "EditSomeListViewDriver";
            this.Text = "Form2";
            this.Load += new System.EventHandler(this.EditSomeListViewDriver_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox txt_Name1;
        private System.Windows.Forms.TextBox txt_Name2;
        private System.Windows.Forms.TextBox txt_Name3;
        private System.Windows.Forms.Button btn_OK;
    }
}