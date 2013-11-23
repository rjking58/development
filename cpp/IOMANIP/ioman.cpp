#include <iostream.h>
#include <iomanip.h>
#include <strstrea.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // may be diff for TSER..

int figurePrecision(double d);
void PreciseDblToString(double val,char *strDbl);
void pValue(double val,int precision);


void main(void)
{
	double aDbl = 10000000.0;
#if 0
	cout << setiosflags(ios::fixed);

	cout << setprecision(0) << aDbl << endl;
	// set up for fixed precision so that 
	// 'setprecision' is interpreted the as 'number of
	// decimal numbers'	

	// one number to right of the decimal point
	cout << setprecision(1) << "setprecision(1)" << endl;

   // test it to make sure!
	cout << 1.001 << " " << 1.01 << " " << 1.1 << endl;


	cout	<< setiosflags(ios::right | ios::fixed)
         << "setiosflags(ios::right | ios::fixed)" << endl
			<< setprecision(0)
         << "setprecision(0)" << endl
			<< 1.0
			<< endl;

	cout	<< setiosflags(ios::right | ios::fixed)
         << "setiosflags(ios::right | ios::fixed)" << endl
			<< setprecision(0)
         << "setprecision(0)" << endl
			<< setfill('0') << setw(6)
			<< "setfill('0') << setw(6)" << endl
			<< 100000.0
			<< endl;

	cout	<< setiosflags(ios::right | ios::fixed)
         << "setiosflags(ios::right | ios::fixed)" << endl
			<< setprecision(0)
         << "setprecision(0)" << endl
			<< setfill('0') << setw(6)
			<< "setfill('0') << setw(6)" << endl
			<< 1000000.0
			<< endl;

	cout	<< setiosflags(ios::right | ios::fixed)
         << "setiosflags(ios::right | ios::fixed)" << endl
			<< setprecision(0)
         << "setprecision(0)" << endl
			<< setfill('0') << setw(6)
			<< "setfill('0') << setw(6)" << endl
			<< 1000000000000.0
			<< endl;

	cout	<< setiosflags(ios::right | ios::fixed)
         << "setiosflags(ios::right | ios::fixed)" << endl
			<< setprecision(0)
         << "setprecision(0)" << endl
			<< setfill('0') << setw(6)
			<< "setfill('0') << setw(6)" << endl
			<< 99999999999999.0
			<< endl;

	cout	<< setiosflags(ios::right | ios::fixed)
         << "setiosflags(ios::right | ios::fixed)" << endl
			<< setprecision(0)
         << "setprecision(0)" << endl
			<< 1.0
			<< endl;

	cout	<< setiosflags(ios::right | ios::fixed)
         << "setiosflags(ios::right | ios::fixed)" << endl
			<< setprecision(0)
         << "setprecision(0)" << endl
			<< 10.0
			<< endl;


	cout	<< setiosflags(ios::right | ios::fixed)
         << "setiosflags(ios::right | ios::fixed)" << endl
			<< setprecision(0)
         << "setprecision(0)" << endl
			<< 99999999999999.0
			<< endl;

	// one number to right of the decimal point
//	cout << setprecision(14) << "setprecision(15)" << endl;
   cout << setw(15) << "setw(15)" << endl;
   cout  << setiosflags(ios::fixed | ios::right) 
         << "setiosflags(ios::fixed | ios::right)" << endl;

   // test it to make sure!
	cout  << 1.00000000000001 << endl
         << 1.0000000000001 << endl
         << 1.000000000001 << endl
         << 1.00000000001 << endl
         << 1.0000000001 << endl
         << 1.000000001 << endl
         << 1.00000001 << endl
         << 1.0000001 << endl
         << 1.000001 << endl
         << 1.00001 << endl
         << 1.0001 << endl
         << 1.001 << endl
         << 1.01 << endl 
         << 1.1 << endl
         << 10.000000000001 << endl
         << 10.00000000001 << endl
         << 10.0000000001 << endl
         << 10.000000001 << endl
         << 10.00000001 << endl
         << 10.0000001 << endl
         << 10.000001 << endl
         << 10.00001 << endl
         << 10.0001 << endl
         << 10.001 << endl
         << 10.01 << endl
         << 10.1 << endl 
         << 100.00000000001 << endl
         << 100.0000000001 << endl
         << 100.000000001 << endl
         << 100.00000001 << endl
         << 100.0000001 << endl
         << 100.000001 << endl
         << 100.00001 << endl
         << 100.0001 << endl
         << 100.001 << endl
         << 100.01 << endl
         << 100.1 << endl ;

   cout << (  log10(0.00001               ) ) << endl;
   cout << (  log10(0.000099999999999999  ) ) << endl;
   cout << (  log10(0.0001                ) ) << endl;
   cout << (  log10(0.00099999999999999   ) ) << endl;
   cout << (  log10(0.001                 ) ) << endl;
   cout << (  log10(0.0099999999999999    ) ) << endl;
   cout << (  log10(0.01                  ) ) << endl;
   cout << (  log10(0.099999999999999     ) ) << endl;
   cout << (  log10(0.1                   ) ) << endl;
   cout << (  log10(0.99999999999999      ) ) << endl;
   cout << (  log10(9.9999999999999       ) ) << endl;
   cout << (  log10(10.000000000000       ) ) << endl;
   cout << (  log10(99.999999999999       ) ) << endl;
   cout << (  log10(100.00000000000       ) ) << endl;
   cout << (  log10(999.99999999999       ) ) << endl;
   cout << (  log10(1000.0000000000       ) ) << endl;
   cout << (  log10(9999.9999999999       ) ) << endl;
   cout << (  log10(10000.000000000       ) ) << endl;
   cout << (  log10(99999.999999999       ) ) << endl;
   cout << (  log10(1000000.0000000       ) ) << endl;
   cout << (  log10(9999999.9999999       ) ) << endl;
   cout << (  log10(10000000.000000       ) ) << endl;
   cout << (  log10(99999999.999999       ) ) << endl;
   cout << (  log10(100000000.00000       ) ) << endl;
   cout << (  log10(999999999.99999       ) ) << endl;
   cout << (  log10(1000000000.0000       ) ) << endl;
   cout << (  log10(9999999999.9999       ) ) << endl;
   cout << figurePrecision(0.00001                                        ) << " 0.00001             " << endl;
   cout << figurePrecision(0.000010000000000001                           ) << " 0.000010000000000001" << endl;
   cout << figurePrecision(0.000099999999999999                           ) << " 0.000099999999999999" << endl;
   cout << figurePrecision(0.0001                                         ) << " 0.0001              " << endl;
   cout << figurePrecision(0.00099999999999999                            ) << " 0.00099999999999999 " << endl;
   cout << figurePrecision(0.001                                          ) << " 0.001               " << endl;
   cout << figurePrecision(0.0099999999999999                             ) << " 0.0099999999999999  " << endl;
   cout << figurePrecision(0.01                                           ) << " 0.01                " << endl;
   cout << figurePrecision(0.099999999999999                              ) << " 0.099999999999999   " << endl;
   cout << figurePrecision(0.1                                            ) << " 0.1                 " << endl;
   cout << figurePrecision(0.99999999999999                               ) << "  0.99999999999999   " <<  endl;
   cout << figurePrecision(9.9999999999999                                ) << " 9.9999999999999     " << endl;
   cout << figurePrecision(10.000000000000                                ) << " 10.000000000000     " << endl;
   cout << figurePrecision(99.999999999999                                ) << " 99.999999999999     " << endl;
   cout << figurePrecision(100.00000000000                                ) << " 100.00000000000     " << endl;
   cout << figurePrecision(999.99999999999                                ) << " 999.99999999999     " << endl;
   cout << figurePrecision(1000.0000000000                                ) << " 1000.0000000000     " << endl;
   cout << figurePrecision(9999.9999999999                                ) << " 9999.9999999999     " << endl;
   cout << figurePrecision(10000.000000000                                ) << " 10000.000000000     " << endl;
   cout << figurePrecision(99999.999999999                                ) << " 99999.999999999     " << endl;
   cout << figurePrecision(1000000.0000000                                ) << " 1000000.0000000     " << endl;
   cout << figurePrecision(9999999.9999999                                ) << " 9999999.9999999     " << endl;
   cout << figurePrecision(10000000.000000                                ) << " 10000000.000000     " << endl;
   cout << figurePrecision(99999999.999999                                ) << " 99999999.999999     " << endl;
   cout << figurePrecision(100000000.00000                                ) << " 100000000.00000     " << endl;
   cout << figurePrecision(999999999.99999                                ) << " 999999999.99999     " << endl;
   cout << figurePrecision(1000000000.0000                                ) << " 1000000000.0000     " << endl;
   cout << figurePrecision(9999999999.9999                                ) << " 9999999999.9999     " << endl;
   char  ds[40];  
   
         pValue(      0.0000000001,                   
      figurePrecision(0.0000000001              ));
         printf("     0.0000000001 \n");
PreciseDblToString(   0.0000000001,ds);
printf("     %s\n",ds);
         pValue(      0.00000000010000000000001,      
      figurePrecision(0.00000000010000000000001));
         printf("     0.00000000010000000000001\n");
PreciseDblToString(   0.00000000010000000000001,ds);
printf("     %s\n",ds);
         pValue(      0.00000000099999999999999,      
      figurePrecision(0.00000000099999999999999));
         printf("     0.00000000099999999999999\n");
PreciseDblToString(   0.00000000099999999999999,ds);
printf("     %s\n",ds);
         pValue(      0.000000001,                    
      figurePrecision(0.000000001              ));
         printf("     0.000000001\n");
PreciseDblToString(   0.000000001,ds);
printf("     %s\n",ds);
         pValue(      0.0000000010000000000001,       
      figurePrecision(0.0000000010000000000001));
         printf("     0.0000000010000000000001\n");
PreciseDblToString(   0.0000000010000000000001,ds);
printf("     %s\n",ds);
         pValue(      0.0000000099999999999999,       
      figurePrecision(0.0000000099999999999999));
         printf("     0.0000000099999999999999\n");
PreciseDblToString(   0.0000000099999999999999,ds);
printf("     %s\n",ds);
         pValue(      0.00000001,                     
      figurePrecision(0.00000001              ));
         printf("     0.00000001\n");
PreciseDblToString(   0.00000001,ds);
printf("     %s\n",ds);
         pValue(      0.000000010000000000001,        
      figurePrecision(0.000000010000000000001));
         printf("     0.000000010000000000001\n");
PreciseDblToString(   0.000000010000000000001,ds);
printf("     %s\n",ds);
         pValue(      0.000000099999999999999,        
      figurePrecision(0.000000099999999999999));
         printf("     0.000000099999999999999\n");
PreciseDblToString(   0.000000099999999999999,ds);
printf("     %s\n",ds);
         pValue(      0.0000001,                      
      figurePrecision(0.0000001              ));
         printf("     0.0000001\n");
PreciseDblToString(   0.0000001,ds);
printf("     %s\n",ds);
         pValue(      0.00000010000000000001,         
      figurePrecision(0.00000010000000000001));
         printf("     0.00000010000000000001\n");
PreciseDblToString(   0.00000010000000000001,ds);
printf("     %s\n",ds);
         pValue(      0.00000099999999999999,         
      figurePrecision(0.00000099999999999999));
         printf("     0.00000099999999999999\n");
PreciseDblToString(   0.00000099999999999999,ds);
printf("     %s\n",ds);
         pValue(      0.000001,                       
      figurePrecision(0.000001              ));
         printf("     0.000001\n");
PreciseDblToString(   0.000001,ds);
printf("     %s\n",ds);
         pValue(      0.0000010000000000001,          
      figurePrecision(0.0000010000000000001));
         printf("     0.0000010000000000001\n");
PreciseDblToString(   0.0000010000000000001,ds);
printf("     %s\n",ds);
         pValue(      0.0000099999999999999,          
      figurePrecision(0.0000099999999999999));
         printf("     0.0000099999999999999\n");
PreciseDblToString(   0.0000099999999999999,ds);
printf("     %s\n",ds);
         pValue(      0.00001,                        
      figurePrecision(0.00001              ));
         printf("     0.00001\n");
PreciseDblToString(   0.00001,ds);
printf("     %s\n",ds);
         pValue(      0.000010000000000001,           
      figurePrecision(0.000010000000000001));
         printf("     0.000010000000000001\n");
PreciseDblToString(   0.000010000000000001,ds);
printf("     %s\n",ds);
         pValue(      0.000099999999999999,           
      figurePrecision(0.000099999999999999));
         printf("     0.000099999999999999\n");
PreciseDblToString(   0.000099999999999999,ds);
printf("     %s\n",ds);
         pValue(      0.0001              ,           
      figurePrecision(0.0001              ));
         printf("     0.0001\n");
PreciseDblToString(   0.0001              ,ds);
printf("     %s\n",ds);
         pValue(      0.00010000000000001,           
      figurePrecision(0.00010000000000001              ));
         printf("     0.00010000000000001\n");
PreciseDblToString(   0.00010000000000001,ds);
printf("     %s\n",ds);
         pValue(      0.00099999999999999 ,           
      figurePrecision(0.00099999999999999 ));
         printf("     0.00099999999999999\n");
PreciseDblToString(   0.00099999999999999 ,ds);
printf("     %s\n",ds);
         pValue(      0.001               ,           
      figurePrecision(0.001               ));
         printf("     0.001\n");
PreciseDblToString(   0.001               ,ds);
printf("     %s\n",ds);
         pValue(      0.0010000000000001               ,           
      figurePrecision(0.0010000000000001               ));
         printf("     0.0010000000000001\n");
PreciseDblToString(   0.0010000000000001               ,ds);
printf("     %s\n",ds);
         pValue(      0.0099999999999999  ,           
      figurePrecision(0.0099999999999999  ));
         printf("     0.0099999999999999\n");
PreciseDblToString(   0.0099999999999999  ,ds);
printf("     %s\n",ds);
         pValue(      0.01                ,           
      figurePrecision(0.01                ));
         printf("     0.01\n");
PreciseDblToString(   0.01                ,ds);
printf("     %s\n",ds);
         pValue(      0.010000000000001                ,           
      figurePrecision(0.010000000000001                ));
         printf("     0.010000000000001\n");
PreciseDblToString(   0.010000000000001                ,ds);
printf("     %s\n",ds);
         pValue(      0.099999999999999   ,           
      figurePrecision(0.099999999999999   ));
         printf("     0.099999999999999\n");
PreciseDblToString(   0.099999999999999   ,ds);
printf("     %s\n",ds);
         pValue(      0.1                 ,           
      figurePrecision(0.1                 ));
         printf("     0.1\n");
PreciseDblToString(   0.1                 ,ds);
printf("     %s\n",ds);
         pValue(      0.10000000000001                 ,           
      figurePrecision(0.10000000000001                 ));
         printf("     0.10000000000001\n");
PreciseDblToString(   0.10000000000001                 ,ds);
printf("     %s\n",ds);
         pValue(      0.99999999999999    ,           
      figurePrecision(0.99999999999999    ));
         printf("     0.99999999999999\n");
PreciseDblToString(   0.99999999999999    ,ds);
printf("     %s\n",ds);
         pValue(      1.0     ,           
      figurePrecision(1.0     ));
         printf("     1.0\n");
PreciseDblToString(   1.0     ,ds);
printf("     %s\n",ds);
         pValue(      1.0000000000001     ,           
      figurePrecision(1.0000000000001     ));
         printf("     1.0000000000001\n");
PreciseDblToString(   1.0000000000001     ,ds);
printf("     %s\n",ds);
         pValue(      9.9999999999999     ,           
      figurePrecision(9.9999999999999     ));
         printf("     9.9999999999999\n");
PreciseDblToString(   9.9999999999999     ,ds);
printf("     %s\n",ds);
         pValue(      10.000000000000     ,           
      figurePrecision(10.000000000000     ));
         printf("     10.000000000000\n");
PreciseDblToString(   10.000000000000     ,ds);
printf("     %s\n",ds);
         pValue(      10.000000000001     ,           
      figurePrecision(10.000000000001     ));
         printf("     10.000000000001\n");
PreciseDblToString(   10.000000000001     ,ds);
printf("     %s\n",ds);
         pValue(      99.999999999999     ,           
      figurePrecision(99.999999999999     ));
         printf("     99.999999999999\n");
PreciseDblToString(   99.999999999999     ,ds);
printf("     %s\n",ds);
         pValue(      100.00000000000     ,           
      figurePrecision(100.00000000000     ));
         printf("     100.00000000000\n");
PreciseDblToString(   100.00000000000     ,ds);
printf("     %s\n",ds);
         pValue(      100.00000000001     ,           
      figurePrecision(100.00000000001     ));
         printf("     100.00000000001\n");
PreciseDblToString(   100.00000000001     ,ds);
printf("     %s\n",ds);
         pValue(      999.99999999999     ,           
      figurePrecision(999.99999999999     ));
         printf("     999.99999999999\n");
PreciseDblToString(   999.99999999999     ,ds);
printf("     %s\n",ds);
         pValue(      1000.0000000000     ,           
      figurePrecision(1000.0000000000     ));
         printf("     1000.0000000000\n");
PreciseDblToString(   1000.0000000000     ,ds);
printf("     %s\n",ds);
         pValue(      1000.0000000001     ,           
      figurePrecision(1000.0000000001     ));
         printf("     1000.0000000001\n");
PreciseDblToString(   1000.0000000001     ,ds);
printf("     %s\n",ds);
         pValue(      9999.9999999999     ,           
      figurePrecision(9999.9999999999     ));
         printf("     9999.9999999999\n");
PreciseDblToString(   9999.9999999999     ,ds);
printf("     %s\n",ds);
         pValue(      10000.000000000     ,           
      figurePrecision(10000.000000000     ));
          printf("    10000.000000000\n");
PreciseDblToString(   10000.000000000     ,ds);
printf("    %s\n",ds);
         pValue(      10000.000000001     ,           
      figurePrecision(10000.000000001     ));
          printf("    10000.000000001\n");
PreciseDblToString(   10000.000000001     ,ds);
printf("    %s\n",ds);
         pValue(      99999.999999999     ,           
      figurePrecision(99999.999999999     ));
          printf("    99999.999999999\n");
PreciseDblToString(   99999.999999999     ,ds);
printf("    %s\n",ds);
         pValue(      100000.00000000     ,           
      figurePrecision(100000.00000000     ));
          printf("    100000.00000000\n");
PreciseDblToString(   100000.00000000     ,ds);
printf("    %s\n",ds);
         pValue(      100000.00000001     ,           
      figurePrecision(100000.00000001     ));
          printf("    100000.00000001\n");
PreciseDblToString(   100000.00000001     ,ds);
printf("    %s\n",ds);
         pValue(      999999.99999999     ,           
      figurePrecision(999999.99999999     ));
          printf("    999999.99999999\n");
PreciseDblToString(   999999.99999999     ,ds);
printf("    %s\n",ds);
          pValue(     1000000.0000000     ,            
      figurePrecision(1000000.0000000     ));
          printf("    1000000.0000000\n");
PreciseDblToString(   1000000.0000000     ,ds);
printf("    %s\n",ds);
          pValue(     1000000.0000001     ,            
      figurePrecision(1000000.0000001     ));
          printf("    1000000.0000001\n");
PreciseDblToString(   1000000.0000001     ,ds);
printf("    %s\n",ds);
          pValue(     9999999.9999999     ,            
      figurePrecision(9999999.9999999     ));
          printf("    9999999.9999999\n");
PreciseDblToString(   9999999.9999999     ,ds);
printf("    %s\n",ds);
          pValue(     10000000.000000     ,            
      figurePrecision(10000000.000000     ));
          printf("    10000000.000000\n");
PreciseDblToString(   10000000.000000     ,ds);
printf("    %s\n",ds);
          pValue(     10000000.000001     ,            
      figurePrecision(10000000.000001     ));
          printf("    10000000.000001\n");
PreciseDblToString(   10000000.000001     ,ds);
printf("    %s\n",ds);
          pValue(     99999999.999999     ,            
      figurePrecision(99999999.999999     ));
          printf("    99999999.999999\n");
PreciseDblToString(   99999999.999999     ,ds);
printf("    %s\n",ds);
          pValue(     100000000.00000     ,            
      figurePrecision(100000000.00000     ));
          printf("    100000000.00000\n");
PreciseDblToString(   100000000.00000     ,ds);
printf("    %s\n",ds);
          pValue(     100000000.00001     ,            
      figurePrecision(100000000.00001     ));
          printf("    100000000.00001\n");
PreciseDblToString(   100000000.00001     ,ds);
printf("    %s\n",ds);
          pValue(     999999999.99999     ,            
      figurePrecision(999999999.99999     ));
          printf("    999999999.99999\n");
PreciseDblToString(   999999999.99999     ,ds);
printf("    %s\n",ds);
          pValue(     1000000000.0000     ,            
      figurePrecision(1000000000.0000     ));
          printf("    1000000000.0000\n");
PreciseDblToString(   1000000000.0000     ,ds);
printf("    %s\n",ds);
          pValue(     1000000000.0001     ,            
      figurePrecision(1000000000.0001     ));
          printf("    1000000000.0001\n");
PreciseDblToString(   1000000000.0001     ,ds);
printf("    %s\n",ds);
          pValue(     9999999999.9999     ,            
      figurePrecision(9999999999.9999     ));
          printf("    9999999999.9999\n");
PreciseDblToString(   9999999999.9999     ,ds);
printf("    %s\n",ds);
          pValue(     10000000000.000     ,            
      figurePrecision(10000000000.000     ));
          printf("    10000000000.000\n");
PreciseDblToString(   10000000000.000     ,ds);
printf("    %s\n",ds);
          pValue(     10000000000.001     ,            
      figurePrecision(10000000000.001     ));
          printf("    10000000000.001\n");
PreciseDblToString(   10000000000.001     ,ds);
printf("    %s\n",ds);
          pValue(     99999999999.999     ,            
      figurePrecision(99999999999.999     ));
          printf("    99999999999.999\n");
PreciseDblToString(   99999999999.999     ,ds);
printf("    %s\n",ds);
          pValue(     100000000000.00     ,            
      figurePrecision(100000000000.00     ));
          printf("    100000000000.00\n");
PreciseDblToString(   100000000000.00     ,ds);
printf("    %s\n",ds);
          pValue(     100000000000.01     ,            
      figurePrecision(100000000000.01     ));
          printf("    100000000000.01\n");
PreciseDblToString(   100000000000.01     ,ds);
printf("    %s\n",ds);
          pValue(     999999999999.99     ,            
      figurePrecision(999999999999.99     ));
          printf("    999999999999.99\n");
PreciseDblToString(   999999999999.99     ,ds);
printf("    %s\n",ds);
          pValue(     1000000000000.0     ,            
      figurePrecision(1000000000000.0     ));
          printf("    1000000000000.0\n");
PreciseDblToString(   1000000000000.0     ,ds);
printf("    %s\n",ds);
          pValue(     1000000000000.1     ,            
      figurePrecision(1000000000000.1     ));
          printf("    1000000000000.1\n");
PreciseDblToString(   1000000000000.1     ,ds);
printf("    %s\n",ds);
          pValue(     9999999999999.9     ,            
      figurePrecision(9999999999999.9     ));
          printf("    9999999999999.9\n");
PreciseDblToString(   9999999999999.9     ,ds);
printf("    %s\n",ds);
          pValue(     10000000000000.0     ,            
      figurePrecision(10000000000000.0     ));
          printf("    10000000000000.0\n");
PreciseDblToString(   10000000000000.0     ,ds);
printf("    %s\n",ds);
          pValue(     10000000000001.0     ,            
      figurePrecision(10000000000001.0     ));
          printf("    10000000000001.0\n");
PreciseDblToString(   10000000000001.0     ,ds);
printf("    %s\n",ds);
          pValue(     99999999999999.0     ,           
      figurePrecision(99999999999999.0     ));
          printf("    99999999999999.0\n");
PreciseDblToString(   99999999999999.0     ,ds);
printf("    %s\n",ds);
          pValue(     100000000000000.0     ,            
      figurePrecision(100000000000000.0     ));
          printf("    100000000000000.0\n");
PreciseDblToString(   100000000000000.0     ,ds);
printf("    %s\n",ds);
          pValue(     100000000000010.0     ,            
      figurePrecision(100000000000010.0     ));
          printf("    100000000000010.0\n");
PreciseDblToString(   100000000000010.0     ,ds);
printf("    %s\n",ds);
          pValue(     999999999999990.0     ,          
      figurePrecision(999999999999990.0     ));
          printf("    999999999999990.0\n");
PreciseDblToString(   999999999999990.0     ,ds);
printf("    %s\n",ds);
          pValue(     1000000000000000.0     ,            
      figurePrecision(1000000000000000.0     ));
          printf("    1000000000000000.0\n");
PreciseDblToString(   1000000000000000.0     ,ds);
printf("    %s\n",ds);
          pValue(     1000000000000100.0     ,            
      figurePrecision(1000000000000100.0     ));
          printf("    1000000000000100.0\n");
PreciseDblToString(   1000000000000100.0     ,ds);
printf("    %s\n",ds);
          pValue(     9999999999999900.0     ,         
      figurePrecision(9999999999999900.0     ));
          printf("    9999999999999900.0\n");
PreciseDblToString(   9999999999999900.0     ,ds);
printf("    %s\n",ds);
          pValue(     10000000000000000.0     ,            
      figurePrecision(10000000000000000.0     ));
          printf("    10000000000000000.0\n");
PreciseDblToString(   10000000000000000.0     ,ds);
printf("    %s\n",ds);
          pValue(     10000000000001000.0     ,            
      figurePrecision(10000000000001000.0     ));
          printf("    10000000000001000.0\n");
PreciseDblToString(   10000000000001000.0     ,ds);
printf("    %s\n",ds);
          pValue(     99999999999999000.0     ,        
      figurePrecision(99999999999999000.0     ));
          printf("    99999999999999000.0\n");
PreciseDblToString(   99999999999999000.0     ,ds);
printf("    %s\n",ds);

// interesting cases..

          pValue(     0.01020300     ,        
      figurePrecision(0.01020300     ));
         printf("     0.01020300\n");
PreciseDblToString(   0.01020300     ,ds);
printf("     %s\n",ds);
          pValue(     0.0102030     ,        
      figurePrecision(0.0102030     ));
         printf("     0.0102030\n");
PreciseDblToString(   0.0102030     ,ds);
printf("     %s\n",ds);
          pValue(     0.010203     ,        
      figurePrecision(0.010203     ));
         printf("     0.010203\n");
PreciseDblToString(   0.010203     ,ds);
printf("     %s\n",ds);
          pValue(     0.0100     ,        
      figurePrecision(0.0100     ));
         printf("     0.0100\n");
PreciseDblToString(   0.0100     ,ds);
printf("     %s\n",ds);
          pValue(     0.010     ,        
      figurePrecision(0.010     ));
         printf("     0.010\n");
PreciseDblToString(   0.010     ,ds);
printf("     %s\n",ds);
          pValue(     0.01     ,        
      figurePrecision(0.01     ));
         printf("     0.01\n");
PreciseDblToString(   0.01     ,ds);
printf("     %s\n",ds);
          pValue(     0.1100     ,        
      figurePrecision(0.1100     ));
         printf("     0.1100\n");
PreciseDblToString(   0.1100     ,ds);
printf("     %s\n",ds);
          pValue(     0.110     ,        
      figurePrecision(0.110     ));
         printf("     0.110\n");
PreciseDblToString(   0.110     ,ds);
printf("     %s\n",ds);
          pValue(     0.11     ,        
      figurePrecision(0.11     ));
         printf("     0.11\n");
PreciseDblToString(   0.11     ,ds);
printf("     %s\n",ds);
          pValue(     0.100     ,        
      figurePrecision(0.100     ));
         printf("     0.100\n");
PreciseDblToString(   0.100     ,ds);
printf("     %s\n",ds);
          pValue(     0.10     ,        
      figurePrecision(0.10     ));
         printf("     0.10\n");
PreciseDblToString(   0.10     ,ds);
printf("     %s\n",ds);
          pValue(     0.1     ,        
      figurePrecision(0.1     ));
         printf("     0.1\n");
PreciseDblToString(   0.1     ,ds);
printf("     %s\n",ds);

#endif
#if 0
	for (int w = 1; w<7 ; w++)
		for (double d = 1.0; d < 1.2; d+= 0.1)
		{
			cout	<< "setiosflags(ios::right)"<< setiosflags(ios::right)
					<< "setfill('0')"<< setfill('0') 
					<< "setw(" << w << ")" << setw(w)
					<< d << " ";

			cout	<< "new cout with just double->" << d << endl;
		}
	for (int i = 1; i <= 120; i++)
	{
		ostrstream strm;
		strm  << "BUCKET_"
				<< setiosflags(ios::right) 
				<< setfill('0')            
				<< setw(3)                 
				<< i
				<< ends;
		cout	<< strm.str() << " ";

// 		strm.flush();

		if (! (i % 5))
		{
			cout << endl;
		}
	}
#endif

   for(int x = 1; x < 200; x++)
   {
      cout << " " << x;
   }
  

}

