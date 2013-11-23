using System;
using System.Collections.Generic;
using System.Text;

using System.Xml;
using System.Xml.Serialization;
using System.IO;

namespace FlashCard
{
    public class CardDeck
    {
        private SortedList<string,SingleFlashCard> m_cards = 
            new SortedList<string,SingleFlashCard>();
        private List<SingleFlashCard> m_shuffledCards = 
            new List<SingleFlashCard>();
        private bool m_shuffled = false;
        
        public bool AddCard(SingleFlashCard sfc)
        {
            bool retVal = false;
            if(!m_cards.ContainsKey(sfc.First))
            {
                m_cards.Add(sfc.First,sfc);            
                retVal = true;
            }

            return retVal;
        }

        public IEnumerable<SingleFlashCard> AllCards()
        {
            if(!m_shuffled)
            {
                Shuffle();
            }
            
            foreach(SingleFlashCard card in m_shuffledCards)
            {
                yield return card;
            }
        }

        public IEnumerable<SingleFlashCard> BelowRating(int Rating)
        {
            if(!m_shuffled)
            {
                Shuffle();
            }
            foreach(SingleFlashCard card in m_shuffledCards)
            {
                if(card.successRank() < Rating)
                {
                    yield return card;                
                }

            }
        }

        public IEnumerable<SingleFlashCard> AboveRating(int Rating)
        {
            if(!m_shuffled)
            {
                Shuffle();
            }
            foreach(SingleFlashCard card in m_shuffledCards)
            {
                if(card.successRank() > Rating)
                {
                    yield return card;
                }

            }
        }
        
        public void Shuffle()
        {
            m_shuffledCards.Clear();

            List<SingleFlashCard> originalOrder = new List<SingleFlashCard>();
            foreach(KeyValuePair<string,SingleFlashCard> kvp in m_cards)
            {
                originalOrder.Add(kvp.Value);
            }

            int count_remaining = originalOrder.Count;

            Random m_rand = new Random();

            for (int currOriginalOfst = 0;
                 currOriginalOfst < originalOrder.Count;
                 currOriginalOfst++)
            {
                int pickedOfst = m_rand.Next(0,count_remaining);
                m_shuffledCards.Add(originalOrder[pickedOfst]);
                originalOrder[pickedOfst] = originalOrder[count_remaining-1];
                count_remaining--;
            }
        }

        public void SaveDeck(string name)
        {
            List<SingleFlashCard> flatList = new List<SingleFlashCard>();

            foreach(KeyValuePair<string,SingleFlashCard> kvp in m_cards)
            {
                flatList.Add(kvp.Value);
            }

            XmlSerializer myXMLSerializer = new XmlSerializer(typeof(List<SingleFlashCard>));
            TextWriter twriter = new StreamWriter(name);

            myXMLSerializer.Serialize(twriter,flatList);

            twriter.Close();
        }
        public void LoadDeck(string name)
        {
            // first, check to make sure we have a good file name..
            // throw exception if name is bad?
            // if name good, open and deserialize
        }
    }
}
