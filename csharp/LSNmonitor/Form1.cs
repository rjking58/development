using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using System.Text;
using System.Web;
using System.Net;
using System.IO;

namespace LSNmonitor
{
	/// <summary>
	/// Summary description for Form1.
	/// </summary>
	public class Form1 : System.Windows.Forms.Form
	{
		private System.Windows.Forms.TextBox Results;
		private System.Windows.Forms.Button getHTML;
		private System.Windows.Forms.TextBox enteredURL;
		private System.Windows.Forms.TextBox tbHttpStatus;
		private System.Windows.Forms.TextBox tbLocation;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.TextBox tbCookieCount;
		private System.Windows.Forms.Label label3;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public Form1()
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
			this.Results = new System.Windows.Forms.TextBox();
			this.getHTML = new System.Windows.Forms.Button();
			this.enteredURL = new System.Windows.Forms.TextBox();
			this.tbHttpStatus = new System.Windows.Forms.TextBox();
			this.tbLocation = new System.Windows.Forms.TextBox();
			this.label1 = new System.Windows.Forms.Label();
			this.label2 = new System.Windows.Forms.Label();
			this.tbCookieCount = new System.Windows.Forms.TextBox();
			this.label3 = new System.Windows.Forms.Label();
			this.SuspendLayout();
			// 
			// Results
			// 
			this.Results.Location = new System.Drawing.Point(32, 24);
			this.Results.Multiline = true;
			this.Results.Name = "Results";
			this.Results.Size = new System.Drawing.Size(400, 464);
			this.Results.TabIndex = 0;
			this.Results.Text = "";
			this.Results.TextChanged += new System.EventHandler(this.Results_TextChanged);
			// 
			// getHTML
			// 
			this.getHTML.Location = new System.Drawing.Point(440, 56);
			this.getHTML.Name = "getHTML";
			this.getHTML.Size = new System.Drawing.Size(192, 23);
			this.getHTML.TabIndex = 1;
			this.getHTML.Text = "getHTML";
			this.getHTML.Click += new System.EventHandler(this.button1_Click);
			// 
			// enteredURL
			// 
			this.enteredURL.Location = new System.Drawing.Point(440, 24);
			this.enteredURL.Name = "enteredURL";
			this.enteredURL.Size = new System.Drawing.Size(256, 20);
			this.enteredURL.TabIndex = 2;
			this.enteredURL.Text = "http://codo-linux1.bytemark.co.uk:8080/LSN/GameManager";
			// 
			// tbHttpStatus
			// 
			this.tbHttpStatus.Location = new System.Drawing.Point(536, 112);
			this.tbHttpStatus.Name = "tbHttpStatus";
			this.tbHttpStatus.ReadOnly = true;
			this.tbHttpStatus.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
			this.tbHttpStatus.Size = new System.Drawing.Size(152, 20);
			this.tbHttpStatus.TabIndex = 3;
			this.tbHttpStatus.Text = "";
			// 
			// tbLocation
			// 
			this.tbLocation.Location = new System.Drawing.Point(536, 136);
			this.tbLocation.Name = "tbLocation";
			this.tbLocation.ReadOnly = true;
			this.tbLocation.Size = new System.Drawing.Size(152, 20);
			this.tbLocation.TabIndex = 4;
			this.tbLocation.Text = "";
			// 
			// label1
			// 
			this.label1.Location = new System.Drawing.Point(440, 112);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(56, 16);
			this.label1.TabIndex = 5;
			this.label1.Text = "httpStatus";
			this.label1.Click += new System.EventHandler(this.label1_Click);
			// 
			// label2
			// 
			this.label2.Location = new System.Drawing.Point(440, 136);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(56, 16);
			this.label2.TabIndex = 6;
			this.label2.Text = "Location";
			// 
			// tbCookieCount
			// 
			this.tbCookieCount.Location = new System.Drawing.Point(536, 160);
			this.tbCookieCount.Name = "tbCookieCount";
			this.tbCookieCount.ReadOnly = true;
			this.tbCookieCount.Size = new System.Drawing.Size(152, 20);
			this.tbCookieCount.TabIndex = 7;
			this.tbCookieCount.Text = "";
			// 
			// label3
			// 
			this.label3.Location = new System.Drawing.Point(440, 160);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(80, 16);
			this.label3.TabIndex = 8;
			this.label3.Text = "CookieCount";
			// 
			// Form1
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(720, 518);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		  this.label3,
																		  this.tbCookieCount,
																		  this.label2,
																		  this.label1,
																		  this.tbLocation,
																		  this.tbHttpStatus,
																		  this.enteredURL,
																		  this.getHTML,
																		  this.Results});
			this.Name = "Form1";
			this.Text = "Form1";
			this.ResumeLayout(false);

		}
		#endregion

		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main() 
		{
			Application.Run(new Form1());
		}

		private void button1_Click(object sender, System.EventArgs e)
		{
			HttpWebRequest 		wreq;
			HttpWebResponse 	wresp;

			Stream            	stream1;
			StreamReader      	stream_rdr1;
			String            	html;

			CookieCollection cc = new CookieCollection();
			CookieContainer c_cnt = new CookieContainer();
//			Cookie cook1 = new Cookie("LSNpassword","amemggjm","/LSN/GameManager","codo-linux1.bytemark.co.uk");
//			Cookie cook2 = new Cookie("LSNplayerName","weezl","/LSN/GameManager","codo-linux1.bytemark.co.uk");
//			Cookie cook3 = new Cookie("LSNplayer_id","4135","/LSN/GameManager","codo-linux1.bytemark.co.uk");    
//			cc.Add(cook1);
//			cc.Add(cook2);
//			cc.Add(cook3);
//			c_cnt.Add(cc);

			wreq =  (HttpWebRequest) WebRequest.Create(enteredURL.Text);
			wreq.AllowAutoRedirect = false;
			wreq.CookieContainer = c_cnt;

			wresp = (HttpWebResponse) wreq.GetResponse();
			HttpStatusCode resp_stat_code = wresp.StatusCode;
			tbHttpStatus.Text = resp_stat_code.ToString();
			switch (resp_stat_code)
			{
				case HttpStatusCode.Found :
				{
					tbLocation.Text = wresp.GetResponseHeader("Location");
					break;
				}
				default:
				{
					Results.Text = "dunno what response we got";
					break;
				}
			}

			int responseCookCount = wresp.Cookies.Count;
			tbCookieCount.Text = responseCookCount.ToString();
			if (responseCookCount > 0)
			{
				// do something with the cookies
			}

			stream1 = wresp.GetResponseStream();
			stream_rdr1 = new StreamReader(stream1);
			html = stream_rdr1.ReadToEnd();
			Results.Text = html;
			wresp.Close();

		}

		private void Results_TextChanged(object sender, System.EventArgs e)
		{
		
		}

		private void label1_Click(object sender, System.EventArgs e)
		{
		
		}
	}
}
