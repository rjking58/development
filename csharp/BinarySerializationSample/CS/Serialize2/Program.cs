using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;
using System.Runtime.Serialization;



namespace Serialize2
{
    [Serializable]
    class SimpleOne
    {
        private int m_i;
        private int m_j;
        public SimpleOne(int i, int j)
        {
            m_i = i;
            m_j = j;
        }

        public override string ToString()
        {
            StringBuilder sb = new StringBuilder();
            sb.Append("i(");
            sb.Append(m_i);
            sb.Append(") j(");
            sb.Append(m_j);
            sb.Append(")\n");
                         
            return sb.ToString();
        }
        
    }

    class Serialize2
    {
        private static void Usage()
        {
            Console.WriteLine("serialize2 ");
            Console.WriteLine("       /r read from binary serialized file ");
            Console.WriteLine("       /w write to binary serialized file ");
        }
        public static void Main(String[] args)
        {
            bool readfile = false;
            bool writefile = false;

            if (args.Length == 0)
            {
                Usage();
                return;
            }
            if (args[0][0] == '-' || args[0][0] == '/')
            {
                if (args[0][1] == '?')
                {
                    Usage();
                    return;
                }

                readfile  = (args[0][1] == 'r');
                writefile = (args[0][1] == 'w');
            }

        


            if (readfile)
            {
                if (!File.Exists("serializedSimpleOne"))
                {
                    Console.WriteLine("Input file not found: {0}\n", "serializedSimpleOne");
                    return;
                }

                Console.WriteLine("\nDeserializing");

                Stream file = File.Open("serializedSimpleOne", FileMode.Open);

                // Create a formatter object based on command line arguments
                IFormatter formatter = (IFormatter)new BinaryFormatter();

                // Deserialize the object graph from stream
                try
                {
                    SimpleOne so = formatter.Deserialize(file) as SimpleOne;

                    // Tests like this are relevant in projects which 
                    // serialize multiple object types
                    if (so != null)
                    {
                        Console.WriteLine(so.ToString());
                    }
                    else
                    {
                        Console.WriteLine("The deserialized object graph" + " is not a SimpleOne.");
                    }
                }
                // Handler for BinaryFormatter exception
                catch (SerializationException)
                {
                    Console.WriteLine("Could not deserialize file.  Check that the input file is valid and the requested serialization format is correct.");
                }
                // Handler for SoapException
                catch (ArgumentException)
                {
                    Console.WriteLine("Could not deserialize file.  Check that the input file is valid and the requested serialization format is correct.");
                }
                // All done
                file.Close();
            }

            if (writefile)
            {
                SimpleOne so = new SimpleOne(4, 5);
                Console.WriteLine(so.ToString());
                
                Stream file = File.Open("serializedSimpleOne", FileMode.Create);
                // Create a formatter object based on command line arguments
                IFormatter formatter = (IFormatter)new BinaryFormatter();
                // Serialize the object graph to stream
                formatter.Serialize(file, so);
                // All done
                file.Close();
            }
            
        }
    // Note that this type is attributed as serializable
    }
}
