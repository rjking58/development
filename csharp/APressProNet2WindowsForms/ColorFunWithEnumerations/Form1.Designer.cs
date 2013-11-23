namespace ColorFunWithEnumerations
{
    partial class ColorChooser
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
            this.lstColors = new System.Windows.Forms.ListBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.txtbox_brightness = new System.Windows.Forms.TextBox();
            this.txtbox_hue = new System.Windows.Forms.TextBox();
            this.txtbox_saturation = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.txtbox_blue = new System.Windows.Forms.TextBox();
            this.txtbox_green = new System.Windows.Forms.TextBox();
            this.txtbox_red = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // lstColors
            // 
            this.lstColors.FormattingEnabled = true;
            this.lstColors.Location = new System.Drawing.Point(26, 23);
            this.lstColors.Name = "lstColors";
            this.lstColors.Size = new System.Drawing.Size(134, 459);
            this.lstColors.TabIndex = 0;
            this.lstColors.SelectedIndexChanged += new System.EventHandler(this.lstColors_SelectedIndexChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(187, 29);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(56, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "Brightness";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(216, 63);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(27, 13);
            this.label2.TabIndex = 3;
            this.label2.Text = "Hue";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(190, 97);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(53, 13);
            this.label3.TabIndex = 5;
            this.label3.Text = "saturation";
            // 
            // txtbox_brightness
            // 
            this.txtbox_brightness.Location = new System.Drawing.Point(266, 26);
            this.txtbox_brightness.Name = "txtbox_brightness";
            this.txtbox_brightness.Size = new System.Drawing.Size(89, 20);
            this.txtbox_brightness.TabIndex = 6;
            // 
            // txtbox_hue
            // 
            this.txtbox_hue.Location = new System.Drawing.Point(266, 60);
            this.txtbox_hue.Name = "txtbox_hue";
            this.txtbox_hue.Size = new System.Drawing.Size(89, 20);
            this.txtbox_hue.TabIndex = 7;
            // 
            // txtbox_saturation
            // 
            this.txtbox_saturation.Location = new System.Drawing.Point(266, 94);
            this.txtbox_saturation.Name = "txtbox_saturation";
            this.txtbox_saturation.Size = new System.Drawing.Size(89, 20);
            this.txtbox_saturation.TabIndex = 8;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(221, 131);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(22, 13);
            this.label4.TabIndex = 9;
            this.label4.Text = "red";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(209, 165);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(34, 13);
            this.label5.TabIndex = 10;
            this.label5.Text = "green";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(216, 199);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(27, 13);
            this.label6.TabIndex = 11;
            this.label6.Text = "blue";
            // 
            // txtbox_blue
            // 
            this.txtbox_blue.Location = new System.Drawing.Point(266, 196);
            this.txtbox_blue.Name = "txtbox_blue";
            this.txtbox_blue.Size = new System.Drawing.Size(89, 20);
            this.txtbox_blue.TabIndex = 12;
            // 
            // txtbox_green
            // 
            this.txtbox_green.Location = new System.Drawing.Point(266, 162);
            this.txtbox_green.Name = "txtbox_green";
            this.txtbox_green.Size = new System.Drawing.Size(89, 20);
            this.txtbox_green.TabIndex = 13;
            // 
            // txtbox_red
            // 
            this.txtbox_red.Location = new System.Drawing.Point(266, 128);
            this.txtbox_red.Name = "txtbox_red";
            this.txtbox_red.Size = new System.Drawing.Size(89, 20);
            this.txtbox_red.TabIndex = 14;
            // 
            // ColorChooser
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(418, 500);
            this.Controls.Add(this.txtbox_red);
            this.Controls.Add(this.txtbox_green);
            this.Controls.Add(this.txtbox_blue);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.txtbox_saturation);
            this.Controls.Add(this.txtbox_hue);
            this.Controls.Add(this.txtbox_brightness);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.lstColors);
            this.Name = "ColorChooser";
            this.Text = "Color Chooser";
            this.Load += new System.EventHandler(this.ColorChooser_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ListBox lstColors;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox txtbox_brightness;
        private System.Windows.Forms.TextBox txtbox_hue;
        private System.Windows.Forms.TextBox txtbox_saturation;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox txtbox_blue;
        private System.Windows.Forms.TextBox txtbox_green;
        private System.Windows.Forms.TextBox txtbox_red;
    }
}

