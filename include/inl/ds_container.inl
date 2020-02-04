#ifndef DS_CONATAINER_INL
#define DS_CONATAINER_INL
#include "ds_container.hpp"

namespace advcpp{

inline OperatorRecord DsContainer::FindOperator(uint const& a_operator)
{
    OperatorRecord rec;
    m_operator.Find(a_operator, rec);
    return rec;
}

inline SubscriberRecord DsContainer::FindSubscriber(uint const& a_subscriber)
{
    SubscriberRecord rec;
    m_subscriber.Find(a_subscriber, rec);
    return rec;
}

} //namespace advcpp 
#endif //DS_CONATAINER_INL