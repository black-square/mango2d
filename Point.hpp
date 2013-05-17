#ifndef CORE_POINT_H
#define CORE_POINT_H
//////////////////////////////////////////////////////////////////////////////////////

template<typename T>
struct point_base_t
{
    typedef T TValueType;
    
    T x;
    T y;

    point_base_t(): x(0), y(0) {}
    point_base_t( T _x, T _y ): x(_x), y(_y) {}
    
    template< class T2>
    explicit point_base_t( const point_base_t<T2> &other ): x(static_cast<T>(other.x)), y(static_cast<T>(other.y)) {}
    
    void set( T _x, T _y ) { x = _x; y = _y; }
    void zeroize() { x = 0; y = 0; }
    bool isZero() const { return x == 0 && y == 0; } 

    point_base_t operator-() const { return point_base_t( -x, -y ); }

    friend point_base_t operator+( const point_base_t &a, const point_base_t &b ) { return point_base_t( a.x + b.x, a.y + b.y ); }
    friend point_base_t operator-( const point_base_t &a, const point_base_t &b ) { return point_base_t( a.x - b.x, a.y - b.y ); }

    friend point_base_t operator*( const point_base_t &a, T val )  { return point_base_t( a.x * val, a.y * val ); }
    friend point_base_t operator*( T val, const point_base_t &a )  { return a * val; }
    friend point_base_t operator/( const point_base_t &a, T val )  { return point_base_t( a.x / val, a.y / val ); }

    point_base_t& operator+=( const point_base_t &_in ) { x += _in.x; y += _in.y; return *this; }
    point_base_t& operator-=( const point_base_t &_in ) { x -= _in.x; y -= _in.y; return *this; }   
    
    point_base_t& operator+=( T v ) { x += v; y += v; return *this; }
    point_base_t& operator-=( T v ) { x -= v; y -= v; return *this; }
    point_base_t& operator*=( T v ) { x *= v; y *= v; return *this; }
    point_base_t& operator/=( T v ) { x /= v; y /= v; return *this; }
};
//////////////////////////////////////////////////////////////////////////////////////
template <typename T>
inline bool operator == ( const point_base_t<T> &a, const point_base_t<T> &b )
{
    return a.x == b.x && a.y == b.y;
}
//////////////////////////////////////////////////////////////////////////////////////
template <typename T>
inline bool operator != ( const point_base_t<T> &a, const point_base_t<T> &b )
{
    return !(a == b);
}
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ¬екторные операции над точкой
///////////////////////////////////////////////////////////////////////////////

//—кал€рное произведение
template< class T >
inline T vecDotProduct( const point_base_t<T> &vec1, const point_base_t<T> &vec2 ) 
{
    return vec1.x * vec2.x + vec1.y * vec2.y;
}

//ƒлина вектора в квадрате
template< class T >
inline T vecLengthSquared( const point_base_t<T> &vec ) 
{
    return vec.x * vec.x + vec.y * vec.y;
}

//ƒлина вектора
template< class T >
inline T vecLength( const point_base_t<T> &vec ) 
{
    return sqrt_t( vecLengthSquared(vec) );
}

//Ќормализаци€ вектора
//»спользуйте перегрузку с length если длина вектора известна
template< class T >
inline point_base_t<T> vecNormalize( const point_base_t<T> &vec, T length ) 
{
    ASSERT( length == vecLength(vec) );
    ASSERT( length > 0 );
    return vec / length;
}

template< class T >
inline point_base_t<T> vecNormalize( const point_base_t<T> &vec ) 
{
    return vecNormalize( vec, vecLength(vec) );
}
///////////////////////////////////////////////////////////////////////////////

//Ћежит ли точка pt слева от пр€мой получаемой при движении от from до to
template< class T > 
bool isOnLeftSide( const point_base_t<T> &from, const point_base_t<T> &to, const point_base_t<T> &pt )
{
    //ƒл€ того чтобы пон€ть с какой стороны лежит точка, 
    //определим угол между этими векторами если он лежит в интервале [0, +Pi], 
    //то точка находитс€ с левой стороны 
    //ƒл€ этого воспользуемс€ скал€рным произведением, которое будет положительным если
    //угол лежит в интервале [-Pi/2, +Pi/2].
    const point_base_t<T> vec1( pt.x - from.x, pt.y - from.y );

    //ƒл€ того чтобы перейти от интервала [0, +Pi] к [-Pi/2, +Pi/2] повернЄм 
    //данный вектор на Pi/2:
    //Ёквивалентно point_base_t<T> vec( to - from ); SWAP( vec2.x, vec2.y ); vec2.y = -vec2.y;
    const point_base_t<T> vec2( to.y - from.y, from.x - to.x );

    //»так, скал€рное произведение vec1 и vec2
    return vecDotProduct(vec1, vec2) > 0;
}
//////////////////////////////////////////////////////////////////////////////////////

template< class T >
inline point_base_t<T> minEachDim( const point_base_t<T> &a, const point_base_t<T> &b ) 
{
    return point_base_t<T>(
        min(a.x, b.x),
        min(a.y, b.y)
    );
}
//////////////////////////////////////////////////////////////////////////////////////

template< class T >
inline point_base_t<T> maxEachDim( const point_base_t<T> &a, const point_base_t<T> &b ) 
{
    return point_base_t<T>(
        max(a.x, b.x),
        max(a.y, b.y)
    );
}
//////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////
typedef point_base_t<int> point_t;
//////////////////////////////////////////////////////////////////////////////////////


#endif
