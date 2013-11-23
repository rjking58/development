using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Threading;

namespace PriorityManager
{
	/// <summary>
	/// Summary description for ToastForm.
	/// </summary>
	public class ToastForm : System.Windows.Forms.Form
	{
		private System.Windows.Forms.Label labelText;
		private System.Windows.Forms.Timer timerAutoClose;
		private System.ComponentModel.IContainer components;

		public ToastForm()
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
			this.components = new System.ComponentModel.Container();
			this.labelText = new System.Windows.Forms.Label();
			this.timerAutoClose = new System.Windows.Forms.Timer(this.components);
			this.SuspendLayout();
			// 
			// labelText
			// 
			this.labelText.Location = new System.Drawing.Point(8, 8);
			this.labelText.Name = "labelText";
			this.labelText.Size = new System.Drawing.Size(272, 24);
			this.labelText.TabIndex = 0;
			this.labelText.Text = "labelText";
			// 
			// timerAutoClose
			// 
			this.timerAutoClose.Tick += new System.EventHandler(this.timerAutoClose_Tick);
			// 
			// ToastForm
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(290, 32);
			this.Controls.Add(this.labelText);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "ToastForm";
			this.ShowInTaskbar = false;
			this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Hide;
			this.Text = "PriorityManager Alert";
			this.TopMost = true;
			this.Load += new System.EventHandler(this.ToastForm_Load);
			this.ResumeLayout(false);

		}
		#endregion

		public static void AsyncShowToast( int seconds , string text )
		{
			ToastForm toast = new ToastForm();

			toast.timerAutoClose.Interval = 1000 * seconds;

			toast.labelText.Text = text;
			
			Thread t = new Thread(	new ThreadStart( toast.AsynchShowDialog ) );

			t.Start();
		}

		private void AsynchShowDialog()
		{
			ShowDialog();
		}

		private void ToastForm_Load(object sender, System.EventArgs e)
		{
			Rectangle workArea = Screen.GetWorkingArea( new Point( 0 , 0 ) );

			SetBounds( workArea.Right-Width , workArea.Bottom-Height , Width , Height );

			timerAutoClose.Enabled = true;
		}

		private void timerAutoClose_Tick(object sender, System.EventArgs e)
		{
			Close();
		}
	}
}
