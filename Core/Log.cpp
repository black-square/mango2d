#include "stdafx.h"
#include "Log.h"
#include "StrFormat.h"

#ifdef WIN32
#include <SDL_syswm.h>
#include <Windows.h>
#endif


static void TerminateApp()
{
#ifdef WIN32
  if ( IsDebuggerPresent() )											
    __debugbreak();	
#endif
  
  std::exit( -42 );
}
//////////////////////////////////////////////////////////////////////////

template<class MsgT>
void LogFatalImpl( const MsgT &msg )
{
#ifdef WIN32
  SDL_SysWMinfo sysInfo = {};

  SDL_VERSION(&sysInfo.version);
  SDL_GetWMInfo(&sysInfo);

  MessageBoxW( 
    sysInfo.window, 
    MakeWString(msg).c_str(), MakeWString("Fatal Error").c_str(),
    MB_OK | MB_ICONSTOP | MB_TOPMOST
    );
#else
  std::fprintf( stderr, "Fatal error: %s\n", MakeString(msg).c_str() );
#endif

  TerminateApp();
}
//////////////////////////////////////////////////////////////////////////

template void LogFatalImpl( const char *const &msg );
template void LogFatalImpl( const std::string &msg );
template void LogFatalImpl( const boost::format &msg );

//////////////////////////////////////////////////////////////////////////

template<class MsgT>
void LogImpl( const MsgT &msg )
{
#ifdef WIN32
  OutputDebugStringW( MakeWString(msg).c_str() );
  OutputDebugStringW( L"\n" );
#else
  std::puts( MakeString(msg).c_str() );
#endif
}
//////////////////////////////////////////////////////////////////////////

template void LogImpl( const char *const &msg );
template void LogImpl( const std::string &msg );
template void LogImpl( const boost::format &msg );

