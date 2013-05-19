//==============================================================================
#include "stdafx.h"
#include "App.h"
#include "GuiStateAutoPlay.h"

void App::OnInit() 
{
  SDL_WM_SetCaption("Dmitry Shesterkin", "Dmitry Shesterkin");
  
  SetMainState(); 
}
//////////////////////////////////////////////////////////////////////////

void App::OnUpdate( float deltaTime ) 
{
  m_pGuiState->OnUpdate( deltaTime );
}
//////////////////////////////////////////////////////////////////////////

void App::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
  m_pGuiState->OnKeyDown( sym, mod, unicode );
}
//////////////////////////////////////////////////////////////////////////

void App::OnLButtonDown(int mX, int mY) 
{
  m_pGuiState->OnLButtonDown( point_t(mX, mY) );      
}
//////////////////////////////////////////////////////////////////////////

void App::OnLButtonUp(int mX, int mY)
{
  m_pGuiState->OnLButtonUp( point_t(mX, mY) );      
}
//////////////////////////////////////////////////////////////////////////

void App::OnRender( SDL_Surface *pDisplay ) 
{
  m_pGuiState->OnRender( pDisplay );
  VERIFY( SDL_Flip(pDisplay) == 0 );
}

void App::SetState( GuiState::TPtrParam p )
{
  m_pGuiState = p;
  m_pGuiState->SetManager(this);
}

void App::SetMainState()
{
  m_pGuiState = boost::make_shared<GuiStateAutoPlay>();
  m_pGuiState->SetManager(this);
}



