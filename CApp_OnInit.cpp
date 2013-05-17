//==============================================================================
#include "stdafx.h"
#include "CApp.h"

//==============================================================================
bool CApp::OnInit() {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }

    if((Surf_Display = SDL_SetVideoMode(600, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
        return false;
    }

    Surf_Grid.Load("./gfx/grid.bmp");
    Surf_X.Load( "./gfx/x.bmp", Color::make_magenta() );
    Surf_O.Load( "./gfx/o.bmp", Color::make_magenta() );

    Reset();

    return true;
}

//==============================================================================
