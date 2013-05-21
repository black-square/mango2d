#ifndef STRFORMAT_HPP_70E3F625_C1E1_4E3F
#define STRFORMAT_HPP_70E3F625_C1E1_4E3F

#include <boost/format.hpp>

template<class T>
inline boost::format FMT( const T &str ) 
{
  boost::format fmter(str);
  fmter.exceptions( boost::io::no_error_bits );
  return fmter;
}

//Уменьшим количество инстанцируемых функций
template<size_t N>
inline boost::format FMT( const char (&msg)[N] )
{
  return FMT( static_cast<const char *>(msg) );
}
///////////////////////////////////////////////////////////////////////////////

//Преобразуем разные типы в std::string
inline std::string MakeString( const char *szStr )
{
  return std::string( szStr );
} 

inline const std::string &MakeString( const std::string &str )
{
  return str;
} 

inline std::string MakeString( const boost::format &fmtStr )
{
  return fmtStr.str();
} 
///////////////////////////////////////////////////////////////////////////////

std::string MakeString( const wchar_t *str );
std::wstring MakeWString( const char *str );

inline std::string MakeString( const std::wstring &str )
{  
  return MakeString( str.c_str() );
}

inline std::wstring MakeWString( const std::string &str )
{
  return MakeWString( str.c_str() );
}

inline std::wstring MakeWString( const boost::format &fmtStr )
{
  return MakeWString( fmtStr.str() );
} 

///////////////////////////////////////////////////////////////////////////////

#endif //#define STRFORMAT_HPP_70E3F625_C1E1_4E3F