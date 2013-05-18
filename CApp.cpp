//==============================================================================
#include "stdafx.h"
#include "CApp.h"

bool CApp::OnInit() 
{
  if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    return false;
  }

  if((Surf_Display = SDL_SetVideoMode(755, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
    return false;
  }

  background.Load( "./_data/BackGround.jpg" );

  m_fieldRender.Init( point_t(330, 100), 42 );

  srand ( (unsigned int) time(NULL) );

  for( int x = 0; x < GameField::FieldSize; ++x )
    for( int y = 0; y < GameField::FieldSize; ++y )
      m_field.Set( x, y, static_cast<GameField::Color>(rand() % GameField::ColorsCount) );

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

void CApp::OnLoop() {
}

//------------------------------------------------------------------------------
void CApp::OnLButtonDown(int mX, int mY) 
{
  m_prevCellPos = m_fieldRender.GetGemPos( point_t(mX, mY) );
}

void CApp::OnLButtonUp(int mX, int mY)
{
  GameFieldRender::PosOpt curCellPos =  m_fieldRender.GetGemPos( point_t(mX, mY) );

  if( m_prevCellPos && curCellPos && *m_prevCellPos != *curCellPos )
    if( manhattanDistance(*m_prevCellPos, *curCellPos) == 1 )
    {
      const GameField::Color cl = m_field.Get( *m_prevCellPos );
      m_field.Set( *m_prevCellPos, m_field.Get( *curCellPos ) );
      m_field.Set( *curCellPos, cl );
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
  m_fieldRender.Render( Surf_Display );

  SDL_Flip(Surf_Display);
}
