

#include "Stdafx.h"
#include "CIDataVersionAdapterV2.h"
#include "StatusCodes.h"

using namespace ArchestrAServices::ASBIDataV2Adapter;


bool CIDataVersionAdapterV2::Connect(String ^% errorMessage) 
{
    bool result = false;

    if(m_ASBProxy != nullptr)
    {
        result = m_ASBProxy->Connect(errorMessage);
    }
    
    return result;
}

void CIDataVersionAdapterV2::Abort() 
{
    if(m_ASBProxy != nullptr)
    {
        m_ASBProxy->Abort();
    }
}

void CIDataVersionAdapterV2::Disconnect() 
{
    if(m_ASBProxy != nullptr)
    {
        m_ASBProxy->Disconnect();
    }
}




ArchestrAResult CIDataVersionAdapterV2::KeepAlive(ConnectionId Id) 
{
    if(m_ASBProxy != nullptr)
    {
        return m_ASBProxy->KeepAlive(Id);
    }
}



//  Reading data.
ArchestrAResult CIDataVersionAdapterV2::Read
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
        result = m_ASBProxy->Read(  Status,
                                    ItemValues,
                                    Id,
                                    Items);
    }
    return result;
}

//  Writing data.
//  WriteHandle for all write modes is a transaction handle that will be returned
//  in PublishWriteComplete().  Special values for WriteHandle are:
//      0: Non-overlapped write call, blocks until return.  PublishWriteComplete() will never contain this.
//      1: Overlapped, but the results will not be requested with PublishWriteComplete(), do not buffer or return.
//      100 and above: Valid write transaction handle.
ArchestrAResult CIDataVersionAdapterV2::Write
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
        result = m_ASBProxy->Write( Status,
                                    Id,
                                    Items,
                                    Values,
                                    WriteHandle);

    }

    return result;
}

ArchestrAResult CIDataVersionAdapterV2::WriteUser
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
        result = m_ASBProxy->WriteUser( Status,
                                        Id,
                                        Items,
                                        Values,
                                        User,
                                        WriteHandle);

    }

    return result;
}

ArchestrAResult CIDataVersionAdapterV2::WriteVerified
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
        result = m_ASBProxy->WriteVerified( Status,
                                            Id,
                                            Items,
                                            Values,
                                            User,
                                            Supervisor,
                                            WriteHandle);

    }
    return result;
}

//US-51105 - WriteSecured method
ArchestrAResult CIDataVersionAdapterV2::WriteSecured
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
        result = m_ASBProxy->WriteSecured(  Status,
                                            Id,
                                            Items,
                                            Values,
                                            User,
                                            WriteHandle);

    }

    return result;
}

ArchestrAResult CIDataVersionAdapterV2::WriteConfirmed
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
        result = m_ASBProxy->WriteConfirmed(ValueReceived,
                                            WriteToken,
                                            Id,
                                            Item,
                                            Value,
                                            User,
                                            Supervisor);
    }
    return result;
}

ArchestrAResult CIDataVersionAdapterV2::ConfirmWrite
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
                                            Item,
                                            WriteToken,
                                            Value,
                                            User,
                                            Supervisor,
                                            WriteHandle);
    }
    return result;
}

ArchestrAResult CIDataVersionAdapterV2::PublishWriteComplete
    (   array<ArchestrAServices::ASBIDataV2Contract::ItemWriteComplete> ^% CompleteWrites, 
        ConnectionId Id) 
{
    ArchestrAResult result;
    result = ResultFactory::MakeResult(ArchestrAError::SpecificError,0x20);
    result.SpecificErrorCode = StatusCodes::BadInternalError;

    if(m_ASBProxy != nullptr)
    {
        result = m_ASBProxy->PublishWriteComplete(  CompleteWrites,
                                                    Id);
    }

    return result;
}

//  Subscriptions.
ArchestrAResult CIDataVersionAdapterV2::CreateSubscription
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

ArchestrAResult CIDataVersionAdapterV2::SetSubscriptionState
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
                                                    NewState,
                                                    StateToChange);
    }

    return result;
}

ArchestrAResult CIDataVersionAdapterV2::GetSubscriptionState
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
        result = m_ASBProxy->GetSubscriptionState(  State,
                                                    Id,
                                                    SubscriptionId,
                                                    StateToGet);
    }

    return result;
}

ArchestrAResult CIDataVersionAdapterV2::DeleteSubscription
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

ArchestrAResult CIDataVersionAdapterV2::AddMonitoredItems
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
        result = m_ASBProxy->AddMonitoredItems( Status,
                                                ItemCapabilities,
                                                Id,
                                                SubscriptionId,
                                                Items,
                                                RequireId);

    }
    return result;
}

ArchestrAResult CIDataVersionAdapterV2::DeleteMonitoredItems
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
        result = m_ASBProxy->DeleteMonitoredItems(  Status,
                                                    Id,
                                                    SubscriptionId,
                                                    Items);

    }

    return result;
}

ArchestrAResult CIDataVersionAdapterV2::GetMonitoredItems
    (   array<ArchestrAServices::ASBIDataV2Contract::MonitoredItem> ^% Items, 
        ConnectionId Id, 
        __int64 SubscriptionId) 
{
    ArchestrAResult result;
    result = ResultFactory::MakeResult(ArchestrAError::SpecificError,0x20);
    result.SpecificErrorCode = StatusCodes::BadInternalError;

    if(m_ASBProxy != nullptr)
    {
        result = m_ASBProxy->GetMonitoredItems( Items,
                                                Id,
                                                SubscriptionId);
    }

    return result;
}

ArchestrAResult CIDataVersionAdapterV2::Publish
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
        result = m_ASBProxy->Publish(   Status,
                                        Values,
                                        Id,
                                        SubscriptionId);

    }
    return result;
}
                                        
ArchestrAResult CIDataVersionAdapterV2::RegisterItems
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
        result = m_ASBProxy->RegisterItems( Status,
                                            ItemCapabilities,
                                            Id,
                                            Items,
                                            RequireId,
                                            RegisterOnly);

    }

    return result;
}

ArchestrAResult CIDataVersionAdapterV2::UnregisterItems
    (   array<ArchestrAServices::ASBIDataV2Contract::ItemStatus>   ^% Status, 
        ConnectionId Id, 
        array<ArchestrAServices::ASBIDataV2Contract::ItemIdentity> ^ Items) 
{
    ArchestrAResult result;
    result = ResultFactory::MakeResult(ArchestrAError::SpecificError,0x20);
    result.SpecificErrorCode = StatusCodes::BadInternalError;

    if(m_ASBProxy != nullptr)
    {
        result  = m_ASBProxy->UnregisterItems(  Status,
                                                Id,
                                                Items);

    }

    return result;
}
