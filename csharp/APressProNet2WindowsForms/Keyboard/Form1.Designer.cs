namespace Keyboard
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
            this.lstbox_formmessages = new System.Windows.Forms.ListBox();
            this.SuspendLayout();
            // 
            // lstbox_formmessages
            // 
            this.lstbox_formmessages.FormattingEnabled = true;
            this.lstbox_formmessages.Location = new System.Drawing.Point(35, 27);
            this.lstbox_formmessages.Name = "lstbox_formmessages";
            this.lstbox_formmessages.Size = new System.Drawing.Size(648, 446);
            this.lstbox_formmessages.TabIndex = 0;
            this.lstbox_formmessages.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.lstboxFrmMsgs_KeyPress);
            this.lstbox_formmessages.KeyDown += new System.Windows.Forms.KeyEventHandler(this.lstboxFrmMsgs_KeyDown);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(752, 493);
            this.Controls.Add(this.lstbox_formmessages);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ListBox lstbox_formmessages;

    }
}

