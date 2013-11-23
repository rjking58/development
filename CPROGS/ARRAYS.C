/*****************************************************************************/
/* Test program :                                                            */
/*      This program illustrates the behaviour of arrays.                    */
/*****************************************************************************/

main ()
{
   int i, a[5];

   for ( i = 0; i < 5; i++ )
      a[i] = i;
   for ( i = -3; i < 9; i++ )
      printf ("i = %d a[i] = %d\n", i, a[i]);
   array_add ( a );

} /* main */

array_add ( array )
int array[10];          /* this array size has no significance at all */
{
   int i;

   for ( i = 0; i < 5; i++ )
      printf ("i * 2 = %d\n", i*2);
} /* array_add */
