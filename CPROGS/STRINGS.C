/*****************************************************************************/
/* Test program :                                                            */
/*      This program illustrates the behaviour of pointers on strings.       */
/*****************************************************************************/

main ()
{
   static char str[] = "This is some sample text for illustration purposes";
   char *p, *q;

   printf ("str = %s\n", str);
   printf ("p = %s\n", p);              /* p is uninitialized */
   printf ("q = %s\n", q);              /* q is uninitialized */

   p = str;
   q = p;
   p += 10;
   printf ("str = %s\n", str);
   printf ("p = %s\n", p);
   printf ("q = %s\n", q);
   printf ("Notice that even though q was assigned p, q is not incremented\n");

   str = "now is the time for all good men to come to the aid of thier country";
   printf ("str = %s\n", str);
   printf ("p = %s\n", p);
   printf ("q = %s\n", q);


} /* main */
