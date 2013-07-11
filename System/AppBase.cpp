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
bool AppBase::DispatchEvent(SDL_Event* e) 
{
	switch(e->type) 
  {
	case SDL_ACTIVEEVENT: 
    DispatchActiveEvent(e);
		break;

	case SDL_KEYDOWN: 
		OnKeyDown(e->key.keysym.sym,e->key.keysym.mod,e->key.keysym.unicode);
		break;

	case SDL_KEYUP:
		OnKeyUp(e->key.keysym.sym,e->key.keysym.mod,e->key.keysym.unicode);
		break;

	case SDL_MOUSEMOTION:
		OnMouseMove( Point(e->motion.x, e->motion.y) );
		break;

	case SDL_MOUSEBUTTONDOWN: 
    OnMouseButtonDown( Point(e->motion.x, e->motion.y), e->button.button );
		break;

	case SDL_MOUSEBUTTONUP:
	  OnMouseButtonUp( Point(e->motion.x, e->motion.y), e->button.button );
		break;
	
	case SDL_QUIT:
		return false;
		break;

	case SDL_VIDEORESIZE:
		OnResize(e->resize.w,e->resize.h);
		break;

	case SDL_VIDEOEXPOSE:
		OnExpose();
		break;
	}

  return true;
}
//////////////////////////////////////////////////////////////////////////

void AppBase::DispatchActiveEvent( SDL_Event* e )
{
  if ( e->active.gain )
    switch(e->active.state)
    {
      case SDL_APPMOUSEFOCUS: OnMouseFocus(); break;  
      case SDL_APPINPUTFOCUS: OnInputFocus(); break;  
      case SDL_APPACTIVE:     OnRestore();    break;  
    }
  else
    switch(e->active.state)
    {
      case SDL_APPMOUSEFOCUS: OnMouseBlur();  break;  
      case SDL_APPINPUTFOCUS: OnInputBlur();  break;  
      case SDL_APPACTIVE:     OnMinimize();   break;  
    }
}
//////////////////////////////////////////////////////////////////////////

void AppBase::MainLoop()
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

    OnRender();

    SDL_GL_SwapBuffers();
  }
}
//////////////////////////////////////////////////////////////////////////

int AppBase::Execute( Size screenSize )
{
  SDL_Surface *pDisplay = SDL_SetVideoMode( screenSize.w, screenSize.h, 32, SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL );

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
  
  glViewport(0, 0, screenSize.w, screenSize.h);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, screenSize.w,screenSize.h, 0, 1, -1);
  
  glEnable( GL_TEXTURE_2D );
  glEnable( GL_BLEND );
  glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

  OnInit();
  MainLoop();
  OnCleanup();
  SDL_FreeSurface(pDisplay);

  return 0;
}


