#ifndef GuiWidgets_h__
#define GuiWidgets_h__

#include "GuiState.h"
#include "Texture.h"
#include "Font.h"
#include "Color.hpp"

class GuiImage: public IWidget, boost::noncopyable
{
public:
  typedef boost::shared_ptr<GuiImage> TPtr;
  typedef const TPtr &TPtrParam;  

public:
  GuiImage( point_t pos, Texture::TPtrParam pTex ):
    m_pos(pos), m_pTex(pTex)
  {}  
 
  rect_t GetRect() const { return rect_t( m_pos, m_pos + m_pTex->GetSize() ); }
  void Render( SDL_Surface *pDisplay ) const;
  void SetTexture( Texture::TPtrParam pTex ) { m_pTex = pTex; }

private:
  point_t m_pos;
  Texture::TPtr m_pTex;
};
//////////////////////////////////////////////////////////////////////////

class GuiLabel: public IWidget, boost::noncopyable
{
public:
  typedef boost::shared_ptr<GuiLabel> TPtr;
  typedef const TPtr &TPtrParam; 
  
public:
  GuiLabel( point_t pos, Font::TPtrParam pFont, const std::string &text = "", Color color = Color::make_white() ):
    m_pos(pos), m_pFont(pFont)
  {
    SetText( text, color );
  }  

  rect_t GetRect() const { return rect_t( m_pos, m_pos + m_tex.GetSize() ); }
  void SetText( const std::string &text, Color color = Color::make_white() );
  void Render( SDL_Surface *pDisplay ) const;

private:
  point_t m_pos;
  Font::TPtr m_pFont;
  Texture m_tex;
};
//////////////////////////////////////////////////////////////////////////

#endif // GuiWidgets_h__
