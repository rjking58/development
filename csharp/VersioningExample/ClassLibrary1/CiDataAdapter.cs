using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;


using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using ArchestrAServices.ASBContract;


namespace ArchestrAServices.ASBContract
{
    //For backward compatibility.
    public struct ConnectionId
    {
        public Guid Id;
    }
}


namespace ArchestrAServices.ASBIDataContract.V2
{
    public partial struct Variant
    {

        private ushort typeField;

        private int lengthField;

        private byte[] payloadField;

        /// <remarks/>
        public ushort Type
        {
            get
            {
                return this.typeField;
            }
            set
            {
                this.typeField = value;
            }
        }

        /// <remarks/>
        public int Length
        {
            get
            {
                return this.lengthField;
            }
            set
            {
                this.lengthField = value;
            }
        }

        /// <remarks/>
        [System.Xml.Serialization.XmlElementAttribute(DataType = "base64Binary", IsNullable = true)]
        public byte[] Payload
        {
            get
            {
                return this.payloadField;
            }
            set
            {
                this.payloadField = value;
            }
        }
    }
}



namespace ArchestrAServices.ASBIDataV2Contract
{

    public partial struct ItemIdentity
    {

        private ushort typeField;

        private ushort referenceTypeField;

        private string nameField;

        private string contextNameField;

        private ulong idField;

        private bool idFieldSpecified;

        /// <remarks/>
        public ushort Type
        {
            get
            {
                return this.typeField;
            }
            set
            {
                this.typeField = value;
            }
        }

        /// <remarks/>
        public ushort ReferenceType
        {
            get
            {
                return this.referenceTypeField;
            }
            set
            {
                this.referenceTypeField = value;
            }
        }

        /// <remarks/>
        public string Name
        {
            get
            {
                return this.nameField;
            }
            set
            {
                this.nameField = value;
            }
        }

        /// <remarks/>
        public string ContextName
        {
            get
            {
                return this.contextNameField;
            }
            set
            {
                this.contextNameField = value;
            }
        }

        /// <remarks/>
        public ulong Id
        {
            get
            {
                return this.idField;
            }
            set
            {
                this.idField = value;
                this.IdSpecified = true;
            }
        }

        /// <remarks/>
        public bool IdSpecified
        {
            get
            {
                return this.idFieldSpecified;
            }
            set
            {
                this.idFieldSpecified = value;
            }
        }
    }

    public enum ItemChoiceType
    {
        
        /// <remarks/>
        Blob,
        
        /// <remarks/>
        Boolean,
        
        /// <remarks/>
        Byte,
        
        /// <remarks/>
        Date,
        
        /// <remarks/>
        DateTime,
        
        /// <remarks/>
        Decimal,
        
        /// <remarks/>
        Double,
        
        /// <remarks/>
        Duration,
        
        /// <remarks/>
        Float,
        
        /// <remarks/>
        Guid,
        
        /// <remarks/>
        Hex,
        
        /// <remarks/>
        Int,
        
        /// <remarks/>
        Integer,
        
        /// <remarks/>
        Long,
        
        /// <remarks/>
        Short,
        
        /// <remarks/>
        String,
        
        /// <remarks/>
        Time,
        
        /// <remarks/>
        UnsignedByte,
        
        /// <remarks/>
        UnsignedInt,
        
        /// <remarks/>
        UnsignedLong,
        
        /// <remarks/>
        UnsignedShort,
    }

    public partial class ResultVariant
    {
        
        private object itemField;
        
        private ItemChoiceType itemElementNameField;
        
        public object Item
        {
            get
            {
                return this.itemField;
            }
            set
            {
                this.itemField = value;
            }
        }
        
        /// <remarks/>
        public ItemChoiceType ItemElementName
        {
            get
            {
                return this.itemElementNameField;
            }
            set
            {
                this.itemElementNameField = value;
            }
        }
    }

    public partial class NamedValue
    {
        
        private string nameField;
        
        private ResultVariant valueField;
        
        /// <remarks/>
        public string Name
        {
            get
            {
                return this.nameField;
            }
            set
            {
                this.nameField = value;
            }
        }
        
        /// <remarks/>
        public ResultVariant Value
        {
            get
            {
                return this.valueField;
            }
            set
            {
                this.valueField = value;
            }
        }
    }

    internal partial struct Variant
    {
        
