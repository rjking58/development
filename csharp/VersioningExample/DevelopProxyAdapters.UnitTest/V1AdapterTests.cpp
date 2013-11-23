#include "stdafx.h"


using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;

#include "IDataProxy_MOCK.h"
#include "ItemIdentityV2Mgr.h"
#include "WriteValueMgr.h"
#include "UserTokenMgr.h"
#include "MonitoredItemManager.h"

namespace DevelopProxyAdaptersUnitTest
{
	[TestClass]
	public ref class V1Adapter
	{
	private:
		TestContext^ testContextInstance;

	public: 
		/// <summary>
		///Gets or sets the test context which provides
		///information about and functionality for the current test run.
		///</summary>
		property Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ TestContext
		{
			Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ get()
			{
				return testContextInstance;
			}
			System::Void set(Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ value)
			{
				testContextInstance = value;
			}
		};

        void VerifyItemStatus(array<ArchestrAServices::ASBIDataV2Contract::ItemStatus>   ^ Status)
        {
            Assert::AreEqual(Status->Length,2);
            Assert::AreEqual(Status[0].Item.Type,(System::UInt16) 1);
            Assert::AreEqual(Status[0].Item.ReferenceType,(System::UInt16) 2);
            Assert::AreEqual(Status[0].Item.Name,"identity");
            Assert::AreEqual(Status[0].Item.ContextName,"CONTEXT");
            Assert::AreEqual(Status[0].Item.Id,(System::UInt64) 3);
            Assert::AreEqual(Status[0].Item.IdSpecified,true);
            Assert::AreEqual(Status[0].ErrorCode,(System::UInt16) 4);
            Assert::AreEqual(Status[0].ErrorCodeSpecified,true);

            Assert::AreEqual(Status[1].Item.Type,(System::UInt16) 5);
            Assert::AreEqual(Status[1].Item.ReferenceType,(System::UInt16) 6);
            Assert::AreEqual(Status[1].Item.Name,"identity2");
            Assert::AreEqual(Status[1].Item.ContextName,"CONTEXT2");
            Assert::AreEqual(Status[1].Item.Id,(System::UInt64) 7);
            Assert::AreEqual(Status[1].Item.IdSpecified,true);
            Assert::AreEqual(Status[1].ErrorCode,(System::UInt16) 8);
            Assert::AreEqual(Status[1].ErrorCodeSpecified,true);
        }

        void VerifyRuntimeValue(array<ArchestrAServices::ASBIDataV2Contract::RuntimeValue> ^ ItemValues)
        {
            Assert::AreEqual(ItemValues[0].Timestamp,DateTime(444));
            Assert::AreEqual(ItemValues[0].TimestampSpecified,true);
            Assert::AreEqual(ItemValues[0].Value.Type,(System::UInt16) 3); 
            Assert::AreEqual(ItemValues[0].Value.Length,4); 
            Assert::AreEqual(ItemValues[0].Value.Payload->Length,2); 
            Assert::AreEqual(ItemValues[0].Value.Payload[0],(System::Byte) 5); 
            Assert::AreEqual(ItemValues[0].Value.Payload[1],(System::Byte) 6); 
            Assert::AreEqual(ItemValues[0].Status.Count,(System::SByte) 0);

            Assert::AreEqual(ItemValues[1].Timestamp,DateTime(555));
            Assert::AreEqual(ItemValues[1].TimestampSpecified,true);
            Assert::AreEqual(ItemValues[1].Value.Type,(System::UInt16) 9); 
            Assert::AreEqual(ItemValues[1].Value.Length,10); 
            Assert::AreEqual(ItemValues[1].Value.Payload->Length,2); 
            Assert::AreEqual(ItemValues[1].Value.Payload[0],(System::Byte) 11); 
            Assert::AreEqual(ItemValues[1].Value.Payload[1],(System::Byte) 12); 
            Assert::AreEqual(ItemValues[1].Status.Count,(System::SByte) 0);
        }

        void MakeItemIdentityAry(array<ArchestrAServices::ASBIDataV2Contract::ItemIdentity> ^ Items)
        {
            Items[0] = ItemIdentityV2Mgr::MakeFirst();
            Items[1] = ItemIdentityV2Mgr::MakeSecond();
        }

        void MakeWriteValueAry(array<ArchestrAServices::ASBIDataV2Contract::WriteValue> ^ Values)
        {
            Values[0] = WriteValueMgr::MakeV2First();
            Values[1] = WriteValueMgr::MakeV2Second();
        }

        void VerifyWriteValue(ArchestrAServices::ASBIDataV2Contract::WriteValue Value)
        {
            Assert::AreEqual(Value.HasQT,true);
            Assert::AreEqual(Value.HasQTSpecified ,true);
            Assert::AreEqual(Value.Value.Type , (System::UInt16) 9);
            Assert::AreEqual(Value.Value.Length , 10);
            Assert::AreEqual(Value.Value.Payload->Length , 2);
            Assert::AreEqual(Value.Value.Payload[0], (System::Byte) 11);
            Assert::AreEqual(Value.Value.Payload[1] ,(System::Byte) 12);
            Assert::AreEqual(Value.Status.Count , (System::SByte) 13);
            Assert::AreEqual(Value.Status.Payload->Length , 2);
            Assert::AreEqual(Value.Status.Payload[0] , (System::Byte) 14);
            Assert::AreEqual(Value.Status.Payload[1] , (System::Byte) 15);
            Assert::AreEqual(Value.Timestamp , DateTime(1616));
            Assert::AreEqual(Value.TimestampSpecified , true);
            Assert::AreEqual(Value.Comment , "Comment2");
        }
        void VerifyItemWriteCompletes(array<ArchestrAServices::ASBIDataV2Contract::ItemWriteComplete>   ^ CompleteWrites)
        {
//            Assert::AreEqual(CompleteWrites[0].
            
            Assert::AreEqual(CompleteWrites[0].Status[0].Item.Type, (System::UInt16) 1);
            Assert::AreEqual(CompleteWrites[0].Status[0].Item.ReferenceType,(System::UInt16) 2);
            Assert::AreEqual(CompleteWrites[0].Status[0].Item.Name, "identity");
            Assert::AreEqual(CompleteWrites[0].Status[0].Item.ContextName , "CONTEXT");
            Assert::AreEqual(CompleteWrites[0].Status[0].Item.Id ,(System::UInt64) 3);
            Assert::AreEqual(CompleteWrites[0].Status[0].ErrorCode ,(System::UInt16) 4);
            Assert::AreEqual(CompleteWrites[0].WriteHandle,(System::UInt32)  1);

            Assert::AreEqual(CompleteWrites[1].Status[0].Item.Type, (System::UInt16) 5);
            Assert::AreEqual(CompleteWrites[1].Status[0].Item.ReferenceType, (System::UInt16) 6);
            Assert::AreEqual(CompleteWrites[1].Status[0].Item.Name, "identity2");
            Assert::AreEqual(CompleteWrites[1].Status[0].Item.ContextName, "CONTEXT2");
            Assert::AreEqual(CompleteWrites[1].Status[0].Item.Id, (System::UInt64) 7);
            Assert::AreEqual(CompleteWrites[1].Status[0].ErrorCode, (System::UInt16) 8);
            Assert::AreEqual(CompleteWrites[1].WriteHandle, (System::UInt32) 2);

        }
        void VerifyItemRegistrationAry(array<ArchestrAServices::ASBIDataV2Contract::ItemRegistration> ^ ItemCapabilities)
        {
            Assert::IsTrue(false);
        }

        #pragma region Additional test attributes
		//
		//You can use the following additional attributes as you write your tests:
		//
		//Use ClassInitialize to run code before running the first test in the class
		//[ClassInitialize()]
		//static void MyClassInitialize(TestContext^ testContext) {};
		//
		//Use ClassCleanup to run code after all tests in a class have run
		//[ClassCleanup()]
		//static void MyClassCleanup() {};
		//
		//Use TestInitialize to run code before running each test
		//[TestInitialize()]
		//void MyTestInitialize() {};
		//
		//Use TestCleanup to run code after each test has run
		//[TestCleanup()]
		//void MyTestCleanup() {};
		//
		#pragma endregion 

		[TestMethod]
		void TestConnect()
		{
            IDataProxy_MOCK ^idpm = gcnew IDataProxy_MOCK();
            CIDataVersionAdapter ^v1Adapter= gcnew CIDataVersionAdapterV1(idpm);

            String ^errMsg;
            v1Adapter->Connect(errMsg);
            Assert::AreEqual(errMsg,"connected");
		};
		[TestMethod]
		void TestAbort()
		{
            IDataProxy_MOCK ^idpm = gcnew IDataProxy_MOCK();
            CIDataVersionAdapter ^v1Adapter= gcnew CIDataVersionAdapterV1(idpm);

            Assert::AreEqual(idpm->AbortCalled,false);
            v1Adapter->Abort();
            Assert::AreEqual(idpm->AbortCalled,true);
            idpm->ResetMock();
            Assert::AreEqual(idpm->AbortCalled,false);
        }
		[TestMethod]
		void TestDisconnect()
		{
            IDataProxy_MOCK ^idpm = gcnew IDataProxy_MOCK();
            CIDataVersionAdapter ^v1Adapter= gcnew CIDataVersionAdapterV1(idpm);

            Assert::AreEqual(idpm->DisconnectCalled,false);
            v1Adapter->Disconnect();
            Assert::AreEqual(idpm->DisconnectCalled,true);
            idpm->ResetMock();
            Assert::AreEqual(idpm->DisconnectCalled,false);
        }

		[TestMethod]
		void TestRead()
		{
            IDataProxy_MOCK ^idpm = gcnew IDataProxy_MOCK();
            CIDataVersionAdapter ^v1Adapter= gcnew CIDataVersionAdapterV1(idpm);

            Assert::AreEqual(idpm->DisconnectCalled,false);

            array<ArchestrAServices::ASBIDataV2Contract::ItemStatus>   ^ Status = nullptr;
            //    = gcnew array<ArchestrAServices::ASBIDataV2Contract::ItemStatus>(2);
            array<ArchestrAServices::ASBIDataV2Contract::RuntimeValue> ^ ItemValues = nullptr;
            //    = gcnew array<ArchestrAServices::ASBIDataV2Contract::RuntimeValue>(2);
            ConnectionId theId;
            theId.Id = Guid("11111111-2222-3333-4444-555555555555");
            array<ArchestrAServices::ASBIDataV2Contract::ItemIdentity> ^ Items
                = gcnew array<ArchestrAServices::ASBIDataV2Contract::ItemIdentity>(2);

            MakeItemIdentityAry(Items);

            ArchestrAResult result;
            result = v1Adapter->Read(Status,ItemValues,theId,Items);

            VerifyItemStatus(Status);

            VerifyRuntimeValue(ItemValues);

            Assert::AreEqual(result.ErrorCode,2);
            Assert::AreEqual(result.SpecificErrorCode,(System::UInt32) 3);
        }
		[TestMethod]
		void TestWrite()
		{
            IDataProxy_MOCK ^idpm = gcnew IDataProxy_MOCK();
            CIDataVersionAdapter ^v1Adapter= gcnew CIDataVersionAdapterV1(idpm);

            Assert::AreEqual(idpm->DisconnectCalled,false);

            array<ArchestrAServices::ASBIDataV2Contract::ItemStatus>   ^ Status = nullptr;

            ConnectionId theId;
            theId.Id = Guid("11111111-2222-3333-4444-555555555555");

            array<ArchestrAServices::ASBIDataV2Contract::ItemIdentity> ^ Items
                = gcnew array<ArchestrAServices::ASBIDataV2Contract::ItemIdentity>(2);
            MakeItemIdentityAry(Items);

            array<ArchestrAServices::ASBIDataV2Contract::WriteValue> ^Values 
                = gcnew array<ArchestrAServices::ASBIDataV2Contract::WriteValue>(2);
            MakeWriteValueAry(Values);


            ArchestrAResult result;

            result = v1Adapter->Write(Status,theId,Items,Values,444);

            VerifyItemStatus(Status);

            Assert::AreEqual(result.ErrorCode,2);
            Assert::AreEqual(result.SpecificErrorCode,(System::UInt32) 3);
        }
		[TestMethod]
		void TestWriteUser()
		{
            IDataProxy_MOCK ^idpm = gcnew IDataProxy_MOCK();
            CIDataVersionAdapter ^v1Adapter= gcnew CIDataVersionAdapterV1(idpm);

            Assert::AreEqual(idpm->DisconnectCalled,false);

            array<ArchestrAServices::ASBIDataV2Contract::ItemStatus>   ^ Status = nullptr;

            ConnectionId theId;
            theId.Id = Guid("11111111-2222-3333-4444-555555555555");

            array<ArchestrAServices::ASBIDataV2Contract::ItemIdentity> ^ Items
                = gcnew array<ArchestrAServices::ASBIDataV2Contract::ItemIdentity>(2);
            MakeItemIdentityAry(Items);

            array<ArchestrAServices::ASBIDataV2Contract::WriteValue> ^Values 
                = gcnew array<ArchestrAServices::ASBIDataV2Contract::WriteValue>(2);
            MakeWriteValueAry(Values);

            ArchestrAServices::ASBIDataV2Contract::UserToken token;
            token = UserTokenV2Mgr::MakeV2First();

            ArchestrAResult result;

            result = v1Adapter->WriteUser(Status,theId,Items,Values,token,444);

            VerifyItemStatus(Status);

            Assert::AreEqual(result.ErrorCode,2);
            Assert::AreEqual(result.SpecificErrorCode,(System::UInt32) 3);
        }
		[TestMethod]
		void TestWriteVerified()
		{
            IDataProxy_MOCK ^idpm = gcnew IDataProxy_MOCK();
            CIDataVersionAdapter ^v1Adapter= gcnew CIDataVersionAdapterV1(idpm);

            Assert::AreEqual(idpm->DisconnectCalled,false);

            array<ArchestrAServices::ASBIDataV2Contract::ItemStatus>   ^ Status = nullptr;

            ConnectionId theId;
            theId.Id = Guid("11111111-2222-3333-4444-555555555555");

            array<ArchestrAServices::ASBIDataV2Contract::ItemIdentity> ^ Items
                = gcnew array<ArchestrAServices::ASBIDataV2Contract::ItemIdentity>(2);
            MakeItemIdentityAry(Items);

            array<ArchestrAServices::ASBIDataV2Contract::WriteValue> ^Values 
                = gcnew array<ArchestrAServices::ASBIDataV2Contract::WriteValue>(2);
            MakeWriteValueAry(Values);

            ArchestrAServices::ASBIDataV2Contract::UserToken token;
            token = UserTokenV2Mgr::MakeV2First();
            ArchestrAServices::ASBIDataV2Contract::UserToken token2;
            token2 = UserTokenV2Mgr::MakeV2Second();

            ArchestrAResult result;

            result = v1Adapter->WriteVerified(Status,theId,Items,Values,token,token2,444);

            VerifyItemStatus(Status);

            Assert::AreEqual(result.ErrorCode,2);
            Assert::AreEqual(result.SpecificErrorCode,(System::UInt32) 3);
        }
		[TestMethod]
		void TestWriteSecured()
		{
            IDataProxy_MOCK ^idpm = gcnew IDataProxy_MOCK();
            CIDataVersionAdapter ^v1Adapter= gcnew CIDataVersionAdapterV1(idpm);

            Assert::AreEqual(idpm->DisconnectCalled,false);

            array<ArchestrAServices::ASBIDataV2Contract::ItemStatus>   ^ Status = nullptr;

            ConnectionId theId;
            theId.Id = Guid("11111111-2222-3333-4444-555555555555");

            array<ArchestrAServices::ASBIDataV2Contract::ItemIdentity> ^ Items
                = gcnew array<ArchestrAServices::ASBIDataV2Contract::ItemIdentity>(2);
            MakeItemIdentityAry(Items);

            array<ArchestrAServices::ASBIDataV2Contract::WriteValue> ^Values 
                = gcnew array<ArchestrAServices::ASBIDataV2Contract::WriteValue>(2);
            MakeWriteValueAry(Values);

            ArchestrAServices::ASBIDataV2Contract::UserToken token;
            token = UserTokenV2Mgr::MakeV2First();

            ArchestrAResult result;

            result = v1Adapter->WriteSecured(Status,theId,Items,Values,token,444);

            VerifyItemStatus(Status);

            Assert::AreEqual(result.ErrorCode,2);
            Assert::AreEqual(result.SpecificErrorCode,(System::UInt32) 3);
        }
#if 0
		[TestMethod]
		void TestWriteConfirmed()
		{
            IDataProxy_MOCK ^idpm = gcnew IDataProxy_MOCK();
            CIDataVersionAdapter ^v1Adapter= gcnew CIDataVersionAdapterV1(idpm);

            Assert::AreEqual(idpm->DisconnectCalled,false);

            // to be verified at end.
            ArchestrAServices::ASBIDataV2Contract::WriteValue ValueReceived;
            __int64 WriteToken;

            ConnectionId theId;

            theId.Id = Guid("11111111-2222-3333-4444-555555555555");

            ArchestrAServices::ASBIDataV2Contract::ItemIdentity Item;
            Item = ItemIdentityV2Mgr::MakeFirst();

            ArchestrAServices::ASBIDataV2Contract::WriteValue Value;
            Value = WriteValueMgr::MakeV2First();

            ArchestrAServices::ASBIDataV2Contract::UserToken token;
            ArchestrAServices::ASBIDataV2Contract::UserToken token2;

            token = UserTokenV2Mgr::MakeV2First();
            token2 = UserTokenV2Mgr::MakeV2Second();

            ArchestrAResult result;

            result = v1Adapter->WriteConfirmed(ValueReceived,WriteToken,theId,Item,Value,token,token2);

            VerifyWriteValue(ValueReceived);
            Assert::AreEqual(WriteToken,(System::Int64) 777);


            Assert::AreEqual(result.ErrorCode,2);
            Assert::AreEqual(result.SpecificErrorCode,(System::UInt32) 3);
        }
#endif
		[TestMethod]
		void TestPublishWriteComplete()
		{
            //ArchestrAResult IDataProxy_MOCK::PublishWriteComplete(  array<ItemWriteComplete> ^% CompleteWrites, 
            //                                                        ConnectionId Id)
            IDataProxy_MOCK ^idpm = gcnew IDataProxy_MOCK();
            CIDataVersionAdapter ^v1Adapter= gcnew CIDataVersionAdapterV1(idpm);

            Assert::AreEqual(idpm->DisconnectCalled,false);

            array<ArchestrAServices::ASBIDataV2Contract::ItemWriteComplete>   ^ CompleteWrites = nullptr;

            ConnectionId theId;
            theId.Id = Guid("11111111-2222-3333-4444-555555555555");


            ArchestrAResult result;

            result = v1Adapter->PublishWriteComplete(CompleteWrites,theId);

            VerifyItemWriteCompletes(CompleteWrites);

            Assert::AreEqual(result.ErrorCode,2);
            Assert::AreEqual(result.SpecificErrorCode,(System::UInt32) 3);
        }
		[TestMethod]
		void TestCreateSubscription()
		{

            IDataProxy_MOCK ^idpm = gcnew IDataProxy_MOCK();
            CIDataVersionAdapter ^v1Adapter= gcnew CIDataVersionAdapterV1(idpm);

            Assert::AreEqual(idpm->DisconnectCalled,false);

            __int64 SubscriptionId;

            ConnectionId theId;
            theId.Id = Guid("11111111-2222-3333-4444-555555555555");


            ArchestrAResult result;

            result = v1Adapter->CreateSubscription(SubscriptionId,theId,1010,1111);

            Assert::AreEqual(SubscriptionId,(System::Int64) 999);

            Assert::AreEqual(result.ErrorCode,2);
            Assert::AreEqual(result.SpecificErrorCode,(System::UInt32) 3);
        }
		[TestMethod]
		void TestDeleteSubscription()
		{

            IDataProxy_MOCK ^idpm = gcnew IDataProxy_MOCK();
            CIDataVersionAdapter ^v1Adapter= gcnew CIDataVersionAdapterV1(idpm);

            Assert::AreEqual(idpm->DisconnectCalled,false);

            ConnectionId theId;
            theId.Id = Guid("11111111-2222-3333-4444-555555555555");


            ArchestrAResult result;

            result = v1Adapter->DeleteSubscription(theId,999);


            Assert::AreEqual(result.ErrorCode,2);
            Assert::AreEqual(result.SpecificErrorCode,(System::UInt32) 3);
        }

		[TestMethod]
		void TestAddMonitoredItems()
		{
//ArchestrAResult IDataProxy_MOCK::AddMonitoredItems( array<ItemStatus>   ^% Status, 
//                                                    array<ItemRegistration> ^% ItemCapabilities,
//                                                    ConnectionId Id, 
//                                                    __int64 SubscriptionId, 
//                                                    array<MonitoredItem> ^ Items, 
//                                                    unsigned char RequireId)

            IDataProxy_MOCK ^idpm = gcnew IDataProxy_MOCK();
            CIDataVersionAdapter ^v1Adapter= gcnew CIDataVersionAdapterV1(idpm);

            Assert::AreEqual(idpm->DisconnectCalled,false);

            array<ArchestrAServices::ASBIDataV2Contract::ItemStatus>   ^ Status = nullptr;
            array<ArchestrAServices::ASBIDataV2Contract::ItemRegistration> ^ ItemCapabilities = nullptr;

            ConnectionId theId;
            theId.Id = Guid("11111111-2222-3333-4444-555555555555");

            array<ArchestrAServices::ASBIDataV2Contract::MonitoredItem> ^ Items 
                = gcnew array<ArchestrAServices::ASBIDataV2Contract::MonitoredItem>(2);

            Items[0] = MonitoredItemMgr::MakeV2First();
            Items[1] = MonitoredItemMgr::MakeV2Second();

            ArchestrAResult result;


            result = v1Adapter->AddMonitoredItems(Status,ItemCapabilities,theId,999,Items,21);

            VerifyItemStatus(Status);
            // TODO rjk: write verify of ItemRegistration array.
            VerifyItemRegistrationAry(ItemCapabilities);

            Assert::AreEqual(result.ErrorCode,2);
            Assert::AreEqual(result.SpecificErrorCode,(System::UInt32) 3);
        }


	};
}
