#include "stdafx.h"
#include "GuiWidgets.h"

void GuiImage::Render( SDL_Surface *pDisplay ) const
{
  Draw( pDisplay, *m_pTex,  m_pos );
}
//////////////////////////////////////////////////////////////////////////

void GuiLabel::SetText( const std::string &text, Color color /*= Color::make_white()*/ )
{
 DrawHQ( *m_pFont, text.c_str(), color, m_tex ); 
}
//////////////////////////////////////////////////////////////////////////

void GuiLabel::Render( SDL_Surface *pDisplay ) const
{
  Draw( pDisplay, m_tex,  m_pos );
}

