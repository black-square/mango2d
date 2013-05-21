#ifndef Log_h__
#define Log_h__

template<class MsgT>
void LogFatalImpl( const MsgT &msg );

template<size_t N>
inline void LogFatalImpl( const char (&msg)[N] )
{
  LogFatalImpl( static_cast<const char * const &>(msg) );
}
//////////////////////////////////////////////////////////////////////////

template<class MsgT>
void LogImpl( const MsgT &msg );

template<size_t N>
inline void LogImpl( const char (&msg)[N] )
{
  LogImpl( static_cast<const char * const &>(msg) );
}
//////////////////////////////////////////////////////////////////////////

#define LOG_FATAL( str ) LogFatalImpl( str )
#define LOG( str ) LogImpl( str )

#endif // Log_h__