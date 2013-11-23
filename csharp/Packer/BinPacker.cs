using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.IO;
using System.Runtime.Serialization.Formatters.Binary;
using System.Runtime.Serialization;

namespace Packer
{
    [Serializable]
    class FileToTransmit
    {
        private string filename = "";
        private byte[] file_image = null;

        public FileToTransmit(string   name,
                              byte []  image)
        {
            filename    = name;
            file_image  = image;
        }

        public string Filename
        {
            get 
            { 
                return filename; 
            }
        }

        public byte[] File_image
        {
            get 
            { 
                return file_image; 
            }
        }
    }
    class BinPacker
    {

        List<FileToTransmit> m_Files = new List<FileToTransmit>();
        IFormatter formatter = (IFormatter)new BinaryFormatter();

        internal List<FileToTransmit> Files
        {
            get 
            { 
                return m_Files; 
            }
            set 
            { 
                m_Files = value; 
            }
        }

        /// <summary>
        /// serialize the internal image of the Files list.
        /// </summary>
        /// <returns></returns>
        public byte [] GetBinaryImage()
        {
            MemoryStream ms = new MemoryStream();
            // Create a formatter object based on command line arguments
            // Serialize the object graph to stream
            formatter.Serialize(ms, m_Files);
            // All done
            ms.Close();
            return ms.ToArray();
        }

        /// <summary>
        /// deserialize a serialized image of the Files list. 
        /// </summary>
        /// <param name="image">the binary image to be deserialized</param>
        /// <exception cref="SerializationException">thrown if deserialization fails</exception>
        /// <exception cref="ArgumentException">thrown if deserialization fails</exception>
        public void SetBinaryImage(byte [] image)
        {
            MemoryStream ms = new MemoryStream(image);
            // Deserialize the object graph from stream
            m_Files = formatter.Deserialize(ms) as List<FileToTransmit>;

            // Tests like this are relevant in projects which 
            // serialize multiple object types
            if (m_Files == null)
            {
                throw new SerializationException("not a serialized List<FileToTransmit>!!");
            }
            // All done
            ms.Close();
        }
    }
 
}
