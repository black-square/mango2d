#include "stdafx.h"
#include "Main.h"

#include "System/App.h"

int SDL_main(int argc, char *argv[])
{
  LOG( FMT("Start path: %s") % argv[0] );
  App theApp;

  return theApp.Execute( Point(755, 600) );
}