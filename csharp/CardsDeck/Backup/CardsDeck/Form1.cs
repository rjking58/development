using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace CardsDeck {
    public partial class Form1 : Form {
        Cards mycardsDeck;

        public Form1() {
            InitializeComponent();
            //initizlize cards deck
            mycardsDeck = new Cards();
            ClearCard();
        }
        #region Event handling
        private void OnNewCardClick(object sender, EventArgs e) {
                     
            string card = mycardsDeck.GetCard();     
            //if card is empty, then no more cards in deck
            if (card.Length == 0) {
                MessageBox.Show("No more cards in deck");
                return;
            }
            //add to list view
            ListViewItem item =  lvDeck.Items.Add(card);
            if (card.Contains("CLUB")) {
                item.ImageIndex = 0;
                ShowCard(Properties.Resources.Club);  
            } else if (card.Contains("DIAMOND")) {
                item.ImageIndex = 1;
                ShowCard(Properties.Resources.diamond);
            } else if (card.Contains("HEART")) {
                item.ImageIndex = 2;
                ShowCard(Properties.Resources.Heart );
            } else {//spade
                item.ImageIndex = 3;
                ShowCard(Properties.Resources.spade );
            }
            //show card number
            ShowCard(card);
        }       

        private void OnShuffleClick(object sender, EventArgs e) {
            //clear list          
            lvDeck.Items.Clear();
            ClearCard();
            mycardsDeck.Shuffle();
        }

        private void OnCloseClick(object sender, EventArgs e) {
            Application.Exit();
        }

        private void OnSortClick(object sender, EventArgs e) {
            lvDeck.Sorting = SortOrder.Ascending;
            lvDeck.Sort();

        }

        #endregion

        #region Private Methods
        /// <summary>
        /// Clears the display card
        /// </summary>
        private void ClearCard() {
            grpOverlay.Visible = true;
            lblTop.Text = string.Empty;
            lblBot.Text = string.Empty;
            picTop.Visible = false;
            picMid.Visible = false;
            picBot.Visible = false;            
        }
        /// <summary>
        /// Shows the display card
        /// </summary>
        /// <param name="img"></param>
        private void ShowCard(Bitmap img) {
            grpOverlay.Visible =false;
            picTop.Image = img;
            picMid.Image = img;
            picBot.Image = img;
            picTop.Visible = true;
            picMid.Visible = true;
            picBot.Visible = true;    
        }
        /// <summary>
        /// Shows the display card number
        /// </summary>
        /// <param name="card"></param>
        private void ShowCard(string card) {
            if (card.Length > 0) {
                string cardnum = card.Substring(card.Length - 2, 2);
                lblTop.Text = cardnum;
                lblBot.Text = cardnum;
            }            
        }
        #endregion


    }
}