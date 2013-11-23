using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Globalization;


namespace DirReadTest
{
        public class CrystalisFile
    {
        private const string    MANIFEST_TXT            = "MANIFEST.TXT";
        private const string    REGISTRY_BIN            = "REGISTRY.BIN";
        private const string    EXTENSION_BIN           = ".BIN";
        private const char      DEVICENAME_PREFIX       = 'D';
        private const char      TEMPDEVICENAME_PREFIX   = 'T';
        private const char      MACRO_PREFIX            = 'M';
        private const string    HEAPNAME                = "HEAP";
        ///<summary>
        /// length of device file name minus the extension 
        ///</summary>
        private const int       DEVNAME_LEN             = 3;
        private const int       HEAPORMACRO_LEN         = 4;
        private const int       DEVNUM_OFFSET           = 1;
        private const int       HEAPORMACRO_OFFSET      = 3;
        private const int       MACRONUM_OFFSET         = 4;
        ///<summary>
        /// length of macro or heap file name minus the extension 
        ///</summary>
        private const int       MACRO_OR_HEAP_NAME_LEN  = 7;


        private enum CrystalisFileType
        {
            DEVICE,
            MACRO,
            HEAP,
            REGISTRY,
            MANIFEST,
            UNKNOWN
        }

        private bool                m_isTemp;

        private FileInfo            m_finfo;

        private CrystalisFileType   m_ftype;
        private int                 m_DeviceNumber;
        private int                 m_MacroNumber;

        public FileInfo fInfo
        {
            get
            {
                return m_finfo;
            }
        }

        public CrystalisFile(FileInfo finfo)
        {
            m_finfo         = finfo;
            m_ftype         = CrystalisFileType.UNKNOWN;
            m_DeviceNumber  = 0;


            string UpperCaseName = m_finfo.Name.ToUpper();

            // easy stuff first..
            if (UpperCaseName == MANIFEST_TXT)
            {
                m_ftype = CrystalisFileType.MANIFEST;
            }
            else if(UpperCaseName == REGISTRY_BIN)
            {
                m_ftype = CrystalisFileType.REGISTRY;
            }
            else
            {
                // either invalid, or device oriented..
                if (Path.GetExtension(UpperCaseName) == EXTENSION_BIN)
                {
                    // ok.. valid extension.. so now get the non-extended name before deciphering further.
                    int non_extended_name_len = UpperCaseName.Length - EXTENSION_BIN.Length;
                    // now.. this length must be three or seven characters.. all others are invalid..
                    if(non_extended_name_len == DEVNAME_LEN)
                    {
                        // device file..
                        string deviceFileName       = UpperCaseName.Substring(0,non_extended_name_len);
                        string deviceFileNumberStr  = UpperCaseName.Substring(1,(non_extended_name_len-1));

                        m_isTemp = (deviceFileName[0] == TEMPDEVICENAME_PREFIX);

                        if (ParseIntoNumber(deviceFileNumberStr, ref m_DeviceNumber))
                        {
                            if(     deviceFileName[0] == DEVICENAME_PREFIX
                                ||  deviceFileName[0] == TEMPDEVICENAME_PREFIX  )
                            {
                                m_ftype = CrystalisFileType.DEVICE;
                            }
                            else
                            {
                                m_ftype = CrystalisFileType.UNKNOWN;
                            }
                        }
                        else
                        {
                            m_ftype = CrystalisFileType.UNKNOWN;
                        }
                    }
                    else if(non_extended_name_len == MACRO_OR_HEAP_NAME_LEN  )
                    {
                        // D??HEAP.BIN
                        // D??M???.BIN
                        // T??HEAP.BIN
                        // T??M???.BIN
                        // 
                        // macro or heap file.
                        string heapOrMacroFileName  = UpperCaseName.Substring(0,non_extended_name_len);
                        // device file..
                        string deviceFileName       = UpperCaseName.Substring(0,DEVNAME_LEN);
                        string deviceFileNumberStr  = UpperCaseName.Substring(DEVNUM_OFFSET,(DEVNAME_LEN-1));
                        string macroOrHeapStr       = UpperCaseName.Substring(HEAPORMACRO_OFFSET,(HEAPORMACRO_LEN));
                        string macroNumberStr       = UpperCaseName.Substring(MACRONUM_OFFSET,(HEAPORMACRO_LEN-1));

                        m_isTemp = (deviceFileName[0] == TEMPDEVICENAME_PREFIX);

                        if (    ParseIntoNumber(deviceFileNumberStr, ref m_DeviceNumber)
                            &&  (   deviceFileName[0] == DEVICENAME_PREFIX
                                 || deviceFileName[0] == TEMPDEVICENAME_PREFIX              )   )
                        {
                            if (macroOrHeapStr[0] == MACRO_PREFIX)
                            {
                                if(ParseIntoNumber(macroNumberStr, ref m_MacroNumber))
                                {
                                    m_ftype = CrystalisFileType.MACRO;
                                }
                                else
                                {
                                    m_ftype = CrystalisFileType.UNKNOWN;
                                }

                            }
                            else if(macroOrHeapStr == HEAPNAME)
                            {
                                m_ftype = CrystalisFileType.HEAP;
                            }
                            else
                            {
                                m_ftype = CrystalisFileType.UNKNOWN;
                            }
                        }
                        else
                        {
                            m_ftype = CrystalisFileType.UNKNOWN;
                        }
                    }
                    else
                    {
                        m_ftype = CrystalisFileType.UNKNOWN;
                    }
                }

            }
        }

