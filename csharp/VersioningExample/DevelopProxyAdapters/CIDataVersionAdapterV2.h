
#include "CIDataVersionAdapter.h"



public ref class CIDataVersionAdapterV2 : public CIDataVersionAdapter
{
private:
    IDataV2 ^   m_ASBProxy;
public:

    CIDataVersionAdapterV2(IDataV2 ^ASBProxy)   :   m_ASBProxy(ASBProxy)
    {
    }

    virtual bool Connect(String ^% errorMessage) override;

    virtual void Abort() override;

    virtual void Disconnect() override;

    // a property
    // since we must now use an interface, we'll need to put
    // access to this behind a method.
    // the MxConsumer's use of this is read only, so a getter should be find for now
    virtual property Guid ConnectionIdProp
    { 
        Guid get() override
        {
            Guid myGuid("x");
            return myGuid;
        }
    };



    virtual ArchestrAResult KeepAlive(ConnectionId Id) override;

    //  Reading data.
    virtual ArchestrAResult Read(  array<ArchestrAServices::ASBIDataV2Contract::ItemStatus>   ^% Status,
                            array<ArchestrAServices::ASBIDataV2Contract::RuntimeValue> ^% ItemValues, 
                            ConnectionId Id, 
                            array<ArchestrAServices::ASBIDataV2Contract::ItemIdentity> ^ Items) override;

    //  Writing data.
    //  WriteHandle for all write modes is a transaction handle that will be returned
    //  in PublishWriteComplete().  Special values for WriteHandle are:
    //      0: Non-overlapped write call, blocks until return.  PublishWriteComplete() will never contain this.
    //      1: Overlapped, but the results will not be requested with PublishWriteComplete(), do not buffer or return.
    //      100 and above: Valid write transaction handle.
    virtual ArchestrAResult Write( array<ArchestrAServices::ASBIDataV2Contract::ItemStatus>   ^% Status, 
                                    ConnectionId Id, 
                                    array<ArchestrAServices::ASBIDataV2Contract::ItemIdentity> ^ Items, 
                                    array<ArchestrAServices::ASBIDataV2Contract::WriteValue>   ^ Values, 
                                    UInt32 WriteHandle) override;

    virtual ArchestrAResult WriteUser(  array<ArchestrAServices::ASBIDataV2Contract::ItemStatus>   ^% Status, 
                                        ConnectionId Id, 
                                        array<ArchestrAServices::ASBIDataV2Contract::ItemIdentity> ^ Items, 
                                        array<ArchestrAServices::ASBIDataV2Contract::WriteValue>   ^ Values, 
                                        ArchestrAServices::ASBIDataV2Contract::UserToken           User, 
                                        unsigned int  WriteHandle) override;

    virtual ArchestrAResult WriteVerified(  array<ArchestrAServices::ASBIDataV2Contract::ItemStatus>   ^% Status, 
                                    ConnectionId Id, 
                                    array<ArchestrAServices::ASBIDataV2Contract::ItemIdentity> ^ Items, 
                                    array<ArchestrAServices::ASBIDataV2Contract::WriteValue> ^ Values, 
                                    ArchestrAServices::ASBIDataV2Contract::UserToken User, 
                                    ArchestrAServices::ASBIDataV2Contract::UserToken Supervisor, 
                                    unsigned int WriteHandle) override;

    //US-51105 - WriteSecured method
    virtual ArchestrAResult WriteSecured(   array<ArchestrAServices::ASBIDataV2Contract::ItemStatus>   ^% Status, 
                                            ConnectionId Id, 
                                            array<ArchestrAServices::ASBIDataV2Contract::ItemIdentity> ^ Items, 
                                            array<ArchestrAServices::ASBIDataV2Contract::WriteValue> ^ Values, 
                                            ArchestrAServices::ASBIDataV2Contract::UserToken User, 
                                            unsigned int WriteHandle) override;

    virtual ArchestrAResult WriteConfirmed( ArchestrAServices::ASBIDataV2Contract::WriteValue % ValueReceived, 
                                            __int64 % WriteToken,
                                            ConnectionId Id, 
                                            ArchestrAServices::ASBIDataV2Contract::ItemIdentity Item, 
                                            ArchestrAServices::ASBIDataV2Contract::WriteValue Value, 
                                            ArchestrAServices::ASBIDataV2Contract::UserToken User, 
                                            ArchestrAServices::ASBIDataV2Contract::UserToken Supervisor) override;

    virtual ArchestrAResult ConfirmWrite(   ConnectionId Id, 
                                            ArchestrAServices::ASBIDataV2Contract::ItemIdentity Item, 
                                            __int64 WriteToken, 
                                            ArchestrAServices::ASBIDataV2Contract::WriteValue Value, 
                                            ArchestrAServices::ASBIDataV2Contract::UserToken User, 
                                            ArchestrAServices::ASBIDataV2Contract::UserToken Supervisor, 
                                            unsigned int WriteHandle) override;

    virtual ArchestrAResult PublishWriteComplete(   array<ArchestrAServices::ASBIDataV2Contract::ItemWriteComplete> ^% CompleteWrites, 
                                                    ConnectionId Id) override;

    //  Subscriptions.
    virtual ArchestrAResult CreateSubscription( __int64 % SubscriptionId, 
                                                ConnectionId Id, 
                                                __int64 MaxQueueSize, 
                                                unsigned __int64 SampleInterval) override;

    virtual ArchestrAResult SetSubscriptionState(   ConnectionId Id, 
                                                    __int64 SubscriptionId, 
                                                    ArchestrAServices::ASBIDataContract::V2::Variant NewState, 
                                                    unsigned short StateToChange /*enum SubscriptionStateType*/) override;

    virtual ArchestrAResult GetSubscriptionState(   ArchestrAServices::ASBIDataContract::V2::Variant % State, 
                                                    ConnectionId Id, 
                                                    __int64 SubscriptionId, 
                                                    unsigned short StateToGet /*enum SubscriptionStateType*/) override;

    virtual ArchestrAResult DeleteSubscription( ConnectionId Id, 
                                        __int64 SubscriptionId) override;

    virtual ArchestrAResult AddMonitoredItems(  array<ArchestrAServices::ASBIDataV2Contract::ItemStatus>   ^% Status, 
                                                array<ArchestrAServices::ASBIDataV2Contract::ItemRegistration> ^% ItemCapabilities,
                                                ConnectionId Id, 
                                                __int64 SubscriptionId, 
                                                array<ArchestrAServices::ASBIDataV2Contract::MonitoredItem> ^ Items, 
                                                unsigned char RequireId) override;

    virtual ArchestrAResult DeleteMonitoredItems(   array<ArchestrAServices::ASBIDataV2Contract::ItemStatus>   ^% Status, 
                                                    ConnectionId Id, 
                                                    __int64 SubscriptionId, 
                                                    array<ArchestrAServices::ASBIDataV2Contract::MonitoredItem> ^ Items) override;

    virtual ArchestrAResult GetMonitoredItems(  array<ArchestrAServices::ASBIDataV2Contract::MonitoredItem> ^% Items, 
                                                ConnectionId Id, 
                                                __int64 SubscriptionId) override;

    virtual ArchestrAResult Publish(array<ArchestrAServices::ASBIDataV2Contract::ItemStatus>           ^% Status, 
                                    array<ArchestrAServices::ASBIDataV2Contract::MonitoredItemValue>   ^% Values, 
                                    ConnectionId Id, 
                                    __int64 SubscriptionId) override;

    virtual ArchestrAResult RegisterItems(  array<ArchestrAServices::ASBIDataV2Contract::ItemStatus>   ^% Status, 
                                    array<ArchestrAServices::ASBIDataV2Contract::ItemRegistration> ^% ItemCapabilities,
                                    ConnectionId Id, 
                                    array<ArchestrAServices::ASBIDataV2Contract::ItemIdentity> ^ Items, 
                                    unsigned char RequireId, 
                                    unsigned char RegisterOnly) override;

    virtual ArchestrAResult UnregisterItems(array<ArchestrAServices::ASBIDataV2Contract::ItemStatus>   ^% Status, 
                                            ConnectionId Id, 
                                            array<ArchestrAServices::ASBIDataV2Contract::ItemIdentity> ^ Items) override;
};
