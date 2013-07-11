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

  void Start( const PointBase<T> &from, const PointBase<T> &to )
  {
    m_delta = abs(to - from);
    m_sign.set( from.x < to.x ? 1 : -1, from.y < to.y ? 1 : -1 );
    m_error = m_delta.x - m_delta.y;
  }

  void Next( PointBase<T> &cur )
  {
    const T error2 = m_error * 2; 
    
    if( error2 > -m_delta.y ) 
    {
      m_error -= m_delta.y;
      cur.x += m_sign.x;
    }

    if( error2 < m_delta.x ) 
    {
      m_error += m_delta.x;
      cur.y += m_sign.y;
    }
  }

private:
  PointBase<T> m_delta;
  PointBase<T> m_sign;
  T m_error;  
};


#endif // DiscretePath_h__