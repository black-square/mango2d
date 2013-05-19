//==============================================================================
#include "stdafx.h"
#include "App.h"

App::App() : 
  m_fieldRender(m_field), m_movesCount(0)
{

}
//////////////////////////////////////////////////////////////////////////

void App::OnInit() 
{
  SDL_WM_SetCaption("Dmitry Shesterkin", "Dmitry Shesterkin");

  m_logic.FillEmptyRandomly( m_field );
  m_logic.SetEventsHandler( this );

  background.Load( "./_data/BackGround.jpg" );
  m_fieldRender.Init( point_t(330, 100), 42 );

  m_font.Load( "./_data/gm.ttf", 25);
  DrawHQ( m_font, "Moves count", Color::make_white(), m_infoText );
}
//////////////////////////////////////////////////////////////////////////

void App::OnLoop( float deltaTime ) 
{
  if( m_autoPlayTimer.TickWithRestart(deltaTime) )
    m_autoPlay.Update( m_field, m_logic ); 
}
//////////////////////////////////////////////////////////////////////////

void App::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
  if( sym == SDLK_a )
    if( !m_autoPlayTimer.IsInProgress() ) 
      m_autoPlayTimer.Start( 0.001f );
    else
      m_autoPlayTimer.Stop();

  if( sym == SDLK_SPACE )
    m_autoPlay.Update( m_field, m_logic );
}

//////////////////////////////////////////////////////////////////////////

void App::OnLButtonDown(int mX, int mY) 
{
  m_prevCellPos = m_fieldRender.GetGemPos( point_t(mX, mY) );    
}
//////////////////////////////////////////////////////////////////////////

void App::OnLButtonUp(int mX, int mY)
{
  GameFieldRender::PosOpt curCellPos =  m_fieldRender.GetGemPos( point_t(mX, mY) );

  if( m_prevCellPos && curCellPos && *m_prevCellPos != *curCellPos )
    if( manhattanDistance(*m_prevCellPos, *curCellPos) == 1 )
    {
      m_logic.Swap( m_field, *m_prevCellPos, *curCellPos );

      m_autoPlay.Reset();
      m_autoPlay.Update( m_field, m_logic );

      //m_logic.DestroyAndFillEmptyToDown(m_field);
    }

  m_prevCellPos = boost::none;
}
//////////////////////////////////////////////////////////////////////////

void App::OnRender( SDL_Surface *pDisplay ) 
{
  Draw(pDisplay, background, point_t(0, 0));

  BOOST_FOREACH( const point_t &cur, m_autoPlay.GetMarks() )
    m_fieldRender.RenderMark( pDisplay, cur ); 

  m_fieldRender.Render( pDisplay );
  Draw( pDisplay, m_infoText, point_t(38, 120) );

  VERIFY( SDL_Flip(pDisplay) == 0 );
}

void App::OnSwap( point_t p1, point_t p2 )
{
  ++m_movesCount;
  DrawHQ( m_font, MakeString(FMT("Moves count: %d") % m_movesCount).c_str(), Color::make_white(), m_infoText ); 
}


