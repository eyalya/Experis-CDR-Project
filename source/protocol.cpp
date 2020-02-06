/*
#include <sstream>
#include "protocol.hpp"

namespace advcpp{
std::stringstream& operator>>(std::stringstream& a_ss, protocol::MOC& a_moc)
{
    a_ss >> a_moc.m_type;
    a_ss >> a_moc.m_cdr; // overload conflict with a_messege.m_cdr
    a_ss >> a_moc.m_duration;
    a_ss >> a_moc.m_paryData;
    return a_ss;
}

std::stringstream& operator>>(std::stringstream& a_ss, protocol::CDR& a_cdr)
{
    a_ss >> a_cdr.m_imsi;
    a_ss >> a_cdr.m_msisdn;
    a_ss >> a_cdr.m_imei;
    a_ss >> a_cdr.m_operator;
    a_ss >> a_cdr.m_mcc;
    a_ss >> a_cdr.m_date;
    a_ss >> a_cdr.m_time;
    return a_ss;    
}

std::stringstream& operator>>(std::stringstream& a_ss, protocol::Operator& a_operator)
{
    
    //a_ss >> a_operator.m_type;
    //a_ss >> a_operator.m_length;
    a_ss >> a_operator.m_value;
    return a_ss;
}

std::stringstream& operator>>(std::stringstream& a_ss, protocol::Date& a_date)
{
    std:: string s;
    std::getline(a_ss, s, '/');

    std:: stringstream ss(s);
    ss >> a_date.m_day;

    std::getline(a_ss, s, '/');
    ss << s;
    a_ss >> a_date.m_month;

    std::getline(a_ss, s, ' ');
    ss << s;
    a_ss >> a_date.m_year;

    return a_ss;
}

std::stringstream& operator>>(std::stringstream& a_ss, protocol::Time& a_time)
{
    std:: string s;
    std::getline(a_ss, s, '/');
    std::stringstream ss(s);
    a_ss >> a_time.m_hour;

    std::getline(a_ss, s, '/');
    ss << s;
    a_ss >> a_time.m_minutes;

    std::getline(a_ss, s, ' ');
    ss << s;
    a_ss >> a_time.m_sec;
    return a_ss;
}

std::stringstream& operator>>(std::stringstream& a_ss, protocol::Party& a_party)
{
    a_ss >> a_party.m_paryMSISDN;
    a_ss >> a_party.m_paryOperator;
    return a_ss;
}

std::stringstream& operator>>(std::stringstream& a_ss, protocol::DataUsage& a_data)
{
    a_ss >> a_data.m_download;
    a_ss >> a_data.m_uploaded;
    return a_ss;
}

std::stringstream& operator>>(std::stringstream& a_ss, protocol::Message& a_messege)
{
    a_ss >> a_messege.m_type;
    a_ss >> a_messege.m_cdr;
    a_ss >> a_messege.m_duration;
    a_ss >> a_messege.m_paryData;
    return a_ss;
}
} //namespace advcpp
*/

