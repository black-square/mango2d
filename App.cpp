//==============================================================================
#include "stdafx.h"
#include "App.h"
#include "GuiStateAutoPlay.h"
#include "GuiStateMain.h"

void App::OnInit() 
{
  SDL_WM_SetCaption("Dmitry Shesterkin", "Dmitry Shesterkin");
  
  //SetMainState();
  SetState( boost::make_shared<GuiStateAutoPlay>() );
  
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
  m_pGuiState->OnLButtonDown( Point(mX, mY) );      
}
//////////////////////////////////////////////////////////////////////////

void App::OnLButtonUp(int mX, int mY)
{
  m_pGuiState->OnLButtonUp( Point(mX, mY) );      
}
//////////////////////////////////////////////////////////////////////////

void App::OnRender() 
{
  m_pGuiState->OnRender();
}

void App::SetState( GuiState::TPtrParam p )
{
  m_pGuiState = p;
  m_pGuiState->SetManager(this);
}

void App::SetMainState()
{
  m_pGuiState = boost::make_shared<GuiStateMain>();
  m_pGuiState->SetManager(this);
}



