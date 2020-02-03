#ifndef RECORD_H
#define RECORD_H
#include "i_record.hpp"
#include <cstdlib>

namespace advcpp
{

struct Record : public IRecord
{
    virtual ~Record();
    void operator+= (const Record & a_record);
    
    uint m_imsi;
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

struct SubscriberRecord : public IRecord
{
    virtual ~SubscriberRecord();
    void operator+= (const Record & a_record);
    
    uint m_imsi;
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

struct OperatorRecord : public IRecord
{
    virtual ~OperatorRecord();
    void operator+= (const Record & a_record);
    
    size_t m_brand;
    size_t m_outVoice;
    size_t m_inVoice;
    size_t m_inSMS;
    size_t m_outSMS;
};

inline OperatorRecord::~OperatorRecord()
{
}

inline SubscriberRecord::~SubscriberRecord()
{
}

inline Record::~Record()
{
}

} // namespace 


#endif // RECORD_H