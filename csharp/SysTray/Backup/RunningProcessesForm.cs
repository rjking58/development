using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Diagnostics;

namespace PriorityManager
{
	/// <summary>
	/// Summary description for RunningProcessesForm.
	/// </summary>
	public class RunningProcessesForm : System.Windows.Forms.Form
	{
		private System.Windows.Forms.Button buttonOK;
		private System.Windows.Forms.Button buttonCancel;
		private System.Windows.Forms.Button buttonRefresh;
		private System.Windows.Forms.ListBox listBoxProcesses;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public RunningProcessesForm()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();

			//
			// TODO: Add any constructor code after InitializeComponent call
			//
		}

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		protected override void Dispose( bool disposing )
		{
			if( disposing )
			{
				if(components != null)
				{
					components.Dispose();
				}
			}
			base.Dispose( disposing );
		}

		#region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			System.Resources.ResourceManager resources = new System.Resources.ResourceManager(typeof(RunningProcessesForm));
			this.buttonOK = new System.Windows.Forms.Button();
			this.buttonCancel = new System.Windows.Forms.Button();
			this.buttonRefresh = new System.Windows.Forms.Button();
			this.listBoxProcesses = new System.Windows.Forms.ListBox();
			this.SuspendLayout();
			// 
			// buttonOK
			// 
			this.buttonOK.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
			this.buttonOK.DialogResult = System.Windows.Forms.DialogResult.OK;
			this.buttonOK.Location = new System.Drawing.Point(20, 280);
			this.buttonOK.Name = "buttonOK";
			this.buttonOK.TabIndex = 2;
			this.buttonOK.Text = "&OK";
			this.buttonOK.Click += new System.EventHandler(this.buttonOK_Click);
			// 
			// buttonCancel
			// 
			this.buttonCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			this.buttonCancel.Location = new System.Drawing.Point(109, 280);
			this.buttonCancel.Name = "buttonCancel";
			this.buttonCancel.Size = new System.Drawing.Size(80, 23);
			this.buttonCancel.TabIndex = 3;
			this.buttonCancel.Text = "&Cancel";
			// 
			// buttonRefresh
			// 
			this.buttonRefresh.Location = new System.Drawing.Point(21, 248);
			this.buttonRefresh.Name = "buttonRefresh";
			this.buttonRefresh.Size = new System.Drawing.Size(168, 23);
			this.buttonRefresh.TabIndex = 1;
			this.buttonRefresh.Text = "&Refresh";
			this.buttonRefresh.Click += new System.EventHandler(this.buttonRefresh_Click);
			// 
			// listBoxProcesses
			// 
			this.listBoxProcesses.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
				| System.Windows.Forms.AnchorStyles.Left) 
				| System.Windows.Forms.AnchorStyles.Right)));
			this.listBoxProcesses.Location = new System.Drawing.Point(8, 8);
			this.listBoxProcesses.Name = "listBoxProcesses";
			this.listBoxProcesses.Size = new System.Drawing.Size(192, 225);
			this.listBoxProcesses.TabIndex = 0;
			// 
			// RunningProcessesForm
			// 
			this.AcceptButton = this.buttonOK;
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.CancelButton = this.buttonCancel;
			this.ClientSize = new System.Drawing.Size(208, 310);
			this.Controls.Add(this.listBoxProcesses);
			this.Controls.Add(this.buttonRefresh);
			this.Controls.Add(this.buttonCancel);
			this.Controls.Add(this.buttonOK);
			this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
			this.Name = "RunningProcessesForm";
			this.Text = "Select...";
			this.Load += new System.EventHandler(this.RunningProcessesForm_Load);
			this.ResumeLayout(false);

		}
		#endregion

		private void RunningProcessesForm_Load(object sender, System.EventArgs e)
		{
			Refresh();
		}

		private void buttonRefresh_Click(object sender, System.EventArgs e)
		{
			Refresh();		
		}

		private void Refresh()
		{
			listBoxProcesses.Items.Clear();

			Process [] pl = Process.GetProcesses();

			foreach ( Process p in pl )
			{
				string name = p.ProcessName;

				try
				{
					name = p.MainModule.ModuleName;
				}
				catch
				{}

				listBoxProcesses.Items.Add( name );
			}
		}

		public string MatchString = "";

		private void buttonOK_Click(object sender, System.EventArgs e)
		{
            MatchString = listBoxProcesses.SelectedItem.ToString();		
		}
	}
}
