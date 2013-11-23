#include <iostream>
#include <vector>
#include <algorithm>
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

typedef vector<string> strVector;

class printStrVec
{
public:
    void operator()(string s)
    {
        cout << s << endl;
    }
};

class Pizza
{
private:
    string m_name;
    string m_dough;
    string m_sauce;
    strVector m_toppings;


public:
    // always.. so that pointer deletes work properly for derived classes
    Pizza(string name,
          string dough,
          string sauce)
        :   m_name(name),
            m_dough(dough),
            m_sauce(sauce)
    {
    }
    virtual ~Pizza()
    {
    }
    void prepare()
    {
        cout << "Preparing: " << m_name << endl;
        cout << "Tossing: " << m_dough << " dough" << endl;
        cout << "Adding: " << m_sauce << " type sauce" << endl;
        cout << "Adding toppings:" << endl;
        for_each(m_toppings.begin(),
                 m_toppings.end(),
                 printStrVec());

    }
    void bake()
    {
        cout << "Bake at 25 minutes for 350" << endl;
    }
    void cut()
    {
        cout << "Cutting the pizza into diagonal slices" << endl;
    }
    void box()
    {
        cout << "Boxing in official 'PizzaStore' box" << endl;
    }
    void addTopping(string topping)
    {
        m_toppings.push_back(topping);
    }

    string getName()
    {
        return m_name;
    }
};

class NYStyleCheesePizza : public Pizza
{
public:
    NYStyleCheesePizza()
        :   Pizza("NY Style Sauce and Cheese Pizza",
                  "Thin Crust Dough",
                  "Marinara Sauce")
    {
        addTopping("Grated Reggiano Cheese");
    }
};

class NYStyleClamPizza : public Pizza
{
public:
    NYStyleClamPizza()
        :   Pizza("NY Style Sauce and Clam Pizza",
                  "Thin Crust Dough",
                  "Marinara Sauce")
    {
        addTopping("Grated Reggiano Cheese");
        addTopping("Clams");
    }
};

class NYStyleVeggiePizza : public Pizza
{
public:
    NYStyleVeggiePizza()
        :   Pizza("NY Style Sauce and Veggie Pizza",
                  "Thin Crust Dough",
                  "Marinara Sauce")
    {
        addTopping("Grated Reggiano Cheese");
        addTopping("carrots");
        addTopping("peas");
    }
};

class NYStylePepperoniPizza : public Pizza
{
public:
    NYStylePepperoniPizza()
        :   Pizza("NY Style Sauce and Pepperoni Pizza",
                  "Thin Crust Dough",
                  "Marinara Sauce")
    {
        addTopping("Grated Reggiano Cheese");
        addTopping("Pepperoni");
    }
};



class ChicagoStyleCheesePizza : public Pizza
{
public:
    ChicagoStyleCheesePizza()
        :   Pizza("Chicago Style Deep Dish Cheese Pizza",
                  "Extra Thick Crust Dough",
                  "Plum Tomato Sauce")
    {
        addTopping("Shredded Mozzarella Cheese");
    }
};

class ChicagoStyleClamPizza : public Pizza
{
public:
    ChicagoStyleClamPizza()
        :   Pizza("Chicago Style Deep Dish Clam Pizza",
                  "Extra Thick Crust Dough",
                  "Plum Tomato Sauce")
    {
        addTopping("Shredded Mozzarella Cheese");
        addTopping("Clams");
    }
};

class ChicagoStyleVeggiePizza : public Pizza
{
public:
    ChicagoStyleVeggiePizza()
        :   Pizza("Chicago Style Deep Dish Veggie Pizza",
                  "Extra Thick Crust Dough",
                  "Plum Tomato Sauce")
    {
        addTopping("Shredded Mozzarella Cheese");
        addTopping("cabbage");
        addTopping("beets");
    }
};

class ChicagoStylePepperoniPizza : public Pizza
{
public:
    ChicagoStylePepperoniPizza()
        :   Pizza("Chicago Style Deep Dish Pepperoni Pizza",
                  "Extra Thick Crust Dough",
                  "Plum Tomato Sauce")
    {
        addTopping("Shredded Mozzarella Cheese");
        addTopping("Pepperoni");
    }
};



class PizzaStore
{
public:
    virtual ~PizzaStore()
    {
    }

    virtual Pizza *createPizza(pizza_type ptype) = 0;
    Pizza * orderPizza(pizza_type ptype)
    {
        Pizza * pizza = createPizza(ptype);

        pizza->prepare();
        pizza->bake();
        pizza->cut();
        pizza->box();

        return pizza;
    }
};

class NYStylePizzaStore : public PizzaStore
{
public:
    virtual Pizza* createPizza(pizza_type ptype) 
    {
        Pizza *pizza = 0;

        switch (ptype)
        {
        case cheese:
            pizza = new NYStyleCheesePizza();
            break;

        case pepperoni:
            pizza = new NYStylePepperoniPizza();
            break;

        case clam:
            pizza = new NYStyleClamPizza();
            break;

        case veggie:
            pizza = new NYStyleVeggiePizza();
            break;

        default:
            cout << "unknown type!!" << endl;
            break;
        }

        return pizza;
    }
};

class ChicagoStylePizzaStore : public PizzaStore
{
public:
    virtual Pizza* createPizza(pizza_type ptype) 
    {
        Pizza *pizza = 0;

        switch (ptype)
        {
        case cheese:
            pizza = new ChicagoStyleCheesePizza();
            break;

        case pepperoni:
            pizza = new ChicagoStylePepperoniPizza();
            break;

        case clam:
            pizza = new ChicagoStyleClamPizza();
            break;

        case veggie:
            pizza = new ChicagoStyleVeggiePizza();
            break;

        default:
            cout << "unknown type!!" << endl;
            break;
        }

        return pizza;
    }
};


void main()
{

    NYStylePizzaStore nysps;

    ChicagoStylePizzaStore csps;

    Pizza *pizza = nysps.orderPizza(clam);
    delete pizza;

    pizza = csps.orderPizza(veggie);
    delete pizza;

}
