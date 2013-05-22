#ifndef Sound_h__
#define Sound_h__

namespace Detail
{
  struct SoundBase
  {
    SoundBase() 
    {
      m_cvt.buf = 0;  
    } 

    SDL_AudioCVT m_cvt;
  };
}
//////////////////////////////////////////////////////////////////////////
  
class Sound: Detail::SoundBase, boost::noncopyable
{
public:
  typedef boost::shared_ptr<Sound> TPtr;
  typedef const TPtr &TPtrParam; 

public:
  Sound() {}
  Sound( const char *file ) { Load(file); }
  ~Sound() { Reset(); }

  bool IsValid() const { return m_cvt.buf != 0; } 
  void Load( const char *file );
  void Reset();
  const SDL_AudioCVT &GetCVT() const { ASSERT(IsValid()); return m_cvt; }
};

#endif // Sound_h__
