#ifndef Size_h__
#define Size_h__

template<typename T>
struct SizeBase
{
  typedef T TValueType;

  T w;
  T h;

  SizeBase(): w(0), h(0) {}
  SizeBase( T _w, T _h ): w(_w), h(_h) {}

  template< class T2>
  explicit SizeBase( const SizeBase<T2> &other ): w(static_cast<T>(other.w)), h(static_cast<T>(other.h)) {}

  void set( T _w, T _h ) { w = _w; h = _h; }
  void zeroize() { w = 0; h = 0; }
  bool isZero() const { return w == 0 && h == 0; } 

  SizeBase operator-() const { return SizeBase( -w, -h ); }

  friend SizeBase operator+( const SizeBase &a, const SizeBase &b ) { return SizeBase( a.w + b.w, a.h + b.h ); }
  friend SizeBase operator-( const SizeBase &a, const SizeBase &b ) { return poisize_base_tnt_base_t( a.w - b.w, a.h - b.h ); }

  friend SizeBase operator*( const SizeBase &a, T val )  { return SizeBase( a.w * val, a.h * val ); }
  friend SizeBase operator*( T val, const SizeBase &a )  { return a * val; }
  friend SizeBase operator/( const SizeBase &a, T val )  { return SizeBase( a.w / val, a.h / val ); }

  SizeBase& operator+=( const SizeBase &_in ) { w += _in.w; h += _in.h; return *this; }
  SizeBase& operator-=( const SizeBase &_in ) { w -= _in.w; h -= _in.h; return *this; }   

  SizeBase& operator+=( T v ) { w += v; h += v; return *this; }
  SizeBase& operator-=( T v ) { w -= v; h -= v; return *this; }
  SizeBase& operator*=( T v ) { w *= v; h *= v; return *this; }
  SizeBase& operator/=( T v ) { w /= v; h /= v; return *this; }
};
//////////////////////////////////////////////////////////////////////////////////////
template <typename T>
inline bool operator == ( const SizeBase<T> &a, const SizeBase<T> &b )
{
  return a.w == b.w && a.h == b.h;
}
//////////////////////////////////////////////////////////////////////////////////////
template <typename T>
inline bool operator != ( const SizeBase<T> &a, const SizeBase<T> &b )
{
  return !(a == b);
}
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Векторные операции над точкой
///////////////////////////////////////////////////////////////////////////////

//Скалярное произведение
template< class T >
inline T vecDotProduct( const SizeBase<T> &vec1, const SizeBase<T> &vec2 ) 
{
  return vec1.w * vec2.w + vec1.h * vec2.h;
}

//Длина вектора в квадрате
template< class T >
inline T vecLengthSquared( const SizeBase<T> &vec ) 
{
  return vec.w * vec.w + vec.h * vec.h;
}

//Длина вектора
template< class T >
inline T vecLength( const SizeBase<T> &vec ) 
{
  return sqrt_t( vecLengthSquared(vec) );
}

template< class T >
inline SizeBase<T> minEachDim( const SizeBase<T> &a, const SizeBase<T> &b ) 
{
  return SizeBase<T>(
    std::min(a.w, b.w),
    std::min(a.h, b.h)
    );
}
//////////////////////////////////////////////////////////////////////////////////////

template< class T >
inline SizeBase<T> maxEachDim( const SizeBase<T> &a, const SizeBase<T> &b ) 
{
  return SizeBase<T>(
    std::max(a.w, b.w),
    std::max(a.h, b.h)
    );
}
//////////////////////////////////////////////////////////////////////////////////////

template< class T >
inline T manhattanDistance( const SizeBase<T> &a, const SizeBase<T> &b ) 
{
  return std::abs(a.w - b.w) + std::abs(a.h - b.h);
}
//////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////
typedef SizeBase<int> Size;
//////////////////////////////////////////////////////////////////////////////////////

#endif // Size_h__
