#ifndef QUERY_INL
#define QUERY_INL
#include "query.hpp"
#include "UI.hpp"

namespace advcpp{

inline Query::Query(DsContainer& a_container)
: m_container(a_container)
{  
}

inline bool Query::GetSubscriber(uint a_sub, SubscriberRecord& a_subRec)
{    
    return m_container.FindSubscriber(a_sub, a_subRec);    
}


// void Query::GetOperator(uint a_op, UI const& a_ui) const
// {
//     return m_container.FindOperator(a_op. a_opRec);
// }

inline void Query::GetAllSubscribers() const
{
    std::cout << "all subscribers chosen\n";
}

// void Query::GetAllOperators() const
// {
//     std::cout << "all operators chosen\n";
// }

} //namespace advcpp
#endif //QUERY_INL