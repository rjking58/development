
#include "Stdafx.h"

#include "IDataProxy_MOCK.h"

#include "ItemStatusMgr.h"
#include "RuntimeValueMgr.h"
#include "WriteValueMgr.h"
#include "ItemWriteCompleteMgr.h"
#include "ItemRegistrationMgr.h"

bool IDataProxy_MOCK::Connect(String ^% errorMessage)
{
    errorMessage = "connected";
    return true;
}
void IDataProxy_MOCK::Abort()
{
    AbortCalled = true;
}
void IDataProxy_MOCK::Disconnect()
{
    DisconnectCalled = true;
}


bool IDataProxy_MOCK::VerifyItemIdentityAry(array<ItemIdentity> ^ Items)
{
    bool result = false;
    
    result = 
            Items[0].Type == 1
        &&  Items[0].ReferenceType == 2
        &&  Items[0].Name == "identity"
        &&  Items[0].ContextName == "CONTEXT"
        &&  Items[0].Id == 3
        &&  Items[0].IdSpecified
        &&  Items[1].Type == 5
        &&  Items[1].ReferenceType == 6
        &&  Items[1].Name == "identity2"
        &&  Items[1].ContextName == "CONTEXT2"
        &&  Items[1].Id == 7
        &&  Items[1].IdSpecified;
    return result;
}

bool IDataProxy_MOCK::VerifyItemIdentity(ItemIdentity Item)
{
    bool result = false;
    
    result = 
            Item.Type == 1
        &&  Item.ReferenceType == 2
        &&  Item.Name == "identity"
        &&  Item.ContextName == "CONTEXT"
        &&  Item.Id == 3
        &&  Item.IdSpecified;

    return result;
}

bool IDataProxy_MOCK::VerifyWriteValueAry(array<WriteValue>   ^ Values)
{
    bool result = false;
    //public partial struct ASBStatus
    //{
    //    public sbyte Count
    //    public byte[] Payload
    //}


    //public partial struct Variant
    //{
    //    public ushort Type
    //    public int Length
    //    public byte[] Payload
    //}

    //public partial struct WriteValue
    //{
    //    public bool                       HasQT
    //    public bool                       HasQTSpecified
    //    public ASBIDataContract.Variant   Value
    //    public ASBStatus                  Status
    //    public System.DateTime            Timestamp
    //    public bool                       TimestampSpecified
    //    public string                     Comment
    //}
    


    result = 
            Values[0].HasQT
        &&  Values[0].HasQTSpecified 
        &&  Values[0].Value.Type == 1
        &&  Values[0].Value.Length == 2
        &&  Values[0].Value.Payload->Length == 2
        &&  Values[0].Value.Payload[0] == 3
        &&  Values[0].Value.Payload[1] == 4
        &&  Values[0].Status.Count == 5
        &&  Values[0].Status.Payload->Length == 2
        &&  Values[0].Status.Payload[0] == 6
        &&  Values[0].Status.Payload[1] == 7
        &&  Values[0].Timestamp == DateTime(888)
        &&  Values[0].TimestampSpecified == true
        &&  Values[0].Comment == "Comment1"
        &&  Values[1].HasQT
        &&  Values[1].HasQTSpecified 
        &&  Values[1].Value.Type == 9
        &&  Values[1].Value.Length == 10
        &&  Values[1].Value.Payload->Length == 2
        &&  Values[1].Value.Payload[0] == 11
        &&  Values[1].Value.Payload[1] == 12
        &&  Values[1].Status.Count == 13
        &&  Values[1].Status.Payload->Length == 2
        &&  Values[1].Status.Payload[0] == 14
        &&  Values[1].Status.Payload[1] == 15
        &&  Values[1].Timestamp == DateTime(1616)
        &&  Values[1].TimestampSpecified == true
        &&  Values[1].Comment == "Comment2";

    return result;

}
bool IDataProxy_MOCK::VerifyWriteValue(WriteValue Value)
{
    bool result = false;
    //public partial struct ASBStatus
    //{
    //    public sbyte Count
    //    public byte[] Payload
    //}


    //public partial struct Variant
    //{
    //    public ushort Type
    //    public int Length
    //    public byte[] Payload
    //}

    //public partial struct WriteValue
    //{
    //    public bool                       HasQT
    //    public bool                       HasQTSpecified
    //    public ASBIDataContract.Variant   Value
    //    public ASBStatus                  Status
    //    public System.DateTime            Timestamp
    //    public bool                       TimestampSpecified
    //    public string                     Comment
    //}
    


    result = 
            Value.HasQT
        &&  Value.HasQTSpecified 
        &&  Value.Value.Type == 1
        &&  Value.Value.Length == 2
        &&  Value.Value.Payload->Length == 2
        &&  Value.Value.Payload[0] == 3
        &&  Value.Value.Payload[1] == 4
        &&  Value.Status.Count == 5
        &&  Value.Status.Payload->Length == 2
        &&  Value.Status.Payload[0] == 6
        &&  Value.Status.Payload[1] == 7
        &&  Value.Timestamp == DateTime(888)
        &&  Value.TimestampSpecified == true
        &&  Value.Comment == "Comment1";

    return result;

}

