#include <windows.h>
#include "ClockTick.h"

ClockTick::ClockTick(DWORD waitInterval)
:  mWaitInterval(waitInterval)
{
   mCurrentTickRef = GetTickCount();
   strcpy(clss_name,"ClockTick");
}
   
bool ClockTick::CheckTick()
{
   bool retval = false;
   DWORD CurrentTick = GetTickCount();
   if ((CurrentTick - mCurrentTickRef) > mWaitInterval)
   {  
      retval = true;
      mCurrentTickRef = CurrentTick;
   }
   return retval;
}

