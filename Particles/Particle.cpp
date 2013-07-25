#include "stdafx.h"
#include "Particle.h"
#include "Engine/Core/Interp.hpp"

//////////////////////////////////////////////////////////////////////////

Particle::Particle( Point pos, Texture::TPtrParam pTex, const Param &param ):
  m_pos(pos), m_time(0), m_param(param), m_pTex(pTex)
{

}
//////////////////////////////////////////////////////////////////////////
Point Particle::Round( PointF p )
{
  return Point( p + PointF(0.5f, 0.5f) );
}
//////////////////////////////////////////////////////////////////////////

bool Particle::Update( float deltaTime )
{
  m_time += deltaTime;
  
  if( m_time >= m_param.lifeTime )
    return false;

  return true;

}
//////////////////////////////////////////////////////////////////////////

void Particle::Render() const
{
  if( m_time < m_param.hideDelay )
    return;

  const float relTime = m_time / m_param.lifeTime;
  const float relTimeNoDelay = ( m_time - m_param.hideDelay ) / m_param.lifeTime;  
    
  const float scale = Lerp( m_param.scaleStart, m_param.scaleEnd, relTime );  
  const float alpha = ThreePointStepFactor<float>( m_param.alphaStart, m_param.alphaMiddle, m_param.alphaEnd )( relTimeNoDelay );
  
  Point diff = Round( PointF( m_pTex->GetSize() ) / 2 * scale );
  Rect rect( m_pos.x - diff.x, m_pos.y - diff.y, m_pos.x + diff.x, m_pos.y + diff.y );
  Draw( *m_pTex, rect, m_param.texFrame, Color::make_white_af(alpha) );  
}

//////////////////////////////////////////////////////////////////////////
