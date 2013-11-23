using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;

namespace BasicService
{
    // NOTE: You can use the "Rename" command on the "Refactor" menu to change the class name "Service1" in both code and config file together.
    public class Service1 : IService1,IDisposable
    {
        int m_sessionId = 0;
        int m_val = 0;

        // implements session id semantics from the service instance start/stop side.
        public Service1()
        {
            m_sessionId = SessionDict.NextSessionId();
            SessionDict.AddSession(m_sessionId);
        }
        public void Dispose()
        {
            SessionDict.RemoveSession(m_sessionId);
        }



        public string GetData(int value)
        {
            m_val = value;

            return string.Format("Yo BOZO [{1}], you entered: {0}", value, m_sessionId);
        }

        public CompositeType GetDataUsingDataContract(CompositeType composite)
        {
            if (composite == null)
            {
                throw new ArgumentNullException("composite");
            }
            if (composite.BoolValue)
            {
                composite.StringValue += "Gerbil";
                composite.BoolValue = !composite.BoolValue;
            }
            return composite;
        }

    }
}
