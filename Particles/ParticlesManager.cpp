#include "stdafx.h"
#include "ParticlesManager.h"

void ParticlesManager::Update( float deltaTime )
{
  TParticles::iterator it = m_particles.begin();

  while( it != m_particles.end() )
    if( (*it)->Update(deltaTime) )
      ++it;
    else
      m_particles.erase( it++ );
}
//////////////////////////////////////////////////////////////////////////

void ParticlesManager::Render() const
{
  BOOST_FOREACH( const Particle::TPtr &p, m_particles )
    p->Render();  
} 
//////////////////////////////////////////////////////////////////////////

void ParticlesManager::Emit( Point pos, Texture::TPtrParam pTex, const Particle::Param &param ) 
{
  m_particles.push_back( boost::make_shared<Particle>( pos, pTex, param) );
}
//////////////////////////////////////////////////////////////////////////

void ParticlesManager::Emit( Point pos, Texture::TPtrParam pTex, const Particle::Param rgParams[], int count )
{
  for( int i = 0; i < count; ++i )
    Emit( pos, pTex, rgParams[i] );     
}
