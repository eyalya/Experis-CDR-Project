#include "record.hpp"

namespace advcpp
{

Record::Record()
: m_brand(0)
, m_imsi(0)
, m_misdn(0)
, m_MCC(0)
, m_operator(0)
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
: m_brand(a_record.m_MCC)
, m_outVoice(a_record.m_outVoiceOutOp + a_record.m_outVoiceInOp)
, m_inVoice(a_record.m_inVoiceInOp + a_record.m_inVoiceOutOp)
, m_inSMS(a_record.m_inSMSInOp + a_record.m_inSMSOutOp)
, m_outSMS(a_record.m_outSMSInOp + a_record.m_outSMSOutOp)
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
    m_inVoice += a_record.m_inVoice;
    m_inSMS += a_record.m_inSMS;
    m_outSMS += a_record.m_outSMS;

    return *this;
}

std::ostream & operator << (std::ostream &out, const SubscriberRecord & a_record)
{
    out << "\033[1;95m" << "subscriber: "                       << "\033[0m" << "\033[1;33m" << a_record.m_imsi          << "\033[0m" << '\n';
    out << "\033[1;95m" << "misdn: "                            << "\033[0m" << "\033[1;33m" << a_record.m_misdn         << "\033[0m" << '\n';
    out << "\033[1;95m" << "out voice calls inside operator: "  << "\033[0m" << "\033[1;33m" << a_record.m_outVoiceInOp  << "\033[0m" << '\n';
    out << "\033[1;95m" << "in voice calls inside operator: "   << "\033[0m" << "\033[1;33m" << a_record.m_inVoiceInOp   << "\033[0m" << '\n';
    out << "\033[1;95m" << "out voice calls outside operator: " << "\033[0m" << "\033[1;33m" << a_record.m_outVoiceOutOp << "\033[0m" << '\n';
    out << "\033[1;95m" << "out voice calls inside operator: "  << "\033[0m" << "\033[1;33m" << a_record.m_inVoiceOutOp  << "\033[0m" << '\n';
    out << "\033[1;95m" << "out sms inside operator: "          << "\033[0m" << "\033[1;33m" << a_record.m_outSMSInOp    << "\033[0m" << '\n';
    out << "\033[1;95m" << "in sms inside operator: "           << "\033[0m" << "\033[1;33m" << a_record.m_inSMSInOp     << "\033[0m" << '\n';
    out << "\033[1;95m" << "out sms outside operator: "         << "\033[0m" << "\033[1;33m" << a_record.m_outSMSOutOp   << "\033[0m" << '\n';
    out << "\033[1;95m" << "in sms outside operator: "          << "\033[0m" << "\033[1;33m" << a_record.m_inSMSOutOp    << "\033[0m" << '\n';
    out << "\033[1;95m" << "megabytes downloaded: "             << "\033[0m" << "\033[1;33m" << a_record.m_download      << "\033[0m" << '\n';
    out << "\033[1;95m" << "megabytes uploaded: "               << "\033[0m" << "\033[1;33m" << a_record.m_upload        << "\033[0m" << '\n';

// \033[1;33m\nThank you, come again!\n\033[0m\n
    return out;
}

std::ostream & operator << (std::ostream &out, const OperatorRecord & a_record)
{
    out << "\033[1;95m" << "operator: "                         << "\033[0m" << "\033[1;33m" << a_record.m_brand    << "\033[0m" << '\n';
    out << "\033[1;95m" << "out voice calls: "                  << "\033[0m" << "\033[1;33m" << a_record.m_outVoice << "\033[0m" << '\n';
    out << "\033[1;95m" << "in voice calls: "                   << "\033[0m" << "\033[1;33m" << a_record.m_inVoice  << "\033[0m" << '\n';
    out << "\033[1;95m" << "out sms: "                          << "\033[0m" << "\033[1;33m" << a_record.m_outSMS   << "\033[0m" << '\n';
    out << "\033[1;95m" << "in sms : "                          << "\033[0m" << "\033[1;33m" << a_record.m_inSMS    << "\033[0m" << '\n';

    return out;
}

} // namespace advcpp
