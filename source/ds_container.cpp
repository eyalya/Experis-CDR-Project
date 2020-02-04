#include "ds_container.hpp"
#include "defs.hpp"

namespace advcpp 
{

DsContainer::DsContainer()
: m_subscriber(SUBSCRIBER_CAPACITY, Hasher<uint>())
, m_operator (OPERATOR_CAPACITY, Hasher<size_t>())
{
}

void DsContainer::DsUpsert(Record& a_record)
{
    SubscriberRecord subRecord(a_record);
    m_subscriber.Upsert(a_record.m_misdn, subRecord, UpdaterSubscriberRecord);
    
    OperatorRecord operatorRecord(a_record);
    m_operator.Upsert(a_record.m_brand, operatorRecord, UpdaterOperatorRecord);
}

void UpdaterSubscriberRecord(SubscriberRecord& a_current, SubscriberRecord const& a_newRecord)
{
    a_current += a_newRecord;
}

void UpdaterOperatorRecord(OperatorRecord& a_current, OperatorRecord const& a_newRecord)
{
    a_current += a_newRecord;
}



} //namespace advcpp 

