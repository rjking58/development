using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.IO;

namespace CsharpToCSharpMarshal
{
    public class MonitoredItemConverter
    {
        private System.Text.Encoding enc = System.Text.Encoding.ASCII;


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


        private void ConvertItemIdentityToBytes(ref ItemIdentity p_itemIdentity, BinaryWriter bw)
        {
            //      [ushort typeField]
            bw.Write(p_itemIdentity.Type);
            //      [ushort referenceTypeField]
            bw.Write(p_itemIdentity.ReferenceType);
            //      <<embedded ary>>
            //          [unsigned int namefield_length]
            //          [bytes nameField_strdata 0..n]
            if (p_itemIdentity.Name != null)
            {
                byte[] tmpArray = enc.GetBytes(p_itemIdentity.Name);
                bw.Write((uint)tmpArray.Length);
                bw.Write(tmpArray);
            }
            else
            {
                bw.Write((uint)0);
            }
            //      <<embedded ary>>
            //          [unsigned int contextNameField_length]
            //          [bytes contextNameField_strdata 0..n]
            if (p_itemIdentity.ContextName != null)
            {
                byte[] tmpArray = enc.GetBytes(p_itemIdentity.ContextName);
                bw.Write((uint)tmpArray.Length);
                bw.Write(tmpArray);
            }
            else
            {
                bw.Write((uint)0);
            }
            //      [ulong idField]
            bw.Write(p_itemIdentity.Id);
            //      [bool idFieldSpecified]
            bw.Write(p_itemIdentity.IdSpecified);

        }
        private void ConvertRuntimeValueToBytes(ref RuntimeValue p_runtimeValue, BinaryWriter bw)
        {
            //      [DateTime timestampField] (converted to 64 bit binary)
            bw.Write(p_runtimeValue.timestampField.ToBinary());
            //      [bool timestampFieldSpecified]
            bw.Write(p_runtimeValue.timestampFieldSpecified);
            //      <<Variant>>
            //          [ushort typeField]
            //          [int lengthField]
            //          <embedded ary>
            //              [unsigned int payloadField_length]
            //              [bytes payloadField_bytes 0..n]
            ConvertVariantToBytes(ref p_runtimeValue.valueField, bw);
            //
            //      <<ASBStatus>>
            //          [sbyte countField]
            bw.Write(p_runtimeValue.statusField.countField);
            //          <<embedded ary>>
            //              [unsigned int payloadfield_length]
            //              [bytes payloadField_bytes 0..n]
            if (p_runtimeValue.statusField.payloadField != null)
            {
                bw.Write((uint)p_runtimeValue.statusField.payloadField.Length);
                bw.Write(p_runtimeValue.statusField.payloadField);
            }
            else
            {
                bw.Write((uint)0);
            }


        }
        private void ConvertVariantToBytes(ref Variant p_variant, BinaryWriter bw)
        {
            //      [ushort typeField]
            bw.Write(p_variant.typeField);
            //      [int lengthField]
            bw.Write(p_variant.lengthField);
            //      <<embedded ary>>
            //          [unsigned int payloadField_length]
            //          [bytes payloadField_bytes 0..n]
            if (p_variant.payloadField != null)
            {
                bw.Write((uint)p_variant.payloadField.Length);
                bw.Write(p_variant.payloadField);
            }
            else
            {
                bw.Write((uint)0);
            }

        }


        private void ConvertBytesToItemIdentity(ref ItemIdentity Item, BinaryReader br)
        {
            //      [ushort typeField]
            Item.Type = br.ReadUInt16();
            //      [ushort referenceTypeField]
            Item.ReferenceType = br.ReadUInt16();
            //      <<embedded ary>>
            //          [unsigned int namefield_length]
            //          [bytes nameField_strdata 0..n]
            int strLen = br.ReadInt32();
            if (strLen > 0)
            {
                byte[] tmpBytes = br.ReadBytes(strLen);
                Item.Name = enc.GetString(tmpBytes);
            }
            else
            {
                Item.Name = "";
            }
            //      <<embedded ary>>
            //          [unsigned int contextNameField_length]
            //          [bytes contextNameField_strdata 0..n]
            strLen = br.ReadInt32();
            if (strLen > 0)
            {
                byte[] tmpBytes = br.ReadBytes(strLen);
                Item.ContextName = enc.GetString(tmpBytes);
            }
            else
            {
                Item.ContextName = "";
            }
            //      [ulong idField]
            Item.Id = br.ReadUInt64();
            //      [bool idFieldSpecified]
            Item.IdSpecified = br.ReadBoolean();

        }
        private void ConvertBytesToRuntimeValue(ref RuntimeValue RValue, BinaryReader br)
        {
            //      [DateTime timestampField] (converted to 64 bit binary)
            RValue.timestampField = DateTime.FromBinary(br.ReadInt64());

            //      [bool timestampFieldSpecified]
            RValue.timestampFieldSpecified = br.ReadBoolean();

            //      <<Variant>>
            //          [ushort typeField]
            //          [int lengthField]
            //          <embedded ary>
            //              [unsigned int payloadField_length]
            //              [bytes payloadField_bytes 0..n]
            ConvertBytesToVariant(ref RValue.valueField, br);

            //
            //      <<ASBStatus>>
            //          [sbyte countField]
            RValue.statusField.countField = br.ReadSByte();
            //          <<embedded ary>>
            //              [unsigned int payloadfield_length]
            //              [bytes payloadField_bytes 0..n]
            int payloadLen = br.ReadInt32();
            if (payloadLen > 0)
            {
                RValue.statusField.Payload = br.ReadBytes(payloadLen);
            }
            else
            {
                RValue.statusField.Payload = null;
            }
        }

