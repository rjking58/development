/*------------------------------------------------------------------------*/
/*                                                                        */
/*  HVECTIMP.H                                                            */
/*                                                                        */
/*  Copyright Borland International 1991, 1992                            */
/*  All Rights Reserved                                                   */
/*                                                                        */
/*------------------------------------------------------------------------*/

#if !defined( __HVECTIMP_H )
#define __HVECTIMP_H

#include <windows.h>

#if !defined( __LIMITS_H )
#include <Limits.h>
#endif  // __LIMITS_H

#if !defined( __CHECKS_H )
#include <Checks.h>
#endif  // __CHECKS_H

#if !defined( __STDTEMPL_H )
#include <StdTempl.h>
#endif  // __STDTEMPL_H

#pragma option -Vo-
#if defined( __BCOPT__ ) && !defined( _ALLOW_po )
#pragma option -po-
#endif

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BIH_VectorImp                                 */
/*                                                                        */
/*  Implements a vector of objects of type T.  Assumes that               */
/*  T has meaningful copy semantics and a default constructor.            */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T> class _CLASSTYPE BIH_VectorImp
{

public:

    friend class _CLASSTYPE BIH_VectorIteratorImp<T>;

	 BIH_VectorImp() :
		  h_data(0),
		  data(0),
		  lim(0)
		  {
		  }

	 BIH_VectorImp( long sz, long = 0 ) :
		  lim(sz)
		  {
		  h_data = GlobalAlloc( GHND, sizeof( T ) * sz );
		  data = ( T huge* ) GlobalLock( h_data );
		  }

	 BIH_VectorImp( const BIH_VectorImp<T> huge & );

	 const BIH_VectorImp<T> huge & operator = ( const BIH_VectorImp<T> huge & );

	 ~BIH_VectorImp()
		  {
		  GlobalUnlock( h_data );
		  GlobalFree( h_data );
		  }

	 T huge & operator [] ( long index ) const
		  {
		  PRECONDITION( lim > 0 && data != 0 && index < lim );
		  return data[index];
		  }

	 long limit() const
		  {
		  return lim;
		  }

	 virtual long top() const
		  {
		  return lim;
        }

    void resize( long, long = 0 );

	 void flush( long = 0, long = LONG_MAX, long = 0 ) {}

    void forEach( void (huge *f)(T huge &, void huge *), void huge *args )
        {
        forEach( f, args, 0, lim );
        }

    void forEach( void (huge *)(T huge &, void huge *),
                  void huge *,
						long,
                  long
                );

    T huge *firstThat( long (huge *)(const T huge &, void huge *),
							  void huge *,
                       long,
							  long
                     ) const;

    T huge *firstThat( long (huge *cond)(const T huge &, void huge *),
                       void huge *args
                     ) const
        {
		  return firstThat( cond, args, 0, lim );
		  }

	 T huge *lastThat( long (huge *)(const T huge &, void huge *),
                      void huge *,
                      long,
                      long
                    ) const;

	 T huge *lastThat( long (huge *cond)(const T huge &, void huge *),
                      void huge *args
                    ) const
        {
        return lastThat( cond, args, 0, lim );
        }

    virtual long getDelta() const
        {
        return 0;
        }

protected:

	 T huge * data;
	 HGLOBAL  h_data;
	 long lim;

	 virtual void zero( long, long )
		  {
		  }

	 virtual void removeData( T )
		  {
        }

};

template <class T>
BIH_VectorImp<T>::BIH_VectorImp( const BIH_VectorImp<T> huge & v ) :
	 lim(v.lim)
{
	 h_data = GlobalAlloc( GHND, sizeof( T ) * v.lim );
	 data   = ( T huge* ) GlobalLock( h_data );

	 PRECONDITION( lim == 0 || (data != 0 && v.data != 0) );
	 for( long i = 0; i < lim; i++ )
		  data[i] = v.data[i];
}

template <class T>
const BIH_VectorImp<T> huge & BIH_VectorImp<T>::operator = ( const BIH_VectorImp<T> huge & v )
{
	 if( data != v.data )
		  {
		  GlobalUnlock( h_data );
		  GlobalFree( h_data );

		  h_data =  GlobalAlloc( GHND, sizeof( T ) * v.lim );
		  data =  ( T huge* ) GlobalLock( h_data );

		  CHECK( data != 0 );
		  lim = v.lim;
		  for( long i = 0; i < lim; i++ )
				data[i] = v.data[i];
		  }
	 return *this;
}

