/*****************************************************************************/
/* Test program :                                                            */
/*      This program illustrates the use of "break" in a switch statement.   */
/*****************************************************************************/

main ()
{
   int i;

   printf ("< 1 - 6 > ------> \n");
   scanf ("%d", &i);
   switch (i)
   {
      case 1:
      case 2:
         printf ("Doing common processing for cases 1 and 2.\n");
         break;
      case 3:
         printf ("Doing case 3. No break after this.\n");
      case 4:
         printf ("Doing case 4.\n");
         break;
      case 5:
         {
            printf ("Doing case 5 ( within block ). No break after this.\n");
         } /* case 5 */
      case 6:
         {
            printf ("Doing case 6 ( within block ).\n");
         }
         break;
      default:
         printf ("Doing default processing. Assigning to switch variable.\n");
         printf ("Switch variable was %d.", i);
         i = 3;
         printf ("It is now %d.\n", i);
   } /* switch */
} /* main */
