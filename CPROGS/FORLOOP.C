/*****************************************************************************/
/* Test program :                                                            */
/*      This program illustrates issues regarding the "for" statement.       */
/*****************************************************************************/

main ()
{
   int i;

   printf ("Testing loop control variable values...........\n");
   printf ("Before loop. i = %d\n", i);
   for ( i = 0; i < 5; i++ )
      printf ("Within loop. i = %d\n", i);
   printf ("After loop. i = %d\n", i);          /* this is outside the loop */

   printf ("Testing assignment to loop control variable....\n");
   for ( i = 0; i < 5; i++ )
   {
      if ( i == 1 )
         i = 4;
      printf ("Within loop. i = %d\n", i);
   } /* for */

   printf ("Testing use of break in loop...................\n");
   for ( i = 0; i < 5; i++ )
   {
      if ( i == 2 )
         break;
      printf ("Within loop. i = %d\n", i);
   } /* for */

   printf ("Testing use of continue in loop................\n");
   for ( i = 0; i < 5; i++ )
   {
      if ( i == 2 )
         continue;
      printf ("Within loop. i = %d\n", i);
   } /* for */
} /* main */
