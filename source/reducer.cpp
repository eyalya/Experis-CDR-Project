#include "reducer.hpp"

namespace advcpp
{

void Reducer::Reduce(const protocol::Message & a_message, Record & a_record)
{
    // FIXME: fix decoder
//    m_reducers[a_message.m_type] -> Reduce(a_message, a_record);
    m_reducers[1] -> Reduce(a_message, a_record);
}

void MCOReducing::Reduce(const protocol::Message & a_message, Record & a_record)
{
    a_record.m_imsi = a_message.m_cdr.m_imsi;
    a_record.m_misdn = a_message.m_cdr.m_msisdn;
    a_record.m_MCC  = a_message.m_cdr.m_mcc;
    a_record.m_operator = a_message.m_cdr.m_operator.m_value;
    
    if(a_message.m_cdr.m_operator.m_value == a_message.m_paryData.m_paryOperator.m_value)
    {
        a_record.m_outVoiceInOp = a_message.m_duration;
    }
    else
    {
        a_record.m_outVoiceOutOp = a_message.m_duration;
    }
}

void MTCReducing::Reduce(const protocol::Message & a_message, Record & a_record)
{
    a_record.m_imsi = a_message.m_cdr.m_imsi;
    a_record.m_misdn = a_message.m_cdr.m_msisdn;
    a_record.m_MCC  = a_message.m_cdr.m_mcc;
    a_record.m_operator = a_message.m_cdr.m_operator.m_value;
    
    if(a_message.m_cdr.m_operator.m_value == a_message.m_paryData.m_paryOperator.m_value)
    {
        a_record.m_inVoiceInOp = a_message.m_duration;
    }
    else
    {
        a_record.m_outVoiceOutOp = a_message.m_duration;
    }
}   

void SMSOReducing::Reduce(const protocol::Message & a_message, Record & a_record)
{
    a_record.m_imsi = a_message.m_cdr.m_imsi;
    a_record.m_misdn = a_message.m_cdr.m_msisdn;
    a_record.m_MCC  = a_message.m_cdr.m_mcc;
    a_record.m_operator = a_message.m_cdr.m_operator.m_value;

    if(a_message.m_cdr.m_operator.m_value == a_message.m_paryData.m_paryOperator.m_value)
    {
        a_record.m_outSMSInOp = 1;
    }
    else
    {
        a_record.m_outSMSOutOp = 1;
    }  
}

void SMSTReducing::Reduce(const protocol::Message & a_message, Record & a_record)
{
    a_record.m_imsi = a_message.m_cdr.m_imsi;
    a_record.m_misdn = a_message.m_cdr.m_msisdn;
    a_record.m_MCC  = a_message.m_cdr.m_mcc;
    a_record.m_operator = a_message.m_cdr.m_operator.m_value;

    if(a_message.m_cdr.m_operator.m_value == a_message.m_paryData.m_paryOperator.m_value)
    {
        a_record.m_inSMSInOp = 1;
    }
    else
    {
        a_record.m_inSMSOutOp = 1;
    } 
}

} // namespace advcpp
