#ifndef RECORD_H
#define RECORD_H
#include <cstdlib>
#include <iostream>

namespace advcpp
{

struct Record
{
    Record();
    // ~Record() = default
    // Record & Record(Record & const) = default
    // Record & operator= (Record & const) = default

    Record & operator+= (const Record & a_record);
    
    size_t m_brand;
    uint m_imsi;
    uint m_misdn;
    uint m_MCC;
    uint m_operator;
    size_t m_outVoiceInOp;
    size_t m_inVoiceInOp;
    size_t m_outVoiceOutOp;
    size_t m_inVoiceOutOp;
    size_t m_outSMSInOp;
    size_t m_inSMSInOp;
    size_t m_outSMSOutOp;
    size_t m_inSMSOutOp;
    size_t m_download;
    size_t m_upload;
};

struct SubscriberRecord
{
    SubscriberRecord();
    SubscriberRecord(const Record & a_record);
    // ~SubscriberRecord(); =default
    // SubscriberRecord & SubscriberRecord(const SubscriberRecord & a_rec); =default
    // SubscriberRecord & operator= (const SubscriberRecord & a_rec); =default
 
    SubscriberRecord & operator+= (const SubscriberRecord & a_record);
    
    uint m_imsi;
    uint m_misdn;
    size_t m_outVoiceInOp;
    size_t m_inVoiceInOp;
    size_t m_outVoiceOutOp;
    size_t m_inVoiceOutOp;
    size_t m_outSMSInOp;
    size_t m_inSMSInOp;
    size_t m_outSMSOutOp;
    size_t m_inSMSOutOp;
    size_t m_download;
    size_t m_upload;
};

struct OperatorRecord
{
    OperatorRecord();
    OperatorRecord(const Record & a_record);
    // ~OperatorRecord(); =default
    // OperatorRecord & OperatorRecord(const OperatorRecord & a_rec); =default
    // OperatorRecord & operator= (const OperatorRecord & a_rec); =default

    OperatorRecord & operator+= (const OperatorRecord & a_record);
    
    size_t m_brand;
    size_t m_outVoice;
    size_t m_inVoice;
    size_t m_inSMS;
    size_t m_outSMS;
};

std::ostream & operator << (std::ostream &out, const SubscriberRecord & a_record);

} // namespace 


#endif // RECORD_H