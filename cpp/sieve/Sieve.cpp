/*	Eratosthenes Sieve Prime Number Program in C, Byte January 1983.
 *	The code has been corrected to produce primes correctly.
*/
#include <stdio.h>
#include <iostream>

const int TRUE	=1;
const int FALSE	=0;
const int NITER	=1;
const int SIZE	=100;

struct prime_compare
{
	prime_compare()
		:	its_a_prime(true),
			verified_prime(false)
	{
	}
	bool its_a_prime;
	bool verified_prime;
};

prime_compare its_a_prime[SIZE+1];
bool is_prime;

void main (void)
{
  register int i,k;
  int iterations, count_of_primes;

  std::cout << NITER << "iterations: " << std::endl;

  for( i = 4; i <= SIZE; i += 2 )
  {
	  its_a_prime[i].its_a_prime = false;
  }

  /* Do sieve once */
  for( iterations = 1; iterations <= NITER; iterations++ )     
  {
    count_of_primes = 0;

    for( i = 2; i <= SIZE; i++ )
//    for( i = 5; i <= SIZE; i += 2 )
    {
      if ( its_a_prime[i].its_a_prime )        /* found a prime */
      {
        for ( k = i + i; k <= SIZE; k += i )
		{
			its_a_prime[k].its_a_prime = FALSE;   /* Cancel its multiples */
		}
        count_of_primes++;
      }
    }
  }
   
  for (i = 2; i <= SIZE; i++)
  {
	std::cout << i;

	if(its_a_prime[i].its_a_prime)
    {
		std::cout << " sieve-prime ";
    }
    else
    {
    	std::cout << "  ";
    }
    /* verify */
    is_prime = true;
    k = 2;
    while( (k < i) && is_prime)
    {
      if( (i % k) == 0 )
      {
        is_prime = false; 
      }
      k++;
    }
    if(is_prime)
    {
		its_a_prime[i].verified_prime = true;
		std::cout << "==prime==" << std::endl;
    }
    else
    {
		its_a_prime[i].verified_prime = false;
		std::cout << "div" << std::endl;
    }
  }
  std::cout << std::endl << count_of_primes << " primes" << std::endl;

  // exceptions...
  std::cout << "doing double check" << std::endl;
  for (i = 2; i <= SIZE; i++)
  {
	  if (its_a_prime[i].verified_prime != its_a_prime[i].its_a_prime) 
	  {
		  std::cout << "this number is bad:" << i << std::endl;
	  }
  }
  std::cout << "double check DONE" << std::endl;
}
