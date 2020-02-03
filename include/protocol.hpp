#ifndef PROTOCOL_HPP
#define	PROTOCOL_HPP

typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned short ushort;

namespace protocol
{


class IMassage
{
public: 
	virtual ~IMassage() = 0;
};

enum Call
{
	CALL_MOC, // outgoing voice call
	CALL_MTC,// incoming voice call
	CALL_SMS_MO, // outgoing SMS
	CALL_SMS_MT, // incoming messages
	CALL_GPRS, // internet
	READ_DATA_ERR
};

typedef uint IMSI;
typedef uint MSISDN;
typedef uint IMEI;
typedef uint MCC;
typedef ushort Duration;

struct Operator 
{
	uchar	m_type;	
	uint	m_length;
	uchar	m_value;
};

struct Date 
{
	uchar	m_day;	
	uchar	m_month;
	ushort	m_year;
};

struct Time 
{
	uchar	m_hour;	
	uchar	m_minutes;
	uchar	m_sec;
};

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

struct ReadErr
{
	uchar		m_type;
};

struct Party 
{
	MSISDN		m_paryMSISDN;
	Operator	m_paryOperator;
};

struct DataUsage 
{
	ushort		m_download;
	ushort		m_uploaded;
};

struct Message 
{
	uchar		m_type;
	CDR			m_cdr;
	Duration	m_duration;
	Party		m_paryData;
};

struct MOC 
{
	uchar		m_type;
	CDR			m_cdr;
	Duration	m_duration;
	Party		m_paryData;
};

struct MTC 
{
	uchar		m_type;
	CDR			m_cdr;
	Duration	m_duration;
	Party		m_paryData;
};

struct SMS_MO 
{
	uchar		m_type;
	CDR			m_cdr;
	Party		m_paryData;
};

struct SMS_MT 
{
	uchar		m_type;
	CDR			m_cdr;
	Party		m_paryData;
};

struct GPRS 
{
	uchar		m_type;
	CDR			m_cdr;
	DataUsage	m_paryData;
};


inline IMassage::~IMassage()
{
}

}

#endif	//PROTOCOL_HPP























