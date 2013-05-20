#ifndef TEXTURE_H
#define TEXTURE_H

#include "Core/Color.hpp"

namespace Detail
{
  struct TextureBase
  {
    TextureBase(): m_hTex(INVALID_TEX_HANDLE), m_framesCount(1) {} 
    static const GLuint INVALID_TEX_HANDLE = 0;

    GLuint m_hTex;
    SizeBase<GLsizei> m_size;
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

  Size GetSize() const { return m_size; } 

  friend void Draw( const Texture &tex, Point pos, int curFrame = 0 );
  friend void Draw( const Texture &tex, const Rect &rect, int curFrame = 0 );
  friend void Draw( const Texture &tex, const Rect &texRect, const Rect &destRect );

private:
  struct FrameMatrixStrat;
  struct RectMatrixStrat;

  template< class TexMatrixStrategyT >
  friend void DrawImpl( const Texture &tex, const Rect &rect, TexMatrixStrategyT matrixStrat );

private:
  std::pair<int, int> GetTexMode( const SDL_Surface *pSurf ) const;
  void LoadImpl( SDL_Surface *pSurf, int framesCount = 1 );
};



#endif