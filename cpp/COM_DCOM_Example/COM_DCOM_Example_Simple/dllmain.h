// dllmain.h : Declaration of module class.

class CCOM_DCOM_Example_SimpleModule : public ATL::CAtlDllModuleT< CCOM_DCOM_Example_SimpleModule >
{
public :
	DECLARE_LIBID(LIBID_COM_DCOM_Example_SimpleLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_COM_DCOM_EXAMPLE_SIMPLE, "{C59082D3-3F2F-4A9B-83E8-E8B46188ED6C}")
};

extern class CCOM_DCOM_Example_SimpleModule _AtlModule;
