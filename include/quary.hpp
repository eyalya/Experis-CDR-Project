#ifndef QUARY_HPP
#define QUARY_HPP
#include <iostream>
#include "ds_container.hpp"

namespace advcpp{

class Quary
{
public:
    Quary(DsContainer& a_container);
    //rule 3 = default;

    bool GetSubscriber(uint a_sub, SubscriberRecord& a_subRec) const;
    bool GetOperator(uint a_op, OperatorRecord& a_opRec) const;
    void GetAllSubscribers() const;
    void GetAllOperators() const;

private:
    DsContainer& m_container;
};

//////////////////////////////////////////////////////////////////////////////////

inline Quary::Quary(DsContainer& a_container)
: m_container(a_container)
{  
}

inline bool Quary::GetSubscriber(uint a_sub, SubscriberRecord& a_subRec) const
{
    m_container.FindSubscriber(a_sub, a_subRec);
    return 
}
//TODO: continue from here
//FIXME:

inline bool Quary::GetOperator(uint a_op, OperatorRecord& a_opRec) const
{
    return m_container.FindOperator(a_op. a_opRec);
}

inline void Quary::GetAllSubscribers() const
{
    std::cout << "all subscribers chosen\n";
}

inline void Quary::GetAllOperators() const
{
    std::cout << "all operators chosen\n";
}


}//namespace advcpp
#endif //QUARY_HPP