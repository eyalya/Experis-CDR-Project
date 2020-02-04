#include "reducer.hpp"

namespace advcpp
{

void Reducer::Reduce(const protocol::Message & a_message, Record & a_record)
{
   m_reducers[a_message.m_type] -> Reduce(a_message, a_record);
}

void MCOReducing::Reduce(const protocol::Message & a_message, Record & a_record)
{
    a_record.m_imsi = a_message.m_cdr.m_imsi;
    a_record.m_MCC  = a_message.m_cdr.m_mcc;
    a_record.m_operator = a_message.m_cdr.m_operator.m_value;
    a_record.m_inVoiceInOp = 0;
    a_record.m_inVoiceOutOp = 0;
    a_record.m_outSMSInOp = 0;
    a_record.m_inSMSInOp = 0;
    a_record.m_outSMSOutOp = 0;
    a_record.m_inSMSOutOp = 0;
    a_record.m_download = 0;
    a_record.m_upload = 0;
    
    if(a_message.m_cdr.m_operator.m_value == a_message.m_paryData.m_paryOperator.m_value)
    {
        a_record.m_outVoiceInOp = a_message.m_duration;
        a_record.m_outVoiceOutOp = 0;
    }
    else
    {
        a_record.m_outVoiceOutOp = a_message.m_duration;
        a_record.m_outVoiceInOp = 0;
    }
}

void MTCReducing::Reduce(const protocol::Message & a_message, Record & a_record)
{
    a_record.m_imsi = a_message.m_cdr.m_imsi;
    a_record.m_MCC  = a_message.m_cdr.m_mcc;
    a_record.m_operator = a_message.m_cdr.m_operator.m_value;
    a_record.m_inVoiceInOp = 0;
    a_record.m_inVoiceOutOp = 0;
    a_record.m_outSMSInOp = 0;
    a_record.m_inSMSInOp = 0;
    a_record.m_outSMSOutOp = 0;
    a_record.m_inSMSOutOp = 0;
    a_record.m_download = 0;
    a_record.m_upload = 0;
    
    if(a_message.m_cdr.m_operator.m_value == a_message.m_paryData.m_paryOperator.m_value)
    {
        a_record.m_outVoiceInOp = a_message.m_duration;
        a_record.m_outVoiceOutOp = 0;
    }
    else
    {
        a_record.m_outVoiceOutOp = a_message.m_duration;
        a_record.m_outVoiceInOp = 0;
    }
}   

} // namespace advcpp
