/*****************************************************************************/
/* Test program :                                                            */
/*      This program illustrates the behaviour of pointers.                  */
/*****************************************************************************/

main ()
{
   int i, j,   /* integers                           */
       *p,     /* a pointer to integers              */
       **p_p;  /* a pointer to a pointer to integers */

   i = 10;
   j = 20;
   p = &i;
   p_p = &p;
   printf ("i = %u\n", i);
   printf ("j = %u\n", j);
   printf ("p.addr = %u\n",p);
   printf ("p.content = %u\n", *p);
   printf ("p_p.addr = %u\n",p_p);
   printf ("p_p.content = %u\n", *p_p );
   printf ("p_p.content.content = %u\n", **p_p);

   i = 100;
   printf ("i = %u\n", i);
   printf ("j = %u\n", j);
   printf ("p.addr = %u\n",p);
   printf ("p.content = %u\n", *p);
   printf ("p_p.addr = %u\n",p_p);
   printf ("p_p.content = %u\n", *p_p );
   printf ("p_p.content.content = %u\n", **p_p);

   p = &j;
   printf ("i = %u\n", i);
   printf ("j = %u\n", j);
   printf ("p.addr = %u\n",p);
   printf ("p.content = %u\n", *p);
   printf ("p_p.addr = %u\n",p_p);
   printf ("p_p.content = %u\n", *p_p );
   printf ("p_p.content.content = %u\n", **p_p);

} /* main */
