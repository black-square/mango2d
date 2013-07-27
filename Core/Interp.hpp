#ifndef Interp_h__
#define Interp_h__

template <typename VecT, typename SclrT>
inline VecT Lerp( const VecT &left, const VecT &right, SclrT k )
{
	return right * k + left * (1 - k);
}
//////////////////////////////////////////////////////////////////////////

//Cheap sinus(x) approximation 
template <typename T>
inline T SerpStepFactor( T k )
{
  //Smoothstep
  //http://sol.gfxile.net/interpolation/index.html#c4
  return k * k * (3 - 2 * k);
}
//////////////////////////////////////////////////////////////////////////

template <typename T>
inline T SquaredStepFactor( T k )
{
  return k * k;
}
//////////////////////////////////////////////////////////////////////////

template <typename T>
inline T CubicStepFactor( T k )
{
  return k * k * k;
}
//////////////////////////////////////////////////////////////////////////

template <typename T>
class SquaredWithBounceStepFactor
{
public:
  SquaredWithBounceStepFactor( T bouncePos, T bounceHeight )
  {
    CalcCoef( bouncePos, bounceHeight );
  }
    
  T operator()( T x ) const
  {
    return  x <= m_bouncePos ? 
      m_f1 * x * x:
      m_g1 * x * x + m_g2 * x + m_g3;
  } 

private:
  void CalcCoef( T b, T v )
  {
    // Maple:
    //  restart;
    //  constants:=constants, B, V:
    //  F := x -> C2 * x^2 + C1 * x^1 + C0:
    //  F1 := unapply( diff(F(x), x ), x ):
    //  Sys := { F(0) = 0, F(B) = 1, F1(0) = 0 }:
    //  ResultFormula1 := factor(eval(F(x),solve(Sys)));
    //  G := x -> C2 * x^2 + C1 * x^1 + C0:
    //  Sys := { G(B) = 1, G(1) = 1, G(B + (1 - B)/2) = V }:
    //  ResultFormula2 := eval(G(x),solve(Sys));
    //  Test := eval([ResultFormula1, ResultFormula2], {V = 9/10, B = 4/5} );
    //  plot( Test, x=0..1, y=0..1 );
    m_bouncePos = b;

    const T b2 = b * b;
    const T denom = ( 1 + b2 - 2 * b );

    m_f1 = 1 / b2;
    m_g1 = 4 * (1-v) / denom;
    m_g2 = 4 * (b+1) * (v-1) / denom;
    m_g3 = ( 1 - 4*b*v + 2*b + b2 ) / denom;  
  } 

private:
  T m_bouncePos;
  T m_f1;
  T m_g1;
  T m_g2;
  T m_g3; 
};
//////////////////////////////////////////////////////////////////////////

template <typename T>
class ThreePointStepFactor
{
public:
  ThreePointStepFactor( T left, T middle, T right )
  { 
    const T allPoints[] = { left, middle, right };  
    m_minmax = Deref( boost::minmax_element(allPoints, allPoints + ARRAY_SIZE(allPoints)) );
    m_c0 = left;
    m_c2 = -11*left + 16*middle -  5*right; 
    m_c3 =  18*left - 32*middle + 14*right; 
    m_c4 =  -8*left + 16*middle -  8*right;  
  }
  
  T operator()( T x ) const
  {
    const float x2 = x * x;
    const float val =  m_c4*x2*x2 + m_c3*x2*x + m_c2*x2 + m_c0;
    return boost::algorithm::clamp( val, m_minmax.first, m_minmax.second );
  }

private:
  template<class IterT>
  static std::pair<T, T> Deref( const std::pair<IterT, IterT> &pr )
  {
    return std::pair<T, T>( *pr.first, *pr.second );    
  }

private:
  //Maple:
  //  restart;
  //  constants:=constants, left, middle, right:
  //  F := x -> c4 * x^4 + c3 * x^3 + c2 * x^2 + c1 * x^1 + c0:
  //  F1 := unapply( diff(F(x), x ), x ):
  //  Sys := { F(0) = left, F(1/2) = middle, F(1) = right, F1(0) = 0, F1(1) = 0 }:
  //  Rez := solve(Sys);
  //  Test := eval([eval(F(x),Rez)], {left = 0, middle = 0.3, right = 1} );
  //  plot( Test, x=0..1, y=0..1 );
  float m_left;
  float m_right;
  float m_c0;
  float m_c2;
  float m_c3;
  float m_c4;
  std::pair<T, T> m_minmax;
};
//////////////////////////////////////////////////////////////////////////

