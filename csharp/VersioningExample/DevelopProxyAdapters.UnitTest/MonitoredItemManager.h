using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;

using namespace ArchestrAServices::ASBContract;
using namespace ArchestrAServices::ASBIDataV2Contract;
using namespace ArchestrAServices::ASBIDataContract::V2;

    //public partial struct MonitoredItem
    //{
    //    public ItemIdentity Item
    //    public ulong SampleInterval
    //    public bool Active
    //    public bool ActiveSpecified
    //    public ulong TimeDeadband
    //    public bool TimeDeadbandSpecified
    //    public ASBIDataContract.Variant ValueDeadband
    //    public ASBIDataContract.Variant UserData
    //}


ref class MonitoredItemMgr
{
public:
    static ArchestrAServices::ASBIDataV2Contract::MonitoredItem MakeV2First()
    {
        // ItemIdentity
        ArchestrAServices::ASBIDataV2Contract::MonitoredItem item;

        ArchestrAServices::ASBIDataV2Contract::ItemIdentity ident;

        ident = ItemIdentityV2Mgr::MakeFirst();

        ArchestrAServices::ASBIDataContract::V2::Variant vrnt;
        vrnt.Type = 1;
        vrnt.Length = 2;
        vrnt.Payload = gcnew array<unsigned char>(2);
        vrnt.Payload[0] = 3;
        vrnt.Payload[1] = 4;

        ArchestrAServices::ASBIDataContract::V2::Variant vrnt2;
        vrnt2.Type = 5;
        vrnt2.Length = 6;
        vrnt2.Payload = gcnew array<unsigned char>(2);
        vrnt2.Payload[0] = 7;
        vrnt2.Payload[1] = 8;

        item.Item = ident;
        item.SampleInterval = 20;
        item.Active = true;
        //    public bool ActiveSpecified
        item.TimeDeadband = 21;
        //    public bool TimeDeadbandSpecified
        item.ValueDeadband = vrnt;
        item.UserData = vrnt2;


        return item;
    }
    static ArchestrAServices::ASBIDataV2Contract::MonitoredItem MakeV2Second()
    {
        ArchestrAServices::ASBIDataV2Contract::MonitoredItem item;

        ArchestrAServices::ASBIDataV2Contract::ItemIdentity ident;

        ident = ItemIdentityV2Mgr::MakeSecond();

        ArchestrAServices::ASBIDataContract::V2::Variant vrnt;
        vrnt.Type = 9;
        vrnt.Length = 10;
        vrnt.Payload = gcnew array<unsigned char>(2);
        vrnt.Payload[0] = 11;
        vrnt.Payload[1] = 12;

        ArchestrAServices::ASBIDataContract::V2::Variant vrnt2;
        vrnt2.Type = 13;
        vrnt2.Length = 14;
        vrnt2.Payload = gcnew array<unsigned char>(2);
        vrnt2.Payload[0] = 15;
        vrnt2.Payload[1] = 16;

        item.Item = ident;
        item.SampleInterval = 22;
        item.Active = true;
        //    public bool ActiveSpecified
        item.TimeDeadband = 23;
        //    public bool TimeDeadbandSpecified
        item.ValueDeadband = vrnt;
        item.UserData = vrnt2;



        return item;
    }
};
