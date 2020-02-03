#ifndef TCP_CLIENT_HPP
#define TCP_CLIENT_HPP
#include <sys/socket.h> //POSIX socket
#include <arpa/inet.h> //???
#include <unistd.h> //close
#include <string.h> //strlen
#include "socket.hpp"

namespace advcpp{


class TCPClientException : private ExtendedException
{
public:
    TCPClientException(const char* a_msg, ExtendInfo a_xInfo)
    : ExtendedException(a_msg, a_xInfo) {}
};


class IClient
{
public:
    IClient() {};
    virtual ~IClient() = 0;

private:
    IClient(IClient const&);
    IClient& operator=(IClient const&);

public:
    virtual void Send(const char* a_msg) = 0;
    virtual size_t Recv() = 0;
    virtual void Close() = 0;

    virtual const char* Messege() = 0;
};

class TCPClient : public IClient
{
public:
    TCPClient(const char* a_address, int a_port);
    //~TCPClient() = default;

    virtual void Send(const char* a_msg);
    virtual size_t Recv();
    virtual void Close();

    virtual const char* Messege();

private:
    const std::string   m_address;
    int                 m_port;
    Socket              m_socket;
    char                m_buff[MAX_BUFF_LEN];
};

}//namespace advcpp
#endif //TCP_CLIENT_HPP