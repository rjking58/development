using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ClassLibrary1
{
    public class CiDataVersionAdapterV1 : ArchestrAServices.ASBIDataV2Contract.CiDataVersionAdapter
    {
        public override void Disconnect()
        {
            throw new NotImplementedException();
        }
        public override void Abort()
        {
            throw new NotImplementedException();
        }
        public override bool Connect(out string errorMessage)
        {
            throw new NotImplementedException();
        }

        public override ArchestrAServices.ASBIDataV2Contract.ArchestrAResult KeepAlive(ArchestrAServices.ASBContract.ConnectionId Id)
        {
            throw new NotImplementedException();
        }

        //public override  void OnConnect(ArchestrAServices.ASBContract.ConnectionId ConnectionId, ulong Timeout)
        //{
        //    throw new NotImplementedException();
        //}

        //public override  ArchestrAServices.ASBIDataV2Contract.ArchestrAResult ActivateUser(ArchestrAServices.ASBContract.ConnectionId Id, ArchestrAServices.ASBIDataV2Contract.UserToken UserToken)
        //{
        //    throw new NotImplementedException();
        //}

        //public override  ArchestrAServices.ASBIDataV2Contract.ArchestrAResult ExchangeCapabilities(out string ServiceCapabilities, ArchestrAServices.ASBContract.ConnectionId Id, string ClientCapabilities)
        //{
        //    throw new NotImplementedException();
        //}

        public override  ArchestrAServices.ASBIDataV2Contract.ArchestrAResult Read(out ArchestrAServices.ASBIDataV2Contract.ItemStatus[] Status, out ArchestrAServices.ASBIDataV2Contract.RuntimeValue[] Values, ArchestrAServices.ASBContract.ConnectionId Id, ArchestrAServices.ASBIDataV2Contract.ItemIdentity[] Items)
        {
            throw new NotImplementedException();
        }

        public override  ArchestrAServices.ASBIDataV2Contract.ArchestrAResult Write(out ArchestrAServices.ASBIDataV2Contract.ItemStatus[] Status, ArchestrAServices.ASBContract.ConnectionId Id, ArchestrAServices.ASBIDataV2Contract.ItemIdentity[] Items, ArchestrAServices.ASBIDataV2Contract.WriteValue[] Values, uint WriteHandle)
        {
            throw new NotImplementedException();
        }

        public override  ArchestrAServices.ASBIDataV2Contract.ArchestrAResult WriteUser(out ArchestrAServices.ASBIDataV2Contract.ItemStatus[] Status, ArchestrAServices.ASBContract.ConnectionId Id, ArchestrAServices.ASBIDataV2Contract.ItemIdentity[] Items, ArchestrAServices.ASBIDataV2Contract.WriteValue[] Values, ArchestrAServices.ASBIDataV2Contract.UserToken User, uint WriteHandle)
        {
            throw new NotImplementedException();
        }

        public override  ArchestrAServices.ASBIDataV2Contract.ArchestrAResult WriteVerified(out ArchestrAServices.ASBIDataV2Contract.ItemStatus[] Status, ArchestrAServices.ASBContract.ConnectionId Id, ArchestrAServices.ASBIDataV2Contract.ItemIdentity[] Items, ArchestrAServices.ASBIDataV2Contract.WriteValue[] Values, ArchestrAServices.ASBIDataV2Contract.UserToken User, ArchestrAServices.ASBIDataV2Contract.UserToken Supervisor, uint WriteHandle)
        {
            throw new NotImplementedException();
        }

        public override  ArchestrAServices.ASBIDataV2Contract.ArchestrAResult WriteSecured(out ArchestrAServices.ASBIDataV2Contract.ItemStatus[] Status, ArchestrAServices.ASBContract.ConnectionId Id, ArchestrAServices.ASBIDataV2Contract.ItemIdentity[] Items, ArchestrAServices.ASBIDataV2Contract.WriteValue[] Values, ArchestrAServices.ASBIDataV2Contract.UserToken User, uint WriteHandle)
        {
            throw new NotImplementedException();
        }

        //public override  ArchestrAServices.ASBIDataV2Contract.ArchestrAResult WriteConfirmed(out ArchestrAServices.ASBIDataV2Contract.WriteValue ValueReceived, out long WriteToken, ArchestrAServices.ASBContract.ConnectionId Id, ArchestrAServices.ASBIDataV2Contract.ItemIdentity Item, ArchestrAServices.ASBIDataV2Contract.WriteValue Value, ArchestrAServices.ASBIDataV2Contract.UserToken User, ArchestrAServices.ASBIDataV2Contract.UserToken Supervisor)
        //{
        //    throw new NotImplementedException();
        //}

        //public override  ArchestrAServices.ASBIDataV2Contract.ArchestrAResult ConfirmWrite(ArchestrAServices.ASBContract.ConnectionId Id, ArchestrAServices.ASBIDataV2Contract.ItemIdentity Item, long WriteToken, ArchestrAServices.ASBIDataV2Contract.WriteValue Value, ArchestrAServices.ASBIDataV2Contract.UserToken User, ArchestrAServices.ASBIDataV2Contract.UserToken Supervisor, uint WriteHandle)
        //{
        //    throw new NotImplementedException();
        //}

        public override  ArchestrAServices.ASBIDataV2Contract.ArchestrAResult PublishWriteComplete(out ArchestrAServices.ASBIDataV2Contract.ItemWriteComplete[] CompleteWrites, ArchestrAServices.ASBContract.ConnectionId Id)
        {
            throw new NotImplementedException();
        }

        public override  ArchestrAServices.ASBIDataV2Contract.ArchestrAResult CreateSubscription(out long SubscriptionId, ArchestrAServices.ASBContract.ConnectionId Id, long MaxQueueSize, ulong SampleInterval)
        {
            throw new NotImplementedException();
        }

        public override  ArchestrAServices.ASBIDataV2Contract.ArchestrAResult SetSubscriptionState(ArchestrAServices.ASBContract.ConnectionId Id, long SubscriptionId, ArchestrAServices.ASBIDataContract.V2.Variant NewState, ushort StateToChange)
        {
            throw new NotImplementedException();
        }

        //public override  ArchestrAServices.ASBIDataV2Contract.ArchestrAResult GetSubscriptionState(out ArchestrAServices.ASBIDataContract.V2.Variant State, ArchestrAServices.ASBContract.ConnectionId Id, long SubscriptionId, ushort StateToGet)
        //{
        //    throw new NotImplementedException();
        //}

        public override  ArchestrAServices.ASBIDataV2Contract.ArchestrAResult DeleteSubscription(ArchestrAServices.ASBContract.ConnectionId Id, long SubscriptionId)
        {
            throw new NotImplementedException();
        }

        public override  ArchestrAServices.ASBIDataV2Contract.ArchestrAResult AddMonitoredItems(out ArchestrAServices.ASBIDataV2Contract.ItemStatus[] Status, out ArchestrAServices.ASBIDataV2Contract.ItemRegistration[] ItemCapabilities, ArchestrAServices.ASBContract.ConnectionId Id, long SubscriptionId, ArchestrAServices.ASBIDataV2Contract.MonitoredItem[] Items, byte RequireId)
        {
            throw new NotImplementedException();
        }

        public override  ArchestrAServices.ASBIDataV2Contract.ArchestrAResult DeleteMonitoredItems(out ArchestrAServices.ASBIDataV2Contract.ItemStatus[] Status, ArchestrAServices.ASBContract.ConnectionId Id, long SubscriptionId, ArchestrAServices.ASBIDataV2Contract.MonitoredItem[] Items)
        {
            throw new NotImplementedException();
        }

        //public override  ArchestrAServices.ASBIDataV2Contract.ArchestrAResult GetMonitoredItems(out ArchestrAServices.ASBIDataV2Contract.MonitoredItem[] Items, ArchestrAServices.ASBContract.ConnectionId Id, long SubscriptionId)
        //{
        //    throw new NotImplementedException();
        //}

        public override  ArchestrAServices.ASBIDataV2Contract.ArchestrAResult Publish(out ArchestrAServices.ASBIDataV2Contract.ItemStatus[] Status, out ArchestrAServices.ASBIDataV2Contract.MonitoredItemValue[] Values, ArchestrAServices.ASBContract.ConnectionId Id, long SubscriptionId)
        {
            throw new NotImplementedException();
        }

        public override  ArchestrAServices.ASBIDataV2Contract.ArchestrAResult RegisterItems(out ArchestrAServices.ASBIDataV2Contract.ItemStatus[] Status, out ArchestrAServices.ASBIDataV2Contract.ItemRegistration[] ItemCapabilities, ArchestrAServices.ASBContract.ConnectionId Id, ArchestrAServices.ASBIDataV2Contract.ItemIdentity[] Items, byte RequireId, byte RegisterOnly)
        {
            throw new NotImplementedException();
        }

        public override  ArchestrAServices.ASBIDataV2Contract.ArchestrAResult UnregisterItems(out ArchestrAServices.ASBIDataV2Contract.ItemStatus[] Status, ArchestrAServices.ASBContract.ConnectionId Id, ArchestrAServices.ASBIDataV2Contract.ItemIdentity[] Items)
        {
            throw new NotImplementedException();
        }

        //public override  void OnDisconnect(ArchestrAServices.ASBContract.ConnectionId Id)
        //{
        //    throw new NotImplementedException();
        //}
    }

    public class CiDataVersionAdapterV2 : ArchestrAServices.ASBIDataV2Contract.CiDataVersionAdapter
    {
        public override void Disconnect()
        {
            throw new NotImplementedException();
        }
        public override void Abort()
        {
            throw new NotImplementedException();
        }
        public override bool Connect(out string errorMessage)
        {
            throw new NotImplementedException();
        }

        public override  ArchestrAServices.ASBIDataV2Contract.ArchestrAResult KeepAlive(ArchestrAServices.ASBContract.ConnectionId Id)
        {
            throw new NotImplementedException();
        }

        //public override  void OnConnect(ArchestrAServices.ASBContract.ConnectionId ConnectionId, ulong Timeout)
        //{
        //    throw new NotImplementedException();
        //}

        //public override  ArchestrAServices.ASBIDataV2Contract.ArchestrAResult ActivateUser(ArchestrAServices.ASBContract.ConnectionId Id, ArchestrAServices.ASBIDataV2Contract.UserToken UserToken)
        //{
        //    throw new NotImplementedException();
        //}

        //public override  ArchestrAServices.ASBIDataV2Contract.ArchestrAResult ExchangeCapabilities(out string ServiceCapabilities, ArchestrAServices.ASBContract.ConnectionId Id, string ClientCapabilities)
        //{
        //    throw new NotImplementedException();
        //}

        public override  ArchestrAServices.ASBIDataV2Contract.ArchestrAResult Read(out ArchestrAServices.ASBIDataV2Contract.ItemStatus[] Status, out ArchestrAServices.ASBIDataV2Contract.RuntimeValue[] Values, ArchestrAServices.ASBContract.ConnectionId Id, ArchestrAServices.ASBIDataV2Contract.ItemIdentity[] Items)
        {
            throw new NotImplementedException();
        }

        public override  ArchestrAServices.ASBIDataV2Contract.ArchestrAResult Write(out ArchestrAServices.ASBIDataV2Contract.ItemStatus[] Status, ArchestrAServices.ASBContract.ConnectionId Id, ArchestrAServices.ASBIDataV2Contract.ItemIdentity[] Items, ArchestrAServices.ASBIDataV2Contract.WriteValue[] Values, uint WriteHandle)
        {
            throw new NotImplementedException();
        }

        public override  ArchestrAServices.ASBIDataV2Contract.ArchestrAResult WriteUser(out ArchestrAServices.ASBIDataV2Contract.ItemStatus[] Status, ArchestrAServices.ASBContract.ConnectionId Id, ArchestrAServices.ASBIDataV2Contract.ItemIdentity[] Items, ArchestrAServices.ASBIDataV2Contract.WriteValue[] Values, ArchestrAServices.ASBIDataV2Contract.UserToken User, uint WriteHandle)
        {
            throw new NotImplementedException();
        }

        public override  ArchestrAServices.ASBIDataV2Contract.ArchestrAResult WriteVerified(out ArchestrAServices.ASBIDataV2Contract.ItemStatus[] Status, ArchestrAServices.ASBContract.ConnectionId Id, ArchestrAServices.ASBIDataV2Contract.ItemIdentity[] Items, ArchestrAServices.ASBIDataV2Contract.WriteValue[] Values, ArchestrAServices.ASBIDataV2Contract.UserToken User, ArchestrAServices.ASBIDataV2Contract.UserToken Supervisor, uint WriteHandle)
        {
            throw new NotImplementedException();
        }

        public override  ArchestrAServices.ASBIDataV2Contract.ArchestrAResult WriteSecured(out ArchestrAServices.ASBIDataV2Contract.ItemStatus[] Status, ArchestrAServices.ASBContract.ConnectionId Id, ArchestrAServices.ASBIDataV2Contract.ItemIdentity[] Items, ArchestrAServices.ASBIDataV2Contract.WriteValue[] Values, ArchestrAServices.ASBIDataV2Contract.UserToken User, uint WriteHandle)
        {
            throw new NotImplementedException();
        }

        //public override  ArchestrAServices.ASBIDataV2Contract.ArchestrAResult WriteConfirmed(out ArchestrAServices.ASBIDataV2Contract.WriteValue ValueReceived, out long WriteToken, ArchestrAServices.ASBContract.ConnectionId Id, ArchestrAServices.ASBIDataV2Contract.ItemIdentity Item, ArchestrAServices.ASBIDataV2Contract.WriteValue Value, ArchestrAServices.ASBIDataV2Contract.UserToken User, ArchestrAServices.ASBIDataV2Contract.UserToken Supervisor)
        //{
        //    throw new NotImplementedException();
        //}

        //public override  ArchestrAServices.ASBIDataV2Contract.ArchestrAResult ConfirmWrite(ArchestrAServices.ASBContract.ConnectionId Id, ArchestrAServices.ASBIDataV2Contract.ItemIdentity Item, long WriteToken, ArchestrAServices.ASBIDataV2Contract.WriteValue Value, ArchestrAServices.ASBIDataV2Contract.UserToken User, ArchestrAServices.ASBIDataV2Contract.UserToken Supervisor, uint WriteHandle)
        //{
        //    throw new NotImplementedException();
        //}

        public override  ArchestrAServices.ASBIDataV2Contract.ArchestrAResult PublishWriteComplete(out ArchestrAServices.ASBIDataV2Contract.ItemWriteComplete[] CompleteWrites, ArchestrAServices.ASBContract.ConnectionId Id)
        {
            throw new NotImplementedException();
        }

        public override  ArchestrAServices.ASBIDataV2Contract.ArchestrAResult CreateSubscription(out long SubscriptionId, ArchestrAServices.ASBContract.ConnectionId Id, long MaxQueueSize, ulong SampleInterval)
        {
            throw new NotImplementedException();
        }

        public override  ArchestrAServices.ASBIDataV2Contract.ArchestrAResult SetSubscriptionState(ArchestrAServices.ASBContract.ConnectionId Id, long SubscriptionId, ArchestrAServices.ASBIDataContract.V2.Variant NewState, ushort StateToChange)
        {
            throw new NotImplementedException();
        }

        //public override  ArchestrAServices.ASBIDataV2Contract.ArchestrAResult GetSubscriptionState(out ArchestrAServices.ASBIDataContract.V2.Variant State, ArchestrAServices.ASBContract.ConnectionId Id, long SubscriptionId, ushort StateToGet)
        //{
        //    throw new NotImplementedException();
        //}

        public override  ArchestrAServices.ASBIDataV2Contract.ArchestrAResult DeleteSubscription(ArchestrAServices.ASBContract.ConnectionId Id, long SubscriptionId)
        {
            throw new NotImplementedException();
        }

        public override  ArchestrAServices.ASBIDataV2Contract.ArchestrAResult AddMonitoredItems(out ArchestrAServices.ASBIDataV2Contract.ItemStatus[] Status, out ArchestrAServices.ASBIDataV2Contract.ItemRegistration[] ItemCapabilities, ArchestrAServices.ASBContract.ConnectionId Id, long SubscriptionId, ArchestrAServices.ASBIDataV2Contract.MonitoredItem[] Items, byte RequireId)
        {
            throw new NotImplementedException();
        }

        public override  ArchestrAServices.ASBIDataV2Contract.ArchestrAResult DeleteMonitoredItems(out ArchestrAServices.ASBIDataV2Contract.ItemStatus[] Status, ArchestrAServices.ASBContract.ConnectionId Id, long SubscriptionId, ArchestrAServices.ASBIDataV2Contract.MonitoredItem[] Items)
        {
            throw new NotImplementedException();
        }

        //public override  ArchestrAServices.ASBIDataV2Contract.ArchestrAResult GetMonitoredItems(out ArchestrAServices.ASBIDataV2Contract.MonitoredItem[] Items, ArchestrAServices.ASBContract.ConnectionId Id, long SubscriptionId)
        //{
        //    throw new NotImplementedException();
        //}

        public override  ArchestrAServices.ASBIDataV2Contract.ArchestrAResult Publish(out ArchestrAServices.ASBIDataV2Contract.ItemStatus[] Status, out ArchestrAServices.ASBIDataV2Contract.MonitoredItemValue[] Values, ArchestrAServices.ASBContract.ConnectionId Id, long SubscriptionId)
        {
            throw new NotImplementedException();
        }

        public override  ArchestrAServices.ASBIDataV2Contract.ArchestrAResult RegisterItems(out ArchestrAServices.ASBIDataV2Contract.ItemStatus[] Status, out ArchestrAServices.ASBIDataV2Contract.ItemRegistration[] ItemCapabilities, ArchestrAServices.ASBContract.ConnectionId Id, ArchestrAServices.ASBIDataV2Contract.ItemIdentity[] Items, byte RequireId, byte RegisterOnly)
        {
            throw new NotImplementedException();
        }

        public override  ArchestrAServices.ASBIDataV2Contract.ArchestrAResult UnregisterItems(out ArchestrAServices.ASBIDataV2Contract.ItemStatus[] Status, ArchestrAServices.ASBContract.ConnectionId Id, ArchestrAServices.ASBIDataV2Contract.ItemIdentity[] Items)
        {
            throw new NotImplementedException();
        }

        //public override  void OnDisconnect(ArchestrAServices.ASBContract.ConnectionId Id)
        //{
        //    throw new NotImplementedException();
        //}
    }
}
