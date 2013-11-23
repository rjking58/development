#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#define DEBUGGING 1
#include "tracer.h"
#define TRUE 1
#define FALSE 0
#define ON  1
#define OFF 0
/* ********************************************
randomly generate people waiting and requesting elevator
start elevator at floor 1
people take between 1 and 20 time ticks to press buttons
first button gets priority
first destination pressed gives direction priority
 


people:  start floor/end floor 
elevator: max capacity
crowding factor (how many people are pissed).

tick loop
    gen waiters (press request)
    move/load elevator 
         load
            (1 passenger/tick until full or no more pass.)
            set destinations (in passenger loading order)
         move
            (move in direction of car until all floors hit)
            (change direction of more destinations or wait)



********************************************* */


#include <stdio.h>
#define FLOORS        20

unsigned int floor_cnt[FLOORS];     /* waiting for elevator */
unsigned int destinations[FLOORS];  /* master goto toggle */
unsigned int dest_cnt; /* total number of floor call buttons pressed */
#define GO_THERE      1
#define DONT_GO_THERE 0

/* people on elevator going somewhere */
/* elevator specific info. */
#define ELEV_CNT 3
typedef struct elevator
   {
   unsigned int elevator_id;
   unsigned int loaded_on_elev;
   unsigned int getoff_cnt[FLOORS];    /* destination count for elev */
   unsigned int e_destinations[FLOORS];  /* master goto toggle */
   unsigned int e_dest_cnt;
   unsigned int elevator_mode;
   unsigned int elevator_dir;
   unsigned int elevator_floor;
   } ELEVATOR_TYPE;

ELEVATOR_TYPE *elevators[ELEV_CNT],
              *elev_temp;
unsigned int   curr_elev;
/*   unsigned int elevator_mode; */

#define LOADING 1
#define MOVING  2
#define WAITING 3

/*   unsigned int elevator_dir;  */
#define UP 2
#define DOWN 1
#define CLEAR 0

#define START_FLOOR 10

#define MAX_PASSENGERS 200

float avg_wait;
unsigned int passenger_cnt;
unsigned int served;
unsigned int pass_master_id;
typedef struct passenger
   {
   unsigned int passenger_id;
   unsigned int source_floor;
   unsigned int dest_floor;
   unsigned int location;
   unsigned int waittime;
   struct passenger *next_dude;
   } PASSENGER_TYPE;

PASSENGER_TYPE *passenger_hol, /*head of list*/
               *passenger_eol, /*end of list */
               *passenger_temp, /*for purposes of creating passengers */
               *passenger_prev,
               *passenger_curr;

#define WAITING_FOR_ELEVATOR 0

unsigned int   time_tick;
unsigned int   last_elevator_floor;

#define MAKE_PASS_THRESHHOLD 5550  /* between 1 and 32,000 */

/* totoprypes */
void wait_er();
void change_elevator_mode();
void make_passenger();
void load_elevator(ELEVATOR_TYPE *elev_t);
void move_elevator();
void show_me();

void *malloc();

