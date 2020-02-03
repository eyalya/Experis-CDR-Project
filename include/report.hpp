#ifndef REPORT_H
#define REPORT_H
#include "ireport.hpp"
#include <cstdlib>

namespace advcpp
{

struct Report : public IReport
{
    virtual ~Report();
    void operator+= (const Report & a_report);
    
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

struct SubscriberReport : public IReport
{
    virtual ~SubscriberReport();
    void operator+= (const Report & a_report);
    
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

struct OperatorReport : public IReport
{
    virtual ~OperatorReport();
    void operator+= (const Report & a_report);
    
    size_t m_brand;
    size_t m_outVoice;
    size_t m_inVoice;
    size_t m_inSMS;
    size_t m_outSMS;
};

inline OperatorReport::~OperatorReport()
{
}

inline SubscriberReport::~SubscriberReport()
{
}

inline Report::~Report()
{
}

} // namespace 


#endif // REPORT_H