using System;

namespace ClassTest1
{

	public class myStupidClass
	{
		private int mId;
		private bool mTouched = false;
		public myStupidClass(int id)
		{
			mId = id; 
		}
		public void whoAmI()
		{
			System.Console.Write("myStupidClass #" + mId + " was ");
			if (mTouched)
			{
				System.Console.WriteLine("touched");
			}
			else
			{
				System.Console.WriteLine("NOT touched");
			}
		}
		public void touch()
		{
			mTouched = true;
		}
	}
	/// <summary>
	/// Summary description for Class1.
	/// </summary>
	class Class1
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
			myStupidClass msc1 = new myStupidClass(30);
			myStupidClass msc2 = new myStupidClass(43);

			msc1.whoAmI();
			msc2.whoAmI();
			touch_stupid(msc1);
			msc1.whoAmI();
			msc2.whoAmI();

		}
		public static void touch_stupid(myStupidClass msc)
		{
			msc.touch();
		}

	}
}