main()
   {
   int rand_num,
       curr_floor;

   int winning_elev,
       winning_elev_dist;


#ifdef DEBUGGING
   if ((trcfile = fopen("elev2.trc", "w")) == NULL) 
      {
      printf("Can't open PC file");
      exit(0);
      }
   else 
      {
#endif


   /* initialize elevators */
   served=0;
   for (curr_elev = 0; curr_elev < ELEV_CNT; curr_elev++ )
      {
      elevators[curr_elev] = (struct elevator *)malloc(sizeof(struct elevator));
      elevators[curr_elev]->loaded_on_elev = 0;
      elevators[curr_elev]->elevator_id    = curr_elev + 1;
      elevators[curr_elev]->elevator_mode  = WAITING;
      elevators[curr_elev]->elevator_dir   = CLEAR;
      elevators[curr_elev]->elevator_floor = START_FLOOR;
      elevators[curr_elev]->e_dest_cnt     = 0;

      for ( curr_floor = 0 ; curr_floor < FLOORS ; curr_floor++)
         {
         elevators[curr_elev]->e_destinations[curr_floor] = DONT_GO_THERE;
         elevators[curr_elev]->getoff_cnt[curr_floor] = 0;
         }
      }
   /* initialize state machine */

   avg_wait = 0;

   for ( curr_floor = 0 ; curr_floor < FLOORS ; curr_floor++)
      {
      destinations[curr_floor] = DONT_GO_THERE;
      dest_cnt = 0;
      floor_cnt[curr_floor] = 0;
      }
   passenger_cnt = 0;
   pass_master_id = 1;
   randomize();
   for (time_tick = 0 ; time_tick < 31000 ; time_tick++)
      {
      /* make a passenger on a floor */
      rand_num = rand();
      if (rand_num < MAKE_PASS_THRESHHOLD)
         make_passenger(); /* >>>done<<< */
      
      TRACE_INT(dest_cnt);
      TRACE_ARR(destinations,FLOORS);
      /* update local pressed buttons with global pressed buttons */
      for (curr_elev = 0; curr_elev < ELEV_CNT; curr_elev++ )
         {
         TRACE_INT(elevators[curr_elev]->e_dest_cnt);
         TRACE_ARR(elevators[curr_elev]->e_destinations,FLOORS);
         /* destinations is call button state                        */
         /* dest_cnt is how many buttons have been pressed and not   */
         /* acted upon                                               */
         if (dest_cnt !=0 )
            {
            for(curr_floor=0 ; curr_floor<FLOORS ; curr_floor++)
               {
               if ((destinations[curr_floor] == GO_THERE) 
                   && ((curr_floor == elevators[curr_elev]->elevator_floor)   
                       || (elevators[curr_elev]->elevator_mode == WAITING)
                       || ((curr_floor < elevators[curr_elev]->elevator_floor) 
                           && (elevators[curr_elev]->elevator_dir == DOWN)
                          ) 
                       || ((curr_floor > elevators[curr_elev]->elevator_floor) 
                           && (elevators[curr_elev]->elevator_dir == UP)
                          ) 
                      )
                  )
                  {
                  if (elevators[curr_elev]->e_destinations[curr_floor] == DONT_GO_THERE)
                     {
                     elevators[curr_elev]->e_destinations[curr_floor]=GO_THERE;
                     elevators[curr_elev]->e_dest_cnt++;
                     }

                  if (destinations[curr_floor] == GO_THERE)
                     {
                     destinations[curr_floor] = DONT_GO_THERE;
                     dest_cnt--;
                     }
                  }
               }
            }
         }
      for (curr_elev = 0; curr_elev < ELEV_CNT; curr_elev++ )
         {
         elev_temp = elevators[curr_elev];

         /* new change elevator mode */
         /* **OR**  send towards call if we are waiting ! */
         if ( (elev_temp->elevator_mode == WAITING)
              && (elev_temp->e_dest_cnt != 0)
            )
            {
            if( elev_temp->
                  e_destinations[elev_temp->elevator_floor] == GO_THERE )
               {
               elev_temp->elevator_mode = LOADING;
               TRACE_STR("************elevator mode change***");
               TRACE_INT(elev_temp->elevator_id);
               TRACE_INT(elev_temp->elevator_mode);
               }
            else
               {
               curr_floor = 0;
               while( elev_temp->e_destinations[curr_floor] != GO_THERE )
                  {
                  curr_floor++;
                  }
               if (curr_floor < elev_temp->elevator_floor)
                  {
                  elev_temp->elevator_dir = DOWN ;
                  }
               else
                  {
                  elev_temp->elevator_dir = UP   ;
                  }
               TRACE_STR("************elevator mode change***");
               TRACE_INT(elev_temp->elevator_id);
               elev_temp->elevator_mode = MOVING;
               TRACE_INT(elev_temp->elevator_mode);
               }
            }
            /* if moving and at a call stop... stop and load ! */
         else if (elev_temp->elevator_mode == MOVING)
            {
            TRACE_STR("Moving%%%%%%%%%%%%%%%%%%%%%%");
            if (elev_temp->elevator_dir == UP)
               {
               if(elev_temp->elevator_floor < (FLOORS - 1))
                  {
                  TRACE_INT(elev_temp->elevator_id);
                  TRACE_INT(elev_temp->elevator_floor);
                  elev_temp->elevator_floor++;
                  TRACE_INT(elev_temp->elevator_floor);
                  }
               }
            else
               {
               /* must be down! */
               if(elev_temp->elevator_floor > 0)
                  {
                  TRACE_INT(elev_temp->elevator_id);
                  TRACE_INT(elev_temp->elevator_floor);
                  elev_temp->elevator_floor--;
                  TRACE_INT(elev_temp->elevator_floor);
                  }
               }
            if ( elev_temp->e_destinations[elev_temp->elevator_floor] == GO_THERE) 
               {
               TRACE_STR("************elevator mode change***");
               TRACE_INT(elev_temp->elevator_id);
               elev_temp->elevator_mode = LOADING;
               TRACE_INT(elev_temp->elevator_mode);
               }
            }
         else if (elev_temp->elevator_mode == LOADING)
            {
            load_elevator(elev_temp);
            }
         }
      /* update screen */
      show_me();
      wait_er(); 
      }
#ifdef DEBUGGING
      fclose(trcfile);
      }
#endif
   } /* main */

