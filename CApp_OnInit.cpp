//==============================================================================
#include "stdafx.h"
#include "CApp.h"

//==============================================================================
bool CApp::OnInit() {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }

    if((Surf_Display = SDL_SetVideoMode(755, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
      return false;
    }

    Surf_Grid.Load("./gfx/grid.bmp");
    Surf_X.Load( "./gfx/x.bmp", Color::make_magenta() );
    Surf_O.Load( "./gfx/o.bmp", Color::make_magenta() );;
    background.Load( "./_data/BackGround.jpg" );

    m_fieldRender.Init();

    srand ( (unsigned int) time(NULL) );

    for( int x = 0; x < GameField::FieldSize; ++x )
      for( int y = 0; y < GameField::FieldSize; ++y )
        m_field.Set( x, y, static_cast<GameField::Color>(rand() % GameField::ColorsCount) );

    Reset();

    return true;
}

//==============================================================================
