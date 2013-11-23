
#include "Stdafx.h"

#include "IDataProxyV2_MOCK.h"


bool IDataProxyV2_MOCK::Connect(String ^% errorMessage)
{
    throw gcnew NotImplementedException();
}
void IDataProxyV2_MOCK::Abort()
{
    throw gcnew NotImplementedException();
}
void IDataProxyV2_MOCK::Disconnect()
{
    throw gcnew NotImplementedException();
}


ArchestrAResult IDataProxyV2_MOCK::KeepAlive(ConnectionId Id)
{
    throw gcnew NotImplementedException();
}

//  Reading data.
ArchestrAResult IDataProxyV2_MOCK::Read(array<ArchestrAServices::ASBIDataV2Contract::ItemStatus>   ^% Status,
                                        array<ArchestrAServices::ASBIDataV2Contract::RuntimeValue> ^% ItemValues, 
                                        ConnectionId Id, 
                                        array<ArchestrAServices::ASBIDataV2Contract::ItemIdentity> ^ Items)
{
    throw gcnew NotImplementedException();
}

//  Writing data.
//  WriteHandle for all write modes is a transaction handle that will be returned
//  in PublishWriteComplete().  Special values for WriteHandle are:
//      0: Non-overlapped write call, blocks until return.  PublishWriteComplete() will never contain this.
//      1: Overlapped, but the results will not be requested with PublishWriteComplete(), do not buffer or return.
//      100 and above: Valid write transaction handle.
ArchestrAResult IDataProxyV2_MOCK::Write(   array<ArchestrAServices::ASBIDataV2Contract::ItemStatus>   ^% Status, 
                                            ConnectionId Id, 
                                            array<ArchestrAServices::ASBIDataV2Contract::ItemIdentity> ^ Items, 
                                            array<ArchestrAServices::ASBIDataV2Contract::WriteValue>   ^ Values, 
                                            UInt32 WriteHandle)
{
    throw gcnew NotImplementedException();
}

ArchestrAResult IDataProxyV2_MOCK::WriteUser(   array<ArchestrAServices::ASBIDataV2Contract::ItemStatus>   ^% Status, 
                                                ConnectionId Id, 
                                                array<ArchestrAServices::ASBIDataV2Contract::ItemIdentity> ^ Items, 
                                                array<ArchestrAServices::ASBIDataV2Contract::WriteValue>   ^ Values, 
                                                ArchestrAServices::ASBIDataV2Contract::UserToken           User, 
                                                unsigned int  WriteHandle)
{
    throw gcnew NotImplementedException();
}

ArchestrAResult IDataProxyV2_MOCK::WriteVerified(   array<ArchestrAServices::ASBIDataV2Contract::ItemStatus>   ^% Status, 
                                                    ConnectionId Id, 
                                                    array<ArchestrAServices::ASBIDataV2Contract::ItemIdentity> ^ Items, 
                                                    array<ArchestrAServices::ASBIDataV2Contract::WriteValue> ^ Values, 
                                                    ArchestrAServices::ASBIDataV2Contract::UserToken User, 
                                                    ArchestrAServices::ASBIDataV2Contract::UserToken Supervisor, 
                                                    unsigned int WriteHandle)
{
    throw gcnew NotImplementedException();
}

//US-51105 - WriteSecured method
ArchestrAResult IDataProxyV2_MOCK::WriteSecured(array<ArchestrAServices::ASBIDataV2Contract::ItemStatus>   ^% Status, 
                                                ConnectionId Id, 
                                                array<ArchestrAServices::ASBIDataV2Contract::ItemIdentity> ^ Items, 
                                                array<ArchestrAServices::ASBIDataV2Contract::WriteValue> ^ Values, 
                                                ArchestrAServices::ASBIDataV2Contract::UserToken User, 
                                                unsigned int WriteHandle)
{
    throw gcnew NotImplementedException();
}

ArchestrAResult IDataProxyV2_MOCK::WriteConfirmed(  ArchestrAServices::ASBIDataV2Contract::WriteValue % ValueReceived, 
                                                    __int64 % WriteToken,
                                                    ConnectionId Id, 
                                                    ArchestrAServices::ASBIDataV2Contract::ItemIdentity Item, 
                                                    ArchestrAServices::ASBIDataV2Contract::WriteValue Value, 
                                                    ArchestrAServices::ASBIDataV2Contract::UserToken User, 
                                                    ArchestrAServices::ASBIDataV2Contract::UserToken Supervisor)
{
    throw gcnew NotImplementedException();
}

ArchestrAResult IDataProxyV2_MOCK::ConfirmWrite(ConnectionId Id, 
                                                ArchestrAServices::ASBIDataV2Contract::ItemIdentity Item, 
                                                __int64 WriteToken, 
                                                ArchestrAServices::ASBIDataV2Contract::WriteValue Value, 
                                                ArchestrAServices::ASBIDataV2Contract::UserToken User, 
                                                ArchestrAServices::ASBIDataV2Contract::UserToken Supervisor, 
                                                unsigned int WriteHandle)
{
    throw gcnew NotImplementedException();
}