bool IDataProxy_MOCK::VerifyUserTokenFirst(UserToken User)
{        
    bool result = 
            User.Encryption == 1
        &&  User.HostName == "Host1"
        &&  User.IdType == 2
        &&  User.LocationID == "LocationId1"
        &&  User.Password == "Password1"
        &&  User.SamlToken->Length == 2
        &&  User.SamlToken[0] == 3
        &&  User.SamlToken[1] == 4
        &&  User.UserName == "Username1"
        &&  User.Validity == 5
        &&  User.X509Certificate->Length == 2
        &&  User.X509Certificate[0] == 6
        &&  User.X509Certificate[1] == 7;

    return result;

}
bool IDataProxy_MOCK::VerifyUserTokenSecond(UserToken User)
{        
    bool result = 
            User.Encryption == 8
        &&  User.HostName == "Host2"
        &&  User.IdType == 9
        &&  User.LocationID == "LocationId2"
        &&  User.Password == "Password2"
        &&  User.SamlToken->Length == 2
        &&  User.SamlToken[0] == 10
        &&  User.SamlToken[1] == 11
        &&  User.UserName == "Username2"
        &&  User.Validity == 12
        &&  User.X509Certificate->Length == 2
        &&  User.X509Certificate[0] == 13
        &&  User.X509Certificate[1] == 14;

    return result;

}

