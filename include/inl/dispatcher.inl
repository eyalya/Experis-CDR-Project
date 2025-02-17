#include "dispatcher.hpp"
#include "thread_utils.hpp" //JoinAll

namespace advcpp
{

template <typename Runnable>
Dispatcher<Runnable>::Dispatcher(std::vector<Runnable>& a_receivers, bool& a_switch)
: m_receivers(a_receivers)
, m_switch(a_switch)
{
}

template <typename Runnable>
void Dispatcher<Runnable>::WorkersInit()
{
    const size_t size = m_receivers.size();
    m_workers.reserve(size);

    try
    {
        for (size_t i = 0; i < size; ++i)
        {
            m_workers.push_back(new Thread (m_receivers[i]));
        }   
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
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
        FailierHandler(m_workers);
        //log
        throw;
    }
}

template <typename Runnable>
void Dispatcher<Runnable>::ShutDown()
{
    m_switch = false;
    JoinAll(m_workers);
}

} // namespace advcpp