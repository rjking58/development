// CastingExamples.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

class B
{
public:
    virtual void isClass()
    {
        std::cout << "B" << std::endl;
    }
};

class D1 : public B
{

public:
    virtual void isClass()
    {
        std::cout << "D1" << std::endl;
    }

    void doD1()
    {
        std::cout << "do D1" << std::endl;
    }
};

class D2 : public B
{

public:
    virtual void isClass()
    {
        std::cout << "D2" << std::endl;
    }

    void doD2()
    {
        std::cout << "do D2" << std::endl;
    }
};
int _tmain(int argc, _TCHAR* argv[])
{
    B  *pBinstance = 0;
    B  *pBinstance2 = 0;
    D1 *pD1instance = 0;
    D2 *pD2instance = 0;


    B  Binstance;
    D1 D1instance;
    D2 D2instance;

    // use dynamic cast!!
    // B->D1
    std::cout << "B->D1" << std::endl;
    pBinstance = &Binstance;
    std::cout << "pBinstance = &Binstance;" << std::endl << std::endl;
    pD1instance = 0;
    std::cout << "pD1instance = 0;" << std::endl;
    pD1instance = static_cast<D1*>(pBinstance);
    std::cout << "pD1instance = static_cast<D1*>(pBinstance);" << std::endl;

    std::cout << "pD1instance[" << pD1instance << "]" << std::endl << std::endl;

    pD1instance = 0;
    std::cout << "pD1instance = 0;" << std::endl;
    pD1instance = dynamic_cast<D1*>(pBinstance);
    std::cout << "pD1instance = dynamic_cast<D1*>(pBinstance);" << std::endl;
    std::cout << "pD1instance[" << pD1instance << "]" << std::endl << std::endl;

    // B->D2
    std::cout << "B->D2" << std::endl;
    pD2instance = 0;
    std::cout << "pD2instance = 0;" << std::endl;
    pD2instance = static_cast<D2*>(pBinstance);
    std::cout << "pD2instance = static_cast<D2*>(pBinstance);" << std::endl;
    std::cout << "pD2instance[" << pD2instance << "]" << std::endl << std::endl;

    pD2instance = 0;
    std::cout << "pD2instance = 0;" << std::endl;
    pD2instance = dynamic_cast<D2*>(pBinstance);
    std::cout << "pD2instance = dynamic_cast<D2*>(pBinstance);" << std::endl;
    std::cout << "pD2instance[" << pD2instance << "]" << std::endl << std::endl;

    pBinstance = 0;

    // D1->B
    std::cout << "D1->B" << std::endl;
    std::cout << "upcasting is safe... " << std::endl << std::endl;
    pBinstance = &D1instance;
    std::cout << "pBinstance = &D1instance;" << std::endl << std::endl;

    pBinstance2 = 0;
    std::cout << "pBinstance2 = 0;" << std::endl;
    pBinstance2 = static_cast<B*>(pBinstance);
    std::cout << "pBinstance2 = static_cast<B*>(pBinstance);" << std::endl;
    std::cout << "pBinstance2[" << pBinstance2 << "]" << std::endl << std::endl;

    pBinstance2 = 0;
    std::cout << "pBinstance2 = 0;" << std::endl;
    pBinstance2 = dynamic_cast<B*>(pBinstance);
    std::cout << "pBinstance2 = dynamic_cast<B*>(pBinstance);" << std::endl;
    std::cout << "pBinstance2[" << pBinstance2 << "]" << std::endl << std::endl;

    pD1instance = 0;

    // D2->B
    std::cout << "D2->B" << std::endl;
    pBinstance = &D2instance;
    std::cout << "pBinstance = &D2instance;" << std::endl << std::endl;

    pBinstance2 = 0;
    std::cout << "pBinstance2 = 0;" << std::endl;
    pBinstance2 = static_cast<B*>(pBinstance);
    std::cout << "pBinstance2 = static_cast<B*>(pBinstance);" << std::endl;
    std::cout << "pBinstance2[" << pBinstance2 << "]" << std::endl << std::endl;

    pBinstance2 = 0;
    std::cout << "pBinstance2 = 0;" << std::endl;
    pBinstance2 = dynamic_cast<B*>(pBinstance);
    std::cout << "pBinstance2 = dynamic_cast<B*>(pBinstance);" << std::endl;
    std::cout << "pBinstance2[" << pBinstance2 << "]" << std::endl << std::endl;
    // D1->D2
    std::cout << "D1->D2" << std::endl;
    pBinstance = &D1instance;
    std::cout << "pBinstance = &D1instance;" << std::endl << std::endl;

    pD2instance = 0;
    std::cout << "pD2instance = 0;" << std::endl;
    pD2instance = static_cast<D2*>(pBinstance);
    std::cout << "pD2instance = static_cast<D2*>(pBinstance);" << std::endl;
    std::cout << "pD2instance[" << pD2instance << "]" << std::endl << std::endl;


    pD2instance = 0;
    std::cout << "pD2instance = 0;" << std::endl;
    pD2instance = dynamic_cast<D2*>(pBinstance);
    std::cout << "pD2instance = dynamic_cast<D2*>(pBinstance);" << std::endl;
    std::cout << "pD2instance[" << pD2instance << "]" << std::endl << std::endl;




   

    // examples of casting using various standard methods...


	return 0;
}

