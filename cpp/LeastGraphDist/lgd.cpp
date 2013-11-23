//Weighted graph depth first search..

// our adj. node.

#include "pq.cpp" // !!!
#include <iostream.h>
void visit(int currVisitNode);


struct node 
{
	node(int v, int w)
	:	vertex(v),
		weight(w),
		next(0)
	{
	}
  	int vertex;
	int weight;
	struct node *next;
	bool	isLesserPriority(node *i)
	{
		return (weight < i->weight);
	}
	bool 	isSamePriority(node *i)
	{
		return (weight == i->weight);
	}
	
	bool 	isEqual(node *i)
	{
		return (vertex == i->vertex);
	}
	void	SetPriority(int p)
	{
		weight = p;
	}
	int		GetPriority()
	{
		return weight;
	}
};

const int UNSEEN = -10000;
const int maxV = 500;

int V = 7;

struct InpVs
{
	int v1;
	int v2;
	int w;
}	InvVList[] = {	{1,2,1},
						{1,6,2},
						{1,7,6},
						{2,3,1},
						{2,4,2},
						{2,5,4},
						{3,5,4},
						{4,5,2},
						{6,4,1},
						{6,5,2},
						{7,5,1},
						{-1,-1,-1}	};






struct node *adj[maxV];
struct node *z;

void adjlist()
{
	struct node *t;
	int j;

	z = new node(0,0);
	z->next = z;
	for (j = 1; j <=7; j++)	// for now.
	{
		adj[j] = z;	// start out w/ empty lists.
	}
	j = 0;
	while (InvVList[j].v1 > 0)
	{
		// make it ...
		t = new node(InvVList[j].v1,InvVList[j].w);
		// show the place that is adjacent..
		// link it up..
		t->next = adj[InvVList[j].v2];
		adj[InvVList[j].v2] = t;
		t = new node(InvVList[j].v2,InvVList[j].w);
		t->next = adj[InvVList[j].v1];
		adj[InvVList[j].v1] = t;
		j++;
	}
}


int val [500];
int dad [500];

PQ<node> pq(maxV);

void search()
{
	int k;
	for (k = 1; k <= V; k++)
	{
		val[k] = UNSEEN;
	}
	for (k = 1; k <= V; k++)
	{
		if (val[k] == UNSEEN)
		{
			visit(k);
		}
	}
	for (k = 1; k <= V; k++)
	{
		cout << (char) ('A' + (k-1)) << " ";
	}
	cout << endl;
	for (k = 1; k <= V; k++)
	{
		cout << (char) ('A' + (dad[k] -1)) << " ";
	}


	cout << endl << "Operations:" << pq.getOperations() << endl;
}


void visit(int currVisitNode)
{
	struct node *t;
	struct node *removedNode;
	
	if (pq.insert(new node(currVisitNode,-UNSEEN)))
	{
		dad[currVisitNode] = 0;
	}
	
	while(!pq.empty())
	{
//		id++;
		removedNode = pq.remove();
		currVisitNode = removedNode->vertex;
		val[currVisitNode] = -val[currVisitNode];
		// this picks up the beginning of tree condition..
		if (val[currVisitNode] == -UNSEEN)
		{
			val[currVisitNode] = 0;
		}
		for (t = adj[currVisitNode]; t != z; t = t->next)
		{
			if (val[t->vertex] < 0)
			{
				if (pq.insert(new node(t->vertex, val[currVisitNode] + t->weight)))
				{
					val[t->vertex] = -(val[currVisitNode] + t->weight);
					dad[t->vertex] = currVisitNode;
				}
			}
		}
	}
}

main()
{
	adjlist();
	search();
}