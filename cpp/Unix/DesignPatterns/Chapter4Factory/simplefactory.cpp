#include <iostream>
// #include <list>
#include <string>



using namespace std;

enum pizza_type 
{
    cheese,
    pepperoni,
    clam,
    veggie
};

class Pizza
{
public:
    // always.. so that pointer deletes work properly for derived classes
    virtual ~Pizza()
    {
    }
    virtual void prepare() = 0;
    virtual void bake()    = 0;
    virtual void cut()     = 0;
    virtual void box()     = 0;
};

class CheesePizza : public Pizza
{
public:
    virtual void prepare() 
    {
        cout << "preparing CheesePizza" << endl;
    }
    virtual void bake() 
    {
        cout << "baking CheesePizza" << endl;
    }
    virtual void cut() 
    {
        cout << "cutting CheesePizza" << endl;
    }
    virtual void box() 
    {
        cout << "boxing CheesePizza" << endl;
    }
};

class ClamPizza : public Pizza
{
public:
    virtual void prepare() 
    {
        cout << "preparing ClamPizza" << endl;
    }
    virtual void bake() 
    {
        cout << "baking ClamPizza" << endl;
    }
    virtual void cut() 
    {
        cout << "cutting ClamPizza" << endl;
    }
    virtual void box() 
    {
        cout << "boxing ClamPizza" << endl;
    }
};

class VeggiePizza : public Pizza
{
public:
    virtual void prepare() 
    {
        cout << "preparing VeggiePizza" << endl;
    }
    virtual void bake() 
    {
        cout << "baking VeggiePizza" << endl;
    }
    virtual void cut() 
    {
        cout << "cutting VeggiePizza" << endl;
    }
    virtual void box() 
    {
        cout << "boxing VeggiePizza" << endl;
    }
};

class PepperoniPizza : public Pizza
{
public:
    virtual void prepare() 
    {
        cout << "preparing PepperoniPizza" << endl;
    }
    virtual void bake() 
    {
        cout << "baking PepperoniPizza" << endl;
    }
    virtual void cut() 
    {
        cout << "cutting PepperoniPizza" << endl;
    }
    virtual void box() 
    {
        cout << "boxing PepperoniPizza" << endl;
    }
};



class SimplePizzaFactory
{
public:
    Pizza* CreatePizza(pizza_type p_type)
    {
        Pizza *pizza = 0;

        switch (p_type)
        {
        case cheese:
            pizza = new CheesePizza();
            break;

        case pepperoni:
            pizza = new PepperoniPizza();
            break;

        case clam:
            pizza = new ClamPizza();
            break;

        case veggie:
            pizza = new VeggiePizza();
            break;

        default:
            cout << "unknown type!!" << endl;
            break;
        }
    }

};

void main()
{
    SimplePizzaFactory spf;

    Pizza *pizza = spf.CreatePizza(cheese);

    pizza->prepare();
    pizza->bake();
    pizza->cut();
    pizza->box();



}
