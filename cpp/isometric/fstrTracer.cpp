#include <fstrTracer.h>

fstream GlobalTraceFile;


void startTracing(char * tfname)
{
   // open for output/ truncate if it exists...
   GlobalTraceFile.open(tfname,ios::out );
}
void stopTracing()                        
{    
   GlobalTraceFile.close();
}
fstream& getTraceFile()
{
   return GlobalTraceFile;
}

