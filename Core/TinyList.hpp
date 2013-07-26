#pragma once

#include <boost/type_traits/remove_const.hpp>

///////////////////////////////////////////////////////////////////////////////
// ���������� �������������� ������������� � ������������ ������� �� ��������� 
// ������ ����������. �.�. ����������/�������� �������� �� ������ �� �������� 
// � �������/������������ ������ � ������ ������������/�����������. ����� 
// �������� �������� �� ������, ������� ���������� ���� ��������, �� �������� 
// �� ���� ������� ���! ��� ��������� ��������� �� ���������� �������� 
// ��������� �� ���� ������� ���������� ������� � ��������� _ptr (����� ������ 
// � ������ � CFixedPool).
//
// ��� ��������� �������� � ��������� ��� ������ ������������� �� 
// TinySLink ��� TinyLink.
//
// ���������� ������ ������������� ��� ��� �� ����� ��� 
// CLinkList � CDblLinkList, ��:
//      - �����������, �� ���� ������������� �������������� �������
//      - ��������� ����� ���������, ������� � STL
//      - �������� ��������� �������� � ���������� ������
///////////////////////////////////////////////////////////////////////////////

template< class, class > class TinySList;
template< class, class > class TinyList;

namespace tiny_list_detail
{
    //Bidirectional Iterator: http://www.sgi.com/tech/stl/BidirectionalIterator.html
    //������� ����� ��� ���������� ��� ��������������� ��� � ������������� ������
    //������������� �������� ����� ��������� ������������, �� �� ��������
    template<class T, class TagT, class NodeT>
    class TIteratorBase
    {
        typedef TIteratorBase<typename boost::remove_const<T>::type, TagT, typename boost::remove_const<NodeT>::type> iterator;
        typedef TIteratorBase<const T, TagT, const NodeT> const_iterator;
        
    public:
        typedef T value_type; 
        typedef value_type *pointer; 
        typedef value_type &reference;
        
    public:
        TIteratorBase()
        {
            DEBUG_OP( m_pCur = 0 );
        }
        
        //copy constructor for iterator and constructor from iterator for const_iterator
        TIteratorBase( const iterator &it ): m_pCur(it.m_pCur) {}
        
        reference operator*() const 
        {
            ASSERT( m_pCur != 0 );
            ASSERT( m_pCur->isLinked() );
            return *static_cast<T *>( m_pCur );
        }
        
        pointer operator->() const { return &**this; }
        
        TIteratorBase &operator++() 
        {
            ASSERT( m_pCur != 0 );
            ASSERT( m_pCur->pNext != 0 );
            ASSERT( m_pCur->isLinked() );
            
            m_pCur = m_pCur->pNext;
            return *this;
        }
        
        TIteratorBase operator++(int) 
        {
            TIteratorBase tmp(*this);
            ++(*this);
            return tmp;
        }
        
        TIteratorBase &operator--() 
        {
            ASSERT( m_pCur != 0 );
            ASSERT( m_pCur->pPrev != 0 );
            ASSERT( m_pCur->isLinked() );

            m_pCur = m_pCur->pPrev;
            return *this;
        }
        
        TIteratorBase operator--(int) 
        {
            TIteratorBase tmp(*this);
            --(*this);
            return tmp;
        }
        
        friend bool operator==( const TIteratorBase &it1, const TIteratorBase &it2 ) 
        {
            return it1.m_pCur == it2.m_pCur;
        }
        
        friend bool operator!=( const TIteratorBase &it1, const TIteratorBase &it2 ) 
        {
            return !(it1 == it2);
        }
        
    private:
        explicit TIteratorBase( NodeT *pCur ): m_pCur(pCur) { ASSERT( m_pCur != 0 ); }

    private: 
        friend class TIteratorBase<const T, TagT, const NodeT>;
        template< class, class > friend class ::TinySList;
        template< class, class > friend class ::TinyList;
        NodeT *m_pCur;
    };    
    
} //namespace tiny_list_detail

///////////////////////////////////////////////////////////////////////////////
// ������� ����� �� �������� ������ ������������� �������, ��� �������� 
// � ������������� ������ TinySList
// �������� TagT ������ ��� ���� ����� ������ ����� ���� ������� � ������ 
// ������� (������ ����� ��������� ��� ������������� �� TinySLink � 
// ������� TagT). TagT ����� �� �������������� � ����� ���� ������������.
///////////////////////////////////////////////////////////////////////////////
template< class TagT = int>
struct TinySLink: boost::noncopyable
{
    TinySLink()
    {
        DEBUG_OP( clearLinkFlag() );
    }

