using System;
using System.Collections.Generic;
using System.Text;

using System.IO;

namespace IntToArbitraryCodesConverter
{

    interface INumberScanCodes
    {
        byte ZeroVal    {get;}
        byte OneVal     {get;}
        byte TwoVal     {get;}
        byte ThreeVal   {get;}
        byte FourVal    {get;}
        byte FiveVal    {get;}
        byte SixVal     {get;}
        byte SevenVal   {get;}
        byte EightVal   {get;}
        byte NineVal    {get;}
    }
    
    class TestScanCodes : INumberScanCodes
    {
        public byte ZeroVal 
        {
            get
            {
                return 0;
            }
        }
        public byte OneVal  
        {
            get
            {
                return 1;
            }
        }
        public byte TwoVal  
        {
            get
            {
                return 2;
            }
        }
        public byte ThreeVal
        {
            get
            {
                return 3;
            }
        }
        public byte FourVal 
        {
            get
            {
                return 4;
            }
        }
        public byte FiveVal 
        {
            get
            {
                return 5;
            }
        }
        public byte SixVal  
        {
            get
            {
                return 6;
            }
        }
        public byte SevenVal
        {
            get
            {
                return 7;
            }
        }
        public byte EightVal
        {
            get
            {
                return 8;
            }
        }
        public byte NineVal 
        {
            get
            {
                return 9;
            }
        }
    }

    class IntToArbitraryByteConverter
    {
        private const int           MAX_ACCEPTABLE_VALUE = 999999999;
        private const int           MAX_ACCEPTABLE_PLACES = 9;
        private INumberScanCodes    m_nsc = null;
        
        public IntToArbitraryByteConverter(INumberScanCodes p_nsc)
        {
            m_nsc = p_nsc;
        }
        
        public void ConvertToAry(List<byte>  convertedVal,
                                 int         NumToConvert)
        {
            if(NumToConvert > MAX_ACCEPTABLE_VALUE)
            {
                throw new ValueTooLargeToConvert();
            }
            
            convertedVal.Clear();
            
            if(NumToConvert == 0)
            {
                convertedVal.Insert(0,m_nsc.ZeroVal);
            }
            else
            {
                while(NumToConvert > 0)
                {
                    int currPlace = NumToConvert % 10;
                    switch(currPlace)
                    {
                        case 0:
                            convertedVal.Insert(0,m_nsc.ZeroVal);
                            break;
                        case 1:
                            convertedVal.Insert(0,m_nsc.OneVal);
                            break;
                        case 2:
                            convertedVal.Insert(0,m_nsc.TwoVal);
                            break;
                        case 3:
                            convertedVal.Insert(0,m_nsc.ThreeVal);
                            break;
                        case 4:
                            convertedVal.Insert(0,m_nsc.FourVal);
                            break;
                        case 5:
                            convertedVal.Insert(0,m_nsc.FiveVal);
                            break;
                        case 6:
                            convertedVal.Insert(0,m_nsc.SixVal);
                            break;
                        case 7:
                            convertedVal.Insert(0,m_nsc.SevenVal);
                            break;
                        case 8:
                            convertedVal.Insert(0,m_nsc.EightVal);
                            break;
                        case 9:
                            convertedVal.Insert(0,m_nsc.NineVal);
                            break;
                    }
                    NumToConvert /= 10;
                }
            }
        }
        public void ConvertFromAry(List<byte>  ValToConvert,
                                   ref int     ConvertedVal)
        {
            // make sure that our array is only 'max size' long.
            if(ValToConvert.Count > MAX_ACCEPTABLE_PLACES)
            {
                throw new ValueTooLargeToConvert();
            }
            // make sure that our array has only valid characters
            foreach(byte scancode in ValToConvert)
            {   
                bool foundScanCode = 
                        (scancode == m_nsc.ZeroVal)
                     || (scancode == m_nsc.OneVal)
                     || (scancode == m_nsc.TwoVal)
                     || (scancode == m_nsc.ThreeVal)
                     || (scancode == m_nsc.FourVal)
                     || (scancode == m_nsc.FiveVal)
                     || (scancode == m_nsc.SixVal)
                     || (scancode == m_nsc.SevenVal)
                     || (scancode == m_nsc.EightVal)
                     || (scancode == m_nsc.NineVal);
                    
                if(! foundScanCode)
                {
                    throw new InvalidScanCodeException();
                }
            }
            // we are valid on input.. let the games begin!
            
            ConvertedVal = 0;
            
            for(int currVal = 0;
                currVal < ValToConvert.Count;
                currVal++)
            {
                ConvertedVal *= 10;
                if(ValToConvert[currVal] == m_nsc.ZeroVal)
                {
                    ConvertedVal += 0;
                }
                else if(ValToConvert[currVal] == m_nsc.OneVal)
                {
                    ConvertedVal += 1;
                }
                else if(ValToConvert[currVal] == m_nsc.TwoVal)
                {
                    ConvertedVal += 2;
                }
                else if(ValToConvert[currVal] == m_nsc.ThreeVal)
                {
                    ConvertedVal += 3;
                }
                else if(ValToConvert[currVal] == m_nsc.FourVal)
                {
                    ConvertedVal += 4;
                }
                else if(ValToConvert[currVal] == m_nsc.FiveVal)
                {
                    ConvertedVal += 5;
                }
                else if(ValToConvert[currVal] == m_nsc.SixVal)
                {
                    ConvertedVal += 6;
                }
                else if(ValToConvert[currVal] == m_nsc.SevenVal)
                {
                    ConvertedVal += 7;
                }
                else if(ValToConvert[currVal] == m_nsc.EightVal)
                {
                    ConvertedVal += 8;
                }
                else if(ValToConvert[currVal] == m_nsc.NineVal)
                {
                    ConvertedVal += 9;
                }
            }
            
        }
        
    }    
    class ValueTooLargeToConvert : System.ApplicationException
    {
    }
    
    class InvalidScanCodeException : System.ApplicationException
    {
    }
    
    class Program
    {
        static List<byte> m_converted  = new List<byte>();
        
        static void Main(string[] args)
        {
            StreamWriter fs = new StreamWriter("converterOutputValues.txt");
            IntToArbitraryByteConverter cnvrtr = new IntToArbitraryByteConverter(new TestScanCodes());
            int secondConvertVal = 0;
            for(int currVal = 0;
                currVal < 10000;
                currVal++)
            {
                try
                {
                    cnvrtr.ConvertToAry(m_converted,currVal);
                    // convert it back..
                    cnvrtr.ConvertFromAry(m_converted,ref secondConvertVal);
                }
                catch(ValueTooLargeToConvert)
                {
                    fs.Write("val too large to convert error");
                }
                printConverted(fs,currVal,secondConvertVal);
            }
            fs.Close();
            
            byte [] tstVal = {1,0,2,3,4,5,6,7,9};
            List<byte> tstValLst = new List<byte>(tstVal);

            int convertedVal = 99;
            cnvrtr.ConvertFromAry(tstValLst,ref convertedVal);
            Console.WriteLine(convertedVal);
        }
        static void printConverted(StreamWriter fs, int currVal,int secondConvertVal)
        {
            foreach(int val in m_converted)
            {   
                fs.Write(String.Format("{0}",val));
            }
            fs.Write(String.Format(",{0},{1}",currVal,secondConvertVal));
            fs.WriteLine();
        }
    }
}
