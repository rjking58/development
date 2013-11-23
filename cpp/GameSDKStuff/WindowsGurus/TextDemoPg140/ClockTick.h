class ClockTick
{
public:
   ClockTick(DWORD waitInterval);
   bool CheckTick();
private:
   DWORD mWaitInterval;
   DWORD mCurrentTickRef;
};

