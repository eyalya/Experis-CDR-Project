#ifndef DS_CONTAINER_HPP
#define DS_CONTAINER_HPP

#include <vector>

#include "record.hpp"
#include "hash_table_safe.hpp"
#include "hash_funcs.hpp"

namespace advcpp 
{

class DsContainer {
public:
    explicit DsContainer();

    //~DsContainer() = default;
    //DsContainer(const DsContainer<T>& a_rhs) = default;
    //DsContainer& operator = (const DsContainer<T> a_rhs) = default;

    void DsUpserter(Record& a_record);

private:
    HashTableSafe<uint, SubscriberRecord, DefaultHasher<uint> > m_subscriber;
    HashTableSafe<uint, OperatorRecord, DefaultHasher<size_t> > m_operator;
};

void UpdaterSubscriberRecord(SubscriberRecord& a_current, SubscriberRecord const& a_newRecord);
void UpdaterOperatorRecord(OperatorRecord& a_current, OperatorRecord const& a_newRecord);

} //namespace advcpp 

#include "ds_container.inl"
#endif //DS_CONTAINER_HPP