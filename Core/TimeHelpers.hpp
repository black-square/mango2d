#ifndef TimeHelpers_h__
#define TimeHelpers_h__

#include <limits>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����� ��������� �������� ��������� ��������� ��������. ������ ��������� �������, ����� 
// ������ ������ Set, �������� ����� ��������� ������ � ����������
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template< class T >
class ValueChangeSmoother
{
public:
  ValueChangeSmoother() { SetTmmediately(0); } 

  ValueChangeSmoother( T _curValue, T _diffPerTick ) 
  {
    Init( _curValue, _diffPerTick );
  }
  
  void Init( T _curValue, T _diffPerTick )
  {
    curValue = destValue = _curValue;
    diffPerTick = _diffPerTick;
  }

  void SetTmmediately( T val ) { curValue = destValue = val; } 

  void Set( T val ) 
  { 
    destValue = val; 
    correctDiffPerTick();
  } 
  
  void SetSpeed( T _diffPerTick )
  {
    diffPerTick = _diffPerTick;
    correctDiffPerTick();
  }

  T Get() const { return curValue; }

  T Tick()
  {
    if( curValue != destValue )
      curValue = CalcNextVal( diffPerTick );

    return Get();
  }
  
  T Tick( float deltaTime )
  {
    if( curValue != destValue )
      curValue = CalcNextVal( diffPerTick * deltaTime );

    return Get();
  }
 
private:
  void correctDiffPerTick()
  {
    if( (destValue >= curValue) != (diffPerTick > 0) )
      diffPerTick = -diffPerTick;
  }

  T CalcNextVal( float diff ) const
  {
    const T nextValue = curValue + diff;

    return (curValue < destValue) != (nextValue > destValue ) ? 
           nextValue : destValue;
  }
  
private:
  T curValue;
  T destValue;
  T diffPerTick;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////
// ������������� ������ ��������� �������� ������������ ����� ��� �������������
// � ������������ ��������������.
// �������� � ���������� ���������� ����������.
//////////////////////////////////////////////////////////////////////////////////////
template< class TimeT> 
class SimpleTimer
{   
public:
  SimpleTimer() { Reset(); }
  explicit SimpleTimer( TimeT savedTotalTime ) { Reset(savedTotalTime); }    

  //�������� ������ � �������� ���������
  void Reset() { curTime = totalTime = GetUndef(); }

  //�������� ������ � �������� ��������� � ��������� �������� savedTotalTime
  void Reset( TimeT savedTotalTime ) { curTime = GetUndef(); totalTime = savedTotalTime; }

  //��������� ������ �� ������������ ����� time ������
  void Start( TimeT time ) { ASSERT(time >= 0); curTime = totalTime = time; }
   
  //������������� �� ��������� �� ����������� ������ Start
  void Start() { ASSERT(time >= 0); curTime = totalTime; }

  //���������� ������
  void Stop() { curTime = GetUndef(); }
    
  //������� �� ������ � ������� ������ � ����� ������������ ��� �� ���������
  bool IsInProgress() const { return curTime != GetUndef(); }
   
  //���������� ����� ����������� � ���������� ������ Start, ��� ��������� ������ 
  //� ���������� ������ Start ������� Restart
  //������������ Start(time); Stop();
  void SetTotalTime( TimeT time ) { ASSERT(time >= 0); totalTime = time;  } 
  
  //�����, �� ������� ��� ������� ������ � ��������� ���
  TimeT GetTotalTime() const { return totalTime; }
  
  //����� �� ������������ �������
  TimeT GetTimeToAlarm() const { return curTime; }
  
  //������ �������� ������� deltaTime.
  //���� ������� ���������� true, ������ �������� ������� ������. ��� ����
  //����� ����� ��������� ������ ����� ������� Start() ��� Restart()
  bool Tick( TimeT deltaTime )
  {          
    if ( IsInProgress() )
    {
      curTime -= deltaTime;

      if ( curTime <= 0 ) 
      { 
        Stop();      
        return true;
      }
    }

    return false;
  } 

  //���������� ������� Tick, �� ������������� ������������� ������ 
  //�� �� �� ����� ����� ��� ������������
  bool TickWithRestart( TimeT deltaTime )
  {
    if ( IsInProgress() )
      return TickWithRestartNonStop( deltaTime );

    return false;
  }

  //���������� ������� TickWithRestart, �� ������� ����� ��� ������ 
  //������ ��� �������. ��������� ����� �������� �������.
  bool TickWithRestartNonStop( TimeT deltaTime )
  {
    ASSERT( IsInProgress() );

    curTime -= deltaTime;

    if ( curTime <= 0 ) 
    { 
      //��� ��������� �������� ��������� �����, ���������� � �������� ������������
      curTime += totalTime;      
      return true;
    }

    return false;
  }

private:
  static TimeT GetUndef() { return std::numeric_limits<TimeT>::min(); } 

private:
  TimeT curTime;   
  TimeT totalTime;     
};

//������� ������� ������ � ������ ������ ������� �� ������������ � ���������
template<class TimeT>
inline TimeT GetPercentProgress( const SimpleTimer<TimeT> &t )
{
  return (t.GetTotalTime() - t.GetTimeToAlarm()) * 100 / t.GetTotalTime(); 
}


#endif // TimeHelpers_h__