    ~TinySLink()
    {
        ASSERT( !isLinked() );
    }

private:
    //�� ����� ������� �������������� �������:
    //���� pNext == this, ������ ������ �� ��������� � ����� ���� ������
    bool isLinked() const { return pNext != this; }
    void clearLinkFlag() { pNext = this; }
    
private:
    template< class, class > friend class TinySList;
    template< class, class, class > friend class tiny_list_detail::TIteratorBase;
    TinySLink *pNext;
};

///////////////////////////////////////////////////////////////////////////////
// ������������� ������ ������������� ������ � 
// STL http://www.sgi.com/tech/stl/Slist.html
//      T    - �������� ������� ���� ����� �������� � ������
//      TagT - ����� ������, ��� ��������� �������� ��������� � ���������� 
//             ������� ������������
///////////////////////////////////////////////////////////////////////////////
template< class T, class TagT = int >
class TinySList: boost::noncopyable
{
    typedef TinySLink<TagT> TNode;
        
public:
    typedef tiny_list_detail::TIteratorBase<T, TagT, TNode> iterator;
    typedef tiny_list_detail::TIteratorBase<const T, TagT, const TNode> const_iterator;
    
public:
    iterator begin() { return iterator(m_base.pNext); }
    iterator end()   { return iterator(&m_base); }
    const_iterator begin() const { return const_iterator(m_base.pNext); }
    const_iterator end()   const { return const_iterator(&m_base); }
    
    TinySList()
    {
        reset();
    }

    ~TinySList() { clear(); }
    
    T &front() { ASSERT(!empty()); ASSERT(m_base.pNext != 0); return *static_cast<T *>(m_base.pNext); }
    const T &front() const { ASSERT(!empty()); ASSERT(m_base.pNext != 0); return *static_cast<const T *>(m_base.pNext); }
    
    void push_front( T *pItem ) { insert_after_impl( &m_base, pItem ); }
    void pop_front() { ASSERT( !empty() ); erase_after_impl( &m_base ); }
    T *pop_front_ptr(){ T &rez = front(); pop_front(); return &rez; }
    
    void insert_after( iterator pos, T *pItem ) { ASSERT(pos != end()); insert_after_impl( pos.m_pCur, pItem ); }
    
    void erase_after( T *pItem ) { ASSERT(pItem != &m_base); erase_after_impl( pItem ); }
    T *erase_after_ptr( T *pItem ) { T * const pRez = getNext( pItem ); erase_after( pItem ); return pRez; }

    //��������� �������� � ���������� before_begin(), ��� ����� ���� ��������� ������� 
    //erase_after_general
    void erase_after( iterator pos ) { ASSERT(pos != end()); erase_after_impl( pos.m_pCur ); }
    T *erase_after_ptr( iterator pos ) { T * const pRez = getNext( pos ); erase_after( pos ); return pRez; }
    
    bool empty() const { return m_base.pNext == &m_base; }

    void clear() 
    {   
        DEBUG_OP( clearAllLinksFlag() );
        reset();
    }

    //���������� ����������� �������� pos, ����������� ����� ������ ��������� �����,
    //��� ++pos == begin(). ����� �������� ������ �������������� � �� ������ ��� ����, 
    //����� ���� ������ �������������� ����� c ��������� ������������� �������� (������� 
    //������), ��� ����� ����� ������� ��� ���������, ���������� = before_begin()
    //� ������� begin() � �������� ��� �������� ��������, ������ erase_after() 
    //erase_after_general(), ��������� ������������ �������. ������:
    //
    //        for( iterator prev = before_begin(), cur = begin(); cur != end(); )
    //        {
    //            if( needDelete(*cur) ) { ++cur; erase_after_general(prev); }
    //            else                   { prev = cur; ++cur; }
    //        }
    //
    iterator before_begin()                  { return iterator(&m_base); }
    const_iterator before_begin()   const    { return const_iterator(&m_base); }
    void erase_after_general( iterator pos ) { erase_after_impl( pos.m_pCur ); }
    T *erase_after_general_ptr( iterator pos ) { T * const pRez = getNext( pos ); erase_after_general( pos ); return pRez; }