        private ushort typeField;
        
        private int lengthField;
        
        private byte[] payloadField;
        
        /// <remarks/>
        public ushort Type
        {
            get
            {
                return this.typeField;
            }
            set
            {
                this.typeField = value;
            }
        }
        
        /// <remarks/>
        public int Length
        {
            get
            {
                return this.lengthField;
            }
            set
            {
                this.lengthField = value;
            }
        }
        
        /// <remarks/>
        public byte[] Payload
        {
            get
            {
                return this.payloadField;
            }
            set
            {
                this.payloadField = value;
            }
        }
    }

    public partial struct ASBStatus
    {
        
        private sbyte countField;
        
        private byte[] payloadField;
        
        /// <remarks/>
        public sbyte Count
        {
            get
            {
                return this.countField;
            }
            set
            {
                this.countField = value;
            }
        }
        
        /// <remarks/>
        public byte[] Payload
        {
            get
            {
                return this.payloadField;
            }
            set
            {
                this.payloadField = value;
            }
        }
    }

    public partial struct RuntimeValue
    {
        
        private System.DateTime timestampField;
        
        private bool timestampFieldSpecified;

        private ASBIDataV2Contract.Variant valueField;
        
        private ASBStatus statusField;
        
        /// <remarks/>
        public System.DateTime Timestamp
        {
            get
            {
                return this.timestampField;
            }
            set
            {
                this.timestampField = value;
                this.TimestampSpecified = true;
            }
        }
        
        /// <remarks/>
        public bool TimestampSpecified
        {
            get
            {
                return this.timestampFieldSpecified;
            }
            set
            {
                this.timestampFieldSpecified = value;
            }
        }
        
        /// <remarks/>
        public ASBIDataContract.V2.Variant Value
        {
            get
            {
                ASBIDataContract.V2.Variant ReturnValue = new ASBIDataContract.V2.Variant();
                ReturnValue.Type = this.valueField.Type;
                ReturnValue.Length = this.valueField.Length;
                ReturnValue.Payload = this.valueField.Payload;
                return ReturnValue;
            }
            set
            {
                this.valueField.Type = value.Type;
                this.valueField.Length = value.Length;
                this.valueField.Payload = value.Payload;
            }
        }
        
        /// <remarks/>
        public ASBStatus Status
        {
            get
            {
                return this.statusField;
            }
            set
            {
                this.statusField = value;
            }
        }
    }


    public partial struct ItemStatus
    {
        
        private ItemIdentity itemField;
        
        private ushort errorCodeField;
        
        private bool errorCodeFieldSpecified;
        
        private ASBStatus statusField;
        
        /// <remarks/>
        public ItemIdentity Item
        {
            get
            {
                return this.itemField;
            }
            set
            {
                this.itemField = value;
            }
        }
        
        /// <remarks/>
        public ushort ErrorCode
        {
            get
            {
                return this.errorCodeField;
            }
            set
            {
                this.errorCodeField = value;
                this.ErrorCodeSpecified = true;
            }
        }
        
        /// <remarks/>
        public bool ErrorCodeSpecified
        {
            get
            {
                return this.errorCodeFieldSpecified;
            }
            set
            {
                this.errorCodeFieldSpecified = value;
            }
        }
        
        /// <remarks/>
        public ASBStatus Status
        {
            get
            {
                return this.statusField;
            }
            set
            {
                this.statusField = value;
            }
        }
    }

    public partial struct ArchestrAResult
    {
        
        private bool successField;
        
        private int resultCodeField;

        private uint specificErrorCodeField;

        private uint statusCodeField;

        private string locationField;
        
        private string[] successMessagesField;
        
        private string[] informationMessagesField;
        
        private string[] errorMessagesField;
        
        private NamedValue[] extensionsField;
        
        /// <remarks/>
        public bool Success
        {
            get
            {
                return this.successField;
            }
            set
            {
                this.successField = value;
            }
        }
        
        /// <remarks/>
        public int ResultCode
        {
            get
            {
                return this.resultCodeField;
            }
            set
            {
                this.resultCodeField = value;
            }
        }

        /// Alias for backward compatibility.
        public int ErrorCode
        {
            get
            {
                return this.resultCodeField;
            }
            set
            {
                this.resultCodeField = value;
            }
        }

