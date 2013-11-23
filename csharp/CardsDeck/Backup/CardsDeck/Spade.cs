using System;
using System.Collections.Generic;
using System.Text;
using System.Collections;

namespace CardsDeck {
    class Spade:ICards {

        #region Private Members            
            private ArrayList Spadecards;
            private const int MaxCardCount = 13;
        #endregion

        #region Ctor
        public Spade() {
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
            if (Spadecards.Count >= MaxCardCount)
                return string.Empty;
 
            //check if new card exists, if exists create new one
            while (cardnumber==0) {
                //generate a random number each time                
                cardnumber = rand.Next(MaxCardCount);                
                if (cardnumber==0) continue;
                if (!Spadecards.Contains(cardnumber)) {//card not found/new card
                    Spadecards.Add(cardnumber);
                    break;
                } else {
                    cardnumber = 0;//card exists
                }
            }
            return "SPADE " + cardnumber;
        }
        public void Shuffle() {
            Spadecards = new ArrayList(MaxCardCount); 
        }

        #endregion
                        
    }
}