void make_passenger()
   {
   int start_floor,end_floor;

   gotoxy(30,1);
   printf("make_passenger");
   start_floor = 0;
   end_floor = 0;
   TRACE_ENTER("make_passenger");
   if (passenger_cnt < MAX_PASSENGERS)
      {
      while (start_floor == end_floor)
         {
         start_floor = rand() % FLOORS;
         end_floor = rand() % FLOORS;
         }
      assert(start_floor != end_floor);
      passenger_temp = (struct passenger *)malloc(sizeof(struct passenger));
      passenger_temp->passenger_id = pass_master_id;
      pass_master_id++;
      if(passenger_cnt == 0)
         {
         passenger_hol = passenger_temp;
         }
      else
         {
         passenger_eol->next_dude = passenger_temp;
         }
      passenger_temp->next_dude = NULL;
      passenger_eol = passenger_temp;
      passenger_cnt++;
      passenger_temp->source_floor = start_floor;
      passenger_temp->dest_floor = end_floor;
      passenger_temp->location = WAITING_FOR_ELEVATOR;
      passenger_temp->waittime = time_tick;

      floor_cnt[start_floor]++;
      if (destinations[start_floor] == DONT_GO_THERE)
         {
         destinations[start_floor] = GO_THERE;
         dest_cnt++;
         }
      }
   TRACE_EXIT("make_passenger");
   }

void load_elevator(ELEVATOR_TYPE *elev_t)
   {
   int curr_floor;
   int found;
   void get_off_the_fucking_bus(ELEVATOR_TYPE *elev_t);
   void get_on_quick_goddamnit(ELEVATOR_TYPE *elev_t);
   
   gotoxy(30,1);
   printf("load_elevator");
   TRACE_ENTER("load_elevator");
   /* check for call but already serviced! */
   if ((floor_cnt[elev_t->elevator_floor] == 0)
       && (elev_t->getoff_cnt[elev_t->elevator_floor] == 0) )
      {
      if (elev_t->e_destinations[elev_t->elevator_floor]==GO_THERE)
         {
         elev_t->e_destinations[elev_t->elevator_floor]= DONT_GO_THERE;
         elev_t->e_dest_cnt--;
         }
      }
   /* unload first please... */
   if(elev_t->getoff_cnt[elev_t->elevator_floor] != 0)
      {
      get_off_the_fucking_bus(elev_t);
      }
   /* load next please... */
   else if ( floor_cnt[elev_t->elevator_floor] != 0 )
      {
      get_on_quick_goddamnit(elev_t);
      }
   /* after loading... if any more requests for elev. (in same dir) are pending,
      go to them... */
   else if ( (elev_t->elevator_floor < (FLOORS - 1)) 
             && (elev_t->elevator_floor > 0)
           )
      {
      if (elev_t->elevator_dir == UP)
         {
         curr_floor = elev_t->elevator_floor + 1;
         found = FALSE;
         while ( (curr_floor < FLOORS) && (found == FALSE))
            {
            if ( elev_t->e_destinations[curr_floor] == GO_THERE )
               {
               found=TRUE;
               TRACE_STR("************elevator mode change***");
               TRACE_INT(elev_temp->elevator_id);
               elev_t->elevator_mode=MOVING;
               TRACE_INT(elev_t->elevator_mode);
               }
            else
               {
               curr_floor++;
               }
            }  
         if (found==FALSE)
            {
            TRACE_STR("************elevator mode change***");
            TRACE_INT(elev_temp->elevator_id);
            elev_t->elevator_mode=WAITING;
            TRACE_INT(elev_t->elevator_mode);
            }
         }
      else
         {
         /* down */
         curr_floor = elev_t->elevator_floor - 1;
         found = FALSE;
         while ( (curr_floor >= 0) && (found == FALSE))
            {
            if ( elev_t->e_destinations[curr_floor] == GO_THERE )
               {
               found=TRUE;
               TRACE_STR("************elevator mode change***");
               TRACE_INT(elev_temp->elevator_id);
               elev_t->elevator_mode=MOVING;
               TRACE_INT(elev_t->elevator_mode);
               }
            else
               {
               curr_floor--;
               }
            }  
         if (found==FALSE)
            {
            TRACE_STR("************elevator mode change***");
            TRACE_INT(elev_temp->elevator_id);
            elev_t->elevator_mode=WAITING;
            TRACE_INT(elev_t->elevator_mode);
            }
         }
      }
   else
      {
      TRACE_STR("************elevator mode change***");
      TRACE_INT(elev_temp->elevator_id);
      elev_t->elevator_mode=WAITING;
      TRACE_INT(elev_t->elevator_mode);
      }
   /* otherwise, if any destinations lie in same dir, go to them! */
   /* otherwise change direction and go! */
   TRACE_EXIT("load_elevator");
   }

