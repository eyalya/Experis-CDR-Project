#include "TCP_client.hpp"

namespace advcpp{

IClient::~IClient()
{    
}

TCPClient::TCPClient(const char* a_address, int a_port)
: m_address(a_address)
, m_port(a_port)
, m_socket(a_address, a_port)
, m_buff()
{
    m_socket.Connect();
}

void TCPClient::Send(const char* a_msg)
{
    m_socket.Send(a_msg);    
}

size_t TCPClient::Recv()
{
    return m_socket.Recv(m_buff);
}

const char* TCPClient::Messege()
{
    return m_buff;
}

void TCPClient::Close()
{
    m_socket.Close();
}

}//namespace advcpp