using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VersioningExample_FirstRelease
{
    public abstract class iImplementationAdapter
    {
        public abstract void DoSomething(int paramA,
                                        int paramB);
    }

    public class ImplementationAdapterV1 : iImplementationAdapter
    {
        private VersioningExample.TargetImplementation_V1 m_Impl;

        public ImplementationAdapterV1(VersioningExample.TargetImplementation_V1 Impl)
        {
            m_Impl = Impl;
        }

        public override void DoSomething(   int paramA,
                                            int paramB)
        {
            m_Impl.DoSomething(paramA,paramB);
        }
    }


}
