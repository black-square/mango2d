#ifndef TimeHelpers_h__
#define TimeHelpers_h__

#include <limits>

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
  void Start() { ASSERT(totalTime != GetUndef()); curTime = totalTime; }

  //���������� ������
  void Stop() { curTime = GetUndef(); }
    
  //������� �� ������ � ������� ������ � ����� ������������ ��� �� ���������
  bool IsInProgress() const { return curTime != GetUndef(); }
  
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

//////////////////////////////////////////////////////////////////////////////////////
// ����� ���������� ������ �������� � ��������� ��������� � ������������ � �������� 
// ���������. ������������ ���������� ������ ��������, �������� � ������������ 
// ���������� �� ��������� �������
//////////////////////////////////////////////////////////////////////////////////////
namespace TimeInterval
{
  template<class T>
  struct SBase
  {   
    T m_lowBound; 
    T m_hightBound;     
    T m_curValue;            
  };

  //��������� �������� � ����� ���������
  //����� ���������� ������ ������� ����� ������������ �� ������ ��������� 
  template<class T>  
  struct Discontinuous: public SBase<T>
  {    
    void Init(){ /*Nothing*/ }

    void Step()
    {
      if( this->m_curValue != this->m_hightBound )
        this->m_curValue += 1;
      else
        this->m_curValue = this->m_lowBound;
    }
  };

  //��������� �������� � ����� ���������
  //����� ���������� ������ ��� ����� ������� �������� �������� ���������� � 
  //�������� �������
  template<class T>  
  struct Continuous: public SBase<T>
  {
    void Init()
    {
      m_curStep = static_cast<T>(-1); // ����� �.�. �� ������ �� ���� �� ��� ������
    }

    void Step()
    {
      if( this->m_curValue == this->m_hightBound || this->m_curValue == this->m_lowBound )
        m_curStep = -m_curStep; //���� ���� ����� T = u8 ������� �� ������ �� �����, ��-�� �����������

      this->m_curValue += m_curStep;
    }

  private:
    T m_curStep; 
  };


  //����� � ������� ��������������� ������������
  template<
    //��� �������� � ���������
    class T, 
    //��������� �������� � ����� ���������
    //����� ���� ���� Discontinuous, ���� Continuous
    template<class> class StrategyT 
  > 
  class Processor: private StrategyT<T>
  {    
    typedef StrategyT<T> TBase;
  public:
    explicit Processor( T val = 0 )
    {
      InitFixed( val );
    }

    Processor( T lowBound, T hightBound, float time )
    {
      InitStepTime( lowBound, hightBound, time );
    }

    //���������������� �����
    //[lowBound, hightBound] - �������� ��������� �������� 
    //time - ����� ���������� ��������� �� 1
    void InitStepTime( T lowBound, T hightBound, float time )
    {
      TBase::Init();
      this->m_curValue = this->m_lowBound = lowBound; 
      this->m_hightBound = hightBound;  
      m_stepTime = time;
      m_curTime = 0;
    }

    //���������������� �����
    //[lowBound, hightBound] - �������� ��������� �������� 
    //time - ����� �� ������� �������� ��������� �� lowBound �� hightBound
    void InitIntervTime( T lowBound, T hightBound, float time )
    {
      InitStepTime( lowBound, hightBound, time / (hightBound - lowBound) );
    }

    void InitFixed( T val )
    {
      InitStepTime( val, val, std::numeric_limits<float>::max() );
    }

    //���������� ������� ����� �� deltaTime
    void Tick( float deltaTime )
    {
      m_curTime += deltaTime;

      while( m_curTime >= m_stepTime )
      {
        m_curTime -= m_stepTime;
        TBase::Step();
      }
    }

    //������� ��������
    T Get() const { return this->m_curValue; }

  private:
    float m_stepTime;
    float m_curTime;
  };
}


#endif // TimeHelpers_h__