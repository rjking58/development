using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.IO;

namespace CsharpToCSharpMarshal
{

    // structures in use in MonitoredItemValue..
    // //////////////////////////////////////////////////////////////////////////////////
    // ItemIdentity..
    // //////////////////////////////////////////////////////////////////////////////////
    public partial struct ItemStatus
    {

        public ItemIdentity itemField;

        public ushort errorCodeField;

        public bool errorCodeFieldSpecified;

        /// <remarks/>
        public ItemIdentity Item
        {
            get
            {
                return this.itemField;
            }
            set
            {
                this.itemField = value;
            }
        }

        /// <remarks/>
        public ushort ErrorCode
        {
            get
            {
                return this.errorCodeField;
            }
            set
            {
                this.errorCodeField = value;
                this.ErrorCodeSpecified = true;
            }
        }

        /// <remarks/>
        [System.Xml.Serialization.XmlIgnoreAttribute()]
        public bool ErrorCodeSpecified
        {
            get
            {
                return this.errorCodeFieldSpecified;
            }
            set
            {
                this.errorCodeFieldSpecified = value;
            }
        }
    }


    public partial struct ItemIdentity
    {

        private ushort typeField;
        private ushort referenceTypeField;
        private string nameField;
        private string contextNameField;
        private ulong idField;
        private bool idFieldSpecified;

        /// <remarks/>
        public ushort Type
        {
            get
            {
                return this.typeField;
            }
            set
            {
                this.typeField = value;
            }
        }

        /// <remarks/>
        public ushort ReferenceType
        {
            get
            {
                return this.referenceTypeField;
            }
            set
            {
                this.referenceTypeField = value;
            }
        }

        /// <remarks/>
        [System.Xml.Serialization.XmlElementAttribute(IsNullable = true)]
        public string Name
        {
            get
            {
                return this.nameField;
            }
            set
            {
                this.nameField = value;
            }
        }

        /// <remarks/>
        [System.Xml.Serialization.XmlElementAttribute(IsNullable = true)]
        public string ContextName
        {
            get
            {
                return this.contextNameField;
            }
            set
            {
                this.contextNameField = value;
            }
        }

        /// <remarks/>
        public ulong Id
        {
            get
            {
                return this.idField;
            }
            set
            {
                this.idField = value;
                this.IdSpecified = true;
            }
        }

        /// <remarks/>
        [System.Xml.Serialization.XmlIgnoreAttribute()]
        public bool IdSpecified
        {
            get
            {
                return this.idFieldSpecified;
            }
            set
            {
                this.idFieldSpecified = value;
            }
        }
    }

    // //////////////////////////////////////////////////////////////////////////////////
    // ASBStatus..
    // //////////////////////////////////////////////////////////////////////////////////
    public partial struct ASBStatus
    {

        public sbyte countField;

        public byte[] payloadField;

        /// <remarks/>
        public sbyte Count
        {
            get
            {
                return this.countField;
            }
            set
            {
                this.countField = value;
            }
        }

        /// <remarks/>
        [System.Xml.Serialization.XmlElementAttribute(DataType = "base64Binary")]
        public byte[] Payload
        {
            get
            {
                return this.payloadField;
            }
            set
            {
                this.payloadField = value;
            }
        }
    }

    // //////////////////////////////////////////////////////////////////////////////////
    // RuntimeValue..
    // //////////////////////////////////////////////////////////////////////////////////
    public partial struct RuntimeValue
    {

        public System.DateTime timestampField;
        public bool timestampFieldSpecified;
        public Variant valueField;
        public ASBStatus statusField;

        /// <remarks/>
        public System.DateTime Timestamp
        {
            get
            {
                return this.timestampField;
            }
            set
            {
                this.timestampField = value;
                this.TimestampSpecified = true;
            }
        }

        /// <remarks/>
        [System.Xml.Serialization.XmlIgnoreAttribute()]
        public bool TimestampSpecified
        {
            get
            {
                return this.timestampFieldSpecified;
            }
            set
            {
                this.timestampFieldSpecified = value;
            }
        }

        /// <remarks/>
        public Variant Value
        {
            get
            {
                return this.valueField;
            }
            set
            {
                this.valueField = value;
            }
        }

        /// <remarks/>
        public ASBStatus Status
        {
            get
            {
                return this.statusField;
            }
            set
            {
                this.statusField = value;
            }
        }
    }
    // //////////////////////////////////////////////////////////////////////////////////
    // Variant..
    // //////////////////////////////////////////////////////////////////////////////////

    public partial struct Variant
    {

        public ushort typeField;
        public int lengthField;
        public byte[] payloadField;

        /// <remarks/>
        public ushort Type
        {
            get
            {
                return this.typeField;
            }
            set
            {
                this.typeField = value;
            }
        }

        /// <remarks/>
        public int Length
        {
            get
            {
                return this.lengthField;
            }
            set
            {
                this.lengthField = value;
            }
        }

        /// <remarks/>
        [System.Xml.Serialization.XmlElementAttribute(DataType = "base64Binary", IsNullable = true)]
        public byte[] Payload
        {
            get
            {
                return this.payloadField;
            }
            set
            {
                this.payloadField = value;
            }
        }
    }
    // //////////////////////////////////////////////////////////////////////////////////
    // MonitoredItemValue..
    //      ItemIdentity
    //          string (2)
    //      RuntimeValue
    //          ASBStatus
    //              byte []
    //          Variant
    //              byte []
    //      Variant
    //          byte []
    // //////////////////////////////////////////////////////////////////////////////////

    public struct MonitoredItemValue
    {

        public ItemIdentity itemField;

