using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections;

namespace JSONExperiment
{
    interface JSONValue
    {
        string GetJSON();
    } 
    class JSONObject : JSONValue
    {
        public void AddPair(string name,JSONValue val)
        {

        }
        public string GetJSON()
        {
            StringBuilder sb = new StringBuilder();
            sb.Append("{");
            int valCnt = 0;
            foreach (KeyValuePair<string,JSONValue> kvp in m_KVPairs)
            {
                if (valCnt != 0)
                {
                    sb.Append(",");
                }
                sb.Append("\"" + kvp.Key + "\"" + " : " + kvp.Value.GetJSON() + "\n");
                valCnt++;
            }
            sb.Append("}");
            return sb.ToString();
        }
        private Dictionary<string, JSONValue> m_KVPairs = new Dictionary<string, JSONValue>();
    }
    class JSONArray : JSONValue
    {
        public void AddValue(JSONValue val)
        {
            m_Vals.Add(val);
        }
        public string GetJSON()
        {
            StringBuilder sb = new StringBuilder();
            sb.Append("[");
            int valCnt = 0;
            foreach(JSONValue jv in m_Vals)
            {
                if(valCnt != 0)
                {
                    sb.Append(",");
                }
                sb.Append(jv.GetJSON());
                valCnt++;
            }
            sb.Append("]");
            return sb.ToString();
        }
        private List<JSONValue> m_Vals = new List<JSONValue>();
    }
    class JSONNumber : JSONValue
    {
        public JSONNumber(long Val)
        {
            m_Val = Val;
        }
        public string GetJSON()
        {
            return m_Val.ToString();
        }
        private long m_Val = 0;
    }
    
    class JSONString : JSONValue
    {
        public string GetJSON()
        {
            return m_Val;
        }
        private string m_Val = "";
    }
    
    class JSONBoolean : JSONValue
    {
        public string GetJSON()
        {
            string retVal = "false";
            if(m_Val)
            {
                retVal = "true";
            }
            return retVal;
        }
        private Boolean m_Val = false;
    }
    
    class Program
    {
        static void Main(string[] args)
        {
            string exampleJSON = "{ \"soda\" : \n"
                                + "  { \"device\": \n"
                                + "    { \"mfg\": \"Vandelay Industries\", \n"
                                + "      \"model\": \"Red Dot\", \n"
                                + "      \"firmware\": \"1.1.2\", \n"
                                + "      \"hardware\": \"1.0.0\", \n"
                                + "      \"serial-number\": \"L97364892383\", \n"
                                + "      \"soda-class\": [ \"wwan\", \"hotspot\", \"gps\" ] \n"
                                + "    } \n"
                                + "  } \n"
                                + "}\n";


            Console.WriteLine(exampleJSON);
            bool success = false;
            object result = JSON.JsonDecode(exampleJSON, ref success);

            JSONObject rootObj = new JSONObject();

            LoadJSONClass(rootObj, result);
            
            rootObj = new JSONObject();
        }
        
        static void LoadJSONClass(JSONObject JSONObj,object parsed_json)
        {
            if (parsed_json is Hashtable)
            {
                Hashtable parsed_json_ht = (Hashtable)parsed_json;
                foreach (DictionaryEntry de in parsed_json_ht)
                {
                    Console.Write("k:" + de.Key);

                    if(de.Value is Hashtable || de.Value is ArrayList)
                    {
                        Console.WriteLine(" ");
                        LoadJSONClass(JSONObj, de.Value);
                    }
                    else
                    {
                        Console.WriteLine(" v:" + de.Value.ToString());
                    }
                }
            }
            else if (parsed_json is ArrayList)
            {
                ArrayList parsed_json_al = (ArrayList)parsed_json;
                foreach( object obj in parsed_json_al)
                {
                    Console.WriteLine(obj.ToString());
                }
            }
        }
    }
}
