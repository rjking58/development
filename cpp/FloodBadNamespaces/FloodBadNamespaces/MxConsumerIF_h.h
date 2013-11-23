

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


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


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __MxConsumerIF_h_h__
#define __MxConsumerIF_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IDataClient_FWD_DEFINED__
#define __IDataClient_FWD_DEFINED__
typedef interface IDataClient IDataClient;

#endif 	/* __IDataClient_FWD_DEFINED__ */


#ifndef __DataClient_FWD_DEFINED__
#define __DataClient_FWD_DEFINED__

#ifdef __cplusplus
typedef class DataClient DataClient;
#else
typedef struct DataClient DataClient;
#endif /* __cplusplus */

#endif 	/* __DataClient_FWD_DEFINED__ */


#ifndef __IDataConsumerCallback_FWD_DEFINED__
#define __IDataConsumerCallback_FWD_DEFINED__
typedef interface IDataConsumerCallback IDataConsumerCallback;

#endif 	/* __IDataConsumerCallback_FWD_DEFINED__ */


#ifndef __IDataConsumer_FWD_DEFINED__
#define __IDataConsumer_FWD_DEFINED__
typedef interface IDataConsumer IDataConsumer;

#endif 	/* __IDataConsumer_FWD_DEFINED__ */


#ifndef __DataConsumer_FWD_DEFINED__
#define __DataConsumer_FWD_DEFINED__

#ifdef __cplusplus
typedef class DataConsumer DataConsumer;
#else
typedef struct DataConsumer DataConsumer;
#endif /* __cplusplus */

#endif 	/* __DataConsumer_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __MxDataConsumerScaleTests_LIBRARY_DEFINED__
#define __MxDataConsumerScaleTests_LIBRARY_DEFINED__

/* library MxDataConsumerScaleTests */
/* [helpstring][version][uuid] */ 

#pragma once
#pragma once
#pragma once
#pragma once
#pragma once
#pragma once
typedef /* [helpstring][version][uuid] */  DECLSPEC_UUID("15C679A3-AC29-4497-AC43-5EA8710BAD46") 
enum IItemIdentityType
    {
        Name	= 0,
        Id	= 1,
        NameAndId	= 2,
        Other	= 65535
    } 	IItemIdentityType;

typedef /* [helpstring][version][uuid] */  DECLSPEC_UUID("78FC3B63-DACE-4192-A550-1E645F607A37") 
enum IItemReferenceType
    {
        ItemReferenceNone	= 0,
        ItemReferenceAbsolute	= 1,
        ItemReferenceHierarchical	= 2,
        ItemReferenceRelative	= 3,
        ItemReferenceOther	= 65535
    } 	IItemReferenceType;

typedef /* [helpstring][version][uuid] */  DECLSPEC_UUID("77051582-C09B-4222-BA2A-766554B0D142") 
enum IDataType
    {
        TypeByte	= 0,
        TypeChar	= 1,
        TypeInt16	= 2,
        TypeUInt16	= 3,
        TypeInt32	= 4,
        TypeUInt32	= 5,
        TypeInt64	= 6,
        TypeUInt64	= 7,
        TypeFloat	= 8,
        TypeDouble	= 9,
        TypeString	= 10,
        TypeDateTime	= 11,
        TypeDuration	= 12,
        TypeGuid	= 13,
        TypeByteString	= 14,
        TypeLocaleID	= 15,
        TypeLocalizedText	= 16,
        TypeBool	= 17,
        TypeSByte	= 18,
        TypeErrorStatus	= 19,
        TypeEnum	= 20,
        TypeDataType	= 21,
        TypeSecurityClassification	= 22,
        TypeDataQuality	= 23,
        TypeByteArray	= 40,
        TypeCharArray	= 41,
        TypeInt16Array	= 42,
        TypeUInt16Array	= 43,
        TypeInt32Array	= 44,
        TypeUInt32Array	= 45,
        TypeInt64Array	= 46,
        TypeUInt64Array	= 47,
        TypeFloatArray	= 48,
        TypeDoubleArray	= 49,
        TypeStringArray	= 50,
        TypeDateTimeArray	= 51,
        TypeDurationArray	= 52,
        TypeGuidArray	= 53,
        TypeByteStringArray	= 54,
        TypeLocaleIDArray	= 55,
        TypeLocalizedTextArray	= 56,
        TypeBoolArray	= 57,
        TypeSByteArray	= 58,
        TypeEnumArray	= 60,
        TypeDataTypeArray	= 61,
        TypeSecurityClassificationArray	= 62,
        TypeDataQualityArray	= 63,
        TypeUnknown	= 65535
    } 	IDataType;

typedef /* [helpstring][version][uuid] */  DECLSPEC_UUID("90F6EA33-C670-4285-887E-74EB765CA422") 
enum IArchestrAError
    {
        ArchestrAErrorSuccess	= 0,
        ArchestrAErrorInvalidConnectionId	= 1,
        ArchestrAErrorApplicationAuthenticationError	= 2,
        ArchestrAErrorUserAuthenticationError	= 3,
        ArchestrAErrorUserAuthorizationError	= 4,
        ArchestrAErrorNotSupportedOperation	= 5,
        ArchestrAErrorMonitoredItemsNotFound	= 6,
        ArchestrAErrorInvalidSubscriptionID	= 7,
        ArchestrAErrorItemAlreadyRegistered	= 8,
        ArchestrAErrorItemAlreadyDeletedOrDoesNotExist	= 9,
        ArchestrAErrorInvalidMonitoredItems	= 10,
        ArchestrAErrorOperationFailed	= 11,
        ArchestrAErrorSpecificError	= 12,
        ArchestrAErrorBadNoCommunication	= 13,
        ArchestrAErrorBad_NothingToDo	= 14,
        ArchestrAErrorBad_TooManyOperations	= 15,
        ArchestrAErrorBad_NodeIdInvalid	= 16,
        ArchestrAErrorBrowseFailed	= 17,
        ArchestrAErrorWriteFailed_BadOutOfRange	= 18,
        ArchestrAErrorWriteFailed_BadTypeMismatch	= 19,
        ArchestrAErrorUnknown	= 65535
    } 	IArchestrAError;

typedef struct _IItemIdentity
    {
    WCHAR *ContextName;
    unsigned __int64 Id;
    WCHAR *Name;
    unsigned short ReferenceType;
    unsigned short Type;
    } 	IItemIdentity;

typedef struct _IWS_BYTES
    {
    ULONG length;
    BYTE *bytes;
    } 	IWS_BYTES;

typedef struct _IVariant
    {
    int Length;
    IWS_BYTES Payload;
    unsigned short Type;
    } 	IVariant;

typedef /* [helpstring][version][uuid] */  DECLSPEC_UUID("8D6DED71-C022-4F83-AF3D-BA24E13D22D0") struct IDataVariant
    {
    /* [helpstring] */ unsigned short Type;
    /* [helpstring] */ int Length;
    /* [helpstring] */ SAFEARRAY * PayLoad;
    } 	IDataVariant;

typedef struct _IMonitoredItem
    {
    unsigned char Active;
    IItemIdentity *Item;
    unsigned __int64 SampleInterval;
    unsigned __int64 TimeDeadband;
    IVariant *UserData;
    IVariant *ValueDeadband;
    } 	IMonitoredItem;

typedef struct _IUserToken
    {
    int Encryption;
    WCHAR *HostName;
    int IdType;
    WCHAR *LocationID;
    WCHAR *Password;
    WCHAR *UserName;
    IWS_BYTES SamlToken;
    unsigned short Validity;
    IWS_BYTES X509Certificate;
    } 	IUserToken;

typedef struct _DataUpdate
    {
    unsigned __int64 ItemId;
    unsigned long StatusCode;
    unsigned long StatusDetail;
    FILETIME Timestamp;
    unsigned long Quality;
    IVariant Value;
    } 	DataUpdate;

typedef struct _WriteRequest
    {
    IItemIdentity *Item;
    FILETIME Timestamp;
    unsigned short StatusCode;
    unsigned long Quality;
    IVariant Value;
    } 	WriteRequest;

typedef struct _WriteRequestWithReasonDesc
    {
    IItemIdentity *Item;
    FILETIME Timestamp;
    unsigned short StatusCode;
    short Quality;
    IVariant Value;
    LPCWSTR reasonDescription;
    } 	WriteRequestWithReasonDesc;

