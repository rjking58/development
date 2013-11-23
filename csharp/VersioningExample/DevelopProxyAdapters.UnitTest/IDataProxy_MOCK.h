

using namespace System;
using namespace ArchestrAServices::ASBContract;
using namespace ArchestrAServices::ASBIDataContract;
using namespace ArchestrAServices::Proxy;


public ref class IDataProxy_MOCK : public IData
{

public:
       
    // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    // mock control and state discovery
    // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    bool AbortCalled;
    bool DisconnectCalled;

    void ResetMock()
    {
        AbortCalled = false;
        DisconnectCalled = false;
    }

    IDataProxy_MOCK()
    {
        ResetMock();
    }

    bool VerifyItemIdentityAry(array<ItemIdentity> ^ Items);
    bool VerifyWriteValueAry(array<WriteValue>   ^ Values);
    bool VerifyItemIdentity(ItemIdentity Item);
    bool VerifyWriteValue(WriteValue Value);

    void SetupGoodResult(ArchestrAResult %result);
    void SetupBadResult(ArchestrAResult %result);
    bool VerifyUserTokenFirst(UserToken User);
    bool VerifyUserTokenSecond(UserToken User);
    bool VerifyMonitoredItemAry(array<MonitoredItem> ^ Items);


    // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    // implementation of interface from public inheritance.
    // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    virtual bool Connect(String ^% errorMessage);
    virtual void Abort();
    virtual void Disconnect();

    // a property
    // since we must now use an interface, we'll need to put
    // access to this behind a method.
    // the MxConsumer's use of this is read only, so a getter should be find for now
    virtual property Guid ConnectionIdProp
    { 
        Guid get()
        {
            Guid myGuid("x");
            return myGuid;
        }
    }



    virtual ArchestrAResult KeepAlive(ConnectionId Id);
    //  Reading data.
    virtual ArchestrAResult Read(  array<ItemStatus>   ^% Status,
                            array<RuntimeValue> ^% ItemValues, 
                            ConnectionId Id, 
                            array<ItemIdentity> ^ Items);

    //  Writing data.
    //  WriteHandle for all write modes is a transaction handle that will be returned
    //  in PublishWriteComplete().  Special values for WriteHandle are:
    //      0: Non-overlapped write call, blocks until return.  PublishWriteComplete() will never contain this.
    //      1: Overlapped, but the results will not be requested with PublishWriteComplete(), do not buffer or return.
    //      100 and above: Valid write transaction handle.
    virtual ArchestrAResult Write( array<ItemStatus>   ^% Status, 
                                    ConnectionId Id, 
                                    array<ItemIdentity> ^ Items, 
                                    array<WriteValue>   ^ Values, 
                                    UInt32 WriteHandle);

    virtual ArchestrAResult WriteUser(  array<ItemStatus>   ^% Status, 
                                        ConnectionId Id, 
                                        array<ItemIdentity> ^ Items, 
                                        array<WriteValue>   ^ Values, 
                                        UserToken           User, 
                                        unsigned int  WriteHandle);

    virtual ArchestrAResult WriteVerified(  array<ItemStatus>   ^% Status, 
                                    ConnectionId Id, 
                                    array<ItemIdentity> ^ Items, 
                                    array<WriteValue> ^ Values, 
                                    UserToken User, 
                                    UserToken Supervisor, 
                                    unsigned int WriteHandle);
    //US-51105 - WriteSecured method
    virtual ArchestrAResult WriteSecured(   array<ItemStatus>   ^% Status, 
                                            ConnectionId Id, 
                                            array<ItemIdentity> ^ Items, 
                                            array<WriteValue> ^ Values, 
                                            UserToken User, 
                                            unsigned int WriteHandle);

    virtual ArchestrAResult WriteConfirmed( WriteValue % ValueReceived, 
                                            __int64 % WriteToken,
                                            ConnectionId Id, 
                                            ItemIdentity Item, 
                                            WriteValue Value, 
                                            UserToken User, 
                                            UserToken Supervisor);

    virtual ArchestrAResult ConfirmWrite(   ConnectionId Id, 
                                            ItemIdentity Item, 
                                            __int64 WriteToken, 
                                            WriteValue Value, 
                                            UserToken User, 
                                            UserToken Supervisor, 
                                            unsigned int WriteHandle);

    virtual ArchestrAResult PublishWriteComplete(   array<ItemWriteComplete> ^% CompleteWrites, 
                                                    ConnectionId Id);

    //  Subscriptions.
    virtual ArchestrAResult CreateSubscription( __int64 % SubscriptionId, 
                                                ConnectionId Id, 
                                                __int64 MaxQueueSize, 
                                                unsigned __int64 SampleInterval);

    virtual ArchestrAResult SetSubscriptionState(   ConnectionId Id, 
                                                    __int64 SubscriptionId, 
                                                    ArchestrAServices::ASBIDataContract::Variant NewState, 
                                                    unsigned short StateToChange /*enum SubscriptionStateType*/);

    virtual ArchestrAResult GetSubscriptionState(   ArchestrAServices::ASBIDataContract::Variant % State, 
                                                    ConnectionId Id, 
                                                    __int64 SubscriptionId, 
                                                    unsigned short StateToGet /*enum SubscriptionStateType*/);

    virtual ArchestrAResult DeleteSubscription( ConnectionId Id, 
                                        __int64 SubscriptionId);

    virtual ArchestrAResult AddMonitoredItems(  array<ItemStatus>   ^% Status, 
                                                array<ItemRegistration> ^% ItemCapabilities,
                                                ConnectionId Id, 
                                                __int64 SubscriptionId, 
                                                array<MonitoredItem> ^ Items, 
                                                unsigned char RequireId);

    virtual ArchestrAResult DeleteMonitoredItems(   array<ItemStatus>   ^% Status, 
                                                    ConnectionId Id, 
                                                    __int64 SubscriptionId, 
                                                    array<MonitoredItem> ^ Items);

    virtual ArchestrAResult GetMonitoredItems(  array<MonitoredItem> ^% Items, 
                                                ConnectionId Id, 
                                                __int64 SubscriptionId);

    virtual ArchestrAResult Publish(array<ItemStatus>           ^% Status, 
                                    array<MonitoredItemValue>   ^% Values, 
                                    ConnectionId Id, 
                                    __int64 SubscriptionId);

    virtual ArchestrAResult RegisterItems(  array<ItemStatus>   ^% Status, 
                                    array<ItemRegistration> ^% ItemCapabilities,
                                    ConnectionId Id, 
                                    array<ItemIdentity> ^ Items, 
                                    unsigned char RequireId, 
                                    unsigned char RegisterOnly);

    virtual ArchestrAResult UnregisterItems(array<ItemStatus>   ^% Status, 
                                            ConnectionId Id, 
                                            array<ItemIdentity> ^ Items);

    // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    // all implementations below are 
    // needed for mock implementation only.. 
    // they are **NOT** used by consumer.
    // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    virtual void OnDisconnect(ConnectionId Id);

    virtual property ArchestrAServices::Contract::IAsbInterfaceSettings^ Settings 
    {  
        ArchestrAServices::Contract::IAsbInterfaceSettings^ get()
        {
            throw gcnew NotImplementedException();
        }
    }

    virtual ArchestrAResult ActivateUser(   ConnectionId Id, 
                                            UserToken UserToken);

    virtual ArchestrAResult ExchangeCapabilities(   String ^% ServiceCapabilities, 
                                                    ConnectionId Id, 
                                                    String ^  ClientCapabilities);

    virtual void OnConnect(ConnectionId ConnectionId, unsigned __int64 Timeout);


};
