#ifndef WAITABLE_QUEUE_HPP
#define WAITABLE_QUEUE_HPP
#include <queue>
#include "common.hpp"
#include "mutex.hpp"
#include "condVar.hpp"

namespace advcpp{

static const size_t DEFAULT_CAPACITY = 64;

template <typename T>
class WaitableQueue : private Uncopyable
{
public:
    explicit WaitableQueue(size_t a_capacity = DEFAULT_CAPACITY) THROW2(MutexException, CondVarException);
    //~WaitableQueue() NOEXCEPT = default;

    void Enqueue(T const& a_data) THROW2(MutexException, CondVarException);
    void Dequeue(T& a_data);

    size_t Size() const THROW1(MutexException);
    size_t Capacity() const NOEXCEPT;

    template <typename U>
    friend class IsQEmpty;

    template <typename U>
    friend class IsQFull;

private:
    bool IsFull() const NOEXCEPT;
    bool IsEmpty() const NOEXCEPT;

private:
    std::queue<T> m_queue;
    CondVar m_cv;
    mutable Mutex m_mutex; 
    const size_t m_capacity;
};

template <typename T>
class IsQEmpty
{
public:
    explicit IsQEmpty(WaitableQueue<T>& a_queue);
    //~IsEmpty() = default;
    //IsEmpty(IsEmpty const&) = default;
    //IsEmpty& operator=(IsEmpty const&) = default;

    bool operator()();

private:
    WaitableQueue<T> const& m_queue;
};

template <typename T>
class IsQFull
{
public:
    explicit IsQFull(WaitableQueue<T>& a_queue);
   //~IsFull() = default;
    //IsFull(IsFull const&) = default;
    //IsFull& operator=(IsFull const&) = default;

    bool operator()();

private:
    WaitableQueue<T> const& m_queue;    
};

} //namespace advcpp

#include "inl/waitable_queue.inl"

#endif //WAITABLE_QUEUE_HPP