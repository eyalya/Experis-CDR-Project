#include "dispatcher.hpp"
#include "thread_utils.hpp" //JoinAll

namespace advcpp
{

template <typename Runnable>
Dispatcher<Runnable>::Dispatcher(std::vector<Runnable>& a_receivers)
: m_receivers(a_receivers)
{
}

template <typename Runnable>
void Dispatcher<Runnable>::WorkersInit()
{
    const size_t size = m_receivers.size();
    m_workers.reserve(size);

    for (size_t i = 0; i < size; ++i)
    {
        m_workers.push_back(new Thread (m_receivers[i]));
    }
}

template <typename Runnable>
void Dispatcher<Runnable>::ActivateWorkers()
{
    try 
    {
        WorkersInit();
    }
    catch(...)
    {
        const size_t size = m_workers.size();
        
        for (size_t i = 0; i < size; ++i)
        {
            delete m_workers[i];
        }
        throw;
    }
    JoinAll(m_workers);
}

} // namespace advcpp