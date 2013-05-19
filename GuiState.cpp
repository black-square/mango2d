#include "stdafx.h"
#include "GuiState.h"

void GuiState::RenderWidgets( SDL_Surface *pDisplay )
{
  BOOST_FOREACH( IWidget::TPtrParam p, m_widgets )
    p->Render( pDisplay );
}

