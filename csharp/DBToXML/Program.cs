using System;
using System.Collections.Generic;
using System.Text;

namespace DBToXML
{
    class Program
    {
        static void Main(string[] args)
        {
            RemoteKeysDBToXMLDS rk_db_to_XML = new RemoteKeysDBToXMLDS();
            
            RemoteKeysDBToXMLDSTableAdapters.RemoteKeysTableAdapter rkTA = 
                new DBToXML.RemoteKeysDBToXMLDSTableAdapters.RemoteKeysTableAdapter();
                
            rkTA.Fill(rk_db_to_XML.RemoteKeys);
            rk_db_to_XML.RemoteKeys.KeyFlagsColumn.
            rk_db_to_XML.WriteXml("RemoteKeys.xml");
            rk_db_to_XML.WriteXmlSchema("RemoteKeys.xsd");
        }
    }
}
