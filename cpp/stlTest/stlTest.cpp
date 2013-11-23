#include <iostream>
#include <vector>

class Test1
{
private:
	int m_i;
public:
	Test1(int p_i) : m_i(p_i)
	{
	}
	void isRef()
	{
		std::cout << "(" << m_i << ")" << std::endl;
	}
};

void main()
{

   std::vector<int>           intVec;
   std::vector<int>::iterator intVecIter;
   std::auto_ptr<Test1> PtrT1(new Test1(1));
   std::auto_ptr<Test1> PtrT2(new Test1(2));
   std::auto_ptr<Test1> PtrT3(new Test1(3));

   PtrT1->isRef();
   PtrT2->isRef();
   PtrT3->isRef();

   intVec.push_back(10);
   intVec.push_back(9);
   intVec.push_back(8);
   intVec.push_back(7);


   for ( intVecIter  = intVec.begin();
         intVecIter != intVec.end();
         intVecIter++)
   {
	   std::cout << *intVecIter << " ";
   }
   std::cout << std::endl;

}