bool IDataProxy_MOCK::VerifyMonitoredItemAry(array<MonitoredItem> ^ Items)
{
    //ArchestrAServices::ASBIDataV2Contract::MonitoredItem item;

    //ArchestrAServices::ASBIDataV2Contract::ItemIdentity ident;

    //ident = ItemIdentityV2Mgr::MakeFirst();
    //item.Item = ident;
    bool result = 
        Items[0].Item.Type == 1
    &&  Items[0].Item.ReferenceType== 2
    &&  Items[0].Item.Name == "identity"
    &&  Items[0].Item.ContextName == "CONTEXT"
    &&  Items[0].Item.Id == 3

        //ArchestrAServices::ASBIDataContract::V2::Variant vrnt;
        //item.ValueDeadband = vrnt;
    &&  Items[0].ValueDeadband.Type == 1
    &&  Items[0].ValueDeadband.Length == 2
    &&  Items[0].ValueDeadband.Payload->Length == 2
    &&  Items[0].ValueDeadband.Payload[0] == 3
    &&  Items[0].ValueDeadband.Payload[1] == 4
        //ArchestrAServices::ASBIDataContract::V2::Variant vrnt2;
        //item.UserData = vrnt2;
    &&  Items[0].UserData.Type == 5
    &&  Items[0].UserData.Length == 6
    &&  Items[0].UserData.Payload->Length == 2
    &&  Items[0].UserData.Payload[0] == 7
    &&  Items[0].UserData.Payload[1] == 8
    &&  Items[0].SampleInterval == 20
    &&  Items[0].Active == true
    &&  Items[0].ActiveSpecified==true
    &&  Items[0].TimeDeadband == 21
    &&  Items[0].TimeDeadbandSpecified==true

    &&  Items[1].Item.Type == 5
    &&  Items[1].Item.ReferenceType== 6
    &&  Items[1].Item.Name == "identity2"
    &&  Items[1].Item.ContextName == "CONTEXT2"
    &&  Items[1].Item.Id == 7

        //ArchestrAServices::ASBIDataContract::V2::Variant vrnt;
        //item.ValueDeadband = vrnt;
    &&  Items[1].ValueDeadband.Type == 9
    &&  Items[1].ValueDeadband.Length == 10
    &&  Items[1].ValueDeadband.Payload->Length == 2
    &&  Items[1].ValueDeadband.Payload[0] == 11
    &&  Items[1].ValueDeadband.Payload[1] == 12
        //ArchestrAServices::ASBIDataContract::V2::Variant vrnt2;
        //item.UserData = vrnt2;
    &&  Items[1].UserData.Type == 13
    &&  Items[1].UserData.Length == 14
    &&  Items[1].UserData.Payload->Length == 2
    &&  Items[1].UserData.Payload[0] == 15
    &&  Items[1].UserData.Payload[1] == 16
    &&  Items[1].SampleInterval == 22
    &&  Items[1].Active == true
    &&  Items[1].ActiveSpecified==true
    &&  Items[1].TimeDeadband == 23
    &&  Items[1].TimeDeadbandSpecified==true;


    return result;
}
void IDataProxy_MOCK::SetupGoodResult(ArchestrAResult %result)
{
    result.ErrorCode = 2;
    result.SpecificErrorCode = 3;
}
void IDataProxy_MOCK::SetupBadResult(ArchestrAResult %result)
{
    result.ErrorCode = 4;
    result.SpecificErrorCode = 5;
}

ArchestrAResult IDataProxy_MOCK::KeepAlive(ConnectionId Id)
{
    throw gcnew NotImplementedException();
}
//  Reading data.
ArchestrAResult IDataProxy_MOCK::Read(  array<ItemStatus>   ^% Status,
                                        array<RuntimeValue> ^% ItemValues, 
                                        ConnectionId Id, 
                                        array<ItemIdentity> ^ Items)
{
    ArchestrAResult result;

    SetupGoodResult(result);

    Status = gcnew array<ItemStatus>(2);
    Status[0] = ItemStatusMgr::MakeFirst();
    Status[1] = ItemStatusMgr::MakeSecond();

    ItemValues = gcnew array<RuntimeValue>(2);
    ItemValues[0] = RuntimeValueMgr::MakeV1First();
    ItemValues[1] = RuntimeValueMgr::MakeV1Second();

    if( ! VerifyItemIdentityAry(Items))
    {
        SetupBadResult(result);
    }
    if( Id.Id.ToString() != "11111111-2222-3333-4444-555555555555")
    {
        SetupBadResult(result);
    }
    return result;
}

