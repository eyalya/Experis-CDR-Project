#include "reducer.hpp"

namespace advcpp
{

void Reducer::Reduce(Report & a_report)
{
   
   (void)a_report;
    a_report.m_imsi = m_moc.m_cdr.m_imsi;
    a_report.m_MCC  = m_moc.m_cdr.m_mcc;
    a_report.m_operator = m_moc.m_cdr.m_operator.m_value;
    a_report.m_inVoiceInOp = 0;
    a_report.m_inVoiceOutOp = 0;
    a_report.m_outSMSInOp = 0;
    a_report.m_inSMSInOp = 0;
    a_report.m_outSMSOutOp = 0;
    a_report.m_inSMSOutOp = 0;
    a_report.m_download = 0;
    a_report.m_upload = 0;
    
    if(m_moc.m_cdr.m_operator.m_value == m_moc.m_paryData.m_paryOperator.m_value)
    {
        a_report.m_outVoiceInOp = m_moc.m_duration;
        a_report.m_outVoiceOutOp = 0;
    }
    else
    {
        a_report.m_outVoiceOutOp = m_moc.m_duration;
        a_report.m_outVoiceInOp = 0;
    }
    
}

} // namespace advcpp
