#include "stdafx.h"
#include "SoundCache.h"

//////////////////////////////////////////////////////////////////////////

Sound &SoundCache::Get( const char *szFile )
{
  TSounds::const_iterator it = m_sounds.find( szFile );

  if( it != m_sounds.end() )
    return *it->second;

  const Sound::TPtr p = boost::make_shared<Sound>( szFile );

  m_sounds.insert( TSounds::value_type(szFile, p) );
  
  return *p;
}
//////////////////////////////////////////////////////////////////////////

const Sound &SoundCache::Get( const char *szFile ) const
{
  TSounds::const_iterator it = m_sounds.find( szFile );

  if( it != m_sounds.end() )
    return *it->second;

  LOG_FATAL( "Const SoundCache can not load sounds" );
  for(;;) {}
}



