#ifndef DS_CONATAINER_INL
#define DS_CONATAINER_INL

#include "ds_container.hpp"
#include "defs.hpp"

namespace advcpp 
{

DsContainer::DsContainer()
: m_subscriber(SUBSCRIBER_CAPACITY, DefaultHasher<uint>())
, m_operator (OPERATOR_CAPACITY, DefaultHasher<size_t>())
{
}

void DsContainer::DsUpserter(Record& a_record)
{
    SubscriberRecord subRecord(a_record);
    m_subscriber.Upsert(a_record.m_misdn, subRecord, UpdaterSubscriber);
    OperatorRecord operatorRecord(a_record);
    m_operator.Upsert(a_record.m_brand, operatorRecord, UpdaterOperator);
}

// void DsContainer::Updater(IRecord& a_lhs, Record const& a_rhs)
// {
//     a_lhs += a_rhs;
// }

void DsContainer::UpdaterSubscriber(SubscriberRecord& a_lhs, Record const& a_rhs)
{
    a_lhs += a_rhs;
}

void DsContainer::UpdaterOperator(OperatorRecord& a_lhs, Record const& a_rhs)
{
    a_lhs += a_rhs;
}

} //namespace advcpp 
#endif //DS_CONATAINER_INL



// In file included from ../../include/hash_table_safe.hpp:94:0,
//                  from ../../include/ds_container.hpp:7,
//                  from ../../source/ds_container.cpp:4:
// ../../include/inl/hash_table_safe.inl: In instantiation of 
// ‘bool advcpp::HashTableSafe<Key, Value, HashFunc>::Upsert(const Key&, const Value&, Update)
// [with Update = void (*)(advcpp::SubscriberRecord&, const advcpp::Record&); Key = unsigned int; Value = advcpp::SubscriberRecord; HashFunc = advcpp::DefaultHasher<unsigned int>]’:

// ../../source/ds_container.cpp:18:88:   required from here
// ../../include/inl/hash_table_safe.inl:107:21: 
// error: invalid initialization of reference of type ‘const advcpp::Record&’ from expression of type ‘const advcpp::SubscriberRecord’
//              a_update(found->second, a_value);
