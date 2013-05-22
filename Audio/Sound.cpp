#include "stdafx.h"
#include "Sound.h"
#include "SoundManager.h"

void Sound::Load( const char *file )
{
  SDL_AudioSpec wave;
  Uint8 *data;
  Uint32 dlen;

  if ( SDL_LoadWAV(file, &wave, &data, &dlen) == NULL ) 
    LOG_FATAL( FMT("Couldn't load %s: %s") % file % SDL_GetError() );

  const SDL_AudioSpec &dst_fmt( SoundManager::GetSpecs() );

  SDL_BuildAudioCVT(&m_cvt, wave.format, wave.channels, wave.freq, dst_fmt.format, dst_fmt.channels, dst_fmt.freq);

  if( wave.format != dst_fmt.format || wave.channels != dst_fmt.channels || wave.freq != dst_fmt.freq )
    LOG( FMT("Format mismatch in mixer and autio file %s. Try to convert") % file );  

  m_cvt.buf = (Uint8 *)std::malloc( dlen * m_cvt.len_mult );
  std::memcpy(m_cvt.buf, data, dlen);
  m_cvt.len = dlen;
  SDL_ConvertAudio(&m_cvt);
  SDL_FreeWAV(data);
}
//////////////////////////////////////////////////////////////////////////

void Sound::Reset()
{
  if( m_cvt.buf != 0 )
  {  
    std::free(m_cvt.buf);
    m_cvt.buf = 0;
  } 
}
