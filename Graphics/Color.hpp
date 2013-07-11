#pragma once

////////////////////////////////////////////////////////////////////////////////////////////
// ѕредставление цвета
////////////////////////////////////////////////////////////////////////////////////////////
class Color
{
public:
    Color() { set(max(), min(), max(), max()); }
    explicit Color( GLuint color ) { set_platform_value(color); }
    Color( GLubyte r, GLubyte g, GLubyte b, GLubyte a ){ set(r, g, b, a); }
    Color( GLubyte r, GLubyte g, GLubyte b ){ set(r, g, b, max()); }

    GLuint get_platform_value() const { return m_platform_value;  }
    void set_platform_value( GLuint color ) { m_platform_value = color; }

    GLubyte r()   const { return m_r; }
    GLubyte g()   const { return m_g; }
    GLubyte b()   const { return m_b; }
    GLubyte a()   const { return m_a; }
    
    //GLfixed rx() const { return ubtofixed( r() ); }
    //GLfixed gx() const { return ubtofixed( g() ); }
    //GLfixed bx() const { return ubtofixed( b() ); }
    //GLfixed ax() const { return ubtofixed( a() ); }
    
    GLfloat rf() const { return ubtofloat( r() ); }
    GLfloat gf() const { return ubtofloat( g() ); }
    GLfloat bf() const { return ubtofloat( b() ); }
    GLfloat af() const { return ubtofloat( a() ); }
    
    GLint ri() const { return ubtoint( r() ); }
    GLint gi() const { return ubtoint( g() ); }
    GLint bi() const { return ubtoint( b() ); }
    GLint ai() const { return ubtoint( a() ); }
    
    void set_rgb_only( GLubyte r, GLubyte g, GLubyte b ) 
    { 
        m_r = r;
        m_g = g;
        m_b = b;      
    }    
    
    void set( GLubyte r, GLubyte g, GLubyte b, GLubyte a ) 
    { 
        set_rgb_only( r, g, b );
        m_a = a;
    }
    
    void setf_rgb_only( GLfloat r, GLfloat g, GLfloat b )
    {
        m_r = floattoub(r);
        m_g = floattoub(g);
        m_b = floattoub(b); 
    }
    
    void setf( GLfloat r, GLfloat g, GLfloat b, GLfloat a )
    {
        setf_rgb_only( r, g, b );
        m_a = floattoub(a); 
    }
    
    void setr( GLubyte v ) { m_r = v; } 
    void setg( GLubyte v ) { m_g = v; } 
    void setb( GLubyte v ) { m_b = v; }
    void seta( GLubyte v ) { m_a = v; } 
    
    static GLubyte max() { return 255; }
    static GLubyte min() { return 0; }

    SDL_Color toSDL_Color() const 
    {
      SDL_Color cl;

      cl.r = r();
      cl.g = g();
      cl.b = b();
      cl.unused = a();

      return cl;
    }

public:
    static Color make_red()      { return Color( max(), min(), min() ); }
    static Color make_green()    { return Color( min(), max(), min() ); }
    static Color make_blue()     { return Color( min(), min(), max() ); }
    static Color make_black()    { return Color( min(), min(), min() ); }
    static Color make_white()    { return Color( max(), max(), max() ); }
    static Color make_cyan()     { return Color( min(), max(), max() ); }
    static Color make_magenta()  { return Color( max(), min(), max() ); }
    static Color make_yellow()   { return Color( max(), max(), min() ); }

    static Color make_white_a( GLubyte a )  { return Color( max(), max(), max(), a ); } 
    static Color make_white_af( GLfloat a )  { return Color( max(), max(), max(), floattoub(a) ); } 
    
    friend Color change_a( Color c, GLubyte a )  { return Color( c.r(), c.g(), c.b(), a ); } 

private:
    //static GLfixed ubtofixed( GLubyte val ) { return (PVRTF2X(val)) / max(); } 
    static GLfloat ubtofloat( GLubyte val ) { return (GLfloat(val)) / max(); } 
    static GLint   ubtoint( GLubyte val )   { static const GLint coef = INT_MAX / max(); return coef * val; } 
    
    static GLubyte floattoub( GLfloat val ) { return GLubyte( val * max() + 0.5f ); } 
     
#if 0
    template<int n>
    static GLuint make( GLubyte c ) { return GLuint(c) << (n * CHAR_BIT); }
    
    template<int n>
    GLubyte get() const { return static_cast<GLubyte>(m_color >> (n * CHAR_BIT)); }
    
    template<int n>
    static GLuint mask() { return GLuint( GLubyte(~0) ) << (n * CHAR_BIT); }
        
    template<int n>
    void set_part( GLubyte v ) { m_color = (m_color & ~mask<n>()) | make<n>(v); }
    
    enum TComponent
    {
        R,
        G,
        B,
        A        
    };
    
    GLuint m_color;
#else
    
    union 
    {
        GLuint m_platform_value;
        
        struct
        {
            GLubyte m_r, m_g, m_b, m_a;
        };
    };
#endif
};

inline bool operator==( const Color &c1, const Color &c2 )
{
    return c1.get_platform_value() == c2.get_platform_value();
}

inline bool operator!=( const Color &c1, const Color &c2 )
{
    return !(c1 == c2);
}


inline void glColor( const Color &c )
{
   glColor4f( c.rf(), c.gf(), c.bf(), c.af() );
}

#if 0
inline void glColorPointer(	GLsizei stride, const Color *pointer )
{
    STATIC_ASSERT( sizeof(Color) == 4 * sizeof(GLubyte) );    
    glColorPointer( 4, GL_UNSIGNED_BYTE, stride, pointer );   
}

inline void glTexEnv( GLenum target, GLenum pname, const Color &c )
{
    const GLfixed data[4] = { c.rx(), c.gx(), c.bx(), c.ax() };
    glTexEnvxv( target, pname, data );
};
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////
// »нициализировать значени€ цвета RGB из пространства HSV (HSB) 
// Ёто же пространство использует Photoshop
// http://en.wikipedia.org/wiki/HSL_color_space
// h - цветовой тон, [0 Ч 360)∞
// s - насыщенность, [0 - 1]
// v - €ркость, [0 - 1] 
///////////////////////////////////////////////////////////////////////////////////////////////////////
inline Color MakeColorFromHSV( GLfloat h, GLfloat s, GLfloat v, GLubyte a = Color::max() )
{
    ASSERT( h >= 0 && h < 360 ); 
    ASSERT( s >= 0 && s <= 1 );
    ASSERT( v >= 0 && v <= 1 );
    
    Color c;

    const GLfloat fl_h = floorf( h / 60 );
    const GLfloat f = h / 60 - fl_h;
    const GLfloat p = v * (1 - s);
    const GLfloat q = v * (1 - f * s);
    const GLfloat t = v * (1 - (1 - f) * s);
    
    switch( (GLint)fl_h % 6 )
    {
        case 0: c.setf_rgb_only(v, t, p); break;
        case 1: c.setf_rgb_only(q, v, p); break;
        case 2: c.setf_rgb_only(p, v, t); break;
        case 3: c.setf_rgb_only(p, q, v); break;
        case 4: c.setf_rgb_only(t, p, v); break;
        case 5: c.setf_rgb_only(v, p, q); break;
    }

    c.seta( a );

    return c;
}

