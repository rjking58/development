#include "stdafx.h"

using namespace System;
using namespace ArchestrAServices::ASBContract;
using namespace ArchestrAServices::ASBIDataContract;
using namespace ArchestrAServices::Proxy;

    //public partial struct ItemWriteComplete
    //{
    //    public ItemStatus[] Status
    //    public uint WriteHandle
    //    public bool WriteHandleSpecified
    //}


ref class ItemWriteCompleteMgr
{
public:
    static ItemWriteComplete MakeFirst()
    {
        ItemWriteComplete iwc;
        
        iwc.Status = gcnew array<ItemStatus>(1);
        iwc.Status[0] = ItemStatusMgr::MakeFirst();
        iwc.WriteHandle = 1;

        return iwc;
    }
    static ItemWriteComplete MakeSecond()
    {
        ItemWriteComplete iwc;
        
        iwc.Status = gcnew array<ItemStatus>(1);
        iwc.Status[0] = ItemStatusMgr::MakeSecond();
        iwc.WriteHandle = 2;

        return iwc;
    }
};
