#ifndef THREAD_UTILS_HPP
#define THREAD_UTILS_HPP

#include <vector>

#include "thread.hpp"

namespace advcpp
{

void JoinAll (std::vector<Thread*> a_threads);

} // namespace advcpp

#include "inl/thread_utils.inl"
#endif //THREAD_UTILS
