#include <iostream>
#include <list>
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


class veggies
{
public:
    virtual ~veggies()
    {
    }
    virtual string getName() = 0;
};

class Garlic : public veggies
{
public:
    virtual string getName() 
    {
        return "Garlic";
    }
};
class RedPepper : public veggies
{
public:
    virtual string getName() 
    {
        return "RedPepper";
    }
};
class Mushroom : public veggies
{
public:
    virtual string getName() 
    {
        return "Mushroom";
    }
};
class Onion : public veggies
{
public:
    virtual string getName() 
    {
        return "Onion";
    }
};
class Beets : public veggies
{
public:
    virtual string getName() 
    {
        return "Beets";
    }
};
class Peas : public veggies
{
public:
    virtual string getName() 
    {
        return "Peas";
    }
};
class Asparagus : public veggies
{
public:
    virtual string getName() 
    {
        return "Asparagus";
    }
};
class Dough 
{
public:
    virtual ~Dough()
    {
    }
    virtual string getName() = 0;
};

class ThinCrustDough : public Dough
{
public:
    virtual string getName() 
    {
        return "Thin Crust Dough";
    }
};
class ThickCrustDough : public Dough
{
public:
    virtual string getName() 
    {
        return "Thick Crust Dough";
    }
};


class Sauce
{
public:
    virtual ~Sauce()
    {
    }
    virtual string getName() = 0;
};

class MarinaraSauce : public Sauce
{
public:
    virtual string getName() 
    {
        return "Marinara Sauce";
    }
};

class PlumTomatoSauce : public Sauce
{
public:
    virtual string getName() 
    {
        return "Plum Tomato Sauce";
    }
};

class Cheese
{
public:
    virtual ~Cheese()
    {
    }
    virtual string getName() = 0;

};

class ReggianoCheese : public Cheese
{
public:
    virtual string getName() 
    {
        return "Reggiano Cheese";
    }
};
class MozzarellaCheese : public Cheese
{
public:
    virtual string getName() 
    {
        return "Mozzarella Cheese";
    }
};


class Clams
{
public:
    virtual ~Clams()
    {
    }
    virtual string getName() = 0;

};

class FreshClams : public Clams
{
public:
    virtual string getName() 
    {
        return "Fresh Clams";
    }
};

class FrozenClams : public Clams
{
public:
    virtual string getName() 
    {
        return "Frozen Clams";
    }
};

class Pepperoni
{
public:
    Pepperoni()
    {
    }
    string getName()
    {
        return "Pepperoni";
    }

};


typedef vector<string>  strVector;
typedef list<veggies *>   veggieList;


class printVeggies
{
public:
    void operator()(veggies *v)
    {
        cout << v->getName() << endl;
    }
};
class deleteVeggies
{
public:
    void operator()(veggies *v)
    {
        delete v;
    }
};




class PizzaIngredientFactory
{
public:
    virtual Dough * createDough() = 0;
    virtual Sauce * createSauce() = 0;
    virtual Cheese * createCheese() = 0;
    virtual veggieList * createVeggies() = 0;
    virtual Pepperoni * createPepperoni() = 0;
    virtual Clams * createClams() = 0;
};

class NYPizzaIngredientFactory : public PizzaIngredientFactory
{
public:
    virtual Dough* createDough() 
    {
        return new ThinCrustDough();
    }
    virtual Sauce* createSauce() 
    {
        return new MarinaraSauce();
    }
    virtual Cheese* createCheese() 
    {
        return new ReggianoCheese();
    }
    virtual veggieList* createVeggies() 
    {
        veggieList *vlist= new veggieList;
        vlist->push_back(new Garlic());
        vlist->push_back(new Onion());
        vlist->push_back(new Mushroom());
        vlist->push_back(new RedPepper());

        return vlist;
    }
    virtual Pepperoni* createPepperoni() 
    {
        return new Pepperoni();
    }
    virtual Clams* createClams() 
    {
        return new FreshClams();
    }
};

