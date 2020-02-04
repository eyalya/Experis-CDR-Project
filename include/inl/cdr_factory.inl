#include "cdr_factory.hpp"

namespace advcpp
{

template <typename Runnable>
CdrFactory<Runnable>::CdrFactory(std::vector<Runnable>& a_upsertors, bool& a_switch)
: Dispatcher<Runnable>(a_upsertors, a_switch)
{
}


} //namespace advcpp