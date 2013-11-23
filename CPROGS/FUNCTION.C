/*****************************************************************************/
/* Test program :                                                            */
/*      This program illustrates a function using call by reference          */
/*****************************************************************************/

main ()
{
   int i, j;

   printf ("Enter two integers ----->");
   scanf ("%d %d", &i, &j);
   printf ("Before swap : i = %d j = %d\n", i, j);
   swap ( &i, &j );
   printf ("After swap : i = %d j = %d\n", i, j);
} /* main */

swap ( x, y )
int *x, *y;
{
   int temp;

   temp = *x;
   *x   = *y;
   *y   = temp;
} /* swap */
