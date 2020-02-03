#ifndef DS_CONATAINER_INL
#define DS_CONATAINER_INL

#include "ds_container.hpp"

namespace advcpp 
{

template <typename Cont>
DsContainer<Cont>::DsContainer(std::vector<Cont>& a_conts)
: m_conts(a_conts)
{
}

template <typename Cont>
void DsContainer<Cont>::DsUpserter(IRecord* a_record)
{
    const size_t size = m_conts.size();

    for (size_t i = 0; i < size; ++i)
    {
        m_conts[i].Upsert(a_record);
    }
}

} //namespace advcpp 
#endif //DS_CONATAINER_INL