#ifndef ParticlesManager_h__
#define ParticlesManager_h__

#include "Particle.h"

class ParticlesManager: boost::noncopyable
{
public:
  void Update( float deltaTime );
  void Render() const; 

  void Emit( Point pos, Texture::TPtrParam pTex, const Particle::Param &param );
  void Emit( Point pos, Texture::TPtrParam pTex, const Particle::Param rgParams[], int count );
   
private:
  typedef std::list<Particle::TPtr> TParticles;

private:
  TParticles m_particles;
};

#endif // ParticlesManager_h__
