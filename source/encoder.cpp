#include "encoder.hpp"


namespace advcpp
{

size_t EncodeMoc(char * a_dest, protocol::MOC & a_moc)
{
    size_t loc = 0; 

    loc += EncodeT<uchar>(&(a_dest[loc]), a_moc.m_type );
    loc += EncodeCdr(&(a_dest[loc]), a_moc.m_cdr);
    loc += EncodeT<ushort>(&(a_dest[loc]), a_moc.m_duration);
    loc += EncodeParty(&(a_dest[loc]), a_moc.m_paryData);

    return loc;
}


size_t EncodeCdr(char * a_dest, protocol::CDR & a_cdr)
{
    size_t loc = 0; 

    loc += EncodeT<uint>(&(a_dest[loc]), a_cdr.m_imsi );
    loc += EncodeT<uint>(&(a_dest[loc]), a_cdr.m_msisdn );
    loc += EncodeT<uint>(&(a_dest[loc]), a_cdr.m_imei );
    loc += EncodeOperator( &(a_dest[loc]), a_cdr.m_operator);
    loc += EncodeT<uint>(&(a_dest[loc]), a_cdr.m_mcc );
    loc += EncodeDate( &(a_dest[loc]), a_cdr.m_date);
    loc += EncodeTime( &(a_dest[loc]),  a_cdr.m_time);
    
    return loc;
}

size_t EncodeOperator(char * a_dest, protocol::Operator & a_operator)
{
    size_t loc = 0; 

    loc += EncodeT<uchar>(&(a_dest[loc]), a_operator.m_type );
    loc += EncodeT<uint>(&(a_dest[loc]), a_operator.m_length );
    loc += EncodeT<uchar>(&(a_dest[loc]), a_operator.m_value );
    
    return loc;
}

size_t EncodeDate(char * a_dest, protocol::Date & a_date)
{
    size_t loc = 0; 

    loc += EncodeT<uchar>(&(a_dest[loc]), a_date.m_day );
    loc += EncodeT<uchar>(&(a_dest[loc]), a_date.m_month );
    loc += EncodeT<ushort>(&(a_dest[loc]), a_date.m_year );
    
    return loc;
}

size_t EncodeTime(char * a_dest, protocol::Time & a_time)
{
    size_t loc = 0; 

    loc += EncodeT<uchar>(&(a_dest[loc]), a_time.m_hour );
    loc += EncodeT<uchar>(&(a_dest[loc]), a_time.m_minutes );
    loc += EncodeT<uchar>(&(a_dest[loc]), a_time.m_sec );
    
    return loc;
}

size_t EncodeParty(char * a_dest, protocol::Party & a_party)
{
    size_t loc = 0; 

    loc += EncodeT<uint>(&(a_dest[loc]), a_party.m_paryMSISDN );
    loc += EncodeOperator( &(a_dest[loc]), a_party.m_paryOperator);
    
    return loc;
}

} // namespace advcpp