        public RuntimeValue valueField;

        public Variant userDataField;

        /// <remarks/>
        public ItemIdentity Item
        {
            get
            {
                return this.itemField;
            }
            set
            {
                this.itemField = value;
            }
        }

        /// <remarks/>
        public RuntimeValue Value
        {
            get
            {
                return this.valueField;
            }
            set
            {
                this.valueField = value;
            }
        }

        /// <remarks/>
        public Variant UserData
        {
            get
            {
                return this.userDataField;
            }
            set
            {
                this.userDataField = value;
            }
        }
    }


    class Program
    {

        static void Main(string[] args)
        {
            // legend:
            //  [something physical to be stored in buffer]  (something to be translated to/from the byte array)
            //  <<description of item>> (no physical storaged.. just to make reading the structure easier!)
            // 
            // overall layout of byte buffer:
            //
            //  [unsigned int number_of_elements ]
            //  [element]
            //  [element]
            //  ...
            //
            // element = 
            //  <<ItemIdentity>>
            //      [ushort typeField]
            //      [ushort referenceTypeField]
            //      <<embedded ary>>
            //          [unsigned int namefield_length]
            //          [bytes nameField_strdata 0..n]
            //      <<embedded ary>>
            //          [unsigned int contextNameField_length]
            //          [bytes contextNameField_strdata 0..n]
            //      [ulong idField]
            //      [bool idFieldSpecified]
            //  <<RuntimeValue>>
            //      [DateTime timestampField] (??)
            //      [bool timestampFieldSpecified]
            //      <<Variant>>
            //          [ushort typeField]
            //          [int lengthField]
            //          <embedded ary>
            //              [unsigned int payloadField_length]
            //              [bytes payloadField_bytes 0..n]
            //
            //      <<ASBStatus>>
            //          [sbyte countField]
            //          <<embedded ary>>
            //              [unsigned int payloadfield_length]
            //              [bytes payloadField_bytes 0..n]
            //
            //  <<Variant>>
            //      [ushort typeField]
            //      [int lengthField]
            //      <<embedded ary>>
            //          [unsigned int payloadField_length]
            //          [bytes payloadField_bytes 0..n]

            // hand marshal the structures..
            MemoryStream ms = new MemoryStream();
            BinaryWriter bw = new BinaryWriter(ms);

            MonitoredItemValue [] mivs = new MonitoredItemValue[3];
            for (   uint currOfst = 0; 
                    currOfst < 3; 
                    currOfst++)
            {
                mivs[currOfst].itemField.Type = (ushort) (currOfst + 1);
                mivs[currOfst].itemField.ReferenceType = (ushort)(currOfst + 2);
                mivs[currOfst].itemField.Name = String.Format("testing name string #{0}",currOfst + 3);
                mivs[currOfst].itemField.ContextName = String.Format("testing contextname string #{0}", currOfst + 4);
                mivs[currOfst].itemField.Id = (ulong)(currOfst + 5);
                mivs[currOfst].itemField.IdSpecified = false;

                mivs[currOfst].valueField.timestampField = DateTime.Now;
                mivs[currOfst].valueField.timestampFieldSpecified = true;
                mivs[currOfst].valueField.valueField.typeField = (ushort) (currOfst + 6);
                mivs[currOfst].valueField.valueField.lengthField = (int) (currOfst + 7);
                byte [] tmpBytes = new byte[currOfst+2];
                for(int aryOfst = 0; aryOfst < tmpBytes.Length; aryOfst++)
                {
                    tmpBytes[aryOfst] = (byte) (aryOfst + currOfst);
                }
                mivs[currOfst].valueField.valueField.payloadField = tmpBytes;
                mivs[currOfst].valueField.statusField.countField = (sbyte) (currOfst + 8);
                mivs[currOfst].valueField.statusField.payloadField = tmpBytes;
                mivs[currOfst].userDataField.typeField =  (ushort) (currOfst + 9);
                mivs[currOfst].userDataField.lengthField = (int) (currOfst + 10);
                mivs[currOfst].userDataField.payloadField = tmpBytes;
            }
            MonitoredItemConverter cnvrtr = new MonitoredItemConverter();

            byte [] buf = cnvrtr.ConvertMIVToBytes(mivs);

            MonitoredItemValue[] mivs2;

            // this makes a copy.. which is probably ok given what we are doing..
            // GetBuffer is more efficient here.. but returns more than what we 
            // need to transfer (its highly likely to have unused slop-over bytes at the 
            // end of the buffer), which is highly wasteful of network resources, which
            // is the efficiency we are tracking here..
            DumpString(buf);

            cnvrtr.ConvertBytesToMIV(buf, out mivs2);


        }

        static void DumpString(byte [] buf)
        {
            int ofst = 0;
            StringBuilder bytePart = new StringBuilder();
            StringBuilder asciiPart = new StringBuilder();
            foreach (byte b in buf)
            {
                bytePart.Append(String.Format("{0:X2} ", b));

                if(     Char.IsLetterOrDigit((char) b) 
                    ||  Char.IsSeparator((char) b)
                    ||  Char.IsWhiteSpace((char) b) )
                {
                    asciiPart.Append(String.Format("{0}  ",(char)b));
                }
                else
                {
                    asciiPart.Append(String.Format("   ", (char)b));
                }
                ofst++;

                if (ofst >= 16)
                {
                    Console.WriteLine(bytePart.ToString());
                    Console.WriteLine(asciiPart.ToString());
                    bytePart.Clear();
                    asciiPart.Clear();

                    Console.WriteLine();
                    ofst = 0;
                }
            }
        }
    }
}
