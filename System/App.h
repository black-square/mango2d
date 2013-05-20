#ifndef _CAPP_H_
#define _CAPP_H_

#include <SDL.h>

#include "AppBase.h"
#include "Gui/State.h"

//==============================================================================
class App: public AppBase, private Gui::IStateManager 
{
public:
  void OnInit();
  void OnLButtonDown(int mX, int mY);
  void OnLButtonUp(int mX, int mY);
  void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
  void OnUpdate( float deltaTime );
  void OnRender();
  void SetState( Gui::State::TPtrParam p );
  void SetMainState();

private:
  Gui::State::TPtr m_pGuiState;
  Gui::State::TPtr m_pNextGuiState;
};

//==============================================================================

#endif
