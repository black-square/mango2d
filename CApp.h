
#ifndef _CAPP_H_
#define _CAPP_H_

#include <SDL.h>


#include "CEvent.h"
#include "Texture.h"

//==============================================================================
class CApp : public CEvent {
    private:
        bool            Running;

        SDL_Surface*    Surf_Display;

    private:
        Texture  Surf_Grid;

        Texture	Surf_X;
        Texture	Surf_O;

    private:
        int		        Grid[9];

        int             CurrentPlayer;

        enum {
            GRID_TYPE_NONE = 0,
            GRID_TYPE_X,
            GRID_TYPE_O
        };

    public:
        CApp();

        int OnExecute();

    public:
        bool OnInit();

        void OnEvent(SDL_Event* Event);

            void OnLButtonDown(int mX, int mY);

            void OnExit();

        void OnLoop();

        void OnRender();

        void OnCleanup();

    public:
        void Reset();

        void SetCell(int ID, int Type);
};

//==============================================================================

#endif
