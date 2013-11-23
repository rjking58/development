// Copyright Treasury Services Corp, 1994, All Rights Reserved                                                   */
// Georgui Rekouts, Nov, 1994
// HARRAYS.H  Template for huge dynamic array

#if !defined( __HARRAYS_H )
#define __HARRAYS_H

#if defined( UNIX )

	#include <arrays.h>

	#define BIH_ArrayAsVector BI_ArrayAsVector
	#define BIH_SArrayAsVector BI_SArrayAsVector
	#define BIH_IArrayAsVector BI_IArrayAsVector
	#define BIH_ISArrayAsVector BI_ISArrayAsVector

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

#if !defined( __HVECTIMP_H )
#include "HVectImp.h"
#endif  // __HVECTIMP_H

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
/*  template <class Vect, class T> class BIH_ArrayAsVectorImp              */
/*                                                                        */
/*  Implements the fundamental array operations, using a vector           */
/*  as the underlying implementation.  The type Vect specifies the        */
/*  form of the vector, either a BIH_CVectorImp<T0> or a                   */
/*  BIH_IVectorImp<T0>.  The type T specifies the type of the              */
/*  objects to be put in the array.  When using BIH_CVectorImp<T0>,        */
/*  T should be the same as T0. When using BIH_ICVectorImp<T0>, T          */
/*  should be of type polonger to T0.  See BIH_ArrayAsVector and            */
/*  BIH_IArrayAsVector for examples.                                       */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class Vect, class T>
class _CLASSTYPE BIH_ArrayAsVectorImp
{

public:

    BIH_ArrayAsVectorImp( long upper, long lower, long delta ) :
        data( upper-lower+1,delta),
		  lowerbound(lower)
		  {
		  }

	 long lowerBound() const
		  {
		  return lowerbound;
		  }

	 long upperBound() const
		  {
		  return boundBase(data.limit())-1;
		  }

	 long arraySize() const
		  {
		  return data.limit();
		  }

	 void add( T t )
		  {
		  data.add( t );
		  }

	 void addAt( T t, long loc )
		  {
		  data.addAt( t, zeroBase(loc) );
        }

	 void detach( T t, TShouldDelete::DeleteType dt = TShouldDelete::NoDelete )
        {
        data.detach( t, dt );
        }

    void detach( long loc,
                 TShouldDelete::DeleteType dt =TShouldDelete::NoDelete
               )
        {
		  data.detach( zeroBase(loc), dt );
        }

    void destroy( long i )
        {
        detach( i, TShouldDelete::Delete );
        }

    void flush( TShouldDelete::DeleteType dt = TShouldDelete::DefDelete )
        {
        data.flush( dt );
        }

    long isFull() const
		  {
        return data.getDelta() == 0 && data.count() >= data.limit();
        }

    long hasMember( T t ) const
        {
        return data.find(t) != LONG_MAX;
		  }

    long isEmpty() const
        {
        return data.count() == 0;
        }

	 long getItemsInContainer() const
        {
        return data.count();
		  }

	 T itemAt( long i ) const
		  {
		  return data[ zeroBase(i) ];
		  }

    long find( const T t ) const
        {
        return boundBase(data.find( t ));
        }

	 void reallocate( long sz, long offset = 0 )
        {
        data.resize( sz, offset );
        }


    void setData( long loc, T t )
        {
        PRECONDITION( loc >= lowerbound && loc <= upperBound() );
        data[ zeroBase(loc) ] = t;
        }

    void insertEntry( long loc )
        {
        PRECONDITION( loc >= lowerbound && loc <= upperBound() );
        T t;
        data.addAt( t, zeroBase(loc) );
        }

	 void removeEntry( long loc )
        {
		  squeezeEntry( zeroBase(loc) );
        }

    void squeezeEntry( long loc )
        {
        PRECONDITION( loc < data.count() );
        data.detach( loc );
        }

    long zeroBase( long loc ) const
		  {
        return loc - lowerbound;
        }

    long boundBase( long loc ) const
        {
		  return loc == LONG_MAX ? LONG_MAX : loc + lowerbound;
		  }

	 void grow( long loc )
		  {
		  if( loc < lowerBound() )
            reallocate( arraySize() + (loc - lowerbound) );
        else if( loc >= boundBase(data.limit()) )
            reallocate( zeroBase(loc) );
        }

    long lowerbound;

