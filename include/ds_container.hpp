#ifndef DS_CONTAINER_HPP
#define DS_CONTAINER_HPP

#include <vector>

#include "record.hpp"
#include "hash_table_safe.hpp"
#include "hash_funcs.hpp"
#include "protocol.hpp"

namespace advcpp 
{

class DsContainer {
public:
    explicit DsContainer();

    //~DsContainer() = default;
    //DsContainer(const DsContainer<T>& a_rhs) = default;
    //DsContainer& operator = (const DsContainer<T> a_rhs) = default;

    void DsUpsert(Record& a_record);
    
    bool FindOperator(uint a_operator, OperatorRecord& a_op) const;
    bool FindSubscriber(uint a_subscriber, SubscriberRecord& a_rec) const;

private:
    HashTableSafe<uint, SubscriberRecord, DefaultHasher<uint> > m_subscriber;
    HashTableSafe<uint, OperatorRecord, DefaultHasher<size_t> > m_operator;
};

void UpdaterSubscriberRecord(SubscriberRecord& a_current, SubscriberRecord const& a_newRecord);
void UpdaterOperatorRecord(OperatorRecord& a_current, OperatorRecord const& a_newRecord);

} //namespace advcpp 

#include "inl/ds_container.inl"

#endif //DS_CONTAINER_HPP