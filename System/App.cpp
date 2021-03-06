#include "stdafx.h"
#include "App.h"
#include "Engine/Audio/SoundManager.h"
#include "Engine/IEngineParams.h"

void App::OnInit() 
{
  SDL_WM_SetCaption( EngineParams()->GetWindowTitle(), EngineParams()->GetWindowTitle() );
  InitGlobalSoundManager();
  SetMainState(); 

  m_updateTimer.Start( EngineParams()->GetUpdateStepTimeDelta() );
}
//////////////////////////////////////////////////////////////////////////

void App::OnCleanup()
{
  DestroyGlobalSoundManager();
}
//////////////////////////////////////////////////////////////////////////

void App::OnUpdate( float deltaTime ) 
{
  if( m_pNextGuiState )
  {
    m_pGuiState = m_pNextGuiState;
    m_pNextGuiState.reset();
  }

  m_pGuiState->Update( deltaTime );

  if( m_updateTimer.TickWithRestartNonStop(deltaTime) )
  {
    m_pGuiState->UpdateStep();
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
  SetState( EngineParams()->MakeMainState() );
}