	 Vect data;

};

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BIH_ArrayAsVector                             */
/*                                                                        */
/*  Implements an array of objects of type T, using a vector as           */
/*  the underlying implementation.                                        */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T> class _CLASSTYPE BIH_ArrayAsVector :
    public BIH_ArrayAsVectorImp<BIH_CVectorImp<T>,T>
{

public:

    friend class _CLASSTYPE BIH_ArrayAsVectorIterator<T>;

    BIH_ArrayAsVector( long upper, long lower = 0, long delta = 0 ) :
        BIH_ArrayAsVectorImp<BIH_CVectorImp<T>,T>( upper, lower, delta )
        {
        }

    T& operator []( long loc )
        {
        grow( loc+1 );
        return data[zeroBase(loc)];
        }

    T& operator []( long loc ) const
        {
        PRECONDITION( loc >= lowerbound && loc < data.count() );
        return data[zeroBase(loc)];
        }

    void forEach( void (huge *f)(T huge &, void huge *), void huge *args )
        {
        if( !isEmpty() )
            data.forEach( f, args );
        }

    T huge *firstThat( long (huge *f)(const T huge &, void huge *),
                       void huge *args
                     ) const
        {
        if( isEmpty() )
            return 0;
        return data.firstThat( f, args );
        }

    T huge *lastThat( long (huge * f)(const T huge &, void huge *),
                      void huge *args
                    ) const
        {
        if( isEmpty() )
            return 0;
        return data.lastThat( f, args );
        }

};

template <class T> class _CLASSTYPE BIH_ArrayAsVectorIterator :
    public BIH_VectorIteratorImp<T>
{

public:

    BIH_ArrayAsVectorIterator( const BIH_ArrayAsVector<T> huge & a ) :
        BIH_VectorIteratorImp<T>(a.data) {}

};

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BIH_IArrayAsVector                            */
/*                                                                        */
/*  Implements an indirect array of objects of type T, using a vector as  */
/*  the underlying implementation.                                        */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T> class _CLASSTYPE BIH_IArrayAsVector :
    public BIH_ArrayAsVectorImp<BIH_ICVectorImp<T>,T huge *>,
    public virtual TShouldDelete
{

public:

    friend class _CLASSTYPE BIH_IArrayAsVectorIterator<T>;

	 BIH_IArrayAsVector( long upper, long lower = 0, long delta = 0 ) :
        BIH_ArrayAsVectorImp<BIH_ICVectorImp<T>,T huge *>( upper, lower, delta )
        {
        }

    ~BIH_IArrayAsVector()
        {
        flush();
        }

    T huge * huge & operator []( long loc )
        {
        grow( loc+1 );
        return data[zeroBase(loc)];
        }

    T huge * huge & operator []( long loc ) const
        {
        PRECONDITION( loc >= lowerbound && zeroBase(loc) < data.limit() );
        return data[zeroBase(loc)];
        }

    void add( T huge *t )
        {
        BIH_ArrayAsVectorImp<BIH_ICVectorImp<T>,T huge *>::add(t);
        }

    void addAt( T huge *t, long loc )
        {
        BIH_ArrayAsVectorImp<BIH_ICVectorImp<T>,T huge *>::addAt(t,loc);
        }

    void detach( long loc, DeleteType dt = NoDelete )
        {
        data.detach( zeroBase(loc), delObj(dt) );
        }

    void detach( T huge *t, DeleteType dt = NoDelete )
        {
        long loc = data.find( t );
        if( loc == LONG_MAX )
            return;
        data.detach( loc, delObj(dt) );
        }

    void flush( DeleteType dt = DefDelete )
        {
        data.flush( delObj(dt), data.limit(), 0 );
        }

    long find( const T *t ) const
        {
        return boundBase(data.find( (T *)t ));
        }

    void forEach( void (huge *f)(T huge &, void huge *), void huge *args )
        {
        if( !isEmpty() )
            data.forEach( f, args );
        }

    T huge *firstThat( long (huge *f)(const T huge &, void huge *),
							  void huge *args
                     ) const
        {
        if( isEmpty() )
            return 0;
        return data.firstThat( f, args );
        }

    T huge *lastThat( long (huge * f)(const T huge &, void huge *),
                      void huge *args
                    ) const
        {
        if( isEmpty() )
            return 0;
        return data.lastThat( f, args );
        }

};