void get_off_the_fucking_bus(ELEVATOR_TYPE *elev_t)
   {
   int finished;

   TRACE_ENTER("get_off_the_fucking_bus");
   gotoxy(30,1);
   printf("get_off_the_fucking_bus");
   if (passenger_hol != NULL)
      {
      passenger_curr=passenger_hol;
      finished = FALSE;
      while(finished != TRUE)
         {
         if ((passenger_curr->dest_floor  == elev_t->elevator_floor)
             && (elev_t->elevator_mode    == LOADING)
             && (passenger_curr->location == elev_t->elevator_id)  )
            {
            TRACE_STR("get_off_the_fu.... passenger found");
            TRACE_INT(passenger_curr->passenger_id);
            TRACE_INT(passenger_curr->dest_floor);
            TRACE_INT(passenger_curr->source_floor);
            TRACE_INT(passenger_curr->location);
            TRACE_INT(elev_t->elevator_id);
            TRACE_INT(elev_t->elevator_floor);
            TRACE_INT(elev_t->getoff_cnt[elev_t->elevator_floor]);
            TRACE_INT(elev_t->loaded_on_elev);

            avg_wait = ((float)(time_tick - passenger_curr->waittime)) + avg_wait / 2.0;
            elev_t->getoff_cnt[elev_t->elevator_floor]--;
            assert(elev_t->getoff_cnt[elev_t->elevator_floor]<100);
            elev_t->loaded_on_elev--;
            passenger_cnt--;
            served++;
            /* ??? */
            if (elev_t->e_destinations[elev_t->elevator_floor]==GO_THERE)
               {
               elev_t->e_destinations[elev_t->elevator_floor]= DONT_GO_THERE;
               elev_t->e_dest_cnt--;
               }

            if (passenger_curr==passenger_hol)
               {
               /* kill head item */
               passenger_hol = passenger_curr->next_dude;
               if (passenger_hol==NULL)
                  passenger_eol=NULL;
               }
            else
               {
               /* delete middle and possibly end item */
               passenger_prev->next_dude = passenger_curr->next_dude;
               if(passenger_curr == passenger_eol)
                  {
                  passenger_eol=passenger_prev;
                  }
               }
            passenger_temp = passenger_curr;
            passenger_curr = passenger_curr->next_dude;
            free( (void *)passenger_temp );
            }
         else
            {
            passenger_prev = passenger_curr;
            passenger_curr = passenger_curr->next_dude;
            }
         if(passenger_curr==NULL)
            {
            finished = TRUE;
            }
         }
      }
   TRACE_EXIT("get_off_the_fucking_bus");
   }
void get_on_quick_goddamnit(ELEVATOR_TYPE *elev_t)
   {
   int finished;

   TRACE_ENTER("get_on_quick_goddamnit");
   gotoxy(30,1);
   printf("get_on_quick_goddamnit");
   if (passenger_hol != NULL) 
      {
      passenger_curr=passenger_hol;
      finished = FALSE;
      while(finished != TRUE)
         {
         if ((passenger_curr->source_floor == elev_t->elevator_floor   ) 
             && (elev_t->elevator_mode     == LOADING)
             && (passenger_curr->location  == WAITING_FOR_ELEVATOR )    )
            {
            TRACE_STR("get_on_quick... found passenger");
            TRACE_INT(floor_cnt[elev_t->elevator_floor]);
            TRACE_INT(passenger_curr->passenger_id);
            TRACE_INT(passenger_curr->dest_floor);
            TRACE_INT(passenger_curr->source_floor);
            TRACE_INT(passenger_curr->location);
            TRACE_INT(elev_t->elevator_id);
            TRACE_INT(elev_t->elevator_floor);
            TRACE_INT(elev_t->getoff_cnt[passenger_curr->dest_floor]);
            TRACE_INT(elev_t->loaded_on_elev);

            elev_t->loaded_on_elev++;
            floor_cnt[elev_t->elevator_floor]--;
            elev_t->getoff_cnt[passenger_curr->dest_floor]++;
            assert(elev_t->getoff_cnt[passenger_curr->dest_floor]<100);
            if (elev_t->e_destinations[elev_t->elevator_floor]==GO_THERE)
               {
               elev_t->e_destinations[elev_t->elevator_floor]= DONT_GO_THERE;
               elev_t->e_dest_cnt--;
               }
            if (elev_t->e_destinations[passenger_curr->dest_floor]==DONT_GO_THERE)
               {
               elev_t->e_destinations[passenger_curr->dest_floor]= GO_THERE;
               elev_t->e_dest_cnt++;
               }
            passenger_curr->location=elev_t->elevator_id;
            }
         passenger_curr = passenger_curr->next_dude;
         if (passenger_curr==NULL)
            {
            finished = TRUE;
            }
         }
      }
   TRACE_EXIT("get_on_quick_goddamnit");
   }

