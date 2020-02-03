#include "reducer.hpp"

namespace advcpp
{

void Reducer::Reduce(Record & a_record)
{
   
    a_record.m_imsi = m_moc.m_cdr.m_imsi;
    a_record.m_MCC  = m_moc.m_cdr.m_mcc;
    a_record.m_operator = m_moc.m_cdr.m_operator.m_value;
    a_record.m_inVoiceInOp = 0;
    a_record.m_inVoiceOutOp = 0;
    a_record.m_outSMSInOp = 0;
    a_record.m_inSMSInOp = 0;
    a_record.m_outSMSOutOp = 0;
    a_record.m_inSMSOutOp = 0;
    a_record.m_download = 0;
    a_record.m_upload = 0;
    
    if(m_moc.m_cdr.m_operator.m_value == m_moc.m_paryData.m_paryOperator.m_value)
    {
        a_record.m_outVoiceInOp = m_moc.m_duration;
        a_record.m_outVoiceOutOp = 0;
    }
    else
    {
        a_record.m_outVoiceOutOp = m_moc.m_duration;
        a_record.m_outVoiceInOp = 0;
    }
    
}

} // namespace advcpp
