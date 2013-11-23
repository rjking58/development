#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TEMP_FACTOR 0.9
#define YES  1
#define NO    0
#define REVERSE      	 1
#define TRANSPOSE 	 0
#define NUMLISTITEMS 200	// NUMBER OF ITEMS ON THE LIST. CHANGE 
							// THIS NUMER TO SUIT YOUR APPLICATION.

//#define ALEN(a,b,c,d) sqrt(((b)-(a))*((b)-(a))+((d)-(c))*((d)-(c)))
inline float ALEN(	float a,
					float b,
					float c,
					float d)
{
	return (float) sqrt((((b-a)*(b-a))+((d-c)*(d-c))));
}

struct ListElement
{ 
	// DEFINE YOUR DATA STRUCTURE HERE. WE'VE ASSUMED SOMETHING
	// LISTED IN CARTESIAN COORDINATES.  IF YOU'RE DATA IS NOT IN 
	// THESE COORDINATES, YOU WILL NEED TO MODIFY THIS STRUCTURE 
	// AND ALSO MAKE THE NECESSARY CHANGES IN THE ENERGY FUNCTION.
   
	float x;
	float y;
};

int CHECKBEST = NO;
float BESTENERGY;
struct ListElement **bestList;




void main(void)
{	
	struct ListElement	**list;
	int					runLimit, 
						sucLimit, 
						numListItems, 
						i, 
						numSuc;
	int					Anneal(	struct ListElement	**list, 
								int listSize, 
								int runLimit, 
								float temperature, 
								int sucLimit, 
								int numListItems);
	float				temperature, 
						energy;
	struct ListElement	**setup(float	*energy, 
								float	*temperature, 
								int		*runLimit, 
								int		*sucLimit, 
								int		numListItems);
	FILE				*outFile, 
						*energyFile;
	void				printList(	FILE				*outFile,
									struct ListElement	**list, 
									int					numListItems);
	
	float				GetEnergy(struct ListElement	**list, 
									int					numListItems);
	float				ener;
	
	numListItems = NUMLISTITEMS;

	list = setup(	&energy, 
					&temperature, 
					&runLimit, 
					&sucLimit, 
					numListItems);

	outFile = fopen("InitList.dat","w");
	printList(outFile,list, numListItems);
	fclose(outFile);
	
	energyFile = fopen("energy.dat", "w");
	fprintf(energyFile,"Temp\tEnergy\tnumSuc\n");
	
	for(i = 1; i < numListItems; i++)
	{	
		numSuc = Anneal(list, 
						numListItems, 
						runLimit, 
						temperature, 
						sucLimit, 
						numListItems);
		ener = GetEnergy(	list,
							numListItems);
		
		printf("%f\t%f\t%d\n",temperature,ener,numSuc);
		fprintf(energyFile,"%f\t%f\t%d\n",temperature,ener,numSuc);
		

			/* Start checking for the best solution?*/

		if(		(numSuc <= runLimit*0.01 )
			&&	(CHECKBEST == NO		 )		) 
		{
			CHECKBEST = YES;
			BESTENERGY = ener;
		}
		
		if(numSuc == 0) 
			break;

		temperature *= (float) TEMP_FACTOR;
	}

	fclose(energyFile);
	
	outFile = fopen("FinalList.dat","w");
	printList(outFile,list, numListItems);
	fclose(outFile);
	
	outFile = fopen("BestList.dat","w");
	printList(outFile,bestList,numListItems);
	fclose(outFile);
	
	outFile = fopen("lowestEnergy.dat","w");
	fprintf(outFile,"Lowest Energy = %f\n",BESTENERGY); /* Store energy. */
	fclose(outFile);
					
					
}


void printList(FILE					*outFile,
			   struct ListElement	**list, 
			   int					numListItems)
{
	int i;
	
	for(i=0; i< numListItems; i++)
		fprintf(outFile,"%f\t%f\n",list[i]->x,list[i]->y);
}


struct ListElement **setup(float	*energy, 
						   float	*temperature, 
						   int		*runLimit, 
						   int		*sucLimit, 
						   int		numListItems)
{	
	struct	ListElement **CreateInitialList( int numListItems);
	struct	ListElement **list;
	float	GetEnergy(	struct ListElement	**list, 
						int					numListItems);

	list = CreateInitialList(numListItems);
	*energy = GetEnergy(list, numListItems);
	*temperature = *energy/numListItems;
	*runLimit = 100 * numListItems;
	*sucLimit = 10 * numListItems;

	return list;
}

struct ListElement **CreateInitialList( int numListItems)
{	
	int					i;
	struct ListElement	**list;

