using System;
using System.Collections.Generic;
using System.Text;

using System.IO;
using System.Xml;
using System.Xml.Schema;

namespace XMLTests
{
    class Program
    {
        static bool m_isValid = false;
        
        static void Main(string[] args)
        {

            XmlTextReader r = new XmlTextReader(@"..\..\XMLFile1.xml");
            XmlValidatingReader v = new XmlValidatingReader(r);
            v.ValidationType = ValidationType.Schema;
            v.ValidationEventHandler += 
               new ValidationEventHandler(MyValidationEventHandler);

            while(v.Read())
            {
                // Can add code here to process the content.
            }
            v.Close();

            // Check whether the document is valid or invalid.
            if(m_isValid)
            {
                Console.WriteLine("Document is valid");
            }
            else
            {
                Console.WriteLine("Document is invalid");
            }


            
        /*
            XmlTextWriter xtw = new XmlTextWriter(new StreamWriter("test1.xml"));
            
            xtw.WriteStartDocument(true);
            xtw.WriteStartElement("MapVals");
            
            xtw.WriteStartElement("MapValKey1");
            xtw.WriteAttributeString("val1","a");
            xtw.WriteAttributeString("val2","b");
            xtw.WriteEndElement();
            
            xtw.WriteStartElement("MapValKey2");
            xtw.WriteAttributeString("val1","qf");
            xtw.WriteAttributeString("val2","xt");
            xtw.WriteEndElement();
            
            xtw.WriteStartElement("MapValKey3");
            xtw.WriteAttributeString("val1","wwu");
            xtw.WriteAttributeString("val2","verble");
            xtw.WriteEndElement();
            
            xtw.WriteEndElement();
            
            xtw.WriteEndDocument();
            xtw.Close();
        */
        }
        
        public static void MyValidationEventHandler(object sender,
                                            ValidationEventArgs args)
        {
            m_isValid = false;
            Console.WriteLine("Validation event\n" + args.Message);
        }

        
    }
}
