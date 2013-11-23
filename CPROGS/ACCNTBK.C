/*****************************************************************************/
/* This simple program creates a small data base, which could typically be   */
/* used for keeping bank accounts. Look at the "README" file under the same  */
/* directory for suggestions(!?!) on how to carry on with the assignment.    */
/*****************************************************************************/

#include <stdio.h>

#define MAX          100
#define PHONENUMSIZE 10
#define NAMESIZE     30
#define STREETSIZE   50
#define CITYSIZE     20
#define SSNUMSIZE    9

int  main       (void   );
void init_db    (void   );
int  menu_sel   (void   );
void add_entry  (void   );
void get_numbers(char *,
                 int    );
int  find_free  (void   );
void del_entry  (void   );
void list_db    (void   );



struct addr
{
   char name[NAMESIZE];
   char street[STREETSIZE];
   char city[CITYSIZE];
   char phonenum[PHONENUMSIZE];
   char ssnum[SSNUMSIZE];
   float balance;

} account[MAX];

main ()
{
   char choice;

   init_db ();                          /* initialize "database" */
   while (1)
   {
      choice = menu_sel ();
      switch (choice)
      {
         case 1: add_entry ();
                 break;
         case 2: del_entry ();
                 break;
         case 3: list_db ();
                 break;
         case 4: exit (0);              /* exit the program */

      } /* switch */
   } /* while */
} /* main */


/*****************************************************************************/
/* NAME : init_db                                                            */
/* PURPOSE : initialize the database with no entries                         */
/*****************************************************************************/

void init_db()
{
   register int t;

   for ( t = 0; t < MAX; t++ )
      account[t].name[0] = '\0';
} /* init_db */


/*****************************************************************************/
/* NAME : menu_sel                                                           */
/* PURPOSE : inquire user for selection of operation on database             */
/*****************************************************************************/

int menu_sel()
{
   char s[80];
   int i;

   printf ("1. Add a new account\n");
   printf ("2. Delete an account\n");
   printf ("3. List the database\n");
   printf ("4. Exit the database\n");
   do
   {
      printf ("\nEnter your choice ----> ");
      gets (s);
      i = atoi (s);                     /* convert alpha value to integer */
   } while ( i < 0 || i > 4 );
   return(i);
} /* menu_sel */


/*****************************************************************************/
/* NAME : add_entry                                                          */
/* PURPOSE : create a new account and put it in the database                 */
/*****************************************************************************/

void add_entry()
{
   int slot;
   int curr_char;
   char in_char;

   slot = find_free ();
   if ( slot == -1 )
   {
      printf ("\nDatabase full !!");
      return;
   } /* if */

   printf ("Enter name ----> ");
   gets (account[slot].name);

   printf ("Enter street ----> ");
   gets (account[slot].street);

   printf ("Enter city ----> ");
   gets (account[slot].city);

   printf ("Enter deposit ----> ");
   scanf ("%f", &account[slot].balance);

   fflush(stdin);

   printf ("Enter phone number { (ac)num-numm } ---->(");

   get_numbers(&account[slot].phonenum[0],3);

   printf(")-");

   get_numbers(&account[slot].phonenum[3],3);

   printf("-");

   get_numbers(&account[slot].phonenum[6],4);

   printf("\n");

   printf ("Enter SS number { ###-##-#### } ---->");

   get_numbers(&account[slot].ssnum[0],3);

   printf("-");

   get_numbers(&account[slot].ssnum[3],2);

   printf("-");

   get_numbers(&account[slot].ssnum[5],4);

   printf("\n");


} /* add_entry */


void get_numbers( str,cnt )
char *str;
int  cnt;
{
  int curr_char;
  char in_char;

  for(curr_char = 0; curr_char < cnt ;++curr_char)
   {
     do
     {
       in_char = (char) getch();                  
     } while ( (in_char < '0') || (in_char > '9'));
     putchar(in_char);
     *str = in_char;
     str++;

   } /* for */


} /* get_numbers */


/*****************************************************************************/
/* NAME : find_free                                                          */
/* PURPOSE : search for a vacant slot in the database                        */
/*****************************************************************************/

int find_free()
{
   register int t;

   for ( t = 0; t < MAX && account[t].name[0]; t++ )
   if ( t == MAX )
      return -1;                        /* no free slots in database */
   return t;
} /* find_free */


/*****************************************************************************/
/* NAME : del_entry                                                          */
/* PURPOSE : delete a bank account from the database                         */
/*****************************************************************************/

void del_entry()
{
   register int slot;
   char s[80];

   printf ("Enter account number ----> ");
   gets (s);
   slot = atoi (s);
   if ( slot > 0 && slot < MAX )
      account[slot].name[0] = '\0';
} /* del_entry */


/*****************************************************************************/
/* NAME : list_db                                                            */
/* PURPOSE : list the entire database on the screen                          */
/*****************************************************************************/

void list_db()
{
   register int t;

   for ( t = 0; t < MAX; t++ )
   {
      if ( account[t].name[0] )
      {
         printf ("%s\n", account[t].name);
         printf ("%s\n", account[t].street);
         printf ("%s\n", account[t].city);
         printf ("%f\n", account[t].balance);
         printf ("(%.3s)%.3s-%.4s\n",
                 &account[t].phonenum[0],
                 &account[t].phonenum[3],
                 &account[t].phonenum[6]   );

         printf ("%.3s-%.2s-%.4s\n",
                 &account[t].ssnum[0],
                 &account[t].ssnum[3],
                 &account[t].ssnum[5]   );



      } /* if */
   } /* for */
   printf ("\n\n");
} /* list_db */
