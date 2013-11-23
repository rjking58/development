using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;
using System.IO;

using NUnit.Framework;

namespace BytesToStringsToBytes
{
    public class ByteArrayAsString
    {

        public enum StringFieldError
        {
            SUCCESS,
            STRING_TOO_LONG,
        }
        
        private byte[]  internal_ary;
        private int     curr_length;

        public ByteArrayAsString(int length_of_byte_ary)
        {
            // make sure we have space for the null.
            // length + null
            internal_ary = new byte[length_of_byte_ary+1];

            clear_ary();
            curr_length = 0;
        }
        
        public int Length
        {
            get
            {
                return curr_length;
            }
        }

        public int MaxLength
        {
            get
            {
                return (internal_ary.Length - 1);
            }
        }

        public StringFieldError SetValue(string str)
        {
            StringFieldError retval = StringFieldError.STRING_TOO_LONG;

            // converter..
            ASCIIEncoding a_encoding = new ASCIIEncoding();

            // must be one less than our internal length.. since null is included in the array length..
            if (str.Length <= (internal_ary.Length - 1))
            {
                // get our ascii encoded byte stream..
                byte[] re_encoded = a_encoding.GetBytes(str.ToCharArray());

                // clear internal array
                clear_ary();

                // copy the ascii encoded array.
                for (int re_encoded_offset = 0;
                     re_encoded_offset < re_encoded.Length;
                     re_encoded_offset++)
                {
                    internal_ary[re_encoded_offset] = re_encoded[re_encoded_offset];
                }
                curr_length = str.Length;

                for (int offset = 0;
                     offset < internal_ary.Length;
                     offset++)
                {
                    Console.Write("{0:X2} ",internal_ary[offset]);
                }
                Console.WriteLine();
                       
                retval = StringFieldError.SUCCESS;
            }

            return retval;
        }
        public string GetString
        {
            get
            {
                ASCIIEncoding a_encoding = new ASCIIEncoding();
                int internal_ary_actual_string_len = 0;
                for (int offset = 0                         ;
                     (      offset < internal_ary.Length
                       &&   internal_ary[offset] != 0       );
                     offset++                                   )
                {
                    internal_ary_actual_string_len++;
                }

                if (internal_ary_actual_string_len == internal_ary.Length)
                {
                    // add a null, since this is a truly wierd error.
                    internal_ary_actual_string_len--;
                    internal_ary[internal_ary_actual_string_len] = 0;
                }

                return a_encoding.GetString(internal_ary,
                                            0,
                                            internal_ary_actual_string_len);
            }
        }

        public void CreateBinaryImage(BinaryWriter bw)
        {
            
        }
/*
        public GLOBAL_CONSTANTS.FileErrorCodes ReadBinaryImage(BinaryReader br)
        {

        }
*/        
        private void clear_ary()
        {
            for (int internal_offset = 0;
                 internal_offset < internal_ary.Length;
                 internal_offset++)
            {
                internal_ary[internal_offset] = 0;
            }
        }
    }
    
