#ifndef SOCKET_HPP
#define SOCKET_HPP
#include <sys/socket.h>
#include <string>
#include "common.hpp"

namespace advcpp{

static const int ERROR = -1;
static const size_t MAX_BUFF_LEN = 60;

class SocketException : private ExtendedException
{
public:
    SocketException(const char* a_msg, ExtendInfo a_xInfo)
    : ExtendedException(a_msg, a_xInfo) {}
};

class ISocket
{
public:    
    ISocket() {};
    virtual ~ISocket() = 0;

private:
    ISocket(ISocket const&);
    ISocket& operator=(ISocket const&);

public:
    virtual void Connect() = 0;

    virtual void Bind() = 0;
    virtual void Listen(int a_backLog) = 0;
    virtual ISocket* Accept() = 0;
    virtual void Reuse() = 0;
    virtual void NoBlock() = 0;
    virtual size_t Recv(char* a_msg) = 0;
    virtual void Send(const char* a_msg, size_t a_buffSize) = 0;
    virtual void Close() = 0; //TODO: hide as private -> close in dtor
    
    virtual int Sock() const = 0;
};


class Socket : public ISocket
{
public:
    Socket(const char* a_ip, int a_port, int a_domain = AF_INET, int a_type = SOCK_STREAM, int a_protocol = 0);
    explicit Socket(long a_socket) NOEXCEPT;
    virtual ~Socket() NOEXCEPT;

    virtual void Connect();

    virtual void Bind();
    virtual void Listen(int a_backLog);
    virtual ISocket* Accept();
    virtual void Reuse();
    virtual void NoBlock();
    virtual size_t Recv(char* a_msg);
    virtual void Send(const char* a_msg, size_t buffSize = 256);
    virtual void Close();
    
    virtual int Sock() const;

private:
    int         m_socket;
    std::string m_ip;
    int         m_port;
};

} //namespace advcpp

#endif //SOCKET_HPP
