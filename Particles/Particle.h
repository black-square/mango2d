#ifndef ParticleObj_h__
#define ParticleObj_h__

#include "Graphics/Texture.h"

class Particle
{
public:
  typedef boost::shared_ptr<Particle> TPtr;
  typedef const TPtr &TPtrParam; 

public:
  struct Param
  {
    float lifeTime;
    float hideDelay;
    float scaleStart;
    float scaleEnd;
    float alphaStart;
    float alphaMiddle;
    float alphaEnd;
    int   texFrame;

    Param(): 
      lifeTime(0), hideDelay(0), scaleStart(1), scaleEnd(1),
      alphaStart(0), alphaMiddle(1), alphaEnd(0), texFrame(0)
    {} 
  };

  typedef PointBase<float> PointF;

public:
  Particle( Point pos, Texture::TPtrParam pTex, const Param &param ); 

  bool Update( float deltaTime );
  void Render() const;

private:
  static Point Round( PointF p );
  
private:
  Point m_pos;
  float m_time;
  Param m_param; 
  Texture::TPtr m_pTex;
};


#endif // ParticleObj_h__
