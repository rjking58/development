

#include "Stdafx.h"
#include "CIDataVersionAdapterV1.h"
#include "StatusCodes.h"

using namespace ArchestrAServices::ASBIDataV2Adapter;


bool CIDataVersionAdapterV1::Connect(String ^% errorMessage) 
{
    bool result = false;

    if(m_ASBProxy != nullptr)
    {
        result = m_ASBProxy->Connect(errorMessage);
    }
    
    return result;
}

void CIDataVersionAdapterV1::Abort() 
{
    if(m_ASBProxy != nullptr)
    {
        m_ASBProxy->Abort();
    }
}

void CIDataVersionAdapterV1::Disconnect() 
{
    if(m_ASBProxy != nullptr)
    {
        m_ASBProxy->Disconnect();
    }
}




ArchestrAResult CIDataVersionAdapterV1::KeepAlive(ConnectionId Id) 
{
    if(m_ASBProxy != nullptr)
    {
        return m_ASBProxy->KeepAlive(Id);
    }
}


//  Reading data.
ArchestrAResult CIDataVersionAdapterV1::Read
    (   array<ArchestrAServices::ASBIDataV2Contract::ItemStatus>   ^% Status,
        array<ArchestrAServices::ASBIDataV2Contract::RuntimeValue> ^% ItemValues, 
        ConnectionId Id, 
        array<ArchestrAServices::ASBIDataV2Contract::ItemIdentity> ^ Items) 
{
    ArchestrAResult result;
    result = ResultFactory::MakeResult(ArchestrAError::SpecificError,0x20);
    result.SpecificErrorCode = StatusCodes::BadInternalError;

    if(m_ASBProxy != nullptr)
    {
        array<ArchestrAServices::ASBContract::ItemStatus>   ^v1Status = nullptr;
        array<ArchestrAServices::ASBContract::RuntimeValue> ^v1ItemValues = nullptr;

        result = m_ASBProxy->Read(  v1Status,
                                    v1ItemValues,
                                    Id,
                                    IDataV2toV1Extensions::ToV1ItemIdentityArray(Items));
        if(v1Status != nullptr)
        {
            Status = IDataV1toV2Extensions::ToV2ItemStatusArray(v1Status);
        }
        if(v1ItemValues != nullptr)
        {
            ItemValues = IDataV1toV2Extensions::ToV2RuntimeValueArray(v1ItemValues);
        }
    }
    return result;
}

//  Writing data.
//  WriteHandle for all write modes is a transaction handle that will be returned
//  in PublishWriteComplete().  Special values for WriteHandle are:
//      0: Non-overlapped write call, blocks until return.  PublishWriteComplete() will never contain this.
//      1: Overlapped, but the results will not be requested with PublishWriteComplete(), do not buffer or return.
//      100 and above: Valid write transaction handle.
ArchestrAResult CIDataVersionAdapterV1::Write
    (   array<ArchestrAServices::ASBIDataV2Contract::ItemStatus>   ^% Status, 
        ConnectionId Id, 
        array<ArchestrAServices::ASBIDataV2Contract::ItemIdentity> ^ Items, 
        array<ArchestrAServices::ASBIDataV2Contract::WriteValue>   ^ Values, 
        UInt32 WriteHandle) 
{
    ArchestrAResult result;
    result = ResultFactory::MakeResult(ArchestrAError::SpecificError,0x20);
    result.SpecificErrorCode = StatusCodes::BadInternalError;

    if(m_ASBProxy != nullptr)
    {
        array<ArchestrAServices::ASBContract::ItemStatus>   ^v1Status = nullptr;

        result = m_ASBProxy->Write( v1Status,
                                    Id,
                                    IDataV2toV1Extensions::ToV1ItemIdentityArray(Items),
                                    IDataV2toV1Extensions::ToV1WriteValueArray(Values),
                                    WriteHandle);

        if(v1Status != nullptr)
        {
            Status = IDataV1toV2Extensions::ToV2ItemStatusArray(v1Status);
        }
    }

    return result;
}

