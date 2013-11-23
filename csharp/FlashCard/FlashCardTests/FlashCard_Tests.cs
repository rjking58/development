using System;
using System.Collections.Generic;
using System.Text;

using System.Threading;

using NUnit.Framework;
using FlashCard;
using System.IO;
using System.Xml;
using System.Xml.Serialization;

namespace FlashCardTests
{
    [TestFixture]
    public class FlashCard_Tests
    {
         
        [SetUp]
        public void Init()
        {
        }
    
        [TearDown] 
        public void Dispose()
        {
        }
    
        [Test]
        public void FlashCardCreation() 
        {
            SingleFlashCard fc = new SingleFlashCard("one", "two"); 
            Assert.AreEqual("one",fc.First);
            Assert.AreEqual("two",fc.Second);
            fc.setSuccess(true);
            fc.setSuccess(false);
            fc.setSuccess(true);
            Assert.AreEqual(6,fc.successRank());
            fc.setSuccess(false);
            Assert.AreEqual(5,fc.successRank());
            fc.setSuccess(false);
            Assert.AreEqual(4,fc.successRank());
            fc.setSuccess(false);
            Assert.AreEqual(3,fc.successRank());
            fc.setSuccess(true);
            Assert.AreEqual(4,fc.successRank());
            fc.setSuccess(false);
            fc.setSuccess(false);
            fc.setSuccess(false);
            Assert.AreEqual(3,fc.successRank());

            fc.setSuccess(false);
            Assert.AreEqual(2,fc.successRank());
            fc.setSuccess(false);
            fc.setSuccess(false);
            Assert.AreEqual(1,fc.successRank());
            fc.setSuccess(false);
            Assert.AreEqual(1,fc.successRank());
            fc.setSuccess(false);
            Assert.AreEqual(1,fc.successRank());
            fc.setSuccess(false);
            Assert.AreEqual(1,fc.successRank());
            fc.setSuccess(false);
            Assert.AreEqual(0,fc.successRank());


            Console.WriteLine(fc.successRank());
        }
        [Test]
        public void CardDeckShufflesTest()
        {
            CardDeck cd = new CardDeck();
            Assert.IsTrue(cd.AddCard(new SingleFlashCard("1","one")));
            Assert.IsTrue(cd.AddCard(new SingleFlashCard("2","one")));
            Assert.IsTrue(cd.AddCard(new SingleFlashCard("3","one")));
            Assert.IsTrue(cd.AddCard(new SingleFlashCard("4","one")));
            Assert.IsTrue(cd.AddCard(new SingleFlashCard("5","one")));
            
            foreach(SingleFlashCard sfc in cd.AllCards())
            {
                Console.WriteLine(sfc.First);
            }
            Console.WriteLine();
            Thread.Sleep(2000);
            cd.Shuffle();
            foreach(SingleFlashCard sfc in cd.AllCards())
            {
                Console.WriteLine(sfc.First);
            }
            Console.WriteLine();
            Thread.Sleep(2000);            
            cd.Shuffle();
            foreach(SingleFlashCard sfc in cd.AllCards())
            {
                Console.WriteLine(sfc.First);
            }
            Console.WriteLine();
            Thread.Sleep(2000);            
            cd.Shuffle();
            foreach(SingleFlashCard sfc in cd.AllCards())
            {
                Console.WriteLine(sfc.First);
            }
            Console.WriteLine();            
        }
    
