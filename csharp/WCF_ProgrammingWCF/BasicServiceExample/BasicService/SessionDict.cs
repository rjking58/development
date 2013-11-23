using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BasicService
{
    class SessionDict
    {
        static object      m_lockSessionId = new object();
        static private int m_sessionId = 0;

        static object m_lockSessionIdDict = new object();
        static Dictionary<int, int> m_sessionIdDict = new Dictionary<int, int>();

        static public void AddSession(int sessionId)
        {
            Console.WriteLine("adding session[" + sessionId + "]");
            lock(m_lockSessionIdDict)
            {
                m_sessionIdDict.Add(sessionId, sessionId);
            }
        }

        static public void RemoveSession(int sessionId)
        {
            Console.WriteLine("removing session[" + sessionId + "]");
            lock (m_lockSessionIdDict)
            {
                m_sessionIdDict.Remove(sessionId);
            }
        }
        static public int NextSessionId()
        {
            lock (m_lockSessionId)
            {
                m_sessionId++;
                return m_sessionId;
            }
        }
    }
}
