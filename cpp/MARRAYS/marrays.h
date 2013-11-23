// Copyright Treasury Services Corp, 1994, All Rights Reserved                                                   */
// Richard King, 1996
// MARRAYS.H  Template for mixed int/huge dynamic array  
//				this array implementation supports up to 2^15 * elements stored in an indirect array...

#if !defined( __MARRAYS_H )
#define __MARRAYS_H

#if defined( UNIX )

	#include <arrays.h>

	#define BIM_ArrayAsVector BI_ArrayAsVector
	#define BIM_IArrayAsVector BI_IArrayAsVector
	#define BIM_ISArrayAsVector BI_ISArrayAsVector

#else

#define TEMPLATES
#include <windows.h>

#if !defined( __DEFS_H )
#include <_defs.h>
#endif  // __DEFS_H

#if !defined( __RESOURCE_H )
#include <Resource.h>
#endif  // __RESOURCE_H

#if !defined( __COLLECT_H )
#include <Collect.h>
#endif  // __COLLECT_H

#if !defined( __MEM_H )
#include <Mem.h>
#endif  // __MEM_H

#if !defined( __MVECTIMP_H )
#include <MVectImp.h>
#endif  // __MVECTIMP_H

#if !defined( __SORTABLE_H )
#include <Sortable.h>
#endif  // __SORTABLE_H

#if !defined( __ABSTARRY_H )
#include <AbstArry.h>
#endif  // __ABSTARRY_H

#pragma option -Vo-
#if defined( __BCOPT__ ) && !defined( _ALLOW_po )
#pragma option -po-
#endif

#pragma warn -ncf

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class Vect, class T> class BIM_ArrayAsVectorImp              */
/*                                                                        */
/*  Implements the fundamental array operations, using a vector           */
/*  as the underlying implementation.  The type Vect specifies the        */
/*  form of the vector, either a BIM_CVectorImp<T0> or a                   */
/*  BIM_IVectorImp<T0>.  The type T specifies the type of the              */
/*  objects to be put in the array.  When using BIM_CVectorImp<T0>,        */
/*  T should be the same as T0. When using BIM_ICVectorImp<T0>, T          */
/*  should be of type polonger to T0.  See BIM_ArrayAsVector and            */
/*  BIM_IArrayAsVector for examples.                                       */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class Vect, class T>
class _CLASSTYPE BIM_ArrayAsVectorImp
{

public:

	 BIM_ArrayAsVectorImp( int upper, int lower, int delta ) :
		  vect_imp( upper-lower+1,delta),
		  lowerbound(lower)
		  {
		  }

	 int lowerBound() const
		  {
		  return lowerbound;
		  }

	 int upperBound() const
		  {
		  return boundBase(vect_imp.limit())-1;
		  }

	 int arraySize() const
		  {
		  return vect_imp.limit();
		  }

	 void add( T t )
		  {
		  vect_imp.add( t );
		  }

	 void addAt( T t, int loc )
		  {
		  vect_imp.addAt( t, zeroBase(loc) );
        }

	 void detach( T t, TShouldDelete::DeleteType dt = TShouldDelete::NoDelete )
        {
        vect_imp.detach( t, dt );
        }

	 void detach( int loc,
					  TShouldDelete::DeleteType dt =TShouldDelete::NoDelete
					)
		  {
		  vect_imp.detach( zeroBase(loc), dt );
		  }

	 void destroy( int i )
		  {
        detach( i, TShouldDelete::Delete );
        }

    void flush( TShouldDelete::DeleteType dt = TShouldDelete::DefDelete )
        {
        vect_imp.flush( dt );
        }

    int isFull() const
		  {
        return vect_imp.getDelta() == 0 && vect_imp.count() >= vect_imp.limit();
        }

    int hasMember( T t ) const
        {
        return vect_imp.find(t) != INT_MAX;
		  }

	 int isEmpty() const
		  {
        return vect_imp.count() == 0;
        }

	 int getItemsInContainer() const
		  {
        return vect_imp.count();
		  }

	 T itemAt( int i ) const
		  {
		  return vect_imp[ zeroBase(i) ];
		  }

    int find( const T t ) const
        {
        return boundBase(vect_imp.find( t ));
		  }

	 void reallocate( int sz, int offset = 0 )
        {
        vect_imp.resize( sz, offset );
		  }


