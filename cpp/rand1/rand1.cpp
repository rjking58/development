#include <iostream.h>
#include <stdlib.h>
#include <time.h>



// #include <stdlib.h>
// #include <stdio.h>
// #include <time.h>
// 
// void main( void )
// {
//    int i;
// 
//    /* Seed the random-number generator with current time so that
//     * the numbers will be different every time we run.
//     */
//    srand( (unsigned)time( NULL ) );
// 
//    /* Display 10 numbers. */
//    for( i = 0;   i < 10;i++ )
//       printf( "  %6d\n", rand() );
// }



class RandomArr // n number of unique random numbers...
{
	public:
		RandomArr (	unsigned long 	init_RandCnt, // how many...
						unsigned long 	RandRng		) // maximum size for random number.
		{	
			unsigned int	ofst;
			unsigned long 	a_random;


			m_RandCnt 			= init_RandCnt;
			m_Elements_added	= 0;
			m_Curr_RandOfst	= 0;

			if (RandRng < init_RandCnt)
			{
				cout << "not possible to create %d unique numbers in the range" << endl;
				cout << init_RandCnt << " to " << RandRng;
				// this is the worst way to exit.. but HEY, this is just a test class.
				exit(0);
			}
			
			m_RandArr = new unsigned long [init_RandCnt];
			if ( m_RandArr == NULL)
			{
				// this is the worst way to exit.. but HEY, this is just a test class.
				cout << "bad memory allocation!" << endl;
				exit(0);		
			}

			srand( 211 ); // a convenient prime...


			a_random = (long) rand() % RandRng;
			for (ofst = 0; ofst < m_RandCnt; ofst++)
			{
				while(		(m_Elements_added != 0)
						&& 	IsNotUnique(a_random) ) 
					a_random = (long) rand() % RandRng;
						
				m_RandArr[ofst] = a_random;
				m_Elements_added++;
				a_random = (long) rand() % RandRng;
			}	
		}
		~RandomArr()
		{
			delete[] m_RandArr;
		}
		
		// access is READ ONLY
		unsigned long operator[](unsigned long ofst) const
		{
			if (ofst >=m_Elements_added)
			{
				cout << "access out of range" << endl;
				exit(0);
			}
			return m_RandArr[ofst];
		}

		unsigned long GetNext() 
		{  
			unsigned int prev_RandOfst = m_Curr_RandOfst;
			
			m_Curr_RandOfst 					= (++m_Curr_RandOfst) % m_RandCnt;
			
			return m_RandArr[prev_RandOfst];
		}

	protected:
		unsigned int			m_Curr_RandOfst;
		unsigned long			m_RandCnt;
		unsigned long 			*m_RandArr;
		unsigned int		   m_Elements_added;

		int	IsNotUnique(unsigned long num)
		{
			unsigned int 	x;
			
			if (m_Elements_added)
			{
				for (x = 0; x < m_Elements_added; x++)
				{
					if (m_RandArr[x] == num)
						return 1;
				}
			}
			return 0;
		}
};


class GenerateConstCPP
{
	public:	
		GenerateConstCPP()
	private:
		GenerateConstCPP()	

}


void main(void)
{
	RandomArr Rnd1(1000,1000);

	int x;
	int y;
	
	for (x = 0 ; x < 999; x++)
	{
		for (y = x+1; y < 1000; y++)
		{
			if(Rnd1[x] == Rnd1[y])
			{
				cout << "NOT UNIQUE" << endl;
				exit(0);
			}
		}
	   
	}
	cout << "passed unique test" << endl;
									  
}

