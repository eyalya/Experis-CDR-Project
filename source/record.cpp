#include "report.hpp"

namespace advcpp
{

void SubscriberReport::operator+= (const Report & a_report)
{
    m_imsi += a_report.m_imsi;
    m_outVoiceInOp += a_report.m_outVoiceInOp;
    m_inVoiceInOp += a_report.m_inVoiceInOp;
    m_outVoiceOutOp += a_report.m_outVoiceOutOp;
    m_inVoiceOutOp += a_report.m_inVoiceOutOp;
    m_outSMSInOp += a_report.m_outSMSInOp;
    m_inSMSInOp += a_report.m_inSMSInOp;
    m_outSMSOutOp += a_report.m_outSMSOutOp;
    m_inSMSOutOp += a_report.m_inSMSOutOp;
    m_download += a_report.m_download;
    m_upload += a_report.m_upload;
}

void OperatorReport::operator+= (const Report & a_report)
{
    m_brand += a_report.m_operator;
    m_outVoice += a_report.m_outVoiceInOp;
    m_outVoice += a_report.m_outVoiceOutOp;
    m_inVoice += a_report.m_inVoiceInOp;
    m_inVoice += a_report.m_inVoiceOutOp;
    m_inSMS += a_report.m_inSMSInOp;
    m_inSMS += a_report.m_inSMSOutOp;
    m_outSMS += a_report.m_outSMSInOp;
    m_outSMS += a_report.m_outSMSOutOp;
}

} // namespace advcpp
