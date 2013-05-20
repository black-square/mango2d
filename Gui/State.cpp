#include "stdafx.h"
#include "Gui/State.h"


void GuiState::LButtonDown( Point pos )
{
  OnLButtonDown( pos );

  BOOST_FOREACH( IWidget::TPtrParam p, m_widgets )
    if( p->GetRect().isContain(pos) )
      p->OnLButtonDown( pos );  
}
//////////////////////////////////////////////////////////////////////////

void GuiState::LButtonUp( Point pos )
{
  OnLButtonUp( pos );

  BOOST_FOREACH( IWidget::TPtrParam p, m_widgets )
    if( p->GetRect().isContain(pos) )
      p->OnLButtonUp( pos );
}
//////////////////////////////////////////////////////////////////////////

void GuiState::KeyDown( SDLKey sym, SDLMod mod, Uint16 unicode )
{
  OnKeyDown( sym, mod, unicode );
}
//////////////////////////////////////////////////////////////////////////

void GuiState::Update( float deltaTime )
{
  OnUpdate( deltaTime );
}
//////////////////////////////////////////////////////////////////////////

void GuiState::Render()
{
  BOOST_FOREACH( IWidget::TPtrParam p, m_widgets )
    p->Render();

  OnRender();
}
//////////////////////////////////////////////////////////////////////////


