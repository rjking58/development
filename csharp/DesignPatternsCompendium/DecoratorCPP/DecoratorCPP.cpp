// DecoratorCPP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <memory>

/// <summary>
/// a component we will use.. the decorator will
/// only decorate the DoSomething method.. 
/// </summary>
class AbstractComponent
{
public: 
    virtual void DoSomething() = 0;

    virtual void DoSomethingElse() = 0;
};

/// <summary>
/// our basic undecorated object.
/// </summary>
class ConcreteComponent : public AbstractComponent
{
public:
    virtual void DoSomething()
    {
        std::cout << "DoSomething" << std::endl;
    }

    virtual void DoSomethingElse()
    {
        std::cout << "DoSomethingElse" << std::endl;
    }
};

/// <summary>
/// abstract definition of the decorator.. we simply forward the
/// non decorated method in this class, and leave the DoSomething() 
/// method untouched, since subclasses will decorate it as needed
/// </summary>
class ComponentDecorator :  public AbstractComponent
{
private:
    /// we don't own this, so never delete
    AbstractComponent * m_component;

public:
    ComponentDecorator(AbstractComponent * ac) : m_component(0)
    {
        m_component = ac;
    }

    // simply forward this, we aren't decorating
    virtual void DoSomethingElse()
    {
        m_component->DoSomethingElse();
    }
};

/// <summary>
/// a 'post decorator'.  Here, we do something AFTER the call to
/// the decorated behavior
/// </summary>
class Post1Decorator : public ComponentDecorator
{
private:
    /// we don't own this, so never delete
    AbstractComponent * m_component;

public:
    Post1Decorator(AbstractComponent * ac) :    ComponentDecorator(ac),
                                                m_component(0)
    {
        m_component = ac;
    }

    /// <summary>
    ///  the decorated behavior
    /// </summary>
    virtual void DoSomething()
    {
        /// the standard behavior
        m_component->DoSomething();
        /// our decoration.. 
        std::cout << "post1" << std::endl;
    }
};

/// <summary>
/// a 'pre decorator'.  Here, we do something BEFORE the call to
/// the decorated behavior
/// </summary>
class Pre1Decorator : public ComponentDecorator
{
private:
    /// we don't own this, so never delete
    AbstractComponent * m_component;

public:
    Pre1Decorator(AbstractComponent * ac):  ComponentDecorator(ac),
                                            m_component(0)
    {
        m_component = ac;
    }

    /// <summary>
    ///  the decorated behavior
    /// </summary>
    virtual void DoSomething()
    {
        /// our decoration.. 
        std::cout << "pre1" << std::endl;
        /// the standard behavior
        m_component->DoSomething();
    }
};

/// <summary>
/// a 'pre decorator'.  Here, we do something BEFORE the call to
/// the decorated behavior
/// </summary>
class Pre2Decorator : public ComponentDecorator
{
private:
    /// we don't own this, so never delete
    AbstractComponent * m_component;

public:
    Pre2Decorator(AbstractComponent * ac):  ComponentDecorator(ac),
                                            m_component(0)
    {
        m_component = ac;
    }

    /// <summary>
    ///  the decorated behavior
    /// </summary>
    virtual void DoSomething()
    {
        /// our decoration.. 
        std::cout << "pre2" << std::endl;
        /// the standard behavior
        m_component->DoSomething();
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    std::auto_ptr<AbstractComponent> ac(new ConcreteComponent);

    {
        std::auto_ptr<AbstractComponent> Pre1Dec(new Pre1Decorator(ac.get()));
        std::auto_ptr<AbstractComponent> Pre2Dec(new Pre2Decorator(Pre1Dec.get()));
        std::auto_ptr<AbstractComponent> Post1Dec(new Post1Decorator(Pre2Dec.get()));

        Post1Dec->DoSomething();
        Post1Dec->DoSomethingElse();
    }
    {
        std::auto_ptr<AbstractComponent> Post1Dec(new Post1Decorator(ac.get()));
        std::auto_ptr<AbstractComponent> Pre2Dec(new Pre2Decorator(Post1Dec.get()));
        std::auto_ptr<AbstractComponent> Pre1Dec(new Pre1Decorator(Pre2Dec.get()));
        Pre1Dec->DoSomething ();
        Pre1Dec->DoSomethingElse ();
    }

	return 0;
}

