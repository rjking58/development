#include <iostream>
#include <stdio.h>
#include <string.h>


////////////////////////////////////////////////////////
// program to exercise understanding of copy constructor/assignment operator
// mechanics...
////////////////////////////////////////////////////////

//
//conclusion:  must copy EVERYTHING when you are using a copy constructor or assignment
//					constructor... NOTHING comes for free.
//
class ReferenceCpyTstr
{
public:
    ReferenceCpyTstr(ReferenceCpyTstr &ref)
    {
        std::cout << "ReferenceCpyTstr cpy constructor called" << std::endl;
        x = ref.x;
    }
    int x;
};

class BaseClass
{
   private:
      static int	ms_Unique_Id_track;
		int			ms_Unique_Id;
		int			m_copyable_int;
      int			*m_int_p;   // pointer to int..
      char			*m_name;    // pointer to char...
      ReferenceCpyTstr  m_tst;

      ////////////////////////////////////////////////////////
      // make default constructor illegal to call.
      ////////////////////////////////////////////////////////
      BaseClass() { };

   public:

            
      ////////////////////////////////////////////////////////
      // constructor:: name + initialization value.
      ////////////////////////////////////////////////////////
      
      BaseClass(int i, char * name, ReferenceCpyTstr &tst);
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
		 std::cout << "---------------------------------------------------" << std::endl;
		 std::cout << "***************************************************" << std::endl;
		 std::cout << "ms_Unique_Id == " << ms_Unique_Id << std::endl;
         std::cout << "Name @ " << &m_name << " = " << m_name << std::endl;
         std::cout << "*m_int_p @" << m_int_p << " == " << *m_int_p << std::endl ;
			std::cout << "copyable int=" << m_copyable_int << std::endl;
		 std::cout << "***************************************************" << std::endl;
		 std::cout << "---------------------------------------------------" << std::endl;
      }



};

int	BaseClass::ms_Unique_Id_track = 0;

BaseClass::BaseClass(int i,char *name, ReferenceCpyTstr &tst) :  m_tst(tst)
{
   std::cout << "Normal constructor called" << std::endl;
   ms_Unique_Id = ms_Unique_Id_track;
   ms_Unique_Id_track++;

	m_copyable_int = 666;

   
   // new integer....
   m_int_p = new int;
   *m_int_p = i;

   // string... REMEMBER THE NULLS!                     
   m_name = new char [strlen(name)+1];
   strcpy (m_name,name);

   // show our progress...
   // who_am_i();
   std::cout << "Normal constructor end" << std::endl << std::endl;

}
BaseClass::~BaseClass()
{
   std::cout << "Normal destructor called" << std::endl;
   who_am_i();
   delete m_int_p;
   delete[] m_name;
   std::cout << "m_int_p deleted" << std::endl;
   std::cout << "Normal destructor end" << std::endl << std::endl;
}


BaseClass::BaseClass(BaseClass &BaseClass_ref)
{
   std::cout << "copy constructor called" << std::endl;

   ms_Unique_Id = ms_Unique_Id_track;
   ms_Unique_Id_track++;
   
   // create some default values so that activity is shown...
   m_int_p = new int;
   *m_int_p = 0;
   m_name = new char [2];
   strcpy(m_name,"z");

   // show our current state.
   // who_am_i();
   // BaseClass_ref.who_am_i();
   
   // assign the int over to our new object..
   *m_int_p = *(BaseClass_ref.m_int_p);

   // copy the string to a new string in our new object..                                             
   delete [] m_name;
   
   m_name = new char [ strlen(BaseClass_ref.m_name) + 1 + 10];
   strcpy(m_name,"Copy of ");
   strcat(m_name, BaseClass_ref.m_name);

	m_copyable_int = BaseClass_ref.m_copyable_int;

   // show our current state...
   // who_am_i();
   // BaseClass_ref.who_am_i();

   std::cout << "copy constructor end" << std::endl << std::endl;
}

BaseClass & BaseClass::operator=(BaseClass &BaseClass_ref)
{
   std::cout << "assignment operator called" << std::endl;

   // who_am_i();
   // BaseClass_ref.who_am_i();

   *m_int_p = *(BaseClass_ref.m_int_p);

   delete [] m_name;
   m_name = new char [ strlen(BaseClass_ref.m_name) + 18];
   strcpy(m_name,"Assignment of ");
   strcat(m_name, BaseClass_ref.m_name);

	m_copyable_int = BaseClass_ref.m_copyable_int;

   // who_am_i();
   // BaseClass_ref.who_am_i();

   std::cout << "assignment operator end" << std::endl << std::endl;

   return *this;
}

BaseClass * assignment_invoker(BaseClass bc_o)
{
   BaseClass *bcp;

   std::cout << "enter assignment_invoker" << std::endl << std::endl;
   std::cout << "making new pointer..." << std::endl << std::endl;

   // invoke constructor during a new operation...                               
   bcp = new BaseClass(1,"invoker created");

   std::cout << "copy bc_o to the new pointer..." << std::endl << std::endl;
   
   // invoke the assignment operator.
   *bcp = bc_o;

   std::cout << "exit assignment_invoker" << std::endl << std::endl;

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
   std::cout << "setting up main pointers" << std::endl;
   bcp_a = &bc_a;
   bcp_b = bcp_a;
   std::cout << "done setting up main pointers" << std::endl;

   std::cout << "calling assignment_invoker" << std::endl << std::endl;
   bcp_created = assignment_invoker(bc_a);
   std::cout << "deleting bcp_created" << std::endl << std::endl;

   std::cout << " bcp_created" << std::endl;
   bcp_created->who_am_i();

   delete bcp_created;

   std::cout << " bc_a" << std::endl;
   bc_a.who_am_i();
   std::cout << " bc_b" << std::endl;
   bc_b.who_am_i();
   std::cout << " bc_c" << std::endl;
   bc_c.who_am_i();
   std::cout << " bcp_a" << std::endl;
   bcp_a->who_am_i();
   std::cout << " bcp_b" << std::endl;
   bcp_b->who_am_i();

   std::cout;


   // invoke assignment operator.                 
   bc_a = bc_b;            
   std::cout << " bc_a" << std::endl;
   bc_a.who_am_i();
   std::cout << " bc_b" << std::endl;
   bc_b.who_am_i();
   std::cout << " bc_c" << std::endl;
   bc_c.who_am_i();
   std::cout << " bcp_a" << std::endl;
   bcp_a->who_am_i();
   std::cout << " bcp_b" << std::endl;
   bcp_b->who_am_i();

   std::cout;


}