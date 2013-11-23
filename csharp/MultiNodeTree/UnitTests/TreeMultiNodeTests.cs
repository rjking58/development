using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using NUnit.Framework;

namespace MultiNodeTree.UnitTests
{
    [TestFixture]
    public class TreeMultiNodeTests
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
        public void SingleNodeTest()
        {
            TreeMultiNode<string> root = new TreeMultiNode<string>("1");
            TreeMultiNode<string>.TreeNodePreOrderIterator iter = root.GetPreOrderIterator();
            while(iter.Current != null)
            {
                Console.WriteLine(iter.Current.Val);
                iter++;
            }
        }
        private void ValidateIteratorOutput(string[] validationList,TreeMultiNode<string> root)
        {
            int currValidation = 0;
            int iteratorCount = 0;
            TreeMultiNode<string>.TreeNodePreOrderIterator iter = root.GetPreOrderIterator();
            while(iter.Current != null)
            {
                Assert.AreEqual(validationList[currValidation],iter.Current.GetNode());
                currValidation++;
                iter++;
                iteratorCount++;
            }
            Assert.AreEqual(validationList.Length,iteratorCount);
        }
        [Test]
        public void DeepTreeTest()
        {
            string [] validation1 = {   "1",
                                        "1-0",
                                        "1-0-0",
                                        "1-0-0-0",
                                        "1-0-0-0-0",
                                        "1-0-0-0-0-0",
                                        "1-0-0-0-0-0-0",
                                        "1-0-0-0-0-0-0-0",
                                        "1-0-0-0-0-0-0-0-0",
                                        "1-0-0-0-0-0-0-0-0-0",
                                    };
            // single node deep tree
            TreeMultiNode<string> root = new TreeMultiNode<string>("1");
            root.AddNode(new TreeMultiNode<string>("1-0"));
            TreeMultiNode<string> curr = root.Children[0];
            curr.AddNode(new TreeMultiNode<string>("1-0-0"));
            curr = curr.Children[0];
            curr.AddNode(new TreeMultiNode<string>("1-0-0-0"));
            curr = curr.Children[0];
            curr.AddNode(new TreeMultiNode<string>("1-0-0-0-0"));
            curr = curr.Children[0];
            curr.AddNode(new TreeMultiNode<string>("1-0-0-0-0-0"));
            curr = curr.Children[0];
            curr.AddNode(new TreeMultiNode<string>("1-0-0-0-0-0-0"));
            curr = curr.Children[0];
            curr.AddNode(new TreeMultiNode<string>("1-0-0-0-0-0-0-0"));
            curr = curr.Children[0];
            curr.AddNode(new TreeMultiNode<string>("1-0-0-0-0-0-0-0-0"));
            curr = curr.Children[0];
            curr.AddNode(new TreeMultiNode<string>("1-0-0-0-0-0-0-0-0-0"));
            
            TreeMultiNode<string>.TreeNodePreOrderIterator iter = root.GetPreOrderIterator();
            while(iter.Current != null)
            {
                Console.WriteLine(iter.Current.Val);
                iter++;
            }
            ValidateIteratorOutput(validation1,root);
        }
        [Test]
        public void BalancedTreeTest()
        {

            string [] validation1 = {   "1",
                                        "1-0",
                                        "1-1",
                                        "1-2",
                                        "1-3",
                                    };
            string [] validation2 = {   "1",
                                        "1-0",
                                        "1-0-0",
                                        "1-0-1",
                                        "1-0-2",
                                        "1-0-3",
                                        "1-1",
                                        "1-2",
                                        "1-3",
                                    };
            string [] validation3 = {   "1",
                                        "1-0",
                                        "1-0-0",
                                        "1-0-0-0",
                                        "1-0-0-1",
                                        "1-0-0-2",
                                        "1-0-0-3",
                                        "1-0-0-4",
                                        "1-0-1",
                                        "1-0-2",
                                        "1-0-2-0",
                                        "1-0-2-1",
                                        "1-0-2-2",
                                        "1-0-2-3",
                                        "1-0-2-4",
                                        "1-0-3",
                                        "1-1",
                                        "1-2",
                                        "1-3",
                                    };
            string [] validation4 = {   "1",
                                        "1-0",
                                        "1-0-0",
                                        "1-0-0-0",
                                        "1-0-0-1",
                                        "1-0-0-2",
                                        "1-0-0-3",
                                        "1-0-0-4",
                                        "1-0-1",
                                        "1-0-2",
                                        "1-0-2-0",
                                        "1-0-2-1",
                                        "1-0-2-2",
                                        "1-0-2-3",
                                        "1-0-2-4",
                                        "1-0-3",
                                        "1-1",
                                        "1-1-0",
                                        "1-1-1",
                                        "1-1-2",
                                        "1-1-3",
                                        "1-2",
                                        "1-2-0",
                                        "1-2-1",
                                        "1-2-1-0",
                                        "1-2-1-1",
                                        "1-2-1-2",
                                        "1-2-1-3",
                                        "1-2-1-4",
                                        "1-2-2",
                                        "1-2-3",
                                        "1-3",
                                    };
            string [] validation5 = {   "1",
                                        "1-0",
                                        "1-0-0",
                                        "1-0-0-0",
                                        "1-0-0-1",
                                        "1-0-0-2",
                                        "1-0-0-3",
                                        "1-0-0-4",
                                        "1-0-1",
                                        "1-0-2",
                                        "1-0-2-0",
                                        "1-0-2-1",
                                        "1-0-2-2",
                                        "1-0-2-3",
                                        "1-0-2-4",
                                        "1-0-3",
                                        "1-1",
                                        "1-1-0",
                                        "1-1-1",
                                        "1-1-2",
                                        "1-1-3",
                                        "1-2",
                                        "1-2-0",
                                        "1-2-1",
                                        "1-2-1-0",
                                        "1-2-1-1",
                                        "1-2-1-2",
                                        "1-2-1-3",
                                        "1-2-1-4",
                                        "1-2-2",
                                        "1-2-3",
                                        "1-2-3-0",
                                        "1-2-3-1",
                                        "1-2-3-2",
                                        "1-2-3-3",
                                        "1-2-3-4",
                                        "1-3",
                                        "1-3-0",
                                        "1-3-1",
                                        "1-3-2",
                                        "1-3-3",
                                    };
            TreeMultiNode<string> root = new TreeMultiNode<string>("1");
            root.AddNode(new TreeMultiNode<string>("1-0"));
            root.AddNode(new TreeMultiNode<string>("1-1"));
            root.AddNode(new TreeMultiNode<string>("1-2"));
            root.AddNode(new TreeMultiNode<string>("1-3"));

            ValidateIteratorOutput(validation1,root);

            TreeMultiNode<string> curr = root.Children[0];
            curr.AddNode(new TreeMultiNode<string>("1-0-0"));
            curr.AddNode(new TreeMultiNode<string>("1-0-1"));
            curr.AddNode(new TreeMultiNode<string>("1-0-2"));
            curr.AddNode(new TreeMultiNode<string>("1-0-3"));

            ValidateIteratorOutput(validation2,root);

            curr = root.Children[0].Children[0];
            curr.AddNode(new TreeMultiNode<string>("1-0-0-0"));
            curr.AddNode(new TreeMultiNode<string>("1-0-0-1"));
            curr.AddNode(new TreeMultiNode<string>("1-0-0-2"));
            curr.AddNode(new TreeMultiNode<string>("1-0-0-3"));
            curr.AddNode(new TreeMultiNode<string>("1-0-0-4"));
            curr = root.Children[0].Children[2];
            curr.AddNode(new TreeMultiNode<string>("1-0-2-0"));
            curr.AddNode(new TreeMultiNode<string>("1-0-2-1"));
            curr.AddNode(new TreeMultiNode<string>("1-0-2-2"));
            curr.AddNode(new TreeMultiNode<string>("1-0-2-3"));
            curr.AddNode(new TreeMultiNode<string>("1-0-2-4"));
            ValidateIteratorOutput(validation3,root);

            curr = root.Children[1];
            curr.AddNode(new TreeMultiNode<string>("1-1-0"));
            curr.AddNode(new TreeMultiNode<string>("1-1-1"));
            curr.AddNode(new TreeMultiNode<string>("1-1-2"));
            curr.AddNode(new TreeMultiNode<string>("1-1-3"));
            curr = root.Children[2];
            curr.AddNode(new TreeMultiNode<string>("1-2-0"));
            curr.AddNode(new TreeMultiNode<string>("1-2-1"));
            curr.AddNode(new TreeMultiNode<string>("1-2-2"));
            curr.AddNode(new TreeMultiNode<string>("1-2-3"));
            curr = root.Children[2].Children[1];
            curr.AddNode(new TreeMultiNode<string>("1-2-1-0"));
            curr.AddNode(new TreeMultiNode<string>("1-2-1-1"));
            curr.AddNode(new TreeMultiNode<string>("1-2-1-2"));
            curr.AddNode(new TreeMultiNode<string>("1-2-1-3"));
            curr.AddNode(new TreeMultiNode<string>("1-2-1-4"));

            ValidateIteratorOutput(validation4,root);

            curr = root.Children[2].Children[3];
            curr = root.Children[2].Children[3];
            curr.AddNode(new TreeMultiNode<string>("1-2-3-0"));
            curr.AddNode(new TreeMultiNode<string>("1-2-3-1"));
            curr.AddNode(new TreeMultiNode<string>("1-2-3-2"));
            curr.AddNode(new TreeMultiNode<string>("1-2-3-3"));
            curr.AddNode(new TreeMultiNode<string>("1-2-3-4"));
            curr = root.Children[3];
            curr.AddNode(new TreeMultiNode<string>("1-3-0"));
            curr.AddNode(new TreeMultiNode<string>("1-3-1"));
            curr.AddNode(new TreeMultiNode<string>("1-3-2"));
            curr.AddNode(new TreeMultiNode<string>("1-3-3"));
            
            ValidateIteratorOutput(validation5,root);
            
            TreeMultiNode<string>.TreeNodePreOrderIterator iter = root.GetPreOrderIterator();
            while(iter.Current != null)
            {
                Console.WriteLine(iter.Current.Val);
                iter++;
            }
        }
    }
       

}
