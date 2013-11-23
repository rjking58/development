namespace ConfigurationsDSWithVSTools
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
            this.RemoteConfigurationsDS = new System.Data.DataSet();
            this.ConfigurationsTbl = new System.Data.DataTable();
            this.Configs_UserID = new System.Data.DataColumn();
            this.Configs_ConfigID = new System.Data.DataColumn();
            this.Configs_ConfigName = new System.Data.DataColumn();
            this.DevicesTbl = new System.Data.DataTable();
            this.Devices_UserID = new System.Data.DataColumn();
            this.Devices_ConfigID = new System.Data.DataColumn();
            this.Devices_DeviceID = new System.Data.DataColumn();
            this.Devices_DeviceName = new System.Data.DataColumn();
            this.btn_DoTest = new System.Windows.Forms.Button();
            this.lstbox_main = new System.Windows.Forms.ListBox();
            this.DeviceKeysTbl = new System.Data.DataTable();
            this.DeviceKeys_UserID = new System.Data.DataColumn();
            this.DeviceKeys_ConfigID = new System.Data.DataColumn();
            this.DeviceKeys_DeviceID = new System.Data.DataColumn();
            this.DeviceKeys_KeyID = new System.Data.DataColumn();
            this.DeviceKeys_KeyName = new System.Data.DataColumn();
            this.DeviceKeys_LearnedID = new System.Data.DataColumn();
            this.LearnedKeysTbl = new System.Data.DataTable();
            this.LearnedKeys_UserID = new System.Data.DataColumn();
            this.LearnedKeys_ConfigID = new System.Data.DataColumn();
            this.LearnedKeys_DeviceID = new System.Data.DataColumn();
            this.LearnedKeys_LearnedID = new System.Data.DataColumn();
            this.dataColumn1 = new System.Data.DataColumn();
            ((System.ComponentModel.ISupportInitialize)(this.RemoteConfigurationsDS)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ConfigurationsTbl)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.DevicesTbl)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.DeviceKeysTbl)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.LearnedKeysTbl)).BeginInit();
            this.SuspendLayout();
            // 
            // RemoteConfigurationsDS
            // 
            this.RemoteConfigurationsDS.DataSetName = "Remote Configurations";
            this.RemoteConfigurationsDS.Tables.AddRange(new System.Data.DataTable[] {
            this.ConfigurationsTbl,
            this.DevicesTbl,
            this.DeviceKeysTbl,
            this.LearnedKeysTbl});
            // 
            // ConfigurationsTbl
            // 
            this.ConfigurationsTbl.Columns.AddRange(new System.Data.DataColumn[] {
            this.Configs_UserID,
            this.Configs_ConfigID,
            this.Configs_ConfigName});
            this.ConfigurationsTbl.TableName = "Configurations";
            // 
            // Configs_UserID
            // 
            this.Configs_UserID.AllowDBNull = false;
            this.Configs_UserID.Caption = "UserID";
            this.Configs_UserID.ColumnMapping = System.Data.MappingType.Attribute;
            this.Configs_UserID.ColumnName = "UserID";
            this.Configs_UserID.DataType = typeof(ulong);
            // 
            // Configs_ConfigID
            // 
            this.Configs_ConfigID.AllowDBNull = false;
            this.Configs_ConfigID.Caption = "ConfigID";
            this.Configs_ConfigID.ColumnMapping = System.Data.MappingType.Attribute;
            this.Configs_ConfigID.ColumnName = "ConfigID";
            this.Configs_ConfigID.DataType = typeof(ushort);
            // 
            // Configs_ConfigName
            // 
            this.Configs_ConfigName.AllowDBNull = false;
            this.Configs_ConfigName.Caption = "ConfigName";
            this.Configs_ConfigName.ColumnMapping = System.Data.MappingType.Attribute;
            this.Configs_ConfigName.ColumnName = "ConfigName";
            // 
            // DevicesTbl
            // 
            this.DevicesTbl.Columns.AddRange(new System.Data.DataColumn[] {
            this.Devices_UserID,
            this.Devices_ConfigID,
            this.Devices_DeviceID,
            this.Devices_DeviceName});
            this.DevicesTbl.TableName = "Devices";
            // 
            // Devices_UserID
            // 
            this.Devices_UserID.AllowDBNull = false;
            this.Devices_UserID.Caption = "UserID";
            this.Devices_UserID.ColumnMapping = System.Data.MappingType.Attribute;
            this.Devices_UserID.ColumnName = "UserID";
            this.Devices_UserID.DataType = typeof(ulong);
            // 
            // Devices_ConfigID
            // 
            this.Devices_ConfigID.AllowDBNull = false;
            this.Devices_ConfigID.Caption = "ConfigID";
            this.Devices_ConfigID.ColumnMapping = System.Data.MappingType.Attribute;
            this.Devices_ConfigID.ColumnName = "ConfigID";
            this.Devices_ConfigID.DataType = typeof(ushort);
            // 
            // Devices_DeviceID
            // 
            this.Devices_DeviceID.AllowDBNull = false;
            this.Devices_DeviceID.Caption = "DeviceID";
            this.Devices_DeviceID.ColumnMapping = System.Data.MappingType.Attribute;
            this.Devices_DeviceID.ColumnName = "DeviceID";
            this.Devices_DeviceID.DataType = typeof(ushort);
            // 
            // Devices_DeviceName
            // 
            this.Devices_DeviceName.AllowDBNull = false;
            this.Devices_DeviceName.Caption = "DeviceName";
            this.Devices_DeviceName.ColumnMapping = System.Data.MappingType.Attribute;
            this.Devices_DeviceName.ColumnName = "DeviceName";
            // 
            // btn_DoTest
            // 
            this.btn_DoTest.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.btn_DoTest.Location = new System.Drawing.Point(12,231);
            this.btn_DoTest.Name = "btn_DoTest";
            this.btn_DoTest.Size = new System.Drawing.Size(126,23);
            this.btn_DoTest.TabIndex = 0;
            this.btn_DoTest.Text = "Run DataSet Test";
            this.btn_DoTest.UseVisualStyleBackColor = true;
            this.btn_DoTest.Click += new System.EventHandler(this.btn_DoTest_Click);
            // 
            // lstbox_main
            // 
            this.lstbox_main.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.lstbox_main.FormattingEnabled = true;
            this.lstbox_main.Location = new System.Drawing.Point(14,13);
            this.lstbox_main.Name = "lstbox_main";
            this.lstbox_main.Size = new System.Drawing.Size(532,199);
            this.lstbox_main.TabIndex = 1;
            // 
            // DeviceKeysTbl
            // 
            this.DeviceKeysTbl.Columns.AddRange(new System.Data.DataColumn[] {
            this.DeviceKeys_UserID,
            this.DeviceKeys_ConfigID,
            this.DeviceKeys_DeviceID,
            this.DeviceKeys_KeyID,
            this.DeviceKeys_KeyName,
            this.DeviceKeys_LearnedID});
            this.DeviceKeysTbl.TableName = "DeviceKeys";
            // 
            // DeviceKeys_UserID
            // 
            this.DeviceKeys_UserID.AllowDBNull = false;
            this.DeviceKeys_UserID.Caption = "UserID";
            this.DeviceKeys_UserID.ColumnMapping = System.Data.MappingType.Attribute;
            this.DeviceKeys_UserID.ColumnName = "UserID";
            this.DeviceKeys_UserID.DataType = typeof(ulong);
            // 
            // DeviceKeys_ConfigID
            // 
            this.DeviceKeys_ConfigID.AllowDBNull = false;
            this.DeviceKeys_ConfigID.Caption = "ConfigID";
            this.DeviceKeys_ConfigID.ColumnMapping = System.Data.MappingType.Attribute;
            this.DeviceKeys_ConfigID.ColumnName = "ConfigID";
            this.DeviceKeys_ConfigID.DataType = typeof(ushort);
            // 
            // DeviceKeys_DeviceID
            // 
            this.DeviceKeys_DeviceID.AllowDBNull = false;
            this.DeviceKeys_DeviceID.Caption = "DeviceID";
            this.DeviceKeys_DeviceID.ColumnMapping = System.Data.MappingType.Attribute;
            this.DeviceKeys_DeviceID.ColumnName = "DeviceID";
            this.DeviceKeys_DeviceID.DataType = typeof(ushort);
            // 
            // DeviceKeys_KeyID
            // 
            this.DeviceKeys_KeyID.AllowDBNull = false;
            this.DeviceKeys_KeyID.Caption = "KeyID";
            this.DeviceKeys_KeyID.ColumnMapping = System.Data.MappingType.Attribute;
            this.DeviceKeys_KeyID.ColumnName = "KeyID";
            this.DeviceKeys_KeyID.DataType = typeof(short);
            // 
            // DeviceKeys_KeyName
            // 
            this.DeviceKeys_KeyName.AllowDBNull = false;
            this.DeviceKeys_KeyName.Caption = "KeyName";
            this.DeviceKeys_KeyName.ColumnMapping = System.Data.MappingType.Attribute;
            this.DeviceKeys_KeyName.ColumnName = "KeyName";
            // 
            // DeviceKeys_LearnedID
            // 
            this.DeviceKeys_LearnedID.Caption = "LearnedID";
            this.DeviceKeys_LearnedID.ColumnMapping = System.Data.MappingType.Attribute;
            this.DeviceKeys_LearnedID.ColumnName = "LearnedID";
            this.DeviceKeys_LearnedID.DataType = typeof(ushort);
            // 
            // LearnedKeysTbl
            // 
            this.LearnedKeysTbl.Columns.AddRange(new System.Data.DataColumn[] {
            this.LearnedKeys_UserID,
            this.LearnedKeys_ConfigID,
            this.LearnedKeys_DeviceID,
            this.LearnedKeys_LearnedID,
            this.dataColumn1});
            this.LearnedKeysTbl.TableName = "LearnedKeys";
            // 
            // LearnedKeys_UserID
            // 
            this.LearnedKeys_UserID.AllowDBNull = false;
            this.LearnedKeys_UserID.Caption = "UserID";
            this.LearnedKeys_UserID.ColumnMapping = System.Data.MappingType.Attribute;
            this.LearnedKeys_UserID.ColumnName = "UserID";
            this.LearnedKeys_UserID.DataType = typeof(ulong);
            // 
            // LearnedKeys_ConfigID
            // 
            this.LearnedKeys_ConfigID.AllowDBNull = false;
            this.LearnedKeys_ConfigID.Caption = "ConfigID";
            this.LearnedKeys_ConfigID.ColumnMapping = System.Data.MappingType.Attribute;
            this.LearnedKeys_ConfigID.ColumnName = "ConfigID";
            this.LearnedKeys_ConfigID.DataType = typeof(ushort);
            // 
            // LearnedKeys_DeviceID
            // 
            this.LearnedKeys_DeviceID.AllowDBNull = false;
            this.LearnedKeys_DeviceID.Caption = "DeviceID";
            this.LearnedKeys_DeviceID.ColumnMapping = System.Data.MappingType.Attribute;
            this.LearnedKeys_DeviceID.ColumnName = "DeviceID";
            this.LearnedKeys_DeviceID.DataType = typeof(ushort);
            // 
            // LearnedKeys_LearnedID
            // 
            this.LearnedKeys_LearnedID.AllowDBNull = false;
            this.LearnedKeys_LearnedID.Caption = "LearnedID";
            this.LearnedKeys_LearnedID.ColumnMapping = System.Data.MappingType.Attribute;
            this.LearnedKeys_LearnedID.ColumnName = "LearnedID";
            this.LearnedKeys_LearnedID.DataType = typeof(ushort);
            // 
            // dataColumn1
            // 
            this.dataColumn1.Caption = "LearnedData";
            this.dataColumn1.ColumnName = "LearnedData";
            this.dataColumn1.DataType = typeof(byte[]);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F,13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(572,266);
            this.Controls.Add(this.lstbox_main);
            this.Controls.Add(this.btn_DoTest);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.RemoteConfigurationsDS)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ConfigurationsTbl)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.DevicesTbl)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.DeviceKeysTbl)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.LearnedKeysTbl)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Data.DataSet RemoteConfigurationsDS;
        private System.Data.DataTable ConfigurationsTbl;
        private System.Data.DataColumn Configs_UserID;
        private System.Data.DataColumn Configs_ConfigID;
        private System.Data.DataColumn Configs_ConfigName;
        private System.Data.DataTable DevicesTbl;
        private System.Data.DataColumn Devices_UserID;
        private System.Data.DataColumn Devices_ConfigID;
        private System.Data.DataColumn Devices_DeviceID;
        private System.Data.DataColumn Devices_DeviceName;
        private System.Windows.Forms.Button btn_DoTest;
        private System.Windows.Forms.ListBox lstbox_main;
        private System.Data.DataTable DeviceKeysTbl;
        private System.Data.DataColumn DeviceKeys_UserID;
        private System.Data.DataColumn DeviceKeys_ConfigID;
        private System.Data.DataColumn DeviceKeys_DeviceID;
        private System.Data.DataColumn DeviceKeys_KeyID;
        private System.Data.DataColumn DeviceKeys_KeyName;
        private System.Data.DataColumn DeviceKeys_LearnedID;
        private System.Data.DataTable LearnedKeysTbl;
        private System.Data.DataColumn LearnedKeys_UserID;
        private System.Data.DataColumn LearnedKeys_ConfigID;
        private System.Data.DataColumn LearnedKeys_DeviceID;
        private System.Data.DataColumn LearnedKeys_LearnedID;
        private System.Data.DataColumn dataColumn1;
    }
}