	 void setData( int loc, T t )
        {
		  PRECONDITION( loc >= lowerbound && loc <= upperBound() );
        vect_imp[ zeroBase(loc) ] = t;
        }

    void insertEntry( int loc )
        {
        PRECONDITION( loc >= lowerbound && loc <= upperBound() );
		  T t;
        vect_imp.addAt( t, zeroBase(loc) );
        }

	 void removeEntry( int loc )
		  {
		  squeezeEntry( zeroBase(loc) );
        }

    void squeezeEntry( unsigned int loc )
		  {
		  PRECONDITION( loc < vect_imp.count() );
		  vect_imp.detach( loc );
        }

	 unsigned int zeroBase( int loc ) const
		  {
		  return loc - lowerbound;
		  }

	 int boundBase( int loc ) const
        {
		  return loc == INT_MAX ? INT_MAX : loc + lowerbound;
		  }

	 void grow( int loc )
		  {
		  if( loc < lowerBound() )
            reallocate( arraySize() + (loc - lowerbound) );
        else if( loc >= boundBase(vect_imp.limit()) )
            reallocate( zeroBase(loc) );
        }

    int lowerbound;

	 Vect vect_imp;

};


/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BIM_ArrayAsVector                             */
/*                                                                        */
/*  Implements an array of objects of type T, using a vector as           */
/*  the underlying implementation.                                        */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T> class _CLASSTYPE BIM_ArrayAsVector :
	 public BIM_ArrayAsVectorImp<BIM_CVectorImp<T>,T>
{

public:

	//friend class _CLASSTYPE BIM_ArrayAsVectorIterator<T>;

	BIM_ArrayAsVector( int upper, int lower = 0, int delta = 0 ) :
		  BIM_ArrayAsVectorImp<BIM_CVectorImp<T>,T>( upper, lower, delta )
	{
	}

	T& operator []( int loc )
	{
		grow( loc+1 );
		return vect_imp[zeroBase(loc)];
	}

	T& operator []( int loc ) const
	{
		PRECONDITION( loc >= lowerbound && loc < data.count() );
		return vect_imp[zeroBase(loc)];
	}

	void forEach( void (*f)(T &, void *), void *args )
	{
		if( !isEmpty() )
			vect_imp.forEach( f, args );
	}

	T huge *firstThat( int (*f)(const T &, void *),
					  void huge *args
					) const
	{
		if( isEmpty() )
			return 0;
		return vect_imp.firstThat( f, args );
	}

	T huge *lastThat( 	int (* f)(const T &, void *),
						void huge *args
						  ) const
	{
		if( isEmpty() )
			return 0;
		return vect_imp.lastThat( f, args );
	}

};
		  
		  
		  
/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BIM_IArrayAsVector                            */
/*                                                                        */
/*  Implements an indirect array of objects of type T, using a vector as  */
/*  the underlying implementation.                                        */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T> class _CLASSTYPE BIM_IArrayAsVector :
	 public BIM_ArrayAsVectorImp<BIM_ICVectorImp<T>,T  *>,
    public virtual TShouldDelete
{

public:

    friend class _CLASSTYPE BIM_IArrayAsVectorIterator<T>;

	 BIM_IArrayAsVector( int upper, int lower = 0, int delta = 0 ) :
        BIM_ArrayAsVectorImp<BIM_ICVectorImp<T>,T  *>( upper, lower, delta )
        {
		  }

    ~BIM_IArrayAsVector()
        {
        flush();
        }

    T  *  & operator []( int loc )
        {
		  grow( loc+1 );
        return vect_imp[zeroBase(loc)];
        }

	 T  *  & operator []( int loc ) const
        {
        PRECONDITION( loc >= lowerbound && zeroBase(loc) < vect_imp.limit() );
        return vect_imp[zeroBase(loc)];
		  }

    void add( T  *t )
        {
		  BIM_ArrayAsVectorImp<BIM_ICVectorImp<T>,T  *>::add(t);
        }

    void addAt( T  *t, int loc )
        {
		  BIM_ArrayAsVectorImp<BIM_ICVectorImp<T>,T  *>::addAt(t,loc);
        }

	 void detach( int loc, DeleteType dt = NoDelete )
		  {
		  vect_imp.detach( zeroBase(loc), delObj(dt) );
		  }

	 void detach( T  *t, DeleteType dt = NoDelete )
        {
        int loc = vect_imp.find( t );
		  if( loc == INT_MAX )
            return;
		  vect_imp.detach( loc, delObj(dt) );
        }

    void flush( DeleteType dt = DefDelete )
        {
        vect_imp.flush( delObj(dt), vect_imp.limit(), 0 );
        }

	 int find( const T *t ) const
        {
        return boundBase(vect_imp.find( (T *)t ));
        }

	 void forEach( void ( *f)(T  &, void  *), void  *args )
		  {
		  if( !isEmpty() )
				vect_imp.forEach( f, args );
		  }

	 T  *firstThat( int ( *f)(const T  &, void  *),
							  void  *args
							) const
		  {
		  if( isEmpty() )
				return 0;
		  return vect_imp.firstThat( f, args );
		  }

	 T  *lastThat( int ( * f)(const T  &, void  *),
							 void  *args
						  ) const
		  {
		  if( isEmpty() )
				return 0;
		  return vect_imp.lastThat( f, args );
		  }

};