inline long nextDelta( long sz, long delta )
{
	 return (sz%delta) ? ((sz+delta)/delta)*delta : sz;
}

template <class T>
void BIH_VectorImp<T>::resize( long newSz, long offset )
{
	 if( newSz <= lim || getDelta() == 0 )
		  return;
	 long sz = lim + nextDelta( newSz - lim, getDelta() );

	 HGLOBAL h_temp = GlobalAlloc( GHND, sizeof( T ) * sz );
	 T huge *temp = ( T huge* ) GlobalLock( h_temp );

	 long last = ( sz-offset < lim ) ? sz-offset : lim ;
	 for( long i = 0; i < last; i++ )
		  temp[i+offset] = data[i];

	 GlobalUnlock( h_data );
	 GlobalFree( h_data );

	 h_data = h_temp;
	 data = temp;
	 lim = sz;
	 zero( last+offset, sz );
}

template <class T>
void BIH_VectorImp<T>::forEach( void (huge *f)( T huge &, void huge * ),
										 void huge *args,
                               long start,
                               long stop
                             )
{
    for( long cur = start; cur < stop; cur++ )
        f( data[cur], args );
}

template <class T>
T huge *BIH_VectorImp<T>::firstThat( long (huge *cond)( const T huge &, void huge * ),
                               void huge *args,
                               long start,
                               long stop
                             ) const
{
    for( long cur = start; cur < stop; cur++ )
        if( cond( data[cur], args ) != 0 )
            return &data[cur];
    return 0;
}