typedef /* [helpstring][version][uuid] */  DECLSPEC_UUID("E3E3A688-9FAE-4B44-B87A-95C1B3711F06") struct IItemIdentity2
    {
    /* [helpstring] */ unsigned short ReferenceType;
    /* [helpstring] */ unsigned short Type;
    /* [helpstring] */ BSTR ContextName;
    /* [helpstring] */ BSTR Name;
    /* [helpstring] */ unsigned __int64 Id;
    } 	IItemIdentity2;

typedef /* [helpstring][version][uuid] */  DECLSPEC_UUID("2AA2E248-AF2E-4FCC-95CD-C46AF4F0A1FA") struct IMonitoredItem2
    {
    /* [helpstring] */ unsigned char Active;
    /* [helpstring] */ unsigned short ReferenceType;
    /* [helpstring] */ unsigned short Type;
    /* [helpstring] */ BSTR ContextName;
    /* [helpstring] */ BSTR Name;
    /* [helpstring] */ unsigned __int64 Id;
    /* [helpstring] */ unsigned __int64 SampleInterval;
    /* [helpstring] */ unsigned __int64 TimeDeadband;
    } 	IMonitoredItem2;

typedef /* [helpstring][version][uuid] */  DECLSPEC_UUID("F6DF55F3-CECE-4857-96FE-3B390D6DAF77") struct WriteRequest2
    {
    /* [helpstring] */ unsigned short ReferenceType;
    /* [helpstring] */ unsigned short Type;
    /* [helpstring] */ BSTR ContextName;
    /* [helpstring] */ BSTR Name;
    /* [helpstring] */ unsigned __int64 Id;
    /* [helpstring] */ unsigned long Quality;
    /* [helpstring] */ IDataVariant Value;
    } 	WriteRequest2;

typedef /* [helpstring][version][uuid] */  DECLSPEC_UUID("4C6219B2-BE72-4EB4-9722-2D14F2B1D94E") struct DataChangeUpdate
    {
    /* [helpstring] */ ULONGLONG ItemId;
    /* [helpstring] */ LONG StatusCode;
    /* [helpstring] */ unsigned int HighDateTime;
    /* [helpstring] */ unsigned int LowDateTime;
    /* [helpstring] */ LONG Quality;
    /* [helpstring] */ IDataVariant Value;
    } 	DataChangeUpdate;

typedef struct _StatusItem
    {
    int ErrorCode;
    IItemIdentity *Item;
    } 	StatusItem;

typedef /* [helpstring][version][uuid] */  DECLSPEC_UUID("953FDABA-3C19-4B96-8B52-AF69BB3FFE0C") 
enum WriteCapabilityType
    {
        WriteUnknown	= 0,
        WriteNonsecure	= 1,
        WriteUser	= 2,
        WriteConfirm	= 4,
        WriteVerify	= 8
    } 	WriteCapabilityType;

typedef /* [helpstring][version][uuid] */  DECLSPEC_UUID("C826B0C8-F2AE-4032-BDF4-B74C189087BD") struct ASBResultCode
    {
    /* [helpstring] */ unsigned __int64 ItemId;
    /* [helpstring] */ HRESULT ErrorCode;
    /* [helpstring] */ unsigned int WriteCapability;
    /* [helpstring] */ unsigned int WriteHandle;
    } 	ASBResultCode;

typedef /* [helpstring][version][uuid] */  DECLSPEC_UUID("8830ECEF-F8A7-4897-9048-83CD085B8EB5") struct IArchestrAResult
    {
    /* [helpstring] */ IArchestrAError ErrorCode;
    /* [helpstring] */ unsigned int SpecificErrorCode;
    /* [helpstring] */ unsigned int Status;
    } 	IArchestrAResult;

typedef /* [helpstring][version][uuid] */  DECLSPEC_UUID("441AC761-08A3-4B41-804C-917C60D0C9CF") struct ItemRegistrationResponse
    {
    /* [helpstring] */ unsigned __int64 ItemId;
    /* [helpstring] */ unsigned __int64 UserData;
    /* [helpstring] */ HRESULT Status;
    /* [helpstring] */ int WriteCapability;
    } 	ItemRegistrationResponse;

typedef /* [helpstring][version][uuid] */  DECLSPEC_UUID("BD6BACE0-9002-44C5-8B7A-8119751F160A") struct ItemSubscriptionResponse
    {
    /* [helpstring] */ unsigned __int64 ItemId;
    /* [helpstring] */ unsigned __int64 UserData;
    /* [helpstring] */ HRESULT Status;
    } 	ItemSubscriptionResponse;

typedef /* [helpstring][version][uuid] */  DECLSPEC_UUID("B960F7E2-A583-49D3-8B15-DB3FE37F718B") struct ItemUnregisterResponse
    {
    /* [helpstring] */ unsigned __int64 ItemId;
    /* [helpstring] */ HRESULT Status;
    } 	ItemUnregisterResponse;

typedef struct _ItemDataUpdate
    {
    unsigned __int64 ItemId;
    unsigned long StatusCode;
    unsigned long StatusDetail;
    FILETIME Timestamp;
    unsigned long Quality;
    IVariant Value;
    } 	ItemDataUpdate;

typedef /* [helpstring][version][uuid] */  DECLSPEC_UUID("FF261F10-8BF9-4CEE-85D3-11D3D530EF9E") struct ItemDataUpdate2
    {
    /* [helpstring] */ unsigned __int64 ItemId;
    /* [helpstring] */ unsigned long StatusCode;
    /* [helpstring] */ unsigned int HighDateTime;
    /* [helpstring] */ unsigned int LowDateTime;
    /* [helpstring] */ unsigned long Quality;
    /* [helpstring] */ IDataVariant Value;
    } 	ItemDataUpdate2;

typedef /* [helpstring][version][uuid] */  DECLSPEC_UUID("5799A991-D9C1-4513-BB6C-D2D91E65F0E5") struct ItemWriteResponse
    {
    /* [helpstring] */ unsigned __int64 ItemId;
    /* [helpstring] */ unsigned __int64 UserData;
    /* [helpstring] */ HRESULT Status;
    } 	ItemWriteResponse;

typedef /* [helpstring][version][uuid] */  DECLSPEC_UUID("E671ED95-A301-4761-97F9-103D15CBCDF7") struct ItemActiveResponse
    {
    /* [helpstring] */ unsigned __int64 ItemId;
    /* [helpstring] */ unsigned __int64 UserData;
    /* [helpstring] */ HRESULT Status;
    } 	ItemActiveResponse;

typedef /* [helpstring][version][uuid] */  DECLSPEC_UUID("1FDA8A16-06B0-413D-BEB3-C764BDCB352A") struct MxResultCode
    {
    /* [helpstring] */ long lNamespaceId;
    /* [helpstring] */ HRESULT ErrorCode;
    /* [helpstring] */ unsigned int ArchestrErrorCode;
    /* [helpstring] */ unsigned int ArchestrSpecific;
    /* [helpstring] */ unsigned int ArchestrStatus;
    } 	MxResultCode;


EXTERN_C const IID LIBID_MxDataConsumerScaleTests;

#ifndef __IDataClient_INTERFACE_DEFINED__
#define __IDataClient_INTERFACE_DEFINED__

/* interface IDataClient */
/* [uuid][object] */ 


