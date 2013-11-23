namespace ClipboardDemo
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
            this.btn_FromClipboard = new System.Windows.Forms.Button();
            this.btn_ToClipboard = new System.Windows.Forms.Button();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tab_csharp = new System.Windows.Forms.TabPage();
            this.tab_cpp = new System.Windows.Forms.TabPage();
            this.button1 = new System.Windows.Forms.Button();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.listBox1 = new System.Windows.Forms.ListBox();
            this.tab_python = new System.Windows.Forms.TabPage();
            this.tab_ruby = new System.Windows.Forms.TabPage();
            this.tab_java = new System.Windows.Forms.TabPage();
            this.textbox_cpp = new System.Windows.Forms.TextBox();
            this.textbox_python = new System.Windows.Forms.TextBox();
            this.textbox_ruby = new System.Windows.Forms.TextBox();
            this.textbox_java = new System.Windows.Forms.TextBox();
            this.textbox_csharp = new System.Windows.Forms.TextBox();
            this.tb_selectedTab = new System.Windows.Forms.TextBox();
            this.tabControl1.SuspendLayout();
            this.tab_csharp.SuspendLayout();
            this.tab_cpp.SuspendLayout();
            this.tab_python.SuspendLayout();
            this.tab_ruby.SuspendLayout();
            this.tab_java.SuspendLayout();
            this.SuspendLayout();
            // 
            // btn_FromClipboard
            // 
            this.btn_FromClipboard.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.btn_FromClipboard.Location = new System.Drawing.Point(514, 448);
            this.btn_FromClipboard.Name = "btn_FromClipboard";
            this.btn_FromClipboard.Size = new System.Drawing.Size(90, 23);
            this.btn_FromClipboard.TabIndex = 1;
            this.btn_FromClipboard.Text = "From Clipboard";
            this.btn_FromClipboard.UseVisualStyleBackColor = true;
            this.btn_FromClipboard.Click += new System.EventHandler(this.btn_FromClipboard_Click);
            // 
            // btn_ToClipboard
            // 
            this.btn_ToClipboard.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.btn_ToClipboard.Location = new System.Drawing.Point(610, 447);
            this.btn_ToClipboard.Name = "btn_ToClipboard";
            this.btn_ToClipboard.Size = new System.Drawing.Size(110, 23);
            this.btn_ToClipboard.TabIndex = 2;
            this.btn_ToClipboard.Text = "To Clipboard";
            this.btn_ToClipboard.UseVisualStyleBackColor = true;
            this.btn_ToClipboard.Click += new System.EventHandler(this.btn_ToClipboard_Click);
            // 
            // tabControl1
            // 
            this.tabControl1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.tabControl1.Controls.Add(this.tab_csharp);
            this.tabControl1.Controls.Add(this.tab_cpp);
            this.tabControl1.Controls.Add(this.tab_python);
            this.tabControl1.Controls.Add(this.tab_ruby);
            this.tabControl1.Controls.Add(this.tab_java);
            this.tabControl1.DrawMode = System.Windows.Forms.TabDrawMode.OwnerDrawFixed;
            this.tabControl1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tabControl1.Location = new System.Drawing.Point(124, 12);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(586, 408);
            this.tabControl1.TabIndex = 3;
            this.tabControl1.DrawItem += new System.Windows.Forms.DrawItemEventHandler(this.tabControl1_DrawItem);
            this.tabControl1.SelectedIndexChanged += new System.EventHandler(this.tabControl1_SelectedIndexChanged);
            // 
            // tab_csharp
            // 
            this.tab_csharp.BackColor = System.Drawing.Color.Transparent;
            this.tab_csharp.Controls.Add(this.textbox_csharp);
            this.tab_csharp.Font = new System.Drawing.Font("Lucida Console", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tab_csharp.ForeColor = System.Drawing.SystemColors.ControlText;
            this.tab_csharp.Location = new System.Drawing.Point(4, 22);
            this.tab_csharp.Name = "tab_csharp";
            this.tab_csharp.Padding = new System.Windows.Forms.Padding(3);
            this.tab_csharp.Size = new System.Drawing.Size(578, 382);
            this.tab_csharp.TabIndex = 0;
            this.tab_csharp.Text = "C#";
            this.tab_csharp.UseVisualStyleBackColor = true;
            // 
            // tab_cpp
            // 
            this.tab_cpp.Controls.Add(this.textbox_cpp);
            this.tab_cpp.Font = new System.Drawing.Font("Lucida Console", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tab_cpp.Location = new System.Drawing.Point(4, 22);
            this.tab_cpp.Name = "tab_cpp";
            this.tab_cpp.Size = new System.Drawing.Size(578, 382);
            this.tab_cpp.TabIndex = 1;
            this.tab_cpp.Text = "C++";
            this.tab_cpp.UseVisualStyleBackColor = true;
            // 
            // button1
            // 
            this.button1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.button1.Location = new System.Drawing.Point(128, 449);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(90, 23);
            this.button1.TabIndex = 4;
            this.button1.Text = "AddTab";
            this.button1.UseVisualStyleBackColor = true;
            // 
            // textBox1
            // 
            this.textBox1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.textBox1.Location = new System.Drawing.Point(18, 449);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(100, 20);
            this.textBox1.TabIndex = 5;
            // 
            // listBox1
            // 
            this.listBox1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)));
            this.listBox1.FormattingEnabled = true;
            this.listBox1.Location = new System.Drawing.Point(3, 41);
            this.listBox1.Name = "listBox1";
            this.listBox1.Size = new System.Drawing.Size(115, 381);
            this.listBox1.TabIndex = 6;
            this.listBox1.SelectedIndexChanged += new System.EventHandler(this.listBox1_SelectedIndexChanged);
            // 
            // tab_python
            // 
            this.tab_python.Controls.Add(this.textbox_python);
            this.tab_python.Font = new System.Drawing.Font("Lucida Console", 9.75F);
            this.tab_python.Location = new System.Drawing.Point(4, 22);
            this.tab_python.Name = "tab_python";
            this.tab_python.Size = new System.Drawing.Size(578, 382);
            this.tab_python.TabIndex = 2;
            this.tab_python.Text = "Python";
            this.tab_python.UseVisualStyleBackColor = true;
            // 
            // tab_ruby
            // 
            this.tab_ruby.Controls.Add(this.textbox_ruby);
            this.tab_ruby.Font = new System.Drawing.Font("Lucida Console", 9.75F);
            this.tab_ruby.Location = new System.Drawing.Point(4, 22);
            this.tab_ruby.Name = "tab_ruby";
            this.tab_ruby.Size = new System.Drawing.Size(578, 382);
            this.tab_ruby.TabIndex = 3;
            this.tab_ruby.Text = "Ruby";
            this.tab_ruby.UseVisualStyleBackColor = true;
            // 
            // tab_java
            // 
            this.tab_java.Controls.Add(this.textbox_java);
            this.tab_java.Font = new System.Drawing.Font("Lucida Console", 9.75F);
            this.tab_java.Location = new System.Drawing.Point(4, 22);
            this.tab_java.Name = "tab_java";
            this.tab_java.Size = new System.Drawing.Size(578, 382);
            this.tab_java.TabIndex = 4;
            this.tab_java.Text = "Java";
            this.tab_java.UseVisualStyleBackColor = true;
            // 
            // textbox_cpp
            // 
            this.textbox_cpp.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.textbox_cpp.Location = new System.Drawing.Point(0, 0);
            this.textbox_cpp.Multiline = true;
            this.textbox_cpp.Name = "textbox_cpp";
            this.textbox_cpp.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.textbox_cpp.Size = new System.Drawing.Size(575, 382);
            this.textbox_cpp.TabIndex = 0;
            this.textbox_cpp.WordWrap = false;
            // 
            // textbox_python
            // 
            this.textbox_python.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.textbox_python.Location = new System.Drawing.Point(0, 0);
            this.textbox_python.Multiline = true;
            this.textbox_python.Name = "textbox_python";
            this.textbox_python.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.textbox_python.Size = new System.Drawing.Size(578, 382);
            this.textbox_python.TabIndex = 1;
            this.textbox_python.WordWrap = false;
            // 
            // textbox_ruby
            // 
            this.textbox_ruby.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.textbox_ruby.Location = new System.Drawing.Point(0, 0);
            this.textbox_ruby.Multiline = true;
            this.textbox_ruby.Name = "textbox_ruby";
            this.textbox_ruby.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.textbox_ruby.Size = new System.Drawing.Size(578, 382);
            this.textbox_ruby.TabIndex = 1;
            this.textbox_ruby.WordWrap = false;
            // 
            // textbox_java
            // 
            this.textbox_java.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.textbox_java.Location = new System.Drawing.Point(0, 0);
            this.textbox_java.Multiline = true;
            this.textbox_java.Name = "textbox_java";
            this.textbox_java.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.textbox_java.Size = new System.Drawing.Size(578, 382);
            this.textbox_java.TabIndex = 1;
            this.textbox_java.WordWrap = false;
            this.textbox_java.TextChanged += new System.EventHandler(this.textBox6_TextChanged);
            // 
            // textbox_csharp
            // 
            this.textbox_csharp.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.textbox_csharp.Location = new System.Drawing.Point(0, 0);
            this.textbox_csharp.Multiline = true;
            this.textbox_csharp.Name = "textbox_csharp";
            this.textbox_csharp.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.textbox_csharp.Size = new System.Drawing.Size(578, 382);
            this.textbox_csharp.TabIndex = 1;
            this.textbox_csharp.WordWrap = false;
            this.textbox_csharp.TextChanged += new System.EventHandler(this.textBox3_TextChanged);
            // 
            // tb_selectedTab
            // 
            this.tb_selectedTab.Location = new System.Drawing.Point(408, 449);
            this.tb_selectedTab.Name = "tb_selectedTab";
            this.tb_selectedTab.Size = new System.Drawing.Size(100, 20);
            this.tb_selectedTab.TabIndex = 7;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(722, 482);
            this.Controls.Add(this.tb_selectedTab);
            this.Controls.Add(this.listBox1);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.tabControl1);
            this.Controls.Add(this.btn_ToClipboard);
            this.Controls.Add(this.btn_FromClipboard);
            this.Name = "Form1";
            this.Text = "Clipboard Copy Demo";
            this.tabControl1.ResumeLayout(false);
            this.tab_csharp.ResumeLayout(false);
            this.tab_csharp.PerformLayout();
            this.tab_cpp.ResumeLayout(false);
            this.tab_cpp.PerformLayout();
            this.tab_python.ResumeLayout(false);
            this.tab_python.PerformLayout();
            this.tab_ruby.ResumeLayout(false);
            this.tab_ruby.PerformLayout();
            this.tab_java.ResumeLayout(false);
            this.tab_java.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btn_FromClipboard;
        private System.Windows.Forms.Button btn_ToClipboard;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tab_csharp;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.TabPage tab_cpp;
        private System.Windows.Forms.ListBox listBox1;
        private System.Windows.Forms.TabPage tab_python;
        private System.Windows.Forms.TabPage tab_ruby;
        private System.Windows.Forms.TabPage tab_java;
        private System.Windows.Forms.TextBox textbox_cpp;
        private System.Windows.Forms.TextBox textbox_python;
        private System.Windows.Forms.TextBox textbox_ruby;
        private System.Windows.Forms.TextBox textbox_java;
        private System.Windows.Forms.TextBox textbox_csharp;
        private System.Windows.Forms.TextBox tb_selectedTab;
    }
}

