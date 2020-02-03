#include "cdr_factory.hpp"

namespace advcpp
{

template <typename Runnable>
CdrFactory::CdrFactory(std::vector<Runnable>& a_cdrMakers)
: Dispatcher(a_cdrMakers)
{
}


} //namespace advcpp