using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Packer
{
    class Program
    {
        static void Main(string[] args)
        {
            byte [] image1 = {1,2,3,4};
            byte [] image2 = {5,6,7,8};


            BinPacker pkr1 = new BinPacker();
            BinPacker pkr2 = new BinPacker();

            pkr1.Files.Add(new FileToTransmit("first",image1));
            pkr1.Files.Add(new FileToTransmit("second",image2));
            byte [] binImage = pkr1.GetBinaryImage();
            pkr2.SetBinaryImage(binImage);
            foreach(FileToTransmit ftt in pkr2.Files)
            {
                Console.WriteLine(ftt.Filename);
                foreach(byte b in ftt.File_image)
                {
                    Console.Write(b + " ");
                }
                Console.WriteLine();
            }
#if false           
            MemoryStream ms = new MemoryStream();
            // Create a formatter object based on command line arguments
            IFormatter formatter = (IFormatter)new BinaryFormatter();
            // Serialize the object graph to stream
            formatter.Serialize(ms, filelist);
            // All done
            ms.Close();
            byte [] serializedAry = ms.ToArray();

            MemoryStream ms2 = new MemoryStream(serializedAry);
            // Deserialize the object graph from stream
            try
            {
                filelistDeserialized = formatter.Deserialize(ms2) as List<FileToTransmit>;

                // Tests like this are relevant in projects which 
                // serialize multiple object types
                if (filelistDeserialized == null)
                {
                    Console.WriteLine("The deserialized object graph is not a List<FileToTransmit>.");
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
            foreach(FileToTransmit ftt in filelistDeserialized)
            {
                Console.WriteLine(ftt.Filename);
                foreach(byte b in ftt.File_image)
                {
                    Console.Write(b + " ");
                }
                Console.WriteLine();
            }
            ms2.Close();
#endif

        }
    }
}