        /// <summary>
        ///  working example of converting an internal sorted list to a serialized XML output.. and coming
        ///  back..
        /// </summary>
        [Test]
        public void SerializationTest()
        {
            SortedList<string, SingleFlashCard> myList = new SortedList<string, SingleFlashCard>();
            List<SingleFlashCard> flatList = new List<SingleFlashCard>();
 
            SingleFlashCard singleCard = new SingleFlashCard("first", "a one ah");
            myList.Add(singleCard.First, singleCard);
            singleCard = new SingleFlashCard("second", "a two ah");
            myList.Add(singleCard.First, singleCard);
            singleCard = new SingleFlashCard("third", "a three ah");
            myList.Add(singleCard.First, singleCard);


            foreach(KeyValuePair<string,SingleFlashCard> kvp in myList)
            {
                flatList.Add(kvp.Value);
            }

            XmlSerializer myXMLSerializer = new XmlSerializer(typeof(List<SingleFlashCard>));
            TextWriter twriter = new StreamWriter("xmlSerializeTest.txt");

            myXMLSerializer.Serialize(twriter,flatList);

            twriter.Close();

            FileStream treader = new FileStream("xmlSerializeTest.txt",FileMode.Open);
            XmlSerializer myXMLSerializer2 = new XmlSerializer(typeof(List<SingleFlashCard>));

            // in case of changes to underlying file..
            myXMLSerializer2.UnknownNode+= new XmlNodeEventHandler(serializer_UnknownNode);
            myXMLSerializer2.UnknownAttribute+= new XmlAttributeEventHandler(serializer_UnknownAttribute);

            SortedList<string, SingleFlashCard> myList2 = new SortedList<string, SingleFlashCard>();
            List<SingleFlashCard> myFlatList2 = null;

            myFlatList2 = (List<SingleFlashCard>)myXMLSerializer2.Deserialize(treader);
            foreach(SingleFlashCard sfc in myFlatList2)
            {
                myList2.Add(sfc.First, sfc);
            }
            foreach(KeyValuePair<string,SingleFlashCard> kvp in myList2)
            {
                Assert.IsTrue(myList.ContainsKey(kvp.Key));
                Assert.AreEqual(myList[kvp.Key].First, myList2[kvp.Key].First);
                Assert.AreEqual(myList[kvp.Key].Second, myList2[kvp.Key].Second);
            }

            treader.Close();
        }
        [Test]
        public void ThousandCardTest()
        {
            CardDeck cd = new CardDeck();

            for (int currCard = 0;
                 currCard < 1000;
                 currCard++)
            {
                string cardstring = "[" + currCard + "]";
                SingleFlashCard sfc = new SingleFlashCard(cardstring,cardstring);
                cd.AddCard(sfc);
            }

            int outputs = 0;
            for (int curroutput = 0;
                 curroutput < 1000;
                 curroutput++)
            {
                SingleFlashCard prevCard0 = null;
                SingleFlashCard prevCard100 = null;
                SingleFlashCard prevCard500 = null;                
                
                foreach(SingleFlashCard sfc in cd.AllCards())
                {
                    if (curroutput == 0)
                    {
                        if(prevCard0 != null)
                        {
                            Assert.AreNotEqual(prevCard0.First,sfc.First);
                            prevCard0 = sfc;
                        }
                        else
                        {
                            prevCard0 = sfc;
                        }
                    }
                    if(curroutput == 100)
                    {
                        if(prevCard100 != null)
                        {
                            Assert.AreNotEqual(prevCard100.First,sfc.First);
                            prevCard100 = sfc;
                        }
                        else
                        {
                            prevCard100 = sfc;
                        }
                    } 
                    if(curroutput == 500)
                    {
                        if(prevCard500 != null)
                        {
                            Assert.AreNotEqual(prevCard500.First,sfc.First);
                            prevCard500 = sfc;
                        }
                        else
                        {
                            prevCard500 = sfc;
                        }
                    }
                    
                    Assert.IsNotNull(sfc);
                }
                Console.Write(".");
                cd.Shuffle();
                Console.Write("s");
                outputs++;
                if (outputs > 50)
                {
                    Console.WriteLine();
                    outputs = 0;
                }
            }
            Console.WriteLine();
        }
        private void serializer_UnknownNode (object sender, XmlNodeEventArgs e)
        {
            Console.WriteLine("Unknown Node:" +   e.Name + "\t" + e.Text);
        }

        private void serializer_UnknownAttribute (object sender, XmlAttributeEventArgs e)
        {
            System.Xml.XmlAttribute attr = e.Attr;
            Console.WriteLine("Unknown attribute " + 
            attr.Name + "='" + attr.Value + "'");
        }

    }
    

}
