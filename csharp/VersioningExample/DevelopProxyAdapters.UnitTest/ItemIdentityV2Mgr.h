using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;

using namespace ArchestrAServices::ASBContract;
using namespace ArchestrAServices::ASBIDataV2Contract;
using namespace ArchestrAServices::ASBIDataContract::V2;


    //public partial struct ItemIdentity
    //{
    //    public ushort Type
    //    /// <remarks/>
    //    public ushort ReferenceType
    //    public string Name
    //    
    //    public string ContextName
    //
    //    public ulong Id
    //    public bool IdSpecified
    //}


ref class ItemIdentityV2Mgr
{
public:
    static ArchestrAServices::ASBIDataV2Contract::ItemIdentity MakeFirst()
    {
        // ItemIdentity
        ArchestrAServices::ASBIDataV2Contract::ItemIdentity ident;
        ident.Type = 1;
        ident.ReferenceType = 2;
        ident.Name = "identity";
        ident.ContextName = "CONTEXT";
        ident.Id = 3;
        //IdSpecified

        return ident;
    }
    static ArchestrAServices::ASBIDataV2Contract::ItemIdentity MakeSecond()
    {
        // ItemIdentity
        ArchestrAServices::ASBIDataV2Contract::ItemIdentity ident;
        ident.Type = 5;
        ident.ReferenceType = 6;
        ident.Name = "identity2";
        ident.ContextName = "CONTEXT2";
        ident.Id = 7;
        //IdSpecified

        return ident;
    }
};
