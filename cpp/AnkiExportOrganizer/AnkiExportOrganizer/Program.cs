using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace AnkiExportOrganizer
{
    class Card
    {
        public Card(string pFront, string pBack)                                                        
        {
            front = pFront;
            back = pBack;
        }
        public string front;
        public string back;
    }
    class FrontAndBack
    {
        private FrontAndBack() {}
        public FrontAndBack(Card pNewCard)
        {
            first = pNewCard;
        }
        public Card first;
        public Card second = null;
    }
    class Program
    {
        static void Main(string[] args)
        {
            StreamReader sr = new StreamReader(@"c:\tmp\spanish1.txt");

            // the key is simply the 'front' of the card
            Dictionary<string, FrontAndBack> cardList = new Dictionary<string, FrontAndBack>();

            while (!sr.EndOfStream)
            {
                String currLine = sr.ReadLine();

                string[] pieces = currLine.Split('\t');
                //Console.WriteLine("1[{0}] 2[{1}] 3[{2}]",
                //                    pieces[0],
                //                    pieces[1],
                //                    pieces[2]);

                if (pieces.Length >= 2)
                {
                    Card newCard = new Card(pieces[0], pieces[1]);
                    // is the 'back' of the card shown as a key in the dictionary? 
                    // if so, we already have the first card.. and this is the second
                    if (cardList.ContainsKey(pieces[1]))
                    {
                        cardList[pieces[1]].second = newCard;
                    }
                    else
                    {
                        FrontAndBack fab = new FrontAndBack(newCard);
                        cardList.Add(newCard.front, fab);
                    }
                }
                else
                {
                    Console.WriteLine("1[{0}]",
                                        pieces[0]);
                }
            }

            sr.Close();

            int singleCount = 0;
            foreach (KeyValuePair<string, FrontAndBack> kvp in cardList)
            {
                if (kvp.Value.second == null)
                {
                    singleCount++;
                }
            }
            Console.WriteLine("size of dict is " + cardList.Count + " single count " + singleCount);

            TextWriter singleCards = new StreamWriter(@"c:\tmp\ForwardCardsSpanish1.txt");
            foreach (KeyValuePair<string, FrontAndBack> kvp in cardList)
            {
                singleCards.WriteLine(kvp.Value.first.front + "\t" + kvp.Value.first.back);
            }
            singleCards.Close();
            
        }
    }
}
