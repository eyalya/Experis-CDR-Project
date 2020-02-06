#ifndef THREAD_UTILS_HPP
#define THREAD_UTILS_HPP

#include <vector>

#include "thread.hpp"

namespace advcpp
{

void KillThreads (std::vector<Thread*> a_threads);

void JoinAll (std::vector<Thread*> a_threads);

void FailierHandler(std::vector<Thread*> a_threads);

} // namespace advcpp

#endif //THREAD_UTILS
