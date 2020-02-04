#ifndef DS_CONATAINER_INL
#define DS_CONATAINER_INL

#include "ds_container.hpp"

namespace advcpp 
{

template <typename Cont>
DsContainer<Cont>::DsContainer()
: m_subscriber(SUBSCRIBER_CAPACITY, DefaultHasher<uint>())
, m_operator (OPERATOR_CAPACITY, DefaultHasher<size_t>())
{
}

template <typename Cont>
void DsContainer<Cont>::DsUpserter(Record& a_record)
{
    m_subscriber.Upsert(a_record.m_misdn, SubscriberRecord(a_record), Updater);
    m_operator.Upsert(a_record.brand, OperatorRecord(a_record), Updater);
}

template <typename Cont>
void DsContainer<Cont>::Updater(IRecord& a_lhs, Record const& a_rhs)
{
    a_lhs += a_rhs;
}

} //namespace advcpp 
#endif //DS_CONATAINER_INL