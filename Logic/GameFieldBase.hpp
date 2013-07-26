#ifndef GameFieldBase_h__
#define GameFieldBase_h__

#include "DefferedSharedPtrDeleter.hpp"
#include "Engine/Core/Matrix.hpp"

template<class GameObjectT>
class GameFieldBase: public DefferedSharedPtrDeleter<GameObjectT, typename GameObjectT::TGameObjectListTag>
{
private:
  typedef TinyList<GameObjectT, typename GameObjectT::TGameObjectListTag> TAllObjects;

public:
  typedef GameObjectT TGameObject;
  typedef typename TGameObject::TPtr TGOPtr;
  typedef typename TGameObject::TPtrParam TGOPtrParam;
  typedef typename GameObjectT::TFieldPos TFieldPos;
  typedef typename TFieldPos::TValueType TFieldCoord;
  typedef SizeBase<TFieldCoord> TFieldSize;

public:
  explicit GameFieldBase( TFieldSize size ): 
    m_field( size )
  {}

  ~GameFieldBase();
  void Clear();

  bool IsValid( TFieldCoord x, TFieldCoord y ) const
  {
    return m_field.IsValid( x, y );
  }

  bool IsValid( TFieldPos pt ) const
  {
    return IsValid( pt.x, pt.y );
  }

  TGOPtrParam Get( TFieldCoord x, TFieldCoord y ) const
  {
    ASSERT( IsValid(x, y) );
    ASSERT( !m_field(x, y) || m_field(x, y)->GetPos() == TFieldPos(x, y) );
    return m_field(x, y);
  }

  TGOPtrParam Get( const TGameObject *pObj ) const
  {
    ASSERT( pObj != 0 );

    TGOPtrParam pRes( Get(pObj->GetPos()) );
    ASSERT( pRes.get() == pObj );

    return pRes;
  } 

  void Set( int x, int y, TGOPtrParam pObj )
  {
    ASSERT( pObj );
    ASSERT( !Get(x, y) );
    ASSERT( this->CheckPtrDeleter(pObj) );

    m_field(x, y) = pObj;
    pObj->SetPos( TFieldPos(x, y) );
    m_allObjects.push_back( pObj.get() );
  }

  void Set( int x, int y )
  {
    ASSERT( Get(x, y) );
    m_field(x, y).get()->erase();
    m_field(x, y).reset();
  }

  void Move( TFieldPos from, TFieldPos to )
  {
    ASSERT( Get(from) && !Get(to) );
    m_field(to) = std::move( m_field(from) );
  }

  TGOPtrParam Get( TFieldPos pt ) const 
  { 
    return Get( pt.x, pt.y ); 
  }

  void Set( TFieldPos pt, TGOPtrParam pObj ) 
  { 
    Set( pt.x, pt.y, pObj ); 
  } 

  void Set( TFieldPos pt ) 
  { 
    Set( pt.x, pt.y ); 
  } 

  TFieldSize GetSize() const
  {
    return m_field.GetSize();
  }

  template<class GameObjectT2, class Fnc>
  friend void ForEachSafeDelete( const GameFieldBase<GameObjectT2> &field, Fnc fnc );

  void DestroyDeleatedObjects()
  {
    this->DestroyAll();
  }

private:
  Matrix<TGOPtr, TFieldCoord> m_field;

  //Separate object list is used for multiple Update call prevention 
  //if object was moved in the m_field on the last call
  mutable TAllObjects m_allObjects;
};
//////////////////////////////////////////////////////////////////////////

template<class GameObjectT>
GameFieldBase<GameObjectT>::~GameFieldBase()
{
  DEBUG_OP( Clear() );
}
//////////////////////////////////////////////////////////////////////////

template<class GameObjectT>
void GameFieldBase<GameObjectT>::Clear()
{
  ASSERT( this->IsDestroyListEmpty() );
  ForEach(GetSize(), [this]( TFieldPos pos )
  {
    if( Get(pos) )
      Set(pos);         
  });

  ASSERT( m_allObjects.empty() );
  DestroyDeleatedObjects(); 
}
//////////////////////////////////////////////////////////////////////////

template<class GameObjectT, class Fnc>
void ForEachSafeDelete( const GameFieldBase<GameObjectT> &field, Fnc fnc )
{
  //We are moving items to new list (very fast operation) to prevent problems with deleting
  typename GameFieldBase<GameObjectT>::TAllObjects newList;

  while( !field.m_allObjects.empty() )
  {
    GameObjectT * const pObj = field.m_allObjects.pop_front_ptr();
    newList.push_back( pObj );

    ASSERT( field.Get(pObj->GetPos()).get() == pObj );
    fnc( pObj );
  }

  field.m_allObjects.swap( newList );
}
//////////////////////////////////////////////////////////////////////////

template<class TCoord, class Fnc>
void ForEach( SizeBase<TCoord> size, Fnc fnc )
{
  PointBase<TCoord> cur;

  for( cur.y = 0; cur.y < size.h; ++cur.y )
    for( cur.x = 0; cur.x < size.w; ++cur.x ) 
      fnc( cur );
}
//////////////////////////////////////////////////////////////////////////

template<class TCoord, class Fnc>
void ForEachRadius( PointBase<TCoord> center, TCoord radius, Fnc fnc )
{
  const float radiusf = radius - 0.5f;
  const float radius2 = radiusf * radiusf;
  PointBase<TCoord> cur;

  for( cur.y = center.y - radius; cur.y <= center.y + radius; ++cur.y )
    for( cur.x = center.x - radius; cur.x <= center.x + radius; ++cur.x )  
      if( vecLengthSquared(PointBase<float>(cur - center)) <= radius2 )
        fnc( cur );
}
//////////////////////////////////////////////////////////////////////////

template<class GameObjectT, class TCoord, class Fnc>
void ForEachRadius( const GameFieldBase<GameObjectT> &field, PointBase<TCoord> center, TCoord radius, Fnc fnc )
{
  ForEachRadius( center, radius, [&field, fnc]( PointBase<TCoord> cur )
  {
    if( !field.IsValid(cur) )
      return;

    auto &pVal = field.Get(cur);

    if( pVal )
      fnc(pVal);    
  });
}
//////////////////////////////////////////////////////////////////////////



#endif // GameFieldBase_h__
