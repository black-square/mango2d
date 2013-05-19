#include "stdafx.h"
#include "Texture.h"
#include <boost/algorithm/string/predicate.hpp>

void Texture::Reset( SDL_Surface *pSurf /*= 0*/ )
{
  if( m_pSurf != 0 )
    SDL_FreeSurface( m_pSurf );
    
  m_pSurf = pSurf;
}
//////////////////////////////////////////////////////////////////////////

void Texture::Load( const char *szFile )
{
  ASSERT( szFile != 0 );
  Reset();

  SDL_Surface* pSurfTmp = 0;

  if( boost::algorithm::ends_with(szFile, ".bmp") )
  {
    pSurfTmp = SDL_LoadBMP(szFile);

	  if( pSurfTmp == 0 ) 
	    LOG_FATAL( FMT("BMP texture loading error %s") % szFile );

	  m_pSurf = SDL_DisplayFormat(pSurfTmp);
  }
  else
  {
    pSurfTmp = IMG_Load(szFile);

	  if( pSurfTmp == 0 ) 
	    LOG_FATAL( FMT("IMG texture loading error %s") % szFile );

	  m_pSurf = SDL_DisplayFormatAlpha(pSurfTmp);  
  }      

  SDL_FreeSurface(pSurfTmp);

  if( m_pSurf == 0 )
    LOG_FATAL( FMT("Texture conversion error %s") % szFile );    
}
//////////////////////////////////////////////////////////////////////////

void Texture::Load( const char *szFile, const Color &transpColor )
{
  Load( szFile );
  
  const Uint32 sdlColor = SDL_MapRGB( m_pSurf->format, transpColor.r(), transpColor.g(), transpColor.b() );
  VERIFY( SDL_SetColorKey(m_pSurf, SDL_SRCCOLORKEY | SDL_RLEACCEL, sdlColor) == 0 );
}
//////////////////////////////////////////////////////////////////////////

point_t Texture::GetSize() const
{
  ASSERT( m_pSurf != 0 );

  return point_t( m_pSurf->w, m_pSurf->h );
}
//////////////////////////////////////////////////////////////////////////

void Draw( SDL_Surface *pDest, const Texture &tex, point_t pos )
{
  ASSERT( pDest != 0 );
  ASSERT( tex.m_pSurf != 0 );

  SDL_Rect destRect = { pos.x, pos.y };

	VERIFY( SDL_BlitSurface(tex.m_pSurf, NULL, pDest, &destRect) == 0 );
}
//////////////////////////////////////////////////////////////////////////

void Draw( SDL_Surface *pDest, const Texture &tex, rect_t rect )
{
  ASSERT( pDest != 0 );
  ASSERT( tex.m_pSurf != 0 );

  SDL_Rect srcRect = { 0, 0, tex.m_pSurf->w, tex.m_pSurf->h };
  SDL_Rect destRect = { rect.x1, rect.y1, rect.getWidth(), rect.getHeight() };

  VERIFY( SDL_BlitSurface(tex.m_pSurf, &srcRect, pDest, &destRect) == 0 );
}
