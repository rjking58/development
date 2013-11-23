#region Assemlbly Reerences
using System;
using System.Collections.Generic;
using System.Text;
#endregion

namespace CardsDeck {
/// <summary>
/// Cards class is a base class
/// </summary>
    public class Cards :ICards {
        #region Private members
            private const int DeckMaxCount = 52;
            private  int currDeckCount;
            private Spade spadeCards;
            private Diamond diamondCards;
            private Heart heartCards;
            private Club clubCards;
            private RandomGen rand;
        #endregion

        #region Ctor
        public Cards() {
            //by default shuffle list
            Shuffle();
        }
        #endregion

        #region ICards Members
        /// <summary>
        ///  Get cards gets one card from the deck each time out of max card count(52)
        /// out out of 4 types of cards each of 13 numbers each
        /// </summary>
        /// <returns></returns>
        public string GetCard() {
            string card = string.Empty;
            //check if there are cards in deck
            if (currDeckCount >= DeckMaxCount) {
                //no more cards in deck
                return card;
            }
            //get a card from deck             
            while (card == string.Empty) {
                //generate a random number each time 1 out of 4 types of card                
                int type = rand.Next(4);                
                //switch on card type
                switch (type) {
                    case 1: //Spade
                        //get spade card                        
                        card = spadeCards.GetCard(); 
                        break;
                    case 2: //Diamond
                        //get diamond card
                        card = diamondCards.GetCard(); 
                        break;
                    case 3: //Heart
                        //get heart card
                        card = heartCards.GetCard(); 
                        break;
                    case 4: //Club                        
                        //get Club card
                        card = clubCards.GetCard(); 
                        break;
                }
            }
            //increament card dec count
            currDeckCount++;

            return card;
        }
        public void Shuffle() {
            currDeckCount = 0;
            rand = new RandomGen();
            spadeCards = new Spade();
            diamondCards = new Diamond();
            heartCards = new Heart();
            clubCards = new Club();
        }
        
        #endregion

       
    }
}

