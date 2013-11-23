namespace ListViewTesting
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
            this.listView1 = new System.Windows.Forms.ListView();
            this.optLargeIcon = new System.Windows.Forms.RadioButton();
            this.optSmallIcon = new System.Windows.Forms.RadioButton();
            this.optDetails = new System.Windows.Forms.RadioButton();
            this.optList = new System.Windows.Forms.RadioButton();
            this.optTile = new System.Windows.Forms.RadioButton();
            this.SuspendLayout();
            // 
            // listView1
            // 
            this.listView1.Location = new System.Drawing.Point(25,19);
            this.listView1.Name = "listView1";
            this.listView1.Size = new System.Drawing.Size(437,353);
            this.listView1.TabIndex = 0;
            this.listView1.UseCompatibleStateImageBehavior = false;
            this.listView1.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler(this.listView1_MouseDoubleClick);
            // 
            // optLargeIcon
            // 
            this.optLargeIcon.AutoSize = true;
            this.optLargeIcon.Location = new System.Drawing.Point(486,44);
            this.optLargeIcon.Name = "optLargeIcon";
            this.optLargeIcon.Size = new System.Drawing.Size(81,17);
            this.optLargeIcon.TabIndex = 1;
            this.optLargeIcon.TabStop = true;
            this.optLargeIcon.Tag = "";
            this.optLargeIcon.Text = "Large Icons";
            this.optLargeIcon.UseVisualStyleBackColor = true;
            this.optLargeIcon.Click += new System.EventHandler(this.NewView);
            // 
            // optSmallIcon
            // 
            this.optSmallIcon.AutoSize = true;
            this.optSmallIcon.Location = new System.Drawing.Point(486,67);
            this.optSmallIcon.Name = "optSmallIcon";
            this.optSmallIcon.Size = new System.Drawing.Size(79,17);
            this.optSmallIcon.TabIndex = 2;
            this.optSmallIcon.TabStop = true;
            this.optSmallIcon.Tag = "";
            this.optSmallIcon.Text = "Small Icons";
            this.optSmallIcon.UseVisualStyleBackColor = true;
            this.optSmallIcon.Click += new System.EventHandler(this.NewView);
            // 
            // optDetails
            // 
            this.optDetails.AutoSize = true;
            this.optDetails.Location = new System.Drawing.Point(486,90);
            this.optDetails.Name = "optDetails";
            this.optDetails.Size = new System.Drawing.Size(57,17);
            this.optDetails.TabIndex = 3;
            this.optDetails.TabStop = true;
            this.optDetails.Tag = "";
            this.optDetails.Text = "Details";
            this.optDetails.UseVisualStyleBackColor = true;
            this.optDetails.Click += new System.EventHandler(this.NewView);
            // 
            // optList
            // 
            this.optList.AutoSize = true;
            this.optList.Location = new System.Drawing.Point(486,113);
            this.optList.Name = "optList";
            this.optList.Size = new System.Drawing.Size(66,17);
            this.optList.TabIndex = 4;
            this.optList.TabStop = true;
            this.optList.Tag = "";
            this.optList.Text = "List view";
            this.optList.UseVisualStyleBackColor = true;
            this.optList.Click += new System.EventHandler(this.NewView);
            // 
            // optTile
            // 
            this.optTile.AutoSize = true;
            this.optTile.Location = new System.Drawing.Point(486,136);
            this.optTile.Name = "optTile";
            this.optTile.Size = new System.Drawing.Size(67,17);
            this.optTile.TabIndex = 5;
            this.optTile.TabStop = true;
            this.optTile.Tag = "";
            this.optTile.Text = "Tile view";
            this.optTile.UseVisualStyleBackColor = true;
            this.optTile.Click += new System.EventHandler(this.NewView);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F,13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(684,400);
            this.Controls.Add(this.optTile);
            this.Controls.Add(this.optList);
            this.Controls.Add(this.optDetails);
            this.Controls.Add(this.optSmallIcon);
            this.Controls.Add(this.optLargeIcon);
            this.Controls.Add(this.listView1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ListView listView1;
        private System.Windows.Forms.RadioButton optLargeIcon;
        private System.Windows.Forms.RadioButton optSmallIcon;
        private System.Windows.Forms.RadioButton optDetails;
        private System.Windows.Forms.RadioButton optList;
        private System.Windows.Forms.RadioButton optTile;
    }
}

