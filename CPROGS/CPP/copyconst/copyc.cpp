#include <iostream.h>
#include <stdio.h>
#include <string.h>


////////////////////////////////////////////////////////
// program to exercise understanding of copy constructor/assignment operator
// mechanics...
////////////////////////////////////////////////////////



class BaseClass
{
   private:
      static int	ms_Unique_Id_track;
	  int			ms_Unique_Id;
      int			*m_int_p;   // pointer to int..
      char			*m_name;    // pointer to char...

      ////////////////////////////////////////////////////////
      // make default constructor illegal to call.
      ////////////////////////////////////////////////////////
      BaseClass() { };

   public:

            
      ////////////////////////////////////////////////////////
      // constructor:: name + initialization value.
      ////////////////////////////////////////////////////////
      
      BaseClass(int i, char * name);
      virtual ~BaseClass();
      
      ////////////////////////////////////////////////////////
      // copy constructor.
      ////////////////////////////////////////////////////////
      BaseClass(BaseClass &BaseClass_ref);
      int get_int(void)
      {
         return *m_int_p;
      }
      
      ////////////////////////////////////////////////////////
      // assignment operator.
      ////////////////////////////////////////////////////////
      BaseClass & operator=(BaseClass &BaseClass_ref);

                             
      void who_am_i(void)
      {
		 cout << "---------------------------------------------------" << endl;
		 cout << "***************************************************" << endl;
		 cout << "ms_Unique_Id == " << ms_Unique_Id << endl;
         cout << "Name @ " << &m_name << " = " << m_name << endl;
         cout << "*m_int_p @" << m_int_p << " == " << *m_int_p << endl ;
		 cout << "***************************************************" << endl;
		 cout << "---------------------------------------------------" << endl;
      }



};

int	BaseClass::ms_Unique_Id_track = 0;

BaseClass::BaseClass(int i,char *name)
{
   cout << "Normal constructor called" << endl;
   ms_Unique_Id = ms_Unique_Id_track;
   ms_Unique_Id_track++;

   
   // new integer....
   m_int_p = new int;
   *m_int_p = i;

   // string... REMEMBER THE NULLS!                     
   m_name = new char [strlen(name)+1];
   strcpy (m_name,name);

   // show our progress...
   who_am_i();
   cout << "Normal constructor end" << endl << endl;

}
BaseClass::~BaseClass()
{
   cout << "Normal destructor called" << endl;
   who_am_i();
   delete m_int_p;
   delete[] m_name;
   cout << "m_int_p deleted" << endl;
   cout << "Normal destructor end" << endl << endl;
}


BaseClass::BaseClass(BaseClass &BaseClass_ref)
{
   cout << "copy constructor called" << endl;

   ms_Unique_Id = ms_Unique_Id_track;
   ms_Unique_Id_track++;
   
   // create some default values so that activity is shown...
   m_int_p = new int;
   *m_int_p = 0;
   m_name = new char [2];
   strcpy(m_name,"z");

   // show our current state.
   who_am_i();
   BaseClass_ref.who_am_i();
   
   // assign the int over to our new object..
   *m_int_p = *(BaseClass_ref.m_int_p);

   // copy the string to a new string in our new object..                                             
   delete [] m_name;
   
   m_name = new char [ strlen(BaseClass_ref.m_name) + 1 + 10];
   strcpy(m_name,"Copy of ");
   strcat(m_name, BaseClass_ref.m_name);

   // show our current state...
   who_am_i();
   BaseClass_ref.who_am_i();

   cout << "copy constructor end" << endl << endl;
}

BaseClass & BaseClass::operator=(BaseClass &BaseClass_ref)
{
   cout << "assignment operator called" << endl;

   who_am_i();
   BaseClass_ref.who_am_i();

   *m_int_p = *(BaseClass_ref.m_int_p);

   delete [] m_name;
   m_name = new char [ strlen(BaseClass_ref.m_name) + 10];
   strcpy(m_name,"Copy of ");
   strcat(m_name, BaseClass_ref.m_name);


   who_am_i();
   BaseClass_ref.who_am_i();

   cout << "assignment operator end" << endl << endl;

   return *this;
}

BaseClass * copy_invoker(BaseClass bc_o)
{
   BaseClass *bcp;

   cout << "enter copy_invoker" << endl << endl;
   cout << "making new pointer..." << endl << endl;

   // invoke constructor during a new operation...                               
   bcp = new BaseClass(1,"invoker created");

   cout << "copy bc_o to the new pointer..." << endl << endl;
   
   // invoke the assignment operator.
   *bcp = bc_o;

   cout << "exit copy_invoker" << endl << endl;

   return bcp;
}

void main(void)
{
   // invoke normal constructor
   BaseClass   bc_a(2,"bc_a");
   // invoke normal constructor
   BaseClass   bc_b(5,"bc_b");
   // invoke copy constructor
   BaseClass   bc_c = bc_b;
   BaseClass   *bcp_a;
   BaseClass   *bcp_b;
   BaseClass   *bcp_created;
 
   // setup pointers...
   cout << "setting up main pointers" << endl;
   bcp_a = &bc_a;
   bcp_b = bcp_a;
   cout << "done setting up main pointers" << endl;

   cout << "calling copy_invoker" << endl << endl;
   bcp_created = copy_invoker(bc_a);
   cout << "deleting bcp_created" << endl << endl;

   cout << " bcp_created" << endl;
   bcp_created->who_am_i();

   delete bcp_created;

   cout << " bc_a" << endl;
   bc_a.who_am_i();
   cout << " bc_b" << endl;
   bc_b.who_am_i();
   cout << " bc_c" << endl;
   bc_c.who_am_i();
   cout << " bcp_a" << endl;
   bcp_a->who_am_i();
   cout << " bcp_b" << endl;
   bcp_b->who_am_i();

   cout;


   // invoke assignment operator.                 
   bc_a = bc_b;            
   cout << " bc_a" << endl;
   bc_a.who_am_i();
   cout << " bc_b" << endl;
   bc_b.who_am_i();
   cout << " bc_c" << endl;
   bc_c.who_am_i();
   cout << " bcp_a" << endl;
   bcp_a->who_am_i();
   cout << " bcp_b" << endl;
   bcp_b->who_am_i();

   cout;


}