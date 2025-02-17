#include <cstdio>
#include "cdr_decoder.hpp"

namespace advcpp
{

size_t DecodeMoc(protocol::Message & a_moc, const char * a_src)
{
    size_t loc = 0; 
    a_moc.m_type = DecodeT<uchar>(&(a_src[loc]), sizeof(uchar));
    loc += sizeof(uchar);
    loc += DecodeCdr(a_moc.m_cdr, &(a_src[loc]));
    a_moc.m_duration = DecodeT<uchar>(&(a_src[loc]), sizeof(uchar));
    loc += sizeof(uchar);
    loc += DecodeParty(a_moc.m_paryData, &(a_src[loc]));

    return loc;
}

size_t DecodeMtc(protocol::Message & a_mtc, char * a_src)
{
    size_t size = DecodeMoc( a_mtc, a_src);

    return size;
}

size_t DecodeSMSMO(protocol::Message & a_smsmo, char * a_src)
{
    size_t loc = 0;
     
    a_smsmo.m_type = DecodeT<uchar>(&(a_src[loc]), sizeof(uchar));
    loc += sizeof(uchar);
    loc += DecodeCdr(a_smsmo.m_cdr, &(a_src[loc]));
    loc += DecodeParty(a_smsmo.m_paryData, &(a_src[loc]));

    return loc;
}

size_t DecodeSMSMT(protocol::Message & a_smsmt, char * a_src)
{
    size_t loc = 0;
     
    a_smsmt.m_type = DecodeT<uchar>(&(a_src[loc]), sizeof(uchar));
    loc += sizeof(uchar);
    loc += DecodeCdr(a_smsmt.m_cdr, &(a_src[loc]));
    loc += DecodeParty(a_smsmt.m_paryData, &(a_src[loc]));

    return loc;
}

size_t DecodeGPRS(protocol::Message & a_sgprs, char * a_src)
{
    size_t loc = 0;
     
    a_sgprs.m_type = DecodeT<uchar>(&(a_src[loc]), sizeof(uchar));
    loc += sizeof(uchar);
    loc += DecodeCdr(a_sgprs.m_cdr, &(a_src[loc]));
    loc += DecodeParty(a_sgprs.m_paryData, &(a_src[loc]));

    return loc;
}



size_t DecodeCdr(protocol::CDR & a_cdr, const char * a_src)
{
    size_t loc = 0; 

    a_cdr.m_imsi = DecodeT<uint>(&(a_src[loc]), sizeof(uint));
    loc += sizeof(uint);
    a_cdr.m_msisdn = DecodeT<uint>(&(a_src[loc]), sizeof(uint));
    loc += sizeof(uint);
    a_cdr.m_imei = DecodeT<uint>(&(a_src[loc]), sizeof(uint));
    loc += sizeof(uint);
    loc += DecodeOperator(a_cdr.m_operator, &(a_src[loc]));
    a_cdr.m_mcc =  DecodeT<uint>(&(a_src[loc]), sizeof(uint));
    loc += sizeof(uint);
    loc += DecodeDate(a_cdr.m_date, &(a_src[loc]));  
    loc += DecodeTime(a_cdr.m_time, &(a_src[loc])); 

    return loc;
}
    

size_t DecodeOperator(protocol::Operator & a_op, const char * a_src)
{
    size_t loc = 0; 

    a_op.m_type = DecodeT<uchar>(&(a_src[loc]), sizeof(uchar));
    loc += sizeof(uchar);
    a_op.m_length = DecodeT<uint>(&(a_src[loc]), sizeof(uint));
    loc += sizeof(uint);
    a_op.m_value = DecodeT<uchar>(&(a_src[loc]), sizeof(uchar));
    loc += sizeof(uchar);

    return loc;
}

size_t DecodeDate(protocol::Date & a_date, const char * a_src)
{
    
    size_t loc = 0; 

    a_date.m_day = DecodeT<uchar>(&(a_src[loc]), sizeof(uchar));
    loc += sizeof(uchar);
    a_date.m_month = DecodeT<uchar>(&(a_src[loc]), sizeof(uchar));
    loc += sizeof(uchar);
    a_date.m_year = DecodeT<ushort>(&(a_src[loc]), sizeof(ushort));
    loc += sizeof(ushort);

    return loc;
}

size_t DecodeTime(protocol::Time & a_time, const char * a_src)
{
    int loc = 0; 

    a_time.m_hour = DecodeT<uchar>(&(a_src[loc]), sizeof(uchar));
    loc += sizeof(uchar);
    a_time.m_minutes = DecodeT<uchar>(&(a_src[loc]), sizeof(uchar));
    loc += sizeof(uchar);
    a_time.m_sec = DecodeT<uchar>(&(a_src[loc]), sizeof(uchar));
    loc += sizeof(uchar);

    return loc;
}

size_t DecodeParty(protocol::Party & a_party, const char * a_src)
{
    size_t loc = 0; 
    
    a_party.m_paryMSISDN = DecodeT<uint>(&(a_src[loc]), 4);
    loc += 4;
    loc += DecodeOperator(a_party.m_paryOperator, &(a_src[loc]));

    return loc;
}


} // namespace advcpp