template <typename T>
inline T SmoothDampStepFactor( T k )
{
  //Данная функция быстро набирает скорость и плавно останавливается - 
  //её график похож на Serp но смещён вправо.
  //Интерполяция с её помощью смотрится приятнее для глаза, чем Serp и SerpX2.
  //Получена при помощи следующего кода на Maple:
  /*
    restart;
    F := x -> C0 * x^4 + C1 * x^3 + C2 * x^2 + C3 * x^1;
    F1 := unapply( diff(F(x), x ), x );
    F2 := unapply( diff(F(x), x, x ), x );
    Sys := { F1(0) = 0, F1(1) = 0, F2(1/3) = 0, F(1) = 1 }:
    Rez := solve(Sys);
    SmoothStep := x -> ((x) * (x) * (3 - 2 * (x))):
    ResultFormula := factor(eval(F(x),Rez));
    plot( [eval(F(x),Rez), eval(F1(x),Rez), eval(F2(x),Rez), SmoothStep(x), SmoothStep(SmoothStep(x))], x = 0..1, y=-0.5..1.5 );
  */
  
  const T k2 = k * k;
  return  k2 * ( 3 * k2 - 8 * k + 6 ); 
}
//////////////////////////////////////////////////////////////////////////

//Cheap sinus(x)  interpolation
template <typename VecT, typename SclrT>
inline VecT Serp( const VecT &left, const VecT &right, SclrT k )
{
  return Lerp( left, right, SerpStepFactor(k) );
}
//////////////////////////////////////////////////////////////////////////

//Cheap approximation of sinus(sinus(x)) interpolation
template <typename VecT, typename SclrT>
inline VecT SerpX2( const VecT &left, const VecT &right, SclrT k )
{
  return Lerp( left, right, SerpStepFactor(SerpStepFactor(k)) );
}  
//////////////////////////////////////////////////////////////////////////

//Asymmetric S-curve interpolation. Fast in - Slow out.
//Fast racing at the beginning and a long stopping.
template <typename VecT, typename SclrT>
inline VecT SmoothDamp( const VecT &left, const VecT &right, SclrT k )
{
  return Lerp( left, right, SmoothDampStepFactor(k) );
}
//////////////////////////////////////////////////////////////////////////

// SmoothCritDamp for ease-in / ease-out smoothing
// Позволяет плавно изменять величину от текущего значения curPos до целевого toPos,
// таким образом, что на плавности изменения не отражается перемещение 
// конечного значения toPos во время движения. Поведение моделирует резинку или 
// пружину на которой подвешен один объект, с координатными curPos, к другому с координатами
// toPos
// Текущая скорость хранится во внешней переменной velocity, а изменение времени с последнего
// вызова передаётся в timeDelta
// Жёсткость пружины определяется, через параметр smoothTime, который характеризует максимальное 
// расстояние от текущей позиции до целевой (время лага):
//    <Максимальное расстояние> = <Текущая скорость> * smoothTime; 
template <typename VecT, typename SclrT>
inline VecT SmoothCritDamp(const VecT &curPos, const VecT &toPos, VecT &velocity, SclrT timeDelta, SclrT smoothTime )
{
  //Based on Game Programming Gems 4 Chapter 1.10
  const SclrT omega = 2.f / smoothTime;
  const SclrT x = omega * timeDelta;
  const SclrT exp = 1.f / ( 1.f + x + 0.48f * x * x + 0.235f * x * x * x );
  const VecT change = curPos - toPos;
  const VecT temp = ( velocity + omega * change ) * timeDelta;
  velocity = ( velocity - omega * temp ) * exp;  
  return toPos + ( change + temp ) * exp;
}

#endif // Interp_h__