        /// <remarks/>
        public uint SpecificErrorCode
        {
            get
            {
                return this.specificErrorCodeField;
            }
            set
            {
                this.specificErrorCodeField = value;
            }
        }

        /// <remarks/>
        public uint Status
        {
            get
            {
                return this.statusCodeField;
            }
            set
            {
                this.statusCodeField = value;
            }
        }

        /// <remarks/>
        public string Location
        {
            get
            {
                return this.locationField;
            }
            set
            {
                this.locationField = value;
            }
        }
        
        /// <remarks/>
        public string[] SuccessMessages
        {
            get
            {
                return this.successMessagesField;
            }
            set
            {
                this.successMessagesField = value;
            }
        }
        
        /// <remarks/>
        public string[] InformationMessages
        {
            get
            {
                return this.informationMessagesField;
            }
            set
            {
                this.informationMessagesField = value;
            }
        }
        
        /// <remarks/>
        public string[] ErrorMessages
        {
            get
            {
                return this.errorMessagesField;
            }
            set
            {
                this.errorMessagesField = value;
            }
        }
        
        /// <remarks/>
        public NamedValue[] Extensions
        {
            get
            {
                return this.extensionsField;
            }
            set
            {
                this.extensionsField = value;
            }
        }
    }

    public partial struct WriteValue
    {

        private bool hasQTField;

        private bool hasQTFieldSpecified;

        private ASBIDataV2Contract.Variant valueField;

        private ASBStatus statusField;

        private System.DateTime timestampField;

        private bool timestampFieldSpecified;

        private string commentField;

        private int arrayElementIndexField;

        private bool arrayElementIndexFieldSpecified;

        /// <remarks/>
        public bool HasQT
        {
            get
            {
                return this.hasQTField;
            }
            set
            {
                this.hasQTField = value;
                this.HasQTSpecified = true;
            }
        }

        public bool HasQTSpecified
        {
            get
            {
                return this.hasQTFieldSpecified;
            }
            set
            {
                this.hasQTFieldSpecified = value;
            }
        }

        /// <remarks/>
        public ASBIDataContract.V2.Variant Value
        {
            get
            {
                ASBIDataContract.V2.Variant ReturnValue = new ASBIDataContract.V2.Variant();
                ReturnValue.Type = this.valueField.Type;
                ReturnValue.Length = this.valueField.Length;
                ReturnValue.Payload = this.valueField.Payload;
                return ReturnValue;
            }
            set
            {
                this.valueField.Type = value.Type;
                this.valueField.Length = value.Length;
                this.valueField.Payload = value.Payload;
            }
        }

        /// <remarks/>
        public ASBStatus Status
        {
            get
            {
                return this.statusField;
            }
            set
            {
                this.statusField = value;
            }
        }

        /// <remarks/>
        public System.DateTime Timestamp
        {
            get
            {
                return this.timestampField;
            }
            set
            {
                this.timestampField = value;
                this.TimestampSpecified = true;
            }
        }

        public bool TimestampSpecified
        {
            get
            {
                return this.timestampFieldSpecified;
            }
            set
            {
                this.timestampFieldSpecified = value;
            }
        }

        /// <remarks/>
        public string Comment
        {
            get
            {
                return this.commentField;
            }
            set
            {
                this.commentField = value;
            }
        }

        /// <remarks/>
        public int ArrayElementIndex
        {
            get
            {
                return this.arrayElementIndexField;
            }
            set
            {
                this.arrayElementIndexField = value;
                this.ArrayElementIndexSpecified = true;
            }
        }

        /// <remarks/>
        public bool ArrayElementIndexSpecified
        {
            get
            {
                return this.arrayElementIndexFieldSpecified;
            }
            set
            {
                this.arrayElementIndexFieldSpecified = value;
            }
        }
    }

    public partial struct UserToken
    {

        private ushort encryptionField;

        private bool encryptionFieldSpecified;

        private string hostNameField;

        private ushort idTypeField;

        private bool idTypeFieldSpecified;

        private string locationIDField;

        private string passwordField;

        private byte[] samlTokenField;

        private string userNameField;

        private ushort validityField;

        private bool validityFieldSpecified;

        private byte[] x509CertificateField;

        /// <remarks/>
        public ushort Encryption
        {
            get
            {
                return this.encryptionField;
            }
            set
            {
                this.encryptionField = value;
                this.EncryptionSpecified = true;
            }
        }

