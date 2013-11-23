namespace MutexGrabber
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
            this.lbl_MutexState = new System.Windows.Forms.Label();
            this.btn_Acquire = new System.Windows.Forms.Button();
            this.btn_Release = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // lbl_MutexState
            // 
            this.lbl_MutexState.AutoSize = true;
            this.lbl_MutexState.Location = new System.Drawing.Point(14,18);
            this.lbl_MutexState.Name = "lbl_MutexState";
            this.lbl_MutexState.Size = new System.Drawing.Size(66,13);
            this.lbl_MutexState.TabIndex = 0;
            this.lbl_MutexState.Text = "not acquired";
            // 
            // btn_Acquire
            // 
            this.btn_Acquire.Location = new System.Drawing.Point(12,62);
            this.btn_Acquire.Name = "btn_Acquire";
            this.btn_Acquire.Size = new System.Drawing.Size(78,23);
            this.btn_Acquire.TabIndex = 1;
            this.btn_Acquire.Text = "Acquire";
            this.btn_Acquire.UseVisualStyleBackColor = true;
            this.btn_Acquire.Click += new System.EventHandler(this.btn_Acquire_Click);
            // 
            // btn_Release
            // 
            this.btn_Release.Location = new System.Drawing.Point(12,105);
            this.btn_Release.Name = "btn_Release";
            this.btn_Release.Size = new System.Drawing.Size(78,23);
            this.btn_Release.TabIndex = 2;
            this.btn_Release.Text = "Release";
            this.btn_Release.UseVisualStyleBackColor = true;
            this.btn_Release.Click += new System.EventHandler(this.btn_Release_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F,13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(115,179);
            this.Controls.Add(this.btn_Release);
            this.Controls.Add(this.btn_Acquire);
            this.Controls.Add(this.lbl_MutexState);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label lbl_MutexState;
        private System.Windows.Forms.Button btn_Acquire;
        private System.Windows.Forms.Button btn_Release;
    }
}

