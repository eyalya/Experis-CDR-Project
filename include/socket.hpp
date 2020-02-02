#ifndef SOCKET_HPP
#define SOCKET_HPP
#include <sys/socket.h>
#include <string>
#include "common.hpp"

namespace advcpp{

static const int ERROR = -1;
static const size_t MAX_BUFF_LEN = 1024;

class SocketException : private ExtendedException
{
public:
    SocketException(const char* a_msg, ExtendInfo a_xInfo)
    : ExtendedException(a_msg, a_xInfo) {}
};

class ISocket
{
public:
    //virtual ISocket() = default;
    virtual ~ISocket() = 0;

private:
    ISocket(ISocket const&);
    ISocket& operator=(ISocket const&);

public:
    virtual void Connect(const char* a_address, int a_port) = 0;
    virtual void Bind(int a_port) = 0;
    virtual void Listen() = 0;
    virtual void Accept() = 0;
    virtual void Reuse() = 0;
    virtual void NoBlock() = 0;
    virtual size_t Recv(char* a_msg) = 0;
    virtual void Send(const char* a_msg) = 0;
    virtual void Close() = 0;
    virtual int Sock() const = 0;
};


class Socket : private Uncopyable
{
public:
    Socket(const char* a_ip, int a_port, int a_domain = AF_INET, int a_type = SOCK_STREAM, int a_protocol = 0);
    explicit Socket(long a_socket) NOEXCEPT;
    ~Socket() NOEXCEPT;

    virtual void Connect();
    virtual void Bind();
    virtual void Listen(int a_backLog);
    virtual void Accept();
    virtual void Reuse();
    virtual void NoBlock();
    virtual size_t Recv(char* a_msg);
    virtual void Send(const char* a_msg);
    virtual void Close();
    virtual int Sock() const;

private:
    int         m_socket;
    std::string m_ip;
    int         m_port;
};

} //namespace advcpp

#endif //SOCKET_HPP
