#include "stdafx.h"
#include "SoundManager.h"
#include "SoundCache.h"

SDL_AudioSpec SoundManager::GetSpecs()
{
  SDL_AudioSpec fmt;

  /* Set 16-bit stereo audio at 22Khz */
  fmt.freq = 44100;
  fmt.format = AUDIO_S16;
  fmt.channels = 1;
  fmt.samples = 1024;        /* A good value for games */

  return fmt;
}
//////////////////////////////////////////////////////////////////////////

SoundManager::SoundManager()
{
  SDL_AudioSpec fmt( GetSpecs() );

  fmt.callback = MixAudioCbk;
  fmt.userdata = this;

  /* Open the audio device and start playing sound! */
  if ( SDL_OpenAudio(&fmt, NULL) < 0 )
    LOG_FATAL( FMT("Unable to open audio: %s") % SDL_GetError() );

  SDL_PauseAudio(0);
}
//////////////////////////////////////////////////////////////////////////

SoundManager::~SoundManager()
{
  SDL_CloseAudio();
}
//////////////////////////////////////////////////////////////////////////

void SoundManager::MixAudioCbk( Uint8 *stream, int len )
{
  int i;
  Uint32 amount;

  for ( i=0; i<NUM_SOUNDS; ++i ) {
    amount = (m_sounds[i].dlen-m_sounds[i].dpos);
    if ( amount > Uint32(len) ) {
      amount = len;
    }
    SDL_MixAudio(stream, &m_sounds[i].data[m_sounds[i].dpos], amount, SDL_MIX_MAXVOLUME);
    m_sounds[i].dpos += amount;
  }
}
//////////////////////////////////////////////////////////////////////////

void SoundManager::MixAudioCbk( void *userdata, Uint8 *stream, int len )
{
  static_cast<SoundManager *>(userdata)->MixAudioCbk(stream, len) ;
}
//////////////////////////////////////////////////////////////////////////

void SoundManager::Play( const Sound &s )
{
  ASSERT( s.IsValid() );

  int index;

  /* Look for an empty (or finished) sound slot */
  for ( index=0; index < NUM_SOUNDS; ++index )
  {
    if( m_sounds[index].dpos == m_sounds[index].dlen )
      break;

    //Block same sounds simultaneously playing
    if( m_sounds[index].dpos == 0 && m_sounds[index].data == s.GetCVT().buf )
      return;
  }

  if( index == NUM_SOUNDS )
    return;

  SDL_LockAudio();
  m_sounds[index].data = s.GetCVT().buf;
  m_sounds[index].dlen = s.GetCVT().len_cvt;
  m_sounds[index].dpos = 0;
  SDL_UnlockAudio();
}
//////////////////////////////////////////////////////////////////////////
static boost::scoped_ptr<SoundManager> g_sndMngr;
static boost::scoped_ptr<SoundCache> g_sndCache;

//////////////////////////////////////////////////////////////////////////
void InitGlobalSoundManager()
{
  g_sndMngr.reset( new SoundManager() );
  g_sndCache.reset( new SoundCache() );
}
//////////////////////////////////////////////////////////////////////////

void DestroyGlobalSoundManager()
{
  g_sndMngr.reset();
  g_sndCache.reset();
}
//////////////////////////////////////////////////////////////////////////

void PlaySound( const char *szFile )
{
  ASSERT( g_sndMngr && g_sndCache );
  g_sndMngr->Play( g_sndCache->Get(szFile) );
}