class ChicagoPizzaIngredientFactory : public PizzaIngredientFactory
{
public:
    virtual Dough* createDough() 
    {
        return new ThickCrustDough();
    }
    virtual Sauce* createSauce() 
    {
        return new PlumTomatoSauce();
    }
    virtual Cheese* createCheese() 
    {
        return new MozzarellaCheese();
    }
    virtual veggieList* createVeggies() 
    {
        veggieList *vlist= new veggieList;
        vlist->push_back(new Beets());
        vlist->push_back(new Peas());
        vlist->push_back(new Asparagus());

        return vlist;
    }
    virtual Pepperoni* createPepperoni() 
    {
        return new Pepperoni();
    }
    virtual Clams* createClams() 
    {
        return new FrozenClams();
    }
};



class Pizza
{
private:
    string      m_name;

public:
    // always.. so that pointer deletes work properly for derived classes
    Pizza(string name)
        :   m_name(name)
    {
    }
    virtual ~Pizza()
    {
    }

    virtual void prepare() = 0;
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

    string getName()
    {
        return m_name;
    }

};

class CheesePizza : public Pizza
{
private:
    Dough                   *m_dough;
    Sauce                   *m_sauce;
    Cheese                  *m_cheese;

    PizzaIngredientFactory  *m_ingred_fact;
public:
    CheesePizza(string name, PizzaIngredientFactory *ingred_fact)
        :   Pizza(name),
            m_ingred_fact(ingred_fact)
    {
        m_dough = m_ingred_fact->createDough();
        m_sauce = m_ingred_fact->createSauce();
        m_cheese = m_ingred_fact->createCheese();
    }

    ~CheesePizza()
    {
        delete m_dough; 
        delete m_sauce; 
        delete m_cheese;
        delete m_ingred_fact;
    }

    virtual void prepare()
    {
        cout << "Tossing Dough:" << m_dough->getName() << endl;
        cout << "Adding Sauce:" << m_sauce->getName() << endl;
        cout << "Adding Cheese:" << m_cheese->getName() << endl;
    }

};

class VeggiePizza : public Pizza
{
private:
    Dough                   *m_dough;
    Sauce                   *m_sauce;
    Cheese                  *m_cheese;
    veggieList              *m_veggielist;


    PizzaIngredientFactory  *m_ingred_fact;
public:
    VeggiePizza(string name, PizzaIngredientFactory *ingred_fact)
        :   Pizza(name),
            m_ingred_fact(ingred_fact)
    {
        m_dough = m_ingred_fact->createDough();
        m_sauce = m_ingred_fact->createSauce();
        m_cheese = m_ingred_fact->createCheese();
        m_veggielist = m_ingred_fact->createVeggies();
    }

    ~VeggiePizza()
    {
        delete m_dough; 
        delete m_sauce; 
        delete m_cheese;
        delete m_ingred_fact;

        for_each(m_veggielist->begin(),
                 m_veggielist->end(),
                 deleteVeggies());
        
        delete m_veggielist;
    }
    virtual void prepare()
    {
        cout << "Tossing Dough:" << m_dough->getName() << endl;
        cout << "Adding Sauce:" << m_sauce->getName() << endl;
        cout << "Adding Cheese:" << m_cheese->getName() << endl;
        cout << "Adding Veggies:" << endl;
        for_each(m_veggielist->begin(),
                 m_veggielist->end(),
                 printVeggies());

    }

};


class ClamPizza : public Pizza
{
private:
    Dough                   *m_dough;
    Sauce                   *m_sauce;
    Cheese                  *m_cheese;
    Clams                   *m_clams;

    PizzaIngredientFactory  *m_ingred_fact;
public:
    ClamPizza(string name, PizzaIngredientFactory *ingred_fact)
        :   Pizza(name),
            m_ingred_fact(ingred_fact)
    {
        m_dough = m_ingred_fact->createDough();
        m_sauce = m_ingred_fact->createSauce();
        m_cheese = m_ingred_fact->createCheese();
        m_clams = m_ingred_fact->createClams();
    }

