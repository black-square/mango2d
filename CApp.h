
#ifndef _CAPP_H_
#define _CAPP_H_

#include <SDL.h>


#include "CEvent.h"
#include "Texture.h"
#include "GameField.h"
#include "GameFieldRender.h"
#include "GameLogic.h"
#include "TimeHelpers.hpp"

#include <boost/chrono/system_clocks.hpp>


class AutoPlay
{
public:
  AutoPlay() {  Reset(); }

  void Reset();
  void Update( GameField &field, GameLogic &logic );
  const GameLogic::TPoints &GetMarks() const { return m_marks; }

private:
  GameLogic::TPoints m_marks;
  int m_state;
  GameLogic::TMove m_nextMove;
};

//==============================================================================
class CApp : public CEvent {
    private:
        bool            Running;
        SDL_Surface*    Surf_Display; 

        typedef boost::chrono::system_clock TClock;

    private:
        Texture	background;
        GameField m_field;
        GameLogic m_logic;
        GameFieldRender m_fieldRender;
        GameFieldRender::PosOpt m_prevCellPos;
        AutoPlay m_autoPlay;
        SimpleTimer<float> m_autoPlayTimer;
        TClock::time_point m_prevClock;

    public:
      CApp();
      
      int OnExecute();

    public:
       bool OnInit();
       void OnEvent(SDL_Event* Event);
       void OnLButtonDown(int mX, int mY);

       void UpdateState();

       void OnLButtonUp(int mX, int mY);
       void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
       void OnExit();
       void OnLoop();
       void OnRender();
       void OnCleanup();
};

//==============================================================================

#endif
