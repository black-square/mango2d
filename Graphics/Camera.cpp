#include "stdafx.h"
#include "Camera.h"
#include "Engine/Core/Interp.hpp"

Camera::Camera( SizeF fieldSize, SizeF viewportSize ):
  m_fieldSize(fieldSize), m_viewportSize(viewportSize)
{

}
//////////////////////////////////////////////////////////////////////////

void Camera::Update( float deltaTime )
{
  m_curPos = SmoothCritDamp( m_curPos, m_destPos, m_velocity, deltaTime, 0.2f );
}
//////////////////////////////////////////////////////////////////////////

void Camera::SetDestPos( PointF destPos )
{
  const PointF cameraPos = destPos - m_viewportSize / 2;
  RectBase<float> camera( cameraPos, m_viewportSize );

  const RectBase<float> bound( ( PointF() ), m_fieldSize );

  clamp( camera, bound );

  m_destPos = camera.getTopLeft();
}
//////////////////////////////////////////////////////////////////////////

Camera::PointF Camera::screenToField( PointF pos ) const
{
  return pos + round<PointF>( m_curPos );
}
//////////////////////////////////////////////////////////////////////////

void Camera::SetTransform()
{
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glTranslatef( -m_curPos.x, -m_curPos.y, 0 );
}
//////////////////////////////////////////////////////////////////////////

void Camera::RestoreTransform()
{
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

