class EULService
{
public:
	EULService(const char *connectionStr);
	const char *GetName();
	int Cleanup();
	const char *GetEulSchemaVersion();
	const char *GetEulCodeVersion();


private:
	DCEEulHandle		*mpEULHandle;		// Pointer to the EUL handle for 

};

