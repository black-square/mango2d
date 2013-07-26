#ifndef DefferedSharedPtrDeleter_h__
#define DefferedSharedPtrDeleter_h__
#include "TinyList.hpp"

//Special shared_ptr deleter (DefferedSharedPtrDeleter.hpp) which keeps object 
//destruction until Update() method finishes, but week pointers become expired 
//immediately.

template<class T, class TinyListTagT>
class DefferedSharedPtrDeleter: boost::noncopyable
{
public:
  ~DefferedSharedPtrDeleter()
  {
    ASSERT( m_destroyList.empty() );
    DestroyAll();
  }

  //Unfortunately MSVC doesn't implement variadic templates
  template< class T >
  boost::shared_ptr<T> MakeShared()
  {
    return boost::shared_ptr<T>( new T(), Deleter(this) ); 
  }

  template< class T, class A1 >
  boost::shared_ptr<T> MakeShared( A1 && a1 )
  {
    return boost::shared_ptr<T>( new T(std::forward<A1>(a1)), Deleter(this) ); 
  }

  template< class T, class A1, class A2 >
  boost::shared_ptr<T> MakeShared( A1 && a1, A2 &&a2 )
  {
    return boost::shared_ptr<T>( new T(std::forward<A1>(a1), std::forward<A2>(a2)), Deleter(this) ); 
  }

  template< class T, class A1, class A2, class A3 >
  boost::shared_ptr<T> MakeShared( A1 && a1, A2 &&a2, A3 &&a3 )
  {
    return boost::shared_ptr<T>( new T(std::forward<A1>(a1), std::forward<A2>(a2), std::forward<A3>(a3)), Deleter(this) ); 
  }

  template< class T, class A1, class A2, class A3, class A4 >
  boost::shared_ptr<T> MakeShared( A1 && a1, A2 &&a2, A3 &&a3, A4 &&a4 )
  {
    return boost::shared_ptr<T>( new T(std::forward<A1>(a1), std::forward<A2>(a2), std::forward<A3>(a3), 
                             std::forward<A4>(a4)), Deleter(this) ); 
  }

  template< class T, class A1, class A2, class A3, class A4, class A5 >
  boost::shared_ptr<T> MakeShared( A1 && a1, A2 &&a2, A3 &&a3, A4 &&a4, A5 &&a5 )
  {
    return boost::shared_ptr<T>( new T(std::forward<A1>(a1), std::forward<A2>(a2), std::forward<A3>(a3), 
      std::forward<A4>(a4), std::forward<A5>(a5)), Deleter(this) ); 
  }

protected:
  bool CheckPtrDeleter( const boost::shared_ptr<T> &p ) const
  {
    Deleter *const pDel = boost::get_deleter<Deleter>(p);
    return pDel != 0 && pDel->m_pParent == this; 
  } 
  
  bool IsDestroyListEmpty() const
  {
    return m_destroyList.empty();
  } 

  void DestroyAll()
  {
    while( !m_destroyList.empty() )
      delete m_destroyList.pop_front_ptr();  
  }

private:
  class Deleter
  {
  public:
    explicit Deleter( DefferedSharedPtrDeleter *pParent ): m_pParent(pParent) {}

    void operator()( T *p ) const
    {
      m_pParent->m_destroyList.push_back(p);
    }

  private:
    friend class DefferedSharedPtrDeleter;
    DefferedSharedPtrDeleter *m_pParent; 
  };

private:
  TinyList<T, TinyListTagT> m_destroyList;    
};


#endif // DefferedSharedPtrDeleter_h__
