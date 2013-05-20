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
  GuiImage( Point pos, Texture::TPtrParam pTex ):
    m_pos(pos), m_pTex(pTex)
  {}  
 
  Rect GetRect() const { return Rect( m_pos, m_pTex->GetSize() ); }
  void Render() const;
  void SetTexture( Texture::TPtrParam pTex ) { m_pTex = pTex; }

private:
  Point m_pos;
  Texture::TPtr m_pTex;
};
//////////////////////////////////////////////////////////////////////////

class GuiLabel: public IWidget, boost::noncopyable
{
public:
  typedef boost::shared_ptr<GuiLabel> TPtr;
  typedef const TPtr &TPtrParam; 
  
public:
  GuiLabel( Point pos, Font::TPtrParam pFont, const std::string &text = "", Color color = Color::make_white() ):
    m_pos(pos), m_pFont(pFont)
  {
    SetText( text, color );
  }  

  Rect GetRect() const { return Rect( m_pos, m_tex.GetSize() ); }
  void SetText( const std::string &text, Color color = Color::make_white() );
  void Render() const;

private:
  Point m_pos;
  Font::TPtr m_pFont;
  Texture m_tex;
};
//////////////////////////////////////////////////////////////////////////

class GuiButton: public IWidget, boost::noncopyable
{
public:
  typedef boost::shared_ptr<GuiButton> TPtr;
  typedef const TPtr &TPtrParam; 

public:
  GuiButton( const Rect &rect, Font::TPtrParam pFont, Texture::TPtrParam pBack, const std::string &text = "", Color color = Color::make_white() ):
    m_rect(rect), m_pFont(pFont), m_pBack(pBack)
  {
    SetText( text, color );
  }  

  Rect GetRect() const { return m_rect; }
  void SetText( const std::string &text, Color color = Color::make_white() );
  void SetTexture( Texture::TPtrParam pBack ) { m_pBack = pBack; }
  void Render() const;

private:
  Rect m_rect;
  Font::TPtr m_pFont;
  Texture::TPtr m_pBack;
  Texture m_labelTex;
};

#endif // GuiWidgets_h__
