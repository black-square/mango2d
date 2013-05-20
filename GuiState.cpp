#include "stdafx.h"
#include "GuiState.h"

void GuiState::RenderWidgets()
{
  BOOST_FOREACH( IWidget::TPtrParam p, m_widgets )
    p->Render();
}

