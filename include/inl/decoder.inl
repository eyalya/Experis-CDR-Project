#include <cstdio>
#include "cdr_decoder.hpp"
#include <iostream>
#include <cstring>

namespace advcpp
{

template <typename T>
T DecodeT(char * a_src, int a_len);
size_t DecodeCdr(protocol::CDR & a_cdr, char * a_src);
size_t DecodeOperator(protocol::Operator & a_op, char * a_src);
size_t DecodeTime(protocol::Time & a_time, char * a_src);
size_t DecodeParty(protocol::Party & a_party, char * a_src);
size_t DecodeDate(protocol::Date & a_date, char * a_src);
size_t DecodeMoc(protocol::Message & a_moc, char * a_src);

inline IDecodeMassge::~IDecodeMassge()
{
}


inline void DecodeMCO::Decode(char * a_src, protocol::Message & a_message)
{
    DecodeMoc(a_message, a_src);
}

inline CdrDecoder::CdrDecoder(std::vector<IDecodeMassge *> & a_decoders)
: m_decoders(a_decoders)
{ 
}

inline void CdrDecoder::Decode(char * a_src, protocol::Message & a_message)
{
    uchar index = DecodeT<uchar>(&(a_src[0]), sizeof(uchar));
    m_decoders[index] -> Decode(a_src, a_message);
}


template <typename T>
T DecodeT(char * a_src, int a_len)
{
    T newType;
    std::memcpy(&newType, a_src, a_len);

    return newType;
}

inline size_t DecodeMoc(protocol::Message & a_moc, char * a_src)
{
    size_t loc = 0; 
    a_moc.m_type = DecodeT<uchar>(&(a_src[loc]), sizeof(uchar));
    loc += sizeof(uchar);
    std::cout <<  loc << '\n';
    loc += DecodeCdr(a_moc.m_cdr, &(a_src[loc]));
    
    a_moc.m_duration = DecodeT<uchar>(&(a_src[loc]), sizeof(uchar));
    loc += sizeof(uchar);
    loc += DecodeParty(a_moc.m_paryData, &(a_src[loc]));

    return loc;
}

inline size_t DecodeCdr(protocol::CDR & a_cdr, char * a_src)
{
    size_t loc = 0; 
    a_cdr.m_imsi = DecodeT<uint>(&(a_src[loc]), sizeof(uint));
    loc += sizeof(uint);
    a_cdr.m_msisdn = DecodeT<uint>(&(a_src[loc]), sizeof(uint));
    loc += sizeof(uint);
    std::cout << "\nloc before imei " << loc;
    a_cdr.m_imei = DecodeT<uint>(&(a_src[loc]), sizeof(uint));
    loc += sizeof(uint);
    std::cout << "\nloc after imei " << loc;
    loc += DecodeOperator(a_cdr.m_operator, &(a_src[loc]));
    std::cout << "\nloc after operator " << loc;
    a_cdr.m_mcc =  DecodeT<uint>(&(a_src[loc]), sizeof(uint));
    loc += sizeof(uint);
    loc += DecodeDate(a_cdr.m_date, &(a_src[loc]));  
    loc += DecodeTime(a_cdr.m_time, &(a_src[loc]));  
    return loc;
}
    

inline size_t DecodeOperator(protocol::Operator & a_op, char * a_src)
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

inline size_t DecodeDate(protocol::Date & a_date, char * a_src)
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

inline size_t DecodeTime(protocol::Time & a_time, char * a_src)
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

inline size_t DecodeParty(protocol::Party & a_party, char * a_src)
{
    size_t loc = 0; 
    a_party.m_paryMSISDN = DecodeT<uint>(&(a_src[loc]), 4);
    loc += 4;
    loc += DecodeOperator(a_party.m_paryOperator, &(a_src[loc]));

    return loc;
}


/*
struct Operator 

{

	uchar	m_type;	

	uint	m_length;

	uchar	m_value;

};

​

struct Date 

{

	uchar	m_day;	

	uchar	m_month;

	ushort	m_year;

};

​

struct Time 

{

	uchar	m_hour;	

	uchar	m_minutes;

	uchar	m_sec;

};



typedef uint IMSI;

typedef uint MSISDN;

typedef uint IMEI;

typedef uint MCC;

typedef ushort Duration;

struct CDR 

{

	IMSI		m_imsi;

	MSISDN		m_msisdn;

	IMEI		m_imei;

	Operator	m_operator;

	MCC			m_mcc;

	Date		m_date;

	Time		m_time;

};


struct MOC 

{

	uchar		m_type;

	CDR			m_cdr;

	Duration	m_duration;

	Party		m_paryData;

};

*/

} // namespace advcpp
