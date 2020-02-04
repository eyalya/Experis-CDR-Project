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

    void GetSubscriber();
    void GetOperator();
    void GetAllSubscribers();
    void GetAllOperators();

private:
    DsContainer const& m_container;
};

//////////////////////////////////////////////////////////////////////////////////

void Quary::GetSubscriber()
{
    m_container.
}

void Quary::GetOperator()
{
    std::cout << "operator chosen\n";
}

void Quary::GetAllSubscribers()
{
    std::cout << "all subscribers chosen\n";
}

void Quary::GetAllOperators()
{
    std::cout << "all operators chosen\n";
}


}//namespace advcpp
#endif //QUARY_HPP