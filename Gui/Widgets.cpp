#include "stdafx.h"
#include "Widgets.h"
#include "Engine/Audio/SoundManager.h"

namespace Gui {

void Image::Render() const
{
  Draw( *m_pTex, m_rect, 0, m_color );
}
//////////////////////////////////////////////////////////////////////////

void Label::SetText( const std::string &text, Color color /*= Color::make_white()*/ )
{
 DrawHQ( *m_pFont, text.c_str(), color, m_tex ); 
}
//////////////////////////////////////////////////////////////////////////

void Label::Render() const
{
  if( !m_tex.IsValid() )
    return;
  
  Point realPos;

  switch (m_align)
  {
   case Left:   realPos = m_pos;  break;
   case Center: realPos = m_pos - Point( m_tex.GetSize().w / 2, 0 ); break;
   case Right:  realPos = m_pos - Point( m_tex.GetSize().w, 0 ); break;
  }
 
  Draw( m_tex,  realPos );
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
  PlaySound( "./_data/click.wav" );
}
//////////////////////////////////////////////////////////////////////////

void Button::OnLButtonUp( Point pos )
{
  if( m_curState == Pressed && m_callback )
    m_callback();

  m_curState = Released;
}

} //namespace Gui 