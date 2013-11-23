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


    //public partial struct RuntimeValue
    //{
    //    public System.DateTime Timestamp
    //    public bool TimestampSpecified
    //    public ASBIDataContract.Variant Value
    //    public ASBStatus Status
    //}


ref class RuntimeValueMgr
{
public:
    static RuntimeValue MakeV1First()
    {
        ASBStatus stat;

        // only for full V2..
        //stat.Count = 2
        //stat.Payload = gcnew array<unsigned char>(2);
        //stat.Payload[0] = 1;
        //stat.Payload[1] = 2;

        Variant vrnt;
        vrnt.Type = 3;
        vrnt.Length = 4;
        vrnt.Payload= gcnew array<unsigned char>(2);
        vrnt.Payload[0] = 5;
        vrnt.Payload[1] = 6;

        RuntimeValue val;
        val.Timestamp = DateTime(444);
        //TimestampSpecified
        val.Value = vrnt;
        val.Status = stat;

        return val;
    }

    static RuntimeValue MakeV1Second()
    {
    
        ASBStatus stat;

        // only for full V2..
        //stat.Count = 2
        //stat.Payload = gcnew array<unsigned char>(2);
        //stat.Payload[0] = 1;
        //stat.Payload[1] = 2;

        Variant vrnt;
        vrnt.Type = 9;
        vrnt.Length = 10;
        vrnt.Payload= gcnew array<unsigned char>(2);
        vrnt.Payload[0] = 11;
        vrnt.Payload[1] = 12;

        RuntimeValue val;
        val.Timestamp = DateTime(555);
        //TimestampSpecified
        val.Value = vrnt;
        val.Status = stat;

        return val;
    }

};

