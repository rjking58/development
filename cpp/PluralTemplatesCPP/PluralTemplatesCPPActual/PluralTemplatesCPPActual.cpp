// PluralTemplatesCPPActual.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>

// function template
template <class T>
T max(T& t1, T& t2)
{
    return t1 < t2 ? t2 : t1;
}
template <class T>
T max(T t1, T t2)
{
    return t1 < t2 ? t2 : t1;
}

class Something
{
private:
    int m_count;
public:
    Something(int count)
        : m_count(count)
    {
    }
    void SetCount(int count)
    {
        m_count = count;
    }
    int GetCount()
    {
        return m_count;
    }
};

template <class T>
class Accum
{
private:
    T total;
public:
    Accum(T start) : total(start) 
    {
    }

    T operator+=(const T& t) 
    {
        return total = total + t;
    }

    T GetTotal() 
    {
        return total;
    }
};

// specialization
template <>
class Accum<Something>
{
private:
    int total;
public:
    Accum(int start) : total(start) 
    {
    }

    int operator+=(Something& t) 
    {
        return total = total + t.GetCount();
    }

    int GetTotal() 
    {
        return total;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    std::cout << "max (1,2) is " << max(1,2) << std::endl;
    std::cout << "max (4,3) is " << max(4,3) << std::endl;
    std::cout << "max (5,6) is " << max(5,6) << std::endl;

    // use a called out specialization..  this requires the use of a specific
    // implementation when things may be ambiguous..
    std::cout << "max (33,2.0) is " << max<double>(33,2.0) << std::endl;


    // use our class template
    Accum<int> integers(0);

    integers += 3;
    integers += 7;
    std::cout << integers.GetTotal() << std::endl;

    Accum<std::string> strings("");

    strings += "hello";
    strings += " ";
    strings += "world";
    std::cout << strings.GetTotal()  << std::endl;

    //integers += "testing";
    //strings += 4;

    Accum<Something> somethings(0);

    Something some1(55);
    Something some2(66);

    somethings += some1;
    somethings += some2;

    std::cout << somethings.GetTotal() << std::endl;


	return 0;
}

