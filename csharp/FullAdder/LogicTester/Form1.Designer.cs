namespace LogicTester
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
            this.inputA_cb = new System.Windows.Forms.CheckBox();
            this.inputB_cb = new System.Windows.Forms.CheckBox();
            this.output_light_sum_txtbox = new System.Windows.Forms.TextBox();
            this.ClockSignal_btn = new System.Windows.Forms.Button();
            this.inputCarry_cb = new System.Windows.Forms.CheckBox();
            this.output_light_carry_txtbox = new System.Windows.Forms.TextBox();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // inputA_cb
            // 
            this.inputA_cb.AutoSize = true;
            this.inputA_cb.Location = new System.Drawing.Point(33, 55);
            this.inputA_cb.Name = "inputA_cb";
            this.inputA_cb.Size = new System.Drawing.Size(60, 17);
            this.inputA_cb.TabIndex = 0;
            this.inputA_cb.Text = "Input A";
            this.inputA_cb.UseVisualStyleBackColor = true;
            this.inputA_cb.CheckedChanged += new System.EventHandler(this.inputA_cb_CheckedChanged);
            // 
            // inputB_cb
            // 
            this.inputB_cb.AutoSize = true;
            this.inputB_cb.Location = new System.Drawing.Point(33, 72);
            this.inputB_cb.Name = "inputB_cb";
            this.inputB_cb.Size = new System.Drawing.Size(60, 17);
            this.inputB_cb.TabIndex = 1;
            this.inputB_cb.Text = "Input B";
            this.inputB_cb.UseVisualStyleBackColor = true;
            this.inputB_cb.CheckedChanged += new System.EventHandler(this.inputB_cb_CheckedChanged);
            // 
            // output_light_sum_txtbox
            // 
            this.output_light_sum_txtbox.BackColor = System.Drawing.Color.Red;
            this.output_light_sum_txtbox.Location = new System.Drawing.Point(515, 79);
            this.output_light_sum_txtbox.Name = "output_light_sum_txtbox";
            this.output_light_sum_txtbox.ReadOnly = true;
            this.output_light_sum_txtbox.Size = new System.Drawing.Size(58, 20);
            this.output_light_sum_txtbox.TabIndex = 2;
            this.output_light_sum_txtbox.Text = "SUM";
            // 
            // ClockSignal_btn
            // 
            this.ClockSignal_btn.Location = new System.Drawing.Point(265, 12);
            this.ClockSignal_btn.Name = "ClockSignal_btn";
            this.ClockSignal_btn.Size = new System.Drawing.Size(75, 23);
            this.ClockSignal_btn.TabIndex = 3;
            this.ClockSignal_btn.Text = "ClockSignal";
            this.ClockSignal_btn.UseVisualStyleBackColor = true;
            this.ClockSignal_btn.Click += new System.EventHandler(this.ClockSignal_btn_Click);
            // 
            // inputCarry_cb
            // 
            this.inputCarry_cb.AutoSize = true;
            this.inputCarry_cb.Location = new System.Drawing.Point(33, 92);
            this.inputCarry_cb.Name = "inputCarry_cb";
            this.inputCarry_cb.Size = new System.Drawing.Size(50, 17);
            this.inputCarry_cb.TabIndex = 4;
            this.inputCarry_cb.Text = "Carry";
            this.inputCarry_cb.UseVisualStyleBackColor = true;
            this.inputCarry_cb.CheckedChanged += new System.EventHandler(this.inputCarry_cb_CheckedChanged);
            // 
            // output_light_carry_txtbox
            // 
            this.output_light_carry_txtbox.BackColor = System.Drawing.Color.Red;
            this.output_light_carry_txtbox.Location = new System.Drawing.Point(515, 158);
            this.output_light_carry_txtbox.Name = "output_light_carry_txtbox";
            this.output_light_carry_txtbox.ReadOnly = true;
            this.output_light_carry_txtbox.Size = new System.Drawing.Size(58, 20);
            this.output_light_carry_txtbox.TabIndex = 5;
            this.output_light_carry_txtbox.Text = "CARRY";
            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = global::LogicTester.Properties.Resources._400px_Full_Adder_svg;
            this.pictureBox1.Location = new System.Drawing.Point(99, 41);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(410, 184);
            this.pictureBox1.TabIndex = 6;
            this.pictureBox1.TabStop = false;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(655, 267);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.output_light_carry_txtbox);
            this.Controls.Add(this.inputCarry_cb);
            this.Controls.Add(this.ClockSignal_btn);
            this.Controls.Add(this.output_light_sum_txtbox);
            this.Controls.Add(this.inputB_cb);
            this.Controls.Add(this.inputA_cb);
            this.Name = "Form1";
            this.Text = "Full Adder Demo";
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.CheckBox inputA_cb;
        private System.Windows.Forms.CheckBox inputB_cb;
        private System.Windows.Forms.TextBox output_light_sum_txtbox;
        private System.Windows.Forms.Button ClockSignal_btn;
        private System.Windows.Forms.CheckBox inputCarry_cb;
        private System.Windows.Forms.TextBox output_light_carry_txtbox;
        private System.Windows.Forms.PictureBox pictureBox1;
    }
}

