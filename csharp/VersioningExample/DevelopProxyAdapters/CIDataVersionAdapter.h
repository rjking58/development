

using namespace System;
using namespace ArchestrAServices::ASBContract;
using namespace ArchestrAServices::ASBIDataV2Contract;
using namespace ArchestrAServices::Proxy;


public ref class CIDataVersionAdapter 
{
public:


        virtual bool Connect(String ^% errorMessage) = 0;

        virtual void Abort() = 0;

        virtual void Disconnect() = 0;

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



        virtual ArchestrAResult KeepAlive(ConnectionId Id) = 0;

        //  Reading data.
        virtual ArchestrAResult Read(  array<ArchestrAServices::ASBIDataV2Contract::ItemStatus>   ^% Status,
                                array<ArchestrAServices::ASBIDataV2Contract::RuntimeValue> ^% ItemValues, 
                                ConnectionId Id, 
                                array<ArchestrAServices::ASBIDataV2Contract::ItemIdentity> ^ Items) = 0;

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
                                        UInt32 WriteHandle) = 0;

        virtual ArchestrAResult WriteUser(  array<ArchestrAServices::ASBIDataV2Contract::ItemStatus>   ^% Status, 
                                            ConnectionId Id, 
                                            array<ArchestrAServices::ASBIDataV2Contract::ItemIdentity> ^ Items, 
                                            array<ArchestrAServices::ASBIDataV2Contract::WriteValue>   ^ Values, 
                                            ArchestrAServices::ASBIDataV2Contract::UserToken           User, 
                                            unsigned int  WriteHandle) = 0;

        virtual ArchestrAResult WriteVerified(  array<ArchestrAServices::ASBIDataV2Contract::ItemStatus>   ^% Status, 
                                        ConnectionId Id, 
                                        array<ArchestrAServices::ASBIDataV2Contract::ItemIdentity> ^ Items, 
                                        array<ArchestrAServices::ASBIDataV2Contract::WriteValue> ^ Values, 
                                        ArchestrAServices::ASBIDataV2Contract::UserToken User, 
                                        ArchestrAServices::ASBIDataV2Contract::UserToken Supervisor, 
                                        unsigned int WriteHandle) = 0;

        //US-51105 - WriteSecured method
        virtual ArchestrAResult WriteSecured(   array<ArchestrAServices::ASBIDataV2Contract::ItemStatus>   ^% Status, 
                                                ConnectionId Id, 
                                                array<ArchestrAServices::ASBIDataV2Contract::ItemIdentity> ^ Items, 
                                                array<ArchestrAServices::ASBIDataV2Contract::WriteValue> ^ Values, 
                                                ArchestrAServices::ASBIDataV2Contract::UserToken User, 
                                                unsigned int WriteHandle) = 0;

        virtual ArchestrAResult WriteConfirmed( ArchestrAServices::ASBIDataV2Contract::WriteValue % ValueReceived, 
                                                __int64 % WriteToken,
                                                ConnectionId Id, 
                                                ArchestrAServices::ASBIDataV2Contract::ItemIdentity Item, 
                                                ArchestrAServices::ASBIDataV2Contract::WriteValue Value, 
                                                ArchestrAServices::ASBIDataV2Contract::UserToken User, 
                                                ArchestrAServices::ASBIDataV2Contract::UserToken Supervisor) = 0;

        virtual ArchestrAResult ConfirmWrite(   ConnectionId Id, 
                                                ArchestrAServices::ASBIDataV2Contract::ItemIdentity Item, 
                                                __int64 WriteToken, 
                                                ArchestrAServices::ASBIDataV2Contract::WriteValue Value, 
                                                ArchestrAServices::ASBIDataV2Contract::UserToken User, 
                                                ArchestrAServices::ASBIDataV2Contract::UserToken Supervisor, 
                                                unsigned int WriteHandle) = 0;

        virtual ArchestrAResult PublishWriteComplete(   array<ArchestrAServices::ASBIDataV2Contract::ItemWriteComplete> ^% CompleteWrites, 
                                                        ConnectionId Id) = 0;

        //  Subscriptions.
        virtual ArchestrAResult CreateSubscription( __int64 % SubscriptionId, 
                                                    ConnectionId Id, 
                                                    __int64 MaxQueueSize, 
                                                    unsigned __int64 SampleInterval) = 0;

        virtual ArchestrAResult SetSubscriptionState(   ConnectionId Id, 
                                                        __int64 SubscriptionId, 
                                                        ArchestrAServices::ASBIDataContract::V2::Variant NewState, 
                                                        unsigned short StateToChange /*enum SubscriptionStateType*/) = 0;

        virtual ArchestrAResult GetSubscriptionState(   ArchestrAServices::ASBIDataContract::V2::Variant % State, 
                                                        ConnectionId Id, 
                                                        __int64 SubscriptionId, 
                                                        unsigned short StateToGet /*enum SubscriptionStateType*/) = 0;

        virtual ArchestrAResult DeleteSubscription( ConnectionId Id, 
                                            __int64 SubscriptionId) = 0;

        virtual ArchestrAResult AddMonitoredItems(  array<ArchestrAServices::ASBIDataV2Contract::ItemStatus>   ^% Status, 
                                                    array<ArchestrAServices::ASBIDataV2Contract::ItemRegistration> ^% ItemCapabilities,
                                                    ConnectionId Id, 
                                                    __int64 SubscriptionId, 
                                                    array<ArchestrAServices::ASBIDataV2Contract::MonitoredItem> ^ Items, 
                                                    unsigned char RequireId) = 0;

        virtual ArchestrAResult DeleteMonitoredItems(   array<ArchestrAServices::ASBIDataV2Contract::ItemStatus>   ^% Status, 
                                                        ConnectionId Id, 
                                                        __int64 SubscriptionId, 
                                                        array<ArchestrAServices::ASBIDataV2Contract::MonitoredItem> ^ Items) = 0;

        virtual ArchestrAResult GetMonitoredItems(  array<ArchestrAServices::ASBIDataV2Contract::MonitoredItem> ^% Items, 
                                                    ConnectionId Id, 
                                                    __int64 SubscriptionId) = 0;

        virtual ArchestrAResult Publish(array<ArchestrAServices::ASBIDataV2Contract::ItemStatus>           ^% Status, 
                                        array<ArchestrAServices::ASBIDataV2Contract::MonitoredItemValue>   ^% Values, 
                                        ConnectionId Id, 
                                        __int64 SubscriptionId) = 0;

        virtual ArchestrAResult RegisterItems(  array<ArchestrAServices::ASBIDataV2Contract::ItemStatus>   ^% Status, 
                                        array<ArchestrAServices::ASBIDataV2Contract::ItemRegistration> ^% ItemCapabilities,
                                        ConnectionId Id, 
                                        array<ArchestrAServices::ASBIDataV2Contract::ItemIdentity> ^ Items, 
                                        unsigned char RequireId, 
                                        unsigned char RegisterOnly) = 0;

        virtual ArchestrAResult UnregisterItems(array<ArchestrAServices::ASBIDataV2Contract::ItemStatus>   ^% Status, 
                                                ConnectionId Id, 
                                                array<ArchestrAServices::ASBIDataV2Contract::ItemIdentity> ^ Items) = 0;
};
