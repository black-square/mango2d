#ifndef Matrix_h__
#define Matrix_h__

#include <vector>

//////////////////////////////////////////////////////////////////////////
// Very simple dynamic matrix implementation
// boost::multi_array is too slow
//////////////////////////////////////////////////////////////////////////
template< class T, class SizeT = typename std::vector<T>::size_type >
class Matrix
{
private:
  typedef std::vector<T> TVec;

public:
  typedef SizeT TSize;
  typedef SizeBase<TSize> TSize2d;
  typedef PointBase<TSize> TPoint2d;

public:
  Matrix() {}
  Matrix( TSize2d size ): m_data( size.w * size.h ), m_size(size) {} 

  bool IsValid( TSize x, TSize y ) const
  {
    return x >= 0 && x < m_size.w && y >= 0 && y < m_size.h;
  }

  bool IsValid( TPoint2d pt ) const
  {
    return IsValid( pt.x, pt.y );
  }

  T &operator()( TSize x, TSize y )
  {
    ASSERT( IsValid(x, y) );

    //Element access is optimized for horizontal iteration, 
    //which is more common
    return m_data[ y * m_size.h + x ];
  }

  const T &operator()( TSize x, TSize y ) const
  {
    ASSERT( IsValid(x, y) );
    return m_data[ y * m_size.h + x ];
  }

  T &operator()( TPoint2d pt )
  {
    return (*this)( pt.x, pt.y );
  }

  const T &operator()( TPoint2d pt ) const
  {
    return (*this)( pt.x, pt.y );
  }

  TSize2d GetSize() const { return m_size; }

private:
  TVec m_data;
  TSize2d m_size;
};

#endif // Matrix_h__
