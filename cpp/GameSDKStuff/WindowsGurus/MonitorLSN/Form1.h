#pragma once


namespace MonitorLSN
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
   using namespace System::Text;	
   using namespace System::Net;
   using namespace System::Web;   
   using namespace System::IO;

	/// <summary> 
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the 
	///          'Resource File Name' property for the managed resource compiler tool 
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public __gc class Form1 : public System::Windows::Forms::Form
	{	
	public:
		Form1(void)
		{
			InitializeComponent();
		}
  
	protected:
		void Dispose(Boolean disposing)
		{
			if (disposing && components)
			{
				components->Dispose();
			}
			__super::Dispose(disposing);
		}
   private: System::Windows::Forms::TextBox *  textBox1;
   private: System::Windows::Forms::TextBox *  textBox2;
   private: System::Windows::Forms::Button *  button1;
   
   private: System::String * shown_strings[];
   private: static const int STRING_ARY_SZ = 10;
   private: System::Windows::Forms::Label *  label1;
   private: System::Windows::Forms::Label *  label2;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container * components;

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
         System::Configuration::AppSettingsReader *  configurationAppSettings = new System::Configuration::AppSettingsReader();
         this->textBox1 = new System::Windows::Forms::TextBox();
         this->textBox2 = new System::Windows::Forms::TextBox();
         this->button1 = new System::Windows::Forms::Button();
         this->label1 = new System::Windows::Forms::Label();
         this->label2 = new System::Windows::Forms::Label();
         this->SuspendLayout();
         // 
         // textBox1
         // 
         this->textBox1->Location = System::Drawing::Point(16, 40);
         this->textBox1->Multiline = (*__try_cast<__box System::Boolean *  >(configurationAppSettings->GetValue(S"textBox1.Multiline", __typeof(System::Boolean))));
         this->textBox1->Name = S"textBox1";
         this->textBox1->Size = System::Drawing::Size(352, 360);
         this->textBox1->TabIndex = 0;
         this->textBox1->Text = S"";
         this->textBox1->TextChanged += new System::EventHandler(this, textBox1_TextChanged);
         // 
         // textBox2
         // 
         this->textBox2->Location = System::Drawing::Point(376, 16);
         this->textBox2->Name = S"textBox2";
         this->textBox2->Size = System::Drawing::Size(216, 20);
         this->textBox2->TabIndex = 1;
         this->textBox2->Text = S"http://codo-linux1.bytemark.co.uk:8080/LSN/GameManager";
         this->textBox2->TextChanged += new System::EventHandler(this, textBox2_TextChanged);
         // 
         // button1
         // 
         this->button1->Location = System::Drawing::Point(376, 48);
         this->button1->Name = S"button1";
         this->button1->TabIndex = 2;
         this->button1->Text = S"GetHTML";
         this->button1->Click += new System::EventHandler(this, button1_Click);
         // 
         // label1
         // 
         this->label1->Location = System::Drawing::Point(312, 16);
         this->label1->Name = S"label1";
         this->label1->Size = System::Drawing::Size(56, 16);
         this->label1->TabIndex = 3;
         this->label1->Text = S"EnterURL";
         this->label1->Click += new System::EventHandler(this, label1_Click);
         // 
         // label2
         // 
         this->label2->Location = System::Drawing::Point(16, 16);
         this->label2->Name = S"label2";
         this->label2->Size = System::Drawing::Size(88, 16);
         this->label2->TabIndex = 4;
         this->label2->Text = S"HTML returned";
         this->label2->Click += new System::EventHandler(this, label2_Click);
         // 
         // Form1
         // 
         this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
         this->ClientSize = System::Drawing::Size(600, 414);
         this->Controls->Add(this->label2);
         this->Controls->Add(this->label1);
         this->Controls->Add(this->button1);
         this->Controls->Add(this->textBox2);
         this->Controls->Add(this->textBox1);
         this->Name = S"Form1";
         this->Text = S"Form1";
         this->Load += new System::EventHandler(this, Form1_Load);
         this->ResumeLayout(false);

      }	
   private: System::Void Form1_Load(System::Object *  sender, System::EventArgs *  e)
            {
               shown_strings = new System::String *[STRING_ARY_SZ];
               for ( int string_ofst = 0; 
                     string_ofst < STRING_ARY_SZ; 
                     string_ofst ++    )
               {
                  shown_strings[string_ofst] = 0;
               }    
              
            }

   private: System::Void button1_Click(System::Object *  sender, System::EventArgs *  e)
            {
//               System::Text::StringBuilder *sb = new System::Text::StringBuilder();
//               for ( int string_ofst = STRING_ARY_SZ -2; 
//                     string_ofst >= 0; 
//                     string_ofst --    )
//               {
//                  shown_strings[string_ofst+1] = shown_strings[string_ofst];
//               }               
//               shown_strings[0] = textBox2->Text;               
//
//               // woohoo!  it is SO easy!
//               textBox1->Lines = shown_strings;               
               // get the URL info..
               HttpWebRequest    *wreq;
               HttpWebResponse   *wresp;
               
               Stream            *stream1;
               StreamReader      *stream_rdr1;
               String            *html;

               // cookie contents to server page..
               // path is /LSN/GameManager
               // domain is codo-linux1.bytemark.co.uk
               // LSNpassword="amemggjm";
               // LSNplayerName="weezl";
               // LSNplayer_id="4135";

               
               CookieCollection *cc = new CookieCollection();
               CookieContainer *c_cnt = new CookieContainer();
               Cookie * cook1 = new Cookie("LSNpassword","amemggjm","/LSN/GameManager","codo-linux1.bytemark.co.uk");
               Cookie * cook2 = new Cookie("LSNplayerName","weezl","/LSN/GameManager","codo-linux1.bytemark.co.uk");
               Cookie * cook3 = new Cookie("LSNplayer_id","4135","/LSN/GameManager","codo-linux1.bytemark.co.uk");    
               cc->Add(cook1);
               cc->Add(cook2);
               cc->Add(cook3);
               c_cnt->Add(cc);
               
               wreq = dynamic_cast<HttpWebRequest *> (WebRequest::Create(textBox2->Text));

               // specific cookies added to request so that user authenticates..
               // 
               wreq->CookieContainer = c_cnt;
               
               wresp = dynamic_cast<HttpWebResponse *> (wreq->GetResponse());
               
               stream1 = wresp->GetResponseStream();
               stream_rdr1 = new StreamReader(stream1);
               html = stream_rdr1->ReadToEnd();
               textBox1->Text = html;
               
               wreq->Finalize();
               wresp->Finalize();
               stream_rdr1->Finalize();
               html->Finalize();
               cc->Finalize();
               c_cnt->Finalize();
               cook1->Finalize();
               cook2->Finalize();
               cook3->Finalize();    
               
            }

   private: System::Void textBox2_TextChanged(System::Object *  sender, System::EventArgs *  e)
            {
               
            }

   private: System::Void textBox1_TextChanged(System::Object *  sender, System::EventArgs *  e)
            {
            }

private: System::Void label1_Click(System::Object *  sender, System::EventArgs *  e)
         {
         }

private: System::Void label2_Click(System::Object *  sender, System::EventArgs *  e)
         {
         }

};
}


