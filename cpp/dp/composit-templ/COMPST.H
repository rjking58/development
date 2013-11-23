
#ifndef _Composite_
#define _Composite_

#include <afxcoll.h>
#include <afxtempl.h>
#include <iostream.h>

#include <assert.h>

#define	TEMPLATED_VAL 1

#if TEMPLATED_VAL > 0						  
template <class T>
#endif
class Val
{
	
public:

	Val()  : mParent(0)
	{
	}

	virtual ~Val()
	{
	}
	
	virtual Val *	GetComposite() 
	{ 
		return 0; 
	}
	
	Val * 		 	GetParent() 
	{ 
		return mParent; 
	}
	
	// only valid for valrec objects.
#if TEMPLATED_VAL > 0						  
	virtual T & GetValRec()
#else
	virtual CWordArray & GetValRec()
#endif
	{
#if TEMPLATED_VAL > 0
		T temp;
#else 
		CWordArray temp;
#endif
		assert(FALSE);
		return temp;
	}
	

	// only valid for valreccomposite objects.
	virtual void				Add(Val * Val_o)
	{
		assert(FALSE);
	}
	virtual void				Remove(Val * Val_o)
	{
		assert(FALSE);
	}
	virtual int					GetCOMPCount()
	{
		assert(FALSE);
		return 0;
	}
	virtual Val *				GetFirstChild()
	{
		assert(FALSE);
		return 0;
	}
	virtual Val *				GetNextChild()
	{
		assert(FALSE);
		return 0;
	}
	virtual BOOL				IsLastChild()
	{
		assert(FALSE);
b		return 0;
	}
	
	
protected:
	
	Val * mParent;
};

#if TEMPLATED_VAL > 0						  
template <class T>								 
class ValRec : public Val<T>
#else
class ValRec : public Val
#endif
{
public:
	ValRec()
	{
	}
	
#if TEMPLATED_VAL > 0						  
	T & GetValRec()
#else
	CWordArray & GetValRec()
#endif
	{
		return mVals;
	}
	
private:	
	
#if TEMPLATED_VAL > 0						  
	T mVals;
#else
	CWordArray mVals;
#endif	
};

	 
	 
#if TEMPLATED_VAL > 0						  
template <class T>
class ValRecComposite : public Val <T>
#else
class ValRecComposite : public Val 
#endif
{

#if TEMPLATED_VAL > 0						  
	CTypedPtrArray<CPtrArray, Val<T> *> _ValMap;
#else
	CTypedPtrArray<CPtrArray, Val *> _ValMap;
#endif	
	int	m_Count;
	int	position;
	
public:
	ValRecComposite()
								:	m_Count(0), position(0)
								{ }
								
	virtual						~ValRecComposite()
	{
		int ElementCount = _ValMap.GetSize();
	
		while(ElementCount > 0)
		{
			ElementCount--;
			delete _ValMap[ElementCount];
			_ValMap.RemoveAt(ElementCount);
		}
		cout << "Deleting ValRecComposite!!";
	}
#if TEMPLATED_VAL > 0						  
	virtual Val<T> *			GetComposite()
#else
	virtual Val *				GetComposite()
#endif	
	{
		return(this);
	}
#if TEMPLATED_VAL > 0						  
	virtual void				Add(Val<T> * Val_o)
#else
	virtual void				Add(Val * Val_o)
#endif	
	{
		_ValMap.Add(Val_o);
		m_Count = _ValMap.GetSize();
	}
#if TEMPLATED_VAL > 0						  
	virtual void				Remove(Val<T> * Val_o)
#else
	virtual void				Remove(Val * Val_o)
#endif	
	{
		int ElementCount = _ValMap.GetSize();
		BOOL Done = FALSE;
	
		while(		(ElementCount > 0	)
				&& 	(!Done				)		)
		{
			ElementCount--;
			if(_ValMap[ElementCount] == Val_o)
			{
				_ValMap.RemoveAt(ElementCount);
				Done = TRUE;
			}
		}
	
	}
	virtual int					GetCOMPCount()
	{
		return _ValMap.GetSize();
	}
#if TEMPLATED_VAL > 0						  
	virtual Val<T> * 				GetFirstChild()
#else
	virtual Val * 					GetFirstChild()
#endif	
	{
		position = 0;
		return _ValMap[position];
	}
#if TEMPLATED_VAL > 0						  
	virtual Val<T> * 				GetNextChild()
#else
	virtual Val * 					GetNextChild()
#endif	
	{
		if((position+1) < m_Count)
			position++;
		return _ValMap[position];
	}
	virtual BOOL				IsLastChild()
	{
		return ((position+1) >= m_Count);
	}
								


};


#endif