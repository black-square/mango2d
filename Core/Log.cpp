#include "stdafx.h"
#include "Log.h"
#include "StrFormat.h"

#include <SDL_syswm.h>
#include <Windows.h>

static void TerminateApp()
{
  if ( IsDebuggerPresent() )											
    __debugbreak();	

  std::exit( -42 );
}
//////////////////////////////////////////////////////////////////////////

template<class MsgT>
void LogFatalImpl( const MsgT &msg )
{
  SDL_SysWMinfo sysInfo = {};

  SDL_VERSION(&sysInfo.version);
  SDL_GetWMInfo(&sysInfo);

  MessageBoxW( 
    sysInfo.window, 
    MakeWString(msg).c_str(), MakeWString("Fatal Error").c_str(),
    MB_OK | MB_ICONSTOP | MB_TOPMOST
    ); 

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
  OutputDebugStringW( MakeWString(msg).c_str() );
  OutputDebugStringW( L"\n" );
}
//////////////////////////////////////////////////////////////////////////

template void LogImpl( const char *const &msg );
template void LogImpl( const std::string &msg );
template void LogImpl( const boost::format &msg );