//  Writing data.
//  WriteHandle for all write modes is a transaction handle that will be returned
//  in PublishWriteComplete().  Special values for WriteHandle are:
//      0: Non-overlapped write call, blocks until return.  PublishWriteComplete() will never contain this.
//      1: Overlapped, but the results will not be requested with PublishWriteComplete(), do not buffer or return.
//      100 and above: Valid write transaction handle.
ArchestrAResult IDataProxy_MOCK::Write( array<ItemStatus>   ^% Status, 
                                        ConnectionId Id, 
                                        array<ItemIdentity> ^ Items, 
                                        array<WriteValue>   ^ Values, 
                                        UInt32 WriteHandle)
{
    ArchestrAResult result;

    SetupGoodResult(result);

    Status = gcnew array<ItemStatus>(2);
    Status[0] = ItemStatusMgr::MakeFirst();
    Status[1] = ItemStatusMgr::MakeSecond();

    if( ! VerifyItemIdentityAry(Items))
    {
        SetupBadResult(result);
    }
    if( ! VerifyWriteValueAry(Values))
    {
        SetupBadResult(result);
    }
    if(     Id.Id.ToString() != "11111111-2222-3333-4444-555555555555"
        ||  WriteHandle != 444)
    {
        SetupBadResult(result);
    }
    return result;

}

ArchestrAResult IDataProxy_MOCK::WriteUser( array<ItemStatus>   ^% Status, 
                                            ConnectionId Id, 
                                            array<ItemIdentity> ^ Items, 
                                            array<WriteValue>   ^ Values, 
                                            UserToken           User, 
                                            unsigned int  WriteHandle)
{
    ArchestrAResult result;

    SetupGoodResult(result);

    Status = gcnew array<ItemStatus>(2);
    Status[0] = ItemStatusMgr::MakeFirst();
    Status[1] = ItemStatusMgr::MakeSecond();

    if( ! VerifyItemIdentityAry(Items))
    {
        SetupBadResult(result);
    }
    if( ! VerifyWriteValueAry(Values))
    {
        SetupBadResult(result);
    }

    if( ! VerifyUserTokenFirst(User))
    {
        SetupBadResult(result);
    }

    if(     Id.Id.ToString() != "11111111-2222-3333-4444-555555555555"
        ||  WriteHandle != 444)
    {
        SetupBadResult(result);
    }
    return result;
}

ArchestrAResult IDataProxy_MOCK::WriteVerified( array<ItemStatus>   ^% Status, 
                                                ConnectionId Id, 
                                                array<ItemIdentity> ^ Items, 
                                                array<WriteValue> ^ Values, 
                                                UserToken User, 
                                                UserToken Supervisor, 
                                                unsigned int WriteHandle)
{
    ArchestrAResult result;

    SetupGoodResult(result);

    Status = gcnew array<ItemStatus>(2);
    Status[0] = ItemStatusMgr::MakeFirst();
    Status[1] = ItemStatusMgr::MakeSecond();

    if( ! VerifyItemIdentityAry(Items))
    {
        SetupBadResult(result);
    }
    if( ! VerifyWriteValueAry(Values))
    {
        SetupBadResult(result);
    }

    if( ! VerifyUserTokenFirst(User))
    {
        SetupBadResult(result);
    }
    if( ! VerifyUserTokenSecond(Supervisor))
    {
        SetupBadResult(result);
    }

    if(     Id.Id.ToString() != "11111111-2222-3333-4444-555555555555"
        ||  WriteHandle != 444)
    {
        SetupBadResult(result);
    }
    return result;
}

//US-51105 - WriteSecured method
ArchestrAResult IDataProxy_MOCK::WriteSecured(  array<ItemStatus>   ^% Status, 
                                                ConnectionId Id, 
                                                array<ItemIdentity> ^ Items, 
                                                array<WriteValue> ^ Values, 
                                                UserToken User, 
                                                unsigned int WriteHandle)
{
    ArchestrAResult result;

    SetupGoodResult(result);

    Status = gcnew array<ItemStatus>(2);
    Status[0] = ItemStatusMgr::MakeFirst();
    Status[1] = ItemStatusMgr::MakeSecond();

    if( ! VerifyItemIdentityAry(Items))
    {
        SetupBadResult(result);
    }
    if( ! VerifyWriteValueAry(Values))
    {
        SetupBadResult(result);
    }

    if( ! VerifyUserTokenFirst(User))
    {
        SetupBadResult(result);
    }

    if(     Id.Id.ToString() != "11111111-2222-3333-4444-555555555555"
        ||  WriteHandle != 444)
    {
        SetupBadResult(result);
    }
    return result;

}

