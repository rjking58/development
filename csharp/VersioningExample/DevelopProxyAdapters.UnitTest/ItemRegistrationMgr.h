#include "stdafx.h"

using namespace System;
using namespace ArchestrAServices::ASBContract;
using namespace ArchestrAServices::ASBIDataContract;
using namespace ArchestrAServices::Proxy;


    //public partial struct ItemRegistration
    //{
    //    
    //    public ulong Id
    //    public bool IdSpecified
    //    public ushort WriteCapability
    //    public bool WriteCapabilitySpecified
    //}

// left this here since its related to classes below it.

ref class ItemRegistrationMgr
{
public:
    static ItemRegistration MakeFirst()
    {
        ItemRegistration reg;

        reg.Id = 1;
        //    IdSpecified
        reg.WriteCapability = 2;
        //    WriteCapabilitySpecified


        return reg;
    }

    static ItemRegistration MakeSecond()
    {
        ItemRegistration reg;

        reg.Id = 3;
        //    IdSpecified
        reg.WriteCapability = 4;
        //    WriteCapabilitySpecified

        return reg;
    }

};

