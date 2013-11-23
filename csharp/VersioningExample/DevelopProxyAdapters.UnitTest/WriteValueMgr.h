

#include "stdafx.h"

using namespace System;
using namespace ArchestrAServices::ASBContract;
using namespace ArchestrAServices::ASBIDataContract;
using namespace ArchestrAServices::Proxy;

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
    

ref class WriteValueMgr
{
public:
    static ArchestrAServices::ASBIDataV2Contract::WriteValue MakeV2First()
    {
        //    Values[0].HasQT
        //&&  Values[0].HasQTSpecified 
        //&&  Values[0].Value.Type == 1
        //&&  Values[0].Value.Length == 2
        //&&  Values[0].Value.Payload.Length == 2
        //&&  Values[0].Value.Payload[0] == 3
        //&&  Values[0].Value.Payload[1] == 4
        //&&  Values[0].Status.Count == 5
        //&&  Values[0].Status.Payload.Length == 2
        //&&  Values[0].Status.Payload[0] == 6
        //&&  Values[0].Status.Payload[1] == 7
        //&&  Values[0].Timestamp == DateTime(888)
        //&&  Values[0].TimestampSpecified == true
        //&&  Values[0].Comment == "Comment1"

        ArchestrAServices::ASBIDataV2Contract::WriteValue val;

        ArchestrAServices::ASBIDataContract::V2::Variant vrnt;
        vrnt.Type = 1;
        vrnt.Length = 2;
        vrnt.Payload = gcnew array<unsigned char>(2);
        vrnt.Payload[0] = 3;
        vrnt.Payload[1] = 4;

        ArchestrAServices::ASBIDataV2Contract::ASBStatus stat;
        stat.Count = 5;
        stat.Payload = gcnew array<unsigned char>(2);
        stat.Payload[0] = 6;
        stat.Payload[1] = 7;


        val.HasQT = true;
        //val.HasQTSpecified 
        val.Timestamp = DateTime(888);
        //TimestampSpecified
        val.Value = vrnt;
        val.Status = stat;
        val.Comment = "Comment1";
        // set in the actual test cases so that it can be tested
        // in variations.
        //ArrayElementIndex
        //ArrayElementIndexSpecified

        return val;
    }

    static ArchestrAServices::ASBIDataV2Contract::WriteValue MakeV2Second()
    {
        //&&  Values[1].HasQT
        //&&  Values[1].HasQTSpecified 
        //&&  Values[1].Value.Type == 9
        //&&  Values[1].Value.Length == 10
        //&&  Values[1].Value.Payload.Length == 2
        //&&  Values[1].Value.Payload[0] == 11
        //&&  Values[1].Value.Payload[1] == 12
        //&&  Values[1].Status.Count == 13
        //&&  Values[1].Status.Payload.Length == 2
        //&&  Values[1].Status.Payload[0] == 14
        //&&  Values[1].Status.Payload[1] == 15
        //&&  Values[1].Timestamp == DateTime(1616)
        //&&  Values[1].TimestampSpecified == true
        //&&  Values[1].Comment == "Comment2";

        ArchestrAServices::ASBIDataV2Contract::WriteValue val;

        ArchestrAServices::ASBIDataContract::V2::Variant vrnt;
        vrnt.Type = 9;
        vrnt.Length = 10;
        vrnt.Payload = gcnew array<unsigned char>(2);
        vrnt.Payload[0] = 11;
        vrnt.Payload[1] = 12;

        ArchestrAServices::ASBIDataV2Contract::ASBStatus stat;
        stat.Count = 13;
        stat.Payload = gcnew array<unsigned char>(2);
        stat.Payload[0] = 14;
        stat.Payload[1] = 15;


        val.HasQT = true;
        //val.HasQTSpecified 
        val.Timestamp = DateTime(1616);
        //TimestampSpecified
        val.Value = vrnt;
        val.Status = stat;
        val.Comment = "Comment2";
        // set in the actual test cases so that it can be tested
        // in variations.
        //ArrayElementIndex
        //ArrayElementIndexSpecified

        return val;
    }
    static ArchestrAServices::ASBContract::WriteValue MakeV1Second()
    {
        //&&  Values[1].HasQT
        //&&  Values[1].HasQTSpecified 
        //&&  Values[1].Value.Type == 9
        //&&  Values[1].Value.Length == 10
        //&&  Values[1].Value.Payload.Length == 2
        //&&  Values[1].Value.Payload[0] == 11
        //&&  Values[1].Value.Payload[1] == 12
        //&&  Values[1].Status.Count == 13
        //&&  Values[1].Status.Payload.Length == 2
        //&&  Values[1].Status.Payload[0] == 14
        //&&  Values[1].Status.Payload[1] == 15
        //&&  Values[1].Timestamp == DateTime(1616)
        //&&  Values[1].TimestampSpecified == true
        //&&  Values[1].Comment == "Comment2";

        ArchestrAServices::ASBContract::WriteValue val;

        ArchestrAServices::ASBIDataContract::Variant vrnt;
        vrnt.Type = 9;
        vrnt.Length = 10;
        vrnt.Payload = gcnew array<unsigned char>(2);
        vrnt.Payload[0] = 11;
        vrnt.Payload[1] = 12;

        ArchestrAServices::ASBContract::ASBStatus stat;
        stat.Count = 13;
        stat.Payload = gcnew array<unsigned char>(2);
        stat.Payload[0] = 14;
        stat.Payload[1] = 15;


        val.HasQT = true;
        //val.HasQTSpecified 
        val.Timestamp = DateTime(1616);
        //TimestampSpecified
        val.Value = vrnt;
        val.Status = stat;
        val.Comment = "Comment2";
        // set in the actual test cases so that it can be tested
        // in variations.
        //ArrayElementIndex
        //ArrayElementIndexSpecified

        return val;
    }

};