template <class T> class _CLASSTYPE BIM_IArrayAsVectorIterator :
	 public BIM_IVectorIteratorImp<T>
{

public:

	 BIM_IArrayAsVectorIterator( const BIM_IArrayAsVector<T>  &a ) :
		  BIM_IVectorIteratorImp<T>(a.vect_imp) {}

};


/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BIM_ISArrayAsVector                          */
/*                                                                        */
/*  Implements an indirect sorted array of objects of type T, using a     */
/*  vector as the underlying implementation.                              */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T> class _CLASSTYPE BIM_ISArrayAsVector :
    public BIM_ArrayAsVectorImp<BIM_ISVectorImp<T>,T _FAR *>,
    public virtual TShouldDelete
{

public:

    friend class _CLASSTYPE BIM_ISArrayAsVectorIterator<T>;

    BIM_ISArrayAsVector( int upper, int lower = 0, int delta = 0 ) :
        BIM_ArrayAsVectorImp<BIM_ISVectorImp<T>,T _FAR*>( upper, lower, delta )
        {
        }

    ~BIM_ISArrayAsVector()
        {
        flush();
        }

    T *  & operator []( int loc )
        {
        grow( loc+1 );
        return vect_imp[zeroBase(loc)];
        }

    T *  & operator []( int loc ) const
        {
        PRECONDITION( loc >= lowerbound && loc < vect_imp.count() );
        return vect_imp[zeroBase(loc)];
        }

    void add( T *t )
        {
        BIM_ArrayAsVectorImp<BIM_ISVectorImp<T>,T *>::add(t);
        }

    void addAt( T *t, int loc )
        {
        BIM_ArrayAsVectorImp<BIM_ISVectorImp<T>,T *>::addAt(t,loc);
        }

    void detach( int loc, DeleteType dt = NoDelete )
        {
        vect_imp.detach( loc, delObj(dt) );
        }

    void detach( T *t, DeleteType dt = NoDelete )
        {
        unsigned loc = vect_imp.find( t );
        if( loc == UINT_MAX )
            return;
        vect_imp.detach( loc, delObj(dt) );
        }

    void flush( DeleteType dt = DefDelete )
        {
        vect_imp.flush( delObj(dt), vect_imp.limit(), 0 );
        }

    int find( const T *t ) const
        {
        return boundBase( vect_imp.find( (T *)t ) );
        }

    void forEach( void ( *f)(T &, void  *), void  *args )
        {
        if( !isEmpty() )
            vect_imp.forEach( f, args );
        }

    T *firstThat( int ( *f)(const T  &, void  *),
                       void *args
                     ) const
        {
        if( isEmpty() )
            return 0;
        return vect_imp.firstThat( f, args );
        }

    T *lastThat( int ( * f)(const T &, void *),
                      void *args
                    ) const
        {
        if( isEmpty() )
            return 0;
        return vect_imp.lastThat( f, args );
        }

};

template <class T> class _CLASSTYPE BIM_ISArrayAsVectorIterator :
    public BIM_IVectorIteratorImp<T>
{

public:

    BIM_ISArrayAsVectorIterator( const BIM_ISArrayAsVector<T> _FAR &a ) :
        BIM_IVectorIteratorImp<T>(a.vect_imp) {}

};



#pragma warn .ncf

#if defined( __BCOPT__ ) && !defined( _ALLOW_po )
#pragma option -po.
#endif
#pragma option -Vo.

#endif  // UNIX

#endif  // __MARRAYS_H