        private void ConvertBytesToVariant(ref Variant variant, BinaryReader br)
        {
            //      [ushort typeField]
            variant.typeField = br.ReadUInt16();
            //      [int lengthField]
            variant.lengthField = br.ReadInt32();
            //      <<embedded ary>>
            //          [unsigned int payloadField_length]
            //          [bytes payloadField_bytes 0..n]
            int payloadLen = br.ReadInt32();
            if (payloadLen > 0)
            {
                variant.Payload = br.ReadBytes(payloadLen);
            }
            else
            {
                variant.Payload = null;
            }
        }

        public byte[] ConvertMIVToBytes(MonitoredItemValue[] mivs)
        {
            System.IO.MemoryStream ms = new System.IO.MemoryStream();
            System.IO.BinaryWriter bw = new System.IO.BinaryWriter(ms);

            byte[] retval = null;

            if (mivs != null)
            {
                if (mivs.Length > 0)
                {
                    //try
                    //{
                    //  [unsigned int number_of_elements ]
                    bw.Write((uint)mivs.Length);
                    uint mivsLen = (uint)mivs.Length;
                    for (uint currOfst = 0;
                         currOfst < mivsLen;
                         currOfst++)
                    {

                        ConvertItemIdentityToBytes(ref mivs[currOfst].itemField, bw);
                        ConvertRuntimeValueToBytes(ref mivs[currOfst].valueField, bw);
                        ConvertVariantToBytes(ref mivs[currOfst].userDataField, bw);
                    }
                    retval = ms.ToArray();
                    //}
                    //catch (Exception e)
                    //{
                    //    // TODO RJK use real logging here..
                    //    Console.WriteLine("{0}", e.StackTrace);
                    //}
                }
            }
            return retval;
        }

        public void ConvertBytesToMIV(byte[] theBuffer, out MonitoredItemValue[] theMivs)
        {
            theMivs = null;

            if (theBuffer != null)
            {
                MemoryStream ms = new MemoryStream(theBuffer);
                BinaryReader br = new BinaryReader(ms);
                // count of MIVs.
                //  [unsigned int number_of_elements ]
                uint mivCnt = br.ReadUInt32();
                theMivs = new MonitoredItemValue[mivCnt];

                //try
                //{
                for (uint currMiv = 0;
                    currMiv < mivCnt;
                    currMiv++)
                {
                    //  <<ItemIdentity>>
                    ConvertBytesToItemIdentity(ref (theMivs[currMiv].itemField), br);
                    //  <<RuntimeValue>>
                    ConvertBytesToRuntimeValue(ref theMivs[currMiv].valueField, br);
                    //  <<Variant>>
                    ConvertBytesToVariant(ref theMivs[currMiv].userDataField, br);

                }
                //}
                //catch (Exception e)
                //{
                //    // TODO RJK use real logging here..
                //    Console.WriteLine("{0}", e.StackTrace);
                //}
            }
        }


        
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
        // 
        //  <<simple variables>>
        //  
        //      [ushort errorCodeField]
        //      [bool errorCodeFieldSpecified]

        public byte[] ConvertItemStatusToBytes(ItemStatus[] theStatuses)
        {
            System.IO.MemoryStream ms = new System.IO.MemoryStream();
            System.IO.BinaryWriter bw = new System.IO.BinaryWriter(ms);
            byte[] retval = null;

            if (theStatuses != null)
            {
                if (theStatuses.Length > 0)
                {
                    //try
                    //{ 

                    //  [unsigned int number_of_elements ]
                    bw.Write((uint)theStatuses.Length);
                    uint statusesLen = (uint)theStatuses.Length;

                    for (uint currOfst = 0;
                         currOfst < statusesLen;
                         currOfst++)
                    {
                        //  <<ItemIdentity>>
                        ConvertItemIdentityToBytes(ref theStatuses[currOfst].itemField, bw);

                        //      [ushort errorCodeField]
                        bw.Write(theStatuses[currOfst].errorCodeField);
                        //      [bool errorCodeFieldSpecified]
                        bw.Write(theStatuses[currOfst].errorCodeFieldSpecified);
                    }
                    retval = ms.ToArray();

                    //}
                    //catch (Exception e)
                    //{
                    //    // TODO RJK use real logging here..
                    //    Console.WriteLine("{0}", e.StackTrace);
                    //}
                }
            }
            return retval;

        }

        public void ConvertBytesToItemStatus(byte[] theBuffer, out ItemStatus[] theStatuses)
        {
            theStatuses = null;

            if (theBuffer != null)
            {
                //try
                //{ 
                MemoryStream ms = new MemoryStream(theBuffer);
                BinaryReader br = new BinaryReader(ms);
                // count of MIVs.
                //  [unsigned int number_of_elements ]
                uint statusCnt = br.ReadUInt32();
                theStatuses = new ItemStatus[statusCnt];

                for (uint currStatus = 0;
                    currStatus < statusCnt;
                    currStatus++)
                {
                    //  <<ItemIdentity>>
                    ConvertBytesToItemIdentity(ref (theStatuses[currStatus].itemField), br);
                    //      [ushort errorCodeField]
                    theStatuses[currStatus].errorCodeField = br.ReadUInt16();
                    //      [bool errorCodeFieldSpecified]
                    theStatuses[currStatus].errorCodeFieldSpecified = br.ReadBoolean();

                }
                //}
                //catch (Exception e)
                //{
                //    // TODO RJK use real logging here..
                //    Console.WriteLine("{0}", e.StackTrace);
                //}
            }
        }
    }

}
