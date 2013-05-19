#ifndef TEXTURE_H
#define TEXTURE_H

#include "Color.hpp"

namespace Detail
{
  struct TextureBase
  {
    TextureBase(): m_pSurf(0) {} 
    SDL_Surface *m_pSurf;
  };
}

class Texture: private Detail::TextureBase,  private boost::noncopyable
{
public:
  typedef boost::shared_ptr<Texture> TPtr;
  typedef const TPtr &TPtrParam;  

public:
  Texture( ) {}
  Texture( const char *szFile ) { Load(szFile); }  
  Texture( const char *szFile, const Color &transpColor ) { Load(szFile, transpColor); }  

  ~Texture() { Reset(); }
  void Reset( SDL_Surface *pSurf = 0 );
  void Load( const char *szFile );
  void Load( const char *szFile, const Color &transpColor );

  point_t GetSize() const; 

  friend void Draw( SDL_Surface *pDest, const Texture &tex, point_t pos );
  friend void Draw( SDL_Surface *pDest, const Texture &tex, rect_t rect );
};



#endif