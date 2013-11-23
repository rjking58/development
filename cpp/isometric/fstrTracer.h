#ifndef FSTRTRACER_H
#define FSTRTRACER_H



#include <fstream.h>

#ifdef TRACING
#define TRACE(X) getTraceFile() << __FILE__ << endl << "(" << __LINE__ << ") >>" << X << endl << flush
#define TRACE_NOHEAD(X) getTraceFile() << "(" << __LINE__ << ") >>" << X << endl << flush
#else
#define TRACE(X)
#define TRACE_NOHEAD(X)
#endif

void startTracing(char * tfname);
void stopTracing();                        
fstream& getTraceFile();
  
// put this in the file to be traced to open the stream..
//#ifdef DEBUGGING
// startTracing("name");
//#endif

// put this in the file to be traced to close the stream..
//#ifdef DEBUGGING
// stopTraceing();
//#endif



#endif // FSTRTRACER_H