    public class Class1
    {
        static void Main()
        {
/*        
            byte[] somestring_as_bytes = new byte[10];
            

            for( int offset = 0;
                 offset < somestring_as_bytes.Length;
                 offset++)
            {
                somestring_as_bytes[offset] = 0;
            }
            
            somestring_as_bytes[0] = (byte) 'X';
            somestring_as_bytes[1] = (byte)'y';
            somestring_as_bytes[2] = (byte)'z';
            for (int offset = 0;
                 offset < somestring_as_bytes.Length;
                 offset++)
            {
                Console.Write("{0:X2} ",somestring_as_bytes[offset]);
            }
            Console.WriteLine();
            
            

            // must scan for null and provide it to ASCIIEncoding.GetString.. since its
            // STUPID.            
            int somestring_as_bytes_len = 0;
            for( int offset = 0;
                 (    offset < somestring_as_bytes.Length
                   && somestring_as_bytes[offset] != 0      );
                 offset++)
            {
                somestring_as_bytes_len++;
            }
            ASCIIEncoding a_encoding = new ASCIIEncoding();
            string mystr = a_encoding.GetString(somestring_as_bytes,0,somestring_as_bytes_len);
            
            Console.WriteLine("mystr(" + mystr.Length + ")[" + mystr + "]");
            
            
            // now.. back to a byte array
            byte [] re_encoded = a_encoding.GetBytes(mystr.ToCharArray());
            Console.WriteLine("re_encoded(" + re_encoded.Length + ")");
            for (int offset = 0;
                 offset < re_encoded.Length;
                 offset++)
            {
                Console.Write("{0:X2} ",re_encoded[offset]);
            }
            Console.WriteLine();
            
*/       

            // test our string implementation..     

            ByteArrayAsString bas_1 = new ByteArrayAsString(1);
            ByteArrayAsString bas_10 = new ByteArrayAsString(10);
            ByteArrayAsString bas_30 = new ByteArrayAsString(30);

            Console.WriteLine("setvalue bas_1 to 'ab'");
            Console.WriteLine(bas_1.SetValue("ab"));
            Console.WriteLine("bas_1.MaxLength:" + bas_1.MaxLength);            
            Console.WriteLine("bas_1.Length:" + bas_1.Length);
            Console.WriteLine("bas_1.GetString(" + bas_1.GetString + ")");

            Console.WriteLine("setvalue bas_1 to ''"); 
            Console.WriteLine(bas_1.SetValue(""));
            Console.WriteLine("bas_1.MaxLength:" + bas_1.MaxLength);
            Console.WriteLine("bas_1.Length:" + bas_1.Length);
            Console.WriteLine("bas_1.GetString(" + bas_1.GetString + ")");

            Console.WriteLine("setvalue bas_1 to 'a'");
            Console.WriteLine(bas_1.SetValue("a"));
            Console.WriteLine("bas_1.MaxLength:" + bas_1.MaxLength); 
            Console.WriteLine("bas_1.Length:" + bas_1.Length);
            Console.WriteLine("bas_1.GetString(" + bas_1.GetString + ")");
            
            Console.WriteLine("setvalue to 'ab'");
            Console.WriteLine(bas_1.SetValue("ab"));
            Console.WriteLine("bas_1.MaxLength:" + bas_1.MaxLength);            
            Console.WriteLine("bas_1.Length:" + bas_1.Length);
            Console.WriteLine("bas_1.GetString(" + bas_1.GetString + ")");


            Console.WriteLine("setvalue to '12345678901'");
            Console.WriteLine(bas_10.SetValue("12345678901"));
            Console.WriteLine("bas_10.MaxLength:" + bas_10.MaxLength);            
            Console.WriteLine("bas_10.Length:" + bas_10.Length);
            Console.WriteLine("bas_10.GetString(" + bas_10.GetString + ")");

            Console.WriteLine("setvalue to ''");
            Console.WriteLine(bas_10.SetValue(""));
            Console.WriteLine("bas_10.MaxLength:" + bas_10.MaxLength);
            Console.WriteLine("bas_10.Length:" + bas_10.Length);
            Console.WriteLine("bas_10.GetString(" + bas_10.GetString + ")");

            Console.WriteLine("setvalue to 'abcde'");
            Console.WriteLine(bas_10.SetValue("abcde"));
            Console.WriteLine("bas_10.MaxLength:" + bas_10.MaxLength);                        
            Console.WriteLine("bas_10.Length:" + bas_10.Length);
            Console.WriteLine("bas_10.GetString(" + bas_10.GetString + ")");

            Console.WriteLine("setvalue to 'abcdefghij'");
            Console.WriteLine(bas_10.SetValue("abcdefghij"));
            Console.WriteLine("bas_10.MaxLength:" + bas_10.MaxLength);                        
            Console.WriteLine("bas_10.Length:" + bas_10.Length);
            Console.WriteLine("bas_10.GetString(" + bas_10.GetString + ")");

            Console.WriteLine("setvalue to '12345678901'");
            Console.WriteLine(bas_10.SetValue("12345678901"));
            Console.WriteLine("bas_10.MaxLength:" + bas_10.MaxLength);                        
            Console.WriteLine("bas_10.Length:" + bas_10.Length);
            Console.WriteLine("bas_10.GetString(" + bas_10.GetString + ")");

            Console.WriteLine("setvalue to '1234567890123456789012345678901'");
            Console.WriteLine(bas_30.SetValue("1234567890123456789012345678901"));
            Console.WriteLine("bas_30.MaxLength:" + bas_30.MaxLength);
            Console.WriteLine("bas_30.Length:" + bas_30.Length);
            Console.WriteLine("bas_30.GetString(" + bas_30.GetString + ")");

            Console.WriteLine(bas_30.SetValue(""));
            Console.WriteLine("bas_30.MaxLength:" + bas_30.MaxLength);
            Console.WriteLine("bas_30.Length:" + bas_30.Length);
            Console.WriteLine("bas_30.GetString(" + bas_30.GetString + ")");

            Console.WriteLine("setvalue to 'abcde'");
            Console.WriteLine(bas_30.SetValue("abcde"));
            Console.WriteLine("bas_30.MaxLength:" + bas_30.MaxLength);            
            Console.WriteLine("bas_30.Length:" + bas_30.Length);
            Console.WriteLine("bas_30.GetString(" + bas_30.GetString + ")");

            Console.WriteLine("setvalue to '12345678901'");
            Console.WriteLine(bas_30.SetValue("12345678901"));
            Console.WriteLine("bas_30.MaxLength:" + bas_30.MaxLength);
            Console.WriteLine("bas_30.Length:" + bas_30.Length);
            Console.WriteLine("bas_30.GetString(" + bas_30.GetString + ")");            
            
            
            Console.WriteLine("done");
        }
        
    }

