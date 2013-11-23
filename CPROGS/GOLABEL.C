/*****************************************************************************/
/* Test program :                                                            */
/*      This program illustrates an unsafe "goto" statement.                 */
/*****************************************************************************/

main ()
{
   int i;

   goto here;
   for ( i = 0; i < 5; i++ )
   {
      printf ("Within loop.");
      here : printf ("i = %d\n", i);
   } /* for */

   goto there;
   if (1)
   {
      int j;
      j = i;
      there : printf ("Within block.");
      printf ("i = %d j = %d\n", i, j);
   } /* if */
} /* main */
