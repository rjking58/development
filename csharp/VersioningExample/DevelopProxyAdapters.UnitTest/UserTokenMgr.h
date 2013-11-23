    //public partial struct UserToken
    //{
    //    public ushort Encryption
    //    public bool EncryptionSpecified
    //    public string HostName
    //    public ushort IdType
    //    public bool IdTypeSpecified
    //    public string LocationID
    //    public string Password
    //    public byte[] SamlToken
    //    public string UserName
    //    public ushort Validity
    //    public bool ValiditySpecified
    //    public byte[] X509Certificate
    //}
ref class UserTokenV2Mgr
{
public:
    static ArchestrAServices::ASBIDataV2Contract::UserToken MakeV2First()
    {
        //    public ushort     Encryption
        //    public bool       EncryptionSpecified
        //    public string     HostName
        //    public ushort     IdType
        //    public bool       IdTypeSpecified
        //    public string     LocationID
        //    public string     Password
        //    public byte[]     SamlToken
        //    public string     UserName
        //    public ushort     Validity
        //    public bool       ValiditySpecified
        //    public byte[]     X509Certificate

        //vrnt.Payload = gcnew array<unsigned char>(2);
        //vrnt.Payload[0] = 3;
        //vrnt.Payload[1] = 4;
        ArchestrAServices::ASBIDataV2Contract::UserToken val;

        val.Encryption = 1;
        val.HostName = "Host1";
        val.IdType = 2;
        val.LocationID = "LocationId1";
        val.Password = "Password1";
        val.SamlToken = gcnew array<unsigned char>(2);
        val.SamlToken[0] = 3;
        val.SamlToken[1] = 4;
        val.UserName = "Username1";
        val.Validity = 5;
        val.X509Certificate = gcnew array<unsigned char>(2);
        val.X509Certificate[0] = 6;
        val.X509Certificate[1] = 7;

        return val;
    }
    static ArchestrAServices::ASBIDataV2Contract::UserToken MakeV2Second()
    {
        //    public ushort     Encryption
        //    public bool       EncryptionSpecified
        //    public string     HostName
        //    public ushort     IdType
        //    public bool       IdTypeSpecified
        //    public string     LocationID
        //    public string     Password
        //    public byte[]     SamlToken
        //    public string     UserName
        //    public ushort     Validity
        //    public bool       ValiditySpecified
        //    public byte[]     X509Certificate

        //vrnt.Payload = gcnew array<unsigned char>(2);
        //vrnt.Payload[0] = 3;
        //vrnt.Payload[1] = 4;
        ArchestrAServices::ASBIDataV2Contract::UserToken val;

        val.Encryption = 8;
        val.HostName = "Host2";
        val.IdType = 9;
        val.LocationID = "LocationId2";
        val.Password = "Password2";
        val.SamlToken = gcnew array<unsigned char>(2);
        val.SamlToken[0] = 10;
        val.SamlToken[1] = 11;
        val.UserName = "Username2";
        val.Validity = 12;
        val.X509Certificate = gcnew array<unsigned char>(2);
        val.X509Certificate[0] = 13;
        val.X509Certificate[1] = 14;

        return val;
    }

};

