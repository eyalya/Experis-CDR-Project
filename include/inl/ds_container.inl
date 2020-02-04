#ifndef DS_CONATAINER_INL
#define DS_CONATAINER_INL
#include "ds_container.hpp"

namespace advcpp{


inline bool DsContainer::FindOperator(uint a_operator, OperatorRecord& a_op) const
{    
    return m_operator.Find(a_operator, a_op);
}

inline bool DsContainer::FindSubscriber(uint a_subscriber, SubscriberRecord& a_sub) const
{    
    return m_subscriber.Find(a_subscriber, a_sub);  
}

} //namespace advcpp 
#endif //DS_CONATAINER_INL