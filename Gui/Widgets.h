#ifndef GuiWidgets_h__
#define GuiWidgets_h__

#include "Gui/State.h"
#include "Graphics/Texture.h"
#include "Graphics/Font.h"

namespace Gui {

class Image: public IWidget, boost::noncopyable
{
public:
  typedef boost::shared_ptr<Image> TPtr;
  typedef const TPtr &TPtrParam;  

public:
  Image( Point pos, Texture::TPtrParam pTex, Color color = Color::make_white() ):
    m_rect(pos, pTex->GetSize()), m_pTex(pTex), m_color(color)
  {}  

  Image( const Rect rect, Texture::TPtrParam pTex, Color color = Color::make_white() ):
    m_rect(rect), m_pTex(pTex), m_color(color)
  {}  
 
  Rect GetRect() const { return m_rect; }
  void Render() const;
  void SetTexture( Texture::TPtrParam pTex ) { m_pTex = pTex; }
  void SetColor( Color color ) { m_color = color; }

private:
  Rect m_rect;
  Texture::TPtr m_pTex;
  Color m_color;
};
//////////////////////////////////////////////////////////////////////////

class Label: public IWidget, boost::noncopyable
{
public:
  typedef boost::shared_ptr<Label> TPtr;
  typedef const TPtr &TPtrParam;
  
  enum Align
  {
    Left,
    Center,
    Right
  }; 
  
public:
  Label( Point pos, Font::TPtrParam pFont, const std::string &text = "", Color color = Color::make_white(), Align align = Left ):
    m_pos(pos), m_pFont(pFont), m_align(align)
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
  Align m_align;
};
//////////////////////////////////////////////////////////////////////////

class Button: public IWidget, boost::noncopyable
{
public:
  typedef boost::shared_ptr<Button> TPtr;
  typedef const TPtr &TPtrParam; 
  typedef boost::function< void() > TCallback;
  typedef const TCallback &TCallbackParam;

public:
  Button( const Rect &rect, Font::TPtrParam pFont, Texture::TPtrParam pBack,
             TCallbackParam callback, const std::string &text = "", 
             Color color = Color::make_white() 
  ):
    m_rect(rect), m_pFont(pFont), m_pBack(pBack), m_callback(callback),  m_curState(Released)
  {
    SetText( text, color );
  }  

  Rect GetRect() const { return m_rect; }
  void SetText( const std::string &text, Color color = Color::make_white() );
  void SetTexture( Texture::TPtrParam pBack ) { m_pBack = pBack; }
  void Render() const;
  void OnLButtonDown( Point pos );
  void OnLButtonUp( Point pos );

private:
  enum State
  {
    Released,
    Pressed
  };

private:
  Rect m_rect;
  Font::TPtr m_pFont;
  Texture::TPtr m_pBack;
  Texture m_labelTex;
  State m_curState;
  TCallback m_callback;
};

} //namespace Gui

#endif // GuiWidgets_h__
