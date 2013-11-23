namespace MultiControlEventHandler
{
    partial class Form1
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
            if (disposing && (components != null))
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
            this.mceh_Button1 = new System.Windows.Forms.Button();
            this.mceh_textBox1 = new System.Windows.Forms.TextBox();
            this.mceh_label1 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // mceh_Button1
            // 
            this.mceh_Button1.Location = new System.Drawing.Point(49, 63);
            this.mceh_Button1.Name = "mceh_Button1";
            this.mceh_Button1.Size = new System.Drawing.Size(109, 29);
            this.mceh_Button1.TabIndex = 0;
            this.mceh_Button1.Text = "mceh_Button1";
            this.mceh_Button1.UseVisualStyleBackColor = true;
            this.mceh_Button1.Click += new System.EventHandler(this.mceh_OnClick);
            // 
            // mceh_textBox1
            // 
            this.mceh_textBox1.Location = new System.Drawing.Point(50, 113);
            this.mceh_textBox1.Name = "mceh_textBox1";
            this.mceh_textBox1.Size = new System.Drawing.Size(108, 20);
            this.mceh_textBox1.TabIndex = 1;
            this.mceh_textBox1.Text = "mceh_textBox1";
            this.mceh_textBox1.Click += new System.EventHandler(this.mceh_OnClick);
            // 
            // mceh_label1
            // 
            this.mceh_label1.AutoSize = true;
            this.mceh_label1.Location = new System.Drawing.Point(47, 155);
            this.mceh_label1.Name = "mceh_label1";
            this.mceh_label1.Size = new System.Drawing.Size(67, 13);
            this.mceh_label1.TabIndex = 2;
            this.mceh_label1.Text = "mceh_label1";
            this.mceh_label1.Click += new System.EventHandler(this.mceh_OnClick);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(30, 29);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(155, 13);
            this.label1.TabIndex = 3;
            this.label1.Text = "Click one of the controls below:";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(564, 262);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.mceh_label1);
            this.Controls.Add(this.mceh_textBox1);
            this.Controls.Add(this.mceh_Button1);
            this.Name = "Form1";
            this.Text = "MultiControl Event Hander";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button mceh_Button1;
        private System.Windows.Forms.TextBox mceh_textBox1;
        private System.Windows.Forms.Label mceh_label1;
        private System.Windows.Forms.Label label1;
    }
}

