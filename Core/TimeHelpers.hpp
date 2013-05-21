#ifndef TimeHelpers_h__
#define TimeHelpers_h__

#include <limits>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Класс позволяет сгладить изменения некоторой величины. Вместо изменения скачком, после 
// вызова метода Set, значение будет изменятся плавно и равномерно
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
// Универсальный таймер процессов длящихся определенное время или повторяющихся
// с определенной периодичностью.
// Помогает в реализации индикатора выполнения.
//////////////////////////////////////////////////////////////////////////////////////
template< class TimeT> 
class SimpleTimer
{   
public:
  SimpleTimer() { Reset(); }
  explicit SimpleTimer( TimeT savedTotalTime ) { Reset(savedTotalTime); }    

  //Сбросить таймер в исходное положение
  void Reset() { curTime = totalTime = GetUndef(); }

  //Сбросить таймер в исходное положение и запомнить интервал savedTotalTime
  void Reset( TimeT savedTotalTime ) { curTime = GetUndef(); totalTime = savedTotalTime; }

  //Запустить таймер на срабатывание через time секунд
  void Start( TimeT time ) { ASSERT(time >= 0); curTime = totalTime = time; }
   
  //Перезапустить со значением от предыдущего вызова Start
  void Start() { ASSERT(time >= 0); curTime = totalTime; }

  //Остановить таймер
  void Stop() { curTime = GetUndef(); }
    
  //Запущен ли таймер в текущий момент и время срабатывания ещё не наступило
  bool IsInProgress() const { return curTime != GetUndef(); }
   
  //Установить время сохраненное в предыдущем вызове Start, что позволяет вместо 
  //в дальнейшем вместо Start вызвать Restart
  //Эквивалентно Start(time); Stop();
  void SetTotalTime( TimeT time ) { ASSERT(time >= 0); totalTime = time;  } 
  
  //Время, на которое был запущен таймер в последний раз
  TimeT GetTotalTime() const { return totalTime; }
  
  //Время до срабатывания таймера
  TimeT GetTimeToAlarm() const { return curTime; }
  
  //Прошёл интервал времени deltaTime.
  //Если функция возвращает true, значит интервал времени прошёл. Для того
  //чтобы снова запустить таймер нужно вызвать Start() или Restart()
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

  //Аналогична функции Tick, но автоматически перезапускает таймер 
  //на то же время после его срабатывания
  bool TickWithRestart( TimeT deltaTime )
  {
    if ( IsInProgress() )
      return TickWithRestartNonStop( deltaTime );

    return false;
  }

  //Аналогична функции TickWithRestart, но требует чтобы при вызове 
  //таймер был запущен. Благодаря этому работает быстрее.
  bool TickWithRestartNonStop( TimeT deltaTime )
  {
    ASSERT( IsInProgress() );

    curTime -= deltaTime;

    if ( curTime <= 0 ) 
    { 
      //Для повышения точности учитываем время, оставшееся с прошлого срабатывания
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

//Сколько времени прошло с начала работы таймера до срабатывания в процентах
template<class TimeT>
inline TimeT GetPercentProgress( const SimpleTimer<TimeT> &t )
{
  return (t.GetTotalTime() - t.GetTimeToAlarm()) * 100 / t.GetTotalTime(); 
}


#endif // TimeHelpers_h__