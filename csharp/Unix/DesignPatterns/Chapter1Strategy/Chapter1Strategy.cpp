// This is the main project file for VC++ application project 
// generated using an Application Wizard.

#include <iostream>


class FlyBehavior
{
public:
    virtual ~FlyBehavior() {}
    virtual void fly() = 0;
};

class FlyWithWings : public FlyBehavior
{
public:
    virtual void fly()
    {
        std::cout << "wings flapping..\n";
    }
};

class FlyNoWay : public FlyBehavior
{
public:
    virtual void fly()
    {
        std::cout << "I can't fly!!!\n";
    }
};

class QuackBehavior
{
public:
    virtual ~QuackBehavior() {}
    virtual void quack() = 0;

};

class Quack : public QuackBehavior
{
public:
    virtual void quack()
    {
        std::cout << "quack!!!\n";
    }
};

class MuteQuack : public QuackBehavior
{
public:
    virtual void quack()
    {
        std::cout << "...silence...\n";
    }
};

class Squeak : public QuackBehavior
{
public:
    virtual void quack()
    {
        std::cout << "Squeak squeak!!\n";
    }
};

class Duck
{
private:
	FlyBehavior     *m_flyBehavior;
	QuackBehavior   *m_quackBehavior;
public:
    Duck(FlyBehavior *flyBehavior,
         QuackBehavior *quackBehavior)
         :  m_flyBehavior(flyBehavior),
            m_quackBehavior(quackBehavior)

    {
    }
    ~Duck()
    {
        delete m_flyBehavior;
        delete m_quackBehavior;
    }
    void performFly()
    {
        if (m_flyBehavior)
        {
            m_flyBehavior->fly();
        }
    }

    void performQuack()
    {
        if (m_quackBehavior)
        {
            m_quackBehavior->quack();
        }
    }

    void swim()
    {
        std::cout << "All ducks float.. even decoys!!\n";
    }

    void setQuackBehavior(QuackBehavior *quackBehavior)
    {
        delete m_quackBehavior;
        m_quackBehavior = quackBehavior;
    }
    void setFlyBehavior(FlyBehavior *flyBehavior)
    {
        delete m_flyBehavior;
        m_flyBehavior = flyBehavior;
    }

};

int main()
{
    // TODO: Please replace the sample code below with your own.

	// std::cout << "xx\n";

	Duck mallard(new FlyWithWings,new Quack);

    mallard.performFly();
    mallard.performQuack();
    mallard.swim();

    // show dynamic runtime behavior..
    mallard.performFly();
    mallard.setFlyBehavior(new FlyNoWay);
    mallard.performFly();

	 
    
	return 0;
}