ArchestrAResult CIDataVersionAdapterV1::WriteUser
    (   array<ArchestrAServices::ASBIDataV2Contract::ItemStatus>   ^% Status, 
        ConnectionId Id, 
        array<ArchestrAServices::ASBIDataV2Contract::ItemIdentity> ^ Items, 
        array<ArchestrAServices::ASBIDataV2Contract::WriteValue>   ^ Values, 
        ArchestrAServices::ASBIDataV2Contract::UserToken           User, 
        unsigned int  WriteHandle) 
{
    ArchestrAResult result;
    result = ResultFactory::MakeResult(ArchestrAError::SpecificError,0x20);
    result.SpecificErrorCode = StatusCodes::BadInternalError;

    if(m_ASBProxy != nullptr)
    {
        array<ArchestrAServices::ASBContract::ItemStatus>   ^v1Status = nullptr;

        result = m_ASBProxy->WriteUser( v1Status,
                                        Id,
                                        IDataV2toV1Extensions::ToV1ItemIdentityArray(Items),
                                        IDataV2toV1Extensions::ToV1WriteValueArray(Values),
                                        IDataV2toV1Extensions::ToV1UserToken(User),
                                        WriteHandle);

        if(v1Status != nullptr)
        {
            Status = IDataV1toV2Extensions::ToV2ItemStatusArray(v1Status);
        }
    }

    return result;
}

ArchestrAResult CIDataVersionAdapterV1::WriteVerified
    (   array<ArchestrAServices::ASBIDataV2Contract::ItemStatus>   ^% Status, 
        ConnectionId Id, 
        array<ArchestrAServices::ASBIDataV2Contract::ItemIdentity> ^ Items, 
        array<ArchestrAServices::ASBIDataV2Contract::WriteValue> ^ Values, 
        ArchestrAServices::ASBIDataV2Contract::UserToken User, 
        ArchestrAServices::ASBIDataV2Contract::UserToken Supervisor, 
        unsigned int WriteHandle) 
{
    ArchestrAResult result;
    result = ResultFactory::MakeResult(ArchestrAError::SpecificError,0x20);
    result.SpecificErrorCode = StatusCodes::BadInternalError;

    if(m_ASBProxy != nullptr)
    {
        array<ArchestrAServices::ASBContract::ItemStatus>   ^v1Status = nullptr;

        result = m_ASBProxy->WriteVerified( v1Status,
                                            Id,
                                            IDataV2toV1Extensions::ToV1ItemIdentityArray(Items),
                                            IDataV2toV1Extensions::ToV1WriteValueArray(Values),
                                            IDataV2toV1Extensions::ToV1UserToken(User),
                                            IDataV2toV1Extensions::ToV1UserToken(Supervisor),
                                            WriteHandle);

        if(v1Status != nullptr)
        {
            Status = IDataV1toV2Extensions::ToV2ItemStatusArray(v1Status);
        }
    }
    return result;
}

//US-51105 - WriteSecured method
ArchestrAResult CIDataVersionAdapterV1::WriteSecured
    (   array<ArchestrAServices::ASBIDataV2Contract::ItemStatus>   ^% Status, 
        ConnectionId Id, 
        array<ArchestrAServices::ASBIDataV2Contract::ItemIdentity> ^ Items, 
        array<ArchestrAServices::ASBIDataV2Contract::WriteValue> ^ Values, 
        ArchestrAServices::ASBIDataV2Contract::UserToken User, 
        unsigned int WriteHandle) 
{
    ArchestrAResult result;
    result = ResultFactory::MakeResult(ArchestrAError::SpecificError,0x20);
    result.SpecificErrorCode = StatusCodes::BadInternalError;

    if(m_ASBProxy != nullptr)
    {
        array<ArchestrAServices::ASBContract::ItemStatus>   ^v1Status = nullptr;

        result = m_ASBProxy->WriteSecured(  v1Status,
                                            Id,
                                            IDataV2toV1Extensions::ToV1ItemIdentityArray(Items),
                                            IDataV2toV1Extensions::ToV1WriteValueArray(Values),
                                            IDataV2toV1Extensions::ToV1UserToken(User),
                                            WriteHandle);

        if(v1Status != nullptr)
        {
            Status = IDataV1toV2Extensions::ToV2ItemStatusArray(v1Status);
        }
    }

    return result;
}

