class ClockTick
{
public:
   ClockTick(DWORD waitInterval);
   bool CheckTick(DWORD &diff);
private:
   char  clss_name[11];
   DWORD mWaitInterval;
   DWORD mCurrentTickRef;
};

