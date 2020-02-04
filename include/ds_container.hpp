#ifndef DS_CONTAINER_HPP
#define DS_CONTAINER_HPP

#include <vector>

#include "record.hpp"
#include "hash_table_safe.hpp"
#include "hash_funcs.hpp"

namespace advcpp 
{

template <typename Cont> 
class DsContainer {
public:
    explicit DsContainer();

    //~DsContainer() = default;
    //DsContainer(const DsContainer<T>& a_rhs) = default;
    //DsContainer& operator = (const DsContainer<T> a_rhs) = default;

    void DsUpserter(Record& a_record);
private:
    void Updater(IRecord& a_lhs, Record const& a_rhs);

private:
    HashTableSafe<uint, SubscriberRecord, DefaultHasher<uint> > m_subscriber;
    HashTableSafe<uint, OperatorRecord, DefaultHasher<size_t> > m_operator;
};


} //namespace advcpp 

#include "ds_container.inl"
#endif //DS_CONTAINER_HPP