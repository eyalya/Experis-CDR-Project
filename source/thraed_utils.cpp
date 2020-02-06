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

void FailierHandler(std::vector<Thread*> a_threads)
{
    const size_t size = a_threads.size();

    try 
    {
        KillThreads(a_threads);
    }
    catch (const ThreadException& except)
    {
        //log except.what()
    }

    for (size_t i = 0; i < size; ++i)
    {
        delete a_threads[i];
    }
}

} //namespace advcpp
