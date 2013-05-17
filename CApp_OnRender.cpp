//==============================================================================
#include "stdafx.h"
#include "CApp.h"

//==============================================================================
void CApp::OnRender() {
	Draw(Surf_Display, Surf_Grid, point_t(0, 0));

    for(int i = 0;i < 9;i++) {
        const point_t pt ( (i % 3) * 200, (i / 3) * 200 ); 

        if(Grid[i] == GRID_TYPE_X) {
            Draw(Surf_Display, Surf_X, pt );
        }else
        if(Grid[i] == GRID_TYPE_O) {
            Draw(Surf_Display, Surf_O, pt );
        }
    }

  Draw(Surf_Display, background, point_t(0, 0));
  m_fieldRender.Render( Surf_Display, point_t(340, 110) );

	SDL_Flip(Surf_Display);
}

//==============================================================================
