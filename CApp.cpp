//==============================================================================
#include "stdafx.h"
#include "CApp.h"


void AutoPlay::Reset()
{
  m_state = 0;
  m_marks.clear();
}
//////////////////////////////////////////////////////////////////////////

void AutoPlay::Update( GameField &field, GameLogic &logic )
{
  switch(m_state)
  {
  case 0:
    if ( logic.FindMatches(field, m_marks) )
      m_state = 1;
    else
    {
      GameLogic::TMoves moves;
      logic.FindAllMoves( field, moves );
      m_marks.clear();

      BOOST_FOREACH( const GameLogic::TMoves::value_type &cur, moves )
        m_marks.push_back( cur.first );  

      if( !moves.empty() )
        m_state = 4;
    }

    break;
  case 1:
    logic.Remove(field, m_marks);
    m_marks.clear();
    m_state = 2;
    break;
  case 2:
    logic.FillEmptyToDown( field );
    m_state = 3; 
    break;

  case 3:
    logic.FillEmptyRandomly( field );
    m_state = 0; 
    break;

  case 4:
    {
      GameLogic::TMoves moves;
      logic.FindAllMoves( field, moves );
      ASSERT( !moves.empty() );
      m_nextMove = moves[logic.GetRand(0, moves.size() - 1)];
    }

    m_marks.clear();
    m_marks.push_back( m_nextMove.first );
    m_marks.push_back( m_nextMove.second );

    m_state = 5;
    break;

  case 5:  
    logic.Swap( field, m_nextMove.first, m_nextMove.second );
    VERIFY( logic.FindMatches(field, m_marks) );
    m_state = 1;
    break;
  }
}
//////////////////////////////////////////////////////////////////////////

CApp::CApp() : 
  m_fieldRender(m_field), Surf_Display(NULL), Running(true)
{

}
//////////////////////////////////////////////////////////////////////////

bool CApp::OnInit() 
{
  if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    return false;
  }

  if((Surf_Display = SDL_SetVideoMode(755, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
    return false;
  }

  m_logic.FillEmptyRandomly( m_field );

  background.Load( "./_data/BackGround.jpg" );
  m_fieldRender.Init( point_t(330, 100), 42 );

  m_prevClock = TClock::now();

  return true;
}
//////////////////////////////////////////////////////////////////////////

void CApp::OnEvent(SDL_Event* Event) {
  CEvent::OnEvent(Event);
}

//==============================================================================
void CApp::OnExit() {
  Running = false;
}

void CApp::OnCleanup() {
  SDL_FreeSurface(Surf_Display);
  SDL_Quit();
}

void CApp::OnLoop() 
{
  const TClock::time_point curClock = TClock::now();
  const float deltaTime = boost::chrono::duration<float>( curClock - m_prevClock ).count();
  m_prevClock = curClock;

  if( m_autoPlayTimer.TickWithRestart(deltaTime) )
    m_autoPlay.Update( m_field, m_logic ); 
}
//////////////////////////////////////////////////////////////////////////

void CApp::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
  if( sym == SDLK_a )
    if( !m_autoPlayTimer.IsInProgress() ) 
      m_autoPlayTimer.Start( 0.001f );
    else
      m_autoPlayTimer.Stop();

  if( sym == SDLK_SPACE )
    m_autoPlay.Update( m_field, m_logic );
}

//------------------------------------------------------------------------------
void CApp::OnLButtonDown(int mX, int mY) 
{
  m_prevCellPos = m_fieldRender.GetGemPos( point_t(mX, mY) );    
}
//////////////////////////////////////////////////////////////////////////


void CApp::OnLButtonUp(int mX, int mY)
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

int CApp::OnExecute() {
    if(OnInit() == false) {
        return -1;
    }

    SDL_Event Event;

    while(Running) {
        while(SDL_PollEvent(&Event)) {
            OnEvent(&Event);
        }

        OnLoop();
        OnRender();
    }

    OnCleanup();

    return 0;
}

void CApp::OnRender() 
{
  Draw(Surf_Display, background, point_t(0, 0));

  BOOST_FOREACH( const point_t &cur, m_autoPlay.GetMarks() )
    m_fieldRender.RenderMark( Surf_Display, cur ); 

  m_fieldRender.Render( Surf_Display );

  SDL_Flip(Surf_Display);
}


