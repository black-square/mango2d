#include "stdafx.h"
#include "Texture.h"
#include <boost/algorithm/string/predicate.hpp>

void Texture::Reset( SDL_Surface *pSurf )
{
  LoadImpl( pSurf, 1 );
}
//////////////////////////////////////////////////////////////////////////

void Texture::Reset()
{
  if( m_hTex != INVALID_TEX_HANDLE )
  {
    glDeleteTextures( 1, &m_hTex );
    ASSERT( glGetError() == GL_NO_ERROR );
    m_hTex = INVALID_TEX_HANDLE;
  }
}
//////////////////////////////////////////////////////////////////////////

std::pair<int, int> Texture::GetTexMode( const SDL_Surface *pSurf ) const
{
  ASSERT( pSurf != 0 );

  if (pSurf->format->BytesPerPixel == 4)
  {
    if (pSurf->format->Rmask == 0x000000ff)
      return std::make_pair( GL_RGBA, GL_RGBA );
    else
      return std::make_pair( GL_RGBA, GL_BGRA );
  } 
  else if (pSurf->format->BytesPerPixel == 3) 
  {
    if (pSurf->format->Rmask == 0x000000ff)
      return std::make_pair( GL_RGB, GL_RGB );
    else
      return std::make_pair( GL_RGB, GL_BGR );
  } 
  else
    LOG_FATAL( "Unknown texture format" );  

  return std::make_pair(0, 0);
}
//////////////////////////////////////////////////////////////////////////

void Texture::LoadImpl( SDL_Surface *pSurf, int framesCount )
{
  ASSERT( pSurf != 0 );
  Reset();   
  
  ASSERT( framesCount > 0 );
  m_framesCount = framesCount;  
  m_size.set( pSurf->w / m_framesCount, pSurf->h );   

  glGenTextures( 1, &m_hTex );
  ASSERT( glGetError() == GL_NO_ERROR );
  ASSERT( m_hTex != INVALID_TEX_HANDLE );

  glBindTexture( GL_TEXTURE_2D, m_hTex ); 
 
  const std::pair<int, int> mode = GetTexMode( pSurf );

  glTexImage2D( GL_TEXTURE_2D, 0, mode.first, pSurf->w, pSurf->h, 0, mode.second, GL_UNSIGNED_BYTE, pSurf->pixels );
  SDL_FreeSurface( pSurf );

  if( glGetError() != GL_NO_ERROR )
    LOG_FATAL( "glTexImage2D error" ); 

  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
}
//////////////////////////////////////////////////////////////////////////

void Texture::Load( const char *szFile, int framesCount /*= 1*/ )
{
  ASSERT( szFile != 0 );
  
  SDL_Surface* pSurf = 0;

  if( boost::algorithm::ends_with(szFile, ".bmp") )
    pSurf = SDL_LoadBMP(szFile);
  else
    pSurf = IMG_Load(szFile);
    
  if( pSurf == 0 ) 
    LOG_FATAL( FMT("Texture loading error: %s") % szFile ); 
  
  LoadImpl( pSurf, framesCount );  
}
//////////////////////////////////////////////////////////////////////////

void Draw( const Texture &tex, point_t pos, int curFrame /*= 0*/ )
{
  Draw( tex, rect_t( pos, pos + tex.m_size ), curFrame );
}
//////////////////////////////////////////////////////////////////////////

void Draw( const Texture &tex, const rect_t &rect, int curFrame /*= 0*/ )
{
  ASSERT( tex.m_hTex != Texture::INVALID_TEX_HANDLE );
  ASSERT( curFrame >= 0 && curFrame < tex.m_framesCount );

  glBindTexture( GL_TEXTURE_2D, tex.m_hTex );

  glMatrixMode( GL_TEXTURE );
  glLoadIdentity();

  if( tex.m_framesCount > 1 )
  {
    glScalef( 1 / GLfloat(tex.m_framesCount), 1, 1 );
    glTranslatef(GLfloat(curFrame), 1, 1 );  
  } 

  glBegin(GL_QUADS);
    glTexCoord2i(0, 0); glVertex3i(rect.x1, rect.y1, 0);
    glTexCoord2i(1, 0); glVertex3i(rect.x2, rect.y1, 0);
    glTexCoord2i(1, 1); glVertex3i(rect.x2, rect.y2, 0);
    glTexCoord2i(0, 1); glVertex3i(rect.x1, rect.y2, 0);
  glEnd();
}
/////////////////////////////////////////////////////////////////////