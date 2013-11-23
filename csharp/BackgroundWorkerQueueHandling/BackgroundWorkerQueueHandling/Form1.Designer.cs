namespace BackgroundWorkerQueueHandling
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
            this.lbl_FirmwareVersion = new System.Windows.Forms.Label();
            this.btn_FirmwareVersion = new System.Windows.Forms.Button();
            this.lbl_RetVal = new System.Windows.Forms.Label();
            this.lbl_Connected = new System.Windows.Forms.Label();
            this.lbl_SerialNumber = new System.Windows.Forms.Label();
            this.btn_SerialNumber = new System.Windows.Forms.Button();
            this.btn_CrashTest = new System.Windows.Forms.Button();
            this.btn_StartThread = new System.Windows.Forms.Button();
            this.lst_FileManifest = new System.Windows.Forms.ListBox();
            this.btn_GetManifest = new System.Windows.Forms.Button();
            this.btn_ClearManifest = new System.Windows.Forms.Button();
            this.txt_filename = new System.Windows.Forms.TextBox();
            this.btn_RemoveFile = new System.Windows.Forms.Button();
            this.txt_SendFile = new System.Windows.Forms.TextBox();
            this.btn_SendFile = new System.Windows.Forms.Button();
            this.txt_GetFile = new System.Windows.Forms.TextBox();
            this.btn_GetFile = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // lbl_FirmwareVersion
            // 
            this.lbl_FirmwareVersion.AutoSize = true;
            this.lbl_FirmwareVersion.Location = new System.Drawing.Point(23,61);
            this.lbl_FirmwareVersion.Name = "lbl_FirmwareVersion";
            this.lbl_FirmwareVersion.Size = new System.Drawing.Size(83,13);
            this.lbl_FirmwareVersion.TabIndex = 3;
            this.lbl_FirmwareVersion.Text = "firmware version";
            // 
            // btn_FirmwareVersion
            // 
            this.btn_FirmwareVersion.Location = new System.Drawing.Point(122,55);
            this.btn_FirmwareVersion.Name = "btn_FirmwareVersion";
            this.btn_FirmwareVersion.Size = new System.Drawing.Size(110,24);
            this.btn_FirmwareVersion.TabIndex = 4;
            this.btn_FirmwareVersion.Text = "Firmware Version";
            this.btn_FirmwareVersion.UseVisualStyleBackColor = true;
            this.btn_FirmwareVersion.Click += new System.EventHandler(this.btn_FirmwareVersion_Click);
            // 
            // lbl_RetVal
            // 
            this.lbl_RetVal.AutoSize = true;
            this.lbl_RetVal.Location = new System.Drawing.Point(22,12);
            this.lbl_RetVal.Name = "lbl_RetVal";
            this.lbl_RetVal.Size = new System.Drawing.Size(35,13);
            this.lbl_RetVal.TabIndex = 5;
            this.lbl_RetVal.Text = "label1";
            // 
            // lbl_Connected
            // 
            this.lbl_Connected.AutoSize = true;
            this.lbl_Connected.Location = new System.Drawing.Point(13,396);
            this.lbl_Connected.Name = "lbl_Connected";
            this.lbl_Connected.Size = new System.Drawing.Size(119,13);
            this.lbl_Connected.TabIndex = 6;
            this.lbl_Connected.Text = "remote NOT connected";
            // 
            // lbl_SerialNumber
            // 
            this.lbl_SerialNumber.AutoSize = true;
            this.lbl_SerialNumber.Location = new System.Drawing.Point(23,102);
            this.lbl_SerialNumber.Name = "lbl_SerialNumber";
            this.lbl_SerialNumber.Size = new System.Drawing.Size(83,13);
            this.lbl_SerialNumber.TabIndex = 7;
            this.lbl_SerialNumber.Text = "firmware version";
            // 
            // btn_SerialNumber
            // 
            this.btn_SerialNumber.Location = new System.Drawing.Point(122,96);
            this.btn_SerialNumber.Name = "btn_SerialNumber";
            this.btn_SerialNumber.Size = new System.Drawing.Size(110,24);
            this.btn_SerialNumber.TabIndex = 8;
            this.btn_SerialNumber.Text = "Serial Number";
            this.btn_SerialNumber.UseVisualStyleBackColor = true;
            this.btn_SerialNumber.Click += new System.EventHandler(this.btn_SerialNumber_Click);
            // 
            // btn_CrashTest
            // 
            this.btn_CrashTest.Location = new System.Drawing.Point(122,354);
            this.btn_CrashTest.Name = "btn_CrashTest";
            this.btn_CrashTest.Size = new System.Drawing.Size(110,24);
            this.btn_CrashTest.TabIndex = 9;
            this.btn_CrashTest.Text = "Stop Thread";
            this.btn_CrashTest.UseVisualStyleBackColor = true;
            this.btn_CrashTest.Click += new System.EventHandler(this.btn_CrashTest_Click);
            // 
            // btn_StartThread
            // 
            this.btn_StartThread.Location = new System.Drawing.Point(238,354);
            this.btn_StartThread.Name = "btn_StartThread";
            this.btn_StartThread.Size = new System.Drawing.Size(110,24);
            this.btn_StartThread.TabIndex = 10;
            this.btn_StartThread.Text = "Start Thread";
            this.btn_StartThread.UseVisualStyleBackColor = true;
            this.btn_StartThread.Click += new System.EventHandler(this.btn_StartThread_Click);
            // 
            // lst_FileManifest
            // 
            this.lst_FileManifest.FormattingEnabled = true;
            this.lst_FileManifest.Location = new System.Drawing.Point(303,19);
            this.lst_FileManifest.Name = "lst_FileManifest";
            this.lst_FileManifest.Size = new System.Drawing.Size(220,316);
            this.lst_FileManifest.TabIndex = 11;
            // 
            // btn_GetManifest
            // 
            this.btn_GetManifest.Location = new System.Drawing.Point(122,140);
            this.btn_GetManifest.Name = "btn_GetManifest";
            this.btn_GetManifest.Size = new System.Drawing.Size(110,24);
            this.btn_GetManifest.TabIndex = 12;
            this.btn_GetManifest.Text = "Get Manifest";
            this.btn_GetManifest.UseVisualStyleBackColor = true;
            this.btn_GetManifest.Click += new System.EventHandler(this.btn_GetManifest_Click);
            // 
            // btn_ClearManifest
            // 
            this.btn_ClearManifest.Location = new System.Drawing.Point(413,354);
            this.btn_ClearManifest.Name = "btn_ClearManifest";
            this.btn_ClearManifest.Size = new System.Drawing.Size(110,24);
            this.btn_ClearManifest.TabIndex = 13;
            this.btn_ClearManifest.Text = "Clear All";
            this.btn_ClearManifest.UseVisualStyleBackColor = true;
            this.btn_ClearManifest.Click += new System.EventHandler(this.btn_ClearManifest_Click);
            // 
            // txt_filename
            // 
            this.txt_filename.Location = new System.Drawing.Point(19,179);
            this.txt_filename.Name = "txt_filename";
            this.txt_filename.Size = new System.Drawing.Size(87,20);
            this.txt_filename.TabIndex = 14;
            // 
            // btn_RemoveFile
            // 
            this.btn_RemoveFile.Location = new System.Drawing.Point(122,176);
            this.btn_RemoveFile.Name = "btn_RemoveFile";
            this.btn_RemoveFile.Size = new System.Drawing.Size(110,24);
            this.btn_RemoveFile.TabIndex = 15;
            this.btn_RemoveFile.Text = "Remove File";
            this.btn_RemoveFile.UseVisualStyleBackColor = true;
            this.btn_RemoveFile.Click += new System.EventHandler(this.btn_RemoveFile_Click);
            // 
            // txt_SendFile
            // 
            this.txt_SendFile.Location = new System.Drawing.Point(19,209);
            this.txt_SendFile.Name = "txt_SendFile";
            this.txt_SendFile.Size = new System.Drawing.Size(87,20);
            this.txt_SendFile.TabIndex = 16;
            // 
            // btn_SendFile
            // 
            this.btn_SendFile.Location = new System.Drawing.Point(122,206);
            this.btn_SendFile.Name = "btn_SendFile";
            this.btn_SendFile.Size = new System.Drawing.Size(110,24);
            this.btn_SendFile.TabIndex = 17;
            this.btn_SendFile.Text = "Send File";
            this.btn_SendFile.UseVisualStyleBackColor = true;
            this.btn_SendFile.Click += new System.EventHandler(this.btn_SendFile_Click);
            // 
            // txt_GetFile
            // 
            this.txt_GetFile.Location = new System.Drawing.Point(19,243);
            this.txt_GetFile.Name = "txt_GetFile";
            this.txt_GetFile.Size = new System.Drawing.Size(87,20);
            this.txt_GetFile.TabIndex = 18;
            // 
            // btn_GetFile
            // 
            this.btn_GetFile.Location = new System.Drawing.Point(122,240);
            this.btn_GetFile.Name = "btn_GetFile";
            this.btn_GetFile.Size = new System.Drawing.Size(110,24);
            this.btn_GetFile.TabIndex = 19;
            this.btn_GetFile.Text = "Get File";
            this.btn_GetFile.UseVisualStyleBackColor = true;
            this.btn_GetFile.Click += new System.EventHandler(this.btn_GetFile_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F,13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(556,423);
            this.Controls.Add(this.btn_GetFile);
            this.Controls.Add(this.txt_GetFile);
            this.Controls.Add(this.btn_SendFile);
            this.Controls.Add(this.txt_SendFile);
            this.Controls.Add(this.btn_RemoveFile);
            this.Controls.Add(this.txt_filename);
            this.Controls.Add(this.btn_ClearManifest);
            this.Controls.Add(this.btn_GetManifest);
            this.Controls.Add(this.lst_FileManifest);
            this.Controls.Add(this.btn_StartThread);
            this.Controls.Add(this.btn_CrashTest);
            this.Controls.Add(this.btn_SerialNumber);
            this.Controls.Add(this.lbl_SerialNumber);
            this.Controls.Add(this.lbl_Connected);
            this.Controls.Add(this.lbl_RetVal);
            this.Controls.Add(this.btn_FirmwareVersion);
            this.Controls.Add(this.lbl_FirmwareVersion);
            this.Name = "Form1";
            this.Text = "MultiThreadTester";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label lbl_FirmwareVersion;
        private System.Windows.Forms.Button btn_FirmwareVersion;
        private System.Windows.Forms.Label lbl_RetVal;
        private System.Windows.Forms.Label lbl_Connected;
        private System.Windows.Forms.Label lbl_SerialNumber;
        private System.Windows.Forms.Button btn_SerialNumber;
        private System.Windows.Forms.Button btn_CrashTest;
        private System.Windows.Forms.Button btn_StartThread;
        private System.Windows.Forms.ListBox lst_FileManifest;
        private System.Windows.Forms.Button btn_GetManifest;
        private System.Windows.Forms.Button btn_ClearManifest;
        private System.Windows.Forms.TextBox txt_filename;
        private System.Windows.Forms.Button btn_RemoveFile;
        private System.Windows.Forms.TextBox txt_SendFile;
        private System.Windows.Forms.Button btn_SendFile;
        private System.Windows.Forms.TextBox txt_GetFile;
        private System.Windows.Forms.Button btn_GetFile;
    }
}

