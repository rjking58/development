namespace FontViewer
{
    partial class FontViewer
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
            this.lstInstalledfonts = new System.Windows.Forms.ListBox();
            this.lblFontdisplay = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // lstInstalledfonts
            // 
            this.lstInstalledfonts.FormattingEnabled = true;
            this.lstInstalledfonts.Location = new System.Drawing.Point(14, 14);
            this.lstInstalledfonts.Name = "lstInstalledfonts";
            this.lstInstalledfonts.Size = new System.Drawing.Size(147, 381);
            this.lstInstalledfonts.TabIndex = 0;
            this.lstInstalledfonts.SelectedIndexChanged += new System.EventHandler(this.lstInstalledfonts_SelectedIndexChanged);
            // 
            // lblFontdisplay
            // 
            this.lblFontdisplay.AutoSize = true;
            this.lblFontdisplay.Font = new System.Drawing.Font("Microsoft Sans Serif", 14F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblFontdisplay.Location = new System.Drawing.Point(208, 117);
            this.lblFontdisplay.Name = "lblFontdisplay";
            this.lblFontdisplay.Size = new System.Drawing.Size(60, 24);
            this.lblFontdisplay.TabIndex = 1;
            this.lblFontdisplay.Text = "label1";
            // 
            // FontViewer
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(783, 420);
            this.Controls.Add(this.lblFontdisplay);
            this.Controls.Add(this.lstInstalledfonts);
            this.Name = "FontViewer";
            this.Text = "Font Viewer";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ListBox lstInstalledfonts;
        private System.Windows.Forms.Label lblFontdisplay;
    }
}

