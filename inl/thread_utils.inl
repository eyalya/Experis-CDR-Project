#ifndef THREAD_UTILS_INL
#define THREAD_UTILS_INL

#include "thread_utils.hpp"

namespace advcpp
{

inline void JoinAll (std::vector<Thread*> a_threads)
{
    const size_t size = a_threads.size();
    for (size_t i = 0; i < size; ++i)
    {
        a_threads[i]->Join();
    }
}

} //namespace advcpp

#endif //THREAD_UTILS_INL