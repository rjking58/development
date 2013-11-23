using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using System.IO;


//#define min(x,y) ((x) < (y) ? (x) : (y))
//#define max(x,y) ((x) > (y) ? (x) : (y))

struct CharacterInfoStruct
{
   public uint     m_SkillOfst;
   public uint     m_FirstAvailable;
   public string   m_SkillName;
   public uint     m_previousLevel;
   public CharacterInfoStruct( uint     SkillOfst,
                               uint     FirstAvailable,
                               string   SkillName )
   {
      m_SkillOfst       = SkillOfst;
      m_FirstAvailable  = FirstAvailable;
      m_SkillName       = SkillName;
      m_previousLevel   = 0;
   }
};
   


enum PALADIN_SKILLS
{
   sacrifice         = 0,
   smite             ,
   might             ,
   prayer            ,
   resist_fire       ,
   holy_bolt         , //6
   holy_fire         ,
   thorns            ,
   defiance          ,
   resist_cold       ,
   zeal              , //12
   charge            ,
   blessed_aim       ,
   cleansing         ,
   resist_lightning  ,
   vengeance         ,  // 18
   blessed_hammer    ,
   concentration     ,
   holy_freeze       ,
   vigor             ,
   conversion        , // 24
   holy_shield       ,
   holy_shock        ,
   sanctuary         ,
   meditation        ,
   fist_of_heavens   , //30
   fanatacism        ,
   conviction        ,
   redemption        ,
   salvation
};


namespace Diablo2ReSkller
{
	/// <summary>
	/// Summary description for Form1.
	/// </summary>


   
   public class Form1 : System.Windows.Forms.Form
   {
      private System.ComponentModel.IContainer components;


      private System.Windows.Forms.ToolTip toolTip1;
      private System.Windows.Forms.MainMenu mainMenu1;
      private System.Windows.Forms.MenuItem menuItem1;
      private System.Windows.Forms.MenuItem File_Save;
      private System.Windows.Forms.MenuItem File_Open;
        
        
      byte[]  m_d2sBuffer;
      uint    m_skill_ofst;
      uint    m_d2sBufferSize;
      byte    m_char_level; 
      uint    m_leftoverSkillPoints;
      private System.Windows.Forms.Label Label1;
      private System.Windows.Forms.Label FileNameLbl;
      private System.Windows.Forms.Label label2;
      private System.Windows.Forms.Label label3;
      private System.Windows.Forms.Label ChecksumLbl;
      private System.Windows.Forms.Label CalcedChecksumLbl;
      String  m_Filename;

      private const uint CHECKSUM_OFST       = 12;
      private const uint CHARACTERLEVEL_OFST = 43;
      private System.Windows.Forms.Label label4;
      private System.Windows.Forms.Label CharLevelLbl;
      private System.Windows.Forms.Label Skill1Lbl;
      private System.Windows.Forms.Label Skill2Lbl;
      private System.Windows.Forms.Label Skill3Lbl;
      private System.Windows.Forms.Label Skill4Lbl;
      private System.Windows.Forms.Label Skill5Lbl;
      private System.Windows.Forms.Label Skill6Lbl;
      private System.Windows.Forms.Label Skill7Lbl;
      private System.Windows.Forms.Label Skill8Lbl;
      private System.Windows.Forms.Label Skill9Lbl;
      private System.Windows.Forms.Label Skill10Lbl;
      private System.Windows.Forms.Label Skill20Lbl;
      private System.Windows.Forms.Label Skill19Lbl;
      private System.Windows.Forms.Label Skill18Lbl;
      private System.Windows.Forms.Label Skill17Lbl;
      private System.Windows.Forms.Label Skill16Lbl;
      private System.Windows.Forms.Label Skill15Lbl;
      private System.Windows.Forms.Label Skill14Lbl;
      private System.Windows.Forms.Label Skill13Lbl;
      private System.Windows.Forms.Label Skill12Lbl;
      private System.Windows.Forms.Label Skill11Lbl;
      private System.Windows.Forms.Label Skill30Lbl;
      private System.Windows.Forms.Label Skill29Lbl;
      private System.Windows.Forms.Label Skill28Lbl;
      private System.Windows.Forms.Label Skill27Lbl;
      private System.Windows.Forms.Label Skill26Lbl;
      private System.Windows.Forms.Label Skill25Lbl;
      private System.Windows.Forms.Label Skill24Lbl;
      private System.Windows.Forms.Label Skill23Lbl;
      private System.Windows.Forms.Label Skill22Lbl;
      private System.Windows.Forms.Label Skill21Lbl;
      private System.Windows.Forms.TextBox LeftOverSkillPointsTxtBox;
      private System.Windows.Forms.Label label5;
      private System.Windows.Forms.NumericUpDown Skill1;
      private System.Windows.Forms.NumericUpDown Skill2;
      private System.Windows.Forms.NumericUpDown Skill3;
      private System.Windows.Forms.NumericUpDown Skill4;
      private System.Windows.Forms.NumericUpDown Skill5;
      private System.Windows.Forms.NumericUpDown Skill6;
      private System.Windows.Forms.NumericUpDown Skill7;
      private System.Windows.Forms.NumericUpDown Skill8;
      private System.Windows.Forms.NumericUpDown Skill9;
      private System.Windows.Forms.NumericUpDown Skill10;
      private System.Windows.Forms.NumericUpDown Skill20;
      private System.Windows.Forms.NumericUpDown Skill19;
      private System.Windows.Forms.NumericUpDown Skill18;
      private System.Windows.Forms.NumericUpDown Skill17;
      private System.Windows.Forms.NumericUpDown Skill16;
      private System.Windows.Forms.NumericUpDown Skill15;
      private System.Windows.Forms.NumericUpDown Skill14;
      private System.Windows.Forms.NumericUpDown Skill13;
      private System.Windows.Forms.NumericUpDown Skill12;
      private System.Windows.Forms.NumericUpDown Skill11;
      private System.Windows.Forms.NumericUpDown Skill30;
      private System.Windows.Forms.NumericUpDown Skill29;
      private System.Windows.Forms.NumericUpDown Skill28;
      private System.Windows.Forms.NumericUpDown Skill27;
      private System.Windows.Forms.NumericUpDown Skill26;
      private System.Windows.Forms.NumericUpDown Skill25;
      private System.Windows.Forms.NumericUpDown Skill24;
      private System.Windows.Forms.NumericUpDown Skill23;
      private System.Windows.Forms.NumericUpDown Skill22;
      private System.Windows.Forms.NumericUpDown Skill21;

      CharacterInfoStruct[]   PaladinSkills;
      CharacterInfoStruct[]   CurrentSkills;
      bool                    mReadAndActive;