        /// <remarks/>
        public bool EncryptionSpecified
        {
            get
            {
                return this.encryptionFieldSpecified;
            }
            set
            {
                this.encryptionFieldSpecified = value;
            }
        }

        /// <remarks/>
        public string HostName
        {
            get
            {
                return this.hostNameField;
            }
            set
            {
                this.hostNameField = value;
            }
        }

        /// <remarks/>
        public ushort IdType
        {
            get
            {
                return this.idTypeField;
            }
            set
            {
                this.idTypeField = value;
                this.IdTypeSpecified = true;
            }
        }

        /// <remarks/>
        public bool IdTypeSpecified
        {
            get
            {
                return this.idTypeFieldSpecified;
            }
            set
            {
                this.idTypeFieldSpecified = value;
            }
        }

        /// <remarks/>
        public string LocationID
        {
            get
            {
                return this.locationIDField;
            }
            set
            {
                this.locationIDField = value;
            }
        }

        /// <remarks/>
        public string Password
        {
            get
            {
                return this.passwordField;
            }
            set
            {
                this.passwordField = value;
            }
        }

        /// <remarks/>
        public byte[] SamlToken
        {
            get
            {
                return this.samlTokenField;
            }
            set
            {
                this.samlTokenField = value;
            }
        }

        /// <remarks/>
        public string UserName
        {
            get
            {
                return this.userNameField;
            }
            set
            {
                this.userNameField = value;
            }
        }

        /// <remarks/>
        public ushort Validity
        {
            get
            {
                return this.validityField;
            }
            set
            {
                this.validityField = value;
                this.ValiditySpecified = true;
            }
        }

        /// <remarks/>
        public bool ValiditySpecified
        {
            get
            {
                return this.validityFieldSpecified;
            }
            set
            {
                this.validityFieldSpecified = value;
            }
        }

        /// <remarks/>
        public byte[] X509Certificate
        {
            get
            {
                return this.x509CertificateField;
            }
            set
            {
                this.x509CertificateField = value;
            }
        }
    }

    public partial struct MonitoredItem
    {

        private ItemIdentity itemField;

        private ulong sampleIntervalField;

        private bool activeField;

        private bool activeFieldSpecified;

        private ulong timeDeadbandField;

        private bool timeDeadbandFieldSpecified;

        private ASBIDataV2Contract.Variant valueDeadbandField;

        private ASBIDataV2Contract.Variant userDataField;

        /// <remarks/>
        public ItemIdentity Item
        {
            get
            {
                return this.itemField;
            }
            set
            {
                this.itemField = value;
            }
        }

        /// <remarks/>
        public ulong SampleInterval
        {
            get
            {
                return this.sampleIntervalField;
            }
            set
            {
                this.sampleIntervalField = value;
            }
        }

        /// <remarks/>
        public bool Active
        {
            get
            {
                return this.activeField;
            }
            set
            {
                this.activeField = value;
                this.ActiveSpecified = true;
            }
        }

        /// <remarks/>
        public bool ActiveSpecified
        {
            get
            {
                return this.activeFieldSpecified;
            }
            set
            {
                this.activeFieldSpecified = value;
            }
        }

        /// <remarks/>
        public ulong TimeDeadband
        {
            get
            {
                return this.timeDeadbandField;
            }
            set
            {
                this.timeDeadbandField = value;
                this.TimeDeadbandSpecified = true;
            }
        }

        public bool TimeDeadbandSpecified
        {
            get
            {
                return this.timeDeadbandFieldSpecified;
            }
            set
            {
                this.timeDeadbandFieldSpecified = value;
            }
        }

        /// <remarks/>
        public ASBIDataContract.V2.Variant ValueDeadband
        {
            get
            {
                ASBIDataContract.V2.Variant ReturnValue = new ASBIDataContract.V2.Variant();
                ReturnValue.Type = this.valueDeadbandField.Type;
                ReturnValue.Length = this.valueDeadbandField.Length;
                ReturnValue.Payload = this.valueDeadbandField.Payload;
                return ReturnValue;
            }
            set
            {
                this.valueDeadbandField.Type = value.Type;
                this.valueDeadbandField.Length = value.Length;
                this.valueDeadbandField.Payload = value.Payload;
            }
        }