void show_me()
   {
   int finished;
   int x,y;
   int temp_dest,temp_loaded;
   int curr_floor;
   int passenger_curr_cnt;
   clrscr();
   printf("%u\n",time_tick);
   printf("  |");
   for(curr_elev=0;curr_elev<ELEV_CNT;curr_elev++)
      {
      if (elevators[curr_elev]->elevator_dir == UP)
         {
         printf("^ |");
         }
      else
         {
         printf("| |");
         }
      }
      printf("\n");
   printf("  |");
   for(curr_elev=0;curr_elev<ELEV_CNT;curr_elev++)
      {
      if (elevators[curr_elev]->elevator_dir == UP)
         {
         printf("| |");
         }
      else
         {
         printf("v |");
         }
      }
      printf("\n");
   for(curr_floor=FLOORS-1;curr_floor >= 0;curr_floor--)
      {
      printf("%2u|",curr_floor);
      for(curr_elev=0;curr_elev<ELEV_CNT;curr_elev++)
         {
         if(elevators[curr_elev]->elevator_floor == curr_floor)
            {
            if (elevators[curr_elev]->elevator_mode == WAITING)
               {
               printf("w |");
               }
            else
               {
               printf("%2u|",
                      elevators[curr_elev]->loaded_on_elev);
               }
            }
         else
            {
            if (elevators[curr_elev]->e_destinations[curr_floor] == GO_THERE)
               {
               if ((elevators[curr_elev]->getoff_cnt[curr_floor] == 0)
                   && (floor_cnt[curr_floor] == 0                    ) )
                  {
                  printf("= |");
                  }
               else
                  {
                  printf("$ |");
                  }
               }
            else
               {
               printf("  |");
               }
            }
         }
      printf("%4u",
             floor_cnt[curr_floor]);
      printf("(%2u)(%2u)(%2u)",
              elevators[0]->getoff_cnt[curr_floor],
              elevators[1]->getoff_cnt[curr_floor],
              elevators[2]->getoff_cnt[curr_floor] );
      if ( floor_cnt[curr_floor] > 0 ) 
         {
         printf("*\n");
         }
      else
         {
         printf("\n");
         }
      }
   gotoxy(31,2);
   printf("pass_cnt=%3u",passenger_cnt);
   gotoxy(31,3);
   printf("served=%u",served);
   gotoxy(31,4);
   printf("avg_wait->%f",avg_wait);

   x=50;
   y=2;
   passenger_curr_cnt=0;
   finished=FALSE;
   passenger_curr=passenger_hol;
   /*                   555555555566666666667 */
   /*                   012345678901234567890 */
   gotoxy(50,1);printf("s  d  l       s  d  l");

   while (finished != TRUE)
      {
      if(passenger_curr==NULL)
         {
         finished = TRUE;
         }
      else
         {
         passenger_curr_cnt++;
         gotoxy(x,y);
         printf("%2u %2u %2u",
                passenger_curr->source_floor,
                passenger_curr->dest_floor,
                passenger_curr->location);
         passenger_curr=passenger_curr->next_dude;
         y++;
         if (y>23)
            {
            x=64;
            y=2;
            }
         }
      }
   }





void wait_er() /* check please! */
   {
   int
      x;
   time_t
      tnow;
   struct tm
      *tm_p;
   int
      then_hour,
      then_min,
      then_sec;

   time(&tnow);
   tm_p = localtime(&tnow);


   then_hour = tm_p->tm_hour ; 
   then_min  = tm_p->tm_min  ; 
   then_sec  = tm_p->tm_sec  ; 

   do
      {
      time(&tnow);
      tm_p = localtime(&tnow);
      }
   while ( (tm_p->tm_hour == then_hour) &&
           (tm_p->tm_min  == then_min ) &&
           (tm_p->tm_sec  == then_sec )    );
   }

/* <<<<<<<<<<<<<<<<<<<<<<<<<<<<<END>>>>>>>>>>>>>>>>>>>>>>>> */

