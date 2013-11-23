using System;
using System.Text;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;

using System.IO;
using CsharpToCSharpMarshal;

namespace CSharpToCSharpMarshalUTs
{
    [TestClass]
    public class CSharpToCSharpMarshalUTs
    {

        void DumpString(byte[] buf)
        {
            int ofst = 0;
            StringBuilder bytePart = new StringBuilder();
            StringBuilder asciiPart = new StringBuilder();
            foreach (byte b in buf)
            {
                bytePart.Append(String.Format("{0:X2} ", b));

                if (Char.IsLetterOrDigit((char)b)
                    || Char.IsSeparator((char)b)
                    || Char.IsWhiteSpace((char)b))
                {
                    asciiPart.Append(String.Format("{0}  ", (char)b));
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

        [TestMethod]
        public void SimpleEndToEnd()
        {
            // this has been supercede by the bulk test.. but is left here 
            // for completeness..  it does NOT have the ItemStatus portion 
            // in it because the Bulk test takes that into account.
            int countToTest = 100;
            MonitoredItemValue[] mivs = new MonitoredItemValue[countToTest];
            for (uint currOfst = 0;
                    currOfst < countToTest;
                    currOfst++)
            {
                mivs[currOfst].itemField.Type = (ushort)(currOfst + 1);
                mivs[currOfst].itemField.ReferenceType = (ushort)(currOfst + 2);
                mivs[currOfst].itemField.Name = String.Format("testing name string #{0}", currOfst + 3);
                mivs[currOfst].itemField.ContextName = String.Format("testing contextname string #{0}", currOfst + 4);
                mivs[currOfst].itemField.Id = (ulong)(currOfst + 5);
                mivs[currOfst].itemField.IdSpecified = false;

                mivs[currOfst].valueField.timestampField = DateTime.Now;
                mivs[currOfst].valueField.timestampFieldSpecified = true;
                mivs[currOfst].valueField.valueField.typeField = (ushort)(currOfst + 6);
                mivs[currOfst].valueField.valueField.lengthField = (int)(currOfst + 7);
                byte[] tmpBytes = new byte[currOfst + 2];
                for (int aryOfst = 0; aryOfst < tmpBytes.Length; aryOfst++)
                {
                    tmpBytes[aryOfst] = (byte)(aryOfst + currOfst);
                }
                mivs[currOfst].valueField.valueField.payloadField = tmpBytes;
                mivs[currOfst].valueField.statusField.countField = (sbyte)(currOfst + 8);
                mivs[currOfst].valueField.statusField.payloadField = tmpBytes;
                mivs[currOfst].userDataField.typeField = (ushort)(currOfst + 9);
                mivs[currOfst].userDataField.lengthField = (int)(currOfst + 10);
                mivs[currOfst].userDataField.payloadField = tmpBytes;
            }
            MonitoredItemConverter cnvrtr = new MonitoredItemConverter();

            byte[] buf = cnvrtr.ConvertMIVToBytes(mivs);

            MonitoredItemValue[] mivs2;

            // this makes a copy.. which is probably ok given what we are doing..
            // GetBuffer is more efficient here.. but returns more than what we 
            // need to transfer (its highly likely to have unused slop-over bytes at the 
            // end of the buffer), which is highly wasteful of network resources, which
            // is the efficiency we are tracking here..
            DumpString(buf);

            cnvrtr.ConvertBytesToMIV(buf, out mivs2);

            Assert.AreEqual(mivs.Length, mivs2.Length);
            Assert.AreEqual(mivs2.Length, countToTest);
            int len = mivs.Length;
            for (int currmiv = 0;
                currmiv < len;
                currmiv++)
            {
                //mivs[currOfst].itemField.Type = (ushort)(currOfst + 1);
                Assert.AreEqual(mivs[currmiv].itemField.Type, mivs2[currmiv].itemField.Type);
                //mivs[currOfst].itemField.ReferenceType = (ushort)(currOfst + 2);
                Assert.AreEqual(mivs[currmiv].itemField.ReferenceType, mivs2[currmiv].itemField.ReferenceType);
                //mivs[currOfst].itemField.Name = String.Format("testing name string #{0}", currOfst + 3);
                Assert.AreEqual(mivs[currmiv].itemField.Name, mivs2[currmiv].itemField.Name);
                //mivs[currOfst].itemField.ContextName = String.Format("testing contextname string #{0}", currOfst + 4);
                Assert.AreEqual(mivs[currmiv].itemField.ContextName, mivs2[currmiv].itemField.ContextName);
                //mivs[currOfst].itemField.Id = (ulong)(currOfst + 5);
                Assert.AreEqual(mivs[currmiv].itemField.Id, mivs2[currmiv].itemField.Id);
                //mivs[currOfst].itemField.IdSpecified = false;
                Assert.AreEqual(mivs[currmiv].itemField.IdSpecified, mivs2[currmiv].itemField.IdSpecified);

                //mivs[currOfst].valueField.timestampField = DateTime.Now;
                Assert.AreEqual(mivs[currmiv].valueField.timestampField, mivs2[currmiv].valueField.timestampField);
                //mivs[currOfst].valueField.timestampFieldSpecified = true;
                Assert.AreEqual(mivs[currmiv].valueField.timestampFieldSpecified, mivs2[currmiv].valueField.timestampFieldSpecified);
                //mivs[currOfst].valueField.valueField.typeField = (ushort)(currOfst + 6);
                Assert.AreEqual(mivs[currmiv].valueField.valueField.typeField, mivs2[currmiv].valueField.valueField.typeField);
                //mivs[currOfst].valueField.valueField.lengthField = (int)(currOfst + 7);
                Assert.AreEqual(mivs[currmiv].valueField.valueField.lengthField, mivs2[currmiv].valueField.valueField.lengthField);
                //byte[] tmpBytes = new byte[currOfst + 2];
                //for (int aryOfst = 0; aryOfst < tmpBytes.Length; aryOfst++)
                //{
                //    tmpBytes[aryOfst] = (byte)(aryOfst + currOfst);
                //}
                //mivs[currOfst].valueField.valueField.payloadField = tmpBytes;
                int len1 = mivs[currmiv].valueField.valueField.payloadField.Length;
                int len2 = mivs2[currmiv].valueField.valueField.payloadField.Length;
                Assert.AreEqual(len1, len2);
                for (int currByteOfst = 0;
                    currByteOfst < len1;
                    currByteOfst++)
                {
                    Assert.AreEqual(mivs[currmiv].valueField.valueField.payloadField[currByteOfst],
                                    mivs2[currmiv].valueField.valueField.payloadField[currByteOfst]);
                }
                //mivs[currOfst].valueField.statusField.countField = (sbyte)(currOfst + 8);
                Assert.AreEqual(mivs[currmiv].valueField.statusField.countField, mivs2[currmiv].valueField.statusField.countField);
                //mivs[currOfst].valueField.statusField.payloadField = tmpBytes;
                len1 = mivs[currmiv].valueField.statusField.payloadField.Length;
                len2 = mivs2[currmiv].valueField.statusField.payloadField.Length;
                Assert.AreEqual(len1, len2);
                for (int currByteOfst = 0;
                    currByteOfst < len1;
                    currByteOfst++)
                {
                    Assert.AreEqual(mivs[currmiv].valueField.statusField.payloadField[currByteOfst],
                                    mivs2[currmiv].valueField.statusField.payloadField[currByteOfst]);
                }

                
                //mivs[currOfst].userDataField.typeField = (ushort)(currOfst + 9);
                Assert.AreEqual(mivs[currmiv].userDataField.typeField, mivs2[currmiv].userDataField.typeField);
                //mivs[currOfst].userDataField.lengthField = (int)(currOfst + 10);
                Assert.AreEqual(mivs[currmiv].userDataField.lengthField, mivs2[currmiv].userDataField.lengthField);
                //mivs[currOfst].userDataField.payloadField = tmpBytes;
                len1 = mivs[currmiv].userDataField.payloadField.Length;
                len2 = mivs2[currmiv].userDataField.payloadField.Length;
                Assert.AreEqual(len1, len2);
                for (int currByteOfst = 0;
                    currByteOfst < len1;
                    currByteOfst++)
                {
                    Assert.AreEqual(mivs[currmiv].userDataField.payloadField[currByteOfst],
                                    mivs2[currmiv].userDataField.payloadField[currByteOfst]);
                }

            }

        }

        [TestMethod]
        public void BlankStringTest()
        {
            int countToTest = 2;
            MonitoredItemValue[] mivs = new MonitoredItemValue[countToTest];
            ItemStatus[] statuses = new ItemStatus[countToTest];
            for (uint currOfst = 0;
                    currOfst < countToTest;
                    currOfst++)
            {
                mivs[currOfst].itemField.Type = (ushort)(currOfst + 1);
                mivs[currOfst].itemField.ReferenceType = (ushort)(currOfst + 2);
                //mivs[currOfst].itemField.Name = String.Format("testing name string #{0}", currOfst + 3);
                mivs[currOfst].itemField.Name = "";
                mivs[currOfst].itemField.ContextName = "";
                mivs[currOfst].itemField.Id = (ulong)(currOfst + 5);
                mivs[currOfst].itemField.IdSpecified = false;

                mivs[currOfst].valueField.timestampField = DateTime.Now;
                mivs[currOfst].valueField.timestampFieldSpecified = true;
                mivs[currOfst].valueField.valueField.typeField = (ushort)(currOfst + 6);
                mivs[currOfst].valueField.valueField.lengthField = (int)(currOfst + 7);
                mivs[currOfst].valueField.valueField.payloadField = null;
                mivs[currOfst].valueField.statusField.countField = (sbyte)(currOfst + 8);
                mivs[currOfst].valueField.statusField.payloadField = null;
                mivs[currOfst].userDataField.typeField = (ushort)(currOfst + 9);
                mivs[currOfst].userDataField.lengthField = (int)(currOfst + 10);
                mivs[currOfst].userDataField.payloadField = null;

                statuses[currOfst].itemField.Type = (ushort)(currOfst + 11);
                statuses[currOfst].itemField.ReferenceType = (ushort)(currOfst + 12);
                statuses[currOfst].itemField.Name = "";
                statuses[currOfst].itemField.ContextName = "";
                statuses[currOfst].itemField.Id = (ulong)(currOfst + 13);
                statuses[currOfst].itemField.IdSpecified = false;
                statuses[currOfst].errorCodeField = (ushort) (currOfst + 14);
                statuses[currOfst].errorCodeFieldSpecified = true;
            }
            MonitoredItemConverter cnvrtr = new MonitoredItemConverter();

            byte[] buf = cnvrtr.ConvertMIVToBytes(mivs);
            byte[] statusesBuf = cnvrtr.ConvertItemStatusToBytes(statuses);

            MonitoredItemValue[] mivs2;
            ItemStatus[] statuses2;

            // this makes a copy.. which is probably ok given what we are doing..
            // GetBuffer is more efficient here.. but returns more than what we 
            // need to transfer (its highly likely to have unused slop-over bytes at the 
            // end of the buffer), which is highly wasteful of network resources, which
            // is the efficiency we are tracking here..
            Console.WriteLine("MIV byte buffer dump");
            DumpString(buf);
            Console.WriteLine("ItemStatus byte buffer dump");
            DumpString(statusesBuf);

            cnvrtr.ConvertBytesToMIV(buf, out mivs2);
            cnvrtr.ConvertBytesToItemStatus(statusesBuf, out statuses2);

            Assert.AreEqual(mivs.Length, mivs2.Length);
            Assert.AreEqual(statuses.Length,statuses2.Length);
            Assert.AreEqual(mivs2.Length, statuses2.Length);

            int len = mivs.Length;
            for (int currmiv = 0;
                currmiv < len;
                currmiv++)
            {
                //mivs[currOfst].itemField.Type = (ushort)(currOfst + 1);
                Assert.AreEqual(mivs[currmiv].itemField.Type, mivs2[currmiv].itemField.Type);
                //mivs[currOfst].itemField.ReferenceType = (ushort)(currOfst + 2);
                Assert.AreEqual(mivs[currmiv].itemField.ReferenceType, mivs2[currmiv].itemField.ReferenceType);
                //mivs[currOfst].itemField.Name = String.Format("testing name string #{0}", currOfst + 3);
                Assert.AreEqual(mivs[currmiv].itemField.Name, mivs2[currmiv].itemField.Name);
                //mivs[currOfst].itemField.ContextName = String.Format("testing contextname string #{0}", currOfst + 4);
                Assert.AreEqual(mivs[currmiv].itemField.ContextName, mivs2[currmiv].itemField.ContextName);
                //mivs[currOfst].itemField.Id = (ulong)(currOfst + 5);
                Assert.AreEqual(mivs[currmiv].itemField.Id, mivs2[currmiv].itemField.Id);
                //mivs[currOfst].itemField.IdSpecified = false;
                Assert.AreEqual(mivs[currmiv].itemField.IdSpecified, mivs2[currmiv].itemField.IdSpecified);

                //mivs[currOfst].valueField.timestampField = DateTime.Now;
                Assert.AreEqual(mivs[currmiv].valueField.timestampField, mivs2[currmiv].valueField.timestampField);
                //mivs[currOfst].valueField.timestampFieldSpecified = true;
                Assert.AreEqual(mivs[currmiv].valueField.timestampFieldSpecified, mivs2[currmiv].valueField.timestampFieldSpecified);
                //mivs[currOfst].valueField.valueField.typeField = (ushort)(currOfst + 6);
                Assert.AreEqual(mivs[currmiv].valueField.valueField.typeField, mivs2[currmiv].valueField.valueField.typeField);
                //mivs[currOfst].valueField.valueField.lengthField = (int)(currOfst + 7);
                Assert.AreEqual(mivs[currmiv].valueField.valueField.lengthField, mivs2[currmiv].valueField.valueField.lengthField);
                //byte[] tmpBytes = new byte[currOfst + 2];
                //for (int aryOfst = 0; aryOfst < tmpBytes.Length; aryOfst++)
                //{
                //    tmpBytes[aryOfst] = (byte)(aryOfst + currOfst);
                //}
                //mivs[currOfst].valueField.valueField.payloadField = tmpBytes;
                Assert.AreEqual(mivs[currmiv].valueField.valueField.payloadField, null);
                Assert.AreEqual(mivs2[currmiv].valueField.valueField.payloadField, null);

                //mivs[currOfst].valueField.statusField.countField = (sbyte)(currOfst + 8);
                Assert.AreEqual(mivs[currmiv].valueField.statusField.countField, mivs2[currmiv].valueField.statusField.countField);
                //mivs[currOfst].valueField.statusField.payloadField = tmpBytes;
                Assert.AreEqual(mivs[currmiv].valueField.statusField.payloadField, null);
                Assert.AreEqual(mivs2[currmiv].valueField.statusField.payloadField, null);


                //mivs[currOfst].userDataField.typeField = (ushort)(currOfst + 9);
                Assert.AreEqual(mivs[currmiv].userDataField.typeField, mivs2[currmiv].userDataField.typeField);
                //mivs[currOfst].userDataField.lengthField = (int)(currOfst + 10);
                Assert.AreEqual(mivs[currmiv].userDataField.lengthField, mivs2[currmiv].userDataField.lengthField);
                //mivs[currOfst].userDataField.payloadField = tmpBytes;
                Assert.AreEqual(mivs[currmiv].userDataField.payloadField, null);
                Assert.AreEqual(mivs2[currmiv].userDataField.payloadField, null);

                Assert.AreEqual(statuses[currmiv].itemField.Type,           statuses2[currmiv].itemField.Type);
                Assert.AreEqual(statuses[currmiv].itemField.ReferenceType,  statuses2[currmiv].itemField.ReferenceType);
                Assert.AreEqual(statuses[currmiv].itemField.Name,           statuses2[currmiv].itemField.Name);
                Assert.AreEqual(statuses[currmiv].itemField.ContextName,    statuses2[currmiv].itemField.ContextName);
                Assert.AreEqual(statuses[currmiv].itemField.Id,             statuses2[currmiv].itemField.Id);
                Assert.AreEqual(statuses[currmiv].itemField.IdSpecified,    statuses2[currmiv].itemField.IdSpecified);

                Assert.AreEqual(statuses[currmiv].errorCodeField,           statuses2[currmiv].errorCodeField);
                Assert.AreEqual(statuses[currmiv].errorCodeFieldSpecified,  statuses2[currmiv].errorCodeFieldSpecified);
            }

        }

        [TestMethod]
        public void NullArrayTest()
        {
            int countToTest = 2;
            MonitoredItemValue[] mivs = new MonitoredItemValue[countToTest];
            ItemStatus[] statuses = new ItemStatus[countToTest];
            for (uint currOfst = 0;
                    currOfst < countToTest;
                    currOfst++)
            {
                mivs[currOfst].itemField.Type = (ushort)(currOfst + 1);
                mivs[currOfst].itemField.ReferenceType = (ushort)(currOfst + 2);
                //mivs[currOfst].itemField.Name = String.Format("testing name string #{0}", currOfst + 3);
                mivs[currOfst].itemField.Name = null;
                mivs[currOfst].itemField.ContextName = null;
                mivs[currOfst].itemField.Id = (ulong)(currOfst + 5);
                mivs[currOfst].itemField.IdSpecified = false;

                mivs[currOfst].valueField.timestampField = DateTime.Now;
                mivs[currOfst].valueField.timestampFieldSpecified = true;
                mivs[currOfst].valueField.valueField.typeField = (ushort)(currOfst + 6);
                mivs[currOfst].valueField.valueField.lengthField = (int)(currOfst + 7);
                mivs[currOfst].valueField.valueField.payloadField = null;
                mivs[currOfst].valueField.statusField.countField = (sbyte)(currOfst + 8);
                mivs[currOfst].valueField.statusField.payloadField = null;
                mivs[currOfst].userDataField.typeField = (ushort)(currOfst + 9);
                mivs[currOfst].userDataField.lengthField = (int)(currOfst + 10);
                mivs[currOfst].userDataField.payloadField = null;

                statuses[currOfst].itemField.Type = (ushort)(currOfst + 11);
                statuses[currOfst].itemField.ReferenceType = (ushort)(currOfst + 12);
                statuses[currOfst].itemField.Name = null;
                statuses[currOfst].itemField.ContextName = null;
                statuses[currOfst].itemField.Id = (ulong)(currOfst + 13);
                statuses[currOfst].itemField.IdSpecified = false;
                statuses[currOfst].errorCodeField = (ushort)(currOfst + 14);
                statuses[currOfst].errorCodeFieldSpecified = true;

            }
            MonitoredItemConverter cnvrtr = new MonitoredItemConverter();

            byte[] buf = cnvrtr.ConvertMIVToBytes(mivs);
            byte[] statusesBuf = cnvrtr.ConvertItemStatusToBytes(statuses);

            MonitoredItemValue[] mivs2;
            ItemStatus[] statuses2;

            // this makes a copy.. which is probably ok given what we are doing..
            // GetBuffer is more efficient here.. but returns more than what we 
            // need to transfer (its highly likely to have unused slop-over bytes at the 
            // end of the buffer), which is highly wasteful of network resources, which
            // is the efficiency we are tracking here..
            Console.WriteLine("MIV buf dump:");
            DumpString(buf);
            Console.WriteLine("ItemStatus buf dump:");
            DumpString(statusesBuf);

            cnvrtr.ConvertBytesToMIV(buf, out mivs2);
            cnvrtr.ConvertBytesToItemStatus(statusesBuf, out statuses2);

            Assert.AreEqual(mivs.Length, mivs2.Length);
            Assert.AreEqual(statuses.Length, statuses2.Length);
            Assert.AreEqual(mivs2.Length,statuses2.Length);

            int len = mivs.Length;
            for (int currmiv = 0;
                currmiv < len;
                currmiv++)
            {
                //mivs[currOfst].itemField.Type = (ushort)(currOfst + 1);
                Assert.AreEqual(mivs[currmiv].itemField.Type, mivs2[currmiv].itemField.Type);
                //mivs[currOfst].itemField.ReferenceType = (ushort)(currOfst + 2);
                Assert.AreEqual(mivs[currmiv].itemField.ReferenceType, mivs2[currmiv].itemField.ReferenceType);
                //mivs[currOfst].itemField.Name = String.Format("testing name string #{0}", currOfst + 3);
                Assert.AreEqual(mivs[currmiv].itemField.Name, null);
                Assert.AreEqual(mivs2[currmiv].itemField.Name,"");
                //mivs[currOfst].itemField.ContextName = String.Format("testing contextname string #{0}", currOfst + 4);
                Assert.AreEqual(mivs[currmiv].itemField.ContextName, null);
                Assert.AreEqual(mivs2[currmiv].itemField.ContextName, "" );
                //mivs[currOfst].itemField.Id = (ulong)(currOfst + 5);
                Assert.AreEqual(mivs[currmiv].itemField.Id, mivs2[currmiv].itemField.Id);
                //mivs[currOfst].itemField.IdSpecified = false;
                Assert.AreEqual(mivs[currmiv].itemField.IdSpecified, mivs2[currmiv].itemField.IdSpecified);

                //mivs[currOfst].valueField.timestampField = DateTime.Now;
                Assert.AreEqual(mivs[currmiv].valueField.timestampField, mivs2[currmiv].valueField.timestampField);
                //mivs[currOfst].valueField.timestampFieldSpecified = true;
                Assert.AreEqual(mivs[currmiv].valueField.timestampFieldSpecified, mivs2[currmiv].valueField.timestampFieldSpecified);
                //mivs[currOfst].valueField.valueField.typeField = (ushort)(currOfst + 6);
                Assert.AreEqual(mivs[currmiv].valueField.valueField.typeField, mivs2[currmiv].valueField.valueField.typeField);
                //mivs[currOfst].valueField.valueField.lengthField = (int)(currOfst + 7);
                Assert.AreEqual(mivs[currmiv].valueField.valueField.lengthField, mivs2[currmiv].valueField.valueField.lengthField);
                //byte[] tmpBytes = new byte[currOfst + 2];
                //for (int aryOfst = 0; aryOfst < tmpBytes.Length; aryOfst++)
                //{
                //    tmpBytes[aryOfst] = (byte)(aryOfst + currOfst);
                //}
                //mivs[currOfst].valueField.valueField.payloadField = tmpBytes;
                Assert.AreEqual(mivs[currmiv].valueField.valueField.payloadField, null);
                Assert.AreEqual(mivs2[currmiv].valueField.valueField.payloadField, null);

                //mivs[currOfst].valueField.statusField.countField = (sbyte)(currOfst + 8);
                Assert.AreEqual(mivs[currmiv].valueField.statusField.countField, mivs2[currmiv].valueField.statusField.countField);
                //mivs[currOfst].valueField.statusField.payloadField = tmpBytes;
                Assert.AreEqual(mivs[currmiv].valueField.statusField.payloadField,null);
                Assert.AreEqual(mivs2[currmiv].valueField.statusField.payloadField,null);


                //mivs[currOfst].userDataField.typeField = (ushort)(currOfst + 9);
                Assert.AreEqual(mivs[currmiv].userDataField.typeField, mivs2[currmiv].userDataField.typeField);
                //mivs[currOfst].userDataField.lengthField = (int)(currOfst + 10);
                Assert.AreEqual(mivs[currmiv].userDataField.lengthField, mivs2[currmiv].userDataField.lengthField);
                //mivs[currOfst].userDataField.payloadField = tmpBytes;
                Assert.AreEqual(mivs[currmiv].userDataField.payloadField,null);
                Assert.AreEqual(mivs2[currmiv].userDataField.payloadField,null);

                Assert.AreEqual(statuses[currmiv].itemField.Type,           statuses2[currmiv].itemField.Type);
                Assert.AreEqual(statuses[currmiv].itemField.ReferenceType,  statuses2[currmiv].itemField.ReferenceType);
                Assert.AreEqual(statuses[currmiv].itemField.Name, null);
                Assert.AreEqual(statuses2[currmiv].itemField.Name, "");
                Assert.AreEqual(statuses[currmiv].itemField.ContextName, null);
                Assert.AreEqual(statuses2[currmiv].itemField.ContextName, "");
                Assert.AreEqual(statuses[currmiv].itemField.Id,             statuses2[currmiv].itemField.Id);
                Assert.AreEqual(statuses[currmiv].itemField.IdSpecified,    statuses2[currmiv].itemField.IdSpecified);
                Assert.AreEqual(statuses[currmiv].errorCodeField,           statuses2[currmiv].errorCodeField);
                Assert.AreEqual(statuses[currmiv].errorCodeFieldSpecified,  statuses2[currmiv].errorCodeFieldSpecified);
            }
        }

        class MIVContainer
        {
            public MonitoredItemValue[] mivs;
            // status addition
            public ItemStatus[] statuses;
        }

        [TestMethod]
        public void LargerScale_20K()
        {
            MonitoredItemConverter cnvrtr = new MonitoredItemConverter();


            for (int x = 0; x < 10; x++)
            {
                int countToTest = 20000;

                MIVContainer mivc = new MIVContainer();
                mivc.mivs = new MonitoredItemValue[countToTest];

                // status addition
                mivc.statuses = new ItemStatus[countToTest];
                for (uint currOfst = 0;
                        currOfst < countToTest;
                        currOfst++)
                {
                    mivc.mivs[currOfst].itemField.Type = (ushort)(currOfst + 1);
                    mivc.mivs[currOfst].itemField.ReferenceType = (ushort)(currOfst + 2);
                    mivc.mivs[currOfst].itemField.Name = String.Format("testing name string #{0}", currOfst + 3);
                    mivc.mivs[currOfst].itemField.ContextName = String.Format("testing contextname string #{0}", currOfst + 4);
                    mivc.mivs[currOfst].itemField.Id = (ulong)(currOfst + 5);
                    mivc.mivs[currOfst].itemField.IdSpecified = false;

                    mivc.mivs[currOfst].valueField.timestampField = DateTime.Now;
                    mivc.mivs[currOfst].valueField.timestampFieldSpecified = true;
                    mivc.mivs[currOfst].valueField.valueField.typeField = (ushort)(currOfst + 6);
                    mivc.mivs[currOfst].valueField.valueField.lengthField = (int)(currOfst + 7);
                    byte[] tmpBytes = new byte[10];
                    for (int aryOfst = 0; aryOfst < tmpBytes.Length; aryOfst++)
                    {
                        tmpBytes[aryOfst] = (byte)(aryOfst + currOfst);
                    }
                    mivc.mivs[currOfst].valueField.valueField.payloadField = tmpBytes;
                    mivc.mivs[currOfst].valueField.statusField.countField = (sbyte)(currOfst + 8);
                    mivc.mivs[currOfst].valueField.statusField.payloadField = tmpBytes;
                    mivc.mivs[currOfst].userDataField.typeField = (ushort)(currOfst + 9);
                    mivc.mivs[currOfst].userDataField.lengthField = (int)(currOfst + 10);
                    mivc.mivs[currOfst].userDataField.payloadField = tmpBytes;

                    // ///////////////////////////////////////
                    // status addition
                    // ///////////////////////////////////////
                    mivc.statuses[currOfst].itemField.Type = (ushort)(currOfst + 11);
                    mivc.statuses[currOfst].itemField.ReferenceType = (ushort)(currOfst + 12);
                    mivc.statuses[currOfst].itemField.Name = String.Format("testing name string #{0}", currOfst + 13);
                    mivc.statuses[currOfst].itemField.ContextName = String.Format("testing contextname string #{0}", currOfst + 14);
                    mivc.statuses[currOfst].itemField.Id = (ulong)(currOfst + 15);
                    mivc.statuses[currOfst].itemField.IdSpecified = false;
                    mivc.statuses[currOfst].errorCodeField = (ushort)(currOfst + 16);
                    mivc.statuses[currOfst].errorCodeFieldSpecified = true;

                }

                TestBigStructParam(mivc.mivs);

                byte[] buf = cnvrtr.ConvertMIVToBytes(mivc.mivs);
                // ///////////////////////////////////////
                // status addition
                // ///////////////////////////////////////
                byte[] statusBuf = cnvrtr.ConvertItemStatusToBytes(mivc.statuses);

                MIVContainer mivc2 = new MIVContainer();

                // this makes a copy.. which is probably ok given what we are doing..
                // GetBuffer is more efficient here.. but returns more than what we 
                // need to transfer (its highly likely to have unused slop-over bytes at the 
                // end of the buffer), which is highly wasteful of network resources, which
                // is the efficiency we are tracking here..
                //DumpString(buf);

                cnvrtr.ConvertBytesToMIV(buf, out mivc2.mivs);
                // ///////////////////////////////////////
                // status addition
                // ///////////////////////////////////////
                cnvrtr.ConvertBytesToItemStatus(statusBuf, out mivc2.statuses);

                Assert.AreEqual(mivc.mivs.Length, mivc2.mivs.Length);
                Assert.AreEqual(mivc2.mivs.Length, countToTest);
                // ///////////////////////////////////////
                // status addition
                // ///////////////////////////////////////
                Assert.AreEqual(mivc.statuses.Length, mivc2.statuses.Length);
                Assert.AreEqual(mivc2.statuses.Length, countToTest);

                int len = mivc.mivs.Length;
                for (int currmiv = 0;
                    currmiv < len;
                    currmiv++)
                {
                    //mivs[currOfst].itemField.Type = (ushort)(currOfst + 1);
                    Assert.AreEqual(mivc.mivs[currmiv].itemField.Type, mivc2.mivs[currmiv].itemField.Type);
                    //mivs[currOfst].itemField.ReferenceType = (ushort)(currOfst + 2);
                    Assert.AreEqual(mivc.mivs[currmiv].itemField.ReferenceType, mivc2.mivs[currmiv].itemField.ReferenceType);
                    //mivs[currOfst].itemField.Name = String.Format("testing name string #{0}", currOfst + 3);
                    Assert.AreEqual(mivc.mivs[currmiv].itemField.Name, mivc2.mivs[currmiv].itemField.Name);
                    //mivs[currOfst].itemField.ContextName = String.Format("testing contextname string #{0}", currOfst + 4);
                    Assert.AreEqual(mivc.mivs[currmiv].itemField.ContextName, mivc2.mivs[currmiv].itemField.ContextName);
                    //mivs[currOfst].itemField.Id = (ulong)(currOfst + 5);
                    Assert.AreEqual(mivc.mivs[currmiv].itemField.Id, mivc2.mivs[currmiv].itemField.Id);
                    //mivs[currOfst].itemField.IdSpecified = false;
                    Assert.AreEqual(mivc.mivs[currmiv].itemField.IdSpecified, mivc2.mivs[currmiv].itemField.IdSpecified);

                    //mivs[currOfst].valueField.timestampField = DateTime.Now;
                    Assert.AreEqual(mivc.mivs[currmiv].valueField.timestampField, mivc2.mivs[currmiv].valueField.timestampField);
                    //mivs[currOfst].valueField.timestampFieldSpecified = true;
                    Assert.AreEqual(mivc.mivs[currmiv].valueField.timestampFieldSpecified, mivc2.mivs[currmiv].valueField.timestampFieldSpecified);
                    //mivs[currOfst].valueField.valueField.typeField = (ushort)(currOfst + 6);
                    Assert.AreEqual(mivc.mivs[currmiv].valueField.valueField.typeField, mivc2.mivs[currmiv].valueField.valueField.typeField);
                    //mivs[currOfst].valueField.valueField.lengthField = (int)(currOfst + 7);
                    Assert.AreEqual(mivc.mivs[currmiv].valueField.valueField.lengthField, mivc2.mivs[currmiv].valueField.valueField.lengthField);
                    //byte[] tmpBytes = new byte[currOfst + 2];
                    //for (int aryOfst = 0; aryOfst < tmpBytes.Length; aryOfst++)
                    //{
                    //    tmpBytes[aryOfst] = (byte)(aryOfst + currOfst);
                    //}
                    //mivs[currOfst].valueField.valueField.payloadField = tmpBytes;
                    int len1 = mivc.mivs[currmiv].valueField.valueField.payloadField.Length;
                    int len2 = mivc2.mivs[currmiv].valueField.valueField.payloadField.Length;
                    Assert.AreEqual(len1, len2);
                    for (int currByteOfst = 0;
                        currByteOfst < len1;
                        currByteOfst++)
                    {
                        Assert.AreEqual(mivc.mivs[currmiv].valueField.valueField.payloadField[currByteOfst],
                                        mivc2.mivs[currmiv].valueField.valueField.payloadField[currByteOfst]);
                    }
                    //mivs[currOfst].valueField.statusField.countField = (sbyte)(currOfst + 8);
                    Assert.AreEqual(mivc.mivs[currmiv].valueField.statusField.countField, mivc2.mivs[currmiv].valueField.statusField.countField);
                    //mivs[currOfst].valueField.statusField.payloadField = tmpBytes;
                    len1 = mivc.mivs[currmiv].valueField.statusField.payloadField.Length;
                    len2 = mivc2.mivs[currmiv].valueField.statusField.payloadField.Length;
                    Assert.AreEqual(len1, len2);
                    for (int currByteOfst = 0;
                        currByteOfst < len1;
                        currByteOfst++)
                    {
                        Assert.AreEqual(mivc.mivs[currmiv].valueField.statusField.payloadField[currByteOfst],
                                        mivc2.mivs[currmiv].valueField.statusField.payloadField[currByteOfst]);
                    }


                    //mivs[currOfst].userDataField.typeField = (ushort)(currOfst + 9);
                    Assert.AreEqual(mivc.mivs[currmiv].userDataField.typeField, mivc2.mivs[currmiv].userDataField.typeField);
                    //mivs[currOfst].userDataField.lengthField = (int)(currOfst + 10);
                    Assert.AreEqual(mivc.mivs[currmiv].userDataField.lengthField, mivc2.mivs[currmiv].userDataField.lengthField);
                    //mivs[currOfst].userDataField.payloadField = tmpBytes;
                    len1 = mivc.mivs[currmiv].userDataField.payloadField.Length;
                    len2 = mivc2.mivs[currmiv].userDataField.payloadField.Length;
                    Assert.AreEqual(len1, len2);
                    for (int currByteOfst = 0;
                        currByteOfst < len1;
                        currByteOfst++)
                    {
                        Assert.AreEqual(mivc.mivs[currmiv].userDataField.payloadField[currByteOfst],
                                        mivc2.mivs[currmiv].userDataField.payloadField[currByteOfst]);
                    }

                    // ///////////////////////////////////////
                    // status addition
                    // ///////////////////////////////////////
                    Assert.AreEqual(mivc.statuses[currmiv].itemField.Type,          mivc2.statuses[currmiv].itemField.Type);
                    Assert.AreEqual(mivc.statuses[currmiv].itemField.ReferenceType, mivc2.statuses[currmiv].itemField.ReferenceType);
                    Assert.AreEqual(mivc.statuses[currmiv].itemField.Name,          mivc2.statuses[currmiv].itemField.Name);
                    Assert.AreEqual(mivc.statuses[currmiv].itemField.ContextName,   mivc2.statuses[currmiv].itemField.ContextName);
                    Assert.AreEqual(mivc.statuses[currmiv].itemField.Id,            mivc2.statuses[currmiv].itemField.Id);
                    Assert.AreEqual(mivc.statuses[currmiv].itemField.IdSpecified,   mivc2.statuses[currmiv].itemField.IdSpecified);
                    Assert.AreEqual(mivc.statuses[currmiv].errorCodeField,          mivc2.statuses[currmiv].errorCodeField);
                    Assert.AreEqual(mivc.statuses[currmiv].itemField.IdSpecified,   mivc2.statuses[currmiv].itemField.IdSpecified);
                }
            }

        }

        private void TestBigStructParam(MonitoredItemValue [] miv)
        {
            Console.WriteLine(miv[0].itemField.Id);
        }

    }
}