        ///<summary>
        /// parse a device or macro number.  True if things went ok, false otherwise.
        ///</summary>
        ///<returns>
        ///<param name="devNumStr">
        /// a hexadecimal number in string form
        ///</param>
        ///<param name="convertedNumber">
        /// set to value of string, or 0 if bad convert.
        ///</param>
        /// false if bad number, true if good number and devnumber is set.. 
        ///</returns>
        private bool ParseIntoNumber(string devNumStr, ref int convertedNumber)
        {
            bool ret = false;
            try
            {
                convertedNumber = Int32.Parse(devNumStr,NumberStyles.AllowHexSpecifier); 
                ret = true;
            }
            catch(System.FormatException ex)
            {   
                //bad name..
                convertedNumber = 0;
                ret = false;
            }
            return ret;
        }

        ///<summary>
        /// true if this is a file representing a device, false otherwise. 
        ///</summary>
        public bool isDevice 
        {
            get
            {
                return m_ftype == CrystalisFileType.DEVICE;
            }
        }
        ///<summary>
        /// true if this is a file representing a macro, false otherwise. 
        ///</summary>
        public bool isMacro
        {
            get
            {
                return m_ftype == CrystalisFileType.MACRO;
            }
        }
        ///<summary>
        /// true if this is a file representing a heap, false otherwise. 
        ///</summary>
        public bool isHeap
        {
            get
            {
                return m_ftype == CrystalisFileType.HEAP;
            }
        }
        ///<summary>
        /// device number for this file.
        ///</summary>
        ///<returns>
        /// device number, or -1 if this isn't a device related file. 
        ///</returns>
        public int DeviceNumber
        {
            get
            {
                return m_DeviceNumber;
            }
        }
        ///<summary>
        /// macro number for this file.  Only valid if 'isMacro' is true.  
        /// returns -1 in all other instances.
        ///</summary>
        ///<returns>
        /// macronumber, or -1 if not a macro. 
        ///</returns>
        public int MacroNumber
        {
            get
            {
                return m_MacroNumber;
            }
        }
        ///<summary>
        /// true if this is a temporary file, false otherwise. 
        ///</summary>
        public bool isTemp
        {
            get
            {
                return m_isTemp;
            }
        }
        ///<summary>
        /// true if this is the registry file, false otherwise. 
        ///</summary>
        public bool isRegistry
        {
            get
            {
                return m_ftype == CrystalisFileType.REGISTRY;
            }
        }

        ///<summary>
        ///  true if this file is a valid crystalis file, false if not
        ///</summary>
        public bool ValidCrystalisFile
        {
            get
            {
                return m_ftype != CrystalisFileType.UNKNOWN;
            }
        }
    }



    class Program
    {
        static void Main(string[] args)
        {
            string masterTestDir = @"C:\testing\NameTests";

            Console.WriteLine("PullMasterTestDir");
            if(Directory.Exists(masterTestDir))
            {
                Console.WriteLine("it exists..");
                string[] fileInMasterDir = Directory.GetFiles(masterTestDir,"*.*");
                List<CrystalisFile> cryFiles = new List<CrystalisFile>();
                foreach(string fileName in fileInMasterDir)
                {
                    Console.WriteLine("fileName:" + fileName);
                    cryFiles.Add(new CrystalisFile(new FileInfo(fileName)));
                }
                foreach(CrystalisFile cfile in cryFiles)
                {
                    Console.WriteLine(cfile.fInfo.Name + ":");
                    Console.Write("    ");
                    Console.WriteLine("valid:" + cfile.ValidCrystalisFile);
                    if (cfile.ValidCrystalisFile)
                    {
                        Console.Write("    ");
                        Console.Write("isDevice:" + cfile.isDevice);
                        Console.Write("  isMacro:" + cfile.isMacro);
                        Console.Write("  isHeap:" + cfile.isHeap);
                        Console.Write("  isTemp:" + cfile.isTemp);
                        Console.Write("  DeviceNumber:" + cfile.DeviceNumber);
                        Console.Write("  MacroNumber:" + cfile.MacroNumber);
                    }
                }

            }
            else
            {
//                Assert.IsTrue(false,"Oops.. master directory not on this system..");
            }
        }
    }
}
