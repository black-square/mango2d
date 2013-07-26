#ifndef DiscretePath_h__
#define DiscretePath_h__

//////////////////////////////////////////////////////////////////////////
// Bresenham's line drawing algorithm 
// http://en.wikipedia.org/wiki/Bresenham's_line_algorithm 
//////////////////////////////////////////////////////////////////////////
template<class T>
class DiscretePath
{
public:
  DiscretePath(): m_error(0) {}

  void Start( const PointBase<T> &dstPos )
  {
    m_nextPos = m_pos;
    m_dstPos = dstPos;
    m_delta = abs(m_dstPos - m_pos);
    m_sign.set( m_pos.x < m_dstPos.x ? 1 : -1, m_pos.y < m_dstPos.y ? 1 : -1 );
    m_error = m_delta.x - m_delta.y;
    CalcNext();
  }

  void Step()
  {
    m_pos = m_nextPos;
    CalcNext();  
  }

  void SetPos( const PointBase<T> &pos )
  {
    m_pos = pos;
    m_nextPos = pos;
    m_dstPos = pos;
  } 

  const PointBase<T> &GetPos() const { return m_pos; }
  const PointBase<T> &GetNextPos() const { return m_nextPos; }
  const PointBase<T> &GetDstPos() const { return m_dstPos; }

private:
  void CalcNext()
  {
    const T error2 = m_error * 2; 
    
    if( error2 > -m_delta.y ) 
    {
      m_error -= m_delta.y;
      m_nextPos.x += m_sign.x;
    }

    if( error2 < m_delta.x ) 
    {
      m_error += m_delta.x;
      m_nextPos.y += m_sign.y;
    }
  }

private:
  PointBase<T> m_pos;
  PointBase<T> m_nextPos;
  PointBase<T> m_dstPos;
  PointBase<T> m_delta;
  PointBase<T> m_sign;
  T m_error;  
};


#endif // DiscretePath_h__