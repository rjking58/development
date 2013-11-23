/*	Eratosthenes Sieve Prime Number Program in C, Byte January 1983.
 *	The code has been corrected to produce primes correctly.
*/
#include <stdio.h>

#define TRUE	1
#define FALSE	0
#define NITER	1
#define SIZE	6000

char its_a_prime[SIZE+1]={0};
char not_prime;

main ()
{
  register int i,k;
  int iterations, count_of_primes;

  printf ("%d iterations: ", NITER);

  /* Do sieve once */
  for( iterations = 1; iterations <= NITER; iterations++ )     
  {
    count_of_primes = 0;
    for( i = 0; i <= SIZE; i++)     /* set all flags true */
      its_a_prime[i] = TRUE;

    for( i = 2; i <= SIZE; i++ )
    {
      if ( its_a_prime[i] )        /* found a prime */
      {
        for ( k = i + i; k <= SIZE; k += i )
          its_a_prime[k] = FALSE;   /* Cancel its multiples */
        count_of_primes++;
      }
    }
  }
   
  for (i = 2; i <= SIZE; i++)
  {
    printf("%d" ,i); 
    if(its_a_prime[i])
    {
      printf(" s");
    }
    else
    {
      printf("  ");
    }
    /* verify */
    not_prime = FALSE;
    k = 2;
    while( (k < i) && (not_prime == FALSE))
    {
      if( (i % k) == 0 )
      {
        not_prime = TRUE; 
      }
      k++;
    }
    if( not_prime == TRUE )
    {
     printf(" \n");
    }
    else
    {
     printf("v\n");
    }
  }
  printf ("\n%d primes\n", count_of_primes);
  exit(0);

}
