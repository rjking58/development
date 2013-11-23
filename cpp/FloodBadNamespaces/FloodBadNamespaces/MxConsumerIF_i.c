

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 8.00.0595 */
/* at Thu Jul 25 14:18:33 2013
 */
/* Compiler settings for MxConsumerIF.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0595 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, LIBID_MxDataConsumerScaleTests,0x980174CF,0x5730,0x4941,0xB5,0x54,0xA7,0x9A,0xC8,0xD1,0xD5,0xEE);


MIDL_DEFINE_GUID(IID, IID_IDataClient,0xD55C14E8,0xFB22,0x48F8,0xA0,0x92,0xEF,0x9B,0xC4,0x52,0xA0,0x83);


MIDL_DEFINE_GUID(CLSID, CLSID_DataClient,0x73BC4121,0xFF89,0x4762,0x90,0x1C,0x20,0x6E,0x2B,0xD9,0xFE,0x87);


MIDL_DEFINE_GUID(IID, IID_IDataConsumerCallback,0xFA990F6C,0x2F68,0x4C46,0x84,0xF7,0x0A,0x02,0x79,0xAD,0xFA,0x99);


MIDL_DEFINE_GUID(IID, IID_IDataConsumer,0xCF507A59,0xD4E6,0x480D,0xB3,0x8E,0x7D,0x8B,0x03,0x5B,0x8C,0x94);


MIDL_DEFINE_GUID(CLSID, CLSID_DataConsumer,0x85209FB2,0x0BA1,0x4594,0xBB,0xC4,0x59,0xD3,0xDD,0xAB,0x82,0x3D);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