struct PrecisionRelator
{
   double   MinDbl;     // if comparison is not >= to this number then
   int      Precision;  // its this precision..
} precisionRelator[] = {  // if we need to detect smaller... boy
                        // are we in trouble..  ;)  rjk
                         {0.000000000000001,29}
                        ,{0.00000000000001, 28}
                        ,{0.0000000000001,  27}
                        ,{0.000000000001,   26}
                        ,{0.00000000001,    25}
                        ,{0.0000000001,     24}
                        ,{0.000000001,      23}
                        ,{0.00000001,       22}
                        ,{0.0000001,        21}
                        ,{0.000001,         20}
                        ,{0.00001,          19}
                        ,{0.0001,           18}
                        ,{0.001,            17}
                        ,{0.01,             16}
                        ,{0.1,              15}
                        ,{1.0,              14}
                        ,{10.0,             13}
                        ,{100.0,            12}
                        ,{1000.0,           11}
                        ,{10000.0,          10}
                        ,{100000.0,          9}
                        ,{1000000.0,         8}
                        ,{10000000.0,        7}
                        ,{100000000.0,       6}
                        ,{1000000000.0,      5}
                        ,{10000000000.0,     4}
                        ,{100000000000.0,    3}
                        ,{1000000000000.0,   2}
                        ,{10000000000000.0,  1}   
                        ,{100000000000000.0, 0}   // end of table
                     };


