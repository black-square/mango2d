//==============================================================================
#include "stdafx.h"
#include "App.h"
#include "GuiStates/StateMain.h"
#include "Engine/Audio/SoundManager.h"
#include "GuiStates/LogicConsts.h"

void App::OnInit() 
{
  SDL_WM_SetCaption("The Game", "The Game");
  InitGlobalSoundManager();
  SetMainState(); 

  m_updateTimer.Start( Editor::LogicUpdateTime() );
}
//////////////////////////////////////////////////////////////////////////

void App::OnCleanup()
{
  DestroyGlobalSoundManager();
}
//////////////////////////////////////////////////////////////////////////

void App::OnUpdate( float deltaTime ) 
{
  if( m_updateTimer.TickWithRestartNonStop(deltaTime) )
  {
  if( m_pNextGuiState )
  {
    m_pGuiState = m_pNextGuiState;
    m_pNextGuiState.reset();
  }

    m_pGuiState->Update();
  }
}
//////////////////////////////////////////////////////////////////////////

void App::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
  m_pGuiState->KeyDown( sym, mod, unicode );
}
//////////////////////////////////////////////////////////////////////////

void App::OnMouseButtonDown( Point pos, Uint8 button ) 
{
  if( button == SDL_BUTTON_LEFT )
    m_pGuiState->LButtonDown( pos );      
}
//////////////////////////////////////////////////////////////////////////

void App::OnMouseButtonUp( Point pos, Uint8 button )
{
  if( button == SDL_BUTTON_LEFT )
    m_pGuiState->LButtonUp( pos );      
}
//////////////////////////////////////////////////////////////////////////

void App::OnMouseMove( Point pos )
{
  m_pGuiState->MouseMove(pos);
}
//////////////////////////////////////////////////////////////////////////

void App::OnRender( float deltaTime ) const
{
  m_pGuiState->Render( deltaTime );
}
//////////////////////////////////////////////////////////////////////////

void App::SetState( Gui::State::TPtrParam p )
{
  ASSERT( !m_pNextGuiState );
  ASSERT( p );

  p->SetManager(this);

  if( m_pGuiState )
    m_pNextGuiState = p;
  else
    m_pGuiState = p;
}
//////////////////////////////////////////////////////////////////////////

void App::SetMainState()
{
  SetState( boost::make_shared<GuiStateMain>() );
}