    ~ClamPizza()
    {
        delete m_dough; 
        delete m_sauce; 
        delete m_cheese;
        delete m_clams;
        delete m_ingred_fact;
    }

    virtual void prepare()
    {
        cout << "Tossing Dough:" << m_dough->getName() << endl;
        cout << "Adding Sauce:" << m_sauce->getName() << endl;
        cout << "Adding Cheese:" << m_cheese->getName() << endl;
        cout << "Adding Clams:" << m_clams->getName() << endl;
    }

};

class PepperoniPizza : public Pizza
{
private:
    Dough                   *m_dough;
    Sauce                   *m_sauce;
    Cheese                  *m_cheese;
    Pepperoni               *m_pepperoni;

    PizzaIngredientFactory  *m_ingred_fact;
public:
    PepperoniPizza(string name, PizzaIngredientFactory *ingred_fact)
        :   Pizza(name),
            m_ingred_fact(ingred_fact)
    {
        m_dough = m_ingred_fact->createDough();
        m_sauce = m_ingred_fact->createSauce();
        m_cheese = m_ingred_fact->createCheese();
        m_pepperoni = m_ingred_fact->createPepperoni();
    }

    ~PepperoniPizza()
    {
        delete m_dough; 
        delete m_sauce; 
        delete m_cheese;
        delete m_pepperoni;
        delete m_ingred_fact;
    }

    virtual void prepare()
    {
        cout << "Tossing Dough:" << m_dough->getName() << endl;
        cout << "Adding Sauce:" << m_sauce->getName() << endl;
        cout << "Adding Cheese:" << m_cheese->getName() << endl;
        cout << "Adding Pepperoni:" << m_pepperoni->getName() << endl;
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

        cout << "Making a " << pizza->getName() << endl;
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
            pizza = new CheesePizza("NY Style Cheese Pizza",new NYPizzaIngredientFactory());
            break;

        case pepperoni:
            pizza = new PepperoniPizza("NY Style Pepperoni Pizza",new NYPizzaIngredientFactory());
            break;

        case clam:
            pizza = new ClamPizza("NY Style Clam Pizza",new NYPizzaIngredientFactory());
            break;

        case veggie:
            pizza = new VeggiePizza("NY Style Veggie Pizza",new NYPizzaIngredientFactory());
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
            pizza = new CheesePizza("Chicago Deep Dish Cheese Pizza",new ChicagoPizzaIngredientFactory());
            break;

        case pepperoni:
            pizza = new PepperoniPizza("Chicago Deep Dish Pepperoni Pizza",new ChicagoPizzaIngredientFactory());
            break;

        case clam:
            pizza = new ClamPizza("Chicago Deep Dish Clam Pizza",new ChicagoPizzaIngredientFactory());
            break;

        case veggie:
            pizza = new VeggiePizza("Chicago Deep Dish Veggie Pizza",new ChicagoPizzaIngredientFactory());
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

    Pizza *pizza = nysps.orderPizza(cheese);
    delete pizza;

    cout << endl;
    cout << endl;

    pizza = nysps.orderPizza(veggie);
    delete pizza;

    cout << endl;
    cout << endl;

    pizza = nysps.orderPizza(clam);
    delete pizza;

    cout << endl;
    cout << endl;

    pizza = nysps.orderPizza(pepperoni);
    delete pizza;

    cout << endl;
    cout << endl;

    pizza = csps.orderPizza(cheese);
    delete pizza;

    cout << endl;
    cout << endl;

    pizza = csps.orderPizza(veggie);
    delete pizza;

    cout << endl;
    cout << endl;

    pizza = csps.orderPizza(clam);
    delete pizza;

    cout << endl;
    cout << endl;

    pizza = csps.orderPizza(pepperoni);
    delete pizza;


//    pizza = csps.orderPizza(veggie);
//    delete pizza;

}

