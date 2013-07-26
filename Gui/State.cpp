#include "stdafx.h"
#include "State.h"

namespace Gui {
void State::LButtonDown( Point pos )
{
  OnLButtonDown( pos );

  BOOST_FOREACH( IWidget::TPtrParam p, m_widgets )
    if( p->GetRect().isContain(pos) )
      p->OnLButtonDown( pos );  
}
//////////////////////////////////////////////////////////////////////////

void State::LButtonUp( Point pos )
{
  OnLButtonUp( pos );

  BOOST_FOREACH( IWidget::TPtrParam p, m_widgets )
    if( p->GetRect().isContain(pos) )
      p->OnLButtonUp( pos );
}
//////////////////////////////////////////////////////////////////////////

void State::MouseMove( Point pos )
{
  OnMouseMove( pos );
}
//////////////////////////////////////////////////////////////////////////

void State::KeyDown( SDLKey sym, SDLMod mod, Uint16 unicode )
{
  OnKeyDown( sym, mod, unicode );
}
//////////////////////////////////////////////////////////////////////////

void State::Update()
{
  OnUpdate();
}
//////////////////////////////////////////////////////////////////////////

void State::Render( float deltaTime ) const 
{
  BOOST_FOREACH( IWidget::TPtrParam p, m_widgets )
    p->Render();

  OnRender( deltaTime );
}
//////////////////////////////////////////////////////////////////////////
} //namespace Gui
