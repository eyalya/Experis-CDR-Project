#ifndef DS_CONATAINER_INL
#define DS_CONATAINER_INL
#include "ds_container.hpp"

namespace advcpp{


inline bool DsContainer::FindOperator(uint a_operator, OperatorRecord& a_opRec) 
{    
    return m_operator.Find(a_operator, a_opRec);
}

inline bool DsContainer::FindSubscriber(uint a_subscriber, SubscriberRecord& a_subRec) 
{    
    return m_subscriber.Find(a_subscriber, a_subRec);  
}

} //namespace advcpp

#endif //DS_CONATAINER_INL