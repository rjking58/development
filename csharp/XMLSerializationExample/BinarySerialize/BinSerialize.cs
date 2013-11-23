using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

namespace BinarySerialize
{
    class BinSerialize
    {
        static void Main(string[] args)
        {
        }
    }
}



using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Xml.Serialization;

namespace XMLSerializationExample
{
    public class contained 
    {
        private int m_i;
        private string id = "contained";

        public int M_i
        {
            set
            {
                m_i = value;
            }
            get
            {
                return m_i;
            }
        }

        public string ID
        {
            set
            {
                id = value;
            }
            get
            {
                return id;
            }
        }
        public contained(int i)
        {
            m_i = i;
        }
        public contained()
        {
        }
        public void incrementInts()
        {
            m_i++;
        }
        
        public void Iam()
        {
            Console.WriteLine(id + m_i);
        }

    }
    public class classToSave
    {
        private static string   SAVE_NAME = "classToSave";
        public contained       c;
        public contained       c2;
        public int             m_i;
        public string          m_string = "one";

        public classToSave(int i, int j, int k)
        {
            m_i = i;
            c = new contained(j);
            c2 = new contained (k);
        }
        public classToSave()
        {
        }

        public void Iam()
        {
            Console.WriteLine("classToSave(" + m_i + m_string + ")");
            c.Iam();
            c2.Iam();
        }
        public void incrementInts()
        {
            m_i++;
            c.incrementInts();
            c2.incrementInts();
        }

        public static classToSave LoadFromDisk()
        {
            StreamReader sr;
            classToSave cts;
            XmlSerializer xmlser = 
                new XmlSerializer(typeof(classToSave));
            try
            {
                sr = new StreamReader(SAVE_NAME);
                cts = (classToSave) xmlser.Deserialize(sr);
                sr.Close();
            }
            catch
            {
                Console.WriteLine("first time.. creating");
                cts = new classToSave(10,20,30);
            }
            return cts;
        }
        public void SaveToDisk()
        {
            //Directory.CreateDirectory(Path.GetDirectoryName(SAVE_NAME));
            StreamWriter sw = new StreamWriter(SAVE_NAME);
            XmlSerializer xmlser = new XmlSerializer(typeof(classToSave));
            xmlser.Serialize(sw,this);
            sw.Close();
        }
    }
    
    class serialization_example
    {
        static void Main(string[] args)
        {
            classToSave cs1 = classToSave.LoadFromDisk();
            cs1.Iam();
            cs1.incrementInts();
            cs1.SaveToDisk();

            Console.ReadLine();
        }

    }
}
