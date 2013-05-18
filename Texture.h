#ifndef TEXTURE_H
#define TEXTURE_H

#include "Color.hpp"

class Texture: boost::noncopyable
{
public:
  Texture(): m_pSurf(0) {}
  ~Texture() { Reset(); }
  void Reset( SDL_Surface *pSurf = 0 );
  void Load( const char *szFile );
  void Load( const char *szFile, const Color &transpColor );

  point_t GetSize() const; 

  friend void Draw( SDL_Surface *pDest, const Texture &tex, point_t pos );

private:
  SDL_Surface *m_pSurf; 
};



#endif