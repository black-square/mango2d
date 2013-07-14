#ifndef TimeHelpers_h__
#define TimeHelpers_h__

#include <limits>

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
  void Start() { ASSERT(totalTime != GetUndef()); curTime = totalTime; }

  //Остановить таймер
  void Stop() { curTime = GetUndef(); }
    
  //Запущен ли таймер в текущий момент и время срабатывания ещё не наступило
  bool IsInProgress() const { return curTime != GetUndef(); }
  
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

//////////////////////////////////////////////////////////////////////////////////////
// Класс циклически меняет значение в некотором интервале в соответствии с заданной 
// скоростью. Пользователю достаточно задать интервал, скорость и периодически 
// уведомлять об изменении времени
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

  //Стратегия перехода в конце интервала
  //После достижения правой границы число сбрасывается на начало интервала 
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

  //Стратегия перехода в конце интервала
  //После достижения правой или левой границы значение начинает возрастать в 
  //обратную сторону
  template<class T>  
  struct Continuous: public SBase<T>
  {
    void Init()
    {
      m_curStep = static_cast<T>(-1); // минус т.к. на первом же шаге мы его меняем
    }

    void Step()
    {
      if( this->m_curValue == this->m_hightBound || this->m_curValue == this->m_lowBound )
        m_curStep = -m_curStep; //Даже если будет T = u8 проблем со знаком не будет, из-за продвижения

      this->m_curValue += m_curStep;
    }

  private:
    T m_curStep; 
  };


  //Класс с которым взаимодействует пользователь
  template<
    //Тип значений в интервале
    class T, 
    //Стратегия перехода в конце интервала
    //Может быть либо Discontinuous, либо Continuous
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

    //Инициализировать класс
    //[lowBound, hightBound] - Интервал изменения значений 
    //time - время увелечения интервала на 1
    void InitStepTime( T lowBound, T hightBound, float time )
    {
      TBase::Init();
      this->m_curValue = this->m_lowBound = lowBound; 
      this->m_hightBound = hightBound;  
      m_stepTime = time;
      m_curTime = 0;
    }

    //Инициализировать класс
    //[lowBound, hightBound] - Интервал изменения значений 
    //time - время за которое значение изменится от lowBound до hightBound
    void InitIntervTime( T lowBound, T hightBound, float time )
    {
      InitStepTime( lowBound, hightBound, time / (hightBound - lowBound) );
    }

    void InitFixed( T val )
    {
      InitStepTime( val, val, std::numeric_limits<float>::max() );
    }

    //Изменилось текущее время на deltaTime
    void Tick( float deltaTime )
    {
      m_curTime += deltaTime;

      while( m_curTime >= m_stepTime )
      {
        m_curTime -= m_stepTime;
        TBase::Step();
      }
    }

    //Текущее значение
    T Get() const { return this->m_curValue; }

  private:
    float m_stepTime;
    float m_curTime;
  };
}


#endif // TimeHelpers_h__