#include "stdafx.h"
#include "Gui/Widgets.h"

namespace Gui {

void Image::Render() const
{
  Draw( *m_pTex,  m_pos );
}
//////////////////////////////////////////////////////////////////////////

void Label::SetText( const std::string &text, Color color /*= Color::make_white()*/ )
{
 DrawHQ( *m_pFont, text.c_str(), color, m_tex ); 
}
//////////////////////////////////////////////////////////////////////////

void Label::Render() const
{
  Draw( m_tex,  m_pos );
}
//////////////////////////////////////////////////////////////////////////

void Button::SetText( const std::string &text, Color color /*= Color::make_white()*/ )
{
  DrawHQ( *m_pFont, text.c_str(), color, m_labelTex ); 
}
//////////////////////////////////////////////////////////////////////////

void Button::Render() const
{
  Draw( *m_pBack,  m_rect, m_curState );

  Rect labelRect( Point(0, 0), m_labelTex.GetSize() );
  labelRect.setPosCenter( m_rect.getCenter() ); 

  if( m_curState == Pressed )
  {
    const int diff = m_rect.getHeight() / 15;
    labelRect.moveOn( diff, diff );
  } 

  Draw( m_labelTex, labelRect );
}
//////////////////////////////////////////////////////////////////////////

void Button::OnLButtonDown( Point pos )
{
  m_curState = Pressed;
}
//////////////////////////////////////////////////////////////////////////

void Button::OnLButtonUp( Point pos )
{
  if( m_curState == Pressed && m_callback )
    m_callback();

  m_curState = Released;
}

} //namespace Gui 