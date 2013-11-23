namespace Chap2ControlAccessKey
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
            this.btn_toggle = new System.Windows.Forms.Button();
            this.lbl_toggleResult = new System.Windows.Forms.Label();
            this.btn_Controlled = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // btn_toggle
            // 
            this.btn_toggle.Location = new System.Drawing.Point(28, 32);
            this.btn_toggle.Name = "btn_toggle";
            this.btn_toggle.Size = new System.Drawing.Size(109, 24);
            this.btn_toggle.TabIndex = 0;
            this.btn_toggle.Text = "&Toggle";
            this.btn_toggle.UseVisualStyleBackColor = true;
            this.btn_toggle.Click += new System.EventHandler(this.btn_toggle_Click);
            // 
            // lbl_toggleResult
            // 
            this.lbl_toggleResult.AutoSize = true;
            this.lbl_toggleResult.Location = new System.Drawing.Point(25, 72);
            this.lbl_toggleResult.Name = "lbl_toggleResult";
            this.lbl_toggleResult.Size = new System.Drawing.Size(35, 13);
            this.lbl_toggleResult.TabIndex = 1;
            this.lbl_toggleResult.Text = "label1";
            // 
            // btn_Controlled
            // 
            this.btn_Controlled.Enabled = false;
            this.btn_Controlled.Location = new System.Drawing.Point(165, 33);
            this.btn_Controlled.Name = "btn_Controlled";
            this.btn_Controlled.Size = new System.Drawing.Size(110, 22);
            this.btn_Controlled.TabIndex = 2;
            this.btn_Controlled.Text = "Controlled";
            this.btn_Controlled.UseVisualStyleBackColor = true;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(292, 114);
            this.Controls.Add(this.btn_Controlled);
            this.Controls.Add(this.lbl_toggleResult);
            this.Controls.Add(this.btn_toggle);
            this.Name = "Form1";
            this.Text = "Access Key Demo";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btn_toggle;
        private System.Windows.Forms.Label lbl_toggleResult;
        private System.Windows.Forms.Button btn_Controlled;
    }
}

