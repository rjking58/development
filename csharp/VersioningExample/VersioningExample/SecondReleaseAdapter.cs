using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VersioningExample_SecondRelease
{
    public abstract class iImplementationAdapter
    {
        public abstract void DoSomething(   int paramA,
                                            int paramB,
                                            bool paramCisValid,
                                            int  paramC);

    }

    public class ImplementationAdapterV1 : iImplementationAdapter
    {
        private VersioningExample.TargetImplementation_V1 m_Impl;

        public ImplementationAdapterV1(VersioningExample.TargetImplementation_V1 Impl)
        {
            m_Impl = Impl;
        }

        public override void DoSomething(   int paramA,
                                            int paramB,
                                            bool paramCisValid,
                                            int paramC)
        {
            if(paramCisValid)
            {
                throw new MissingFieldException("oops, TargetImplementation_V1 doesn't support paramC");
            }
            m_Impl.DoSomething(paramA, paramB);
        }
    }

    public class ImplementationAdapterV2 : iImplementationAdapter
    {
        private VersioningExample.TargetImplementation_V2 m_Impl;

        public ImplementationAdapterV2(VersioningExample.TargetImplementation_V2 Impl)
        {
            m_Impl = Impl;
        }

        public override void DoSomething(int paramA,
                                            int paramB,
                                            bool paramCisValid,
                                            int paramC)
        {
            m_Impl.DoSomething(paramA, paramB, paramCisValid,paramC);
        }
    }


}