        /// <remarks/>
        public ASBIDataContract.V2.Variant UserData
        {
            get
            {
                ASBIDataContract.V2.Variant ReturnValue = new ASBIDataContract.V2.Variant();
                ReturnValue.Type = this.userDataField.Type;
                ReturnValue.Length = this.userDataField.Length;
                ReturnValue.Payload = this.userDataField.Payload;
                return ReturnValue;
            }
            set
            {
                this.userDataField.Type = value.Type;
                this.userDataField.Length = value.Length;
                this.userDataField.Payload = value.Payload;
            }
        }
    }
    public partial struct MonitoredItemValue
    {

        private ItemIdentity itemField;

        private RuntimeValue valueField;

        private ASBIDataV2Contract.Variant userDataField;

        /// <remarks/>
        public ItemIdentity Item
        {
            get
            {
                return this.itemField;
            }
            set
            {
                this.itemField = value;
            }
        }

        /// <remarks/>
        public RuntimeValue Value
        {
            get
            {
                return this.valueField;
            }
            set
            {
                this.valueField = value;
            }
        }

        /// <remarks/>
        public ASBIDataContract.V2.Variant UserData
        {
            get
            {
                ASBIDataContract.V2.Variant ReturnValue = new ASBIDataContract.V2.Variant();
                ReturnValue.Type = this.userDataField.Type;
                ReturnValue.Length = this.userDataField.Length;
                ReturnValue.Payload = this.userDataField.Payload;
                return ReturnValue;
            }
            set
            {
                this.userDataField.Type = value.Type;
                this.userDataField.Length = value.Length;
                this.userDataField.Payload = value.Payload;
            }
        }
    }

    public partial struct ItemWriteComplete
    {

        private ItemStatus[] statusField;

        private uint writeHandleField;

        private bool writeHandleFieldSpecified;

        /// <remarks/>
        [System.Xml.Serialization.XmlElementAttribute("Status")]
        public ItemStatus[] Status
        {
            get
            {
                return this.statusField;
            }
            set
            {
                this.statusField = value;
            }
        }

        /// <remarks/>
        public uint WriteHandle
        {
            get
            {
                return this.writeHandleField;
            }
            set
            {
                this.writeHandleField = value;
                this.WriteHandleSpecified = true;
            }
        }

        /// <remarks/>
        [System.Xml.Serialization.XmlIgnoreAttribute()]
        public bool WriteHandleSpecified
        {
            get
            {
                return this.writeHandleFieldSpecified;
            }
            set
            {
                this.writeHandleFieldSpecified = value;
            }
        }
    }

    public partial struct ItemRegistration
    {

        private ulong idField;

        private bool idFieldSpecified;

        private ushort writeCapabilityField;

        private bool writeCapabilityFieldSpecified;

        /// <remarks/>
        public ulong Id
        {
            get
            {
                return this.idField;
            }
            set
            {
                this.idField = value;
                this.IdSpecified = true;
            }
        }

        /// <remarks/>
        [System.Xml.Serialization.XmlIgnoreAttribute()]
        public bool IdSpecified
        {
            get
            {
                return this.idFieldSpecified;
            }
            set
            {
                this.idFieldSpecified = value;
            }
        }

        /// <remarks/>
        public ushort WriteCapability
        {
            get
            {
                return this.writeCapabilityField;
            }
            set
            {
                this.writeCapabilityField = value;
                this.WriteCapabilitySpecified = true;
            }
        }

        /// <remarks/>
        [System.Xml.Serialization.XmlIgnoreAttribute()]
        public bool WriteCapabilitySpecified
        {
            get
            {
                return this.writeCapabilityFieldSpecified;
            }
            set
            {
                this.writeCapabilityFieldSpecified = value;
            }
        }
    }


    public abstract class CiDataVersionAdapter
    {
        public abstract void Abort();
        public abstract void Disconnect();
        public abstract bool Connect(out string errorMessage);

        public abstract ArchestrAResult KeepAlive(ASBContract.ConnectionId Id);
        //public abstract void OnConnect(ASBContract.ConnectionId ConnectionId, ulong Timeout);

        //public abstract ArchestrAResult ActivateUser(ASBContract.ConnectionId Id, UserToken UserToken);

        //public abstract ArchestrAResult ExchangeCapabilities(out string ServiceCapabilities, ASBContract.ConnectionId Id, string ClientCapabilities);