ArchestrAResult IDataProxy_MOCK::PublishWriteComplete(  array<ItemWriteComplete> ^% CompleteWrites, 
                                                        ConnectionId Id)
{
    ArchestrAResult result;

    SetupGoodResult(result);

    CompleteWrites = gcnew array<ItemWriteComplete>(2);
    CompleteWrites[0] = ItemWriteCompleteMgr::MakeFirst();
    CompleteWrites[1] = ItemWriteCompleteMgr::MakeSecond(); 

    if(     Id.Id.ToString() != "11111111-2222-3333-4444-555555555555")
    {
        SetupBadResult(result);
    }
    return result;

}

//  Subscriptions.
ArchestrAResult IDataProxy_MOCK::CreateSubscription(__int64 % SubscriptionId, 
                                                    ConnectionId Id, 
                                                    __int64 MaxQueueSize, 
                                                    unsigned __int64 SampleInterval)
{
    ArchestrAResult result;

    SetupGoodResult(result);

    SubscriptionId = 999;

    if(     Id.Id.ToString() != "11111111-2222-3333-4444-555555555555"
        ||  MaxQueueSize !=     1010
        ||  SampleInterval !=   1111)
    {
        SetupBadResult(result);
    }
    return result;

}


ArchestrAResult IDataProxy_MOCK::DeleteSubscription(ConnectionId Id, 
                                                    __int64 SubscriptionId)
{
    ArchestrAResult result;

    SetupGoodResult(result);


    if(     Id.Id.ToString() != "11111111-2222-3333-4444-555555555555"
        ||  SubscriptionId != 999)
    {
        SetupBadResult(result);
    }
    return result;
}

ArchestrAResult IDataProxy_MOCK::AddMonitoredItems( array<ItemStatus>   ^% Status, 
                                                    array<ItemRegistration> ^% ItemCapabilities,
                                                    ConnectionId Id, 
                                                    __int64 SubscriptionId, 
                                                    array<MonitoredItem> ^ Items, 
                                                    unsigned char RequireId)
{
    ArchestrAResult result;

    SetupGoodResult(result);

    Status = gcnew array<ItemStatus>(2);
    Status[0] = ItemStatusMgr::MakeFirst();
    Status[1] = ItemStatusMgr::MakeSecond();

    ItemCapabilities = gcnew array<ItemRegistration>(2);
    ItemCapabilities[0] = ItemRegistrationMgr::MakeFirst();
    ItemCapabilities[1] = ItemRegistrationMgr::MakeSecond();

    if( ! VerifyMonitoredItemAry(Items))
    {
        SetupBadResult(result);
    }

    if(     Id.Id.ToString() != "11111111-2222-3333-4444-555555555555"
        ||  SubscriptionId != 999
        ||  RequireId != 21)
    {
        SetupBadResult(result);
    }
    return result;
}

ArchestrAResult IDataProxy_MOCK::DeleteMonitoredItems(  array<ItemStatus>   ^% Status, 
                                                        ConnectionId Id, 
                                                        __int64 SubscriptionId, 
                                                        array<MonitoredItem> ^ Items)
{
    //TODO rjk Implement this code path
    throw gcnew NotImplementedException();
}


ArchestrAResult IDataProxy_MOCK::Publish(array<ItemStatus>           ^% Status, 
                                array<MonitoredItemValue>   ^% Values, 
                                ConnectionId Id, 
                                __int64 SubscriptionId)
{
    //TODO rjk Implement this code path
    throw gcnew NotImplementedException();
}

