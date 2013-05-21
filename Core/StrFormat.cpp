#include "stdafx.h"
#include "StrFormat.h"
#include <boost/filesystem/detail/utf8_codecvt_facet.hpp>
#include <boost/filesystem/path_traits.hpp>

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