double portableLog10(double d)
{
   return (log(d)/log(10.0));
}

int figurePrecision(double d)
{
   int   currRelator = 0;

   while (     precisionRelator[currRelator].Precision != 0
          &&   d >= precisionRelator[currRelator].MinDbl    )
   {
      currRelator++;
   }
   return precisionRelator[currRelator].Precision;
}


int figurePrecisionOldAndBad(double d)
{
   double   logOfd = portableLog10(d);
   // maximum precision...
   int      startPrecis = 14;

   if (logOfd < 0.0)
   {
      // this is fractional
      startPrecis += abs((int) logOfd);
   }
   else
   {
      // this is non-fractional and OK.
      startPrecis -= ((int) logOfd) + 1;
   }
   // find boundary case for fractional
   if (startPrecis < 0)
   {
      startPrecis = 0;
   }
   return startPrecis;
}

void PreciseDblToString(double val,char *strDbl)
{
   char FmtSpecifier[200];
   char *strDbl_p;
   // get the number at maximum needed precision
   sprintf(FmtSpecifier,"%%.%uf",figurePrecision(val));
   sprintf(strDbl,FmtSpecifier,val);

   // do we have a period??
   strDbl_p = strDbl;
   while(      *strDbl_p
            && *strDbl_p != '.' )
   {
      strDbl_p++;
   }

   // if we have a decimal point, strip all but one zero off tail end..
   // since this code following is a bit cryptic, here it the
   // boolean analysis.. note that strDbl_p always points
   // to the end of the string.
   // also remember.. since sprintf is generating this we will always
   // have at least one number after the decimal point, or no decimal
   // point, so the case where strDbl_p is pointing to a decimal point
   // does not have to be handled!
   // analysis legend:
   //       x is non-zero number
   //       D is a don't care number
   //       0 is zero (of course!)
   //       . is the decimal point!
   //       T is true
   //       F is false
   //       a true in both columns means: strip zero and strDbl_p--
   //       any other condition means 'stop now, we are done!'
   //                            analysis
   //                            --------
   //       *(strDbl_p) == 0    *(strDbl_p - 1) != '.'
   // D.0         T                      F              ANDed: F <**stop**>
   // D.00        T                      T              ANDed: T <STRIP>
   // D.x         F                      F              ANDed: F <**stop**>
   // D.x0        T                      T              ANDed: T <STRIP>
   // D.x00       T                      T              ANDed: T <STRIP>
   // D.Dx        F                      T              ANDed: F <**stop**>
   // D.Dx0       T                      T              ANDed: T <STRIP>
   // D.Dx00      T                      T              ANDed: T <STRIP>
   if (*strDbl_p) // i.e. not null.. we found a decimal point..
   {
      strDbl_p = (strDbl + strlen(strDbl)) - 1;
      while(   *(strDbl_p)       == '0'
            && *(strDbl_p - 1)   != '.'   )
      {
         *strDbl_p = 0;
         strDbl_p--;
      }
   }
   
}

void pValue(double val,int precision)
{
   char FmtSpecifier[200];

   sprintf(FmtSpecifier,"(%u) %%.%uf\n",precision,precision);
   printf(FmtSpecifier,val);
}

