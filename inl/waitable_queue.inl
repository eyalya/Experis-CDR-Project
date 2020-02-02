#include "waitable_queue.hpp"
#include "locks.hpp"

namespace advcpp
{

template <typename T>
WaitableQueue<T>::WaitableQueue(size_t a_capapcity)
: m_que()
, m_lock()
, m_conitionalVariable(m_lock)
, m_capacity(a_capapcity)
{
    assert(m_que.empty());
}

template <typename T>
void WaitableQueue<T>::Enqueue(T const& a_val)
{
    {
        Guard guard(m_lock);
        
        m_conitionalVariable.Wait(PredicateFull<T>(*this));
        
        m_que.push(a_val);
    }
    m_conitionalVariable.Notify();
}

template <typename T>
void WaitableQueue<T>::Dequeue(T& a_result)
{
    {
        Guard guard(m_lock);

        m_conitionalVariable.Wait(PredicateEmpty<T>(*this));
        
        a_result = m_que.front();    
        m_que.pop();
    }
    m_conitionalVariable.Notify();
}

template <typename T>
bool WaitableQueue<T>::IsEmpty() const
{
    Guard guard(m_lock);
    return m_que.empty();
}

template <typename T>
bool WaitableQueue<T>::isEmpty() const
{
    return m_que.empty();
}

template <typename T>
bool WaitableQueue<T>::isFull() const
{
    return m_que.size() == m_capacity;
}

template <typename T>
PredicateEmpty<T>::PredicateEmpty(WaitableQueue<T> const& a_que)
:m_que(a_que)
{ 
}

template <typename T>
bool PredicateEmpty<T>::operator () () const
{ 
    return m_que.isEmpty(); 
}

template <typename T>
PredicateFull<T>::PredicateFull(WaitableQueue<T> const& a_que)
:m_que(a_que)
{ }

template <typename T>
bool PredicateFull<T>::operator () () const
{ 
    return m_que.isFull(); 
}

} //namespace advcpp

