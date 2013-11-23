using System;
using System.Collections.Generic;
using System.Text;
using System.Collections;

namespace CardsDeck {
    public class Club : ICards {

        
        #region Private Members
            private const int MaxCardCount=13;
            private ArrayList clubCards;
        #endregion

        #region Ctor
        public Club() {
            //call shuffle
            Shuffle();
        }
        #endregion

        #region ICards Methods
        /// <summary>
        /// returns a spade card
        /// </summary>
        /// <returns></returns>
        public string GetCard() {
            int cardnumber = 0;
            RandomGen rand = new RandomGen();

            //check if there are any cards on deck
            if (clubCards.Count >= MaxCardCount)
                return string.Empty;
 
            //check if new card exists, if exists create new one
            while (cardnumber==0) {
                //generate a random number each time                 
                cardnumber = rand.Next(MaxCardCount); 
                if (!clubCards.Contains(cardnumber)) {//card not found/new card
                    clubCards.Add(cardnumber);
                    break;
                } else {
                    cardnumber = 0;//card exists
                }
            }
            return "CLUB " + cardnumber;
        }
        public void Shuffle() {
            clubCards = new ArrayList(MaxCardCount); 
        }

        #endregion
    }
}
