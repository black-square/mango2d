#include "stdafx.h"
#include "Main.h"

#include "System/App.h"
#include <boost/filesystem.hpp>

int SDL_main(int argc, char *argv[])
{
  using namespace boost::filesystem;
  
  LOG( FMT("Start path: %s") % argv[0] );

  #ifndef WIN32
    current_path( system_complete(argv[0]).parent_path() );
  #endif
  
  App theApp;

  return theApp.Execute( Point(755, 600) );
}