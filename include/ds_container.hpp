#ifndef DS_CONTAINER_HPP
#define DS_CONTAINER_HPP

#include <vector>

#include "i_record.hpp"


namespace advcpp 
{

template <typename Cont> 
class DsContainer {
public:
    explicit DsContainer(std::vector<Cont>& a_conts);

    //~DsContainer() = default;
    //DsContainer(const DsContainer<T>& a_rhs) = default;
    //DsContainer& operator = (const DsContainer<T> a_rhs) = default;

    void DsUpserter(IRecord* a_record);

private:
    std::vector<Cont>& m_conts; 
};

} //namespace advcpp 

#include "ds_container.inl"
#endif //DS_CONTAINER_HPP