#ifndef _CAPP_H_
#define _CAPP_H_

#include <SDL.h>

#include "AppBase.h"
#include "Texture.h"
#include "GameField.h"
#include "GameFieldRender.h"
#include "GameLogic.h"
#include "TimeHelpers.hpp"
#include "Font.h"
#include "AutoPlay.h"

//==============================================================================
class App: public AppBase, private IGameLogicEvents 
{
public:
  App();

  void OnInit();
  void OnLButtonDown(int mX, int mY);
  void OnLButtonUp(int mX, int mY);
  void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
  void OnLoop( float deltaTime );
  void OnRender( SDL_Surface *pDisplay );
  void OnSwap( point_t p1, point_t p2 );

private:
  Texture	background;
  GameField m_field;
  GameLogic m_logic;
  GameFieldRender m_fieldRender;
  GameFieldRender::PosOpt m_prevCellPos;
  AutoPlay m_autoPlay;
  SimpleTimer<float> m_autoPlayTimer;

  Font m_font;
  int m_movesCount;
  Texture m_infoText;
};

//==============================================================================

#endif
