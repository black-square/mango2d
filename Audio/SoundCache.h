#ifndef SoundCache_h__
#define SoundCache_h__

#include "Sound.h"

class SoundCache: boost::noncopyable
{
public:
  Sound &Get( const char *szFile );
  const Sound &Get( const char *szFile ) const;

private:
  typedef std::map< std::string, Sound::TPtr > TSounds;

private:
  TSounds m_sounds;
};



#endif // SoundCache_h__