ArchestrAResult IDataProxy_MOCK::RegisterItems( array<ItemStatus>   ^% Status, 
                                                array<ItemRegistration> ^% ItemCapabilities,
                                                ConnectionId Id, 
                                                array<ItemIdentity> ^ Items, 
                                                unsigned char RequireId, 
                                                unsigned char RegisterOnly)
{
    //TODO rjk Implement this code path
    throw gcnew NotImplementedException();
}

ArchestrAResult IDataProxy_MOCK::UnregisterItems(   array<ItemStatus>   ^% Status, 
                                                    ConnectionId Id, 
                                                    array<ItemIdentity> ^ Items)
{
    //TODO rjk Implement this code path
    throw gcnew NotImplementedException();
}

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// all implementations below are 
// needed for mock implementation only.. 
// they are **NOT** used by consumer.
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void IDataProxy_MOCK::OnDisconnect(ConnectionId Id)
{
    throw gcnew NotImplementedException();
}


ArchestrAResult IDataProxy_MOCK::ActivateUser(  ConnectionId Id, 
                                                UserToken UserToken)
{
    throw gcnew NotImplementedException();
}

ArchestrAResult IDataProxy_MOCK::ExchangeCapabilities(  String ^% ServiceCapabilities, 
                                                        ConnectionId Id, 
                                                        String ^  ClientCapabilities)
{
    throw gcnew NotImplementedException();
}

void IDataProxy_MOCK::OnConnect(ConnectionId ConnectionId, 
                                unsigned __int64 Timeout)
{
    throw gcnew NotImplementedException();
}
ArchestrAResult IDataProxy_MOCK::WriteConfirmed(WriteValue % ValueReceived, 
                                                __int64 % WriteToken,
                                                ConnectionId Id, 
                                                ItemIdentity Item, 
                                                WriteValue Value, 
                                                UserToken User, 
                                                UserToken Supervisor)
{
#if 0
    ArchestrAResult result;

    SetupGoodResult(result);

    ValueReceived = WriteValueMgr::MakeV1Second();
    WriteToken = 777;

    if( ! VerifyWriteValue(Value))
    {
        SetupBadResult(result);
    }

    if( ! VerifyItemIdentity(Item))
    {
        SetupBadResult(result);
    }

    if( ! VerifyUserTokenFirst(User))
    {
        SetupBadResult(result);
    }

    if( ! VerifyUserTokenSecond(Supervisor))
    {
        SetupBadResult(result);
    }

    if(     Id.Id.ToString() != "11111111-2222-3333-4444-555555555555")
    {
        SetupBadResult(result);
    }
    return result;
#endif
    // not used by Consumer.
    throw gcnew NotImplementedException();

}

ArchestrAResult IDataProxy_MOCK::ConfirmWrite(  ConnectionId Id, 
                                                ItemIdentity Item, 
                                                __int64 WriteToken, 
                                                WriteValue Value, 
                                                UserToken User, 
                                                UserToken Supervisor, 
                                                unsigned int WriteHandle)
{
    // not used by Consumer.
    throw gcnew NotImplementedException();
}

ArchestrAResult IDataProxy_MOCK::SetSubscriptionState(  ConnectionId Id, 
                                                        __int64 SubscriptionId, 
                                                        ArchestrAServices::ASBIDataContract::Variant NewState, 
                                                        unsigned short StateToChange /*enum SubscriptionStateType*/)
{
    throw gcnew NotImplementedException();
}

ArchestrAResult IDataProxy_MOCK::GetSubscriptionState(  ArchestrAServices::ASBIDataContract::Variant % State, 
                                                        ConnectionId Id, 
                                                        __int64 SubscriptionId, 
                                                        unsigned short StateToGet /*enum SubscriptionStateType*/)
{
    throw gcnew NotImplementedException();
}

ArchestrAResult IDataProxy_MOCK::GetMonitoredItems( array<MonitoredItem> ^% Items, 
                                                    ConnectionId Id, 
                                                    __int64 SubscriptionId)
{
    throw gcnew NotImplementedException();
}

