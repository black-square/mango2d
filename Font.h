#ifndef Font_h__
#define Font_h__

#include <SDL_ttf.h>
#include "Texture.h"

class Font: boost::noncopyable
{
public:
  Font(): m_font(0) {}
  ~Font() { Reset(); }
  void Reset();
  void Load( const char *szFile, int ptsize );

  friend void Draw( const Font &font, const char *szText, Color fg, Texture &res );
  friend void DrawHQ( const Font &font, const char *szText, Color fg, Texture &res );

private:
  TTF_Font *m_font;  
};

#endif // Font_h__
