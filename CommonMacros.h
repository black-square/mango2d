#ifndef ASSERT_H_BED03A6B_0132_41D9_98D6
#define ASSERT_H_BED03A6B_0132_41D9_98D6
#include <cassert>
#include <boost/static_assert.hpp>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define ARRAY_SIZE( a ) ( sizeof( a ) / sizeof( *(a) ) )

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef NDEBUG            
  #define ASSERT( cond ) assert( cond )
  #define ASSERT_MSG( cond, msg ) (void)( (!!(cond)) || (_wassert(_CRT_WIDE(#cond) ## _CRT_WIDE("\n") ## _CRT_WIDE(msg), _CRT_WIDE(__FILE__), __LINE__), 0) )
#else
	#define ASSERT( cond ) ((void)0)
  #define ASSERT_MSG( cond, msg ) ((void)0)
#endif
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
#ifndef NDEBUG
    #define VERIFY(expr) ASSERT(expr)
#else
    #define VERIFY(expr) ((void)(expr))
#endif
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef NDEBUG
    #define DEBUG_OP( arg ) ( arg )
#else
    #define DEBUG_OP( arg ) ( (void) 0 )
#endif
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef NDEBUG
    #define DEBUG_VAR( arg ) arg
#else
    #define DEBUG_VAR( arg ) typedef void BOOST_JOIN( DEBUG_VARIABLE_T_, __LINE__ )
#endif    
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                            

//http://gcc.gnu.org/onlinedocs/gcc-4.5.1/gcc/Variadic-Macros.html#Variadic-Macros
#define BIND_THIS(method, ...) boost::bind( &ThisType::method, this, ## __VA_ARGS__ )

#define FUNC_PARAM(...) const boost::function< void(__VA_ARGS__) > &

#endif //#define ASSERT_H_BED03A6B_0132_41D9_98D6
