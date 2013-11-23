using System;
using System.Collections.Generic;
using System.Text;
using System.Collections;

namespace CardsDeck {
    public class Diamond:ICards {
        
        #region Private Members
            private const int MaxCardCount=13;
            private ArrayList diamondCards;
        #endregion

        #region Ctor
        public Diamond() {
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
            if (diamondCards.Count >= MaxCardCount)
                return string.Empty;
 
            //check if new card exists, if exists create new one
            while (cardnumber==0) {
                //generate a random number each time               
                cardnumber = rand.Next(MaxCardCount);               
                if (!diamondCards.Contains(cardnumber)) {//card not found/new card
                    diamondCards.Add(cardnumber);
                    break;
                } else {
                    cardnumber = 0;//card exists
                }
            }
            return "DIAMOND " + cardnumber;
        }
        public void Shuffle() {
            diamondCards = new ArrayList(MaxCardCount); 
        }

        #endregion
                        
    }
}
