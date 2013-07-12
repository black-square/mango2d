#ifndef Camera_h__
#define Camera_h__

class Camera
{
public:
  typedef PointBase<float> PointF;
  typedef SizeBase<float> SizeF;

public:
  Camera( SizeF fieldSize, SizeF viewportSize );
  void Update( float deltaTime );
  void SetDestPos( PointF destPos );
  
  PointF screenToField( PointF pos ) const;

  void SetTransform();
  void RestoreTransform();

private:
  SizeF  m_fieldSize;
  SizeF  m_viewportSize; 
  PointF m_curPos;
  PointF m_destPos;
  PointF m_velocity;
    
};

#endif // Camera_h__