        //  Reading data.
        public abstract ArchestrAResult Read(out ItemStatus[] Status, out RuntimeValue[] Values, ASBContract.ConnectionId Id, ItemIdentity[] Items);

        //  Writing data.
        //  WriteHandle for all write modes is a transaction handle that will be returned
        //  in PublishWriteComplete().  Special values for WriteHandle are:
        //      0: Non-overlapped write call, blocks until return.  PublishWriteComplete() will never contain this.
        //      1: Overlapped, but the results will not be requested with PublishWriteComplete(), do not buffer or return.
        //      100 and above: Valid write transaction handle.
        public abstract ArchestrAResult Write(out ItemStatus[] Status, ASBContract.ConnectionId Id, ItemIdentity[] Items, WriteValue[] Values, UInt32 WriteHandle);

        public abstract ArchestrAResult WriteUser(out ItemStatus[] Status, ASBContract.ConnectionId Id, ItemIdentity[] Items, WriteValue[] Values, UserToken User, UInt32 WriteHandle);

        public abstract ArchestrAResult WriteVerified(out ItemStatus[] Status, ASBContract.ConnectionId Id, ItemIdentity[] Items, WriteValue[] Values, UserToken User, UserToken Supervisor, UInt32 WriteHandle);

        //US-51105 - WriteSecured method
        public abstract ArchestrAResult WriteSecured(out ItemStatus[] Status, ASBContract.ConnectionId Id, ItemIdentity[] Items, WriteValue[] Values, UserToken User, UInt32 WriteHandle);

        //public abstract ArchestrAResult WriteConfirmed(out WriteValue ValueReceived, out Int64 WriteToken,
        //                                    ASBContract.ConnectionId Id, ItemIdentity Item, WriteValue Value, UserToken User, UserToken Supervisor);

        //public abstract ArchestrAResult ConfirmWrite(ASBContract.ConnectionId Id, ItemIdentity Item, Int64 WriteToken, WriteValue Value, UserToken User, UserToken Supervisor, UInt32 WriteHandle);
        
        public abstract ArchestrAResult PublishWriteComplete(out ItemWriteComplete[] CompleteWrites, ASBContract.ConnectionId Id);

        //  Subscriptions.
        public abstract ArchestrAResult CreateSubscription(out Int64 SubscriptionId, ASBContract.ConnectionId Id, Int64 MaxQueueSize, UInt64 SampleInterval);

        public abstract ArchestrAResult SetSubscriptionState(ASBContract.ConnectionId Id, Int64 SubscriptionId, ASBIDataContract.V2.Variant NewState, ushort StateToChange /*enum SubscriptionStateType*/);

        //public abstract ArchestrAResult GetSubscriptionState(out ASBIDataContract.V2.Variant State, ASBContract.ConnectionId Id, Int64 SubscriptionId, ushort StateToGet /*enum SubscriptionStateType*/);

        public abstract ArchestrAResult DeleteSubscription(ASBContract.ConnectionId Id, Int64 SubscriptionId);

        public abstract ArchestrAResult AddMonitoredItems(out ItemStatus[] Status, out ItemRegistration[] ItemCapabilities,
                                            ASBContract.ConnectionId Id, Int64 SubscriptionId, MonitoredItem[] Items, byte RequireId);

        public abstract ArchestrAResult DeleteMonitoredItems(out ItemStatus[] Status, ASBContract.ConnectionId Id, Int64 SubscriptionId, MonitoredItem[] Items);

        //public abstract ArchestrAResult GetMonitoredItems(out MonitoredItem[] Items, ASBContract.ConnectionId Id, Int64 SubscriptionId);

        public abstract ArchestrAResult Publish(out ItemStatus[] Status, out MonitoredItemValue[] Values, ASBContract.ConnectionId Id, Int64 SubscriptionId);

        public abstract ArchestrAResult RegisterItems(out ItemStatus[] Status, out ItemRegistration[] ItemCapabilities,
                                            ASBContract.ConnectionId Id, ItemIdentity[] Items, byte RequireId, byte RegisterOnly);

        public abstract ArchestrAResult UnregisterItems(out ItemStatus[] Status, ASBContract.ConnectionId Id, ItemIdentity[] Items);

        //public abstract void OnDisconnect(ASBContract.ConnectionId Id);
    }


}
