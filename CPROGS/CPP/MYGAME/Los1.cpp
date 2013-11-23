#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <ctype.h>
//#include <memory.h>
#include <math.h>

//#define NDEBUG /* to turn off asserts */
#include <assert.h>

// goodies
#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

// distance table...
#define X_SIZE 100
#define Y_SIZE 100

int xy_dist[X_SIZE][Y_SIZE];
void init_distance_table(void);



// map oriented data
enum Map_Obj_type {   VWALL=1
                     ,HWALL
                     ,BWALL
                     ,TREE
                     ,CLEAR
                     ,LOS_BLOCKED
                     ,PERSON
                  };   
#define MAP_VSIZE 8
#define MAP_HSIZE 8      


void Show_Map(Map_Obj_type map_obj[MAP_HSIZE][MAP_VSIZE]);
void Show_LOS_Map(Map_Obj_type map_obj[MAP_HSIZE][MAP_VSIZE]);

Map_Obj_type map[MAP_HSIZE][MAP_VSIZE];
Map_Obj_type LOS_map[MAP_HSIZE][MAP_VSIZE];

int in_LOS( int x1, 
            int y1,
            int x2,
            int y2,
            int x_delta,
            int y_delta  );


main()
   {
   int   x,y,done;
   int   person_x,person_y;
   int   delta_x,delta_y;
   char  cmnd;

   init_distance_table();
   
   for(y=0;y<MAP_VSIZE;y++)
      for (x=0;x<MAP_HSIZE;x++)
         {
         map[x][y] = CLEAR;
         LOS_map[x][y] = CLEAR;
         }
   map    [2][2] = VWALL;
   LOS_map[2][2] = VWALL;
   map    [2][3] = VWALL;
   LOS_map[2][3] = VWALL;
   map    [2][4] = VWALL;
   LOS_map[2][4] = VWALL;
   map    [5][2] = HWALL;
   LOS_map[5][2] = HWALL;
   map    [6][2] = HWALL;
   LOS_map[6][2] = HWALL;
   map    [7][2] = HWALL;
   LOS_map[7][2] = HWALL;
   
   clrscr();
   Show_Map(map);
   
   // put object P
   // remove object R
   // help H
   // quit Q
   done = FALSE;
   while(!done)
      {   
      gotoxy(1,11);
      printf("Input command:");
      
      cmnd = getch();
//      scanf("%1c",&cmnd);
//      flushall();
      if (isalpha(cmnd))
         {
         cmnd = toupper(cmnd);
         switch(cmnd)
            {
            case 'H':
               {
               printf("\n");
               printf("D: display map    \n");
               printf("P: put object     \n");
               printf("R: remove object  \n");
               printf("H: help           \n");
               printf("L: do LOS calc    \n");
               printf("Q: quit           \n");
   
               break;
               }
            case 'P':
               {
               printf("input map ");
               break;
               }
            case 'R':
               {
               
               break;
               }
            case 'Q':
               {
               done = TRUE;
               break;
               }
            case 'L':
               {
//               printf("\ninput x,y of person");
//               scanf("%d %d",&person_x,&person_y);
//               flushall();
               for (person_x=0;person_x<MAP_HSIZE;person_x++)
                  for (person_y=0;person_y<MAP_VSIZE;person_y++)
                     {
                     if (map[person_x][person_y] == CLEAR)
                        {                     
                        while(!kbhit());
                        while(kbhit())
                           getch();

                        memcpy(LOS_map,
                               map, 
                               (sizeof (Map_Obj_type) * MAP_HSIZE * MAP_VSIZE));
                               
                        LOS_map[person_x][person_y]=PERSON;
                               
                        for(y=0;y<MAP_VSIZE;y++)
                           for (x=0;x<MAP_HSIZE;x++)
                              {
                              if (x > person_x)
                                 {
                                 delta_x = x - person_x;
                                 }
                              else
                                 {
                                 delta_x = person_x - x;
                                 }
                              if (y > person_y)
                                 {
                                 delta_y = y - person_y;
                                 }
                              else
                                 {
                                 delta_y = person_y - y;
                                 }
                              if ( ! (    (y==person_y) 
                                       && (x==person_x)  ) 
                                 )
                                 {
                                 
                                 if ( ! in_LOS( person_x, 
                                                person_y,
                                                x,
                                                y,
                                                delta_x,
                                                delta_y  )
                                    )
                                    {
                                    if (LOS_map[x][y] == CLEAR)
                                       {
                                       LOS_map[x][y] = LOS_BLOCKED;
                                       }
                                    }
                                 }   
                              }
                        gotoxy(1,1);
                        Show_LOS_Map(LOS_map);
                        }
                     }
               break;
               }
            case 'D':
               {
               clrscr();
               Show_Map(map);
               break;
               }
            default:
               break;   
            } // switch(command)
         }// if (isalpha(command))
      } // while(!done)
   } // main()

