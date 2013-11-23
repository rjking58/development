using System;
using System.Collections.Generic;
using System.Text;


namespace FlashCard
{
    [Serializable]
    public class SingleFlashCard
    {
        private string m_FirstSide;
        private string m_SecondSide;
        private Queue<bool> m_success = new Queue<bool>();
        
        public string First
        {
            get
            {
                return m_FirstSide;
            }
            set
            {
                m_FirstSide = value;
            }
        }
        public string Second
        {
            get
            {
                return m_SecondSide;
            }
            set
            {
                m_SecondSide = value;
            }
        }
    
        public SingleFlashCard(string first,
                               string second)
        {
            m_FirstSide = first;
            m_SecondSide = second;
        }

        public SingleFlashCard()
        {
        }

        public void setSuccess(bool success)
        {
            m_success.Enqueue(success);
            if(m_success.Count > 10)
            {
                m_success.Dequeue();
            }
        }
        public int successRank()
        {
            int totalEntries = m_success.Count;
            int count_of_true = 0;
            foreach (bool successRating in m_success)
            {
                if (successRating)
                {
                    count_of_true++;
                }
            }

            return (int)(  (    (   (double)count_of_true   )
                                    /
                                (   (double)totalEntries    )   
                           )
                           *    10.0
                        );     
            
        }
        public override string ToString()
        {
            return m_FirstSide;
        }
    }
}