ArchestrAResult IDataProxyV2_MOCK::PublishWriteComplete
    (   array<ArchestrAServices::ASBIDataV2Contract::ItemWriteComplete> ^% CompleteWrites, 
        ConnectionId Id)
{
    throw gcnew NotImplementedException();
}

//  Subscriptions.
ArchestrAResult IDataProxyV2_MOCK::CreateSubscription(  __int64 % SubscriptionId, 
                                                        ConnectionId Id, 
                                                        __int64 MaxQueueSize, 
                                                        unsigned __int64 SampleInterval)
{
    throw gcnew NotImplementedException();
}

ArchestrAResult IDataProxyV2_MOCK::SetSubscriptionState(ConnectionId Id, 
                                                        __int64 SubscriptionId, 
                                                        ArchestrAServices::ASBIDataContract::V2::Variant NewState, 
                                                        unsigned short StateToChange /*enum SubscriptionStateType*/)
{
    throw gcnew NotImplementedException();
}

ArchestrAResult IDataProxyV2_MOCK::GetSubscriptionState(ArchestrAServices::ASBIDataContract::V2::Variant % State, 
                                                        ConnectionId Id, 
                                                        __int64 SubscriptionId, 
                                                        unsigned short StateToGet /*enum SubscriptionStateType*/)
{
    throw gcnew NotImplementedException();
}

ArchestrAResult IDataProxyV2_MOCK::DeleteSubscription(  ConnectionId Id, 
                                                        __int64 SubscriptionId)
{
    throw gcnew NotImplementedException();
}

ArchestrAResult IDataProxyV2_MOCK::AddMonitoredItems
    (   array<ArchestrAServices::ASBIDataV2Contract::ItemStatus>   ^% Status, 
        array<ArchestrAServices::ASBIDataV2Contract::ItemRegistration> ^% ItemCapabilities,
        ConnectionId Id, 
        __int64 SubscriptionId, 
        array<ArchestrAServices::ASBIDataV2Contract::MonitoredItem> ^ Items, 
        unsigned char RequireId)
{
    throw gcnew NotImplementedException();
}

ArchestrAResult IDataProxyV2_MOCK::DeleteMonitoredItems
    (   array<ArchestrAServices::ASBIDataV2Contract::ItemStatus>   ^% Status, 
        ConnectionId Id, 
        __int64 SubscriptionId, 
        array<ArchestrAServices::ASBIDataV2Contract::MonitoredItem> ^ Items)
{
    throw gcnew NotImplementedException();
}

ArchestrAResult IDataProxyV2_MOCK::GetMonitoredItems
    (   array<ArchestrAServices::ASBIDataV2Contract::MonitoredItem> ^% Items, 
        ConnectionId Id, 
        __int64 SubscriptionId)
{
    throw gcnew NotImplementedException();
}

ArchestrAResult IDataProxyV2_MOCK::Publish
    (   array<ArchestrAServices::ASBIDataV2Contract::ItemStatus>           ^% Status, 
        array<ArchestrAServices::ASBIDataV2Contract::MonitoredItemValue>   ^% Values, 
        ConnectionId Id, 
        __int64 SubscriptionId)
{
    throw gcnew NotImplementedException();
}

ArchestrAResult IDataProxyV2_MOCK::RegisterItems
    (   array<ArchestrAServices::ASBIDataV2Contract::ItemStatus>   ^% Status, 
        array<ArchestrAServices::ASBIDataV2Contract::ItemRegistration> ^% ItemCapabilities,
        ConnectionId Id, 
        array<ArchestrAServices::ASBIDataV2Contract::ItemIdentity> ^ Items, 
        unsigned char RequireId, 
        unsigned char RegisterOnly)
{
    throw gcnew NotImplementedException();
}

ArchestrAResult IDataProxyV2_MOCK::UnregisterItems
    (   array<ArchestrAServices::ASBIDataV2Contract::ItemStatus>   ^% Status, 
        ConnectionId Id, 
        array<ArchestrAServices::ASBIDataV2Contract::ItemIdentity> ^ Items)
{
    throw gcnew NotImplementedException();
}

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// all implementations below are 
// needed for mock implementation only.. 
// they are **NOT** used by consumer.
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void IDataProxyV2_MOCK::OnDisconnect(ConnectionId Id)
{
    throw gcnew NotImplementedException();
}

ArchestrAResult IDataProxyV2_MOCK::ActivateUser(ConnectionId Id, 
                                                ArchestrAServices::ASBIDataV2Contract::UserToken UserToken)
{
    throw gcnew NotImplementedException();
}

ArchestrAResult IDataProxyV2_MOCK::ExchangeCapabilities(String ^% ServiceCapabilities, 
                                                        ConnectionId Id, 
                                                        String ^  ClientCapabilities)
{
    throw gcnew NotImplementedException();
}

void IDataProxyV2_MOCK::OnConnect(  ConnectionId ConnectionId, 
                                    unsigned __int64 Timeout)
{
    throw gcnew NotImplementedException();
}