    //���� �� � ������ ������� pNode
    //������������ ��� �������
    bool hasElement( const TNode *pNode ) const
    {
        for( const_iterator it = begin(); it != end(); ++it )
            if( it.m_pCur == pNode )
                return true;
        
        return false;
    }

private:
    void reset()
    {
        m_base.pNext = &m_base;
    }

    void insert_after_impl( TNode *pPos, TNode *pNode )
    {
        ASSERT( pPos != 0 );
        ASSERT( pPos == &m_base || hasElement(pPos) ); //��� ������ push_front() pPos == &m_base 
        ASSERT( pNode != 0 );
        ASSERT( !pNode->isLinked() );
        ASSERT( pNode != &m_base && !hasElement(pNode) );  
        ASSERT( pPos->pNext != 0 );
        
        pNode->pNext = pPos->pNext;
        pPos->pNext = pNode;
    }

    void erase_after_impl( TNode *pNode )
    {
        ASSERT( pNode != 0 );
        ASSERT( pNode->pNext != 0 );
        ASSERT( pNode->pNext->pNext != 0 );
        ASSERT( pNode->isLinked() );
        ASSERT( pNode->pNext->isLinked() );
        ASSERT( pNode == &m_base || hasElement(pNode) ); //��� ������ pop_front() pPos == &m_base 
        ASSERT( pNode->pNext != &m_base );

        DEBUG_VAR( TNode * const pTmp = pNode->pNext );
        pNode->pNext = pNode->pNext->pNext;
        DEBUG_OP( pTmp->clearLinkFlag() );
    }

    //������� clearLinkFlag() � ���� ��������� 
    void clearAllLinksFlag()
    {
        while( !empty() ) pop_front();
    }

    //�������� ��������� �� ��������� �������
    static T *getNext( T *pItem )
    {
        ASSERT( pItem != 0 ); 
        return static_cast<T *>( static_cast<TNode *>(pItem)->pNext );
    }

    static T *getNext( iterator pos )
    { 
        return &*(++pos);
    }

private:
    TNode m_base;
};


///////////////////////////////////////////////////////////////////////////////
// ������� ����� �� �������� ������ ������������� �������, ��� �������� 
// � ������������ ������ TinyList
// �������� TagT ������ ��� ���� ����� ������ ����� ���� ������� � ������ 
// ������� (������ ����� ��������� ��� ������������� �� TinyLink � 
// ������� TagT). TagT ����� �� �������������� � ����� ���� ������������.
///////////////////////////////////////////////////////////////////////////////
template< class TagT = int >
struct TinyLink: boost::noncopyable
{
    TinyLink()
    {
        DEBUG_OP( clearLinkFlag() );
    }

    ~TinyLink()
    {
        ASSERT( !isLinked() );
    }

    //������ ������� �� ������������� ������ ������� � ���, ��� ������� ����� 
    //������� �� ������ �� ����� ������ � ������ ������ (�.�. ��� ��������� 
    //�� TinyList)
    //���� ������� �� ��������� � ������, �� ��������� ���������� �� �����������! 
    //����� ������������ �������� ��� ������ ������ TinyList, �.�.
    //� ���������� ������ ����� ������������ ������ ��������.
    void erase()
    {
        ASSERT( isLinked() );
        ASSERT( pNext != 0 );
        ASSERT( pPrev != 0 );
        
        pPrev->pNext = pNext;
        pNext->pPrev = pPrev;
        
        DEBUG_OP( clearLinkFlag() );
    }

private:
    //�� ����� ������� �������������� �������:
    //���� pNext == this, ������ ������ �� ��������� � ����� ���� ������
    bool isLinked() const { ASSERT( (pNext == this) == (pPrev == this) ); return pNext != this; }
    void clearLinkFlag() { pNext = this; pPrev = this; }

private:
    template< class, class > friend class TinyList;
    template< class, class, class > friend class tiny_list_detail::TIteratorBase;
    TinyLink *pNext;
    TinyLink *pPrev;
};


