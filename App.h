#ifndef _CAPP_H_
#define _CAPP_H_

#include <SDL.h>

#include "AppBase.h"
#include "GuiState.h"

//==============================================================================
class App: public AppBase, private IGuiStateManager 
{
public:
  void OnInit();
  void OnLButtonDown(int mX, int mY);
  void OnLButtonUp(int mX, int mY);
  void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
  void OnUpdate( float deltaTime );
  void OnRender( SDL_Surface *pDisplay );
  void SetState( GuiState::TPtrParam p );
  void SetMainState();

private:
  GuiState::TPtr m_pGuiState;
};

//==============================================================================

#endif
