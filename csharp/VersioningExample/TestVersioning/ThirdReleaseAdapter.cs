using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VersioningExample_ThirdRelease
{
    public abstract class iImplementationAdapter
    {
        public abstract void DoSomething(   int paramA,
                                            int paramB,
                                            bool paramCisValid,
                                            int paramC);

        public abstract void DoSomethingElse(int paramA);

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
            if (paramCisValid)
            {
                throw new MissingFieldException("oops, TargetImplementation_V1 doesn't support paramC");
            }
            m_Impl.DoSomething(paramA, paramB);
        }

        public override void DoSomethingElse(int paramA)
        {
            throw new MissingMemberException("oops, TargetImplementation_V1 doesn't support DoSomethingElse");
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
            m_Impl.DoSomething(paramA, paramB, paramCisValid, paramC);
        }

        public override void DoSomethingElse(int paramA)
        {
            throw new MissingMemberException("oops, TargetImplementation_V1 doesn't support DoSomethingElse");
        }
    }

    public class ImplementationAdapterV3 : iImplementationAdapter
    {
        private VersioningExample.TargetImplementation_V3 m_Impl;

        public ImplementationAdapterV3(VersioningExample.TargetImplementation_V3 Impl)
        {
            m_Impl = Impl;
        }

        public override void DoSomething(int paramA,
                                            int paramB,
                                            bool paramCisValid,
                                            int paramC)
        {
            m_Impl.DoSomething(paramA, paramB, paramCisValid, paramC);
        }

        public override void DoSomethingElse(int paramA)
        {
            m_Impl.DoSomethingElse(paramA);
        }
    }

}