ArchestrAResult CIDataVersionAdapterV1::WriteConfirmed
    (   ArchestrAServices::ASBIDataV2Contract::WriteValue % ValueReceived, 
        __int64 % WriteToken,
        ConnectionId Id, 
        ArchestrAServices::ASBIDataV2Contract::ItemIdentity Item, 
        ArchestrAServices::ASBIDataV2Contract::WriteValue Value, 
        ArchestrAServices::ASBIDataV2Contract::UserToken User, 
        ArchestrAServices::ASBIDataV2Contract::UserToken Supervisor) 
{
    ArchestrAResult result;
    result = ResultFactory::MakeResult(ArchestrAError::SpecificError,0x20);
    result.SpecificErrorCode = StatusCodes::BadInternalError;

    if(m_ASBProxy != nullptr)
    {
        ArchestrAServices::ASBContract::WriteValue v1ValueReceived;

        result = m_ASBProxy->WriteConfirmed(v1ValueReceived,
                                            WriteToken,
                                            Id,
                                            IDataV2toV1Extensions::ToV1ItemIdentity(Item),
                                            IDataV2toV1Extensions::ToV1WriteValue(Value),
                                            IDataV2toV1Extensions::ToV1UserToken(User),
                                            IDataV2toV1Extensions::ToV1UserToken(Supervisor));
        ValueReceived = IDataV1toV2Extensions::ToV2WriteValue(v1ValueReceived);
    }
    return result;
}

ArchestrAResult CIDataVersionAdapterV1::ConfirmWrite
    (   ConnectionId Id, 
        ArchestrAServices::ASBIDataV2Contract::ItemIdentity Item, 
        __int64 WriteToken, 
        ArchestrAServices::ASBIDataV2Contract::WriteValue Value, 
        ArchestrAServices::ASBIDataV2Contract::UserToken User, 
        ArchestrAServices::ASBIDataV2Contract::UserToken Supervisor, 
        unsigned int WriteHandle) 
{
    ArchestrAResult result;
    result = ResultFactory::MakeResult(ArchestrAError::SpecificError,0x20);
    result.SpecificErrorCode = StatusCodes::BadInternalError;

    if(m_ASBProxy != nullptr)
    {
        result = m_ASBProxy->ConfirmWrite(  Id,
                                            IDataV2toV1Extensions::ToV1ItemIdentity(Item),
                                            WriteToken,
                                            IDataV2toV1Extensions::ToV1WriteValue(Value),
                                            IDataV2toV1Extensions::ToV1UserToken(User),
                                            IDataV2toV1Extensions::ToV1UserToken(Supervisor),
                                            WriteHandle);
    }
    return result;
}

ArchestrAResult CIDataVersionAdapterV1::PublishWriteComplete
    (   array<ArchestrAServices::ASBIDataV2Contract::ItemWriteComplete> ^% CompleteWrites, 
        ConnectionId Id) 
{
    ArchestrAResult result;
    result = ResultFactory::MakeResult(ArchestrAError::SpecificError,0x20);
    result.SpecificErrorCode = StatusCodes::BadInternalError;

    if(m_ASBProxy != nullptr)
    {
        array<ArchestrAServices::ASBContract::ItemWriteComplete>   ^v1CompleteWrites = nullptr;
        result = m_ASBProxy->PublishWriteComplete(  v1CompleteWrites,
                                                    Id);
        if(v1CompleteWrites != nullptr)
        {
            CompleteWrites = IDataV1toV2Extensions::ToV2ItemWriteCompleteArray(v1CompleteWrites);
        }
    }

    return result;
}

//  Subscriptions.
ArchestrAResult CIDataVersionAdapterV1::CreateSubscription
    (   __int64 % SubscriptionId, 
        ConnectionId Id, 
        __int64 MaxQueueSize, 
        unsigned __int64 SampleInterval) 
{
    ArchestrAResult result;
    result = ResultFactory::MakeResult(ArchestrAError::SpecificError,0x20);
    result.SpecificErrorCode = StatusCodes::BadInternalError;

    if(m_ASBProxy != nullptr)
    {
        result = m_ASBProxy->CreateSubscription(SubscriptionId,
                                                Id,
                                                MaxQueueSize,
                                                SampleInterval);
    }

    return result;
}

ArchestrAResult CIDataVersionAdapterV1::SetSubscriptionState
    (   ConnectionId Id, 
        __int64 SubscriptionId, 
        ArchestrAServices::ASBIDataContract::V2::Variant NewState, 
        unsigned short StateToChange /*enum SubscriptionStateType*/) 
{
    ArchestrAResult result;
    result = ResultFactory::MakeResult(ArchestrAError::SpecificError,0x20);
    result.SpecificErrorCode = StatusCodes::BadInternalError;

    if(m_ASBProxy != nullptr)
    {
        result = m_ASBProxy->SetSubscriptionState(  Id,
                                                    SubscriptionId,
                                                    IDataV2toV1Extensions::ToV1Variant(NewState),
                                                    StateToChange);
    }

    return result;
}

