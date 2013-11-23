#include "stdafx.h"

using namespace System;
using namespace ArchestrAServices::ASBContract;
using namespace ArchestrAServices::ASBIDataContract;
using namespace ArchestrAServices::Proxy;


    //public partial struct ItemIdentity
    //{
    //    public ushort Type
    //    /// <remarks/>
    //    public ushort ReferenceType
    //    public string Name
    //    
    //    public string ContextName
    //
    //    public ulong Id
    //    public bool IdSpecified
    //}


    //public partial struct ItemStatus
    //{
    //    
    //    
    //    /// <remarks/>
    //    public ItemIdentity Item
    //    /// <remarks/>
    //    public ushort ErrorCode
    //    
    //    /// <remarks/>
    //    public bool ErrorCodeSpecified
    //}

// left this here since its related to classes below it.
ref class ItemIdentityV1Mgr
{
public:
    static ItemIdentity MakeFirst()
    {
        // ItemIdentity
        ItemIdentity ident;
        ident.Type = 1;
        ident.ReferenceType = 2;
        ident.Name = "identity";
        ident.ContextName = "CONTEXT";
        ident.Id = 3;
        //IdSpecified

        return ident;
    }
    static ItemIdentity MakeSecond()
    {
        // ItemIdentity
        ItemIdentity ident;
        ident.Type = 5;
        ident.ReferenceType = 6;
        ident.Name = "identity2";
        ident.ContextName = "CONTEXT2";
        ident.Id = 7;
        //IdSpecified

        return ident;
    }
};

ref class ItemStatusMgr
{
public:
    static ItemStatus MakeFirst()
    {
        ItemStatus stat;

        //IdSpecified

        // don't know why this trick is required..
        stat.Item = ItemIdentityV1Mgr::MakeFirst();

        stat.ErrorCode = 4;
        //ErrorCodeSpecified
        return stat;
    }

    static ItemStatus MakeSecond()
    {
        ItemStatus stat;


        // don't know why this trick is required..
        stat.Item = ItemIdentityV1Mgr::MakeSecond();

        stat.ErrorCode = 8;
        //ErrorCodeSpecified
        return stat;
    }

};

