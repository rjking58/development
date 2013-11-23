
#ifndef DebugOut_H
#define DebugOut_H
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

class DebugOut
{
	public:
		DebugOut(char * FName)
		{
			mFName = FName;
		}

      void info(  const char *Name,
                  const char *SRCname,
                  const int Line)
      {
			OpenIT();
			header(SRCname,Line,Name);
			fprintf(OutputF,"\n");
			CloseIT();
      }
      void fentry(const char *Name,
                  const char *SRCname,
                  const int Line)
      {
			OpenIT();
			header(SRCname,Line,Name);
			fprintf(OutputF,"ENTRY\n");
			CloseIT();
      }
      void fexit( const char *Name,
                  const char *SRCname,
                  const int Line)
      {
			OpenIT();
			header(SRCname,Line,Name);
			fprintf(OutputF,"EXIT\n");
			CloseIT();
      }
		void put(int AnInt,
					const char *Name,
					const char *SRCname,
					const int Line)
		{
			OpenIT();
			header(SRCname,Line,Name);
			fprintf(OutputF,"%d",AnInt);
			fprintf(OutputF,"<-\n");
			CloseIT();
		}

		void put(char AChar,
					const char *Name,
					const char *SRCname,
					const int Line)
		{
			OpenIT();
			header(SRCname,Line,Name);
			fprintf(OutputF,"'%c'",AChar);
			fprintf(OutputF,"<-\n");
			CloseIT();
		}  
		void put(char * AzString, 
					const char *Name,
					const char *SRCname,
					const int Line)
		{
			OpenIT();
			header(SRCname,Line,Name);
			fprintf(OutputF,"%s",AzString);
			fprintf(OutputF,"<-\n");
			CloseIT();
		}  
		void put(int * AnIntArray, 
					const char *Name,
					int AnIntArrayLen, 
					const char *SRCname,
					const int Line)
		{
			int i;

			OpenIT();
			header(SRCname,Line,Name);
			for (i = 0; i < AnIntArrayLen; i++)
				fprintf(OutputF,"%x ",AnIntArray[i]);
			fprintf(OutputF,"<-\n");
			CloseIT();
		}  

	private:

		void OpenIT()
		{

			OutputF = fopen(mFName,"a");
			if (!OutputF)
			{
				exit(0);		// extremely ungraceful, isn't it!
			}
		}

		void CloseIT()
		{
			if (OutputF)
			{
				fclose(OutputF);
			}
		}

		void header(const char *SRCname,const int Line, const char * Name)
		{
			time_t 		SecsSince;
			struct tm	*LTimeStruc;

			SecsSince = time(NULL);
			LTimeStruc = localtime(&SecsSince);

			fprintf(	OutputF,
						"%s:%d/%d/%d %d:%d (%u)",
						SRCname,
						LTimeStruc->tm_mon,
						LTimeStruc->tm_mday,
						LTimeStruc->tm_year,
						LTimeStruc->tm_hour,
						LTimeStruc->tm_min,
						Line);
			fprintf(	OutputF,
						"'%s'->",
						Name);
		}
		FILE 		*OutputF;
		char		*mFName;


};

#endif DebugOut_H
