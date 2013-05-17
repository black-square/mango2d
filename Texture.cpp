#include "stdafx.h"
#include "Texture.h"


Texture::~Texture()
{
  Release();
}

void Texture::Release()
{
  if( m_pSurf != 0 )
  {
    SDL_FreeSurface( m_pSurf );
    m_pSurf = 0;
  }
}

void Texture::Load( const char *szFile )
{
  ASSERT( szFile != 0 );
  Release();

  SDL_Surface* pSurfTmp = SDL_LoadBMP(szFile);

	if( pSurfTmp == 0 ) 
	  LOG_FATAL( FMT("Texture loading error %s") % szFile );

	m_pSurf = SDL_DisplayFormat(pSurfTmp);
  SDL_FreeSurface(pSurfTmp);

  if( m_pSurf == 0 )
    LOG_FATAL( FMT("Texture conversion error %s") % szFile );    
}

void Texture::Load( const char *szFile, const Color &transpColor )
{
  Load( szFile );
  
  const Uint32 sdlColor = SDL_MapRGB( m_pSurf->format, transpColor.r(), transpColor.g(), transpColor.b() );
  VERIFY( SDL_SetColorKey(m_pSurf, SDL_SRCCOLORKEY | SDL_RLEACCEL, sdlColor) == 0 );
}

void Draw( SDL_Surface *pDest, const Texture &tex, point_t pos )
{
  ASSERT( pDest != 0 );

  SDL_Rect DestR = { pos.x, pos.y };

	VERIFY( SDL_BlitSurface(tex.m_pSurf, NULL, pDest, &DestR) == 0 );
}