ArchestrAResult CIDataVersionAdapterV1::GetSubscriptionState
    (   ArchestrAServices::ASBIDataContract::V2::Variant % State, 
        ConnectionId Id, 
        __int64 SubscriptionId,
        unsigned short StateToGet /*enum SubscriptionStateType*/) 
{
    ArchestrAResult result;
    result = ResultFactory::MakeResult(ArchestrAError::SpecificError,0x20);
    result.SpecificErrorCode = StatusCodes::BadInternalError;

    if(m_ASBProxy != nullptr)
    {
        ArchestrAServices::ASBIDataContract::Variant v1State;
        result = m_ASBProxy->GetSubscriptionState(  v1State,
                                                    Id,
                                                    SubscriptionId,
                                                    StateToGet);
        State = IDataV1toV2Extensions::ToV2Variant(v1State);
    }

    return result;
}

ArchestrAResult CIDataVersionAdapterV1::DeleteSubscription
    (   ConnectionId Id, 
        __int64 SubscriptionId) 
{
    ArchestrAResult result;
    result = ResultFactory::MakeResult(ArchestrAError::SpecificError,0x20);
    result.SpecificErrorCode = StatusCodes::BadInternalError;

    if(m_ASBProxy != nullptr)
    {
        result = m_ASBProxy->DeleteSubscription(Id,SubscriptionId);
    }

    return result;
}

ArchestrAResult CIDataVersionAdapterV1::AddMonitoredItems
    (   array<ArchestrAServices::ASBIDataV2Contract::ItemStatus>   ^% Status, 
        array<ArchestrAServices::ASBIDataV2Contract::ItemRegistration> ^% ItemCapabilities,
        ConnectionId Id, 
        __int64 SubscriptionId, 
        array<ArchestrAServices::ASBIDataV2Contract::MonitoredItem> ^ Items, 
        unsigned char RequireId) 
{
    ArchestrAResult result;
    result = ResultFactory::MakeResult(ArchestrAError::SpecificError,0x20);
    result.SpecificErrorCode = StatusCodes::BadInternalError;

    if(m_ASBProxy != nullptr)
    {
        array<ArchestrAServices::ASBContract::ItemStatus>       ^v1Status = nullptr;
        array<ArchestrAServices::ASBContract::ItemRegistration> ^v1ItemCapabilities = nullptr;

        result = m_ASBProxy->AddMonitoredItems( v1Status,
                                                v1ItemCapabilities,
                                                Id,
                                                SubscriptionId,
                                                IDataV2toV1Extensions::ToV1MonitoredItemArray(Items),
                                                RequireId);

        if(v1Status != nullptr)
        {
            Status = IDataV1toV2Extensions::ToV2ItemStatusArray(v1Status);
        }
        if(v1ItemCapabilities != nullptr)
        {
            ItemCapabilities = IDataV1toV2Extensions::ToV2ItemRegistrationArray(v1ItemCapabilities);
        }
    }
    return result;
}

ArchestrAResult CIDataVersionAdapterV1::DeleteMonitoredItems
    (   array<ArchestrAServices::ASBIDataV2Contract::ItemStatus>   ^% Status, 
        ConnectionId Id, 
        __int64 SubscriptionId, 
        array<ArchestrAServices::ASBIDataV2Contract::MonitoredItem> ^ Items) 
{
    ArchestrAResult result;
    result = ResultFactory::MakeResult(ArchestrAError::SpecificError,0x20);
    result.SpecificErrorCode = StatusCodes::BadInternalError;

    if(m_ASBProxy != nullptr)
    {
        array<ArchestrAServices::ASBContract::ItemStatus>   ^v1Status = nullptr;

        result = m_ASBProxy->DeleteMonitoredItems(  v1Status,
                                                    Id,
                                                    SubscriptionId,
                                                    IDataV2toV1Extensions::ToV1MonitoredItemArray(Items));

        if(v1Status != nullptr)
        {
            Status = IDataV1toV2Extensions::ToV2ItemStatusArray(v1Status);
        }
    }

    return result;
}