      public Form1()
		{
         //
			// Required for Windows Form Designer support
			//
			InitializeComponent();

			//
			// TODO: Add any constructor code after InitializeComponent call
			//
         m_d2sBufferSize = 0;
         m_d2sBuffer = new byte[5000];
         m_skill_ofst = 0;
         m_char_level = 0;
         m_leftoverSkillPoints = 0;
         PaladinSkills = new CharacterInfoStruct [30];
         CurrentSkills = PaladinSkills;
         PaladinSkills[ 0] = new CharacterInfoStruct( 0, 1,"sacrifice       "); 
         PaladinSkills[ 1] = new CharacterInfoStruct( 1, 1,"smite           "); 
         PaladinSkills[ 2] = new CharacterInfoStruct( 2, 1,"might           "); 
         PaladinSkills[ 3] = new CharacterInfoStruct( 3, 1,"prayer          "); 
         PaladinSkills[ 4] = new CharacterInfoStruct( 4, 1,"resist_fire     "); 
         PaladinSkills[ 5] = new CharacterInfoStruct( 5, 6,"holy_bolt       "); 
         PaladinSkills[ 6] = new CharacterInfoStruct( 6, 6,"holy_fire       "); 
         PaladinSkills[ 7] = new CharacterInfoStruct( 7, 6,"thorns          "); 
         PaladinSkills[ 8] = new CharacterInfoStruct( 8, 6,"defiance        "); 
         PaladinSkills[ 9] = new CharacterInfoStruct( 9, 6,"resist_cold     "); 
         PaladinSkills[10] = new CharacterInfoStruct(10,12,"zeal            "); 
         PaladinSkills[11] = new CharacterInfoStruct(11,12,"charge          "); 
         PaladinSkills[12] = new CharacterInfoStruct(12,12,"blessed_aim     "); 
         PaladinSkills[13] = new CharacterInfoStruct(13,12,"cleansing       "); 
         PaladinSkills[14] = new CharacterInfoStruct(14,12,"resist_lightning"); 
         PaladinSkills[15] = new CharacterInfoStruct(15,18,"vengeance       "); 
         PaladinSkills[16] = new CharacterInfoStruct(16,18,"blessed_hammer  "); 
         PaladinSkills[17] = new CharacterInfoStruct(17,18,"concentration   "); 
         PaladinSkills[18] = new CharacterInfoStruct(18,18,"holy_freeze     "); 
         PaladinSkills[19] = new CharacterInfoStruct(19,18,"vigor           "); 
         PaladinSkills[20] = new CharacterInfoStruct(20,24,"conversion      "); 
         PaladinSkills[21] = new CharacterInfoStruct(21,24,"holy_shield     "); 
         PaladinSkills[22] = new CharacterInfoStruct(22,24,"holy_shock      "); 
         PaladinSkills[23] = new CharacterInfoStruct(23,24,"sanctuary       "); 
         PaladinSkills[24] = new CharacterInfoStruct(24,24,"meditation      "); 
         PaladinSkills[25] = new CharacterInfoStruct(25,30,"fist_of_heavens "); 
         PaladinSkills[26] = new CharacterInfoStruct(26,30,"fanatacism      "); 
         PaladinSkills[27] = new CharacterInfoStruct(27,30,"conviction      "); 
         PaladinSkills[28] = new CharacterInfoStruct(28,30,"redemption      "); 
         PaladinSkills[29] = new CharacterInfoStruct(29,30,"salvation       "); 
         
         LeftOverSkillPointsTxtBox.Text = String.Format("{0:d2}",m_leftoverSkillPoints);

         mReadAndActive = false;
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
         this.toolTip1 = new System.Windows.Forms.ToolTip(this.components);
         this.mainMenu1 = new System.Windows.Forms.MainMenu();
         this.menuItem1 = new System.Windows.Forms.MenuItem();
         this.File_Save = new System.Windows.Forms.MenuItem();
         this.File_Open = new System.Windows.Forms.MenuItem();
         this.Label1 = new System.Windows.Forms.Label();
         this.FileNameLbl = new System.Windows.Forms.Label();
         this.label2 = new System.Windows.Forms.Label();
         this.label3 = new System.Windows.Forms.Label();
         this.ChecksumLbl = new System.Windows.Forms.Label();
         this.CalcedChecksumLbl = new System.Windows.Forms.Label();
         this.label4 = new System.Windows.Forms.Label();
         this.CharLevelLbl = new System.Windows.Forms.Label();
         this.Skill1 = new System.Windows.Forms.NumericUpDown();
         this.Skill1Lbl = new System.Windows.Forms.Label();
         this.Skill2Lbl = new System.Windows.Forms.Label();
         this.Skill2 = new System.Windows.Forms.NumericUpDown();
         this.Skill3Lbl = new System.Windows.Forms.Label();
         this.Skill3 = new System.Windows.Forms.NumericUpDown();
         this.Skill4Lbl = new System.Windows.Forms.Label();
         this.Skill4 = new System.Windows.Forms.NumericUpDown();
         this.Skill5Lbl = new System.Windows.Forms.Label();
         this.Skill5 = new System.Windows.Forms.NumericUpDown();
         this.Skill6Lbl = new System.Windows.Forms.Label();
         this.Skill6 = new System.Windows.Forms.NumericUpDown();
         this.Skill7Lbl = new System.Windows.Forms.Label();
         this.Skill7 = new System.Windows.Forms.NumericUpDown();
         this.Skill8Lbl = new System.Windows.Forms.Label();
         this.Skill8 = new System.Windows.Forms.NumericUpDown();
         this.Skill9Lbl = new System.Windows.Forms.Label();
         this.Skill9 = new System.Windows.Forms.NumericUpDown();
         this.Skill10Lbl = new System.Windows.Forms.Label();
         this.Skill10 = new System.Windows.Forms.NumericUpDown();
         this.Skill20Lbl = new System.Windows.Forms.Label();
         this.Skill20 = new System.Windows.Forms.NumericUpDown();
         this.Skill19Lbl = new System.Windows.Forms.Label();
         this.Skill19 = new System.Windows.Forms.NumericUpDown();
         this.Skill18Lbl = new System.Windows.Forms.Label();
         this.Skill18 = new System.Windows.Forms.NumericUpDown();
         this.Skill17Lbl = new System.Windows.Forms.Label();
         this.Skill17 = new System.Windows.Forms.NumericUpDown();
         this.Skill16Lbl = new System.Windows.Forms.Label();
         this.Skill16 = new System.Windows.Forms.NumericUpDown();
         this.Skill15Lbl = new System.Windows.Forms.Label();
         this.Skill15 = new System.Windows.Forms.NumericUpDown();
         this.Skill14Lbl = new System.Windows.Forms.Label();
         this.Skill14 = new System.Windows.Forms.NumericUpDown();
         this.Skill13Lbl = new System.Windows.Forms.Label();
         this.Skill13 = new System.Windows.Forms.NumericUpDown();
         this.Skill12Lbl = new System.Windows.Forms.Label();
         this.Skill12 = new System.Windows.Forms.NumericUpDown();
         this.Skill11Lbl = new System.Windows.Forms.Label();
         this.Skill11 = new System.Windows.Forms.NumericUpDown();
         this.Skill30Lbl = new System.Windows.Forms.Label();
         this.Skill30 = new System.Windows.Forms.NumericUpDown();
         this.Skill29Lbl = new System.Windows.Forms.Label();
         this.Skill29 = new System.Windows.Forms.NumericUpDown();
         this.Skill28Lbl = new System.Windows.Forms.Label();
         this.Skill28 = new System.Windows.Forms.NumericUpDown();
         this.Skill27Lbl = new System.Windows.Forms.Label();
         this.Skill27 = new System.Windows.Forms.NumericUpDown();
         this.Skill26Lbl = new System.Windows.Forms.Label();
         this.Skill26 = new System.Windows.Forms.NumericUpDown();
         this.Skill25Lbl = new System.Windows.Forms.Label();
         this.Skill25 = new System.Windows.Forms.NumericUpDown();
         this.Skill24Lbl = new System.Windows.Forms.Label();
         this.Skill24 = new System.Windows.Forms.NumericUpDown();
         this.Skill23Lbl = new System.Windows.Forms.Label();
         this.Skill23 = new System.Windows.Forms.NumericUpDown();
         this.Skill22Lbl = new System.Windows.Forms.Label();
         this.Skill22 = new System.Windows.Forms.NumericUpDown();
         this.Skill21Lbl = new System.Windows.Forms.Label();
         this.Skill21 = new System.Windows.Forms.NumericUpDown();
         this.LeftOverSkillPointsTxtBox = new System.Windows.Forms.TextBox();
         this.label5 = new System.Windows.Forms.Label();
         ((System.ComponentModel.ISupportInitialize)(this.Skill1)).BeginInit();
         ((System.ComponentModel.ISupportInitialize)(this.Skill2)).BeginInit();
         ((System.ComponentModel.ISupportInitialize)(this.Skill3)).BeginInit();
         ((System.ComponentModel.ISupportInitialize)(this.Skill4)).BeginInit();
         ((System.ComponentModel.ISupportInitialize)(this.Skill5)).BeginInit();
         ((System.ComponentModel.ISupportInitialize)(this.Skill6)).BeginInit();
         ((System.ComponentModel.ISupportInitialize)(this.Skill7)).BeginInit();
         ((System.ComponentModel.ISupportInitialize)(this.Skill8)).BeginInit();
         ((System.ComponentModel.ISupportInitialize)(this.Skill9)).BeginInit();
         ((System.ComponentModel.ISupportInitialize)(this.Skill10)).BeginInit();
         ((System.ComponentModel.ISupportInitialize)(this.Skill20)).BeginInit();
         ((System.ComponentModel.ISupportInitialize)(this.Skill19)).BeginInit();
         ((System.ComponentModel.ISupportInitialize)(this.Skill18)).BeginInit();
         ((System.ComponentModel.ISupportInitialize)(this.Skill17)).BeginInit();
         ((System.ComponentModel.ISupportInitialize)(this.Skill16)).BeginInit();
         ((System.ComponentModel.ISupportInitialize)(this.Skill15)).BeginInit();
         ((System.ComponentModel.ISupportInitialize)(this.Skill14)).BeginInit();
         ((System.ComponentModel.ISupportInitialize)(this.Skill13)).BeginInit();
         ((System.ComponentModel.ISupportInitialize)(this.Skill12)).BeginInit();
         ((System.ComponentModel.ISupportInitialize)(this.Skill11)).BeginInit();
         ((System.ComponentModel.ISupportInitialize)(this.Skill30)).BeginInit();
         ((System.ComponentModel.ISupportInitialize)(this.Skill29)).BeginInit();
         ((System.ComponentModel.ISupportInitialize)(this.Skill28)).BeginInit();
         ((System.ComponentModel.ISupportInitialize)(this.Skill27)).BeginInit();
         ((System.ComponentModel.ISupportInitialize)(this.Skill26)).BeginInit();
         ((System.ComponentModel.ISupportInitialize)(this.Skill25)).BeginInit();
         ((System.ComponentModel.ISupportInitialize)(this.Skill24)).BeginInit();
         ((System.ComponentModel.ISupportInitialize)(this.Skill23)).BeginInit();
         ((System.ComponentModel.ISupportInitialize)(this.Skill22)).BeginInit();
         ((System.ComponentModel.ISupportInitialize)(this.Skill21)).BeginInit();
         this.SuspendLayout();
         // 
         // mainMenu1
         // 
         this.mainMenu1.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
                                                                                  this.menuItem1});
         // 
         // menuItem1
         // 
         this.menuItem1.Index = 0;
         this.menuItem1.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
                                                                                  this.File_Save,
                                                                                  this.File_Open});
         this.menuItem1.Text = "&File";
         // 
         // File_Save
         // 
         this.File_Save.Index = 0;
         this.File_Save.Text = "&Save";
         this.File_Save.Click += new System.EventHandler(this.File_Save_Click);
         // 
         // File_Open
         // 
         this.File_Open.Index = 1;
         this.File_Open.Text = "&Open";
         this.File_Open.Click += new System.EventHandler(this.File_Open_Click);
         // 
         // Label1
         // 
         this.Label1.ImageAlign = System.Drawing.ContentAlignment.MiddleRight;
         this.Label1.Location = new System.Drawing.Point(200, 16);
         this.Label1.Name = "Label1";
         this.Label1.Size = new System.Drawing.Size(56, 16);
         this.Label1.TabIndex = 0;
         this.Label1.Text = "FileName:";
         this.Label1.TextAlign = System.Drawing.ContentAlignment.TopRight;
         // 
         // FileNameLbl
         // 
         this.FileNameLbl.Location = new System.Drawing.Point(264, 16);
         this.FileNameLbl.Name = "FileNameLbl";
         this.FileNameLbl.Size = new System.Drawing.Size(344, 16);
         this.FileNameLbl.TabIndex = 1;
         // 
         // label2
         // 
         this.label2.ImageAlign = System.Drawing.ContentAlignment.MiddleRight;
         this.label2.Location = new System.Drawing.Point(192, 40);
         this.label2.Name = "label2";
         this.label2.Size = new System.Drawing.Size(64, 16);
         this.label2.TabIndex = 2;
         this.label2.Text = "CheckSum:";
         this.label2.TextAlign = System.Drawing.ContentAlignment.TopRight;
         // 
         // label3
         // 
         this.label3.Location = new System.Drawing.Point(152, 64);
         this.label3.Name = "label3";
         this.label3.Size = new System.Drawing.Size(104, 16);
         this.label3.TabIndex = 3;
         this.label3.Text = "Calc\'d CheckSum:";
         this.label3.TextAlign = System.Drawing.ContentAlignment.TopRight;
         // 
         // ChecksumLbl
         // 
         this.ChecksumLbl.Location = new System.Drawing.Point(264, 40);
         this.ChecksumLbl.Name = "ChecksumLbl";
         this.ChecksumLbl.Size = new System.Drawing.Size(120, 16);
         this.ChecksumLbl.TabIndex = 4;
         // 
         // CalcedChecksumLbl
         // 
         this.CalcedChecksumLbl.Location = new System.Drawing.Point(264, 64);
         this.CalcedChecksumLbl.Name = "CalcedChecksumLbl";
         this.CalcedChecksumLbl.Size = new System.Drawing.Size(120, 16);
         this.CalcedChecksumLbl.TabIndex = 5;
         // 
         // label4
         // 
         this.label4.Location = new System.Drawing.Point(184, 88);
         this.label4.Name = "label4";
         this.label4.Size = new System.Drawing.Size(72, 16);
         this.label4.TabIndex = 6;
         this.label4.Text = "Char. Level:";
         this.label4.TextAlign = System.Drawing.ContentAlignment.TopRight;
         // 
         // CharLevelLbl
         // 
         this.CharLevelLbl.Location = new System.Drawing.Point(264, 88);
         this.CharLevelLbl.Name = "CharLevelLbl";
         this.CharLevelLbl.Size = new System.Drawing.Size(120, 16);
         this.CharLevelLbl.TabIndex = 7;
         // 
         // Skill1
         // 
         this.Skill1.AccessibleName = "";
         this.Skill1.Enabled = false;
         this.Skill1.Location = new System.Drawing.Point(104, 120);
         this.Skill1.Name = "Skill1";
         this.Skill1.Size = new System.Drawing.Size(40, 20);
         this.Skill1.TabIndex = 8;
         this.Skill1.ValueChanged += new System.EventHandler(this.numericUpDown1_ValueChanged);
         // 
         // Skill1Lbl
         // 
         this.Skill1Lbl.Location = new System.Drawing.Point(24, 120);
         this.Skill1Lbl.Name = "Skill1Lbl";
         this.Skill1Lbl.Size = new System.Drawing.Size(72, 24);
         this.Skill1Lbl.TabIndex = 9;
         this.Skill1Lbl.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
         // 
         // Skill2Lbl
         // 
         this.Skill2Lbl.Location = new System.Drawing.Point(24, 152);
         this.Skill2Lbl.Name = "Skill2Lbl";
         this.Skill2Lbl.Size = new System.Drawing.Size(72, 24);
         this.Skill2Lbl.TabIndex = 11;
         this.Skill2Lbl.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
         // 
         // Skill2
         // 
         this.Skill2.AccessibleName = "";
         this.Skill2.Enabled = false;
         this.Skill2.Location = new System.Drawing.Point(104, 152);
         this.Skill2.Name = "Skill2";
         this.Skill2.Size = new System.Drawing.Size(40, 20);
         this.Skill2.TabIndex = 10;
         this.Skill2.ValueChanged += new System.EventHandler(this.Skill2_ValueChanged);
         // 
         // Skill3Lbl
         // 
         this.Skill3Lbl.Location = new System.Drawing.Point(24, 184);
         this.Skill3Lbl.Name = "Skill3Lbl";
         this.Skill3Lbl.Size = new System.Drawing.Size(72, 24);
         this.Skill3Lbl.TabIndex = 13;
         this.Skill3Lbl.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
         // 
         // Skill3
         // 
         this.Skill3.AccessibleName = "";
         this.Skill3.Enabled = false;
         this.Skill3.Location = new System.Drawing.Point(104, 184);
         this.Skill3.Name = "Skill3";
         this.Skill3.Size = new System.Drawing.Size(40, 20);
         this.Skill3.TabIndex = 12;
         this.Skill3.ValueChanged += new System.EventHandler(this.Skill3_ValueChanged);
         // 
         // Skill4Lbl
         // 
         this.Skill4Lbl.Location = new System.Drawing.Point(24, 216);
         this.Skill4Lbl.Name = "Skill4Lbl";
         this.Skill4Lbl.Size = new System.Drawing.Size(72, 24);
         this.Skill4Lbl.TabIndex = 15;
         this.Skill4Lbl.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
         // 
         // Skill4
         // 
         this.Skill4.AccessibleName = "";
         this.Skill4.Enabled = false;
         this.Skill4.Location = new System.Drawing.Point(104, 216);
         this.Skill4.Name = "Skill4";
         this.Skill4.Size = new System.Drawing.Size(40, 20);
         this.Skill4.TabIndex = 14;
         this.Skill4.ValueChanged += new System.EventHandler(this.Skill4_ValueChanged);
         // 
         // Skill5Lbl
         // 
         this.Skill5Lbl.Location = new System.Drawing.Point(24, 248);
         this.Skill5Lbl.Name = "Skill5Lbl";
         this.Skill5Lbl.Size = new System.Drawing.Size(72, 24);
         this.Skill5Lbl.TabIndex = 17;
         this.Skill5Lbl.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
         // 
         // Skill5
         // 
         this.Skill5.AccessibleName = "";
         this.Skill5.Enabled = false;
         this.Skill5.Location = new System.Drawing.Point(104, 248);
         this.Skill5.Name = "Skill5";
         this.Skill5.Size = new System.Drawing.Size(40, 20);
         this.Skill5.TabIndex = 16;
         this.Skill5.ValueChanged += new System.EventHandler(this.Skill5_ValueChanged);
         // 
         // Skill6Lbl
         // 
         this.Skill6Lbl.Location = new System.Drawing.Point(24, 280);
         this.Skill6Lbl.Name = "Skill6Lbl";
         this.Skill6Lbl.Size = new System.Drawing.Size(72, 24);
         this.Skill6Lbl.TabIndex = 19;
         this.Skill6Lbl.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
         // 
         // Skill6
         // 
         this.Skill6.AccessibleName = "";
         this.Skill6.Enabled = false;
         this.Skill6.Location = new System.Drawing.Point(104, 280);
         this.Skill6.Name = "Skill6";
         this.Skill6.Size = new System.Drawing.Size(40, 20);
         this.Skill6.TabIndex = 18;
         this.Skill6.ValueChanged += new System.EventHandler(this.Skill6_ValueChanged);
         // 
         // Skill7Lbl
         // 
         this.Skill7Lbl.Location = new System.Drawing.Point(24, 312);
         this.Skill7Lbl.Name = "Skill7Lbl";
         this.Skill7Lbl.Size = new System.Drawing.Size(72, 24);
         this.Skill7Lbl.TabIndex = 21;
         this.Skill7Lbl.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
         // 
         // Skill7
         // 
         this.Skill7.AccessibleName = "";
         this.Skill7.Enabled = false;
         this.Skill7.Location = new System.Drawing.Point(104, 312);
         this.Skill7.Name = "Skill7";
         this.Skill7.Size = new System.Drawing.Size(40, 20);
         this.Skill7.TabIndex = 20;
         this.Skill7.ValueChanged += new System.EventHandler(this.Skill7_ValueChanged);
         // 
         // Skill8Lbl
         // 
         this.Skill8Lbl.Location = new System.Drawing.Point(24, 344);
         this.Skill8Lbl.Name = "Skill8Lbl";
         this.Skill8Lbl.Size = new System.Drawing.Size(72, 24);
         this.Skill8Lbl.TabIndex = 23;
         this.Skill8Lbl.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
         // 
         // Skill8
         // 
         this.Skill8.AccessibleName = "";
         this.Skill8.Enabled = false;
         this.Skill8.Location = new System.Drawing.Point(104, 344);
         this.Skill8.Name = "Skill8";
         this.Skill8.Size = new System.Drawing.Size(40, 20);
         this.Skill8.TabIndex = 22;
         this.Skill8.ValueChanged += new System.EventHandler(this.Skill8_ValueChanged);
         // 
         // Skill9Lbl
         // 
         this.Skill9Lbl.Location = new System.Drawing.Point(24, 376);
         this.Skill9Lbl.Name = "Skill9Lbl";
         this.Skill9Lbl.Size = new System.Drawing.Size(72, 24);
         this.Skill9Lbl.TabIndex = 25;
         this.Skill9Lbl.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
         // 
         // Skill9
         // 
         this.Skill9.AccessibleName = "";
         this.Skill9.Enabled = false;
         this.Skill9.Location = new System.Drawing.Point(104, 376);
         this.Skill9.Name = "Skill9";
         this.Skill9.Size = new System.Drawing.Size(40, 20);
         this.Skill9.TabIndex = 24;
         this.Skill9.ValueChanged += new System.EventHandler(this.Skill9_ValueChanged);
         // 
         // Skill10Lbl
         // 
         this.Skill10Lbl.Location = new System.Drawing.Point(24, 408);
         this.Skill10Lbl.Name = "Skill10Lbl";
         this.Skill10Lbl.Size = new System.Drawing.Size(72, 24);
         this.Skill10Lbl.TabIndex = 27;
         this.Skill10Lbl.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
         // 
         // Skill10
         // 
         this.Skill10.AccessibleName = "";
         this.Skill10.Enabled = false;
         this.Skill10.Location = new System.Drawing.Point(104, 408);
         this.Skill10.Name = "Skill10";
         this.Skill10.Size = new System.Drawing.Size(40, 20);
         this.Skill10.TabIndex = 26;
         this.Skill10.ValueChanged += new System.EventHandler(this.Skill10_ValueChanged);
         // 
         // Skill20Lbl
         // 
         this.Skill20Lbl.Location = new System.Drawing.Point(176, 408);
         this.Skill20Lbl.Name = "Skill20Lbl";
         this.Skill20Lbl.Size = new System.Drawing.Size(72, 24);
         this.Skill20Lbl.TabIndex = 47;
         this.Skill20Lbl.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
         // 
         // Skill20
         // 
         this.Skill20.AccessibleName = "";
         this.Skill20.Enabled = false;
         this.Skill20.Location = new System.Drawing.Point(256, 408);
         this.Skill20.Name = "Skill20";
         this.Skill20.Size = new System.Drawing.Size(40, 20);
         this.Skill20.TabIndex = 46;
         this.Skill20.ValueChanged += new System.EventHandler(this.Skill20_ValueChanged);
         // 
         // Skill19Lbl
         // 
         this.Skill19Lbl.Location = new System.Drawing.Point(176, 376);
         this.Skill19Lbl.Name = "Skill19Lbl";
         this.Skill19Lbl.Size = new System.Drawing.Size(72, 24);
         this.Skill19Lbl.TabIndex = 45;
         this.Skill19Lbl.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
         // 
         // Skill19
         // 
         this.Skill19.AccessibleName = "";
         this.Skill19.Enabled = false;
         this.Skill19.Location = new System.Drawing.Point(256, 376);
         this.Skill19.Name = "Skill19";
         this.Skill19.Size = new System.Drawing.Size(40, 20);
         this.Skill19.TabIndex = 44;
         this.Skill19.ValueChanged += new System.EventHandler(this.Skill19_ValueChanged);
         // 
         // Skill18Lbl
         // 
         this.Skill18Lbl.Location = new System.Drawing.Point(176, 344);
         this.Skill18Lbl.Name = "Skill18Lbl";
         this.Skill18Lbl.Size = new System.Drawing.Size(72, 24);
         this.Skill18Lbl.TabIndex = 43;
         this.Skill18Lbl.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
         // 
         // Skill18
         // 
         this.Skill18.AccessibleName = "";
         this.Skill18.Enabled = false;
         this.Skill18.Location = new System.Drawing.Point(256, 344);
         this.Skill18.Name = "Skill18";
         this.Skill18.Size = new System.Drawing.Size(40, 20);
         this.Skill18.TabIndex = 42;
         this.Skill18.ValueChanged += new System.EventHandler(this.Skill18_ValueChanged);
         // 
         // Skill17Lbl
         // 
         this.Skill17Lbl.Location = new System.Drawing.Point(176, 312);
         this.Skill17Lbl.Name = "Skill17Lbl";
         this.Skill17Lbl.Size = new System.Drawing.Size(72, 24);
         this.Skill17Lbl.TabIndex = 41;
         this.Skill17Lbl.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
         // 
         // Skill17
         // 
         this.Skill17.AccessibleName = "";
         this.Skill17.Enabled = false;
         this.Skill17.Location = new System.Drawing.Point(256, 312);
         this.Skill17.Name = "Skill17";
         this.Skill17.Size = new System.Drawing.Size(40, 20);
         this.Skill17.TabIndex = 40;
         this.Skill17.ValueChanged += new System.EventHandler(this.Skill17_ValueChanged);
         // 
         // Skill16Lbl
         // 
         this.Skill16Lbl.Location = new System.Drawing.Point(176, 280);
         this.Skill16Lbl.Name = "Skill16Lbl";
         this.Skill16Lbl.Size = new System.Drawing.Size(72, 24);
         this.Skill16Lbl.TabIndex = 39;
         this.Skill16Lbl.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
         // 
         // Skill16
         // 
         this.Skill16.AccessibleName = "";
         this.Skill16.Enabled = false;
         this.Skill16.Location = new System.Drawing.Point(256, 280);
         this.Skill16.Name = "Skill16";
         this.Skill16.Size = new System.Drawing.Size(40, 20);
         this.Skill16.TabIndex = 38;
         this.Skill16.ValueChanged += new System.EventHandler(this.Skill16_ValueChanged);
         // 
         // Skill15Lbl
         // 
         this.Skill15Lbl.Location = new System.Drawing.Point(176, 248);
         this.Skill15Lbl.Name = "Skill15Lbl";
         this.Skill15Lbl.Size = new System.Drawing.Size(72, 24);
         this.Skill15Lbl.TabIndex = 37;
         this.Skill15Lbl.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
         // 
         // Skill15
         // 
         this.Skill15.AccessibleName = "";
         this.Skill15.Enabled = false;
         this.Skill15.Location = new System.Drawing.Point(256, 248);
         this.Skill15.Name = "Skill15";
         this.Skill15.Size = new System.Drawing.Size(40, 20);
         this.Skill15.TabIndex = 36;
         this.Skill15.ValueChanged += new System.EventHandler(this.Skill15_ValueChanged);
         // 
         // Skill14Lbl
         // 
         this.Skill14Lbl.Location = new System.Drawing.Point(176, 216);
         this.Skill14Lbl.Name = "Skill14Lbl";
         this.Skill14Lbl.Size = new System.Drawing.Size(72, 24);
         this.Skill14Lbl.TabIndex = 35;
         this.Skill14Lbl.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
         // 
         // Skill14
         // 
         this.Skill14.AccessibleName = "";
         this.Skill14.Enabled = false;
         this.Skill14.Location = new System.Drawing.Point(256, 216);
         this.Skill14.Name = "Skill14";
         this.Skill14.Size = new System.Drawing.Size(40, 20);
         this.Skill14.TabIndex = 34;
         this.Skill14.ValueChanged += new System.EventHandler(this.Skill14_ValueChanged);
         // 
         // Skill13Lbl
         // 
         this.Skill13Lbl.Location = new System.Drawing.Point(176, 184);
         this.Skill13Lbl.Name = "Skill13Lbl";
         this.Skill13Lbl.Size = new System.Drawing.Size(72, 24);
         this.Skill13Lbl.TabIndex = 33;
         this.Skill13Lbl.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
         // 
         // Skill13
         // 
         this.Skill13.AccessibleName = "";
         this.Skill13.Enabled = false;
         this.Skill13.Location = new System.Drawing.Point(256, 184);
         this.Skill13.Name = "Skill13";
         this.Skill13.Size = new System.Drawing.Size(40, 20);
         this.Skill13.TabIndex = 32;
         this.Skill13.ValueChanged += new System.EventHandler(this.Skill13_ValueChanged);
         // 
         // Skill12Lbl
         // 
         this.Skill12Lbl.Location = new System.Drawing.Point(176, 152);
         this.Skill12Lbl.Name = "Skill12Lbl";
         this.Skill12Lbl.Size = new System.Drawing.Size(72, 24);
         this.Skill12Lbl.TabIndex = 31;
         this.Skill12Lbl.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
         // 
         // Skill12
         // 
         this.Skill12.AccessibleName = "";
         this.Skill12.Enabled = false;
         this.Skill12.Location = new System.Drawing.Point(256, 152);
         this.Skill12.Name = "Skill12";
         this.Skill12.Size = new System.Drawing.Size(40, 20);
         this.Skill12.TabIndex = 30;
         this.Skill12.ValueChanged += new System.EventHandler(this.Skill12_ValueChanged);
         // 
         // Skill11Lbl
         // 
         this.Skill11Lbl.Location = new System.Drawing.Point(176, 120);
         this.Skill11Lbl.Name = "Skill11Lbl";
         this.Skill11Lbl.Size = new System.Drawing.Size(72, 24);
         this.Skill11Lbl.TabIndex = 29;
         this.Skill11Lbl.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
         // 
         // Skill11
         // 
         this.Skill11.AccessibleName = "";
         this.Skill11.Enabled = false;
         this.Skill11.Location = new System.Drawing.Point(256, 120);
         this.Skill11.Name = "Skill11";
         this.Skill11.Size = new System.Drawing.Size(40, 20);
         this.Skill11.TabIndex = 28;
         this.Skill11.ValueChanged += new System.EventHandler(this.Skill11_ValueChanged);
         // 
         // Skill30Lbl
         // 
         this.Skill30Lbl.Location = new System.Drawing.Point(328, 408);
         this.Skill30Lbl.Name = "Skill30Lbl";
         this.Skill30Lbl.Size = new System.Drawing.Size(72, 24);
         this.Skill30Lbl.TabIndex = 67;
         this.Skill30Lbl.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
         // 
         // Skill30
         // 
         this.Skill30.AccessibleName = "";
         this.Skill30.Enabled = false;
         this.Skill30.Location = new System.Drawing.Point(408, 408);
         this.Skill30.Name = "Skill30";
         this.Skill30.Size = new System.Drawing.Size(40, 20);
         this.Skill30.TabIndex = 66;
         this.Skill30.ValueChanged += new System.EventHandler(this.Skill30_ValueChanged);
         // 
         // Skill29Lbl
         // 
         this.Skill29Lbl.Location = new System.Drawing.Point(328, 376);
         this.Skill29Lbl.Name = "Skill29Lbl";
         this.Skill29Lbl.Size = new System.Drawing.Size(72, 24);
         this.Skill29Lbl.TabIndex = 65;
         this.Skill29Lbl.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
         // 
         // Skill29
         // 
         this.Skill29.AccessibleName = "";
         this.Skill29.Enabled = false;
         this.Skill29.Location = new System.Drawing.Point(408, 376);
         this.Skill29.Name = "Skill29";
         this.Skill29.Size = new System.Drawing.Size(40, 20);
         this.Skill29.TabIndex = 64;
         this.Skill29.ValueChanged += new System.EventHandler(this.Skill29_ValueChanged);
         // 
         // Skill28Lbl
         // 
         this.Skill28Lbl.Location = new System.Drawing.Point(328, 344);
         this.Skill28Lbl.Name = "Skill28Lbl";
         this.Skill28Lbl.Size = new System.Drawing.Size(72, 24);
         this.Skill28Lbl.TabIndex = 63;
         this.Skill28Lbl.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
         // 
         // Skill28
         // 
         this.Skill28.AccessibleName = "";
         this.Skill28.Enabled = false;
         this.Skill28.Location = new System.Drawing.Point(408, 344);
         this.Skill28.Name = "Skill28";
         this.Skill28.Size = new System.Drawing.Size(40, 20);
         this.Skill28.TabIndex = 62;
         this.Skill28.ValueChanged += new System.EventHandler(this.Skill28_ValueChanged);
         // 
         // Skill27Lbl
         // 
         this.Skill27Lbl.Location = new System.Drawing.Point(328, 312);
         this.Skill27Lbl.Name = "Skill27Lbl";
         this.Skill27Lbl.Size = new System.Drawing.Size(72, 24);
         this.Skill27Lbl.TabIndex = 61;
         this.Skill27Lbl.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
         // 
         // Skill27
         // 
         this.Skill27.AccessibleName = "";
         this.Skill27.Enabled = false;
         this.Skill27.Location = new System.Drawing.Point(408, 312);
         this.Skill27.Name = "Skill27";
         this.Skill27.Size = new System.Drawing.Size(40, 20);
         this.Skill27.TabIndex = 60;
         this.Skill27.ValueChanged += new System.EventHandler(this.Skill27_ValueChanged);
         // 
         // Skill26Lbl
         // 
         this.Skill26Lbl.Location = new System.Drawing.Point(328, 280);
         this.Skill26Lbl.Name = "Skill26Lbl";
         this.Skill26Lbl.Size = new System.Drawing.Size(72, 24);
         this.Skill26Lbl.TabIndex = 59;
         this.Skill26Lbl.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
         // 
         // Skill26
         // 
         this.Skill26.AccessibleName = "";
         this.Skill26.Enabled = false;
         this.Skill26.Location = new System.Drawing.Point(408, 280);
         this.Skill26.Name = "Skill26";
         this.Skill26.Size = new System.Drawing.Size(40, 20);
         this.Skill26.TabIndex = 58;
         this.Skill26.ValueChanged += new System.EventHandler(this.Skill26_ValueChanged);
         // 
         // Skill25Lbl
         // 
         this.Skill25Lbl.Location = new System.Drawing.Point(328, 248);
         this.Skill25Lbl.Name = "Skill25Lbl";
         this.Skill25Lbl.Size = new System.Drawing.Size(72, 24);
         this.Skill25Lbl.TabIndex = 57;
         this.Skill25Lbl.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
         // 
         // Skill25
         // 
         this.Skill25.AccessibleName = "";
         this.Skill25.Enabled = false;
         this.Skill25.Location = new System.Drawing.Point(408, 248);
         this.Skill25.Name = "Skill25";
         this.Skill25.Size = new System.Drawing.Size(40, 20);
         this.Skill25.TabIndex = 56;
         this.Skill25.ValueChanged += new System.EventHandler(this.Skill25_ValueChanged);
         // 
         // Skill24Lbl
         // 
         this.Skill24Lbl.Location = new System.Drawing.Point(328, 216);
         this.Skill24Lbl.Name = "Skill24Lbl";
         this.Skill24Lbl.Size = new System.Drawing.Size(72, 24);
         this.Skill24Lbl.TabIndex = 55;
         this.Skill24Lbl.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
         // 
         // Skill24
         // 
         this.Skill24.AccessibleName = "";
         this.Skill24.Enabled = false;
         this.Skill24.Location = new System.Drawing.Point(408, 216);
         this.Skill24.Name = "Skill24";
         this.Skill24.Size = new System.Drawing.Size(40, 20);
         this.Skill24.TabIndex = 54;
         this.Skill24.ValueChanged += new System.EventHandler(this.Skill24_ValueChanged);
         // 
         // Skill23Lbl
         // 
         this.Skill23Lbl.Location = new System.Drawing.Point(328, 184);
         this.Skill23Lbl.Name = "Skill23Lbl";
         this.Skill23Lbl.Size = new System.Drawing.Size(72, 24);
         this.Skill23Lbl.TabIndex = 53;
         this.Skill23Lbl.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
         // 
         // Skill23
         // 
         this.Skill23.AccessibleName = "";
         this.Skill23.Enabled = false;
         this.Skill23.Location = new System.Drawing.Point(408, 184);
         this.Skill23.Name = "Skill23";
         this.Skill23.Size = new System.Drawing.Size(40, 20);
         this.Skill23.TabIndex = 52;
         this.Skill23.ValueChanged += new System.EventHandler(this.Skill23_ValueChanged);
         // 
         // Skill22Lbl
         // 
         this.Skill22Lbl.Location = new System.Drawing.Point(328, 152);
         this.Skill22Lbl.Name = "Skill22Lbl";
         this.Skill22Lbl.Size = new System.Drawing.Size(72, 24);
         this.Skill22Lbl.TabIndex = 51;
         this.Skill22Lbl.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
         // 
         // Skill22
         // 
         this.Skill22.AccessibleName = "";
         this.Skill22.Enabled = false;
         this.Skill22.Location = new System.Drawing.Point(408, 152);
         this.Skill22.Name = "Skill22";
         this.Skill22.Size = new System.Drawing.Size(40, 20);
         this.Skill22.TabIndex = 50;
         this.Skill22.ValueChanged += new System.EventHandler(this.Skill22_ValueChanged);
         // 
         // Skill21Lbl
         // 
         this.Skill21Lbl.Location = new System.Drawing.Point(328, 120);
         this.Skill21Lbl.Name = "Skill21Lbl";
         this.Skill21Lbl.Size = new System.Drawing.Size(72, 24);
         this.Skill21Lbl.TabIndex = 49;
         this.Skill21Lbl.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
         // 
         // Skill21
         // 
         this.Skill21.AccessibleName = "";
         this.Skill21.Enabled = false;
         this.Skill21.Location = new System.Drawing.Point(408, 120);
         this.Skill21.Name = "Skill21";
         this.Skill21.Size = new System.Drawing.Size(40, 20);
         this.Skill21.TabIndex = 48;
         this.Skill21.ValueChanged += new System.EventHandler(this.Skill21_ValueChanged);
         // 
         // LeftOverSkillPointsTxtBox
         // 
         this.LeftOverSkillPointsTxtBox.Location = new System.Drawing.Point(560, 120);
         this.LeftOverSkillPointsTxtBox.Name = "LeftOverSkillPointsTxtBox";
         this.LeftOverSkillPointsTxtBox.ReadOnly = true;
         this.LeftOverSkillPointsTxtBox.Size = new System.Drawing.Size(32, 20);
         this.LeftOverSkillPointsTxtBox.TabIndex = 68;
         this.LeftOverSkillPointsTxtBox.Text = "textBox1";
         this.LeftOverSkillPointsTxtBox.TextChanged += new System.EventHandler(this.LeftOverSkillPointsTxtBox_TextChanged);
         // 
         // label5
         // 
         this.label5.Location = new System.Drawing.Point(464, 120);
         this.label5.Name = "label5";
         this.label5.Size = new System.Drawing.Size(88, 24);
         this.label5.TabIndex = 69;
         this.label5.Text = "Left Over Points:";
         this.label5.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
         // 
         // Form1
         // 
         this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
         this.ClientSize = new System.Drawing.Size(624, 449);
         this.Controls.AddRange(new System.Windows.Forms.Control[] {
                                                                      this.label5,
                                                                      this.LeftOverSkillPointsTxtBox,
                                                                      this.Skill30Lbl,
                                                                      this.Skill30,
                                                                      this.Skill29Lbl,
                                                                      this.Skill29,
                                                                      this.Skill28Lbl,
                                                                      this.Skill28,
                                                                      this.Skill27Lbl,
                                                                      this.Skill27,
                                                                      this.Skill26Lbl,
                                                                      this.Skill26,
                                                                      this.Skill25Lbl,
                                                                      this.Skill25,
                                                                      this.Skill24Lbl,
                                                                      this.Skill24,
                                                                      this.Skill23Lbl,
                                                                      this.Skill23,
                                                                      this.Skill22Lbl,
                                                                      this.Skill22,
                                                                      this.Skill21Lbl,
                                                                      this.Skill21,
                                                                      this.Skill20Lbl,
                                                                      this.Skill20,
                                                                      this.Skill19Lbl,
                                                                      this.Skill19,
                                                                      this.Skill18Lbl,
                                                                      this.Skill18,
                                                                      this.Skill17Lbl,
                                                                      this.Skill17,
                                                                      this.Skill16Lbl,
                                                                      this.Skill16,
                                                                      this.Skill15Lbl,
                                                                      this.Skill15,
                                                                      this.Skill14Lbl,
                                                                      this.Skill14,
                                                                      this.Skill13Lbl,
                                                                      this.Skill13,
                                                                      this.Skill12Lbl,
                                                                      this.Skill12,
                                                                      this.Skill11Lbl,
                                                                      this.Skill11,
                                                                      this.Skill10Lbl,
                                                                      this.Skill10,
                                                                      this.Skill9Lbl,
                                                                      this.Skill9,
                                                                      this.Skill8Lbl,
                                                                      this.Skill8,
                                                                      this.Skill7Lbl,
                                                                      this.Skill7,
                                                                      this.Skill6Lbl,
                                                                      this.Skill6,
                                                                      this.Skill5Lbl,
                                                                      this.Skill5,
                                                                      this.Skill4Lbl,
                                                                      this.Skill4,
                                                                      this.Skill3Lbl,
                                                                      this.Skill3,
                                                                      this.Skill2Lbl,
                                                                      this.Skill2,
                                                                      this.Skill1Lbl,
                                                                      this.Skill1,
                                                                      this.CharLevelLbl,
                                                                      this.label4,
                                                                      this.CalcedChecksumLbl,
                                                                      this.ChecksumLbl,
                                                                      this.label3,
                                                                      this.label2,
                                                                      this.FileNameLbl,
                                                                      this.Label1});
         this.Menu = this.mainMenu1;
         this.Name = "Form1";
         this.Text = "Form1";
         ((System.ComponentModel.ISupportInitialize)(this.Skill1)).EndInit();
         ((System.ComponentModel.ISupportInitialize)(this.Skill2)).EndInit();
         ((System.ComponentModel.ISupportInitialize)(this.Skill3)).EndInit();
         ((System.ComponentModel.ISupportInitialize)(this.Skill4)).EndInit();
         ((System.ComponentModel.ISupportInitialize)(this.Skill5)).EndInit();
         ((System.ComponentModel.ISupportInitialize)(this.Skill6)).EndInit();
         ((System.ComponentModel.ISupportInitialize)(this.Skill7)).EndInit();
         ((System.ComponentModel.ISupportInitialize)(this.Skill8)).EndInit();
         ((System.ComponentModel.ISupportInitialize)(this.Skill9)).EndInit();
         ((System.ComponentModel.ISupportInitialize)(this.Skill10)).EndInit();
         ((System.ComponentModel.ISupportInitialize)(this.Skill20)).EndInit();
         ((System.ComponentModel.ISupportInitialize)(this.Skill19)).EndInit();
         ((System.ComponentModel.ISupportInitialize)(this.Skill18)).EndInit();
         ((System.ComponentModel.ISupportInitialize)(this.Skill17)).EndInit();
         ((System.ComponentModel.ISupportInitialize)(this.Skill16)).EndInit();
         ((System.ComponentModel.ISupportInitialize)(this.Skill15)).EndInit();
         ((System.ComponentModel.ISupportInitialize)(this.Skill14)).EndInit();
         ((System.ComponentModel.ISupportInitialize)(this.Skill13)).EndInit();
         ((System.ComponentModel.ISupportInitialize)(this.Skill12)).EndInit();
         ((System.ComponentModel.ISupportInitialize)(this.Skill11)).EndInit();
         ((System.ComponentModel.ISupportInitialize)(this.Skill30)).EndInit();
         ((System.ComponentModel.ISupportInitialize)(this.Skill29)).EndInit();
         ((System.ComponentModel.ISupportInitialize)(this.Skill28)).EndInit();
         ((System.ComponentModel.ISupportInitialize)(this.Skill27)).EndInit();
         ((System.ComponentModel.ISupportInitialize)(this.Skill26)).EndInit();
         ((System.ComponentModel.ISupportInitialize)(this.Skill25)).EndInit();
         ((System.ComponentModel.ISupportInitialize)(this.Skill24)).EndInit();
         ((System.ComponentModel.ISupportInitialize)(this.Skill23)).EndInit();
         ((System.ComponentModel.ISupportInitialize)(this.Skill22)).EndInit();
         ((System.ComponentModel.ISupportInitialize)(this.Skill21)).EndInit();
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

      private uint figureChecksum()
      {
         uint byte_read;
         uint bufferChecksum = 0;
          
         // this matches the _asm block, but is kinda easier to read!
         for (uint x = 0; x < m_d2sBufferSize; x++)
         {
            byte_read = (uint) m_d2sBuffer[x];
            
            // roll the top bit low if necessary...
            if ((bufferChecksum & 0x80000000) != 0)
            {
               byte_read++;
            }
            
            bufferChecksum = bufferChecksum << 1;
            bufferChecksum += byte_read;
         }
         return bufferChecksum;
      }

      private void File_Open_Click(object sender, System.EventArgs e)
      {

         OpenFileDialog openFileDialog1 = new OpenFileDialog();
         openFileDialog1.Filter = "D2S Files|*.d2s";
         openFileDialog1.Title = "Select a character file";

         // Show the Dialog.
         // If the user clicked OK in the dialog and
         // a .CUR file was selected, open it.
         if (openFileDialog1.ShowDialog() == DialogResult.OK)
         {
            try
            {
                  //MessageBox.Show(openFileDialog1.FileName,
                      //"File Reading...",
                      //MessageBoxButtons.OK, 
                      //MessageBoxIcon.Exclamation);
               m_Filename = openFileDialog1.FileName;
               FileNameLbl.Text = m_Filename;
               FileStream f = new FileStream(openFileDialog1.FileName ,FileMode.Open);

               // read and load up the list box..
               try
                  {
                  m_d2sBufferSize = (uint) f.Length;
                  
                  uint currentByte = 0;
                  
                  while(f.Length != f.Position)
                  {
                     m_d2sBuffer[currentByte] = (byte) f.ReadByte();
                     currentByte++;
                  }
                  
               }
               catch(IOException exc)
               {
                  MessageBox.Show(exc.Message,
                                  "File Reading...",
                                  MessageBoxButtons.OK, 
                                  MessageBoxIcon.Exclamation);
               }
               
            }
            catch (System.IO.FileNotFoundException exc2)
            {
               MessageBox.Show(exc2.Message,
                               "File Reading...",
                               MessageBoxButtons.OK, 
                               MessageBoxIcon.Exclamation);
            }

            FindSkillOfst();

            ChecksumLbl.Text = String.Format("{0:x4}",FetchChecksum());
            clearChecksum();
            CalcedChecksumLbl.Text = String.Format("{0:x4}",figureChecksum());
            m_char_level = m_d2sBuffer[CHARACTERLEVEL_OFST];
            CharLevelLbl.Text = String.Format("{0:d2}",m_d2sBuffer[CHARACTERLEVEL_OFST]);
            LoadUpPaladinSkills();
            AdjustMinMaxes();
            mReadAndActive = true;

         }
      }
      
      private void File_Save_Click(object sender, System.EventArgs e)
      {
         MessageBox.Show("Save Clicked",
                         "Save...",
                         MessageBoxButtons.OK, 
                         MessageBoxIcon.Exclamation);
        
      }

      private void FindSkillOfst()
      {
         // find skill offset..
         for (m_skill_ofst = 769; m_skill_ofst < m_d2sBufferSize; m_skill_ofst++)
         {
            if (        m_d2sBuffer[m_skill_ofst]   == 'i' 
                     && m_d2sBuffer[m_skill_ofst+1] == 'f'  )
            {
               break;
            }
         }
         m_skill_ofst += 2;
      }

      private uint FetchChecksum()
      {
         uint lb  = (uint) m_d2sBuffer[CHECKSUM_OFST+0];
         uint lmb = (uint) m_d2sBuffer[CHECKSUM_OFST+1];
         uint hmb = (uint) m_d2sBuffer[CHECKSUM_OFST+2];
         uint hb  = (uint) m_d2sBuffer[CHECKSUM_OFST+3];
         uint checksum = lb + (lmb << 8) + (hmb << 16) + (hb << 24); 

         return checksum;
      }

      private void LoadUpPaladinSkills()
      {
         PaladinSkills[ 0].m_previousLevel = m_d2sBuffer[m_skill_ofst];    
         PaladinSkills[ 1].m_previousLevel = m_d2sBuffer[m_skill_ofst+1];  
         PaladinSkills[ 2].m_previousLevel = m_d2sBuffer[m_skill_ofst+2];  
         PaladinSkills[ 3].m_previousLevel = m_d2sBuffer[m_skill_ofst+3];  
         PaladinSkills[ 4].m_previousLevel = m_d2sBuffer[m_skill_ofst+4];  
         PaladinSkills[ 5].m_previousLevel = m_d2sBuffer[m_skill_ofst+5];  
         PaladinSkills[ 6].m_previousLevel = m_d2sBuffer[m_skill_ofst+6];  
         PaladinSkills[ 7].m_previousLevel = m_d2sBuffer[m_skill_ofst+7];  
         PaladinSkills[ 8].m_previousLevel = m_d2sBuffer[m_skill_ofst+8];  
         PaladinSkills[ 9].m_previousLevel = m_d2sBuffer[m_skill_ofst+9];  
         PaladinSkills[10].m_previousLevel = m_d2sBuffer[m_skill_ofst+10]; 
         PaladinSkills[11].m_previousLevel = m_d2sBuffer[m_skill_ofst+11]; 
         PaladinSkills[12].m_previousLevel = m_d2sBuffer[m_skill_ofst+12]; 
         PaladinSkills[13].m_previousLevel = m_d2sBuffer[m_skill_ofst+13]; 
         PaladinSkills[14].m_previousLevel = m_d2sBuffer[m_skill_ofst+14]; 
         PaladinSkills[15].m_previousLevel = m_d2sBuffer[m_skill_ofst+15]; 
         PaladinSkills[16].m_previousLevel = m_d2sBuffer[m_skill_ofst+16]; 
         PaladinSkills[17].m_previousLevel = m_d2sBuffer[m_skill_ofst+17]; 
         PaladinSkills[18].m_previousLevel = m_d2sBuffer[m_skill_ofst+18]; 
         PaladinSkills[19].m_previousLevel = m_d2sBuffer[m_skill_ofst+19]; 
         PaladinSkills[20].m_previousLevel = m_d2sBuffer[m_skill_ofst+20]; 
         PaladinSkills[21].m_previousLevel = m_d2sBuffer[m_skill_ofst+21]; 
         PaladinSkills[22].m_previousLevel = m_d2sBuffer[m_skill_ofst+22]; 
         PaladinSkills[23].m_previousLevel = m_d2sBuffer[m_skill_ofst+23]; 
         PaladinSkills[24].m_previousLevel = m_d2sBuffer[m_skill_ofst+24]; 
         PaladinSkills[25].m_previousLevel = m_d2sBuffer[m_skill_ofst+25]; 
         PaladinSkills[26].m_previousLevel = m_d2sBuffer[m_skill_ofst+26]; 
         PaladinSkills[27].m_previousLevel = m_d2sBuffer[m_skill_ofst+27]; 
         PaladinSkills[28].m_previousLevel = m_d2sBuffer[m_skill_ofst+28]; 
         PaladinSkills[29].m_previousLevel = m_d2sBuffer[m_skill_ofst+29]; 

         Skill1.Value  = m_d2sBuffer[m_skill_ofst];
         Skill2.Value  = m_d2sBuffer[m_skill_ofst+1];
         Skill3.Value  = m_d2sBuffer[m_skill_ofst+2];
         Skill4.Value  = m_d2sBuffer[m_skill_ofst+3];
         Skill5.Value  = m_d2sBuffer[m_skill_ofst+4];
         Skill6.Value  = m_d2sBuffer[m_skill_ofst+5];
         Skill7.Value  = m_d2sBuffer[m_skill_ofst+6];
         Skill8.Value  = m_d2sBuffer[m_skill_ofst+7];
         Skill9.Value  = m_d2sBuffer[m_skill_ofst+8];
         Skill10.Value = m_d2sBuffer[m_skill_ofst+9];
         Skill11.Value = m_d2sBuffer[m_skill_ofst+10];
         Skill12.Value = m_d2sBuffer[m_skill_ofst+11];
         Skill13.Value = m_d2sBuffer[m_skill_ofst+12];
         Skill14.Value = m_d2sBuffer[m_skill_ofst+13];
         Skill15.Value = m_d2sBuffer[m_skill_ofst+14];
         Skill16.Value = m_d2sBuffer[m_skill_ofst+15];
         Skill17.Value = m_d2sBuffer[m_skill_ofst+16];
         Skill18.Value = m_d2sBuffer[m_skill_ofst+17];
         Skill19.Value = m_d2sBuffer[m_skill_ofst+18];
         Skill20.Value = m_d2sBuffer[m_skill_ofst+19];
         Skill21.Value = m_d2sBuffer[m_skill_ofst+20];
         Skill22.Value = m_d2sBuffer[m_skill_ofst+21];
         Skill23.Value = m_d2sBuffer[m_skill_ofst+22];
         Skill24.Value = m_d2sBuffer[m_skill_ofst+23];
         Skill25.Value = m_d2sBuffer[m_skill_ofst+24];
         Skill26.Value = m_d2sBuffer[m_skill_ofst+25];
         Skill27.Value = m_d2sBuffer[m_skill_ofst+26];
         Skill28.Value = m_d2sBuffer[m_skill_ofst+27];
         Skill29.Value = m_d2sBuffer[m_skill_ofst+28];
         Skill30.Value = m_d2sBuffer[m_skill_ofst+29];
         

         Skill1.Enabled  = true;
         Skill2.Enabled  = true;
         Skill3.Enabled  = true;
         Skill4.Enabled  = true;
         Skill5.Enabled  = true;
         Skill6.Enabled  = true;
         Skill7.Enabled  = true;
         Skill8.Enabled  = true;
         Skill9.Enabled  = true;
         Skill10.Enabled = true;
         Skill11.Enabled = true;
         Skill12.Enabled = true;
         Skill13.Enabled = true;
         Skill14.Enabled = true;
         Skill15.Enabled = true;
         Skill16.Enabled = true;
         Skill17.Enabled = true;
         Skill18.Enabled = true;
         Skill19.Enabled = true;
         Skill20.Enabled = true;
         Skill21.Enabled = true;
         Skill22.Enabled = true;
         Skill23.Enabled = true;
         Skill24.Enabled = true;
         Skill25.Enabled = true;
         Skill26.Enabled = true;
         Skill27.Enabled = true;
         Skill28.Enabled = true;
         Skill29.Enabled = true;
         Skill30.Enabled = true;
         
         // specific to each class. hard-coded for now..
         Skill1Lbl.Text  = PaladinSkills[ 0].m_SkillName;
         Skill2Lbl.Text  = PaladinSkills[ 1].m_SkillName;
         Skill3Lbl.Text  = PaladinSkills[ 2].m_SkillName;
         Skill4Lbl.Text  = PaladinSkills[ 3].m_SkillName;
         Skill5Lbl.Text  = PaladinSkills[ 4].m_SkillName;
         Skill6Lbl.Text  = PaladinSkills[ 5].m_SkillName;
         Skill7Lbl.Text  = PaladinSkills[ 6].m_SkillName;
         Skill8Lbl.Text  = PaladinSkills[ 7].m_SkillName;
         Skill9Lbl.Text  = PaladinSkills[ 8].m_SkillName;
         Skill10Lbl.Text = PaladinSkills[ 9].m_SkillName;
         Skill11Lbl.Text = PaladinSkills[10].m_SkillName;
         Skill12Lbl.Text = PaladinSkills[11].m_SkillName;
         Skill13Lbl.Text = PaladinSkills[12].m_SkillName;
         Skill14Lbl.Text = PaladinSkills[13].m_SkillName;
         Skill15Lbl.Text = PaladinSkills[14].m_SkillName;
         Skill16Lbl.Text = PaladinSkills[15].m_SkillName;
         Skill17Lbl.Text = PaladinSkills[16].m_SkillName;
         Skill18Lbl.Text = PaladinSkills[17].m_SkillName;
         Skill19Lbl.Text = PaladinSkills[18].m_SkillName;
         Skill20Lbl.Text = PaladinSkills[19].m_SkillName;
         Skill21Lbl.Text = PaladinSkills[20].m_SkillName;
         Skill22Lbl.Text = PaladinSkills[21].m_SkillName;
         Skill23Lbl.Text = PaladinSkills[22].m_SkillName;
         Skill24Lbl.Text = PaladinSkills[23].m_SkillName;
         Skill25Lbl.Text = PaladinSkills[24].m_SkillName;
         Skill26Lbl.Text = PaladinSkills[25].m_SkillName;
         Skill27Lbl.Text = PaladinSkills[26].m_SkillName;
         Skill28Lbl.Text = PaladinSkills[27].m_SkillName;
         Skill29Lbl.Text = PaladinSkills[28].m_SkillName;
         Skill30Lbl.Text = PaladinSkills[29].m_SkillName;

         
      }

      private void clearChecksum()
      {
         m_d2sBuffer[CHECKSUM_OFST+0] = 0;
         m_d2sBuffer[CHECKSUM_OFST+1] = 0;
         m_d2sBuffer[CHECKSUM_OFST+2] = 0;
         m_d2sBuffer[CHECKSUM_OFST+3] = 0;
      }

      private void doSkillAdjust(uint skillOfst,uint currValue)
      {
         // the tried to descrease level of skill
         if (mReadAndActive)
         {
            if (CurrentSkills[skillOfst].m_previousLevel > currValue)
            {
               // ok.. show as extra skill point..
               m_leftoverSkillPoints ++; 

               CurrentSkills[skillOfst].m_previousLevel = currValue;
            }
            else
            {
               // they tried to increase value of skill..
               if (CurrentSkills[skillOfst].m_previousLevel < currValue)
               {
                  m_leftoverSkillPoints--;
                  CurrentSkills[skillOfst].m_previousLevel = currValue;
               }
            }
            AdjustMinMaxes();
            LeftOverSkillPointsTxtBox.Text = String.Format("{0:d2}",m_leftoverSkillPoints);
         }
      }
      private void numericUpDown1_ValueChanged(object sender, System.EventArgs e)
      {
         // Skill1...
         uint skillOfst = 0;
         uint currValue = (uint) Skill1.Value;
         doSkillAdjust(skillOfst,currValue);
      }

      private void LeftOverSkillPointsTxtBox_TextChanged(object sender, System.EventArgs e)
      {
      
      }

      private void Skill2_ValueChanged(object sender, System.EventArgs e)
      {
         uint skillOfst = 1;
         uint currValue = (uint) Skill2.Value;
         doSkillAdjust(skillOfst,currValue);
      
      }

      private void Skill3_ValueChanged(object sender, System.EventArgs e)
      {
      
         uint skillOfst = 2;
         uint currValue = (uint) Skill3.Value;
         doSkillAdjust(skillOfst,currValue);
      }

      private void Skill4_ValueChanged(object sender, System.EventArgs e)
      {
      
         uint skillOfst = 3;
         uint currValue = (uint) Skill4.Value;
         doSkillAdjust(skillOfst,currValue);
      }

      private void Skill5_ValueChanged(object sender, System.EventArgs e)
      {
         uint skillOfst = 4;
         uint currValue = (uint) Skill5.Value;
         doSkillAdjust(skillOfst,currValue);
      
      }

      private void Skill6_ValueChanged(object sender, System.EventArgs e)
      {
      
         uint skillOfst = 5;
         uint currValue = (uint) Skill6.Value;
         doSkillAdjust(skillOfst,currValue);

      }

      private void Skill7_ValueChanged(object sender, System.EventArgs e)
      {
      
         uint skillOfst = 6;
         uint currValue = (uint) Skill7.Value;
         doSkillAdjust(skillOfst,currValue);
      }

      private void Skill8_ValueChanged(object sender, System.EventArgs e)
      {
      
         uint skillOfst = 7;
         uint currValue = (uint) Skill8.Value;
         doSkillAdjust(skillOfst,currValue);
      }

      private void Skill9_ValueChanged(object sender, System.EventArgs e)
      {
         uint skillOfst = 8;
         uint currValue = (uint) Skill9.Value;
         doSkillAdjust(skillOfst,currValue);
      
      }

      private void Skill10_ValueChanged(object sender, System.EventArgs e)
      {
         uint skillOfst = 9;
         uint currValue = (uint) Skill10.Value;
         doSkillAdjust(skillOfst,currValue);
      
      }

      private void Skill11_ValueChanged(object sender, System.EventArgs e)
      {
         uint skillOfst = 10;
         uint currValue = (uint) Skill11.Value;
         doSkillAdjust(skillOfst,currValue);
      
      }

      private void Skill12_ValueChanged(object sender, System.EventArgs e)
      {
         uint skillOfst = 11;
         uint currValue = (uint) Skill12.Value;
         doSkillAdjust(skillOfst,currValue);
      
      }

      private void Skill13_ValueChanged(object sender, System.EventArgs e)
      {
         uint skillOfst = 12;
         uint currValue = (uint) Skill13.Value;
         doSkillAdjust(skillOfst,currValue);
      
      }

      private void Skill14_ValueChanged(object sender, System.EventArgs e)
      {
         uint skillOfst = 13;
         uint currValue = (uint) Skill14.Value;
         doSkillAdjust(skillOfst,currValue);
      
      }

      private void Skill15_ValueChanged(object sender, System.EventArgs e)
      {
      
         uint skillOfst = 14;
         uint currValue = (uint) Skill15.Value;
         doSkillAdjust(skillOfst,currValue);
      }

      private void Skill16_ValueChanged(object sender, System.EventArgs e)
      {
      
         uint skillOfst = 15;
         uint currValue = (uint) Skill16.Value;
         doSkillAdjust(skillOfst,currValue);
      }

      private void Skill17_ValueChanged(object sender, System.EventArgs e)
      {
         uint skillOfst = 16;
         uint currValue = (uint) Skill17.Value;
         doSkillAdjust(skillOfst,currValue);
      
      }

      private void Skill18_ValueChanged(object sender, System.EventArgs e)
      {
         uint skillOfst = 17;
         uint currValue = (uint) Skill18.Value;
         doSkillAdjust(skillOfst,currValue);
      
      }

      private void Skill19_ValueChanged(object sender, System.EventArgs e)
      {
         uint skillOfst = 18;
         uint currValue = (uint) Skill19.Value;
         doSkillAdjust(skillOfst,currValue);
      
      }

      private void Skill20_ValueChanged(object sender, System.EventArgs e)
      {
      
         uint skillOfst = 19;
         uint currValue = (uint) Skill20.Value;
         doSkillAdjust(skillOfst,currValue);
      }

      private void Skill21_ValueChanged(object sender, System.EventArgs e)
      {
      
         uint skillOfst = 20;
         uint currValue = (uint) Skill21.Value;
         doSkillAdjust(skillOfst,currValue);
      }

      private void Skill22_ValueChanged(object sender, System.EventArgs e)
      {
      
         uint skillOfst = 21;
         uint currValue = (uint) Skill22.Value;
         doSkillAdjust(skillOfst,currValue);
      }

      private void Skill23_ValueChanged(object sender, System.EventArgs e)
      {
      
         uint skillOfst = 22;
         uint currValue = (uint) Skill23.Value;
         doSkillAdjust(skillOfst,currValue);
      }

      private void Skill24_ValueChanged(object sender, System.EventArgs e)
      {
         uint skillOfst = 23;
         uint currValue = (uint) Skill24.Value;
         doSkillAdjust(skillOfst,currValue);
      
      }

      private void Skill25_ValueChanged(object sender, System.EventArgs e)
      {
         uint skillOfst = 24;
         uint currValue = (uint) Skill25.Value;
         doSkillAdjust(skillOfst,currValue);
      
      }

      private void Skill26_ValueChanged(object sender, System.EventArgs e)
      {
         uint skillOfst = 25;
         uint currValue = (uint) Skill26.Value;
         doSkillAdjust(skillOfst,currValue);
      
      }

      private void Skill27_ValueChanged(object sender, System.EventArgs e)
      {
         uint skillOfst = 26;
         uint currValue = (uint) Skill27.Value;
         doSkillAdjust(skillOfst,currValue);
      }

      private void Skill28_ValueChanged(object sender, System.EventArgs e)
      {
         uint skillOfst = 27;
         uint currValue = (uint) Skill28.Value;
         doSkillAdjust(skillOfst,currValue);
      
      }

      private void Skill29_ValueChanged(object sender, System.EventArgs e)
      {
         uint skillOfst = 28;
         uint currValue = (uint) Skill29.Value;
         doSkillAdjust(skillOfst,currValue);
      
      }

      private void Skill30_ValueChanged(object sender, System.EventArgs e)
      {
         uint skillOfst = 29;
         uint currValue = (uint) Skill30.Value;
         doSkillAdjust(skillOfst,currValue);
      
      }

      private void AdjustMinMaxes()
      {
         int currSkillValue = 0;
         uint MaximumSkillValue;
         
         for (uint currSkill = 0; currSkill < 30; currSkill++)
         {
            // if m_FirstAvailable > m_char_level then max = 0.
            // otherwise skillMax = min((m_char_level - m_FirstAvailable),(currValue + m_leftoverSkillPoints));
            switch (currSkill)
            {
            case 0:
               currSkillValue = (int)Skill1.Value;
               break;
            case 1:
               currSkillValue = (int)Skill2.Value;
               break;
            case 2:
               currSkillValue = (int)Skill3.Value;
               break;
            case 3:
               currSkillValue = (int)Skill4.Value;
               break;
            case 4:
               currSkillValue = (int)Skill5.Value;
               break;
            case 5:
               currSkillValue = (int)Skill6.Value;
               break;
            case 6:
               currSkillValue = (int)Skill7.Value;
               break;
            case 7:
               currSkillValue = (int)Skill8.Value;
               break;
            case 8:
               currSkillValue = (int)Skill9.Value;
               break;
            case 9:
               currSkillValue = (int)Skill10.Value;
               break;
            case 10:
               currSkillValue = (int)Skill11.Value;
               break;
            case 11:
               currSkillValue = (int)Skill12.Value;
               break;
            case 12:
               currSkillValue = (int)Skill13.Value;
               break;
            case 13:
               currSkillValue = (int)Skill14.Value;
               break;
            case 14:
               currSkillValue = (int)Skill15.Value;
               break;
            case 15:
               currSkillValue = (int)Skill16.Value;
               break;
            case 16:
               currSkillValue = (int)Skill17.Value;
               break;
            case 17:
               currSkillValue = (int)Skill18.Value;
               break;
            case 18:
               currSkillValue = (int)Skill19.Value;
               break;
            case 19:
               currSkillValue = (int)Skill20.Value;
               break;
            case 20:
               currSkillValue = (int)Skill21.Value;
               break;
            case 21:
               currSkillValue = (int)Skill22.Value;
               break;
            case 22:
               currSkillValue = (int)Skill23.Value;
               break;
            case 23:
               currSkillValue = (int)Skill24.Value;
               break;
            case 24:
               currSkillValue = (int)Skill25.Value;
               break;
            case 25:
               currSkillValue = (int)Skill26.Value;
               break;
            case 26:
               currSkillValue = (int)Skill27.Value;
               break;
            case 27:
               currSkillValue = (int)Skill28.Value;
               break;
            case 28:
               currSkillValue = (int)Skill29.Value;
               break;
            case 29:
               currSkillValue = (int)Skill30.Value;
               break;
            }

            if (m_char_level < PaladinSkills[currSkill].m_FirstAvailable)
            {
               MaximumSkillValue = 0;
            }
            else
            {
               MaximumSkillValue = (uint) Math.Min((m_char_level - PaladinSkills[currSkill].m_FirstAvailable),
                                       (currSkillValue + m_leftoverSkillPoints)                    );
            }
            
            switch (currSkill)
            {
            case 0:
               Skill1.Minimum = 0;
               Skill1.Maximum = MaximumSkillValue;
               break;
            case 1:
               Skill2.Minimum = 0;
               Skill2.Maximum = MaximumSkillValue;
               break;
            case 2:
               Skill3.Minimum = 0;
               Skill3.Maximum = MaximumSkillValue;
               break;
            case 3:
               Skill4.Minimum = 0;
               Skill4.Maximum = MaximumSkillValue;
               break;
            case 4:
               Skill5.Minimum = 0;
               Skill5.Maximum = MaximumSkillValue;
               break;
            case 5:
               Skill6.Minimum = 0;
               Skill6.Maximum = MaximumSkillValue;
               break;
            case 6:
               Skill7.Minimum = 0;
               Skill7.Maximum = MaximumSkillValue;
               break;
            case 7:
               Skill8.Minimum = 0;
               Skill8.Maximum = MaximumSkillValue;
               break;
            case 8:
               Skill9.Minimum = 0;
               Skill9.Maximum = MaximumSkillValue;
               break;
            case 9:
               Skill10.Minimum = 0;
               Skill10.Maximum = MaximumSkillValue;
               break;
            case 10:
               Skill11.Minimum = 0;
               Skill11.Maximum = MaximumSkillValue;
               break;
            case 11:
               Skill12.Minimum = 0;
               Skill12.Maximum = MaximumSkillValue;
               break;
            case 12:
               Skill13.Minimum = 0;
               Skill13.Maximum = MaximumSkillValue;
               break;
            case 13:
               Skill14.Minimum = 0;
               Skill14.Maximum = MaximumSkillValue;
               break;
            case 14:
               Skill15.Minimum = 0;
               Skill15.Maximum = MaximumSkillValue;
               break;
            case 15:
               Skill16.Minimum = 0;
               Skill16.Maximum = MaximumSkillValue;
               break;
            case 16:
               Skill17.Minimum = 0;
               Skill17.Maximum = MaximumSkillValue;
               break;
            case 17:
               Skill18.Minimum = 0;
               Skill18.Maximum = MaximumSkillValue;
               break;
            case 18:
               Skill19.Minimum = 0;
               Skill19.Maximum = MaximumSkillValue;
               break;
            case 19:
               Skill20.Minimum = 0;
               Skill20.Maximum = MaximumSkillValue;
               break;
            case 20:
               Skill21.Minimum = 0;
               Skill21.Maximum = MaximumSkillValue;
               break;
            case 21:
               Skill22.Minimum = 0;
               Skill22.Maximum = MaximumSkillValue;
               break;
            case 22:
               Skill23.Minimum = 0;
               Skill23.Maximum = MaximumSkillValue;
               break;
            case 23:
               Skill24.Minimum = 0;
               Skill24.Maximum = MaximumSkillValue;
               break;
            case 24:
               Skill25.Minimum = 0;
               Skill25.Maximum = MaximumSkillValue;
               break;
            case 25:
               Skill26.Minimum = 0;
               Skill27.Maximum = MaximumSkillValue;
               break;
            case 26:
               Skill27.Minimum = 0;
               Skill27.Maximum = MaximumSkillValue;
               break;
            case 27:
               Skill28.Minimum = 0;
               Skill28.Maximum = MaximumSkillValue;
               break;
            case 28:
               Skill29.Minimum = 0;
               Skill29.Maximum = MaximumSkillValue;
               break;
            case 29:
               Skill30.Minimum = 0;
               Skill30.Maximum = MaximumSkillValue;
               break;
            }

         }

      }


   }
}



