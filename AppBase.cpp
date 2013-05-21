//==============================================================================
#include "stdafx.h"

#include "AppBase.h"


GlobalInitHelper::GlobalInitHelper()
{
  if(SDL_Init(SDL_INIT_EVERYTHING) < 0) 
    LOG_FATAL( "SDL_Init error" );

  if( TTF_Init() != 0 )
    LOG_FATAL( "TTF_Init error" ); 
}
//////////////////////////////////////////////////////////////////////////

GlobalInitHelper::~GlobalInitHelper()
{
  TTF_Quit();
  SDL_Quit();
}

//==============================================================================
bool AppBase::DispatchEvent(SDL_Event* Event) {
	switch(Event->type) {
		case SDL_ACTIVEEVENT: {
			switch(Event->active.state) {
				case SDL_APPMOUSEFOCUS: {
					if ( Event->active.gain )	OnMouseFocus();
					else				OnMouseBlur();

					break;
				}
				case SDL_APPINPUTFOCUS: {
					if ( Event->active.gain )	OnInputFocus();
					else				OnInputBlur();

					break;
				}
				case SDL_APPACTIVE:	{
					if ( Event->active.gain )	OnRestore();
					else				OnMinimize();

					break;
				}
			}
			break;
		}

		case SDL_KEYDOWN: {
			OnKeyDown(Event->key.keysym.sym,Event->key.keysym.mod,Event->key.keysym.unicode);
			break;
		}

		case SDL_KEYUP: {
			OnKeyUp(Event->key.keysym.sym,Event->key.keysym.mod,Event->key.keysym.unicode);
			break;
		}

		case SDL_MOUSEMOTION: {
			OnMouseMove(Event->motion.x,Event->motion.y,Event->motion.xrel,Event->motion.yrel,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_LEFT))!=0,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_RIGHT))!=0,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_MIDDLE))!=0);
			break;
		}

		case SDL_MOUSEBUTTONDOWN: {
			switch(Event->button.button) {
				case SDL_BUTTON_LEFT: {
					OnLButtonDown(Event->button.x,Event->button.y);
					break;
				}
				case SDL_BUTTON_RIGHT: {
					OnRButtonDown(Event->button.x,Event->button.y);
					break;
				}
				case SDL_BUTTON_MIDDLE: {
					OnMButtonDown(Event->button.x,Event->button.y);
					break;
				}
			}
			break;
		}

		case SDL_MOUSEBUTTONUP:	{
			switch(Event->button.button) {
				case SDL_BUTTON_LEFT: {
					OnLButtonUp(Event->button.x,Event->button.y);
					break;
				}
				case SDL_BUTTON_RIGHT: {
					OnRButtonUp(Event->button.x,Event->button.y);
					break;
				}
				case SDL_BUTTON_MIDDLE: {
					OnMButtonUp(Event->button.x,Event->button.y);
					break;
				}
			}
			break;
		}

		case SDL_JOYAXISMOTION: {
			OnJoyAxis(Event->jaxis.which,Event->jaxis.axis,Event->jaxis.value);
			break;
		}

		case SDL_JOYBALLMOTION: {
			OnJoyBall(Event->jball.which,Event->jball.ball,Event->jball.xrel,Event->jball.yrel);
			break;
		}

		case SDL_JOYHATMOTION: {
			OnJoyHat(Event->jhat.which,Event->jhat.hat,Event->jhat.value);
			break;
		}
		case SDL_JOYBUTTONDOWN: {
			OnJoyButtonDown(Event->jbutton.which,Event->jbutton.button);
			break;
		}

		case SDL_JOYBUTTONUP: {
			OnJoyButtonUp(Event->jbutton.which,Event->jbutton.button);
			break;
		}

		case SDL_QUIT: {
			return false;
			break;
		}

		case SDL_SYSWMEVENT: {
			//Ignore
			break;
		}

		case SDL_VIDEORESIZE: {
			OnResize(Event->resize.w,Event->resize.h);
			break;
		}

		case SDL_VIDEOEXPOSE: {
			OnExpose();
			break;
		}

		default: {
			OnUser(Event->user.type,Event->user.code,Event->user.data1,Event->user.data2);
			break;
		}
	}

  return true;
}
//////////////////////////////////////////////////////////////////////////

void AppBase::MainLoop( SDL_Surface *pDisplay )
{
  TClock::time_point prevClock = TClock::now();

  SDL_Event event;

  for(;;) 
  {
    while( SDL_PollEvent(&event) )
      if( !DispatchEvent(&event) )
        return;

    const TClock::time_point curClock = TClock::now();
    const float deltaTime = boost::chrono::duration<float>( curClock - prevClock ).count();
    prevClock = curClock;

    OnUpdate( deltaTime );
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    OnRender( pDisplay );

    SDL_GL_SwapBuffers();
  }
}
//////////////////////////////////////////////////////////////////////////

int AppBase::Execute( point_t screenSize )
{
  SDL_Surface *pDisplay = SDL_SetVideoMode( screenSize.x, screenSize.y, 32, SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL );

  if( pDisplay == 0 )
    LOG_FATAL( "SDL_SetVideoMode error" ); 

  SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
  SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
  SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
  SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 8 );

  SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
  SDL_GL_SetAttribute( SDL_GL_BUFFER_SIZE, 32 );

  SDL_GL_SetAttribute( SDL_GL_ACCUM_RED_SIZE, 8 );
  SDL_GL_SetAttribute( SDL_GL_ACCUM_GREEN_SIZE, 8 );
  SDL_GL_SetAttribute( SDL_GL_ACCUM_BLUE_SIZE, 8 );
  SDL_GL_SetAttribute( SDL_GL_ACCUM_ALPHA_SIZE, 8 );

  SDL_GL_SetAttribute( SDL_GL_MULTISAMPLEBUFFERS, 1 );
  SDL_GL_SetAttribute( SDL_GL_MULTISAMPLESAMPLES, 2 );

  glClearColor(0, 0, 0, 0);
  glClearDepth(1.0f);
  
  glViewport(0, 0, screenSize.x, screenSize.y);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, screenSize.x,screenSize.y, 0, 1, -1);
  
  glEnable( GL_TEXTURE_2D );
  glEnable( GL_BLEND );
  glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

  OnInit();
  MainLoop(pDisplay);
  OnCleanup();
  SDL_FreeSurface(pDisplay);

  return 0;
}


