#ifndef SoundManager_h__
#define SoundManager_h__

#include "Sound.h"

class SoundManager: boost::noncopyable
{
public:
  SoundManager();
  ~SoundManager();
  void Play( const Sound &s );

  static SDL_AudioSpec GetSpecs();

private:
  struct TSample 
  {
    Uint8 *data;
    Uint32 dpos;
    Uint32 dlen;

    TSample(): 
      data(0), dpos(0), dlen(0)
    {}     
  };

private:
  static void MixAudioCbk(void *unused, Uint8 *stream, int len);
  void MixAudioCbk(Uint8 *stream, int len);

private:
  enum { NUM_SOUNDS = 5 };
  TSample m_sounds[NUM_SOUNDS];
};


void InitGlobalSoundManager();
void DestroyGlobalSoundManager();
void PlaySound( const char *szFile );


#endif // SoundManager_h__
