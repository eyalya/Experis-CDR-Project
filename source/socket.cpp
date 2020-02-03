#include <errno.h> //errno
#include <sys/types.h> //???
#include <string.h> //memset
//#include <sys/socket.h>
#include <unistd.h> //close
#include <iostream> // cerr
#include <arpa/inet.h> //inet_addr
#include <netinet/in.h> //struct sockaddr_in
#include "socket.hpp"
#include "numbers.hpp"

namespace advcpp{

ISocket::~ISocket()
{    
}

Socket::Socket(const char* a_ip, int a_port, int a_domain, int a_type, int a_protocol)
: m_socket(socket(a_domain, a_type, a_protocol))
, m_ip(a_ip)
, m_port(a_port)
{
    if(m_socket == ERROR)       
    {
        std::cerr << "socket failed";
        throw SocketException(numbers::Itoa(errno), ExtendInfo(XINFO));
    }    
}

Socket::Socket(long a_socket) NOEXCEPT
: m_socket(a_socket)
{    
}


Socket::~Socket() NOEXCEPT
{
    close(m_socket);
}

int Socket::Sock() const
{
    return m_socket;
}

void Socket::Connect()
{    
    struct sockaddr_in sin;

	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = inet_addr(m_ip.c_str());
	sin.sin_port = htons(m_port);   
    int res = connect(m_socket, (sockaddr*)&sin, sizeof(sin));
    
    if (res == ERROR)
    {
        std::cerr << "connect failed\n";
        throw SocketException(numbers::Itoa(errno), ExtendInfo(XINFO));
    }	
}

void Socket::Bind()
{	
	struct sockaddr_in sin;	

	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = inet_addr(m_ip.c_str());
	sin.sin_port = htons(m_port);   

    int res = bind(m_socket, (sockaddr*)&sin, sizeof(sin));

    if (res == ERROR)
    {
        std::cerr <<  "bind failed\n";
        throw SocketException(numbers::Itoa(errno), ExtendInfo(XINFO));
    }
}

void Socket::Listen(int a_backLog)
{
    int res = listen(m_socket, a_backLog);

    if (res == ERROR)
    {
        std::cerr << "listen failed\n";
        throw SocketException(numbers::Itoa(errno), ExtendInfo(XINFO));
    } 
}

void Socket::Reuse()
{
    int optval = 1;

    int res = setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

    if (res == ERROR)
    {
        std::cerr << "connect failed\n";
        throw SocketException(numbers::Itoa(errno), ExtendInfo(XINFO));
    }
}

size_t Socket::Recv(char* a_buff)
{
    int readBytes = recv(m_socket, a_buff, MAX_BUFF_LEN, 0);
	
	if (readBytes == ERROR)
	{
		std::cerr << "recv failed\n";
        throw SocketException(numbers::Itoa(errno), ExtendInfo(XINFO));
	}    
    return readBytes;
}

//TODO: return here
void Socket::Send(const char* a_msg)
{
    size_t len = strlen(a_msg);
    int sentBytes = send(Sock(), a_msg, len, 0);
	
	if (sentBytes == ERROR)
	{
		std::cerr << "send failed\n";
        throw SocketException(numbers::Itoa(errno), ExtendInfo(XINFO));
	}        
}

void Socket::Accept()
{    
}

void Socket::NoBlock()
{    
}

void Socket::Close()
{    
}

} //namespace advcpp

