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


#endif // TimeHelpers_h__