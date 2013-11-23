

using namespace System;
using namespace ArchestrAServices::ASBContract;
using namespace ArchestrAServices::ASBIDataV2Contract;
using namespace ArchestrAServices::Proxy;


public ref class IDataProxyV2_MOCK : public IDataV2
{
public:


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
        virtual ArchestrAResult Read(  array<ArchestrAServices::ASBIDataV2Contract::ItemStatus>   ^% Status,
                                array<ArchestrAServices::ASBIDataV2Contract::RuntimeValue> ^% ItemValues, 
                                ConnectionId Id, 
                                array<ArchestrAServices::ASBIDataV2Contract::ItemIdentity> ^ Items);

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
                                        UInt32 WriteHandle);

        virtual ArchestrAResult WriteUser(  array<ArchestrAServices::ASBIDataV2Contract::ItemStatus>   ^% Status, 
                                            ConnectionId Id, 
                                            array<ArchestrAServices::ASBIDataV2Contract::ItemIdentity> ^ Items, 
                                            array<ArchestrAServices::ASBIDataV2Contract::WriteValue>   ^ Values, 
                                            ArchestrAServices::ASBIDataV2Contract::UserToken           User, 
                                            unsigned int  WriteHandle);

        virtual ArchestrAResult WriteVerified(  array<ArchestrAServices::ASBIDataV2Contract::ItemStatus>   ^% Status, 
                                        ConnectionId Id, 
                                        array<ArchestrAServices::ASBIDataV2Contract::ItemIdentity> ^ Items, 
                                        array<ArchestrAServices::ASBIDataV2Contract::WriteValue> ^ Values, 
                                        ArchestrAServices::ASBIDataV2Contract::UserToken User, 
                                        ArchestrAServices::ASBIDataV2Contract::UserToken Supervisor, 
                                        unsigned int WriteHandle);

        //US-51105 - WriteSecured method
        virtual ArchestrAResult WriteSecured(   array<ArchestrAServices::ASBIDataV2Contract::ItemStatus>   ^% Status, 
                                                ConnectionId Id, 
                                                array<ArchestrAServices::ASBIDataV2Contract::ItemIdentity> ^ Items, 
                                                array<ArchestrAServices::ASBIDataV2Contract::WriteValue> ^ Values, 
                                                ArchestrAServices::ASBIDataV2Contract::UserToken User, 
                                                unsigned int WriteHandle);

        virtual ArchestrAResult WriteConfirmed( ArchestrAServices::ASBIDataV2Contract::WriteValue % ValueReceived, 
                                                __int64 % WriteToken,
                                                ConnectionId Id, 
                                                ArchestrAServices::ASBIDataV2Contract::ItemIdentity Item, 
                                                ArchestrAServices::ASBIDataV2Contract::WriteValue Value, 
                                                ArchestrAServices::ASBIDataV2Contract::UserToken User, 
                                                ArchestrAServices::ASBIDataV2Contract::UserToken Supervisor);

        virtual ArchestrAResult ConfirmWrite(   ConnectionId Id, 
                                                ArchestrAServices::ASBIDataV2Contract::ItemIdentity Item, 
                                                __int64 WriteToken, 
                                                ArchestrAServices::ASBIDataV2Contract::WriteValue Value, 
                                                ArchestrAServices::ASBIDataV2Contract::UserToken User, 
                                                ArchestrAServices::ASBIDataV2Contract::UserToken Supervisor, 
                                                unsigned int WriteHandle);

        virtual ArchestrAResult PublishWriteComplete(   array<ArchestrAServices::ASBIDataV2Contract::ItemWriteComplete> ^% CompleteWrites, 
                                                        ConnectionId Id);

        //  Subscriptions.
        virtual ArchestrAResult CreateSubscription( __int64 % SubscriptionId, 
                                                    ConnectionId Id, 
                                                    __int64 MaxQueueSize, 
                                                    unsigned __int64 SampleInterval);

        virtual ArchestrAResult SetSubscriptionState(   ConnectionId Id, 
                                                        __int64 SubscriptionId, 
                                                        ArchestrAServices::ASBIDataContract::V2::Variant NewState, 
                                                        unsigned short StateToChange /*enum SubscriptionStateType*/);

        virtual ArchestrAResult GetSubscriptionState(   ArchestrAServices::ASBIDataContract::V2::Variant % State, 
                                                        ConnectionId Id, 
                                                        __int64 SubscriptionId, 
                                                        unsigned short StateToGet /*enum SubscriptionStateType*/);

        virtual ArchestrAResult DeleteSubscription( ConnectionId Id, 
                                            __int64 SubscriptionId);

        virtual ArchestrAResult AddMonitoredItems(  array<ArchestrAServices::ASBIDataV2Contract::ItemStatus>   ^% Status, 
                                                    array<ArchestrAServices::ASBIDataV2Contract::ItemRegistration> ^% ItemCapabilities,
                                                    ConnectionId Id, 
                                                    __int64 SubscriptionId, 
                                                    array<ArchestrAServices::ASBIDataV2Contract::MonitoredItem> ^ Items, 
                                                    unsigned char RequireId);

        virtual ArchestrAResult DeleteMonitoredItems(   array<ArchestrAServices::ASBIDataV2Contract::ItemStatus>   ^% Status, 
                                                        ConnectionId Id, 
                                                        __int64 SubscriptionId, 
                                                        array<ArchestrAServices::ASBIDataV2Contract::MonitoredItem> ^ Items);

        virtual ArchestrAResult GetMonitoredItems(  array<ArchestrAServices::ASBIDataV2Contract::MonitoredItem> ^% Items, 
                                                    ConnectionId Id, 
                                                    __int64 SubscriptionId);

        virtual ArchestrAResult Publish(array<ArchestrAServices::ASBIDataV2Contract::ItemStatus>           ^% Status, 
                                        array<ArchestrAServices::ASBIDataV2Contract::MonitoredItemValue>   ^% Values, 
                                        ConnectionId Id, 
                                        __int64 SubscriptionId);

        virtual ArchestrAResult RegisterItems(  array<ArchestrAServices::ASBIDataV2Contract::ItemStatus>   ^% Status, 
                                        array<ArchestrAServices::ASBIDataV2Contract::ItemRegistration> ^% ItemCapabilities,
                                        ConnectionId Id, 
                                        array<ArchestrAServices::ASBIDataV2Contract::ItemIdentity> ^ Items, 
                                        unsigned char RequireId, 
                                        unsigned char RegisterOnly);

        virtual ArchestrAResult UnregisterItems(array<ArchestrAServices::ASBIDataV2Contract::ItemStatus>   ^% Status, 
                                                ConnectionId Id, 
                                                array<ArchestrAServices::ASBIDataV2Contract::ItemIdentity> ^ Items);

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
                                                ArchestrAServices::ASBIDataV2Contract::UserToken UserToken);

        virtual ArchestrAResult ExchangeCapabilities(   String ^% ServiceCapabilities, 
                                                        ConnectionId Id, 
                                                        String ^  ClientCapabilities);

        virtual void OnConnect(ConnectionId ConnectionId, unsigned __int64 Timeout);

};