ArchestrAResult CIDataVersionAdapterV1::GetMonitoredItems
    (   array<ArchestrAServices::ASBIDataV2Contract::MonitoredItem> ^% Items, 
        ConnectionId Id, 
        __int64 SubscriptionId) 
{
    ArchestrAResult result;
    result = ResultFactory::MakeResult(ArchestrAError::SpecificError,0x20);
    result.SpecificErrorCode = StatusCodes::BadInternalError;

    if(m_ASBProxy != nullptr)
    {
        result = m_ASBProxy->GetMonitoredItems( IDataV2toV1Extensions::ToV1MonitoredItemArray(Items),
                                                Id,
                                                SubscriptionId);
    }

    return result;
}

ArchestrAResult CIDataVersionAdapterV1::Publish
    (   array<ArchestrAServices::ASBIDataV2Contract::ItemStatus>           ^% Status, 
        array<ArchestrAServices::ASBIDataV2Contract::MonitoredItemValue>   ^% Values, 
        ConnectionId Id, 
        __int64 SubscriptionId) 
{
    ArchestrAResult result;
    result = ResultFactory::MakeResult(ArchestrAError::SpecificError,0x20);
    result.SpecificErrorCode = StatusCodes::BadInternalError;

    if(m_ASBProxy != nullptr)
    {
        array<ArchestrAServices::ASBContract::ItemStatus>           ^v1Status = nullptr;
        array<ArchestrAServices::ASBContract::MonitoredItemValue>   ^v1Values = nullptr;

        result = m_ASBProxy->Publish(   v1Status,
                                        v1Values,
                                        Id,
                                        SubscriptionId);

        if(v1Status != nullptr)
        {
            Status = IDataV1toV2Extensions::ToV2ItemStatusArray(v1Status);
        }
        if(v1Values)
        {
            Values = IDataV1toV2Extensions::ToV2MonitoredItemValueArray(v1Values);
        }
    }
    return result;
}
                                        
ArchestrAResult CIDataVersionAdapterV1::RegisterItems
    (   array<ArchestrAServices::ASBIDataV2Contract::ItemStatus>   ^% Status, 
        array<ArchestrAServices::ASBIDataV2Contract::ItemRegistration> ^% ItemCapabilities,
        ConnectionId Id, 
        array<ArchestrAServices::ASBIDataV2Contract::ItemIdentity> ^ Items, 
        unsigned char RequireId, 
        unsigned char RegisterOnly) 
{
    ArchestrAResult result;
    result = ResultFactory::MakeResult(ArchestrAError::SpecificError,0x20);
    result.SpecificErrorCode = StatusCodes::BadInternalError;

    if(m_ASBProxy != nullptr)
    {
        array<ArchestrAServices::ASBContract::ItemStatus>       ^v1Status = nullptr;
        array<ArchestrAServices::ASBContract::ItemRegistration> ^v1ItemCapabilities = nullptr;

        result = m_ASBProxy->RegisterItems( v1Status,
                                            v1ItemCapabilities,
                                            Id,
                                            IDataV2toV1Extensions::ToV1ItemIdentityArray(Items),
                                            RequireId,
                                            RegisterOnly);

        if(v1Status != nullptr)
        {
            Status = IDataV1toV2Extensions::ToV2ItemStatusArray(v1Status);
        }
        if(v1ItemCapabilities != nullptr)
        {
            ItemCapabilities = IDataV1toV2Extensions::ToV2ItemRegistrationArray(v1ItemCapabilities);
        }
    }

    return result;
}

ArchestrAResult CIDataVersionAdapterV1::UnregisterItems
    (   array<ArchestrAServices::ASBIDataV2Contract::ItemStatus>   ^% Status, 
        ConnectionId Id, 
        array<ArchestrAServices::ASBIDataV2Contract::ItemIdentity> ^ Items) 
{
    ArchestrAResult result;
    result = ResultFactory::MakeResult(ArchestrAError::SpecificError,0x20);
    result.SpecificErrorCode = StatusCodes::BadInternalError;

    if(m_ASBProxy != nullptr)
    {
        array<ArchestrAServices::ASBContract::ItemStatus>   ^v1Status = nullptr;

        result  = m_ASBProxy->UnregisterItems(  v1Status,
                                                Id,
                                                IDataV2toV1Extensions::ToV1ItemIdentityArray(Items));

        if(v1Status != nullptr)
        {
            Status = IDataV1toV2Extensions::ToV2ItemStatusArray(v1Status);
        }
    }

    return result;
}