    ///<summary>
    /// testing...
    ///</summary>
    [TestFixture]
    public class ByteArrayAsString_test
    {
        [TestFixtureSetUp]
        public void TestFixtureSetUp()
        {
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
        public void ZeroByteString()
        {
            ByteArrayAsString bas_1 = new ByteArrayAsString(0);
            ByteArrayAsString.StringFieldError err; 
            
            err = bas_1.SetValue("a");
            Assert.AreEqual(err,ByteArrayAsString.StringFieldError.STRING_TOO_LONG);
            Assert.AreEqual(bas_1.MaxLength,0);
            Assert.AreEqual(bas_1.Length,0);
            Assert.AreEqual(bas_1.GetString,"");
        }

        [Test]
        public void OneByteString()
        {
            ByteArrayAsString bas_1 = new ByteArrayAsString(1);
            ByteArrayAsString.StringFieldError err;

            
            err = bas_1.SetValue("ab");
            Assert.AreEqual(err,ByteArrayAsString.StringFieldError.STRING_TOO_LONG);
            Assert.AreEqual(bas_1.MaxLength,1);
            Assert.AreEqual(bas_1.Length,0);
            Assert.AreEqual(bas_1.GetString,"");

            err = bas_1.SetValue("");
            Assert.AreEqual(err,ByteArrayAsString.StringFieldError.SUCCESS);
            Assert.AreEqual(bas_1.MaxLength,1);
            Assert.AreEqual(bas_1.Length,0);
            Assert.AreEqual(bas_1.GetString,"");


            err = bas_1.SetValue("a");
            Assert.AreEqual(err,ByteArrayAsString.StringFieldError.SUCCESS);
            Assert.AreEqual(bas_1.MaxLength,1);
            Assert.AreEqual(bas_1.Length,1);
            Assert.AreEqual(bas_1.GetString,"a");

            err = bas_1.SetValue("ab");
            Assert.AreEqual(err,ByteArrayAsString.StringFieldError.STRING_TOO_LONG);
            Assert.AreEqual(bas_1.MaxLength,1);
            Assert.AreEqual(bas_1.Length,1);
            Assert.AreEqual(bas_1.GetString,"a");




        }
        [Test]
        public void TenByteString()
        {
            ByteArrayAsString bas_10 = new ByteArrayAsString(10);
            ByteArrayAsString.StringFieldError err;

            err = bas_10.SetValue("12345678901");

            Assert.AreEqual(err,ByteArrayAsString.StringFieldError.STRING_TOO_LONG);
            Assert.AreEqual(bas_10.MaxLength,10);
            Assert.AreEqual(bas_10.Length,0);
            Assert.AreEqual(bas_10.GetString,"");
                                 
            err = bas_10.SetValue("");
            Assert.AreEqual(err,ByteArrayAsString.StringFieldError.SUCCESS);
            Assert.AreEqual(bas_10.MaxLength,10);
            Assert.AreEqual(bas_10.Length,0);
            Assert.AreEqual(bas_10.GetString,"");

            err = bas_10.SetValue("abcde");
            Assert.AreEqual(err,ByteArrayAsString.StringFieldError.SUCCESS);
            Assert.AreEqual(bas_10.MaxLength,10);
            Assert.AreEqual(bas_10.Length,5);
            Assert.AreEqual(bas_10.GetString,"abcde");

            err = bas_10.SetValue("abcdefghij");
            Assert.AreEqual(err,ByteArrayAsString.StringFieldError.SUCCESS);
            Assert.AreEqual(bas_10.MaxLength,10);
            Assert.AreEqual(bas_10.Length,10);
            Assert.AreEqual(bas_10.GetString,"abcdefghij");

            err = bas_10.SetValue("12345678901");
            Assert.AreEqual(err,ByteArrayAsString.StringFieldError.STRING_TOO_LONG);
            Assert.AreEqual(bas_10.MaxLength,10);
            Assert.AreEqual(bas_10.Length,10);
            Assert.AreEqual(bas_10.GetString,"abcdefghij");

        }
        [Test]
        public void ThirtyByteString()
        {
            ByteArrayAsString bas_30 = new ByteArrayAsString(30);
            ByteArrayAsString.StringFieldError err;

            err = bas_30.SetValue("1234567890123456789012345678901");
            Assert.AreEqual(err,ByteArrayAsString.StringFieldError.STRING_TOO_LONG);
            Assert.AreEqual(bas_30.MaxLength,30);
            Assert.AreEqual(bas_30.Length,0);
            Assert.AreEqual(bas_30.GetString,"");

            err = bas_30.SetValue("");
            Assert.AreEqual(err,ByteArrayAsString.StringFieldError.SUCCESS);
            Assert.AreEqual(bas_30.MaxLength,30);
            Assert.AreEqual(bas_30.Length,0);
            Assert.AreEqual(bas_30.GetString,"");

            err = bas_30.SetValue("abcde");
            Assert.AreEqual(err,ByteArrayAsString.StringFieldError.SUCCESS);
            Assert.AreEqual(bas_30.MaxLength,30);
            Assert.AreEqual(bas_30.Length,5);
            Assert.AreEqual(bas_30.GetString,"abcde");

            err = bas_30.SetValue("123456789012345678901234567890");
            Assert.AreEqual(err,ByteArrayAsString.StringFieldError.SUCCESS);
            Assert.AreEqual(bas_30.MaxLength,30);
            Assert.AreEqual(bas_30.Length,30);
            Assert.AreEqual(bas_30.GetString,"123456789012345678901234567890");

            err = bas_30.SetValue("1234567890123456789012345678901");
            Assert.AreEqual(err,ByteArrayAsString.StringFieldError.STRING_TOO_LONG);
            Assert.AreEqual(bas_30.MaxLength,30);
            Assert.AreEqual(bas_30.Length,30);
            Assert.AreEqual(bas_30.GetString,"123456789012345678901234567890");

        }
    }
}
