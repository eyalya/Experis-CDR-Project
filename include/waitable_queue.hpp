#ifndef WAITABLE_QUEUE_H
#define WAITABLE_QUEUE_H

#include <queue> //queue

#include "common.hpp"
#include "enriched_exeptions.hpp" // EnrichedExeption
#include "locks.hpp" //mutexs
#include "condVar.hpp" //CondVar

namespace advcpp
{

class WaitableQueueException: public EnrichedExeption {
public:
    explicit WaitableQueueException (InfoException a_info, const char* a_msg = "Vc Failed")
    : EnrichedExeption(a_msg, a_info) 
    {};
};

template <typename T>
class PredicateEmpty;
template <typename T>
class PredicateFull;

template <typename T>
class WaitableQueue: public UnCopiable {
public:
    explicit WaitableQueue(size_t a_capapcity);
    
    //~WaitableQueue() = default;

    //WaitableQueue(const WaitableQueue<T>& a_rhs) = deleted;
    //WaitableQueue& operator = (const WaitableQueue<T> a_rhs)  = deleted;
    
    void Enqueue(T const& a_val);
    void Dequeue(T& a_result);

    template <typename U>
    friend class PredicateEmpty;
    template <typename U>
    friend class PredicateFull;
    bool IsEmpty() const;

private:
    bool isEmpty() const;
    bool isFull() const;
    
private:
    std::queue<T> m_que;
    mutable Mutex m_lock;
    CondVar m_conitionalVariable;
    size_t m_capacity;
};

template <typename T>
class PredicateEmpty {
public:
    PredicateEmpty(WaitableQueue<T> const& a_que);
    bool operator () () const;

private:
    WaitableQueue<T> const& m_que;
};

template <typename T>
class PredicateFull {
public:
    PredicateFull(WaitableQueue<T> const& a_que);
    bool operator () () const;

private:
    WaitableQueue<T>const & m_que;
};


} // namespace advcpp

#include "waitable_queue.inl"
#endif //WAITABLE_QUEUE_H