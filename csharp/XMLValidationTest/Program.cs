using System;
using System.Collections.Generic;
using System.Text;

using System.Xml;
using System.Xml.Schema;

namespace XMLValidationTest
{
    class Program
    {
        private static bool isValid = true; // If a validation error occurs,
                                            // set this flag to false in the
                                            // validation event handler. 
        static void Main(string[] args)
        {
            XmlTextReader r = new XmlTextReader(@"..\..\GenKeyIDList.xml");
            XmlValidatingReader v = new XmlValidatingReader(r);
            
            v.ValidationType = ValidationType.Schema;
            v.ValidationEventHandler += 
               new ValidationEventHandler(MyValidationEventHandler);

            while (v.Read())
            {
                // Can add code here to process the content.
                Console.WriteLine(v.LocalName);

                if (v.LocalName == "GenericKeyIDList")
                {
                    if(v.IsStartElement())
                    {
                        v.MoveToFirstAttribute();               
                        v.ReadAttributeValue();
                        Console.WriteLine("    " + v.ReadContentAsString());
                    }
                }
            }
            v.Close();

            // Check whether the document is valid or invalid.
            if (isValid)
            {
               Console.WriteLine("Document is valid");
            }
            else
            {
               Console.WriteLine("Document is invalid");
            }

        
        }
        
        public static void MyValidationEventHandler(object sender, 
                                                    ValidationEventArgs args) 
        {
           isValid = false;
           Console.WriteLine("Validation event\n" + args.Message);
        }
        
    }
}
