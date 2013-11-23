using System;

namespace ParameterSemantics
{
	/// <summary>
	/// Summary description for Class1.
	/// </summary>
	/// 
    class myObj
    {
        private int m_i;
        private string m_myObjName;
        public myObj(int i,string myObjName)
        {
            m_i = i;
            m_myObjName = myObjName;
        }
        public void setI(int i)
        {
            m_i = i;
        }
        public void IAm()
        {
            System.Console.WriteLine("myObj<" + m_myObjName + ">.m_i(" + m_i + ")");
        }
    }
	class Parameter1
	{
		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main(string[] args)
		{
			//
			// TODO: Add code to start application here
			//
			System.Console.WriteLine("mo1 test:::::::::::");
            myObj mo1 = new myObj(1,"mo1");
            myObj mo2 = new myObj(2,"mo2");
            mo1.IAm();
            ObjPassDemo(mo1);
            mo1.IAm();
            mo1.setI(1);
            mo1.IAm();
            // mo2 test.
			System.Console.WriteLine("mo2 test:::::::::::");            
            mo2.IAm();
            ObjPassDemo(mo2);
            mo2.IAm();
            mo2.setI(2);
            mo2.IAm();
            System.Console.WriteLine("mo1 method parameter test::::::::");            
            mo1.IAm();
            mo2.IAm();

            ObjReplaceDemo(mo1);
            mo1.IAm();
		}
        static void ObjPassDemo(myObj mo)
        {
            mo.setI(44);
        }
        // semantics here are purely by value.. 
        // so the pointer being passed in can be changed, but never
        // exits the method.
        // NOT BY REFERENCE
        static void ObjReplaceDemo(myObj mo)
        {
            System.Console.WriteLine("ObjReplaceDemo ENTER>>>");
            mo = new myObj(3,"mo3");
            mo.IAm();
            System.Console.WriteLine("ObjReplaceDemo EXIT<<<");
        }
	}
  
}
