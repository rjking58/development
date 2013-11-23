#include <iostream>
// #include <list>
#include <string>



using namespace std;

class Beverage
{
public:    
    enum bev_size
    {
        TALL,
        GRANDE,
        VENTI
    };

    Beverage(string description)
        :   m_description(description)
    {
    }

    virtual ~Beverage()
    {
    }

    virtual string getDescription()
    {
        return m_description;
    }

	virtual bev_size getSize() = 0;
    virtual double cost() = 0;

private:
    string m_description;
};


class CondimentDecorator : public Beverage
{
public:
    CondimentDecorator(string description)
        :    Beverage(description)
    {
    }
    virtual string getDescription() = 0;
    
    string constructDescription(string first, string second)
    {
        string fulldescription = first;
        fulldescription += "," ;
        fulldescription += second;

        return fulldescription;
    }
};

class Espresso : public Beverage
{
public:
    Espresso(bev_size b_size)
        :   Beverage("Espresso"),
			m_b_size(b_size)
    {
    }
    virtual double cost() 
    {
		double cost_by_size = 0.0;

		switch(getSize())
		{
		case TALL:
			cost_by_size = 1.99;
			break;

		case GRANDE:
			cost_by_size = 2.40;
			break;
				
		case VENTI:
			cost_by_size = 2.70;
			break;
		}
        return cost_by_size;
    }

	virtual bev_size getSize()
	{
		return m_b_size;
	}

	virtual string getDescription()
	{
        string descrip;

        switch (m_b_size)
        {
            case TALL   : descrip = "Tall"  ; break;
            case GRANDE : descrip = "Grande"; break;
            case VENTI  : descrip = "Venti" ; break;
        }
		descrip += "(";
		descrip += Beverage::getDescription();
		descrip += ")";

		return descrip;
	}

private:
    bev_size m_b_size;
};

class HouseBlend : public Beverage
{
public:
    HouseBlend(bev_size b_size)
        :	Beverage("House Blend Coffee"),
			m_b_size(b_size)
    {
    }
    virtual double cost() 
    {
		double cost_by_size = 0.0;

		switch(getSize())
		{
		case TALL:
			cost_by_size = 0.89;
			break;

		case GRANDE:
			cost_by_size = 1.19;
			break;
				
		case VENTI:
			cost_by_size = 1.49;
			break;
		}
        return cost_by_size;
    }

	virtual bev_size getSize()
	{
		return m_b_size;
	}

	virtual string getDescription()
	{
        string descrip;

        switch (m_b_size)
        {
            case TALL   : descrip = "Tall"  ; break;
            case GRANDE : descrip = "Grande"; break;
            case VENTI  : descrip = "Venti" ; break;
        }
		descrip += "(";
		descrip += Beverage::getDescription();
		descrip += ")";

		return descrip;
	}
private:
    bev_size m_b_size;
};

class Mocha : public CondimentDecorator
{
public:
    Mocha(Beverage *beverage)
        :   CondimentDecorator("Mocha"),
            m_beverage(beverage)
    {
    }
    virtual ~Mocha()
    {
        delete m_beverage;
    }
    virtual double cost() 
    {
		double cost_by_size = 0.0;

		switch(getSize())
		{
		case TALL:
			cost_by_size = .20;
			break;

		case GRANDE:
			cost_by_size = .23;
			break;
				
		case VENTI:
			cost_by_size = .27;
			break;
		}

        return cost_by_size + m_beverage->cost();
    }
    virtual string getDescription()
    {
        return constructDescription(m_beverage->getDescription(),Beverage::getDescription());
    }

	virtual bev_size getSize()
	{
		return m_beverage->getSize();
	}

private:
    Beverage *m_beverage;
};


class Soy : public CondimentDecorator
{
public:
    Soy(Beverage *beverage)
        :    CondimentDecorator("Soy"),
            m_beverage(beverage)
    {
    }
    virtual ~Soy()
    {
        delete m_beverage;
    }
    virtual double cost() 
    {
		double cost_by_size = 0.0;

		switch(getSize())
		{
		case TALL:
			cost_by_size = .42;
			break;

		case GRANDE:
			cost_by_size = .50;
			break;
				
		case VENTI:
			cost_by_size = .57;
			break;
		}
        return cost_by_size + m_beverage->cost();
    }
    virtual string getDescription()
    {
        return constructDescription(m_beverage->getDescription(),Beverage::getDescription());
    }
	virtual bev_size getSize()
	{
		return m_beverage->getSize();
	}
private:
    Beverage *m_beverage;
};

class Whip : public CondimentDecorator
{
public:
    Whip(Beverage *beverage)
        :   CondimentDecorator("Whip"),
            m_beverage(beverage)
    {
    }
    virtual ~Whip()
    {
        delete m_beverage;
    }
    virtual double cost() 
    {
		double cost_by_size = 0.0;

		switch(getSize())
		{
		case TALL:
			cost_by_size = .12;
			break;

		case GRANDE:
			cost_by_size = .14;
			break;
				
		case VENTI:
			cost_by_size = .16;
			break;
		}
        return cost_by_size + m_beverage->cost();
    }
    virtual string getDescription()
    {
        return constructDescription(m_beverage->getDescription(),Beverage::getDescription());
    }
	virtual bev_size getSize()
	{
		return m_beverage->getSize();
	}
private:
    Beverage *m_beverage;
};


void main()
{
//     list<int> my_list;
//     my_list.push_back(10);
//     my_list.push_back(30);
//     my_list.push_back(100);
// 
//     list<int>::iterator my_list_iter;
//     list<int>::iterator my_list_end;
// 
//     my_list_iter = my_list.begin();
//     my_list_end = my_list.end();
//     for (my_list_iter = my_list.begin(); 
//          my_list_iter != my_list_end;
//          my_list_iter++)
//     {
//         cout << "my_list_iter[" << *my_list_iter << "]\n";
//     }
//     cout << "yo!\n";

    Espresso espresso_cup(Beverage::VENTI);
    cout << "espresso_cup[" << espresso_cup.getDescription() << "]\n";
    cout << "espresso_cup.cost[" << espresso_cup.cost() << "]\n";
    HouseBlend houseblend_cup(Beverage::GRANDE);
    cout << "houseblend_cup[" << houseblend_cup.getDescription() << "]\n";
    cout << "houseblend_cup.cost[" << houseblend_cup.cost() << "]\n";

    Beverage *my_bev = new Espresso(Beverage::VENTI);
    my_bev = new Mocha(my_bev);
    cout << "my_bev[" << my_bev->getDescription() << "]\n";
    cout << "my_bev[" << my_bev->cost() << "]\n";

    cout << "add another mocha.. do it again\n";

    my_bev = new Mocha(my_bev);
    cout << "my_bev[" << my_bev->getDescription() << "]\n";
    cout << "my_bev[" << my_bev->cost() << "]\n";


    my_bev = new Soy(my_bev);
    cout << "my_bev[" << my_bev->getDescription() << "]\n";
    cout << "my_bev[" << my_bev->cost() << "]\n";
    // whip it good!
    my_bev = new Whip(my_bev);
    cout << "my_bev[" << my_bev->getDescription() << "]\n";
    cout << "my_bev[" << my_bev->cost() << "]\n";
    my_bev = new Whip(my_bev);
    cout << "my_bev[" << my_bev->getDescription() << "]\n";
    cout << "my_bev[" << my_bev->cost() << "]\n";


}