///////////////////////////////////////////////////////////////////////////////
// ������������ ������ ������������� ������ � 
// STL http://www.sgi.com/tech/stl/List.html
//      T    - �������� ������� ���� ����� �������� � ������
//      TagT - ����� ������, ��� ��������� �������� ��������� � ���������� 
//             ������� ������������
///////////////////////////////////////////////////////////////////////////////
template< class T, class TagT = int >
class TinyList: boost::noncopyable
{
    typedef TinyLink<TagT> TNode;

public:
    typedef tiny_list_detail::TIteratorBase<T, TagT, TNode> iterator;
    typedef tiny_list_detail::TIteratorBase<const T, TagT, const TNode> const_iterator;

public:
    iterator begin() { return iterator(m_base.pNext); }
    iterator end()   { return iterator(&m_base); }
    const_iterator begin() const { return const_iterator(m_base.pNext); }
    const_iterator end()   const { return const_iterator(&m_base); }

    TinyList()
    {
        reset();
    }

    ~TinyList() { clear(); }

    T &front() { ASSERT(!empty()); ASSERT(m_base.pNext != 0); return *static_cast<T *>(m_base.pNext); }
    const T &front() const { ASSERT(!empty()); ASSERT(m_base.pNext != 0); return *static_cast<const T *>(m_base.pNext); }
    T &back() { ASSERT(!empty()); ASSERT(m_base.pPrev != 0); return *static_cast<T *>(m_base.pPrev); }
    const T &back() const { ASSERT(!empty()); ASSERT(m_base.pPrev != 0); return *static_cast<const T *>(m_base.pPrev); }

    void push_front( T *pItem ) { insert_impl( m_base.pNext, pItem ); }
    void push_back( T *pItem ) { insert_impl( &m_base, pItem ); }
    void pop_front() { ASSERT( !empty() ); erase_impl( m_base.pNext ); }
    void pop_back() { ASSERT( !empty() ); erase_impl( m_base.pPrev ); }

    T *pop_front_ptr(){ T &rez = front(); pop_front(); return &rez; }
    T *pop_back_ptr(){ T &rez = back(); pop_back(); return &rez; }

    void insert( iterator pos, T *pItem ) { insert_impl( pos.m_pCur, pItem ); }
    void erase( T *pItem ) { erase_impl( pItem ); }
    void erase( iterator pos ) { erase_impl( pos.m_pCur ); }

	  T *erase_ptr( T *pItem ) { erase( pItem ); return *pItem; }
	  T *erase_ptr( iterator pos ) { T &rez = *pos; erase( pos ); return &rez; }

    bool empty() const 
    { 
        ASSERT( (m_base.pNext == &m_base) == (m_base.pPrev == &m_base) ); 
        return m_base.pNext == &m_base; 
    }

    void clear() 
    {   
        DEBUG_OP( clearAllLinksFlag() );
        reset();
    }

    void swap( TinyList &other )
    {
      changeBase( &other.m_base );
      other.changeBase( &m_base );
      std::swap( m_base.pNext, other.m_base.pNext );
      std::swap( m_base.pPrev, other.m_base.pPrev );
    }

    //���� �� � ������ ������� pNode
    //������������ ��� �������
    bool hasElement( const TNode *pNode ) const
    {
        for( const_iterator it = begin(); it != end(); ++it )
            if( it.m_pCur == pNode )
                return true;
        
        return false;
    }

private:
    void reset()
    {
        m_base.pNext = &m_base;
        m_base.pPrev = &m_base;
    }

    void insert_impl( TNode *pPos, TNode *pNode )
    {
        ASSERT( pPos != 0 );
        ASSERT( pPos == &m_base || hasElement(pPos) );
        ASSERT( pNode != 0 );
        ASSERT( !pNode->isLinked() );
        ASSERT( pNode != &m_base && !hasElement(pNode) );  
        ASSERT( pPos->pPrev != 0 );
        ASSERT( pPos->pNext != 0 );
        
        pNode->pPrev = pPos->pPrev;
        pNode->pNext = pPos;
        pPos->pPrev->pNext = pNode;
        pPos->pPrev = pNode;
    }

    void erase_impl( TNode *pNode )
    {
        ASSERT( pNode != 0 );
        ASSERT( pNode->isLinked() );
        ASSERT( pNode != &m_base && hasElement(pNode) );
        
        pNode->erase();
    }    

    //������� clearLinkFlag() � ���� ��������� 
    void clearAllLinksFlag()
    {
        while( !empty() ) pop_front();
    }

    void changeBase( TNode *pNewBase )
    {
      //��������� ���������� �������� ��������� ���������� ������ ������
      TNode * const pNextTmp = m_base.pNext;
      m_base.pPrev->pNext = pNewBase;
      pNextTmp->pPrev = pNewBase;
    }

private:
    TNode m_base;
};

