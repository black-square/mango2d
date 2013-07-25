#ifndef engine_stdafx_h__
#define engine_stdafx_h__

#ifdef WIN32
  #include <SDL.h>
  #include <SDL_ttf.h>
  #include <SDL_image.h>
  #include <SDL_opengl.h>
  #include <SDL_audio.h>
#else
  #include <SDL/SDL.h>
  #include <SDL_ttf/SDL_ttf.h>
  #include <SDL_image/SDL_image.h>
  #include <SDL/SDL_opengl.h>
  #include <SDL/SDL_audio.h>
#endif

#include "Core/CommonMacros.h"
#include "Core/StrFormat.h"
#include "Core/Log.h"


#endif // engine_stdafx_h__
