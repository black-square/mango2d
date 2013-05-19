#ifndef Font_h__
#define Font_h__

#include "Texture.h"

namespace Detail
{
  struct FontBase
  {
    FontBase(): m_font(0) {} 
    TTF_Font *m_font;
  };
}

class Font: private Detail::FontBase, private boost::noncopyable
{
public:
  typedef boost::shared_ptr<Font> TPtr;
  typedef const TPtr &TPtrParam;

public:
  Font() {}
  Font(  const char *szFile, int ptsize  ) { Load(szFile, ptsize); }
  ~Font() { Reset(); }
  void Reset();
  void Load( const char *szFile, int ptsize );

  friend void Draw( const Font &font, const char *szText, Color fg, Texture &res );
  friend void DrawHQ( const Font &font, const char *szText, Color fg, Texture &res );

private:
  
};

#endif // Font_h__
