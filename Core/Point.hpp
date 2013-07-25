#ifndef CORE_POINT_H
#define CORE_POINT_H

#include "Size.hpp"

//////////////////////////////////////////////////////////////////////////////////////

template<typename T>
struct PointBase
{
    typedef T TValueType;
    
    T x;
    T y;

    PointBase(): x(0), y(0) {}
    PointBase( T _x, T _y ): x(_x), y(_y) {}
    
    template< class T2 >
    explicit PointBase( const PointBase<T2> &other ): x(static_cast<T>(other.x)), y(static_cast<T>(other.y)) {}
    
    template< class T2 >
    explicit PointBase( const SizeBase<T2> &other ): x(static_cast<T>(other.w)), y(static_cast<T>(other.h)) {}

    void set( T _x, T _y ) { x = _x; y = _y; }
    void zeroize() { x = 0; y = 0; }
    bool isZero() const { return x == 0 && y == 0; } 

    PointBase operator-() const { return PointBase( -x, -y ); }

    friend PointBase operator+( const PointBase &a, const PointBase &b ) { return PointBase( a.x + b.x, a.y + b.y ); }
    friend PointBase operator-( const PointBase &a, const PointBase &b ) { return PointBase( a.x - b.x, a.y - b.y ); }

    friend PointBase operator+( const PointBase &a, const SizeBase<T> &b ) { return PointBase( a.x + b.w, a.y + b.h ); }
    friend PointBase operator-( const PointBase &a, const SizeBase<T> &b ) { return PointBase( a.x - b.w, a.y - b.h ); }

    friend PointBase operator*( const PointBase &a, T val )  { return PointBase( a.x * val, a.y * val ); }
    friend PointBase operator*( T val, const PointBase &a )  { return a * val; }
    friend PointBase operator/( const PointBase &a, T val )  { return PointBase( a.x / val, a.y / val ); }

    PointBase& operator+=( const PointBase &_in ) { x += _in.x; y += _in.y; return *this; }
    PointBase& operator-=( const PointBase &_in ) { x -= _in.x; y -= _in.y; return *this; }
    
    PointBase& operator+=( const SizeBase<T> &_in ) { x += _in.w; y += _in.h; return *this; }
    PointBase& operator-=( const SizeBase<T> &_in ) { x -= _in.w; y -= _in.h; return *this; }    
    
    PointBase& operator+=( T v ) { x += v; y += v; return *this; }
    PointBase& operator-=( T v ) { x -= v; y -= v; return *this; }
    PointBase& operator*=( T v ) { x *= v; y *= v; return *this; }
    PointBase& operator/=( T v ) { x /= v; y /= v; return *this; }
};
//////////////////////////////////////////////////////////////////////////////////////
template <typename T>
inline bool operator == ( const PointBase<T> &a, const PointBase<T> &b )
{
    return a.x == b.x && a.y == b.y;
}
//////////////////////////////////////////////////////////////////////////////////////
template <typename T>
inline bool operator != ( const PointBase<T> &a, const PointBase<T> &b )
{
    return !(a == b);
}
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ��������� �������� ��� ������
///////////////////////////////////////////////////////////////////////////////

//��������� ������������
template< class T >
inline T vecDotProduct( const PointBase<T> &vec1, const PointBase<T> &vec2 ) 
{
    return vec1.x * vec2.x + vec1.y * vec2.y;
}

//����� ������� � ��������
template< class T >
inline T vecLengthSquared( const PointBase<T> &vec ) 
{
    return vec.x * vec.x + vec.y * vec.y;
}

//����� �������
template< class T >
inline T vecLength( const PointBase<T> &vec ) 
{
    return std::sqrt( vecLengthSquared(vec) );
}

//������������ �������
//����������� ���������� � length ���� ����� ������� ��������
template< class T >
inline PointBase<T> vecNormalize( const PointBase<T> &vec, T length ) 
{
    ASSERT( length == vecLength(vec) );
    ASSERT( length > 0 );
    return vec / length;
}

template< class T >
inline PointBase<T> vecNormalize( const PointBase<T> &vec ) 
{
    return vecNormalize( vec, vecLength(vec) );
}
///////////////////////////////////////////////////////////////////////////////

//����� �� ����� pt ����� �� ������ ���������� ��� �������� �� from �� to
template< class T > 
bool isOnLeftSide( const PointBase<T> &from, const PointBase<T> &to, const PointBase<T> &pt )
{
    //��� ���� ����� ������ � ����� ������� ����� �����, 
    //��������� ���� ����� ����� ��������� ���� �� ����� � ��������� [0, +Pi], 
    //�� ����� ��������� � ����� ������� 
    //��� ����� ������������� ��������� �������������, ������� ����� ������������� ����
    //���� ����� � ��������� [-Pi/2, +Pi/2].
    const PointBase<T> vec1( pt.x - from.x, pt.y - from.y );

    //��� ���� ����� ������� �� ��������� [0, +Pi] � [-Pi/2, +Pi/2] ������� 
    //������ ������ �� Pi/2:
    //������������ PointBase<T> vec( to - from ); SWAP( vec2.x, vec2.y ); vec2.y = -vec2.y;
    const PointBase<T> vec2( to.y - from.y, from.x - to.x );

    //����, ��������� ������������ vec1 � vec2
    return vecDotProduct(vec1, vec2) > 0;
}
//////////////////////////////////////////////////////////////////////////////////////

template< class T >
inline PointBase<T> minEachDim( const PointBase<T> &a, const PointBase<T> &b ) 
{
    return PointBase<T>(
        std::min(a.x, b.x),
        std::min(a.y, b.y)
    );
}
//////////////////////////////////////////////////////////////////////////////////////

template< class T >
inline PointBase<T> maxEachDim( const PointBase<T> &a, const PointBase<T> &b ) 
{
    return PointBase<T>(
        std::max(a.x, b.x),
        std::max(a.y, b.y)
    );
}
//////////////////////////////////////////////////////////////////////////////////////

template< class T >
inline T manhattanDistance( const PointBase<T> &a, const PointBase<T> &b ) 
{
  return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}
//////////////////////////////////////////////////////////////////////////////////////

template< class T >
inline PointBase<T> abs( const PointBase<T> &a ) 
{
  return PointBase<T>(
    std::abs(a.x),
    std::abs(a.y)
  );
}

//////////////////////////////////////////////////////////////////////////////////////
typedef PointBase<int> Point;
//////////////////////////////////////////////////////////////////////////////////////

template< class CharT, class CharTraitsT, class PointT >
inline std::basic_ostream<CharT, CharTraitsT> &operator<<( std::basic_ostream<CharT, CharTraitsT> &os, const PointBase<PointT> &p )
{
  return os << '[' << p.x << ", " << p.y << ']';
}

#endif
