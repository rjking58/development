using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.IO;
using System.Runtime.Serialization.Formatters.Binary;
using System.Runtime.Serialization;
using System.Threading;

namespace BinarySerializationTests
{
    [Serializable]
    class ContainedClass
    {
        private int m_z;
        
        public int Z
        {
            get
            {
                return m_z;
            }
            set
            {
                m_z = value;
            }
        }
    }
    [Serializable]
    class Class1
    {
        private int m_x = 5;
        private int m_y = 44;

        //private ContainedClass m_cc = new ContainedClass();

        public Class1()
        {
            m_y = 44;
            //m_cc = new ContainedClass();

        }
        public int X
        {
            get
            {
                return m_x;
            }
            set
            {
                m_x = value;
            }
        }
        public int Y
        {
            get
            {
                return m_y;
            }
            set
            {
                m_y = value;
            }
        }
#if false
        public ContainedClass Cc
        {
            get
            {
                return m_cc;
            }
        }
#endif

    }
    class Program
    {
        private const string  f_name = "serializedClass1.bin";
        static void Main(string[] args)
        {
            Class1 c1 = null;
            IFormatter formatter = (IFormatter) new BinaryFormatter();
            Stream file = null;
            if(! File.Exists (f_name))
            {
                file = File.Open(f_name,FileMode.Create);
                Console.WriteLine("creating..");
                // write it
                c1 = new Class1();
                c1.X = 10;
                formatter.Serialize(file,c1);
            }
            else
            {
                file = File.Open(f_name,FileMode.Open);
                Console.WriteLine("reading..");
                c1 = formatter.Deserialize(file) as Class1;
            }
            file.Close();
            Console.WriteLine(c1.X);
            Console.WriteLine(c1.Y);
#if false
            if(c1.Cc != null)
            {
                Console.WriteLine("not null");
            }
            else
            {
                Console.WriteLine("NULL");
            }
#endif

        }
    }
}
