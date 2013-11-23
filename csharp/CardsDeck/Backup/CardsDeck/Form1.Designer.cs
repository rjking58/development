namespace CardsDeck {
    partial class Form1 {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing) {
            if (disposing && (components != null)) {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent() {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.btnNewcard = new System.Windows.Forms.Button();
            this.btnShuffle = new System.Windows.Forms.Button();
            this.lvDeck = new System.Windows.Forms.ListView();
            this.columnHeader1 = new System.Windows.Forms.ColumnHeader();
            this.imlCards = new System.Windows.Forms.ImageList(this.components);
            this.grpNewCard = new System.Windows.Forms.GroupBox();
            this.lblBot = new System.Windows.Forms.Label();
            this.lblTop = new System.Windows.Forms.Label();
            this.picBot = new System.Windows.Forms.PictureBox();
            this.picMid = new System.Windows.Forms.PictureBox();
            this.picTop = new System.Windows.Forms.PictureBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.btnClose = new System.Windows.Forms.Button();
            this.grpOverlay = new System.Windows.Forms.GroupBox();
            this.btnSortList = new System.Windows.Forms.Button();
            this.grpNewCard.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.picBot)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.picMid)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.picTop)).BeginInit();
            this.groupBox2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // btnNewcard
            // 
            this.btnNewcard.Location = new System.Drawing.Point(267, 288);
            this.btnNewcard.Name = "btnNewcard";
            this.btnNewcard.Size = new System.Drawing.Size(75, 23);
            this.btnNewcard.TabIndex = 1;
            this.btnNewcard.Text = "&New Card";
            this.btnNewcard.UseVisualStyleBackColor = true;
            this.btnNewcard.Click += new System.EventHandler(this.OnNewCardClick);
            // 
            // btnShuffle
            // 
            this.btnShuffle.Location = new System.Drawing.Point(267, 317);
            this.btnShuffle.Name = "btnShuffle";
            this.btnShuffle.Size = new System.Drawing.Size(75, 23);
            this.btnShuffle.TabIndex = 2;
            this.btnShuffle.Text = "&Shuffle";
            this.btnShuffle.UseVisualStyleBackColor = true;
            this.btnShuffle.Click += new System.EventHandler(this.OnShuffleClick);
            // 
            // lvDeck
            // 
            this.lvDeck.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader1});
            this.lvDeck.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.None;
            this.lvDeck.LargeImageList = this.imlCards;
            this.lvDeck.Location = new System.Drawing.Point(17, 282);
            this.lvDeck.Name = "lvDeck";
            this.lvDeck.Size = new System.Drawing.Size(236, 146);
            this.lvDeck.SmallImageList = this.imlCards;
            this.lvDeck.TabIndex = 3;
            this.lvDeck.UseCompatibleStateImageBehavior = false;
            this.lvDeck.View = System.Windows.Forms.View.Details;
            // 
            // columnHeader1
            // 
            this.columnHeader1.Width = 200;
            // 
            // imlCards
            // 
            this.imlCards.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imlCards.ImageStream")));
            this.imlCards.TransparentColor = System.Drawing.Color.Transparent;
            this.imlCards.Images.SetKeyName(0, "Club.jpg");
            this.imlCards.Images.SetKeyName(1, "diamond.jpg");
            this.imlCards.Images.SetKeyName(2, "Heart.jpg");
            this.imlCards.Images.SetKeyName(3, "spade.jpg");
            // 
            // grpNewCard
            // 
            this.grpNewCard.BackColor = System.Drawing.Color.White;
            this.grpNewCard.Controls.Add(this.lblBot);
            this.grpNewCard.Controls.Add(this.lblTop);
            this.grpNewCard.Controls.Add(this.picBot);
            this.grpNewCard.Controls.Add(this.picMid);
            this.grpNewCard.Controls.Add(this.picTop);
            this.grpNewCard.Location = new System.Drawing.Point(190, 12);
            this.grpNewCard.Name = "grpNewCard";
            this.grpNewCard.Size = new System.Drawing.Size(161, 238);
            this.grpNewCard.TabIndex = 5;
            this.grpNewCard.TabStop = false;
            // 
            // lblBot
            // 
            this.lblBot.AutoSize = true;
            this.lblBot.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblBot.Location = new System.Drawing.Point(125, 209);
            this.lblBot.Name = "lblBot";
            this.lblBot.Size = new System.Drawing.Size(27, 24);
            this.lblBot.TabIndex = 4;
            this.lblBot.Text = " 2";
            // 
            // lblTop
            // 
            this.lblTop.AutoSize = true;
            this.lblTop.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblTop.Location = new System.Drawing.Point(8, 12);
            this.lblTop.Name = "lblTop";
            this.lblTop.Size = new System.Drawing.Size(27, 24);
            this.lblTop.TabIndex = 3;
            this.lblTop.Text = " 2";
            // 
            // picBot
            // 
            this.picBot.Image = global::CardsDeck.Properties.Resources.Club;
            this.picBot.Location = new System.Drawing.Point(122, 179);
            this.picBot.Name = "picBot";
            this.picBot.Size = new System.Drawing.Size(33, 27);
            this.picBot.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.picBot.TabIndex = 2;
            this.picBot.TabStop = false;
            // 
            // picMid
            // 
            this.picMid.Image = global::CardsDeck.Properties.Resources.Club;
            this.picMid.Location = new System.Drawing.Point(48, 97);
            this.picMid.Name = "picMid";
            this.picMid.Size = new System.Drawing.Size(56, 49);
            this.picMid.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.picMid.TabIndex = 1;
            this.picMid.TabStop = false;
            // 
            // picTop
            // 
            this.picTop.Image = global::CardsDeck.Properties.Resources.Club;
            this.picTop.Location = new System.Drawing.Point(6, 36);
            this.picTop.Name = "picTop";
            this.picTop.Size = new System.Drawing.Size(33, 27);
            this.picTop.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.picTop.TabIndex = 0;
            this.picTop.TabStop = false;
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.pictureBox1);
            this.groupBox2.Location = new System.Drawing.Point(12, 12);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(161, 238);
            this.groupBox2.TabIndex = 6;
            this.groupBox2.TabStop = false;
            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = global::CardsDeck.Properties.Resources.Cards;
            this.pictureBox1.Location = new System.Drawing.Point(5, 12);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(150, 221);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox1.TabIndex = 0;
            this.pictureBox1.TabStop = false;
            this.pictureBox1.Click += new System.EventHandler(this.OnNewCardClick);
            // 
            // btnClose
            // 
            this.btnClose.Location = new System.Drawing.Point(267, 405);
            this.btnClose.Name = "btnClose";
            this.btnClose.Size = new System.Drawing.Size(75, 23);
            this.btnClose.TabIndex = 7;
            this.btnClose.Text = "&Close";
            this.btnClose.UseVisualStyleBackColor = true;
            this.btnClose.Click += new System.EventHandler(this.OnCloseClick);
            // 
            // grpOverlay
            // 
            this.grpOverlay.Location = new System.Drawing.Point(190, 11);
            this.grpOverlay.Name = "grpOverlay";
            this.grpOverlay.Size = new System.Drawing.Size(161, 238);
            this.grpOverlay.TabIndex = 5;
            this.grpOverlay.TabStop = false;
            // 
            // btnSortList
            // 
            this.btnSortList.Location = new System.Drawing.Point(267, 376);
            this.btnSortList.Name = "btnSortList";
            this.btnSortList.Size = new System.Drawing.Size(75, 23);
            this.btnSortList.TabIndex = 8;
            this.btnSortList.Text = "S&ort List";
            this.btnSortList.UseVisualStyleBackColor = true;
            this.btnSortList.Click += new System.EventHandler(this.OnSortClick);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Control;
            this.ClientSize = new System.Drawing.Size(389, 455);
            this.Controls.Add(this.btnSortList);
            this.Controls.Add(this.grpOverlay);
            this.Controls.Add(this.btnClose);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.grpNewCard);
            this.Controls.Add(this.lvDeck);
            this.Controls.Add(this.btnShuffle);
            this.Controls.Add(this.btnNewcard);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Cards Deck";
            this.grpNewCard.ResumeLayout(false);
            this.grpNewCard.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.picBot)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.picMid)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.picTop)).EndInit();
            this.groupBox2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button btnNewcard;
        private System.Windows.Forms.Button btnShuffle;
        private System.Windows.Forms.ListView lvDeck;
        private System.Windows.Forms.ImageList imlCards;
        private System.Windows.Forms.ColumnHeader columnHeader1;
        private System.Windows.Forms.GroupBox grpNewCard;
        private System.Windows.Forms.Label lblTop;
        private System.Windows.Forms.PictureBox picBot;
        private System.Windows.Forms.PictureBox picMid;
        private System.Windows.Forms.PictureBox picTop;
        private System.Windows.Forms.Label lblBot;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Button btnClose;
        private System.Windows.Forms.GroupBox grpOverlay;
        private System.Windows.Forms.Button btnSortList;
    }
}

