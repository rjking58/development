namespace Chap2MouseCursorDemo
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
            this.btn_WaitCursor = new System.Windows.Forms.Button();
            this.btn_DefaultCursor = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // btn_WaitCursor
            // 
            this.btn_WaitCursor.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btn_WaitCursor.Location = new System.Drawing.Point(12, 219);
            this.btn_WaitCursor.Name = "btn_WaitCursor";
            this.btn_WaitCursor.Size = new System.Drawing.Size(73, 26);
            this.btn_WaitCursor.TabIndex = 0;
            this.btn_WaitCursor.Text = "&Wait Cursor";
            this.btn_WaitCursor.UseVisualStyleBackColor = true;
            this.btn_WaitCursor.Click += new System.EventHandler(this.btn_WaitCursor_Click);
            // 
            // btn_DefaultCursor
            // 
            this.btn_DefaultCursor.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btn_DefaultCursor.Location = new System.Drawing.Point(207, 219);
            this.btn_DefaultCursor.Name = "btn_DefaultCursor";
            this.btn_DefaultCursor.Size = new System.Drawing.Size(73, 26);
            this.btn_DefaultCursor.TabIndex = 1;
            this.btn_DefaultCursor.Text = "&Default Cursor";
            this.btn_DefaultCursor.UseVisualStyleBackColor = true;
            this.btn_DefaultCursor.Click += new System.EventHandler(this.btn_DefaultCursor_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(292, 266);
            this.Controls.Add(this.btn_DefaultCursor);
            this.Controls.Add(this.btn_WaitCursor);
            this.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button btn_WaitCursor;
        private System.Windows.Forms.Button btn_DefaultCursor;
    }
}

