using System;
using System.Collections.Generic;
using System.Text;

namespace PropertyGridDemo
{
    class SimpleClass
    {
        private string m_name;
        private int m_num;
        public string Name
        {
            get
            {
                return m_name;
            }
            set
            {
                m_name = value;
            }
        }
        public int SimpleNumber
        {
            get
            {
                return m_num;
            }
            set
            {
                m_num = value;
            }
        }
    }
}
