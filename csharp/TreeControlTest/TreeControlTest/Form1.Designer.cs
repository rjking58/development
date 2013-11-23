namespace TreeControlTest
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
            this.components = new System.ComponentModel.Container();
            this.tree_View1 = new System.Windows.Forms.TreeView();
            this.contextMenu_Tree1 = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.validateSubtreeToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.tb_result = new System.Windows.Forms.TextBox();
            this.contextMenu_Tree1.SuspendLayout();
            this.SuspendLayout();
            // 
            // tree_View1
            // 
            this.tree_View1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tree_View1.Location = new System.Drawing.Point(13, 12);
            this.tree_View1.Name = "tree_View1";
            this.tree_View1.Size = new System.Drawing.Size(163, 516);
            this.tree_View1.TabIndex = 0;
            this.tree_View1.AfterSelect += new System.Windows.Forms.TreeViewEventHandler(this.tree_View1_AfterSelect);
            this.tree_View1.MouseUp += new System.Windows.Forms.MouseEventHandler(this.tree_View1_MouseUp);
            // 
            // contextMenu_Tree1
            // 
            this.contextMenu_Tree1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.validateSubtreeToolStripMenuItem});
            this.contextMenu_Tree1.Name = "contextMenu_Tree1";
            this.contextMenu_Tree1.Size = new System.Drawing.Size(159, 26);
            // 
            // validateSubtreeToolStripMenuItem
            // 
            this.validateSubtreeToolStripMenuItem.Name = "validateSubtreeToolStripMenuItem";
            this.validateSubtreeToolStripMenuItem.Size = new System.Drawing.Size(158, 22);
            this.validateSubtreeToolStripMenuItem.Text = "Validate subtree";
            this.validateSubtreeToolStripMenuItem.Click += new System.EventHandler(this.validateSubtreeToolStripMenuItem_Click);
            // 
            // tb_result
            // 
            this.tb_result.Location = new System.Drawing.Point(198, 12);
            this.tb_result.Multiline = true;
            this.tb_result.Name = "tb_result";
            this.tb_result.ReadOnly = true;
            this.tb_result.Size = new System.Drawing.Size(144, 392);
            this.tb_result.TabIndex = 2;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(415, 540);
            this.Controls.Add(this.tb_result);
            this.Controls.Add(this.tree_View1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.contextMenu_Tree1.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TreeView tree_View1;
        private System.Windows.Forms.ContextMenuStrip contextMenu_Tree1;
        private System.Windows.Forms.ToolStripMenuItem validateSubtreeToolStripMenuItem;
        private System.Windows.Forms.TextBox tb_result;
    }
}

