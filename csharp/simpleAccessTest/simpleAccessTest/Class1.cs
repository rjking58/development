using System;
using System.Collections.Generic;
using System.Text;

namespace simpleAccessTest
{
    public interface IInternalClass
    {
        int Method1();
    }
    internal class InternalClass :IInternalClass
    {
        int m_one;
        int m_two;
        public InternalClass(int i, int j)
        {
            m_one = i;
            m_two = j;
        }
        public int Method1()
        {
            return m_one;
        }
        public int Method2()
        {
            return m_two;
        }
        public void Method2Set(int two)
        {
            m_two = two;
        }
    }

    public class extRef
    {
        List<InternalClass> m_ics = new List<InternalClass>();
        public void makeEntry(int i, int j)
        {
            m_ics.Add(new InternalClass(i,j));
        }
        
        public IInternalClass this[int idx]
        {
            get
            {
                IInternalClass retval = null;
                if (idx < m_ics.Count)
                {
                    retval = (IInternalClass) m_ics[idx];
                }
                return retval;
            }
        }
        public int Count()
        {
            return m_ics.Count;
        }
        
    }
    
    
}
