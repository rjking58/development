class ClockTick
{
public:
   ClockTick(DWORD waitInterval);
   bool CheckTick();
private:
   char  clss_name[11];
   DWORD mWaitInterval;
   DWORD mCurrentTickRef;
};

