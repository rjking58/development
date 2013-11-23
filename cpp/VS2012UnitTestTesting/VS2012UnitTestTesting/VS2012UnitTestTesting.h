
#ifdef VS2012UNITTESTTESTING
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT __declspec(dllimport)
#endif


class DLLEXPORT ClassUnderTest
{
private:
    int m_i;
public:
    ClassUnderTest();
    ClassUnderTest(int i);
    void SetI(int i);
    int GetI();
};