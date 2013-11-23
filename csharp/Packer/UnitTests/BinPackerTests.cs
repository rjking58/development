using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.Serialization;

using NUnit.Framework;

namespace Packer.UnitTests
{
    
    [TestFixture]
    public class BinPackerTests
    {
        private byte [] image1 = null;
        private byte [] image2 = null;
        private byte [] image3 = null;
        private const int image1_sz = 1024;
        private const int image2_sz = 3002;
        private const int image3_sz = 55;

        [TestFixtureSetUp]
        public void TestFixtureSetUp()
        {
            image1 = new byte [image1_sz];
            image2 = new byte [image2_sz];
            image3 = new byte [image3_sz];
           
            int val = 0;
            for(int currByte = 0;
                currByte < image1.Length;
                currByte++)
            {
                image1[currByte] = (byte) val;
                val++;
            }
            for(int currByte = 0;
                currByte < image2.Length;
                currByte++)
            {
                image2[currByte] = (byte) val;
                val++;
            }
            for(int currByte = 0;
                currByte < image3.Length;
                currByte++)
            {
                image3[currByte] = (byte) val;
                val++;
            }
        }

        [SetUp]
        public void Setup()
        {
        }

        [TestFixtureTearDown]
        public void TestFixtureTearDown()
        {
        }

        [TearDown]
        public void Teardown()
        {
        }
        [Test]
        public void BadImageTest()
        {
            byte [] image1 = {1,2,3,4};
            BinPacker pkr1 = new BinPacker();

            try
            {
                pkr1.SetBinaryImage(image1);
                Assert.IsTrue(false);
            }
            catch(SerializationException ex)
            {
                Console.WriteLine(ex.Message);
            }
        }
        [Test]
        public void EmptyImageTest()
        {
            BinPacker pkr1 = new BinPacker();
            BinPacker pkr2 = new BinPacker();

            byte [] img = pkr1.GetBinaryImage();
            pkr2.SetBinaryImage(img);
            Assert.AreEqual(0,pkr2.Files.Count);
        }
        [Test]
        public void BinPackerBasicTest()
        {
            const string image_name1 = "first";
            const string image_name2 = "second";
            const string image_name3 = "third";


            BinPacker pkr1 = new BinPacker();
            BinPacker pkr2 = new BinPacker();

            pkr1.Files.Add(new FileToTransmit(image_name1,image1));
            pkr1.Files.Add(new FileToTransmit(image_name2,image2));
            pkr1.Files.Add(new FileToTransmit(image_name3,image3));
            byte [] binImage = pkr1.GetBinaryImage();
            pkr2.SetBinaryImage(binImage);
            Assert.AreEqual(3,pkr2.Files.Count);
            bool first_seen = false;
            bool second_seen = false;
            bool third_seen = false;
            byte [] compare_img = null;
            foreach(FileToTransmit ftt in pkr2.Files)
            {
                switch(ftt.Filename)
                {
                    case image_name1:
                        first_seen = true;
                        compare_img = image1;
                        break;
                    case image_name2:
                        second_seen = true;
                        compare_img = image2;
                        break;
                    case image_name3:
                        third_seen = true;
                        compare_img = image3;
                        break;
                }
                int curr_byte = 0;
                foreach(byte b in ftt.File_image)
                {
                    Assert.AreEqual(b,compare_img[curr_byte]);
                    curr_byte++;
                }
            }

            Assert.IsTrue(first_seen);
            Assert.IsTrue(second_seen);
            Assert.IsTrue(third_seen);
        }
    }
       
}
