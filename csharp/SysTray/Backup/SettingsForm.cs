using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;

namespace PriorityManager
{
	/// <summary>
	/// Summary description for SettingsForm.
	/// </summary>
	public class SettingsForm : System.Windows.Forms.Form
	{
		private System.Windows.Forms.Button buttonOK;
		private System.Windows.Forms.Button buttonCancel;
		private System.Windows.Forms.GroupBox groupBoxProcesses;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;
		private System.Windows.Forms.GroupBox groupBoxState;
		private System.Windows.Forms.ContextMenu contextMenuSettings;
		private System.Windows.Forms.MenuItem menuItemEdit;
		private System.Windows.Forms.MenuItem menuItemDelete;
		private System.Windows.Forms.CheckedListBox checkedListBoxProcessActions;
		private System.Windows.Forms.CheckBox checkBoxToast;
		private System.Windows.Forms.Button buttonAdd;
		private System.Windows.Forms.Button buttonEdit;
		private System.Windows.Forms.Button buttonDelete;
		private System.Windows.Forms.MenuItem menuItemAdd;
		private System.Windows.Forms.CheckBox checkBoxEnabled;

		public SettingsForm()
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
			System.Resources.ResourceManager resources = new System.Resources.ResourceManager(typeof(SettingsForm));
			this.buttonOK = new System.Windows.Forms.Button();
			this.buttonCancel = new System.Windows.Forms.Button();
			this.groupBoxProcesses = new System.Windows.Forms.GroupBox();
			this.checkedListBoxProcessActions = new System.Windows.Forms.CheckedListBox();
			this.contextMenuSettings = new System.Windows.Forms.ContextMenu();
			this.menuItemEdit = new System.Windows.Forms.MenuItem();
			this.menuItemDelete = new System.Windows.Forms.MenuItem();
			this.groupBoxState = new System.Windows.Forms.GroupBox();
			this.checkBoxToast = new System.Windows.Forms.CheckBox();
			this.checkBoxEnabled = new System.Windows.Forms.CheckBox();
			this.buttonAdd = new System.Windows.Forms.Button();
			this.buttonEdit = new System.Windows.Forms.Button();
			this.buttonDelete = new System.Windows.Forms.Button();
			this.menuItemAdd = new System.Windows.Forms.MenuItem();
			this.groupBoxProcesses.SuspendLayout();
			this.groupBoxState.SuspendLayout();
			this.SuspendLayout();
			// 
			// buttonOK
			// 
			this.buttonOK.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
			this.buttonOK.Location = new System.Drawing.Point(82, 228);
			this.buttonOK.Name = "buttonOK";
			this.buttonOK.Size = new System.Drawing.Size(75, 24);
			this.buttonOK.TabIndex = 2;
			this.buttonOK.Text = "&OK";
			this.buttonOK.Click += new System.EventHandler(this.buttonOK_Click);
			// 
			// buttonCancel
			// 
			this.buttonCancel.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
			this.buttonCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			this.buttonCancel.Location = new System.Drawing.Point(178, 228);
			this.buttonCancel.Name = "buttonCancel";
			this.buttonCancel.Size = new System.Drawing.Size(75, 24);
			this.buttonCancel.TabIndex = 3;
			this.buttonCancel.Text = "&Cancel";
			this.buttonCancel.Click += new System.EventHandler(this.buttonCancel_Click);
			// 
			// groupBoxProcesses
			// 
			this.groupBoxProcesses.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
				| System.Windows.Forms.AnchorStyles.Left) 
				| System.Windows.Forms.AnchorStyles.Right)));
			this.groupBoxProcesses.Controls.Add(this.buttonDelete);
			this.groupBoxProcesses.Controls.Add(this.buttonEdit);
			this.groupBoxProcesses.Controls.Add(this.buttonAdd);
			this.groupBoxProcesses.Controls.Add(this.checkedListBoxProcessActions);
			this.groupBoxProcesses.Location = new System.Drawing.Point(16, 64);
			this.groupBoxProcesses.Name = "groupBoxProcesses";
			this.groupBoxProcesses.Size = new System.Drawing.Size(300, 148);
			this.groupBoxProcesses.TabIndex = 1;
			this.groupBoxProcesses.TabStop = false;
			this.groupBoxProcesses.Text = "Processes to Monitor";
			// 
			// checkedListBoxProcessActions
			// 
			this.checkedListBoxProcessActions.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
				| System.Windows.Forms.AnchorStyles.Left) 
				| System.Windows.Forms.AnchorStyles.Right)));
			this.checkedListBoxProcessActions.ContextMenu = this.contextMenuSettings;
			this.checkedListBoxProcessActions.Location = new System.Drawing.Point(8, 16);
			this.checkedListBoxProcessActions.Name = "checkedListBoxProcessActions";
			this.checkedListBoxProcessActions.Size = new System.Drawing.Size(280, 94);
			this.checkedListBoxProcessActions.TabIndex = 0;
			this.checkedListBoxProcessActions.ItemCheck += new System.Windows.Forms.ItemCheckEventHandler(this.checkedListBoxProcessActions_ItemCheck);
			// 
			// contextMenuSettings
			// 
			this.contextMenuSettings.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
																								this.menuItemAdd,
																								this.menuItemEdit,
																								this.menuItemDelete});
			// 
			// menuItemEdit
			// 
			this.menuItemEdit.Index = 1;
			this.menuItemEdit.Text = "&Edit";
			this.menuItemEdit.Click += new System.EventHandler(this.menuItemEdit_Click);
			// 
			// menuItemDelete
			// 
			this.menuItemDelete.Index = 2;
			this.menuItemDelete.Text = "&Delete";
			this.menuItemDelete.Click += new System.EventHandler(this.menuItemDelete_Click);
			// 
			// groupBoxState
			// 
			this.groupBoxState.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
				| System.Windows.Forms.AnchorStyles.Right)));
			this.groupBoxState.Controls.Add(this.checkBoxToast);
			this.groupBoxState.Controls.Add(this.checkBoxEnabled);
			this.groupBoxState.Location = new System.Drawing.Point(16, 8);
			this.groupBoxState.Name = "groupBoxState";
			this.groupBoxState.Size = new System.Drawing.Size(300, 48);
			this.groupBoxState.TabIndex = 0;
			this.groupBoxState.TabStop = false;
			this.groupBoxState.Text = "Preferences";
			// 
			// checkBoxToast
			// 
			this.checkBoxToast.Location = new System.Drawing.Point(154, 16);
			this.checkBoxToast.Name = "checkBoxToast";
			this.checkBoxToast.Size = new System.Drawing.Size(136, 24);
			this.checkBoxToast.TabIndex = 1;
			this.checkBoxToast.Text = "Toast Enabled";
			// 
			// checkBoxEnabled
			// 
			this.checkBoxEnabled.Location = new System.Drawing.Point(10, 16);
			this.checkBoxEnabled.Name = "checkBoxEnabled";
			this.checkBoxEnabled.Size = new System.Drawing.Size(136, 24);
			this.checkBoxEnabled.TabIndex = 0;
			this.checkBoxEnabled.Text = "Enabled at Startup";
			// 
			// buttonAdd
			// 
			this.buttonAdd.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
			this.buttonAdd.Location = new System.Drawing.Point(8, 120);
			this.buttonAdd.Name = "buttonAdd";
			this.buttonAdd.TabIndex = 1;
			this.buttonAdd.Text = "&Add";
			this.buttonAdd.Click += new System.EventHandler(this.buttonAdd_Click);
			// 
			// buttonEdit
			// 
			this.buttonEdit.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
			this.buttonEdit.Location = new System.Drawing.Point(112, 120);
			this.buttonEdit.Name = "buttonEdit";
			this.buttonEdit.TabIndex = 2;
			this.buttonEdit.Text = "&Edit";
			this.buttonEdit.Click += new System.EventHandler(this.buttonEdit_Click);
			// 
			// buttonDelete
			// 
			this.buttonDelete.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
			this.buttonDelete.Location = new System.Drawing.Point(216, 120);
			this.buttonDelete.Name = "buttonDelete";
			this.buttonDelete.TabIndex = 3;
			this.buttonDelete.Text = "&Delete";
			this.buttonDelete.Click += new System.EventHandler(this.buttonDelete_Click);
			// 
			// menuItemAdd
			// 
			this.menuItemAdd.Index = 0;
			this.menuItemAdd.Text = "&Add";
			this.menuItemAdd.Click += new System.EventHandler(this.menuItemAdd_Click);
			// 
			// SettingsForm
			// 
			this.AcceptButton = this.buttonOK;
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.CancelButton = this.buttonCancel;
			this.ClientSize = new System.Drawing.Size(332, 266);
			this.Controls.Add(this.groupBoxState);
			this.Controls.Add(this.groupBoxProcesses);
			this.Controls.Add(this.buttonCancel);
			this.Controls.Add(this.buttonOK);
			this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
			this.MinimumSize = new System.Drawing.Size(340, 300);
			this.Name = "SettingsForm";
			this.Text = "Settings";
			this.Load += new System.EventHandler(this.SettingsForm_Load);
			this.groupBoxProcesses.ResumeLayout(false);
			this.groupBoxState.ResumeLayout(false);
			this.ResumeLayout(false);

		}
		#endregion

		private ArrayList	ProcessActions = new ArrayList();

		bool Initialised = false;

		private void SettingsForm_Load(object sender, System.EventArgs e)
		{
		bool initiallyEnabled,toast;

			SettingsManager.ReadSettings( out initiallyEnabled , out toast , ProcessActions );

			checkBoxEnabled.Checked = initiallyEnabled;
			checkBoxToast.Checked   = toast;

			foreach( ProcessAction p in ProcessActions )
			{
				checkedListBoxProcessActions.Items.Add( p , p.Enabled );
			}

			Initialised = true;

			Activate();
		}

		private void buttonOK_Click(object sender, System.EventArgs e)
		{
			DialogResult = DialogResult.OK;

			SettingsManager.WriteSettings( checkBoxEnabled.Checked , checkBoxToast.Checked , ProcessActions );			

			Close();
		}

		private void buttonCancel_Click(object sender, System.EventArgs e)
		{
			DialogResult = DialogResult.Cancel;

			Close();
		}

		private void menuItemAdd_Click(object sender, System.EventArgs e)
		{
			ProcessAction p = new ProcessAction();
			p.Name = "New Action";

			if ( Edit( p ) )
			{
				checkedListBoxProcessActions.Items.Add( p );
				ProcessActions.Add( p );
			}
		}

		private void menuItemEdit_Click(object sender, System.EventArgs e)
		{
			if ( checkedListBoxProcessActions.SelectedItem == null ) return;

			ProcessAction p = checkedListBoxProcessActions.SelectedItem as ProcessAction;

			Edit( p );
		}

		private void menuItemDelete_Click(object sender, System.EventArgs e)
		{
			if ( checkedListBoxProcessActions.SelectedItem == null ) return;

			ProcessAction p = checkedListBoxProcessActions.SelectedItem as ProcessAction;

			if ( MessageBox.Show( this , "Are you sure you wish to delete " + p.Name + " ?" , "PriorityManager Settings" , MessageBoxButtons.YesNo , MessageBoxIcon.Question ) == DialogResult.Yes )
			{
				checkedListBoxProcessActions.Items.Remove( p );

				ProcessActions.Remove( p );
			}
		}

		private void checkedListBoxProcessActions_ItemCheck(object sender, System.Windows.Forms.ItemCheckEventArgs e)
		{
			if ( !Initialised ) return;

			if ( checkedListBoxProcessActions.SelectedItem == null ) return;

			ProcessAction p = checkedListBoxProcessActions.SelectedItem as ProcessAction;

			p.Enabled = ( e.NewValue == CheckState.Checked );
		}

		private bool Edit( ProcessAction p )
		{
			SettingsItemForm sif = new SettingsItemForm( p );

			return ( sif.ShowDialog( this ) == DialogResult.OK );
		}

		private void buttonAdd_Click(object sender, System.EventArgs e)
		{
			menuItemAdd_Click( sender , e );
		}

		private void buttonEdit_Click(object sender, System.EventArgs e)
		{
			menuItemEdit_Click( sender , e );
		}

		private void buttonDelete_Click(object sender, System.EventArgs e)
		{
			menuItemDelete_Click( sender , e );
		}
	}
}
