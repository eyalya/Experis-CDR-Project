#include "cdr_factory.hpp"

namespace advcpp
{

template <typename Runnable>
CdrFactory<Runnable>::CdrFactory(std::vector<Runnable>& a_upsertors)
: Dispatcher(a_cdrMakers)
{
}


} //namespace advcpp