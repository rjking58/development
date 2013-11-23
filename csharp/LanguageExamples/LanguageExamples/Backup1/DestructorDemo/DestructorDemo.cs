using System;

namespace DestructorDemo
{
	/// <summary>
	/// Summary description for Class1.
	/// </summary>
	
	class Destruct
	{
	    private int x;
	    public Destruct(int i)
	    {
	        x = i;
	    }
	    ~Destruct()
	    {
	        Console.WriteLine("Destructing " + x);
	    }
	    public void generator(int i)
	    {
	        Destruct o = new Destruct(i);
	        Console.WriteLine("Creating " + i);
	    }
	}
	
	class DestructDemo
	{
       
		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main(string[] args)
		{
            int count;
            Destruct destruct_ob = new Destruct(0);
            //
			// TODO: Add code to start application here
			//
            for(count=1; count < 10000; count++)
            {
                destruct_ob.generator(count);
            }
            Console.WriteLine(">>>DONE<<<");
		}
	}
}
