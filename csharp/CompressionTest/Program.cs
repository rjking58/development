using System;
using System.Collections.Generic;
using System.Text;

using System.IO;
using System.IO.Compression;

namespace CompressionTest
{

    class DeflateResult 
    {
        private int m_deflatedBytes = 0;
        public int DeflatedBytes
        {
            get
            {
                return m_deflatedBytes;
            }
            set
            {
                m_deflatedBytes = value;
            }
        }
        public DeflateResult(int p_deflatedBytes)
        {
            m_deflatedBytes = p_deflatedBytes;
        }
        
    }
    class Program
    {
        
        static void FillArrayWithRandomNums(byte [] buffer)
        {
            Random m_rnd = new Random((int) DateTime.Now.Ticks);
            m_rnd.NextBytes(buffer);
        }
        
        static void Main(string[] args)
        {
            const int TEST_COUNT = 50000;
            const int ORIGINAL_LEN = 160;
            byte [] compressCandidate = new byte [ORIGINAL_LEN];
            List<DeflateResult> results = new List<DeflateResult>();
            
            for (int testCount = 0;
                 testCount < TEST_COUNT;
                 testCount++)
            {
                MemoryStream ms = new MemoryStream();
                FillArrayWithRandomNums(compressCandidate);
                
                // Use the newly created memory stream for the compressed data.
                GZipStream deflatedStream = new GZipStream(ms,CompressionMode.Compress,true);
                //Console.WriteLine("Compression");
                deflatedStream.Write(compressCandidate,0,compressCandidate.Length);
                // Close the stream.
                deflatedStream.Close();
                
                results.Add(new DeflateResult((int)ms.Length));
                
                ms.Position = 0;
                
                GZipStream inflater = new GZipStream(ms,CompressionMode.Decompress);
                byte [] resultBuffer = new byte[compressCandidate.Length];
                int totalCount = ReadAllBytesFromStream(inflater,resultBuffer);
                if(! CompareData(compressCandidate,resultBuffer))
                {
                    throw new System.ApplicationException("bad compare!");
                }
            }
            // 
            // figure average and count of deflations that were actually INflations..
            double  aggregatedDeflateSize = 0.0;
            int     inflateCount = 0;
            int     minSize = 0;
            int     maxSize = 0;
            for (int currtest = 0; currtest < TEST_COUNT; currtest++)
            {
                aggregatedDeflateSize += (double) results[currtest].DeflatedBytes;
                
                if (results[currtest].DeflatedBytes > ORIGINAL_LEN)
                {
                    inflateCount++;
                }
                if(currtest == 0)
                {
                    minSize = results[currtest].DeflatedBytes;
                    maxSize = results[currtest].DeflatedBytes;
                }
                else
                {
                    minSize = Math.Min(minSize,results[currtest].DeflatedBytes);
                    maxSize = Math.Max(maxSize,results[currtest].DeflatedBytes);
                }
            }
            double avgDeflateSize = (double)(aggregatedDeflateSize/50000.0);
            Console.WriteLine("avgDeflateSize[" + avgDeflateSize + "]");
            Console.WriteLine("inflateCount[" + inflateCount + "]");
            Console.WriteLine("minSize[" + minSize + "]");
            Console.WriteLine("maxSize[" + maxSize + "]");

        }
        public static int ReadAllBytesFromStream(Stream stream,byte[] buffer)
        {
            // Use this method is used to read all bytes from a stream.
            bool endOfStream = false;
            int offset = 0;
            while (! endOfStream)
            {
                int byteread = stream.ReadByte();
                if(byteread != -1)
                {
                    buffer[offset] = (byte) byteread;
                    offset++;
                }
                else
                {
                    endOfStream = true;
                }
            }
            return offset;
        } 
        public static bool CompareData(byte[] buf1,byte[] buf2)
        {
            // Use this method to compare data from two different buffers.
            if (buf1.Length != buf2.Length)
            {
                Console.WriteLine("Number of bytes in two buffer are different {0}:{1}",
                                  buf1.Length,
                                  buf2.Length);
                return false;
            }

            for (int i = 0;i < buf1.Length;i++)
            {
                if (buf1[i] != buf2[i])
                {
                    Console.WriteLine("byte {0} is different {1}|{2}",i,buf1[i],buf2[i]);
                    return false;
                }
            }
            //Console.WriteLine("All bytes compare.");
            return true;
        }

    }
}