void Show_Map(Map_Obj_type map_obj[MAP_HSIZE][MAP_VSIZE])
   {
   int x,y;
   
   gotoxy(1,1);   
   for (x=0;x<MAP_HSIZE;x++)
      {
      printf("%d",x);
      }
   printf("\n");   
   
   for(y=0;y<MAP_VSIZE;y++)
      {
      printf("%d",y);
      for (x=0;x<MAP_HSIZE;x++)
         {
         switch(map_obj[x][y])
            {
            case VWALL:
            case HWALL:
            case BWALL:
               {
               printf("W");
               break;
               }
            case TREE :
               {
               printf("T");
               break;
               }
            case CLEAR:
               {
               printf(".");
               break;
               }
            } // switch(map_obj[x][y])
         } // for (x=0;x<MAP_HSIZE;x++)
      printf("\n");   
      } // for(y=0;y<MAP_VSIZE;y++)
   } // Show_Map()
   
void Show_LOS_Map(Map_Obj_type map_obj[MAP_HSIZE][MAP_VSIZE])
   {
   int x,y;
   
   gotoxy(1,1);   
   for (x=0;x<MAP_HSIZE;x++)
      {
      printf("%d",x);
      }
   printf("\n");   
   
   for(y=0;y<MAP_VSIZE;y++)
      {
      printf("%d",y);
      for (x=0;x<MAP_HSIZE;x++)
         {
         switch(map_obj[x][y])
            {
            case VWALL:
            case HWALL:
            case BWALL:
               {
               printf("W");
               break;
               }
            case TREE :
               {
               printf("T");
               break;
               }
            case CLEAR:
               {
               printf(".");
               break;
               }
            case LOS_BLOCKED:
               {
               printf("X");
               break;
               }   
            case PERSON:
               {
               printf("P");
               break;
               }   
            } // switch(map_obj[x][y])
         } // for (x=0;x<MAP_HSIZE;x++)
      printf("\n");   
      } // for(y=0;y<MAP_VSIZE;y++)
   } // Show_LOS_Map()

void init_distance_table(void)
   {
   int x,y;
   
   for (x=0;x<X_SIZE;x++)
      for(y = 0;y<Y_SIZE;y++)
         {
         if(x==0 && y==0)
            {
            xy_dist[x][y] = 0;
            }
         else if ( x == 0 || y == 0 )
            {
            xy_dist[x][y] = x+y;
            }
         else
            {
            xy_dist[x][y] = (unsigned int) sqrt( (double) ((x*x) + (y*y)) );
            }   
         }
   }

int in_LOS( int x1, 
            int y1,
            int x2,
            int y2,
            int x_delta,
            int y_delta  )
   {

   int x_from,
       y_from,
       x_to,
       y_to,
       curr_x,
       curr_y,
       x_overflow,
       y_overflow,
       x_increment,
       y_increment,
       clear = TRUE;

   if (x_delta > y_delta)
      {
      // increment by x
      if (x1 > x2)
         {
         x_from = x2;
         y_from = y2;
         x_to   = x1;
         y_to   = y1;
         }
      else
         {
         x_from = x1;
         y_from = y1;
         x_to   = x2;
         y_to   = y2;
         }
      if (y_from > y_to)
         {
         y_increment = -1;
         }
      else
         {
         y_increment =  1;
         }   
      // do it..
      y_overflow = 0;
      curr_y = y_from;
      for ( curr_x = x_from; curr_x <= x_to; curr_x++)
         {
         if (     (map[curr_x][curr_y] == HWALL)
             ||   (map[curr_x][curr_y] == VWALL)
             ||   (map[curr_x][curr_y] == BWALL)
             ||   (map[curr_x][curr_y] == TREE )
            )
            {
            clear = FALSE;
            break;
            }    
         y_overflow += y_delta;
         if (y_overflow >= x_delta)
            {
            y_overflow -= x_delta;
            curr_y += y_increment;
            }   
         }                
         
      }
   else
      {
      // increment by y
      if (y1 > y2)
         {
         x_from = x2;
         y_from = y2;
         x_to   = x1;
         y_to   = y1;
         }
      else
         {
         x_from = x1;
         y_from = y1;
         x_to   = x2;
         y_to   = y2;
         }
      if (x_from > x_to)
         {
         x_increment = -1;
         }
      else
         {
         x_increment =  1;
         }   
      // do it..
      x_overflow = 0;
      curr_x = x_from;
      for ( curr_y = y_from; curr_y <= y_to; curr_y++)
         {
         if (     (map[curr_x][curr_y] == HWALL)
             ||   (map[curr_x][curr_y] == VWALL)
             ||   (map[curr_x][curr_y] == BWALL)
             ||   (map[curr_x][curr_y] == TREE )
            )
            {
            clear = FALSE;
            break;
            }    
         x_overflow += x_delta;
         if (x_overflow >= y_delta)
            {
            x_overflow -= y_delta;
            curr_x += x_increment;
            }   
         }          
      }
   return(clear);   
   }               
