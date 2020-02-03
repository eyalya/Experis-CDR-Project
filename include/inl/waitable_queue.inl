#ifndef WAITABLE_QUEUE_INL
#define WAITABLE_QUEUE_INL
namespace advcpp{

template <typename T>
WaitableQueue<T>::WaitableQueue(size_t a_capacity) THROW2(MutexException, CondVarException)
: m_capacity(a_capacity)
{
}

template <typename T>
void WaitableQueue<T>::Enqueue(T const& a_data) THROW2(MutexException, CondVarException)
{
    {
        Guard guard(m_mutex);    
        m_cv.Wait(m_mutex, IsQFull<T>(*this));
        m_queue.push(a_data);
    }
    m_cv.Notify();
}

template <typename T>
void WaitableQueue<T>::Dequeue(T& a_data)
{
    {
        Guard guard(m_mutex);
        m_cv.Wait(m_mutex,IsQEmpty<T>(*this));
        a_data = m_queue.front();
        m_queue.pop();
    }
    m_cv.Notify();    
}

template <typename T>
size_t WaitableQueue<T>::Size() const THROW1(MutexException)
{
    m_mutex.Lock();
    size_t size = m_queue.size();
    m_mutex.Unlock();

    return size;
}

template <typename T>
size_t WaitableQueue<T>::Capacity() const NOEXCEPT
{
    Guard guard(m_mutex);
    return m_capacity;
}

template <typename T>
bool WaitableQueue<T>::IsEmpty() const NOEXCEPT
{
    Guard guard(m_mutex);
    return m_queue.size() == 0;
}

template <typename T>
bool WaitableQueue<T>::IsFull() const NOEXCEPT
{
    Guard guard(m_mutex);
    return m_queue.size() == m_capacity;
}

template <typename T>
IsQEmpty<T>::IsQEmpty(WaitableQueue<T>& a_queue)
: m_queue(a_queue)
{
}

template <typename T>
bool IsQEmpty<T>::operator()()
{
    return m_queue.IsEmpty();
}

template <typename T>
IsQFull<T>::IsQFull(WaitableQueue<T>& a_queue)
: m_queue(a_queue)
{
}

template <typename T>
bool IsQFull<T>::operator()()
{
    return m_queue.IsFull();
}

}//namespace advcpp
#endif //WAITABLE_QUEUE_INL