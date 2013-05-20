#include "stdafx.h"
#include "GuiWidgets.h"

void GuiImage::Render() const
{
  Draw( *m_pTex,  m_pos );
}
//////////////////////////////////////////////////////////////////////////

void GuiLabel::SetText( const std::string &text, Color color /*= Color::make_white()*/ )
{
 DrawHQ( *m_pFont, text.c_str(), color, m_tex ); 
}
//////////////////////////////////////////////////////////////////////////

void GuiLabel::Render() const
{
  Draw( m_tex,  m_pos );
}
//////////////////////////////////////////////////////////////////////////

void GuiButton::SetText( const std::string &text, Color color /*= Color::make_white()*/ )
{
  DrawHQ( *m_pFont, text.c_str(), color, m_labelTex ); 
}
//////////////////////////////////////////////////////////////////////////

void GuiButton::Render() const
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

void GuiButton::OnLButtonDown( Point pos )
{
  m_curState = Pressed;
}
//////////////////////////////////////////////////////////////////////////

void GuiButton::OnLButtonUp( Point pos )
{
  if( m_curState == Pressed && m_callback )
    m_callback();

  m_curState = Released;
}
