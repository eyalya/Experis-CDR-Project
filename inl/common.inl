#include "common.hpp"

namespace advcpp
{

UnCopiable::UnCopiable(UnCopiable const& a_rhs)
{
    (void) a_rhs;
}
UnCopiable& UnCopiable::operator = (UnCopiable const& a_rhs)
{
    (void) a_rhs;
    return *this;
}

} //namespace advcpp