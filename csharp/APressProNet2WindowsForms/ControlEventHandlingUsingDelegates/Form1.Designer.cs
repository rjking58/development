using System.Windows.Forms;

namespace ControlEventHandlingUsingDelegates
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        private TextBox tb;
        private TextBox ntb; // implement as a delegated event.


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
            this.tb = new System.Windows.Forms.TextBox();
            this.ntb = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // tb
            // 
            this.tb.Location = new System.Drawing.Point(40, 40);
            this.tb.Name = "tb";
            this.tb.Size = new System.Drawing.Size(200, 20);
            this.tb.TabIndex = 1;
            this.tb.Text = "txtSimpleBox";
            // 
            // ntb
            // 
            this.ntb.Location = new System.Drawing.Point(40, 80);
            this.ntb.Name = "ntb";
            this.ntb.Size = new System.Drawing.Size(200, 20);
            this.ntb.TabIndex = 2;
            this.ntb.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.numeric_TextBox_KeyPress);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(392, 362);
            this.Controls.Add(this.tb);
            this.Controls.Add(this.ntb);
            this.Name = "Form1";
            this.Text = "Control Event Handling Using Delegates";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion


    }
}

