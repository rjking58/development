// AbstractFactoryCPP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <memory>

/// <summary>
/// a product of our factory.. expressed abstractly
/// </summary>
class AbstractProduct
{
public:
    virtual void DoSomething() = 0;
};

/// <summary>
/// a product of our factory.. concrete product 1
/// </summary>
class Product1 : public AbstractProduct
{
public:
    void DoSomething()
    {
        std::cout << "DoSomething Product1" << std::endl;
    }
};

/// <summary>
/// a product of our factory.. concrete product 2
/// </summary>
class Product2 : public AbstractProduct
{
public:
    void DoSomething()
    {
        std::cout << "DoSomething Product2" << std::endl;
    }
};

/// <summary>
/// our factory, expressed abstractly
/// </summary>
class AbstractFactory
{
public:
    virtual AbstractProduct * MakeProduct() = 0;
};

/// <summary>
/// a factory that generates product1s
/// </summary>
class Factory1 : public AbstractFactory
{
public:
    AbstractProduct * MakeProduct()
    {
        return new Product1();
    }
};

/// <summary>
/// a factory that generates product2s
/// </summary>
class Factory2 : public AbstractFactory
{
public:
    AbstractProduct * MakeProduct()
    {
        return new Product2();
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    {
        std::auto_ptr<AbstractFactory> af(new Factory1());
        std::auto_ptr<AbstractProduct> ap(af->MakeProduct ());
        ap->DoSomething ();
    }
    {
        std::auto_ptr<AbstractFactory> af(new Factory2());
        std::auto_ptr<AbstractProduct> ap(af->MakeProduct ());
        ap->DoSomething ();
    }

	return 0;
}

