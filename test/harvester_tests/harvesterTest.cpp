#include <iostream>
#include <sstream>
#include "TCP_client.hpp"
#include "text_reader.hpp"
#include "parser.hpp"
#include "protocol.hpp"
#include "encoder.hpp"

static const char* filename = "~/CDR_in/cdr1.txt";
static const size_t MAX_BUFF_LEN = 1024;
static const char* LOOPBACK_ADDR = "127.0.0.1";
static const bool FOREVER = true;
static const int PORT = 2300;
typedef std::vector<std::string> Fields;

/*
struct MOC 
{
	uchar		m_type;
	CDR			m_cdr;
	Duration	m_duration;
	Party		m_paryData;
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
*/


bool fields2MOC(Fields const& a_fields, protocol::MOC& a_moc)
{
    
    enum CDR_ENUMS
    {
        imsi , msisdn  , imei  , operatorName  , operatorType , operatorLength, mcc  ,   type  ,  date  ,  time  ,   duration  ,  download   ,   upload   ,   partyMsisbn  ,  partyMccMnc
    };
    
    enum Date
    {
        DAY, MONTH, YEAR
    };

    enum Operator
    {
        TYPE, LENGTH, VALUE
    };

    enum Time
    {
        HOUR, MINUTE, SECOND
    }
    std::stringstream ss;
    
    // extract type
    ss << a_fields[imsi];
    ss >> a_moc.m_type;

    // extract cdr
        //extract date
        ss << a_fields[day];
        ss >> a_moc.m_cdr.m_date.m_day;
        ss << a_fields[month];
        ss >> a_moc.m_cdr.m_date.m_month;
        ss << a_fields[year];
        ss >> a_moc.m_cdr.m_date.m_year;

    ss << a_fields[imei];
    ss >> a_moc.m_cdr.m_imei;    
    ss << a_fields[imsi];
    ss >> a_moc.m_cdr.m_imsi;
    ss << a_fields[msisdn];
    ss >> a_moc.m_cdr.m_msisdn;
    ss << a_fields[mcc];
    ss >> a_moc.m_cdr.m_mcc;

        //extract operator
        ss >> a_moc.m_cdr.m_operator.m_type;
        ss >> a_moc.m_cdr.m_operator.m_length;
        ss >> a_moc.m_cdr.m_operator.m_value;

        //extract time
        ss >> a_moc.m_cdr.m_time.m_hour;
        ss >> a_moc.m_cdr.m_time.m_minutes;
        ss >> a_moc.m_cdr.m_time.m_sec;

    //extract party data    
    ss >> a_moc.m_paryData.m_paryMSISDN;
    ss >> a_moc.m_paryData.m_paryOperator.m_type;
    ss >> a_moc.m_paryData.m_paryOperator.m_length;
    ss >> a_moc.m_paryData.m_paryOperator.m_value;

    //extract duration
    ss >> a_moc.m_duration;


}


int main()
{
    advcpp::FileReader reader(filename);
    advcpp::RecordParseByDelim parser('|');
    Fields fields;

    advcpp::TCPClient client(LOOPBACK_ADDR, PORT);    
    
    while(!reader.IsDone)
    {
        std::string& record = reader.Read();
        parser.Parse(record, fields);
        protocol::MOC moc;
        Fields2MOC(fields, moc);
        char buff[MAX_BUFF_LEN];
        advcpp::EncodeMoc(buff, moc);
        client.Send(buff);
    }

    //move file to old files folder

    return 0;    
}