	void InitializeElement(struct ListElement *element);
	
	// Allocate memory for the array of pointers.
	list = (struct ListElement **)malloc(sizeof(struct ListElement *) * numListItems);
	bestList = (struct ListElement **)malloc(sizeof(struct ListElement *) * 
		numListItems);
	
		/* Create the data structures and install pointers to them into the list. */
	for(i = 0; i < numListItems; i++)
		list[i] = (struct ListElement *)malloc(sizeof(struct ListElement));

	for(i = 0; i < numListItems; i++)		/* Set initial values. */
		InitializeElement(list[i]);
		
	return list;
}

void InitializeElement(struct ListElement *element)
{
	/* NOTE: YOU WILL HAVE TO CHANGE THIS FUNCTION. THIS 
	FUNCTION SETS THE INITIAL VALUES IN THE DATA STRUCTURE. 
	HERE WE JUST SET THE COORDINATES TO NUMBERS BETWEEN ZERO 
	AND 100. */

	element->x = (float)rand()/RAND_MAX * 100;
	element->y = (float)rand()/RAND_MAX * 100;
}


float GetEnergy(struct ListElement	**list, 
				int					numListItems)
{	int i;
	float ener; 
	float energy(	struct ListElement	**list, 
					int				   	v1, 
					int				   	v2);

	for(ener = (float) 0.0, i = 0; i < numListItems - 1; i++)
		ener += energy(list, i, i+1);

	return ener;
}

/* THIS FUNCTION CARRIES OUT THE ANNEALING PROCEDURE.  */

int Anneal(	struct ListElement	**list, 
			int listSize, 
			int runLimit, 
			float temperature, 
			int sucLimit, 
			int numListItems)
{
	int numSuc, 
		start, 
		end, 
		insertPoint, 
		alteration, 
		i, 
		j;
	int Oracle(float Edif, 
			   float temperature);
	int PickAlteration();
	float Ediff;
	float EnergyDif(ListElement		**list, 
					int				start, 
					int				end, 
					int				insertPoint, 
					int				listSize, 
					int				alteration);
	void GetSegment(int *start, 
					int *end, 
					int *insertPoint, 
					int listSize);
	void AlterList(struct ListElement	**list, 
				   int					start, 
				   int					end, 
				   int					insertPoint, 
				   int					alteration, 
				   int					listSize);
//	FILE *bestFile;
	
	float GetEnergy(struct ListElement	**list, 
		  			int					numListItems);
	float ener;
	
	numSuc = 0;

	for(i = 0; i < runLimit; i++){
		GetSegment(&start, &end, &insertPoint, numListItems);
		
		alteration = PickAlteration();
		Ediff = EnergyDif(list, start, end, insertPoint, numListItems, alteration);
		
		
		if(Oracle(Ediff, temperature) == YES){
			AlterList(list,start,end, insertPoint, alteration, numListItems);
			numSuc++;
			if(CHECKBEST == YES) {
				ener = GetEnergy(list,numListItems);
				if(ener < BESTENERGY) {		/* Save best list. */
					BESTENERGY = ener;
					for(j = 0; j < numListItems; j++) bestList[j] = list[j];	
				}
			}
		}

		if(numSuc >= sucLimit) break;
		
	}

	return numSuc;
}


/* THIS FUNCTION DECIDES IF A NEW PATH SHOULD BE KEPT. */

int Oracle(float Edif, 
		   float temperature)
{

	if(Edif < 0.0 || exp(-Edif/temperature) > (double)rand()/RAND_MAX) return YES;

	return NO;
}


/* THIS FUNCTION DECIDES WHETHER TO TRY REVERSING THE PATH OR
TRANSPOSING IT.  */

int PickAlteration(void)
{
	if((double)rand()/RAND_MAX < 0.5) return REVERSE;
	
	return TRANSPOSE;
}


/* THIS FUNCTION SELECTS A SEGMENT FOR POSSIBLE ALTERATION. */
void GetSegment(int *start, 
				int *end, 
				int *insertPoint, 
				int listSize)
{	int shuffle[3], done = NO, i, j, hold;
	
	do{		/* Select three different numbers between 0 and listSize - 1 */
		for(i = 0; i <3; i++)
			shuffle[i] = (int)(((float)rand()/RAND_MAX)*(listSize - 1));
	
		if(shuffle[0] == shuffle[1] ||   /* Make sure no two are the same. */
		    shuffle[0] == shuffle[2] || 
 		    shuffle[1] == shuffle[2]) ;
		else done = YES;

	}while(done == NO);


	/* Sort these numbers. */

	for(i = 0; i < 3; i++){
		for(j = i + 1; j < 3; j++){
			if(shuffle[i] > shuffle[j]){
				hold = shuffle[i];
				shuffle[i] = shuffle[j];
				shuffle[j] = hold;
			}
		}
	}

	/* Decide whether to set the insertPoint above or below the block to be altered. */

	if((double)rand()/RAND_MAX < 0.5 || shuffle[2] - 1 == shuffle[1]){
		*insertPoint = shuffle[0];
		*start = shuffle[1];
		*end = shuffle[2];
	}
	else{
		*start = shuffle[0];
		*end  = shuffle[1];
		*insertPoint = shuffle[2];
	}
}


