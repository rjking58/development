// TemplateMethodCPP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <memory>

/// <summary>
/// our 'template method class'
/// </summary>
class AbstractStepwiseProcess
{
public:
    /// <summary>
    /// a bunch of steps which will have overridden 
    /// behavior in subclasses.. Note that not all steps 
    /// must look like this.. we may have steps that never
    /// change and therefore would have a simple method declared
    /// in this class
    /// </summary>
    virtual void Step1() = 0;
    virtual void Step2() = 0;
    virtual void Step3() = 0;

    void Step4()
    {
        std::cout << "Process:Step4" << std::endl;
    }

    /// <summary>
    /// our template method. 
    /// </summary>
    void DoProcess()
    {
        Step1();
        Step2();
        Step3();
        Step4();
    }
};
/// <summary>
/// a class which provides specific behaviors for the 
/// abstract steps in the base class
/// </summary>
class Process1 : public AbstractStepwiseProcess
{
public:
    virtual void Step1()
    {
        std::cout << "Process1:Step1" << std::endl;
    }
    virtual void Step2()
    {
        std::cout << "Process1:Step2" << std::endl;
    }
    virtual void Step3()
    {
        std::cout << "Process1:Step3" << std::endl;
    }
};
/// <summary>
/// a class which provides specific behaviors for the 
/// abstract steps in the base class
/// </summary>
class Process2 : public AbstractStepwiseProcess
{
public:
    virtual void Step1()
    {
        std::cout << "Process2:Step1" << std::endl;
    }
    virtual void Step2()
    {
        std::cout << "Process2:Step2" << std::endl;
    }
    virtual void Step3()
    {
        std::cout << "Process2:Step3" << std::endl;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    {
        std::auto_ptr<AbstractStepwiseProcess> asp(new Process1);
        asp->DoProcess();
    }
    {
        std::auto_ptr<AbstractStepwiseProcess> asp(new Process2);
        asp->DoProcess();
    }
	return 0;
}

