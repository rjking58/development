// this if fragments only... they ran when in a main(), but are only
// fragments here...


// tangent oriented data
#define TAN_LOCS 89
struct tangents
   {
   int angle;
   double tangent;
   double next_tangent;
   };
   
struct tangents tan_table[TAN_LOCS];

int find_tangent( double target,
                  struct tangents tan_table[TAN_LOCS]);        
                  
   // setup tangent table
   for (angle=0;angle<TAN_LOCS;angle++)
      {
      // note that this loop accesses the structure as 0 offset
      // even though the angles are based on 1 to 89!
      tan_table[angle].angle = angle + 1;
      tan_table[angle].tangent = tan( ((double)(angle + 1)) / 57.29578);
      tan_table[angle].next_tangent = -1.0;
      if (angle>0)
         {
         tan_table[angle-1].next_tangent= tan_table[angle].tangent;
         }
      }
// test code only!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!      
//   for (angle=0;angle<TAN_LOCS;angle++)
//      {
//      printf("|tan(%d) %lf %lf",
//             tan_table[angle].angle,
//             tan_table[angle].tangent,
//             tan_table[angle].next_tangent) ;
//      }  
//   while(!kbhit()); 
//   for (x=0;x<8900;x++)
//      {
//      if (    ( x != 0        )
//           && ( (x % 20) == 0 )
//         )
//         {
//         while(!kbhit());
//         }   
//      angle = find_tangent( testval,
//                            tan_table);
//
//      printf("%d --> %lf %lf %lf\n",
//             angle,
//             testval,
//             tan_table[angle-1].tangent,
//             tan_table[angle-1].next_tangent);
//      testval+= .01 ;    
//      }
//   exit(0);
// test code only!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!      




//*********************************************************
// find the angle for a given tangent...
//*********************************************************

int find_tangent( double target,
                  struct tangents tan_table[TAN_LOCS])
   {
   int test_loc,
       done,
       increment;

   // binary search tangent table for target tangent
   increment = TAN_LOCS / 2;
   test_loc = increment;
   done = FALSE;
   while(!done)
      {
      if (   (target < tan_table[test_loc].tangent             )
          && (tan_table[test_loc].angle == 1                   ) 
         )
         {
         // angle is less than tangent for 1 degree... show as 1 degree
         done = TRUE;
         }       
      else if(   (target >= tan_table[test_loc].tangent            )
              && (  (target <  tan_table[test_loc].next_tangent)
                  ||(tan_table[test_loc].next_tangent == -1.0  )   )
             )
         {
         // it either matches or is above 89 degree tangent.. show as such
         done = TRUE;
         }
      else
         {
         // next...
         increment /= 2;
         if (increment < 1)
            increment = 1;
         if (target < tan_table[test_loc].tangent)
            {
            test_loc -= increment;
            }
         else
            {
            test_loc += increment;
            }                     
         }
      }
   return(tan_table[test_loc].angle);   
   }   
