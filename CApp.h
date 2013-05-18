
#ifndef _CAPP_H_
#define _CAPP_H_

#include <SDL.h>


#include "CEvent.h"
#include "Texture.h"
#include "GameField.h"
#include "GameFieldRender.h"

//==============================================================================
class CApp : public CEvent {
    private:
        bool            Running;
        SDL_Surface*    Surf_Display;

    private:
        Texture	background;
        GameField m_field;
        GameFieldRender m_fieldRender;
        GameFieldRender::PosOpt m_prevCellPos;

    public:
      CApp(): 
        m_fieldRender(m_field), Surf_Display(NULL), Running(true) 
      {}
      
      int OnExecute();

    public:
       bool OnInit();
       void OnEvent(SDL_Event* Event);
       void OnLButtonDown(int mX, int mY);
       void OnLButtonUp(int mX, int mY);
       void OnExit();
       void OnLoop();
       void OnRender();
       void OnCleanup();
};

//==============================================================================

#endif
