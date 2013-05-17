#include "stdafx.h"
#include "StrFormat.h"
#include <boost/filesystem/detail/utf8_codecvt_facet.hpp>
#include <boost/filesystem/path_traits.hpp>

#include <SDL_syswm.h>
#include <Windows.h>

static const boost::filesystem::detail::utf8_codecvt_facet &utf8_facet()
{
  static const boost::filesystem::detail::utf8_codecvt_facet facet;
  return facet;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::string MakeString( const wchar_t *str )
{
  std::string msg; 
  boost::filesystem::path_traits::convert( str, msg, utf8_facet() );
  
  return msg;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::wstring MakeWString( const char *str )
{
  std::wstring wmsg; 
  boost::filesystem::path_traits::convert( str, wmsg, utf8_facet() );
  
  return wmsg;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void TerminateApp()
{
  if ( IsDebuggerPresent() )											
    __debugbreak();	

  std::exit( -42 );
}


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

template void LogFatalImpl( const char *const &msg );
template void LogFatalImpl( const std::string &msg );
template void LogFatalImpl( const boost::format &msg );