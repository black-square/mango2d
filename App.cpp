//==============================================================================
#include "stdafx.h"
#include "App.h"
#include "GuiStateMain.h"

void App::OnInit() 
{
  SDL_WM_SetCaption("Dmitry Shesterkin", "Dmitry Shesterkin");
  
  SetMainState(); 
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
}
//////////////////////////////////////////////////////////////////////////

void App::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
  m_pGuiState->KeyDown( sym, mod, unicode );
}
//////////////////////////////////////////////////////////////////////////

void App::OnLButtonDown(int mX, int mY) 
{
  m_pGuiState->LButtonDown( Point(mX, mY) );      
}
//////////////////////////////////////////////////////////////////////////

void App::OnLButtonUp(int mX, int mY)
{
  m_pGuiState->LButtonUp( Point(mX, mY) );      
}
//////////////////////////////////////////////////////////////////////////

void App::OnRender() 
{
  m_pGuiState->Render();
}

void App::SetState( GuiState::TPtrParam p )
{
  ASSERT( !m_pNextGuiState );
  ASSERT( p );

  m_pNextGuiState = p;
  m_pNextGuiState->SetManager(this);
}

void App::SetMainState()
{
  SetState( boost::make_shared<GuiStateMain>() );
}



