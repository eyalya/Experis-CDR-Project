#ifndef QUERY_HPP
#define QUERY_HPP
#include <iostream>
#include "ds_container.hpp"

namespace advcpp{

class Query
{
public:
    Query(DsContainer& a_container);
    //rule 3 = default;

    bool GetSubscriber (uint a_sub, SubscriberRecord& a_subRec);
    bool GetOperator (uint a_sub, OperatorRecord& a_opRec);
    //void GetAllSubscribers() const;
    // void GetAllOperators() const;
    
private:
    DsContainer& m_container;
};

}//namespace advcpp
#include "inl/query.inl"
#endif //QUERY_HPP