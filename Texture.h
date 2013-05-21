#ifndef TEXTURE_H
#define TEXTURE_H

#include "Color.hpp"

namespace Detail
{
  struct TextureBase
  {
    TextureBase(): m_hTex(INVALID_TEX_HANDLE), m_framesCount(1) {} 
    static const GLuint INVALID_TEX_HANDLE = 0;

    GLuint m_hTex;
    point_base_t<GLsizei> m_size;
    int m_framesCount;
  };
}
//////////////////////////////////////////////////////////////////////////

class Texture: private Detail::TextureBase,  private boost::noncopyable
{
public:
  typedef boost::shared_ptr<Texture> TPtr;
  typedef const TPtr &TPtrParam;  

public:
  Texture() {}
  explicit Texture( const char *szFile, int framesCount = 1 ) { Load(szFile, framesCount); }  

  ~Texture() { Reset(); }
  void Reset( SDL_Surface *pSurf );
  void Reset();
  void Load( const char *szFile, int framesCount = 1 );

  point_t GetSize() const { return m_size; } 

  friend void Draw( const Texture &tex, point_t pos, int curFrame = 0 );
  friend void Draw( const Texture &tex, const rect_t &rect, int curFrame = 0 );

private:
  std::pair<int, int> GetTexMode( const SDL_Surface *pSurf ) const;
  void LoadImpl( SDL_Surface *pSurf, int framesCount = 1 );
};



#endif