#include "ds_container.hpp"
#include "defs.hpp"
#include <iostream>

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
    std::cout << subRecord << "\n";
    
    OperatorRecord operatorRecord(a_record);
    std::cout << operatorRecord << "\n\n";
    m_operator.Upsert(a_record.m_MCC, operatorRecord, UpdaterOperatorRecord);
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

