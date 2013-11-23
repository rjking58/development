using System;
using System.Collections.Generic;
using System.Text;
using System.Collections;
namespace CardsDeck {
    public class Heart:ICards  {
        
        #region Private Members
            private const int MaxCardCount=13;
            private ArrayList heartCards;
        #endregion

        #region Ctor
        public Heart() {
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
            if (heartCards.Count >= MaxCardCount)
                return string.Empty;
 
            //check if new card exists, if exists create new one
            while (cardnumber==0) {
                //generate a random number each time                 
                cardnumber = rand.Next(MaxCardCount);            
                if (!heartCards.Contains(cardnumber)) {//card not found/new card
                    heartCards.Add(cardnumber);
                    break;
                } else {
                    cardnumber = 0; //card exists
                }
            }
            return "HEART " + cardnumber;
        }
        public void Shuffle() {
            heartCards = new ArrayList(MaxCardCount); 
        }

        #endregion
    }
}