template <class T> class _CLASSTYPE BIH_IArrayAsVectorIterator :
    public BIH_IVectorIteratorImp<T>
{

public:

	 BIH_IArrayAsVectorIterator( const BIH_IArrayAsVector<T> huge &a ) :
		  BIH_IVectorIteratorImp<T>(a.data) {}

};

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BIH_SArrayAsVector                            */
/*                                                                        */
/*  Implements a sorted array of objects of type T, using a vector as     */
/*  the underlying implementation.                                        */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T> class _CLASSTYPE BIH_SArrayAsVector :
	 public BIH_ArrayAsVectorImp<BIH_SVectorImp<T>,T>
{

public:

	 friend class _CLASSTYPE BIH_SArrayAsVectorIterator<T>;

    BIH_SArrayAsVector( long upper, long lower = 0, long delta = 0 ) :
        BIH_ArrayAsVectorImp<BIH_SVectorImp<T>,T>( upper, lower, delta )
        {
        }

    T& operator []( long loc )
        {
        grow( loc+1 );
        return data[zeroBase(loc)];
        }

    T& operator []( long loc ) const
        {
        PRECONDITION( loc >= lowerbound && loc < data.count() );
		  return data[zeroBase(loc)];
        }

    void forEach( void (huge *f)(T huge &, void huge *), void huge *args )
        {
        if( !isEmpty() )
            data.forEach( f, args );
        }

    T huge *firstThat( long (huge *f)(const T huge &, void huge *),
                       void huge *args
                     ) const
        {
        if( isEmpty() )
            return 0;
        return data.firstThat( f, args );
        }

    T huge *lastThat( long (huge * f)(const T huge &, void huge *),
                      void huge *args
                    ) const
        {
        if( isEmpty() )
            return 0;
        return data.lastThat( f, args );
        }

};

template <class T> class _CLASSTYPE BIH_SArrayAsVectorIterator :
    public BIH_VectorIteratorImp<T>
{

public:

    BIH_SArrayAsVectorIterator( const BIH_SArrayAsVector<T> huge & a ) :
        BIH_VectorIteratorImp<T>(a.data) {}

};

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BIH_ISArrayAsVector                           */
/*                                                                        */
/*  Implements an indirect sorted array of objects of type T, using a     */
/*  vector as the underlying implementation.                              */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T> class _CLASSTYPE BIH_ISArrayAsVector :
    public BIH_ArrayAsVectorImp<BIH_ISVectorImp<T>,T huge *>,
    public virtual TShouldDelete
{

public:

    friend class _CLASSTYPE BIH_ISArrayAsVectorIterator<T>;

    BIH_ISArrayAsVector( long upper, long lower = 0, long delta = 0 ) :
        BIH_ArrayAsVectorImp<BIH_ISVectorImp<T>,T huge*>( upper, lower, delta )
        {
        }

    ~BIH_ISArrayAsVector()
        {
        flush();
        }

    T huge * huge & operator []( long loc )
        {
        grow( loc+1 );
        return data[zeroBase(loc)];
        }

    T huge * huge & operator []( long loc ) const
        {
        PRECONDITION( loc >= lowerbound && loc < data.count() );
        return data[zeroBase(loc)];
        }

    void add( T huge *t )
        {
        BIH_ArrayAsVectorImp<BIH_ISVectorImp<T>,T huge *>::add(t);
        }

    void addAt( T huge *t, long loc )
        {
        BIH_ArrayAsVectorImp<BIH_ISVectorImp<T>,T huge *>::addAt(t,loc);
        }

    void detach( long loc, DeleteType dt = NoDelete )
        {
        data.detach( loc, delObj(dt) );
		  }

    void detach( T huge *t, DeleteType dt = NoDelete )
        {
        long loc = data.find( t );
        if( loc == LONG_MAX )
            return;
        data.detach( loc, delObj(dt) );
        }

    void flush( DeleteType dt = DefDelete )
        {
		  data.flush( delObj(dt), data.limit(), 0 );
        }

    long find( const T *t ) const
        {
        return boundBase( data.find( (T *)t ) );
        }

    void forEach( void (huge *f)(T huge &, void huge *), void huge *args )
        {
        if( !isEmpty() )
            data.forEach( f, args );
        }

    T huge *firstThat( long (huge *f)(const T huge &, void huge *),
                       void huge *args
                     ) const
        {
        if( isEmpty() )
				return 0;
		  return data.firstThat( f, args );
		  }

	 T huge *lastThat( long (huge * f)(const T huge &, void huge *),
							 void huge *args
						  ) const
		  {
		  if( isEmpty() )
				return 0;
		  return data.lastThat( f, args );
		  }

};

template <class T> class _CLASSTYPE BIH_ISArrayAsVectorIterator :
	 public BIH_IVectorIteratorImp<T>
{

public:

	 BIH_ISArrayAsVectorIterator( const BIH_ISArrayAsVector<T> huge &a ) :
		  BIH_IVectorIteratorImp<T>(a.data) {}

};


#pragma warn .ncf

#if defined( __BCOPT__ ) && !defined( _ALLOW_po )
#pragma option -po.
#endif
#pragma option -Vo.

#endif  // UNIX

#endif  // __ARRAYS_H

