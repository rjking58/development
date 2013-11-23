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

void wait_er();
void change_elevator_mode();
void make_passenger();
void load_elevator();
void move_elevator();
void show_me();

void *malloc();

#include <stdio.h>
#define FLOORS        20

/* people on elevator going somewhere */
unsigned int loaded_on_elev;
unsigned int floor_cnt[FLOORS];
unsigned int getoff_cnt[FLOORS];

unsigned int destinations[FLOORS];
#define GO_THERE      1
#define DONT_GO_THERE 0

/* people waiting for elevator */
unsigned int elevator_requested_total_cnt;
unsigned int elevator_requested_local_cnt[FLOORS];
unsigned int elevator_requested[FLOORS];
#define COME_HERE_MY_SON 1
#define SKIP_IT          0

unsigned int elevator_mode;
#define LOADING 1
#define MOVING  2
#define WAITING 3

unsigned int elevator_dir;
#define UP 2
#define DOWN 1
#define CLEAR 0

unsigned int elevator_floor;

#define MAX_PASSENGERS 200

float avg_wait;
unsigned int passenger_cnt;
typedef struct passenger
   {
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

#define IN_ELEVATOR 1
#define WAITING_FOR_ELEVATOR 0

unsigned int   time_tick;
unsigned int   same_floor_master_cnt;
unsigned int   last_elevator_floor;

#define MAKE_PASS_THRESHHOLD 2550  /* between 1 and 32,000 */

main()
   {
   int rand_num,
       curr_floor;

   /* initialize state machine */
   same_floor_master_cnt=0;
   last_elevator_floor=20;

   avg_wait = 0;

   elevator_dir = CLEAR;
   elevator_mode = WAITING;
   elevator_floor = 10;
   elevator_requested_total_cnt = 0 ;
   for ( curr_floor = 0 ; curr_floor < FLOORS ; curr_floor++)
      {
      destinations[curr_floor] = DONT_GO_THERE;
      floor_cnt[curr_floor] = 0;
      getoff_cnt[curr_floor] = 0;
      }
   passenger_cnt = 0;
   randomize();
   for (time_tick = 0 ; time_tick < 31000 ; time_tick++)
      {
      /* make a passenger on a floor */
      rand_num = rand();
      if (rand_num < MAKE_PASS_THRESHHOLD)
         make_passenger(); /* >>>done<<< */
      /* move or unload/load elevator */
      if ( (elevator_mode == WAITING                ) && 
           ( (elevator_requested_total_cnt != 0) ||
             (loaded_on_elev != 0              )    )    )
         {
         change_elevator_mode();
         }
      else if (elevator_mode == LOADING)
         {
         load_elevator();
         }
      else if (elevator_mode == MOVING)
         {
         move_elevator();
         }
      if ((elevator_requested_total_cnt == 0) &&
          (loaded_on_elev == 0              )    ) 
         {
         elevator_mode = WAITING;
         }
      /* update screen */
      show_me();
      wait_er();
      }
   } /* main */

void make_passenger()
   {
   int start_floor,end_floor;

   gotoxy(30,1);
   printf("make_passenger");
   start_floor = 0;
   end_floor = 0;

   if (passenger_cnt < MAX_PASSENGERS)
      {
      while (start_floor == end_floor)
         {
         start_floor = rand() % FLOORS;
         end_floor = rand() % FLOORS;
         }
      passenger_temp = (struct passenger *)malloc(sizeof(struct passenger));
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

      elevator_requested_total_cnt++;
      floor_cnt[start_floor]++;
      destinations[start_floor] = GO_THERE;
      }
   }
void change_elevator_mode()
   {
   int curr_floor;

   gotoxy(30,1);
   printf("change_elevator_mode");

   if (destinations[elevator_floor] == GO_THERE)
      {
      elevator_mode = LOADING;
      }
   else
      {
      curr_floor = 0;
      while( destinations[curr_floor] != GO_THERE )
         {
         curr_floor++;
         }
      if (curr_floor < elevator_floor)
         {
         elevator_dir = DOWN ;
         }
      else
         {
         elevator_dir = UP   ;
         }
      elevator_mode = MOVING;
      }
   }

void load_elevator()
   {
   int curr_floor;
   int found;
   void get_off_the_fucking_bus();
   void get_on_quick_goddamnit();
   
   gotoxy(30,1);
   printf("load_elevator");

   /* unload first please... */
   if(getoff_cnt[elevator_floor] != 0)
      {
      get_off_the_fucking_bus();
      if ( ( floor_cnt[elevator_floor]  == 0 ) && 
           ( getoff_cnt[elevator_floor] == 0 )   )
         {
         destinations[elevator_floor]= DONT_GO_THERE;
         }
      }
   /* load next please... */
   else if ( floor_cnt[elevator_floor] != 0 )
      {
      get_on_quick_goddamnit();
      if ( ( floor_cnt[elevator_floor]  == 0 ) && 
           ( getoff_cnt[elevator_floor] == 0 )   )
         {
         destinations[elevator_floor]= DONT_GO_THERE;
         }
      }
   /* after loading... if any more requests for elev. (in same dir) are pending,
      go to them... */
   else if ((elevator_floor < (FLOORS - 1)) && (elevator_floor > 0))
      {
      if (elevator_dir == UP)
         {
         curr_floor = elevator_floor + 1;
         found = FALSE;
         while ( (curr_floor < FLOORS) && (found == FALSE))
            {
            if ( destinations[curr_floor] == GO_THERE )
               {
               found=TRUE;
               elevator_mode=MOVING;
               }
            else
               {
               curr_floor++;
               }
            }  
         if (found==FALSE)
            {
            elevator_mode=WAITING;
            }
         }
      else
         {
         /* down */
         curr_floor = elevator_floor - 1;
         found = FALSE;
         while ( (curr_floor >= 0) && (found == FALSE))
            {
            if ( destinations[curr_floor] == GO_THERE )
               {
               found=TRUE;
               elevator_mode=MOVING;
               }
            else
               {
               curr_floor--;
               }
            }  
         if (found==FALSE)
            {
            elevator_mode=WAITING;
            }
         }
      }
   else
      {
      elevator_mode=WAITING;
      }
   /* otherwise, if any destinations lie in same dir, go to them! */
   /* otherwise change direction and go! */
   }
void move_elevator()
   {
   gotoxy(30,1);
   printf("move_elevator");

   if (elevator_dir == UP)
      {
      if(elevator_floor < (FLOORS - 1))
         elevator_floor++;
      }
   else
      {
      if(elevator_floor > 0)
         elevator_floor--;
      }
   if ( destinations[elevator_floor] == GO_THERE) 
      {
      elevator_mode = LOADING;
      }
   }

void get_off_the_fucking_bus()
   {
   int finished;

   gotoxy(30,1);
   printf("get_off_the_fucking_bus");
   if (passenger_hol != NULL)
      {
      passenger_curr=passenger_hol;
      finished = FALSE;
      while(finished != TRUE)
         {
         if ((passenger_curr->dest_floor == elevator_floor) &&
            (passenger_curr->location == IN_ELEVATOR     )    )
            {
            avg_wait = ((float)(time_tick - passenger_curr->waittime)) + avg_wait / 2.0;
            getoff_cnt[elevator_floor]--;
            loaded_on_elev--;
            passenger_cnt--;
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
   }
void get_on_quick_goddamnit()
   {
   int finished;

   gotoxy(30,1);
   printf("get_on_quick_goddamnit");
   if (passenger_hol != NULL) 
      {
      passenger_curr=passenger_hol;
      finished = FALSE;
      while(finished != TRUE)
         {
         if ((passenger_curr->source_floor == elevator_floor   ) &&
            (passenger_curr->location == WAITING_FOR_ELEVATOR )    )
            {
            elevator_requested_total_cnt--;
            loaded_on_elev++;
            floor_cnt[elevator_floor]--;
            getoff_cnt[passenger_curr->dest_floor]++;
            destinations[passenger_curr->dest_floor]= GO_THERE;
            passenger_curr->location=IN_ELEVATOR;
            }
         passenger_curr = passenger_curr->next_dude;
         if (passenger_curr==NULL)
            {
            finished = TRUE;
            }
         }
      }
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
   for(curr_floor=0;curr_floor<FLOORS;curr_floor++)
      {
      if(curr_floor != elevator_floor)
         {
         printf("|    |%4u (%4u)",
                floor_cnt[curr_floor],
                getoff_cnt[curr_floor] );
         }
      else
         {
         printf("|%4u|%4u (%4u)",
                loaded_on_elev,
                floor_cnt[curr_floor],
                getoff_cnt[curr_floor]);
         }
      if ( floor_cnt[curr_floor] > 0 ) 
         {
         printf("*\n");
         }
      else
         {
         printf("\n");
         }
      }
    
   gotoxy(23,2);
   printf("pass_cnt=%3u",passenger_cnt);
   gotoxy(23,3);
   printf("elev_floor=%3u",elevator_floor);
   gotoxy(23,4);
   printf("elev_rqst_cnt=%3u",elevator_requested_total_cnt);
   gotoxy(23,5);
   printf("elevator_mode=");
   if (elevator_mode == LOADING)
      {
      printf("LOADING");
      }
   if (elevator_mode == MOVING)
      {
      printf("MOVING");
      }
   if (elevator_mode == WAITING)
      {
      printf("WAITING");
      }
   if (elevator_dir==UP)
      {
      printf("^");
      }
   else
      {
      printf("v");
      }
   gotoxy(23,6);
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
   gotoxy(2,23);
/*   if (elevator_floor==last_elevator_floor)
      {
      same_floor_master_cnt++;
      }
   else
      {
      same_floor_master_cnt= 0;
      }
   last_elevator_floor=elevator_floor;
   if(same_floor_master_cnt>20)
      exit(0); */
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