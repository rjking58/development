using System;
using System.Text;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace TestVersioning
{
    [TestClass]
    public class UnitTest1
    {
        [TestMethod]
        public void Release1Test()
        {
            VersioningExample_FirstRelease.ImplementationAdapterV1 v1Adapt = 
                new VersioningExample_FirstRelease.ImplementationAdapterV1(new VersioningExample.TargetImplementation_V1());

            v1Adapt.DoSomething(1,2);
        }


        private void Release2TryBoth(VersioningExample_SecondRelease.iImplementationAdapter adptr)
        {
            adptr.DoSomething(1,2,false,0);
            try
            {
                adptr.DoSomething(1, 2, true, 0);
            }
            catch (MissingFieldException ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        [TestMethod]
        public void Release2Test()
        {
            VersioningExample_SecondRelease.ImplementationAdapterV1 v1Adapt =
                new VersioningExample_SecondRelease.ImplementationAdapterV1(new VersioningExample.TargetImplementation_V1());

            Release2TryBoth(v1Adapt);

            VersioningExample_SecondRelease.ImplementationAdapterV2 v2Adapt =
                new VersioningExample_SecondRelease.ImplementationAdapterV2(new VersioningExample.TargetImplementation_V2());

            Release2TryBoth(v2Adapt);
        }

        private void Release3TryAll(VersioningExample_ThirdRelease.iImplementationAdapter adptr)
        {
            adptr.DoSomething(1, 2, false, 0);
            try
            {
                adptr.DoSomething(1, 2, true, 0);
            }
            catch (MissingFieldException ex)
            {
                Console.WriteLine(ex.Message);
            }

            try
            {
                adptr.DoSomethingElse(4);
            }
            catch(MissingMemberException ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        [TestMethod]
        public void Release3Test()
        {
            VersioningExample_ThirdRelease.ImplementationAdapterV1 v1Adapt =
                new VersioningExample_ThirdRelease.ImplementationAdapterV1(new VersioningExample.TargetImplementation_V1());

            Release3TryAll(v1Adapt);

            VersioningExample_ThirdRelease.ImplementationAdapterV2 v2Adapt =
                new VersioningExample_ThirdRelease.ImplementationAdapterV2(new VersioningExample.TargetImplementation_V2());

            Release3TryAll(v2Adapt);

            VersioningExample_ThirdRelease.ImplementationAdapterV3 v3Adapt =
                new VersioningExample_ThirdRelease.ImplementationAdapterV3(new VersioningExample.TargetImplementation_V3());

            Release3TryAll(v3Adapt);
        }
    }
}