EXTERN_C const IID IID_IDataClient;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D55C14E8-FB22-48F8-A092-EF9BC452A083")
    IDataClient : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ BSTR bstrNamespace) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetLastError( 
            /* [retval][out] */ BSTR *LastError) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ResetHeap( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Connect( 
            /* [in] */ BSTR endPointUri,
            /* [in] */ unsigned __int64 timeout,
            /* [in] */ IUserToken *UserToken,
            /* [out] */ unsigned long *clientId,
            /* [retval][out] */ IArchestrAResult **pArchestrAResult) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Connect2( 
            /* [in] */ BSTR endPointUri,
            /* [in] */ unsigned __int64 timeout,
            /* [in] */ IUserToken *UserToken,
            /* [out] */ unsigned long *clientId,
            /* [retval][out] */ SAFEARRAY * *pArchestrAResult) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Disconnect( 
            /* [retval][out] */ IArchestrAResult **pArchestrAResult) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Disconnect2( 
            /* [retval][out] */ SAFEARRAY * *pArchestrAResult) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IsIDataClientConnected( 
            /* [retval][out] */ BOOL *bConnected) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CreateSubscription( 
            /* [in] */ __int64 MaxQueueSize,
            /* [in] */ unsigned __int64 SampleInterval,
            /* [in] */ int ActiveState,
            /* [out] */ __int64 *SubscriptionId,
            /* [retval][out] */ IArchestrAResult **pArchestrAResult) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CreateSubscription2( 
            /* [in] */ __int64 MaxQueueSize,
            /* [in] */ unsigned __int64 SampleInterval,
            /* [in] */ int ActiveState,
            /* [out] */ __int64 *SubscriptionId,
            /* [retval][out] */ SAFEARRAY * *pArchestrAResult) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ChangeSubscription( 
            /* [in] */ __int64 SubscriptionId,
            /* [in] */ int ActiveState,
            /* [retval][out] */ IArchestrAResult **pArchestrAResult) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ChangeSubscription2( 
            /* [in] */ __int64 SubscriptionId,
            /* [in] */ int ActiveState,
            /* [retval][out] */ SAFEARRAY * *pArchestrAResult) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DeleteSubscription( 
            /* [in] */ __int64 SubscriptionId,
            /* [retval][out] */ IArchestrAResult **pArchestrAResult) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DeleteSubscription2( 
            /* [in] */ __int64 SubscriptionId,
            /* [retval][out] */ SAFEARRAY * *pArchestrAResult) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AddMonitoredItems( 
            /* [in] */ __int64 SubscriptionId,
            /* [in] */ IMonitoredItem *MonItems,
            /* [in] */ unsigned int ItemsCount,
            /* [out] */ ASBResultCode **pResultCode,
            /* [out] */ unsigned int *ResultCount,
            /* [retval][out] */ IArchestrAResult **pArchestrAResult) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AddMonitoredItems2( 
            /* [in] */ __int64 SubscriptionId,
            /* [in] */ SAFEARRAY * MonItems,
            /* [in] */ unsigned int ItemsCount,
            /* [out] */ SAFEARRAY * *pResultCode,
            /* [out] */ unsigned int *ResultCount,
            /* [retval][out] */ SAFEARRAY * *pArchestrAResult) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ChangeMonitoredItems( 
            /* [in] */ __int64 SubscriptionId,
            /* [in] */ IMonitoredItem *MonItems,
            /* [in] */ unsigned int ItemsCount,
            /* [out] */ ASBResultCode **pResultCode,
            /* [out] */ unsigned int *ResultCount,
            /* [retval][out] */ IArchestrAResult **pArchestrAResult) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ChangeMonitoredItems2( 
            /* [in] */ __int64 SubscriptionId,
            /* [in] */ SAFEARRAY * MonItems,
            /* [in] */ unsigned int ItemsCount,
            /* [out] */ SAFEARRAY * *pResultCode,
            /* [out] */ unsigned int *ResultCount,
            /* [retval][out] */ SAFEARRAY * *pArchestrAResult) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DeleteMonitoredItems( 
            /* [in] */ __int64 SubscriptionId,
            /* [in] */ unsigned __int64 *ItemIds,
            /* [in] */ unsigned int ItemsCount,
            /* [out] */ ASBResultCode **pResultCode,
            /* [out] */ unsigned int *ResultCount,
            /* [retval][out] */ IArchestrAResult **pArchestrAResult) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DeleteMonitoredItems2( 
            /* [in] */ __int64 SubscriptionId,
            /* [in] */ SAFEARRAY * ItemIds,
            /* [in] */ unsigned int ItemsCount,
            /* [out] */ SAFEARRAY * *pResultCode,
            /* [out] */ unsigned int *ResultCount,
            /* [retval][out] */ SAFEARRAY * *pArchestrAResult) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RegisterItems( 
            /* [in] */ IItemIdentity *IdItems,
            /* [in] */ unsigned int ItemsCount,
            /* [out] */ ASBResultCode **pResultCode,
            /* [out] */ unsigned int *ResultCount,
            /* [retval][out] */ IArchestrAResult **pArchestrAResult) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RegisterItems2( 
            /* [in] */ SAFEARRAY * IdItems,
            /* [in] */ unsigned int ItemsCount,
            /* [out] */ SAFEARRAY * *pResultCode,
            /* [out] */ unsigned int *ResultCount,
            /* [retval][out] */ SAFEARRAY * *pArchestrAResult) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UnregisterItems( 
            /* [in] */ unsigned __int64 *varItems,
            /* [in] */ unsigned int ItemsCount,
            /* [out] */ ASBResultCode **pResultCode,
            /* [out] */ unsigned int *ResultCount,
            /* [retval][out] */ IArchestrAResult **pArchestrAResult) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UnregisterItems2( 
            /* [in] */ SAFEARRAY * varItems,
            /* [in] */ unsigned int ItemsCount,
            /* [out] */ SAFEARRAY * *pResultCode,
            /* [out] */ unsigned int *ResultCount,
            /* [retval][out] */ SAFEARRAY * *pArchestrAResult) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Write( 
            /* [in] */ WriteRequest *pWriteRequests,
            /* [in] */ unsigned int RequestsCount,
            /* [in] */ unsigned int WriteHandle,
            /* [in] */ IUserToken *User,
            /* [in] */ IUserToken *UserToken,
            /* [out] */ ASBResultCode **pResultCode,
            /* [out] */ unsigned int *ResultCount,
            /* [retval][out] */ IArchestrAResult **pArchestrAResult) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Write2( 
            /* [in] */ SAFEARRAY * pWriteRequests,
            /* [in] */ unsigned int RequestsCount,
            /* [in] */ unsigned int WriteHandle,
            /* [in] */ IUserToken *User,
            /* [in] */ IUserToken *UserToken,
            /* [out] */ SAFEARRAY * *pResultCode,
            /* [out] */ unsigned int *ResultCount,
            /* [retval][out] */ SAFEARRAY * *pArchestrAResult) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Publish( 
            /* [in] */ __int64 SubscriptionId,
            /* [out] */ DataUpdate **pDataUpdates,
            /* [out] */ unsigned int *UpdatesCount,
            /* [retval][out] */ IArchestrAResult **pArchestrAResult) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Publish2( 
            /* [in] */ __int64 SubscriptionId,
            /* [out] */ SAFEARRAY * *pDataUpdates,
            /* [out] */ unsigned int *ResultCount,
            /* [retval][out] */ SAFEARRAY * *pArchestrAResult) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PublishWriteComplete( 
            /* [out] */ ASBResultCode **pResultCode,
            /* [out] */ unsigned int *ResultCount,
            /* [retval][out] */ IArchestrAResult **pArchestrAResult) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PublishWriteComplete2( 
            /* [out] */ SAFEARRAY * *pResultCode,
            /* [out] */ unsigned int *ResultCount,
            /* [retval][out] */ SAFEARRAY * *pArchestrAResult) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Read( 
            /* [in] */ IItemIdentity *IdItems,
            /* [in] */ unsigned int ItemsCount,
            /* [out] */ DataUpdate **pDataUpdates,
            /* [out] */ unsigned int *UpdatesCount,
            /* [retval][out] */ IArchestrAResult **pArchestrAResult) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Read2( 
            /* [in] */ SAFEARRAY * IdItems,
            /* [in] */ unsigned int ItemsCount,
            /* [out] */ SAFEARRAY * *pDataUpdates,
            /* [out] */ unsigned int *UpdatesCount,
            /* [retval][out] */ SAFEARRAY * *pArchestrAResult) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDataClientVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDataClient * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDataClient * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDataClient * This);
        
        HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            IDataClient * This,
            /* [in] */ BSTR bstrNamespace);
        
        HRESULT ( STDMETHODCALLTYPE *GetLastError )( 
            IDataClient * This,
            /* [retval][out] */ BSTR *LastError);
        
        HRESULT ( STDMETHODCALLTYPE *ResetHeap )( 
            IDataClient * This);
        
        HRESULT ( STDMETHODCALLTYPE *Connect )( 
            IDataClient * This,
            /* [in] */ BSTR endPointUri,
            /* [in] */ unsigned __int64 timeout,
            /* [in] */ IUserToken *UserToken,
            /* [out] */ unsigned long *clientId,
            /* [retval][out] */ IArchestrAResult **pArchestrAResult);
        
        HRESULT ( STDMETHODCALLTYPE *Connect2 )( 
            IDataClient * This,
            /* [in] */ BSTR endPointUri,
            /* [in] */ unsigned __int64 timeout,
            /* [in] */ IUserToken *UserToken,
            /* [out] */ unsigned long *clientId,
            /* [retval][out] */ SAFEARRAY * *pArchestrAResult);
        
        HRESULT ( STDMETHODCALLTYPE *Disconnect )( 
            IDataClient * This,
            /* [retval][out] */ IArchestrAResult **pArchestrAResult);
        
        HRESULT ( STDMETHODCALLTYPE *Disconnect2 )( 
            IDataClient * This,
            /* [retval][out] */ SAFEARRAY * *pArchestrAResult);
        
        HRESULT ( STDMETHODCALLTYPE *IsIDataClientConnected )( 
            IDataClient * This,
            /* [retval][out] */ BOOL *bConnected);
        
        HRESULT ( STDMETHODCALLTYPE *CreateSubscription )( 
            IDataClient * This,
            /* [in] */ __int64 MaxQueueSize,
            /* [in] */ unsigned __int64 SampleInterval,
            /* [in] */ int ActiveState,
            /* [out] */ __int64 *SubscriptionId,
            /* [retval][out] */ IArchestrAResult **pArchestrAResult);
        
        HRESULT ( STDMETHODCALLTYPE *CreateSubscription2 )( 
            IDataClient * This,
            /* [in] */ __int64 MaxQueueSize,
            /* [in] */ unsigned __int64 SampleInterval,
            /* [in] */ int ActiveState,
            /* [out] */ __int64 *SubscriptionId,
            /* [retval][out] */ SAFEARRAY * *pArchestrAResult);
        
        HRESULT ( STDMETHODCALLTYPE *ChangeSubscription )( 
            IDataClient * This,
            /* [in] */ __int64 SubscriptionId,
            /* [in] */ int ActiveState,
            /* [retval][out] */ IArchestrAResult **pArchestrAResult);
        
        HRESULT ( STDMETHODCALLTYPE *ChangeSubscription2 )( 
            IDataClient * This,
            /* [in] */ __int64 SubscriptionId,
            /* [in] */ int ActiveState,
            /* [retval][out] */ SAFEARRAY * *pArchestrAResult);
        
        HRESULT ( STDMETHODCALLTYPE *DeleteSubscription )( 
            IDataClient * This,
            /* [in] */ __int64 SubscriptionId,
            /* [retval][out] */ IArchestrAResult **pArchestrAResult);
        
        HRESULT ( STDMETHODCALLTYPE *DeleteSubscription2 )( 
            IDataClient * This,
            /* [in] */ __int64 SubscriptionId,
            /* [retval][out] */ SAFEARRAY * *pArchestrAResult);
        
        HRESULT ( STDMETHODCALLTYPE *AddMonitoredItems )( 
            IDataClient * This,
            /* [in] */ __int64 SubscriptionId,
            /* [in] */ IMonitoredItem *MonItems,
            /* [in] */ unsigned int ItemsCount,
            /* [out] */ ASBResultCode **pResultCode,
            /* [out] */ unsigned int *ResultCount,
            /* [retval][out] */ IArchestrAResult **pArchestrAResult);
        
        HRESULT ( STDMETHODCALLTYPE *AddMonitoredItems2 )( 
            IDataClient * This,
            /* [in] */ __int64 SubscriptionId,
            /* [in] */ SAFEARRAY * MonItems,
            /* [in] */ unsigned int ItemsCount,
            /* [out] */ SAFEARRAY * *pResultCode,
            /* [out] */ unsigned int *ResultCount,
            /* [retval][out] */ SAFEARRAY * *pArchestrAResult);
        
        HRESULT ( STDMETHODCALLTYPE *ChangeMonitoredItems )( 
            IDataClient * This,
            /* [in] */ __int64 SubscriptionId,
            /* [in] */ IMonitoredItem *MonItems,
            /* [in] */ unsigned int ItemsCount,
            /* [out] */ ASBResultCode **pResultCode,
            /* [out] */ unsigned int *ResultCount,
            /* [retval][out] */ IArchestrAResult **pArchestrAResult);
        
        HRESULT ( STDMETHODCALLTYPE *ChangeMonitoredItems2 )( 
            IDataClient * This,
            /* [in] */ __int64 SubscriptionId,
            /* [in] */ SAFEARRAY * MonItems,
            /* [in] */ unsigned int ItemsCount,
            /* [out] */ SAFEARRAY * *pResultCode,
            /* [out] */ unsigned int *ResultCount,
            /* [retval][out] */ SAFEARRAY * *pArchestrAResult);
        
        HRESULT ( STDMETHODCALLTYPE *DeleteMonitoredItems )( 
            IDataClient * This,
            /* [in] */ __int64 SubscriptionId,
            /* [in] */ unsigned __int64 *ItemIds,
            /* [in] */ unsigned int ItemsCount,
            /* [out] */ ASBResultCode **pResultCode,
            /* [out] */ unsigned int *ResultCount,
            /* [retval][out] */ IArchestrAResult **pArchestrAResult);
        
        HRESULT ( STDMETHODCALLTYPE *DeleteMonitoredItems2 )( 
            IDataClient * This,
            /* [in] */ __int64 SubscriptionId,
            /* [in] */ SAFEARRAY * ItemIds,
            /* [in] */ unsigned int ItemsCount,
            /* [out] */ SAFEARRAY * *pResultCode,
            /* [out] */ unsigned int *ResultCount,
            /* [retval][out] */ SAFEARRAY * *pArchestrAResult);
        
        HRESULT ( STDMETHODCALLTYPE *RegisterItems )( 
            IDataClient * This,
            /* [in] */ IItemIdentity *IdItems,
            /* [in] */ unsigned int ItemsCount,
            /* [out] */ ASBResultCode **pResultCode,
            /* [out] */ unsigned int *ResultCount,
            /* [retval][out] */ IArchestrAResult **pArchestrAResult);
        
        HRESULT ( STDMETHODCALLTYPE *RegisterItems2 )( 
            IDataClient * This,
            /* [in] */ SAFEARRAY * IdItems,
            /* [in] */ unsigned int ItemsCount,
            /* [out] */ SAFEARRAY * *pResultCode,
            /* [out] */ unsigned int *ResultCount,
            /* [retval][out] */ SAFEARRAY * *pArchestrAResult);
        
        HRESULT ( STDMETHODCALLTYPE *UnregisterItems )( 
            IDataClient * This,
            /* [in] */ unsigned __int64 *varItems,
            /* [in] */ unsigned int ItemsCount,
            /* [out] */ ASBResultCode **pResultCode,
            /* [out] */ unsigned int *ResultCount,
            /* [retval][out] */ IArchestrAResult **pArchestrAResult);
        
        HRESULT ( STDMETHODCALLTYPE *UnregisterItems2 )( 
            IDataClient * This,
            /* [in] */ SAFEARRAY * varItems,
            /* [in] */ unsigned int ItemsCount,
            /* [out] */ SAFEARRAY * *pResultCode,
            /* [out] */ unsigned int *ResultCount,
            /* [retval][out] */ SAFEARRAY * *pArchestrAResult);
        
        HRESULT ( STDMETHODCALLTYPE *Write )( 
            IDataClient * This,
            /* [in] */ WriteRequest *pWriteRequests,
            /* [in] */ unsigned int RequestsCount,
            /* [in] */ unsigned int WriteHandle,
            /* [in] */ IUserToken *User,
            /* [in] */ IUserToken *UserToken,
            /* [out] */ ASBResultCode **pResultCode,
            /* [out] */ unsigned int *ResultCount,
            /* [retval][out] */ IArchestrAResult **pArchestrAResult);
        
        HRESULT ( STDMETHODCALLTYPE *Write2 )( 
            IDataClient * This,
            /* [in] */ SAFEARRAY * pWriteRequests,
            /* [in] */ unsigned int RequestsCount,
            /* [in] */ unsigned int WriteHandle,
            /* [in] */ IUserToken *User,
            /* [in] */ IUserToken *UserToken,
            /* [out] */ SAFEARRAY * *pResultCode,
            /* [out] */ unsigned int *ResultCount,
            /* [retval][out] */ SAFEARRAY * *pArchestrAResult);
        
        HRESULT ( STDMETHODCALLTYPE *Publish )( 
            IDataClient * This,
            /* [in] */ __int64 SubscriptionId,
            /* [out] */ DataUpdate **pDataUpdates,
            /* [out] */ unsigned int *UpdatesCount,
            /* [retval][out] */ IArchestrAResult **pArchestrAResult);
        
        HRESULT ( STDMETHODCALLTYPE *Publish2 )( 
            IDataClient * This,
            /* [in] */ __int64 SubscriptionId,
            /* [out] */ SAFEARRAY * *pDataUpdates,
            /* [out] */ unsigned int *ResultCount,
            /* [retval][out] */ SAFEARRAY * *pArchestrAResult);
        
        HRESULT ( STDMETHODCALLTYPE *PublishWriteComplete )( 
            IDataClient * This,
            /* [out] */ ASBResultCode **pResultCode,
            /* [out] */ unsigned int *ResultCount,
            /* [retval][out] */ IArchestrAResult **pArchestrAResult);
        
        HRESULT ( STDMETHODCALLTYPE *PublishWriteComplete2 )( 
            IDataClient * This,
            /* [out] */ SAFEARRAY * *pResultCode,
            /* [out] */ unsigned int *ResultCount,
            /* [retval][out] */ SAFEARRAY * *pArchestrAResult);
        
        HRESULT ( STDMETHODCALLTYPE *Read )( 
            IDataClient * This,
            /* [in] */ IItemIdentity *IdItems,
            /* [in] */ unsigned int ItemsCount,
            /* [out] */ DataUpdate **pDataUpdates,
            /* [out] */ unsigned int *UpdatesCount,
            /* [retval][out] */ IArchestrAResult **pArchestrAResult);
        
        HRESULT ( STDMETHODCALLTYPE *Read2 )( 
            IDataClient * This,
            /* [in] */ SAFEARRAY * IdItems,
            /* [in] */ unsigned int ItemsCount,
            /* [out] */ SAFEARRAY * *pDataUpdates,
            /* [out] */ unsigned int *UpdatesCount,
            /* [retval][out] */ SAFEARRAY * *pArchestrAResult);
        
        END_INTERFACE
    } IDataClientVtbl;

    interface IDataClient
    {
        CONST_VTBL struct IDataClientVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDataClient_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDataClient_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDataClient_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDataClient_Initialize(This,bstrNamespace)	\
    ( (This)->lpVtbl -> Initialize(This,bstrNamespace) ) 

#define IDataClient_GetLastError(This,LastError)	\
    ( (This)->lpVtbl -> GetLastError(This,LastError) ) 

#define IDataClient_ResetHeap(This)	\
    ( (This)->lpVtbl -> ResetHeap(This) ) 

#define IDataClient_Connect(This,endPointUri,timeout,UserToken,clientId,pArchestrAResult)	\
    ( (This)->lpVtbl -> Connect(This,endPointUri,timeout,UserToken,clientId,pArchestrAResult) ) 

#define IDataClient_Connect2(This,endPointUri,timeout,UserToken,clientId,pArchestrAResult)	\
    ( (This)->lpVtbl -> Connect2(This,endPointUri,timeout,UserToken,clientId,pArchestrAResult) ) 

#define IDataClient_Disconnect(This,pArchestrAResult)	\
    ( (This)->lpVtbl -> Disconnect(This,pArchestrAResult) ) 

#define IDataClient_Disconnect2(This,pArchestrAResult)	\
    ( (This)->lpVtbl -> Disconnect2(This,pArchestrAResult) ) 

#define IDataClient_IsIDataClientConnected(This,bConnected)	\
    ( (This)->lpVtbl -> IsIDataClientConnected(This,bConnected) ) 

#define IDataClient_CreateSubscription(This,MaxQueueSize,SampleInterval,ActiveState,SubscriptionId,pArchestrAResult)	\
    ( (This)->lpVtbl -> CreateSubscription(This,MaxQueueSize,SampleInterval,ActiveState,SubscriptionId,pArchestrAResult) ) 

#define IDataClient_CreateSubscription2(This,MaxQueueSize,SampleInterval,ActiveState,SubscriptionId,pArchestrAResult)	\
    ( (This)->lpVtbl -> CreateSubscription2(This,MaxQueueSize,SampleInterval,ActiveState,SubscriptionId,pArchestrAResult) ) 

#define IDataClient_ChangeSubscription(This,SubscriptionId,ActiveState,pArchestrAResult)	\
    ( (This)->lpVtbl -> ChangeSubscription(This,SubscriptionId,ActiveState,pArchestrAResult) ) 

#define IDataClient_ChangeSubscription2(This,SubscriptionId,ActiveState,pArchestrAResult)	\
    ( (This)->lpVtbl -> ChangeSubscription2(This,SubscriptionId,ActiveState,pArchestrAResult) ) 

#define IDataClient_DeleteSubscription(This,SubscriptionId,pArchestrAResult)	\
    ( (This)->lpVtbl -> DeleteSubscription(This,SubscriptionId,pArchestrAResult) ) 

#define IDataClient_DeleteSubscription2(This,SubscriptionId,pArchestrAResult)	\
    ( (This)->lpVtbl -> DeleteSubscription2(This,SubscriptionId,pArchestrAResult) ) 

#define IDataClient_AddMonitoredItems(This,SubscriptionId,MonItems,ItemsCount,pResultCode,ResultCount,pArchestrAResult)	\
    ( (This)->lpVtbl -> AddMonitoredItems(This,SubscriptionId,MonItems,ItemsCount,pResultCode,ResultCount,pArchestrAResult) ) 

#define IDataClient_AddMonitoredItems2(This,SubscriptionId,MonItems,ItemsCount,pResultCode,ResultCount,pArchestrAResult)	\
    ( (This)->lpVtbl -> AddMonitoredItems2(This,SubscriptionId,MonItems,ItemsCount,pResultCode,ResultCount,pArchestrAResult) ) 

#define IDataClient_ChangeMonitoredItems(This,SubscriptionId,MonItems,ItemsCount,pResultCode,ResultCount,pArchestrAResult)	\
    ( (This)->lpVtbl -> ChangeMonitoredItems(This,SubscriptionId,MonItems,ItemsCount,pResultCode,ResultCount,pArchestrAResult) ) 

#define IDataClient_ChangeMonitoredItems2(This,SubscriptionId,MonItems,ItemsCount,pResultCode,ResultCount,pArchestrAResult)	\
    ( (This)->lpVtbl -> ChangeMonitoredItems2(This,SubscriptionId,MonItems,ItemsCount,pResultCode,ResultCount,pArchestrAResult) ) 

#define IDataClient_DeleteMonitoredItems(This,SubscriptionId,ItemIds,ItemsCount,pResultCode,ResultCount,pArchestrAResult)	\
    ( (This)->lpVtbl -> DeleteMonitoredItems(This,SubscriptionId,ItemIds,ItemsCount,pResultCode,ResultCount,pArchestrAResult) ) 

#define IDataClient_DeleteMonitoredItems2(This,SubscriptionId,ItemIds,ItemsCount,pResultCode,ResultCount,pArchestrAResult)	\
    ( (This)->lpVtbl -> DeleteMonitoredItems2(This,SubscriptionId,ItemIds,ItemsCount,pResultCode,ResultCount,pArchestrAResult) ) 

#define IDataClient_RegisterItems(This,IdItems,ItemsCount,pResultCode,ResultCount,pArchestrAResult)	\
    ( (This)->lpVtbl -> RegisterItems(This,IdItems,ItemsCount,pResultCode,ResultCount,pArchestrAResult) ) 

#define IDataClient_RegisterItems2(This,IdItems,ItemsCount,pResultCode,ResultCount,pArchestrAResult)	\
    ( (This)->lpVtbl -> RegisterItems2(This,IdItems,ItemsCount,pResultCode,ResultCount,pArchestrAResult) ) 

#define IDataClient_UnregisterItems(This,varItems,ItemsCount,pResultCode,ResultCount,pArchestrAResult)	\
    ( (This)->lpVtbl -> UnregisterItems(This,varItems,ItemsCount,pResultCode,ResultCount,pArchestrAResult) ) 

#define IDataClient_UnregisterItems2(This,varItems,ItemsCount,pResultCode,ResultCount,pArchestrAResult)	\
    ( (This)->lpVtbl -> UnregisterItems2(This,varItems,ItemsCount,pResultCode,ResultCount,pArchestrAResult) ) 

#define IDataClient_Write(This,pWriteRequests,RequestsCount,WriteHandle,User,UserToken,pResultCode,ResultCount,pArchestrAResult)	\
    ( (This)->lpVtbl -> Write(This,pWriteRequests,RequestsCount,WriteHandle,User,UserToken,pResultCode,ResultCount,pArchestrAResult) ) 

#define IDataClient_Write2(This,pWriteRequests,RequestsCount,WriteHandle,User,UserToken,pResultCode,ResultCount,pArchestrAResult)	\
    ( (This)->lpVtbl -> Write2(This,pWriteRequests,RequestsCount,WriteHandle,User,UserToken,pResultCode,ResultCount,pArchestrAResult) ) 

#define IDataClient_Publish(This,SubscriptionId,pDataUpdates,UpdatesCount,pArchestrAResult)	\
    ( (This)->lpVtbl -> Publish(This,SubscriptionId,pDataUpdates,UpdatesCount,pArchestrAResult) ) 

#define IDataClient_Publish2(This,SubscriptionId,pDataUpdates,ResultCount,pArchestrAResult)	\
    ( (This)->lpVtbl -> Publish2(This,SubscriptionId,pDataUpdates,ResultCount,pArchestrAResult) ) 

#define IDataClient_PublishWriteComplete(This,pResultCode,ResultCount,pArchestrAResult)	\
    ( (This)->lpVtbl -> PublishWriteComplete(This,pResultCode,ResultCount,pArchestrAResult) ) 

#define IDataClient_PublishWriteComplete2(This,pResultCode,ResultCount,pArchestrAResult)	\
    ( (This)->lpVtbl -> PublishWriteComplete2(This,pResultCode,ResultCount,pArchestrAResult) ) 

#define IDataClient_Read(This,IdItems,ItemsCount,pDataUpdates,UpdatesCount,pArchestrAResult)	\
    ( (This)->lpVtbl -> Read(This,IdItems,ItemsCount,pDataUpdates,UpdatesCount,pArchestrAResult) ) 

#define IDataClient_Read2(This,IdItems,ItemsCount,pDataUpdates,UpdatesCount,pArchestrAResult)	\
    ( (This)->lpVtbl -> Read2(This,IdItems,ItemsCount,pDataUpdates,UpdatesCount,pArchestrAResult) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDataClient_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_DataClient;

#ifdef __cplusplus

class DECLSPEC_UUID("73BC4121-FF89-4762-901C-206E2BD9FE87")
DataClient;
#endif

#ifndef __IDataConsumerCallback_INTERFACE_DEFINED__
#define __IDataConsumerCallback_INTERFACE_DEFINED__

/* interface IDataConsumerCallback */
/* [uuid][object] */ 


EXTERN_C const IID IID_IDataConsumerCallback;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FA990F6C-2F68-4C46-84F7-0A0279ADFA99")
    IDataConsumerCallback : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE NamespaceResolved( 
            /* [in] */ long lNamespaceId) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDataConsumerCallbackVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDataConsumerCallback * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDataConsumerCallback * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDataConsumerCallback * This);
        
        HRESULT ( STDMETHODCALLTYPE *NamespaceResolved )( 
            IDataConsumerCallback * This,
            /* [in] */ long lNamespaceId);
        
        END_INTERFACE
    } IDataConsumerCallbackVtbl;

    interface IDataConsumerCallback
    {
        CONST_VTBL struct IDataConsumerCallbackVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDataConsumerCallback_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDataConsumerCallback_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDataConsumerCallback_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDataConsumerCallback_NamespaceResolved(This,lNamespaceId)	\
    ( (This)->lpVtbl -> NamespaceResolved(This,lNamespaceId) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDataConsumerCallback_INTERFACE_DEFINED__ */


#ifndef __IDataConsumer_INTERFACE_DEFINED__
#define __IDataConsumer_INTERFACE_DEFINED__

/* interface IDataConsumer */
/* [uuid][object] */ 


EXTERN_C const IID IID_IDataConsumer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CF507A59-D4E6-480D-B38E-7D8B035B8C94")
    IDataConsumer : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE RegisterCallback( 
            /* [in] */ IDataConsumerCallback *pCallback) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UnregisterCallback( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ResolveNamespace( 
            /* [in] */ BSTR bstrNamespace,
            /* [retval][out] */ long *pNamespaceId) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ResolveReference( 
            /* [in] */ long lNamespaceId,
            /* [in] */ BSTR bstrName,
            /* [in] */ BSTR bstrContext,
            /* [in] */ long lItemId,
            /* [in] */ unsigned __int64 ulUserData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Subscribe( 
            /* [in] */ long lNamespaceId,
            /* [in] */ long lItemId,
            /* [in] */ unsigned __int64 ulUserData,
            /* [in] */ BOOL bActive) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UnregisterReference( 
            /* [in] */ long lNamespaceId,
            /* [in] */ long lItemId) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ActivateSuspend( 
            /* [in] */ long lNamespaceId,
            /* [in] */ long lItemId,
            /* [in] */ unsigned __int64 ulUserData,
            /* [in] */ BOOL bActive) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Write( 
            /* [in] */ long lNamespaceId,
            /* [in] */ long lItemId,
            /* [in] */ unsigned __int64 ulUserData,
            /* [in] */ GUID *userId,
            /* [in] */ GUID *verifierId,
            /* [in] */ VARIANT_BOOL bUserVerified,
            /* [in] */ FILETIME ItemTimestamp,
            /* [in] */ unsigned __int32 ItemQuality,
            /* [in] */ IVariant *ItemValue,
            /* [in] */ unsigned __int32 MxOperationType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Write2( 
            /* [in] */ long lNamespaceId,
            /* [in] */ long lItemId,
            /* [in] */ unsigned __int64 ulUserData,
            /* [in] */ GUID *userId,
            /* [in] */ GUID *verifierId,
            /* [in] */ VARIANT_BOOL bUserVerified,
            /* [in] */ unsigned __int32 ItemQuality,
            /* [in] */ SAFEARRAY * ItemValue,
            /* [in] */ unsigned __int32 MxOperationType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE WriteWithReasonDesc( 
            /* [in] */ long lNamespaceId,
            /* [in] */ long lItemId,
            /* [in] */ unsigned __int64 ulUserData,
            /* [in] */ GUID *userId,
            /* [in] */ GUID *verifierId,
            /* [in] */ VARIANT_BOOL bUserVerified,
            /* [in] */ FILETIME ItemTimestamp,
            /* [in] */ short ItemQuality,
            /* [in] */ IVariant *ItemValue,
            /* [in] */ LPCWSTR reasonDescription,
            /* [in] */ unsigned __int32 MxOperationType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ProcessMessages( 
            /* [out] */ long *lSize,
            /* [size_is][size_is][out] */ ItemDataUpdate **updates,
            /* [out] */ MxResultCode **pResultCode,
            /* [retval][out] */ unsigned int *ResultCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ProcessMessages2( 
            /* [out] */ long *lSize,
            /* [size_is][size_is][out] */ SAFEARRAY * *updates,
            /* [out] */ SAFEARRAY * *pResultCode,
            /* [retval][out] */ unsigned int *ResultCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ProcessRegistration( 
            /* [out] */ long *lSize,
            /* [size_is][size_is][out] */ ItemRegistrationResponse **responses,
            /* [out] */ MxResultCode **pResultCode,
            /* [retval][out] */ unsigned int *ResultCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ProcessRegistration2( 
            /* [out] */ long *lSize,
            /* [size_is][size_is][out] */ SAFEARRAY * *responses,
            /* [out] */ SAFEARRAY * *pResultCode,
            /* [retval][out] */ unsigned int *ResultCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ProcessSubscription( 
            /* [out] */ long *lSize,
            /* [size_is][size_is][out] */ ItemSubscriptionResponse **responses,
            /* [out] */ MxResultCode **pResultCode,
            /* [retval][out] */ unsigned int *ResultCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ProcessSubscription2( 
            /* [out] */ long *lSize,
            /* [size_is][size_is][out] */ SAFEARRAY * *responses,
            /* [out] */ SAFEARRAY * *pResultCode,
            /* [retval][out] */ unsigned int *ResultCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ProcessUnregister( 
            /* [out] */ long *lSize,
            /* [size_is][size_is][out] */ ItemUnregisterResponse **responses,
            /* [out] */ MxResultCode **pResultCode,
            /* [retval][out] */ unsigned int *ResultCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ProcessUnregister2( 
            /* [out] */ long *lSize,
            /* [size_is][size_is][out] */ SAFEARRAY * *responses,
            /* [out] */ SAFEARRAY * *pResultCode,
            /* [retval][out] */ unsigned int *ResultCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ProcessWriteComplete( 
            /* [out] */ long *lSize,
            /* [size_is][size_is][out] */ ItemWriteResponse **responses,
            /* [out] */ MxResultCode **pResultCode,
            /* [retval][out] */ unsigned int *ResultCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ProcessWriteComplete2( 
            /* [out] */ long *lSize,
            /* [size_is][size_is][out] */ SAFEARRAY * *responses,
            /* [out] */ SAFEARRAY * *pResultCode,
            /* [retval][out] */ unsigned int *ResultCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ProcessActivateSuspend( 
            /* [out] */ long *lSize,
            /* [size_is][size_is][out] */ ItemActiveResponse **responses,
            /* [out] */ MxResultCode **pResultCode,
            /* [retval][out] */ unsigned int *ResultCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ProcessActivateSuspend2( 
            /* [out] */ long *lSize,
            /* [size_is][size_is][out] */ SAFEARRAY * *responses,
            /* [out] */ SAFEARRAY * *pResultCode,
            /* [retval][out] */ unsigned int *ResultCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IsConnected( 
            /* [in] */ long namespaceId,
            /* [out] */ BOOL *connected) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Shutdown( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDataConsumerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDataConsumer * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDataConsumer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDataConsumer * This);
        
        HRESULT ( STDMETHODCALLTYPE *RegisterCallback )( 
            IDataConsumer * This,
            /* [in] */ IDataConsumerCallback *pCallback);
        
        HRESULT ( STDMETHODCALLTYPE *UnregisterCallback )( 
            IDataConsumer * This);
        
        HRESULT ( STDMETHODCALLTYPE *ResolveNamespace )( 
            IDataConsumer * This,
            /* [in] */ BSTR bstrNamespace,
            /* [retval][out] */ long *pNamespaceId);
        
        HRESULT ( STDMETHODCALLTYPE *ResolveReference )( 
            IDataConsumer * This,
            /* [in] */ long lNamespaceId,
            /* [in] */ BSTR bstrName,
            /* [in] */ BSTR bstrContext,
            /* [in] */ long lItemId,
            /* [in] */ unsigned __int64 ulUserData);
        
        HRESULT ( STDMETHODCALLTYPE *Subscribe )( 
            IDataConsumer * This,
            /* [in] */ long lNamespaceId,
            /* [in] */ long lItemId,
            /* [in] */ unsigned __int64 ulUserData,
            /* [in] */ BOOL bActive);
        
        HRESULT ( STDMETHODCALLTYPE *UnregisterReference )( 
            IDataConsumer * This,
            /* [in] */ long lNamespaceId,
            /* [in] */ long lItemId);
        
        HRESULT ( STDMETHODCALLTYPE *ActivateSuspend )( 
            IDataConsumer * This,
            /* [in] */ long lNamespaceId,
            /* [in] */ long lItemId,
            /* [in] */ unsigned __int64 ulUserData,
            /* [in] */ BOOL bActive);
        
        HRESULT ( STDMETHODCALLTYPE *Write )( 
            IDataConsumer * This,
            /* [in] */ long lNamespaceId,
            /* [in] */ long lItemId,
            /* [in] */ unsigned __int64 ulUserData,
            /* [in] */ GUID *userId,
            /* [in] */ GUID *verifierId,
            /* [in] */ VARIANT_BOOL bUserVerified,
            /* [in] */ FILETIME ItemTimestamp,
            /* [in] */ unsigned __int32 ItemQuality,
            /* [in] */ IVariant *ItemValue,
            /* [in] */ unsigned __int32 MxOperationType);
        
        HRESULT ( STDMETHODCALLTYPE *Write2 )( 
            IDataConsumer * This,
            /* [in] */ long lNamespaceId,
            /* [in] */ long lItemId,
            /* [in] */ unsigned __int64 ulUserData,
            /* [in] */ GUID *userId,
            /* [in] */ GUID *verifierId,
            /* [in] */ VARIANT_BOOL bUserVerified,
            /* [in] */ unsigned __int32 ItemQuality,
            /* [in] */ SAFEARRAY * ItemValue,
            /* [in] */ unsigned __int32 MxOperationType);
        
        HRESULT ( STDMETHODCALLTYPE *WriteWithReasonDesc )( 
            IDataConsumer * This,
            /* [in] */ long lNamespaceId,
            /* [in] */ long lItemId,
            /* [in] */ unsigned __int64 ulUserData,
            /* [in] */ GUID *userId,
            /* [in] */ GUID *verifierId,
            /* [in] */ VARIANT_BOOL bUserVerified,
            /* [in] */ FILETIME ItemTimestamp,
            /* [in] */ short ItemQuality,
            /* [in] */ IVariant *ItemValue,
            /* [in] */ LPCWSTR reasonDescription,
            /* [in] */ unsigned __int32 MxOperationType);
        
        HRESULT ( STDMETHODCALLTYPE *ProcessMessages )( 
            IDataConsumer * This,
            /* [out] */ long *lSize,
            /* [size_is][size_is][out] */ ItemDataUpdate **updates,
            /* [out] */ MxResultCode **pResultCode,
            /* [retval][out] */ unsigned int *ResultCount);
        
        HRESULT ( STDMETHODCALLTYPE *ProcessMessages2 )( 
            IDataConsumer * This,
            /* [out] */ long *lSize,
            /* [size_is][size_is][out] */ SAFEARRAY * *updates,
            /* [out] */ SAFEARRAY * *pResultCode,
            /* [retval][out] */ unsigned int *ResultCount);
        
        HRESULT ( STDMETHODCALLTYPE *ProcessRegistration )( 
            IDataConsumer * This,
            /* [out] */ long *lSize,
            /* [size_is][size_is][out] */ ItemRegistrationResponse **responses,
            /* [out] */ MxResultCode **pResultCode,
            /* [retval][out] */ unsigned int *ResultCount);
        
        HRESULT ( STDMETHODCALLTYPE *ProcessRegistration2 )( 
            IDataConsumer * This,
            /* [out] */ long *lSize,
            /* [size_is][size_is][out] */ SAFEARRAY * *responses,
            /* [out] */ SAFEARRAY * *pResultCode,
            /* [retval][out] */ unsigned int *ResultCount);
        
        HRESULT ( STDMETHODCALLTYPE *ProcessSubscription )( 
            IDataConsumer * This,
            /* [out] */ long *lSize,
            /* [size_is][size_is][out] */ ItemSubscriptionResponse **responses,
            /* [out] */ MxResultCode **pResultCode,
            /* [retval][out] */ unsigned int *ResultCount);
        
        HRESULT ( STDMETHODCALLTYPE *ProcessSubscription2 )( 
            IDataConsumer * This,
            /* [out] */ long *lSize,
            /* [size_is][size_is][out] */ SAFEARRAY * *responses,
            /* [out] */ SAFEARRAY * *pResultCode,
            /* [retval][out] */ unsigned int *ResultCount);
        
        HRESULT ( STDMETHODCALLTYPE *ProcessUnregister )( 
            IDataConsumer * This,
            /* [out] */ long *lSize,
            /* [size_is][size_is][out] */ ItemUnregisterResponse **responses,
            /* [out] */ MxResultCode **pResultCode,
            /* [retval][out] */ unsigned int *ResultCount);
        
        HRESULT ( STDMETHODCALLTYPE *ProcessUnregister2 )( 
            IDataConsumer * This,
            /* [out] */ long *lSize,
            /* [size_is][size_is][out] */ SAFEARRAY * *responses,
            /* [out] */ SAFEARRAY * *pResultCode,
            /* [retval][out] */ unsigned int *ResultCount);
        
        HRESULT ( STDMETHODCALLTYPE *ProcessWriteComplete )( 
            IDataConsumer * This,
            /* [out] */ long *lSize,
            /* [size_is][size_is][out] */ ItemWriteResponse **responses,
            /* [out] */ MxResultCode **pResultCode,
            /* [retval][out] */ unsigned int *ResultCount);
        
        HRESULT ( STDMETHODCALLTYPE *ProcessWriteComplete2 )( 
            IDataConsumer * This,
            /* [out] */ long *lSize,
            /* [size_is][size_is][out] */ SAFEARRAY * *responses,
            /* [out] */ SAFEARRAY * *pResultCode,
            /* [retval][out] */ unsigned int *ResultCount);
        
        HRESULT ( STDMETHODCALLTYPE *ProcessActivateSuspend )( 
            IDataConsumer * This,
            /* [out] */ long *lSize,
            /* [size_is][size_is][out] */ ItemActiveResponse **responses,
            /* [out] */ MxResultCode **pResultCode,
            /* [retval][out] */ unsigned int *ResultCount);
        
        HRESULT ( STDMETHODCALLTYPE *ProcessActivateSuspend2 )( 
            IDataConsumer * This,
            /* [out] */ long *lSize,
            /* [size_is][size_is][out] */ SAFEARRAY * *responses,
            /* [out] */ SAFEARRAY * *pResultCode,
            /* [retval][out] */ unsigned int *ResultCount);
        
        HRESULT ( STDMETHODCALLTYPE *IsConnected )( 
            IDataConsumer * This,
            /* [in] */ long namespaceId,
            /* [out] */ BOOL *connected);
        
        HRESULT ( STDMETHODCALLTYPE *Shutdown )( 
            IDataConsumer * This);
        
        END_INTERFACE
    } IDataConsumerVtbl;

    interface IDataConsumer
    {
        CONST_VTBL struct IDataConsumerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDataConsumer_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDataConsumer_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDataConsumer_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDataConsumer_RegisterCallback(This,pCallback)	\
    ( (This)->lpVtbl -> RegisterCallback(This,pCallback) ) 

#define IDataConsumer_UnregisterCallback(This)	\
    ( (This)->lpVtbl -> UnregisterCallback(This) ) 

#define IDataConsumer_ResolveNamespace(This,bstrNamespace,pNamespaceId)	\
    ( (This)->lpVtbl -> ResolveNamespace(This,bstrNamespace,pNamespaceId) ) 

#define IDataConsumer_ResolveReference(This,lNamespaceId,bstrName,bstrContext,lItemId,ulUserData)	\
    ( (This)->lpVtbl -> ResolveReference(This,lNamespaceId,bstrName,bstrContext,lItemId,ulUserData) ) 

#define IDataConsumer_Subscribe(This,lNamespaceId,lItemId,ulUserData,bActive)	\
    ( (This)->lpVtbl -> Subscribe(This,lNamespaceId,lItemId,ulUserData,bActive) ) 

#define IDataConsumer_UnregisterReference(This,lNamespaceId,lItemId)	\
    ( (This)->lpVtbl -> UnregisterReference(This,lNamespaceId,lItemId) ) 

#define IDataConsumer_ActivateSuspend(This,lNamespaceId,lItemId,ulUserData,bActive)	\
    ( (This)->lpVtbl -> ActivateSuspend(This,lNamespaceId,lItemId,ulUserData,bActive) ) 

#define IDataConsumer_Write(This,lNamespaceId,lItemId,ulUserData,userId,verifierId,bUserVerified,ItemTimestamp,ItemQuality,ItemValue,MxOperationType)	\
    ( (This)->lpVtbl -> Write(This,lNamespaceId,lItemId,ulUserData,userId,verifierId,bUserVerified,ItemTimestamp,ItemQuality,ItemValue,MxOperationType) ) 

#define IDataConsumer_Write2(This,lNamespaceId,lItemId,ulUserData,userId,verifierId,bUserVerified,ItemQuality,ItemValue,MxOperationType)	\
    ( (This)->lpVtbl -> Write2(This,lNamespaceId,lItemId,ulUserData,userId,verifierId,bUserVerified,ItemQuality,ItemValue,MxOperationType) ) 

#define IDataConsumer_WriteWithReasonDesc(This,lNamespaceId,lItemId,ulUserData,userId,verifierId,bUserVerified,ItemTimestamp,ItemQuality,ItemValue,reasonDescription,MxOperationType)	\
    ( (This)->lpVtbl -> WriteWithReasonDesc(This,lNamespaceId,lItemId,ulUserData,userId,verifierId,bUserVerified,ItemTimestamp,ItemQuality,ItemValue,reasonDescription,MxOperationType) ) 

#define IDataConsumer_ProcessMessages(This,lSize,updates,pResultCode,ResultCount)	\
    ( (This)->lpVtbl -> ProcessMessages(This,lSize,updates,pResultCode,ResultCount) ) 

#define IDataConsumer_ProcessMessages2(This,lSize,updates,pResultCode,ResultCount)	\
    ( (This)->lpVtbl -> ProcessMessages2(This,lSize,updates,pResultCode,ResultCount) ) 

#define IDataConsumer_ProcessRegistration(This,lSize,responses,pResultCode,ResultCount)	\
    ( (This)->lpVtbl -> ProcessRegistration(This,lSize,responses,pResultCode,ResultCount) ) 

#define IDataConsumer_ProcessRegistration2(This,lSize,responses,pResultCode,ResultCount)	\
    ( (This)->lpVtbl -> ProcessRegistration2(This,lSize,responses,pResultCode,ResultCount) ) 

#define IDataConsumer_ProcessSubscription(This,lSize,responses,pResultCode,ResultCount)	\
    ( (This)->lpVtbl -> ProcessSubscription(This,lSize,responses,pResultCode,ResultCount) ) 

#define IDataConsumer_ProcessSubscription2(This,lSize,responses,pResultCode,ResultCount)	\
    ( (This)->lpVtbl -> ProcessSubscription2(This,lSize,responses,pResultCode,ResultCount) ) 

#define IDataConsumer_ProcessUnregister(This,lSize,responses,pResultCode,ResultCount)	\
    ( (This)->lpVtbl -> ProcessUnregister(This,lSize,responses,pResultCode,ResultCount) ) 

#define IDataConsumer_ProcessUnregister2(This,lSize,responses,pResultCode,ResultCount)	\
    ( (This)->lpVtbl -> ProcessUnregister2(This,lSize,responses,pResultCode,ResultCount) ) 

#define IDataConsumer_ProcessWriteComplete(This,lSize,responses,pResultCode,ResultCount)	\
    ( (This)->lpVtbl -> ProcessWriteComplete(This,lSize,responses,pResultCode,ResultCount) ) 

#define IDataConsumer_ProcessWriteComplete2(This,lSize,responses,pResultCode,ResultCount)	\
    ( (This)->lpVtbl -> ProcessWriteComplete2(This,lSize,responses,pResultCode,ResultCount) ) 

#define IDataConsumer_ProcessActivateSuspend(This,lSize,responses,pResultCode,ResultCount)	\
    ( (This)->lpVtbl -> ProcessActivateSuspend(This,lSize,responses,pResultCode,ResultCount) ) 

#define IDataConsumer_ProcessActivateSuspend2(This,lSize,responses,pResultCode,ResultCount)	\
    ( (This)->lpVtbl -> ProcessActivateSuspend2(This,lSize,responses,pResultCode,ResultCount) ) 

#define IDataConsumer_IsConnected(This,namespaceId,connected)	\
    ( (This)->lpVtbl -> IsConnected(This,namespaceId,connected) ) 

#define IDataConsumer_Shutdown(This)	\
    ( (This)->lpVtbl -> Shutdown(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDataConsumer_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_DataConsumer;

#ifdef __cplusplus

class DECLSPEC_UUID("85209FB2-0BA1-4594-BBC4-59D3DDAB823D")
DataConsumer;
#endif
#endif /* __MxDataConsumerScaleTests_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


