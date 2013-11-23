// ObserverCPP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <memory>
#include <string>
#include <set>

/// <summary>
/// the interface our observers comply with..
/// a 'subscriber' in publish/subscribe parlance
/// </summary>
class ISomeObserver
{
public:
    /// <summary>
    /// how a notification is sent to an observer
    /// </summary>
    /// <param name="s">contents of the messages sent</param>
    virtual void HandleNotification(std::string s) = 0;
};
/// <summary>
/// a concrete expression of our observer..
/// </summary>
class SomeObserver : public ISomeObserver
{
private:
    std::string m_name;

public:
    SomeObserver(std::string name)
    {
        m_name = name;
    }
    void  HandleNotification(std::string s)
    {
        std::cout << m_name << " " << s << std::endl;
    }
};
/// <summary>
/// a class that is to be observed.. a 'publisher' in 
/// publish/subscribe parlance.
/// </summary>
class SomethingObserved
{
private:
    /// <summary>
    /// list of all current observers/subscribers
    /// note that we don't own any of these.. so 
    /// never ever delete.
    /// </summary>
    std::set<ISomeObserver *> m_observers;


    /// <summary>
    /// simulates some event received by the publisher..
    /// one of the things it must do is notify all observers of a 
    /// change in state..
    /// </summary>
    /// <param name="s"></param>
public:

    void ReceiveMessage(std::string s)
    {
        NotifyObservers(s);
    }

    /// <summary>
    /// add an observer/subscriber
    /// </summary>
    /// <param name="iso">the observer/subscriber to add</param>
    void add(ISomeObserver * iso)
    {
        /// only add if we haven't already added it..
        std::set<ISomeObserver *>::iterator iso_iter = m_observers.find (iso);
        if(iso_iter == m_observers.end ())
        {
            m_observers.insert(iso);
        }
    }
    /// <summary>
    /// remove an observer/subscriber
    /// </summary>
    /// <param name="iso">the observer/subscriber to remove</param>
    void remove(ISomeObserver * iso)
    {
        /// only remove if it is already contained ..
        std::set<ISomeObserver *>::iterator iso_iter = m_observers.find (iso);

        if(iso_iter != m_observers.end ())
        {
            m_observers.erase (iso_iter);
        }
    }
    /// <summary>
    /// publish the change event to the observers/subscribers
    /// </summary>
    /// <param name="s">any info we want to pass to the 
    /// observers/subscribers</param>
private:
    
    void NotifyObservers(std::string s)
    {
        for(std::set<ISomeObserver *>::iterator currVal = m_observers.begin ();
            currVal != m_observers.end ();
            currVal++)
        {
            (*currVal)->HandleNotification(s);
        }
    }

};

int _tmain(int argc, _TCHAR* argv[])
{
    SomethingObserved observed;
    SomeObserver observer1("observer1");
    SomeObserver observer2("observer2");

    observed.add(&observer1);
    observed.ReceiveMessage("msg1");

    observed.add(&observer2);
    observed.ReceiveMessage("msg2");

    observed.remove(&observer1);
    observed.ReceiveMessage("msg3");

    observed.remove(&observer2);
    observed.ReceiveMessage("msg4");

	return 0;
}

