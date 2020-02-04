#include "record.hpp"

namespace advcpp
{

OperatorRecord::OperatorRecord()
: m_brand(0)
, m_outVoice(0)
, m_inVoice(0)
, m_inSMS(0)
, m_outSMS(0)
{
}

SubscriberRecord::SubscriberRecord()
: m_imsi(0)
, m_misdn(0)
, m_outVoiceInOp(0)
, m_inVoiceInOp(0)
, m_outVoiceOutOp(0)
, m_inVoiceOutOp(0)
, m_outSMSInOp(0)
, m_inSMSInOp(0)
, m_outSMSOutOp(0)
, m_inSMSOutOp(0)
, m_download(0)
, m_upload(0)
{
}

OperatorRecord::OperatorRecord(const Record & a_record)
: m_brand(a_record.m_brand)
, m_outVoice(a_record.m_outVoiceInOp)
, m_inVoice(a_record.m_inVoiceInOp)
, m_inSMS(a_record.m_inSMSInOp)
, m_outSMS(a_record.m_outSMSInOp)
{
}

SubscriberRecord::SubscriberRecord(const Record & a_record)
: m_imsi(a_record.m_imsi)
, m_misdn(a_record.m_misdn)
, m_outVoiceInOp(a_record.m_outVoiceInOp)
, m_inVoiceInOp(a_record.m_inVoiceInOp)
, m_outVoiceOutOp(a_record.m_outVoiceOutOp)
, m_inVoiceOutOp(a_record.m_inVoiceOutOp)
, m_outSMSInOp(a_record.m_outSMSInOp)
, m_inSMSInOp(a_record.m_inSMSInOp)
, m_outSMSOutOp(a_record.m_outSMSOutOp)
, m_inSMSOutOp(a_record.m_inSMSOutOp)
, m_download(a_record.m_download)
, m_upload(a_record.m_upload)
{
}


Record & Record::operator+= (const Record & a_record)
{
    m_operator += a_record.m_operator;
    m_MCC += a_record.m_MCC;
    m_imsi += a_record.m_imsi;
    m_outVoiceInOp += a_record.m_outVoiceInOp;
    m_inVoiceInOp += a_record.m_inVoiceInOp;
    m_outVoiceOutOp += a_record.m_outVoiceOutOp;
    m_inVoiceOutOp += a_record.m_inVoiceOutOp;
    m_outSMSInOp += a_record.m_outSMSInOp;
    m_inSMSInOp += a_record.m_inSMSInOp;
    m_outSMSOutOp += a_record.m_outSMSOutOp;
    m_inSMSOutOp += a_record.m_inSMSOutOp;
    m_download += a_record.m_download;
    m_upload += a_record.m_upload;

    return *this;
}

SubscriberRecord & SubscriberRecord::operator+= (const SubscriberRecord & a_record)
{
    m_outVoiceInOp += a_record.m_outVoiceInOp;
    m_inVoiceInOp += a_record.m_inVoiceInOp;
    m_outVoiceOutOp += a_record.m_outVoiceOutOp;
    m_inVoiceOutOp += a_record.m_inVoiceOutOp;
    m_outSMSInOp += a_record.m_outSMSInOp;
    m_inSMSInOp += a_record.m_inSMSInOp;
    m_outSMSOutOp += a_record.m_outSMSOutOp;
    m_inSMSOutOp += a_record.m_inSMSOutOp;
    m_download += a_record.m_download;
    m_upload += a_record.m_upload;

    return *this;
}

OperatorRecord & OperatorRecord::operator+= (const OperatorRecord & a_record)
{
    m_outVoice += a_record.m_outVoice;
    m_outVoice += a_record.m_outVoice;
    m_inVoice += a_record.m_inVoice;
    m_inVoice += a_record.m_inVoice;
    m_inSMS += a_record.m_inSMS;
    m_inSMS += a_record.m_inSMS;
    m_outSMS += a_record.m_outSMS;
    m_outSMS += a_record.m_outSMS;

    return *this;
}

std::ostream & operator << (std::ostream &out, const SubscriberRecord & a_record)
{
    out << "subscriber: " << a_record.m_imsi << '\n';
    
    out << "misdn: " << a_record.m_misdn << '\n';
    out << "out voice calls inside operator: " << a_record.m_outVoiceInOp << '\n';
    out << "in voice calls inside operator: " << a_record.m_inVoiceInOp << '\n';
    out << "out voice calls outside operator: " << a_record.m_outVoiceOutOp << '\n';
    out << "out voice calls inside operator: " << a_record.m_inVoiceOutOp << '\n';
    out << "out sms inside operator: " << a_record.m_outSMSInOp << '\n';
    out << "in sms inside operator: " << a_record.m_inSMSInOp << '\n';
    out << "out sms outside operator: " << a_record.m_outSMSOutOp << '\n';
    out << "in sms outside operator: " << a_record.m_inSMSOutOp << '\n';
    out << "megabytes downloaded: " << a_record.m_download << '\n';
    out << "megabytes uploaded: " << a_record.m_upload;

    return out;
}

} // namespace advcpp
