using System;
using System.Collections.Generic;
using System.Text;

namespace Decorator
{

    public abstract class Beverage
    {
        public enum bev_size
        {
            TALL,
            GRANDE,
            VENTI
        }

        public Beverage(String description)
        {
            m_description = description;
        }

        ~Beverage()
        {
        }
    
        public String getBaseDescription()
        {
            return m_description;
        }

        public abstract String getDescription();
    	public abstract bev_size getSize();
        public abstract double cost();
    
        private String m_description;
    }

    public abstract class CondimentDecorator : Beverage
    {
        public CondimentDecorator(String description) : base(description)
        {
        }

      
        public String constructDescription(String first, String second)
        {
            String fulldescription = first;
            fulldescription += "," ;
            fulldescription += second;
    
            return fulldescription;
        }

        public override abstract String getDescription();
    }

    public class Espresso : Beverage
    {
        public Espresso(bev_size b_size)
            :   base ("Espresso")
        {
            m_b_size = b_size;
        }
        public override double cost() 
        {
    		double cost_by_size = 0.0;
    
    		switch(getSize())
    		{
    		case Beverage.bev_size.TALL:
    			cost_by_size = 1.99;
    			break;

            case Beverage.bev_size.GRANDE:
    			cost_by_size = 2.40;
    			break;

            case Beverage.bev_size.VENTI:
    			cost_by_size = 2.70;
    			break;
    		}
            return cost_by_size;
        }
    
    	public override bev_size getSize()
    	{
    		return m_b_size;
    	}

        public override String getDescription()
    	{
            String descrip = "";
    
            switch (m_b_size)
            {
                case Beverage.bev_size.TALL: descrip = "Tall"; break;
                case Beverage.bev_size.GRANDE: descrip = "Grande"; break;
                case Beverage.bev_size.VENTI: descrip = "Venti"; break;
            }
    		descrip += "(";
    		descrip += getBaseDescription();
    		descrip += ")";
    
    		return descrip;
    	}
    
        private bev_size m_b_size;
    }



    public class HouseBlend : Beverage
    {

        public HouseBlend(bev_size b_size)
            :	base("House Blend Coffee")
        {
            m_b_size = b_size;
        }
        public override double cost() 
        {
    		double cost_by_size = 0.0;
    
    		switch(getSize())
    		{
    		case Beverage.bev_size.TALL:
    			cost_by_size = 0.89;
    			break;
    
    		case Beverage.bev_size.GRANDE:
    			cost_by_size = 1.19;
    			break;
    				
    		case Beverage.bev_size.VENTI:
    			cost_by_size = 1.49;
    			break;
    		}
            return cost_by_size;
        }
    
    	public override bev_size getSize()
    	{
    		return m_b_size;
    	}
    
    	public override string getDescription()
    	{
            string descrip = "";
    
            switch (m_b_size)
            {
                case Beverage.bev_size.TALL   : descrip = "Tall"  ; break;
                case Beverage.bev_size.GRANDE : descrip = "Grande"; break;
                case Beverage.bev_size.VENTI  : descrip = "Venti" ; break;
            }
    		descrip += "(";
    		descrip += getBaseDescription();
    		descrip += ")";
    
    		return descrip;
    	}
        
        private bev_size m_b_size;
    }



    public class Mocha : CondimentDecorator
    {
        public Mocha(Beverage beverage)
            :   base("Mocha")
        {
            m_beverage = beverage;
        }
        public override double cost() 
        {
    		double cost_by_size = 0.0;
    
    		switch(getSize())
    		{
            case Beverage.bev_size.TALL:
    			cost_by_size = .20;
    			break;

            case Beverage.bev_size.GRANDE:
    			cost_by_size = .23;
    			break;

            case Beverage.bev_size.VENTI:
    			cost_by_size = .27;
    			break;
    		}
    
            return cost_by_size + m_beverage.cost();
        }
        public override string getDescription()
        {
            return constructDescription(m_beverage.getDescription(),getBaseDescription());
        }
    
    	public override bev_size getSize()
    	{
    		return m_beverage.getSize();
    	}
    
        Beverage m_beverage;
    };

    public class Soy : CondimentDecorator
    {
        public Soy(Beverage beverage)
            :    base("Soy")
        {
            m_beverage = beverage;
        }
        public override double cost() 
        {
    		double cost_by_size = 0.0;
    
    		switch(getSize())
    		{
    		case Beverage.bev_size.TALL:
    			cost_by_size = .42;
    			break;
    
    		case Beverage.bev_size.GRANDE:
    			cost_by_size = .50;
    			break;
    				
    		case Beverage.bev_size.VENTI:
    			cost_by_size = .57;
    			break;
    		}
            return cost_by_size + m_beverage.cost();
        }
        public override string getDescription()
        {
            return constructDescription(m_beverage.getDescription(),getBaseDescription());
        }
    	public override bev_size getSize()
    	{
    		return m_beverage.getSize();
    	}
        private Beverage m_beverage;
    }
    
    public class Whip : CondimentDecorator
    {
        public Whip(Beverage beverage)
            :   base("Whip")
        {
            m_beverage = beverage;
        }
        public override double cost() 
        {
    		double cost_by_size = 0.0;
    
    		switch(getSize())
    		{
    		case Beverage.bev_size.TALL:
    			cost_by_size = .12;
    			break;
    
    		case Beverage.bev_size.GRANDE:
    			cost_by_size = .14;
    			break;
    				
    		case Beverage.bev_size.VENTI:
    			cost_by_size = .16;
    			break;
    		}
            return cost_by_size + m_beverage.cost();
        }
        public override string getDescription()
        {
            return constructDescription(m_beverage.getDescription(),getBaseDescription());
        }
    	public override bev_size getSize()
    	{
    		return m_beverage.getSize();
    	}
        
        private Beverage m_beverage;
    }



    class Program
    {
        static void Main(string[] args)
        {
            System.Console.WriteLine("woof!");

            Beverage my_bev = new Espresso(Beverage.bev_size.VENTI);
            System.Console.WriteLine("my_bev[" + my_bev.getDescription() + "]");
            System.Console.WriteLine("my_bev.cost[" + my_bev.cost() + "]");

            my_bev = new Mocha(my_bev);
            System.Console.WriteLine("my_bev[" + my_bev.getDescription() + "]");
            System.Console.WriteLine("my_bev.cost[" + my_bev.cost() + "]");
            
            my_bev = new Mocha(my_bev);
            System.Console.WriteLine("my_bev[" + my_bev.getDescription() + "]");
            System.Console.WriteLine("my_bev.cost[" + my_bev.cost() + "]");

            my_bev = new Soy(my_bev);
            System.Console.WriteLine("my_bev[" + my_bev.getDescription() + "]");
            System.Console.WriteLine("my_bev.cost[" + my_bev.cost() + "]");

            my_bev = new Whip(my_bev);
            System.Console.WriteLine("my_bev[" + my_bev.getDescription() + "]");
            System.Console.WriteLine("my_bev.cost[" + my_bev.cost() + "]");

            my_bev = new Whip(my_bev);
            System.Console.WriteLine("my_bev[" + my_bev.getDescription() + "]");
            System.Console.WriteLine("my_bev.cost[" + my_bev.cost() + "]");

        }
    }
}
