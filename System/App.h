#ifndef _CAPP_H_
#define _CAPP_H_

#include "AppBase.h"
#include "Gui/State.h"

//==============================================================================
class App: public AppBase, private Gui::IStateManager 
{
public:
  void OnInit();
  void OnCleanup();
  void OnMouseButtonDown( Point pos, Uint8 button );
  void OnMouseButtonUp( Point pos, Uint8 button );
  void OnMouseMove( Point pos );
  void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
  void OnUpdate( float deltaTime );
  void OnRender() const;
  void SetState( Gui::State::TPtrParam p );
  void SetMainState();

private:
  Gui::State::TPtr m_pGuiState;
  Gui::State::TPtr m_pNextGuiState;
};

//==============================================================================

#endif
