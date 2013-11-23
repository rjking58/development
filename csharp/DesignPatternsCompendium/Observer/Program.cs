using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Observer
{
    /// <summary>
    /// the interface our observers comply with..
    /// a 'subscriber' in publish/subscribe parlance
    /// </summary>
    interface ISomeObserver
    {
        /// <summary>
        /// how a notification is sent to an observer
        /// </summary>
        /// <param name="s">contents of the messages sent</param>
        void HandleNotification(string s);
    }
    /// <summary>
    /// a concrete expression of our observer..
    /// </summary>
    class SomeObserver : ISomeObserver
    {
        private string m_name = "";
        public SomeObserver(string name)
        {
            m_name = name;
        }
        public void  HandleNotification(string s)
        {
            Console.WriteLine(m_name + " " + s);
        }
    }
    /// <summary>
    /// a class that is to be observed.. a 'publisher' in 
    /// publish/subscribe parlance.
    /// </summary>
    class SomethingObserved
    {
        /// <summary>
        /// list of all current observers/subscribers
        /// </summary>
        private List<ISomeObserver> m_observers = new List<ISomeObserver>();

        /// <summary>
        /// simulates some event received by the publisher..
        /// one of the things it must do is notify all observers of a 
        /// change in state..
        /// </summary>
        /// <param name="s"></param>
        public void ReceiveMessage(string s)
        {
            NotifyObservers(s);
        }

        /// <summary>
        /// add an observer/subscriber
        /// </summary>
        /// <param name="iso">the observer/subscriber to add</param>
        public void add(ISomeObserver iso)
        {
            /// only add if we haven't already added it..
            if( ! m_observers.Contains(iso))
            {
                m_observers.Add(iso);
            }
        }
        /// <summary>
        /// remove an observer/subscriber
        /// </summary>
        /// <param name="iso">the observer/subscriber to remove</param>
        public void remove(ISomeObserver iso)
        {
            /// only remove if it is already contained ..
            if(m_observers.Contains(iso))
            {
                m_observers.Remove(iso);
            }
        }
        /// <summary>
        /// publish the change event to the observers/subscribers
        /// </summary>
        /// <param name="s">any info we want to pass to the 
        /// observers/subscribers</param>
        private void NotifyObservers(string s)
        {
            foreach(ISomeObserver iso in m_observers)
            {
                iso.HandleNotification(s);
            }
        }

    }
    class Program
    {
        static void Main(string[] args)
        {
            SomethingObserved observed = new SomethingObserved();
            SomeObserver observer1 = new SomeObserver("observer1");
            SomeObserver observer2 = new SomeObserver("observer2");

            observed.add(observer1);
            observed.ReceiveMessage("msg1");

            observed.add(observer2);
            observed.ReceiveMessage("msg2");

            observed.remove(observer1);
            observed.ReceiveMessage("msg3");

            observed.remove(observer2);
            observed.ReceiveMessage("msg4");
        }
    }
}