template <class T>
T huge *BIH_VectorImp<T>::lastThat( long (huge *cond)( const T huge &, void huge * ),
                              void huge *args,
                              long start,
                              long stop
                            ) const
{
    T huge *res = 0;
    for( long cur = start; cur < stop; cur++ )
		  if( cond( data[cur], args ) != 0 )
            res = &data[cur];
    return res;
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BIH_CVectorImp                                */
/*                                                                        */
/*  Implements a counted vector of objects of type T.  Assumes that       */
/*  T has meaningful copy semantics and a default constructor.            */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T> class _CLASSTYPE BIH_CVectorImp : public BIH_VectorImp<T>
{

public:

    BIH_CVectorImp() :
        count_(0),
        delta(0)
        {
        }

    BIH_CVectorImp( long sz, long d = 0 ) :
        BIH_VectorImp<T>( sz ),
        count_(0),
        delta(d)
        {
        }

    void add( T );
    void addAt( T, long );
    void detach( T, long = 0 );
    void detach( long, long = 0 );

    long isEmpty() const
        {
        return count_ == 0;
        }

    void forEach( void (huge *f)(T huge &, void huge *), void huge *args )
        {
        forEach( f, args, 0, count_ );
        }

    void forEach( void (huge *func)(T huge &, void huge *),
                  void huge *args,
                  long low,
                  long high
                )
        {
        BIH_VectorImp<T>::forEach( func, args, low, high );
        }

    T huge *firstThat( long (huge *cond)(const T huge &, void huge *),
                       void huge *args
                     ) const
        {
        return firstThat( cond, args, 0, count_ );
        }

    T huge *firstThat( long (huge *cond)(const T huge &, void huge *),
                       void huge *args,
                       long low,
                       long high
                     ) const
        {
        return BIH_VectorImp<T>::firstThat( cond, args, low, high );
        }

    T huge *lastThat( long (huge *cond)(const T huge &, void huge *),
                      void huge *args
                    ) const
        {
        return lastThat( cond, args, 0, count_ );
        }

    T huge *lastThat( long (huge *cond)(const T huge &, void huge *),
                      void huge *args,
                      long low,
                      long high
                    ) const
        {
        return BIH_VectorImp<T>::lastThat( cond, args, low, high );
        }

    void flush( long del = 0,
                long stop = LONG_MAX,
                long start = 0
              )
        {
		  BIH_VectorImp<T>::flush( del, stop, start ); count_ = 0;
        }

    virtual long find( T ) const;

    virtual long top() const
        {
        return count_;
        }

    long count() const
        {
        return count_;
        }

    virtual long getDelta() const
        {
        return delta;
        }

protected:

    long count_;
    long delta;

};

template <class T> void BIH_CVectorImp<T>::add( T t )
{
    if( ++count_ > lim )
        resize( count_ );
	 data[count_-1] = t;
}

template <class T> void BIH_CVectorImp<T>::addAt( T t, long loc )
{
    if( loc >= lim )
        resize( loc+1 );
    data[loc] = t;
}

template <class T> void BIH_CVectorImp<T>::detach( T t, long del )
{
    detach( find(t), del );
}

template <class T> void BIH_CVectorImp<T>::detach( long loc, long del )
{
    if( loc >= lim )
        return;
    if( del )
        removeData( data[loc] );
    if( loc >= count_ )
        {
        zero( loc, loc+1 ); // removing an element that's not
        return;             // in the counted portion
        }
    count_--;
    for( long cur = loc; cur < count_; cur++ )
        data[cur] = data[cur+1];
    zero( count_, count_+1 );
}

template <class T> long BIH_CVectorImp<T>::find( T t ) const
{
    if( count_ != 0 )
        {
        for( long loc = 0; loc < count_; loc++ )
            if( data[loc] == t )
                return loc;
        }
    return LONG_MAX;
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BIH_SVectorImp                                */
/*                                                                        */
/*  Implements a sorted vector of objects of type T.  Assumes that        */
/*  T has meaningful copy semantics, a meaningful < operator,             */
/*  and a default constructor.                                            */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T> class _CLASSTYPE BIH_SVectorImp : public BIH_CVectorImp<T>
{

public:

    BIH_SVectorImp()
        {
        }

	 BIH_SVectorImp( long sz, long d = 0 ) :
        BIH_CVectorImp<T>( sz, d )
        {
        }

    void add( T );

    virtual long find( T ) const;

};

template <class T> void BIH_SVectorImp<T>::add( T t )
{
    long loc = count_++;
    if( count_ > lim )
        resize( count_ );
    while( loc > 0 && t < data[loc-1] )
        {
        data[loc] = data[loc-1];
        loc--;
        }
    data[loc] = t;
}

template <class T> long BIH_SVectorImp<T>::find( T t ) const
{
    long lower = 0;
    long upper = count_-1;
    if( count_ != 0 )
        {
        while( lower < upper && upper != LONG_MAX )
				{
            long middle = (lower+upper)/2;
            if( data[middle] == t )
                return middle;
            if( data[middle] < t )
                lower = middle+1;
            else
                upper = middle-1;
            }
        }
    if( lower == upper && data[lower] == t )
        return lower;
    else
        return LONG_MAX;
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BIH_VectorIteratorImp                         */
/*                                                                        */
/*  Implements a vector iterator.  This iterator works with any direct    */
/*  vector.  For indirect vectors, see BIH_IVectorIteratorImp.             */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T> class _CLASSTYPE BIH_VectorIteratorImp
{

public:

    BIH_VectorIteratorImp( const BIH_VectorImp<T> huge &v )
		  {
        vect = &v;
        restart(0,v.limit());
        }

    BIH_VectorIteratorImp( const BIH_VectorImp<T> huge &v,
                          long start,
                          long stop
                        )
        {
        vect = &v;
        restart( start, stop );
        }


    operator long()
        {
        return cur < upper;
        }

    T current()
        {
        return (cur < upper) ? (*vect)[cur] : (*vect)[upper-1];
        }

	 T operator ++ ( int )
        {
        if( cur >= upper )
            return (*vect)[upper-1];
        else
            return (*vect)[cur++];
		  }

    T operator ++ ()
        {
        if( cur < upper )
            cur++;
        if( cur >= upper )
            return (*vect)[upper-1];
        else
            return (*vect)[cur];
        }

    void restart()
        {
        restart(lower,upper);
        }

    void restart( long start, long stop )
        {
        cur = lower = start;
        upper = stop;
        }

private:

    const BIH_VectorImp<T> huge *vect;
    long cur;
    long lower, upper;

};

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T, class Vect> class BIH_InternalIVectorImp            */
/*                                                                        */
/*  Implements a vector of polongers to objects of type T.                 */
/*  This is implemented through the form of BIH_VectorImp specified by     */
/*  Vect.  Since polongers always have meaningful copy semantics,          */
/*  this class can handle any type of object.                             */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T, class Vect> class _CLASSTYPE BIH_InternalIVectorImp :
    public Vect
{

public:

    BIH_InternalIVectorImp( long sz, long d = 0 ) :
        Vect( sz, d )
        {
        zero( 0, sz );
        }

    ~BIH_InternalIVectorImp()
        {
        flush();
        }

    T huge * huge & operator [] ( long index )
        {
        PRECONDITION( lim == 0 || data != 0 && index < lim );
		  return (T huge *)(data[index]);
        }

    T huge * huge & operator [] ( long index ) const
        {
        PRECONDITION( lim > 0 && data != 0 && index < lim );
        return (T huge *)(data[index]);
        }

    void flush( long = 0, long = LONG_MAX, long = 0 );

    void forEach( void (huge *f)(T huge &, void huge *), void huge *args )
        {
        forEach( f, args, 0, lim );
        }

    void forEach( void (huge *)(T huge &, void huge *),
                  void huge *,
                  long,
                  long
                );

    T huge *firstThat( long (huge *cond)(const T huge &, void huge *),
                       void huge *args
                     ) const
        {
        return firstThat( cond, args, 0, lim );
        }

    T huge *firstThat( long (huge *)(const T huge &, void huge *),
                       void huge *,
							  long,
                       long
                     ) const;

    T huge *lastThat( long (huge *cond)(const T huge &, void huge *),
                      void huge *args
                    ) const
        {
        return lastThat( cond, args, 0, lim );
        }

    T huge *lastThat( long (huge *)(const T huge &, void huge *),
                      void huge *,
                      long,
                      long
                    ) const;

    virtual void zero( long, long );

protected:

    virtual void removeData( void huge *t )
		  {
		  delete (T huge *)t;
		  }

private:

	 static void delObj( T huge &, void huge * );

};

template <class T, class Vect>
void BIH_InternalIVectorImp<T,Vect>::delObj( T huge &tRef, void huge *vect )
{
	 ((BIH_InternalIVectorImp<T,Vect> *)vect)->removeData( &tRef );
}

template <class T, class Vect>
void BIH_InternalIVectorImp<T,Vect>::flush(
                                           long del,
                                           long upr,
                                           long lwr
                                         )
{
	 upr = ( upr < limit() ) ? upr : limit();
    if( del )
        forEach( delObj, this, lwr, upr );
    zero( lwr, upr );
    Vect::flush( del, upr, lwr );
}

template <class T, class Vect>
void BIH_InternalIVectorImp<T,Vect>::forEach( void (huge *f)( T huge &, void huge * ),
                                             void huge *args,
                                             long start,
                                             long stop
                                           )
{
    for( long cur = start; cur < stop; cur++ )
        if( data[cur] != 0 )
            f( *(T huge *)(data[cur]), args );
}

template <class T, class Vect>
T huge *BIH_InternalIVectorImp<T,Vect>::firstThat( long (huge *cond)( const T huge &, void huge * ),
                                             void huge *args,
                                             long start,
                                             long stop
                                           ) const
{
    for( long cur = start; cur < stop; cur++ )
        if( data[cur] != 0 && cond( *(T huge *)(data[cur]), args ) != 0 )
            return (T huge *)data[cur];
    return 0;
}

template <class T, class Vect>
T huge *BIH_InternalIVectorImp<T,Vect>::lastThat( long (huge *cond)( const T huge &, void huge * ),
                                            void huge *args,
                                            long start,
                                            long stop
                                          ) const
{
    T huge *res = 0;
    for( long cur = start; cur < stop; cur++ )
        if( data[cur] != 0 && cond( *(T huge *)(data[cur]), args ) != 0 )
            res = (T huge *)data[cur];
    return res;
}

template <class T, class Vect>
void BIH_InternalIVectorImp<T,Vect>::zero( long lwr, long upr )
{
	 for( long i = lwr; i < ( ( limit() < upr ) ? limit() : upr ); i++ )
        data[i] = 0;
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BIH_IVectorImp                                */
/*                                                                        */
/*  Implements a vector of polongers to objects of type T.                 */
/*  This is implemented through the template BIH_InternalIVectorImp.       */
/*  Since polongers always have meaningful copy semantics, this class      */
/*  can handle any type of object.                                        */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T> class _CLASSTYPE BIH_IVectorImp :
    public BIH_InternalIVectorImp<T, BIH_VectorImp<void huge *> >
{

public:

    BIH_IVectorImp( long sz ) :
        BIH_InternalIVectorImp<T, BIH_VectorImp<void huge *> >(sz)
        {
        }


};

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BIH_ICVectorImp                               */
/*                                                                        */
/*  Implements a counted vector of polongers to objects of type T.         */
/*  Since polongers always have meaningful copy semantics, this class      */
/*  can handle any type of object.                                        */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T> class _CLASSTYPE BIH_ICVectorImp :
    public BIH_InternalIVectorImp<T, BIH_CVectorImp<void huge *> >
{

public:

    BIH_ICVectorImp( long sz, long d = 0 ) :
        BIH_InternalIVectorImp<T, BIH_CVectorImp<void huge *> >(sz)
        {
        delta = d;
        }

    long find( T huge *t ) const
        {
        return find( (void huge *)t );
        }

    void add( T huge *t );

protected:

    virtual long find( void huge * ) const;

};

template <class T> long BIH_ICVectorImp<T>::find( void huge *t ) const
{
    if( limit() != 0 )
        {
        for( long loc = 0; loc < limit(); loc++ )
            if( data[loc] &&
                *(const T huge *)(data[loc]) == *(const T huge *)t
              )
                return loc;
        }
    return LONG_MAX;
}

template <class T > void BIH_ICVectorImp<T>::add( T huge *t )
{
    while( count_ < limit() && (*this)[count_] != 0 )
        count_++;
    BIH_InternalIVectorImp<T, BIH_CVectorImp<void huge *> >::add(t);
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BIH_ISVectorImp                               */
/*                                                                        */
/*  Implements a sorted vector of polongers to objects of type T.          */
/*  This is implemented through the template BIH_InternalIVectorImp.       */
/*  Since polongers always have meaningful copy semantics, this class      */
/*  can handle any type of object.                                        */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T> class _CLASSTYPE BIH_ISVectorImp :
    public BIH_InternalIVectorImp<T, BIH_SVectorImp<void huge *> >
{

public:

    BIH_ISVectorImp( long sz, long d = 0 ) :
        BIH_InternalIVectorImp<T, BIH_SVectorImp<void huge *> >(sz)
        {
        delta = d;
        }

    long find( T huge *t ) const
        {
        return find( (void huge *)t );
        }

    void add( T huge *t );

protected:

    virtual long find( void huge * ) const;

};

template <class T> long BIH_ISVectorImp<T>::find( void huge *t ) const
{
	 long lower = 0;
	 long upper = count_-1;

	 if( count_ != 0 )
		  {
		  while( lower < upper )
				{
				long middle = (lower+upper)/2;
				if( *(const T huge *)(data[middle]) == *(const T huge *)t )
					 return middle;
				if( *(const T huge *)(data[middle]) < *(const T huge *)t )
					 lower = middle+1;
				else
					 upper = middle-1;
				}
		  }
	 if( lower == upper && *(const T huge*)(data[lower]) == *(const T huge*)t )
		  return lower;
	 else
		  return LONG_MAX;
}

template <class T> void BIH_ISVectorImp<T>::add( T huge *t )
{
    long loc = count_++;
    if( count_ > lim )
		  resize( count_ );
    while( loc > 0 && *t < *((T huge *)(*this)[loc-1]) )
        {
        data[loc] = data[loc-1];
        loc--;
        }
    data[loc] = t;
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BIH_IVectorIteratorImp                        */
/*                                                                        */
/*  Implements a vector iterator.  This iterator works with any indirect  */
/*  vector.  For direct vectors, see BIH_VectorIteratorImp.                */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T> class _CLASSTYPE BIH_IVectorIteratorImp :
    public BIH_VectorIteratorImp<void huge *>
{

public:

    BIH_IVectorIteratorImp( const BIH_VectorImp<void huge *> huge &v ) :
        BIH_VectorIteratorImp<void huge *>(v)
        {
        bump();
        }

    BIH_IVectorIteratorImp( const BIH_VectorImp<void huge *> huge &v,
									long l, long u
                         ) :
        BIH_VectorIteratorImp<void huge *>(v,l,u)
        {
        bump();
        }

    T huge *current()
        {
        return (T huge *)BIH_VectorIteratorImp<void huge *>::current();
        }

	 T huge *operator ++ ( int );
    T huge *operator ++ ();

    void restart()
        {
        BIH_VectorIteratorImp<void huge *>::restart();
        bump();
        }

	 void restart( long start, long stop )
        {
        BIH_VectorIteratorImp<void huge *>::restart( start, stop );
        bump();
        }

private:

    void bump();

};

template <class T> T huge * BIH_IVectorIteratorImp<T>::operator ++ ()
{
    BIH_VectorIteratorImp<void huge *>::operator++();
    bump();
    return (T huge *)current();
}

template <class T> T huge * BIH_IVectorIteratorImp<T>::operator ++ ( long )
{
    void *temp = current();
    BIH_VectorIteratorImp<void huge *>::operator++(1);
    bump();
    return (T huge *)temp;
}

template <class T> void BIH_IVectorIteratorImp<T>::bump()
{
    while( *this != 0 && current() == 0 )
		  BIH_VectorIteratorImp<void huge *>::operator++();
}

#if defined( __BCOPT__ ) && !defined( _ALLOW_po )
#pragma option -po.
#endif
#pragma option -Vo.

#endif // __VECTIMP_H
