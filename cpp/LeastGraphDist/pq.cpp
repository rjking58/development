#include <assert.h>

// must implement these in class to be used by PQ..
// class ItemType
// {
// 	virtual bool	isLesserPriority(ItemType *) = 0;
//		virtual bool 	isSamePriority
// 	virtual bool 	isEqual(ItemType *) = 0;
// 	virtual void	SetPriority(int) = 0;
// 	virtual int		GetPriority() = 0;
// };

template <class T>
class PQ
{
	private:
		T **mItems;
		int mMaxItems;
		int mLastItemIndex;
		int mOperations;
		
		void insertNoCheck(T *v)
		{
			if(mLastItemIndex < mMaxItems)
			{
				mItems[mLastItemIndex] = v;
				mLastItemIndex++;
			}
			else
			{
			  	assert(0); // !!
			}
			
		}
	public:
		PQ(int max=500)
		:	mMaxItems(max),
			mLastItemIndex(0),
			mOperations(0)
		{
			mItems = new T * [max];
			for (int x = 0; x < max; x++)
			{
				mItems[x] = 0;
			}

		}
		~PQ()
		{
			delete [] mItems;
		}
		
		int getOperations() { return mOperations; }
		bool empty()
		{
			return mLastItemIndex == 0;
		}
		
		T * remove()
		{
			int 		currTestItem;
			int 		smallestItemFound = 0;
			T			*temp;
			
			mOperations++;
			
			if (mLastItemIndex)
			{
				
				for (	currTestItem=1;
						currTestItem < mLastItemIndex; 
						currTestItem++)
				{
					if (mItems[currTestItem]->isLesserPriority(mItems[smallestItemFound]))
					{
						smallestItemFound = currTestItem;
					}
				}
				// last to temporary..
				temp = mItems[mLastItemIndex - 1];
				// take max and put it into the last slot
				mItems[mLastItemIndex - 1] = mItems[smallestItemFound];
				// take our saved off temp and store it
				// where the max USED TO BE
				mItems[smallestItemFound] = temp;
			
			}
			else
			{
				assert(0);
			}
			mLastItemIndex--;
			return mItems[mLastItemIndex];
		}
		// returns true if inserted/changed, false if not.
		bool insert(T * item)
		{
			int 	currTestItem;
			bool 	found = false;
			bool  retval = true;
			
			mOperations++;				 
				 
			for (	currTestItem=0	;
					(		(currTestItem < mLastItemIndex)
						&&	(! found		)); 
					currTestItem++		)
			{
				if (mItems[currTestItem]->isEqual(item))
				{
					found = true;
				}
			}
			if (! found)
			{
				insertNoCheck(item);
			}
			else
			{
				// found... are the priorities the same??
				if (! mItems[currTestItem]->isSamePriority(item))
				{
					mItems[currTestItem]->SetPriority(item->GetPriority());
				}
				else
				{
					retval = false;
				}
				
				delete item;
			}
			return retval;
		}
};
