#include "record.hpp"

namespace advcpp
{

void Record::operator+= (const Record & a_record)
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
}

void SubscriberRecord::operator+= (const Record & a_record)
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
}

void OperatorRecord::operator+= (const Record & a_record)
{
    m_outVoice += a_record.m_outVoiceInOp;
    m_outVoice += a_record.m_outVoiceOutOp;
    m_inVoice += a_record.m_inVoiceInOp;
    m_inVoice += a_record.m_inVoiceOutOp;
    m_inSMS += a_record.m_inSMSInOp;
    m_inSMS += a_record.m_inSMSOutOp;
    m_outSMS += a_record.m_outSMSInOp;
    m_outSMS += a_record.m_outSMSOutOp;
}

} // namespace advcpp
