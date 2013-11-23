using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using System.Management;
using System.Diagnostics;
using System.Text.RegularExpressions;

namespace PriorityManager
{
	/// <summary>
	/// Summary description for PriorityManager.
	/// </summary>
	public class PriorityManager : System.Windows.Forms.Form
	{
		private System.Windows.Forms.NotifyIcon notifyIcon;
		private System.Windows.Forms.ContextMenu contextMenu;
		private System.Windows.Forms.MenuItem menuItemSettings;
		private System.Windows.Forms.MenuItem menuItemEnabled;
		private System.Windows.Forms.MenuItem menuItemQuit;
		private System.ComponentModel.IContainer components;

		private SettingsForm ActiveSettingsForm = null;

		private ToastForm    ActiveToastForm    = null;

		private ManagementEventWatcher ProcessWatcher = null;

		private bool ToastEnabled = true;

		public ArrayList ProcessActions = new ArrayList();

		public PriorityManager()
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
				if (components != null) 
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
			System.Resources.ResourceManager resources = new System.Resources.ResourceManager(typeof(PriorityManager));
			this.notifyIcon = new System.Windows.Forms.NotifyIcon(this.components);
			this.contextMenu = new System.Windows.Forms.ContextMenu();
			this.menuItemSettings = new System.Windows.Forms.MenuItem();
			this.menuItemEnabled = new System.Windows.Forms.MenuItem();
			this.menuItemQuit = new System.Windows.Forms.MenuItem();
			// 
			// notifyIcon
			// 
			this.notifyIcon.ContextMenu = this.contextMenu;
			this.notifyIcon.Icon = ((System.Drawing.Icon)(resources.GetObject("notifyIcon.Icon")));
			this.notifyIcon.Text = "notifyIcon";
			this.notifyIcon.Visible = true;
			this.notifyIcon.DoubleClick += new System.EventHandler(this.notifyIcon_DoubleClick);
			// 
			// contextMenu
			// 
			this.contextMenu.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
																						this.menuItemSettings,
																						this.menuItemEnabled,
																						this.menuItemQuit});
			// 
			// menuItemSettings
			// 
			this.menuItemSettings.Index = 0;
			this.menuItemSettings.Text = "&Settings";
			this.menuItemSettings.Click += new System.EventHandler(this.menuItemSettings_Click);
			// 
			// menuItemEnabled
			// 
			this.menuItemEnabled.Checked = true;
			this.menuItemEnabled.Index = 1;
			this.menuItemEnabled.Text = "&Enabled";
			this.menuItemEnabled.Click += new System.EventHandler(this.menuItemEnabled_Click);
			// 
			// menuItemQuit
			// 
			this.menuItemQuit.Index = 2;
			this.menuItemQuit.Text = "&Quit";
			this.menuItemQuit.Click += new System.EventHandler(this.menuItemQuit_Click);
			// 
			// PriorityManager
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(240, 38);
			this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
			this.Name = "PriorityManager";
			this.Text = "PriorityManager";
			this.Load += new System.EventHandler(this.PriorityManager_Load);

		}
		#endregion

		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main() 
		{
			if ( !ThisProcessAlreadyExistsForThisUser() )
			{
				Application.Run(new PriorityManager());
			}
		}


		private void PriorityManager_Load(object sender, System.EventArgs e)
		{
			bool initiallyEnabled;

			SettingsManager.ReadSettings( out initiallyEnabled , out ToastEnabled , ProcessActions );

			TopLevel = false;

			menuItemEnabled.Checked = initiallyEnabled;

			if ( initiallyEnabled )
			{
				StartMonitoring();
			}
			else
			{
				StopMonitoring();
			}

			DoProcessActionsForCurrentProcesses();
		}

		private void menuItemQuit_Click(object sender, System.EventArgs e)
		{
			if ( menuItemEnabled.Checked )
			{
				StopMonitoring();
			}

			Close();
		}

		private void menuItemEnabled_Click(object sender, System.EventArgs e)
		{
			menuItemEnabled.Checked = !menuItemEnabled.Checked;

			if ( menuItemEnabled.Checked )
			{
				StartMonitoring();
			}
			else
			{
				notifyIcon.Icon = new Icon( this.GetType() , "Disabled.ico" );
			}
		}

		private void menuItemSettings_Click(object sender, System.EventArgs e)
		{
			if ( ActiveSettingsForm == null )
				{
				ActiveSettingsForm = new SettingsForm();

				if ( ActiveSettingsForm.ShowDialog() == DialogResult.OK )
				{
				bool ignore;

					SettingsManager.ReadSettings( out ignore , out ToastEnabled , ProcessActions );

					DoProcessActionsForCurrentProcesses();
				}

				ActiveSettingsForm = null;
			}
			else
			{
				ActiveSettingsForm.Activate();
			}
		}

		private void notifyIcon_DoubleClick(object sender, System.EventArgs e)
		{
			menuItemSettings_Click( sender , e );
		}

		private void StartMonitoring()
		{
			notifyIcon.Icon = new Icon( this.GetType() , "Enabled.ico" );
			notifyIcon.Text = "PriorityMonitor (Enabled)";

			if ( ProcessWatcher == null )
			{
				WqlEventQuery wmiQuery = new WqlEventQuery( "SELECT * FROM __InstanceCreationEvent WITHIN 2 WHERE TargetInstance ISA \"Win32_Process\"" );
			
				ProcessWatcher = new ManagementEventWatcher( wmiQuery );

				ProcessWatcher.EventArrived +=new EventArrivedEventHandler(ProcessWatcher_EventArrived);
			}

			ProcessWatcher.Start();
		}

		private void StopMonitoring()
		{
			notifyIcon.Icon = new Icon( this.GetType() , "Disabled.ico" );
			notifyIcon.Text = "PriorityMonitor (Disabled)";

			if ( ProcessWatcher == null ) return; // Stop not needed!

			ProcessWatcher.Stop();
		}

		private void ProcessWatcher_EventArrived(object sender, EventArrivedEventArgs e)
		{
			ROOT.CIMV2.Process wmiProcess = new ROOT.CIMV2.Process( (ManagementBaseObject)e.NewEvent["TargetInstance"] );

			Process p = Process.GetProcessById( (int)wmiProcess.ProcessId );

			string thisOwner = GetProcessOwner( Process.GetCurrentProcess() );

			if ( thisOwner == GetProcessOwner( p ) )
			{
				DoProcessAction( p );
			}
		}

		private void DoProcessActionsForCurrentProcesses()
		{
			Process [] pl = Process.GetProcesses();

			string thisOwner = GetProcessOwner( Process.GetCurrentProcess() );

			foreach ( Process p in pl )
			{
				if ( thisOwner == GetProcessOwner( p ) )
				{
					DoProcessAction( p );
				}
			}
		}

		private void DoProcessAction( Process process )
		{
			string name = process.ProcessName;

			try
			{ 
				name = process.MainModule.ModuleName;
			}
			catch
			{
				// Ignore - if it fails just use the name
			}
			
			lock( ProcessActions.SyncRoot )
			{
				foreach ( ProcessAction p in ProcessActions )
				{
					if ( p.Enabled && Regex.IsMatch( name , p.MatchString ) )
					{
						if ( process.PriorityClass != p.PriorityClass )
						{
							process.PriorityClass = p.PriorityClass;

							if ( ToastEnabled )
							{
								ToastForm.AsyncShowToast( 5 ,  "Process \"" + name + "\" set to priority " + p.PriorityClass );
							}
						}
					}
				}
			}
		}

		private static bool ThisProcessAlreadyExistsForThisUser()
		{
			Process thisProcess = Process.GetCurrentProcess();

			string thisOwner = GetProcessOwner( thisProcess );

			Process [] pl = Process.GetProcesses();

			foreach ( Process p in pl )
			{
				if ( ( thisProcess.ProcessName == p.ProcessName ) && ( thisProcess.Id != p.Id ) )
				{
					// Names match but IDs don't - check if user matches
					if ( thisOwner == GetProcessOwner( p ) )
					{
						return true;
					}
				}
			}

			return false;
		}

		private static string GetProcessOwner( Process p )
		{
			string s =  "\\\\.\\root\\CIMV2:Win32_Process.Handle=\"" + p.Id + "\"";

			ManagementPath mp = new ManagementPath( s );

			ROOT.CIMV2.Process wmip = new ROOT.CIMV2.Process( mp );

			string domain,user;

			wmip.GetOwner( out domain , out user );

			return domain + "\\" + user;
		}
	}
}
