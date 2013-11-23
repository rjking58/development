using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BXMLToBinaryExample
{
    class IDAndName
    {
        private byte m_ID;
        private string m_Name;

        public byte ID
        {
            get 
            { 
                return m_ID; 
            }
        }

        public string Name
        {
            get 
            { 
                return m_Name; 
            }
        }
        public IDAndName(byte   ID,
                         string Name)
        {
            m_ID = ID;
            m_Name = Name;
        }
    }
}
