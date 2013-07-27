#ifndef CORE_RECT_H
#define CORE_RECT_H
#include "./point.hpp"
//////////////////////////////////////////////////////////////////////////////////////

template<typename T>
struct RectBase
{
    typedef T TValueType;

    T x1, y1; //Точки принадлежат прямоугольнику
    T x2, y2; //Точки НЕ принадлежат прямоугольнику

    RectBase(): x1(0), y1(0), x2(0), y2(0) {}
    RectBase( T _x1, T _y1, T _x2, T _y2 ): x1(_x1), y1(_y1), x2(_x2), y2(_y2) {}
    RectBase( const PointBase<T> &min, const PointBase<T> &max ): x1(min.x), y1(min.y), x2(max.x), y2(max.y) {}
    RectBase( const PointBase<T> &pos, const SizeBase<T> &size ): x1(pos.x), y1(pos.y), x2(pos.x + size.w), y2(pos.y + size.h) {}

    template< class OtherT >
    explicit RectBase( const RectBase<OtherT> &other ): x1(other.x1), y1(other.y1), x2(other.x2), y2(other.y2) {}

    RectBase &zeroize() { x1 = 0; y1 = 0; x2 = 0; y2 = 0; return *this; }

    PointBase<T> getCenter() const { return PointBase<T>( (x1 + x2) / 2, ( y1 + y2 ) / 2 ); }
    PointBase<T> getTopLeft() const { return PointBase<T>( x1, y1 ); }
    PointBase<T> getTopRight() const { return PointBase<T>( x2 - 1, y1 ); }
    PointBase<T> getBottomLeft() const { return PointBase<T>( x1, y2 - 1 ); }
    PointBase<T> getBottomRight() const { return PointBase<T>( x2 - 1, y2 - 1); }
    
    T getWidth() const { return x2 - x1; }
    T getHeight() const { return y2 - y1; }

    RectBase &setWidth( T val )
    {
        x2 = x1 + val;
        return *this;
    }

    RectBase &setHeight( T val )
    {
        y2 = y1 + val;
        return *this;
    }

    SizeBase<T> getSize() const { return SizeBase<T>(getWidth(), getHeight()); }
          
    //Специально не стал называть isIn дабы при переносе
    //старого кода компилятор указал на ошибку
    bool isContain( T x, T y ) const
    {
        return x >= x1 && x < x2 && y >= y1 && y < y2;
    }
    
    bool isContain( const PointBase<T> &p ) const
    {
        return isContain( p.x, p.y );
    }
    
    RectBase &set( T _x1, T _y1, T _x2, T _y2 )
    {
        x1 = _x1;
        y1 = _y1;
        x2 = _x2;
        y2 = _y2;

        return *this;
    }

    RectBase &setSize( T width, T height )
    {
        x2 = x1 + width;
        y2 = y1 + height;

        return *this;
    }

    RectBase &setSize( const SizeBase<T> &p )
    {
        return setSize( p.w, p.h );
    }

    RectBase &setPos( T left, T top )
    {
        x2 = left + getWidth();
        y2 = top + getHeight();
        x1 = left;
        y1 = top;

        return *this;
    }
    
    RectBase &setPos( const PointBase<T> &p )
    {
        return setPos( p.x, p.y );
    }

    PointBase<T> getPos() const
    {
        return getTopLeft();
    }

    RectBase &setPosCenter( T x, T y )
    {
        const T width = getWidth();
        const T height = getHeight();

        x1 = x - (width / 2);
        y1 = y - (height / 2);
        x2 = x1 + width;
        y2 = y1 + height;

        return *this;
    }

    RectBase &setPosCenter( const PointBase<T> &p )
    {
        return setPosCenter( p.x, p.y );
    }

    RectBase &moveOn( T x, T y )
    {
        x2 += x;
        y2 += y;
        x1 += x;
        y1 += y;

        return *this;
    }

    RectBase &moveOn( const PointBase<T> &p )
    {
        return moveOn( p.x, p.y );
    }

    RectBase &scaleOn( T val )
    {
        x1 -= val;
        y1 -= val;
        x2 += val;
        y2 += val;   

        return *this;
    }
};
//////////////////////////////////////////////////////////////////////////////////////
template< class T2 >
inline bool operator==( const RectBase<T2> &r1, const RectBase<T2> &r2 )
{
    return 
        r1.x1 == r2.x1 && 
        r1.x2 == r2.x2 && 
        r1.y1 == r2.y1 && 
        r1.y2 == r2.y2;
}
//////////////////////////////////////////////////////////////////////////////////////

template< class T2 >
inline bool operator!=( const RectBase<T2> &r1, const RectBase<T2> &r2 )
{
    return !( r1 == r2 );     
}
//////////////////////////////////////////////////////////////////////////////////////

//Пересекаются ли два прямоугольника.
//Hint: Если размер меньшего прямоугольника будет отрицательным то возникает интересный 
//эффект, когда функция возвращает true только если больший прямоугольник полностью
//включает меньший
template< class T2 >
inline bool isIntersect( const RectBase<T2> &r1, const RectBase<T2> &r2 )
{
    return r1.x1 < r2.x2 && r2.x1 < r1.x2 && r1.y1 < r2.y2 && r2.y1 < r1.y2;
}
//////////////////////////////////////////////////////////////////////////////////////

//Прямоугольник r сдвигается на минимальное растояние, так чтобы он полностью 
//помещался в bound
//Возвр: true в том случае когда r пришлось двигать
template< class T2 >
inline bool clamp( RectBase<T2> &r, const RectBase<T2> &bound )
{
    bool result = false;

    if( r.x1 < bound.x1 )
    {
        r.x2 = bound.x1 + r.getWidth();
        r.x1 = bound.x1;
        result = true;
    }
    else if( r.x2 > bound.x2 )
    {
        r.x1 = bound.x2 - r.getWidth();
        r.x2 = bound.x2;
        result = true;
    }

    if( r.y1 < bound.y1 )
    {
        r.y2 = bound.y1 + r.getHeight();
        r.y1 = bound.y1;        
        result = true;
    }  
    else if( r.y2 > bound.y2 )
    {
        r.y1 = bound.y2 - r.getHeight();
        r.y2 = bound.y2;
        result = true;
    }

    return result;
}
//////////////////////////////////////////////////////////////////////////

template< class T2 >
inline PointBase<T2> clamp( PointBase<T2> p, const RectBase<T2> &bound )
{ 
  if( p.x < bound.x1 )
    p.x = bound.x1;
  else if( p.x >= bound.x2 )
    p.x = bound.x2 - 1;

  if( p.y < bound.y1 )
    p.y = bound.y1;
  else if( p.y >= bound.y2 )
    p.y = bound.y2 - 1;

  return p;
}

//////////////////////////////////////////////////////////////////////////////////////
typedef RectBase<int> Rect;
//////////////////////////////////////////////////////////////////////////////////////

#endif
