#include <iostream.h>

// this creates the class queue
class queue 
	{
	int 		q[100];
	int 		idnum,
            sloc,
				rloc;
	public:
	queue(int id); 	// constructor
	~queue(void);     // destructor
	void qput(int i);
	int qget(void);
	};
// constructor function

queue::queue(int id)
	{
	sloc=0;
	rloc=0;
   idnum=id;
	cout << "queue #" << idnum << " initialized!\n" ;
	}

queue::~queue(void)
	{
	cout << "queue #" << idnum << " blasted...\n";
	}

void queue::qput(int i)
	{
	if (sloc==100)
		{
		cout << "queue full!";
		return;
		}
	sloc++;
	q[sloc] = i;
	}

int queue::qget(void)
	{
	if (rloc==sloc)
		{
		cout << "queue underflow (by golly!)";
		return 0;
		}
	rloc++;
	return q[rloc];
	}
main (void)
	{
	queue a(1),
         b(2);
 
	a.qput(10);
	b.qput(19);
	a.qput(20);
	b.qput(1);


   
	cout << a.qget() << " ";
	cout << a.qget() << " ";
	cout << b.qget() << " ";
	cout << b.qget() << "\n";
	}