float EnergyDif(ListElement		**list, 
				int				start, 
				int				end, 
				int				insertPoint, 
				int				listSize, 
				int				alteration)
{
	float trans_cost(struct ListElement		**list,
					 int					start,
					 int					end,
					 int					insertPoint,
					 int					listSize);
	float reverse_cost(struct ListElement	**list,
					   int					start,
					   int					end,
					   int					listSize);

	switch(alteration)
	{
		case TRANSPOSE:
		return trans_cost(list,start,end,insertPoint,listSize);

		case REVERSE:
		return  reverse_cost(list,start,end,listSize);
	}

	return (float) 0.0;
}


float trans_cost(struct ListElement		**list,
				 int					start,
				 int					end,
				 int					insertPoint,
				 int					listSize)
{	
	float cost; 
	float energy(	struct ListElement	**list, 
					int				   	v1, 
					int				   	v2);

	cost = (float) 0.0;
					/* Break the current connections. */
	
	if(start > 0) cost -= energy(list, start-1, start);
	if(end < listSize - 1) cost -= energy(list, end, end+1);
	if(insertPoint > 0) cost -= energy(list,insertPoint, insertPoint -1);

					/* Build the new connections. */

	cost += energy(list, insertPoint , end);
	if(insertPoint - 1 >= 0 ) cost += energy(list,insertPoint - 1, start);
	if(start > 0 && end < listSize - 1 )
		 cost += energy(list, start - 1, end + 1);

	return cost/listSize;
}

float reverse_cost(struct ListElement	**list,
				   int					start,
				   int					end,
				   int					listSize)
{	float cost;
	float energy(	struct ListElement	**list, 
					int				   	v1, 
					int				   	v2);

	cost = (float) 0.0;

					/*Subtract the old cost. */

	if(start > 0) cost -= energy(list, start - 1, start);
	if(end < listSize- 1) cost -= energy(list,end,end+1);


					/* Add the new cost.  */

	if(start > 0) cost += energy(list,start - 1, end);
	if(end < listSize-1) cost += energy(list,start,end+1);

	return cost/listSize;

}


float energy(	struct ListElement	**list, 
				int				   	v1, 
				int				   	v2)
{
	/* YOU MUST CHANGE THIS FUNCTION TO CALCULATE THE 
	THE "ENERGY" BETWEEN TWO ELEMENTS IN YOUR LIST.  HERE WE 
	JUST CALCULATE THE PATH LENGTH BETWEEN TWO POINTS ON A 
	PLANE */
			
	return  (float)ALEN(list[v1]->x,list[v2]->x,list[v1]->y,list[v2]->y);

}


void AlterList(struct ListElement	**list, 
			   int					start, 
			   int					end, 
			   int					insertPoint, 
			   int					alteration, 
			   int					listSize)
{	struct ListElement *holder, **dumList;
	int i, j;

	switch(alteration)
	{	case REVERSE:
		for(i = start, j = end; i < j; i++, j--){
			holder = list[i];
			list[i] = list[j];
			list[j] = holder;
		}
		return;


		case TRANSPOSE:
		dumList = (struct ListElement **)malloc(sizeof(struct ListElment 
				*)*listSize);
		
		for(j = 0, i = start; i <= end; i++, j++)	/* Copy group. */
			dumList[j] = list[i];

		if(insertPoint > end){				/* Move downward. */
		   for(j=end+1, i = start; j < insertPoint; i++, j++)
			list[i] = list[j];

		    for(j = insertPoint - (end - start + 1), i = 0; j < insertPoint; i++, j++)
			list[j] = dumList[i];			/* Reinstall group. */
		}
		else {
		   for(j=start - 1, i = end; j >= insertPoint; i--, j--)
			list[i] = list[j];				/* Move upward. */

		    for(j = insertPoint, i = 0; i <= (end - start); i++, j++)
			list[j] = dumList[i];

		}
		
		free(dumList);
		
		return;
	}
	
	
}

