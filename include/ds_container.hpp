#ifndef DS_CONTAINER_HPP
#define DS_CONTAINER_HPP

#include <vector>

#include "record.hpp"
#include "hash_table_safe.hpp"
#include "protocol.hpp"

namespace advcpp 
{

class DsContainer {
public:
    explicit DsContainer();

    //~DsContainer() = default;
    //DsContainer(const DsContainer<T>& a_rhs) = default;
    //DsContainer& operator = (const DsContainer<T> a_rhs) = default;

    void DsUpserter(Record& a_record);
    
    OperatorRecord FindOperator(uint const& a_operator);
    SubscriberRecord FindSubscriber(uint const& a_subscriber);

private:
    HashTableSafe<uint, SubscriberRecord, Hasher<uint> > m_subscriber;
    HashTableSafe<uint, OperatorRecord, Hasher<size_t> > m_operator;
};

void UpdaterSubscriberRecord(SubscriberRecord& a_current, SubscriberRecord const& a_newRecord);
void UpdaterOperatorRecord(OperatorRecord& a_current, OperatorRecord const& a_newRecord);

} //namespace advcpp 

#include "ds_container.inl"
#endif //DS_CONTAINER_HPP