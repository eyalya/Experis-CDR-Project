#ifndef QUARY_HPP
#define QUARY_HPP
#include <iostream>
#include "ds_container.hpp"

namespace advcpp{

class Quary
{
public:
    //Quary() = default;
    //rule 3 = default;

    SubscriberRecord GetSubscriber(uint a_sub) const;
    OperatorRecord GetOperator(uint a_sub) const;
    void GetAllSubscribers() const;
    void GetAllOperators() const;

private:
    DsContainer& m_container;
};

//////////////////////////////////////////////////////////////////////////////////

inline SubscriberRecord Quary::GetSubscriber(uint a_sub) const
{
    return m_container.FindSubscriber(a_sub);
}

inline OperatorRecord Quary::GetOperator(uint a_op) const
{
    return m_container.FindOperator(a_op);
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