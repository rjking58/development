using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using NUnit.Framework;

namespace GridEngy1_weelzUT
{
    [TestFixture]
    public class GridEngyTests
    {
        [Test]
        public void SimpleTest()
        {
            
           Assert.AreEqual("woof-boy",GridEngy1_weezl.GridEngyClass.retrieveFromAssembly());
        }
    }
}
