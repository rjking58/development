using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Diagnostics;

namespace PriorityManager
{
	/// <summary>
	/// Summary description for SettingsItemForm.
	/// </summary>
	public class SettingsItemForm : System.Windows.Forms.Form
	{
		private System.Windows.Forms.Button buttonCancel;
		private System.Windows.Forms.Button buttonOK;
		private System.Windows.Forms.Label labelName;
		private System.Windows.Forms.TextBox textBoxName;
		private System.Windows.Forms.ComboBox comboBoxPriority;
		private System.Windows.Forms.Label labelMatchString;
		private System.Windows.Forms.TextBox textBoxMatchString;
		private System.Windows.Forms.Label labelPriority;
		private System.Windows.Forms.ErrorProvider errorProviderName;
		private System.Windows.Forms.ErrorProvider errorProviderMatchString;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;
		private System.Windows.Forms.Button buttonExisting;

		private ProcessAction Initial = null;

		public SettingsItemForm( ProcessAction initial )
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();

			//
			// TODO: Add any constructor code after InitializeComponent call
			//
			Initial = initial;
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
			System.Resources.ResourceManager resources = new System.Resources.ResourceManager(typeof(SettingsItemForm));
			this.textBoxName = new System.Windows.Forms.TextBox();
			this.buttonCancel = new System.Windows.Forms.Button();
			this.buttonOK = new System.Windows.Forms.Button();
			this.comboBoxPriority = new System.Windows.Forms.ComboBox();
			this.labelName = new System.Windows.Forms.Label();
			this.labelMatchString = new System.Windows.Forms.Label();
			this.textBoxMatchString = new System.Windows.Forms.TextBox();
			this.labelPriority = new System.Windows.Forms.Label();
			this.errorProviderName = new System.Windows.Forms.ErrorProvider();
			this.errorProviderMatchString = new System.Windows.Forms.ErrorProvider();
			this.buttonExisting = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// textBoxName
			// 
			this.textBoxName.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
				| System.Windows.Forms.AnchorStyles.Right)));
			this.textBoxName.Location = new System.Drawing.Point(88, 8);
			this.textBoxName.Name = "textBoxName";
			this.textBoxName.Size = new System.Drawing.Size(136, 20);
			this.textBoxName.TabIndex = 1;
			this.textBoxName.Text = "";
			this.textBoxName.Validating += new System.ComponentModel.CancelEventHandler(this.textBoxName_Validating);
			// 
			// buttonCancel
			// 
			this.buttonCancel.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
			this.buttonCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			this.buttonCancel.Location = new System.Drawing.Point(137, 136);
			this.buttonCancel.Name = "buttonCancel";
			this.buttonCancel.Size = new System.Drawing.Size(75, 24);
			this.buttonCancel.TabIndex = 7;
			this.buttonCancel.Text = "&Cancel";
			// 
			// buttonOK
			// 
			this.buttonOK.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
			this.buttonOK.DialogResult = System.Windows.Forms.DialogResult.OK;
			this.buttonOK.Location = new System.Drawing.Point(41, 136);
			this.buttonOK.Name = "buttonOK";
			this.buttonOK.Size = new System.Drawing.Size(75, 24);
			this.buttonOK.TabIndex = 6;
			this.buttonOK.Text = "&OK";
			this.buttonOK.Click += new System.EventHandler(this.buttonOK_Click);
			// 
			// comboBoxPriority
			// 
			this.comboBoxPriority.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
				| System.Windows.Forms.AnchorStyles.Right)));
			this.comboBoxPriority.CausesValidation = false;
			this.comboBoxPriority.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.comboBoxPriority.Location = new System.Drawing.Point(88, 104);
			this.comboBoxPriority.Name = "comboBoxPriority";
			this.comboBoxPriority.Size = new System.Drawing.Size(156, 21);
			this.comboBoxPriority.TabIndex = 5;
			// 
			// labelName
			// 
			this.labelName.Location = new System.Drawing.Point(8, 8);
			this.labelName.Name = "labelName";
			this.labelName.Size = new System.Drawing.Size(72, 20);
			this.labelName.TabIndex = 0;
			this.labelName.Text = "Name:";
			this.labelName.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			// 
			// labelMatchString
			// 
			this.labelMatchString.Location = new System.Drawing.Point(8, 40);
			this.labelMatchString.Name = "labelMatchString";
			this.labelMatchString.Size = new System.Drawing.Size(72, 20);
			this.labelMatchString.TabIndex = 2;
			this.labelMatchString.Text = "Match String:";
			this.labelMatchString.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			// 
			// textBoxMatchString
			// 
			this.textBoxMatchString.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
				| System.Windows.Forms.AnchorStyles.Right)));
			this.textBoxMatchString.Location = new System.Drawing.Point(88, 40);
			this.textBoxMatchString.Name = "textBoxMatchString";
			this.textBoxMatchString.Size = new System.Drawing.Size(136, 20);
			this.textBoxMatchString.TabIndex = 3;
			this.textBoxMatchString.Text = "";
			this.textBoxMatchString.Validating += new System.ComponentModel.CancelEventHandler(this.textBoxMatchString_Validating);
			// 
			// labelPriority
			// 
			this.labelPriority.Location = new System.Drawing.Point(8, 104);
			this.labelPriority.Name = "labelPriority";
			this.labelPriority.Size = new System.Drawing.Size(72, 20);
			this.labelPriority.TabIndex = 4;
			this.labelPriority.Text = "Priority:";
			this.labelPriority.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			// 
			// errorProviderName
			// 
			this.errorProviderName.ContainerControl = this;
			// 
			// errorProviderMatchString
			// 
			this.errorProviderMatchString.ContainerControl = this;
			// 
			// buttonExisting
			// 
			this.buttonExisting.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
				| System.Windows.Forms.AnchorStyles.Right)));
			this.buttonExisting.Location = new System.Drawing.Point(88, 72);
			this.buttonExisting.Name = "buttonExisting";
			this.buttonExisting.Size = new System.Drawing.Size(136, 20);
			this.buttonExisting.TabIndex = 8;
			this.buttonExisting.Text = "Match Running Process";
			this.buttonExisting.Click += new System.EventHandler(this.buttonExisting_Click);
			// 
			// SettingsItemForm
			// 
			this.AcceptButton = this.buttonOK;
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.CancelButton = this.buttonCancel;
			this.ClientSize = new System.Drawing.Size(252, 174);
			this.Controls.Add(this.buttonExisting);
			this.Controls.Add(this.labelPriority);
			this.Controls.Add(this.labelMatchString);
			this.Controls.Add(this.textBoxMatchString);
			this.Controls.Add(this.textBoxName);
			this.Controls.Add(this.labelName);
			this.Controls.Add(this.comboBoxPriority);
			this.Controls.Add(this.buttonCancel);
			this.Controls.Add(this.buttonOK);
			this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
			this.MaximumSize = new System.Drawing.Size(10000, 220);
			this.MinimumSize = new System.Drawing.Size(260, 200);
			this.Name = "SettingsItemForm";
			this.Text = "SettingsItemForm";
			this.Load += new System.EventHandler(this.SettingsItemForm_Load);
			this.ResumeLayout(false);

		}
		#endregion

		private void SettingsItemForm_Load(object sender, System.EventArgs e)
		{
			comboBoxPriority.Items.AddRange( Enum.GetNames( typeof( ProcessPriorityClass ) ) ); 

			foreach ( string s in comboBoxPriority.Items )
			{
				if ( s == Initial.PriorityClass.ToString() )
				{
					comboBoxPriority.SelectedItem = s;
				}
			}

			textBoxMatchString.Text = Initial.MatchString;
			textBoxName.Text = Initial.Name;
		}

		private void buttonOK_Click(object sender, System.EventArgs e)
		{
			Initial.MatchString   = textBoxMatchString.Text;
			Initial.Name		  = textBoxName.Text;
			Initial.PriorityClass = (ProcessPriorityClass)Enum.Parse( typeof( ProcessPriorityClass ), comboBoxPriority.SelectedItem.ToString() );
		}

		private void textBoxMatchString_Validating(object sender, System.ComponentModel.CancelEventArgs e)
		{
			if ( textBoxMatchString.Text.Trim().Length < 5 )
			{
				e.Cancel = true;
				errorProviderMatchString.SetError( textBoxMatchString , "Match string too short" );
			}
		}

		private void textBoxName_Validating(object sender, System.ComponentModel.CancelEventArgs e)
		{
			if ( textBoxName.Text.Trim().Length == 0 )
			{
				e.Cancel = true;
				errorProviderName.SetError( textBoxName , "A name must be specified" );
			}
		}

		private void buttonExisting_Click(object sender, System.EventArgs e)
		{
			RunningProcessesForm rpf = new RunningProcessesForm();

			if ( rpf.ShowDialog() == DialogResult.OK )
			{
				textBoxMatchString.Text = "^" +  rpf.MatchString + "$";
			}
		}

	}
}
