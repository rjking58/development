#include "stdafx.h"
#include <WinUnit.h>

class myClass
{
private:
	int m_i;
public:
	myClass(int p_i): m_i(p_i)
	{
	}
	bool operator==(const myClass& rhs)
	{
		return (m_i == rhs.m_i);
	}
};
BEGIN_TEST(DummyTest)
{
   WIN_ASSERT_TRUE(3 == 3, _T("You should see this error message."));
}
END_TEST

BEGIN_TEST(Dummy2Test)
{
   WIN_ASSERT_EQUAL(3 , 3, _T("3 isn't equal to 4, big surprise!"));
}
END_TEST

BEGIN_TEST(myClassOperatorEqualEqualTest)
{
	myClass mc1(10);
	myClass mc2(10);

	WIN_ASSERT_TRUE(mc1 == mc2, _T("they aren't equal!!"));
}
END_TEST