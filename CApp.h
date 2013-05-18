
#ifndef _CAPP_H_
#define _CAPP_H_

#include <SDL.h>


#include "CEvent.h"
#include "Texture.h"
#include "GameField.h"
#include "GameFieldRender.h"
#include "GameLogic.h"

//==============================================================================
class CApp : public CEvent {
    private:
        bool            Running;
        SDL_Surface*    Surf_Display;

    private:
        Texture	background;
        GameField m_field;
        GameLogic m_logic;
        GameFieldRender m_fieldRender;
        GameFieldRender::PosOpt m_prevCellPos;
        GameLogic::TPoints m_marks;
        int m_state;

    public:
      CApp();
      
      int OnExecute();

    public:
       bool OnInit();
       void OnEvent(SDL_Event* Event);
       void OnLButtonDown(int mX, int mY);

       void UpdateState();

       void OnLButtonUp(int mX, int mY);
       void OnExit();
       void OnLoop();
       void OnRender();
       void OnCleanup();
};

//==============================================================================

#endif
