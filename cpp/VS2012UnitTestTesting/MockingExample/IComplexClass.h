
#pragma once

#include "ExportHeader.h"

#include "IUserOfComplexClass.h"

class DLLEXPORT IComplexClass
{
private:


public:
    virtual void StartCom() = 0;
    virtual void StopCom() = 0;
    virtual void RegisterCallback(IUserOfComplexClass *iUser)= 0;
};
