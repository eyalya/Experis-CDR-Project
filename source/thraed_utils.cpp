#include "thread_utils.hpp"

namespace advcpp
{

void KillThreads (std::vector<Thread*> a_threads)
{
    const size_t size = a_threads.size();
    for (size_t i = 0; i < size; ++i)
    {
        a_threads[i]->Kill();
    }
}

void JoinAll (std::vector<Thread*> a_threads)
{
    const size_t size = a_threads.size();
    for (size_t i = 0; i < size; ++i)
    {
        a_threads[i]->Join();
    }
}

} //namespace advcpp
