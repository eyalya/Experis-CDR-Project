#ifndef DISPATCHER_HPP
#define DISPATCHER_HPP

#include <vector>

#include "thread.hpp"
#include "socket.hpp"
#include "irecievers.hpp"

namespace advcpp 
{

template <typename Runnable>
class Dispatcher {
public:
    explicit Dispatcher(std::vector<Runnable>& a_runnable);

    //~Dispatcher() = default;
    //Dispatcher(const Dispatcher<T>& a_rhs) = default;
    //Dispatcher& operator = (const Dispatcher<T> a_rhs) = default;

    void ActivateWorkers();

private:
    void WorkersInit();

private:
    std::vector<Runnable>& m_runnable; 
    std::vector<Thread*> m_workers;
};

} //namespace advcpp 
#include "dispatcher.inl"
#endif //DISPATCHER_HPP