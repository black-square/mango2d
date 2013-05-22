#include "stdafx.h"
#include "Font.h"

void Font::Reset()
{
  if( m_font != 0 )
  {
    TTF_CloseFont( m_font );
    m_font = 0;
  }
}
//////////////////////////////////////////////////////////////////////////

void Font::Load( const char *szFile, int ptsize )
{
  ASSERT( szFile != 0 );
  Reset();

  m_font = TTF_OpenFont( szFile, ptsize );

  if( m_font == 0 )
    LOG_FATAL( FMT("Font loading error %s") % szFile );
}
//////////////////////////////////////////////////////////////////////////

void Draw( const Font &font, const char *szText, Color fg, Texture &res )
{                  
  ASSERT( font.m_font != 0 );
  ASSERT( szText != 0 );

  if( *szText == '\0' )
  {
    res.Reset();
    return;
  }

  SDL_Surface * const pRez = TTF_RenderText_Solid( font.m_font, szText, fg.toSDL_Color() );

  if( pRez == 0 )
    LOG_FATAL( FMT("Text render error: %s") % szText );

  res.Reset( pRez );
}
//////////////////////////////////////////////////////////////////////////

void DrawHQ( const Font &font, const char *szText, Color fg, Texture &res )
{                  
  ASSERT( font.m_font != 0 );
  ASSERT( szText != 0 );

  if( *szText == '\0' )
  {
    res.Reset();
    return;
  }

  SDL_Surface * const pRez = TTF_RenderText_Blended( font.m_font, szText, fg.toSDL_Color() );

  if( pRez == 0 )
    LOG_FATAL( FMT("Text render error: %s") % szText );

  res.Reset( pRez );
}


