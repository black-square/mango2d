#ifndef Interp_h__
#define Interp_h__

template <typename VecT, typename SclrT>
inline VecT Lerp( const VecT &left, const VecT &right, SclrT k )
{
	return right * k + left * (1 - k);
}
//////////////////////////////////////////////////////////////////////////

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
inline T SmoothDampStepFactor( T k )
{
  //������ ������� ������ �������� �������� � ������ ��������������� - 
  //� ������ ����� �� Serp �� ������ ������.
  //������������ � � ������� ��������� �������� ��� �����, ��� Serp � SerpX2.
  //�������� ��� ������ ���������� ���� �� Maple:
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

//Cheap approximation of sinus(x) interpolation
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
// ��������� ������ �������� �������� �� �������� �������� curPos �� �������� toPos,
// ����� �������, ��� �� ��������� ��������� �� ���������� ����������� 
// ��������� �������� toPos �� ����� ��������. ��������� ���������� ������� ��� 
// ������� �� ������� �������� ���� ������, � ������������� curPos, � ������� � ������������
// toPos
// ������� �������� �������� �� ������� ���������� velocity, � ��������� ������� � ����������
// ������ ��������� � timeDelta
// Ƹ������� ������� ������������, ����� �������� smoothTime, ������� ������������� ������������ 
// ���������� �� ������� ������� �� ������� (����� ����):
//    <������������ ����������> = <������� ��������> * smoothTime; 
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
