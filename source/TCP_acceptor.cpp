#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE 500
#endif 	/*_XOPEN_SOURCE*/
#include <errno.h> //perror, errno
#include <string.h> //strlen
#include <arpa/inet.h> //recv
#include <sys/types.h> //bind
#include <fcntl.h> //fcntl
#include <unistd.h> //close
#include <iostream> // cerr
#include "TCP_acceptor.hpp"

namespace advcpp{

IAcceptor::~IAcceptor()
{	
}

TCPAcceptor::TCPAcceptor(const char* a_ip, int a_port, WaitableQueue<ISocket*>& a_queue)
: m_ip(a_ip)
, m_port(a_port)
, m_socket(m_ip.c_str(), m_port)
, m_queue(a_queue)
{	
	m_socket.Reuse(); //setsockopt
	m_socket.Bind();
	//check if need to add SIGINT sigaction...
}

void TCPAcceptor::ShutDown()
{
    //FIXME: busy wait for queue to empty... what is better?
	while(m_queue.Size() > 0);
	m_socket.Close();
}

void TCPAcceptor::Run()
{
	m_socket.Listen(QUEUE_SIZE);
	
	while (true)
	{   
		
		ISocket* newSock;	
		try
		{
			#if DEBUG > 0
				std::cout << "Acceptor: accepting..."
			#endif

			newSock = m_socket.Accept(); //FIXME: blocks here on second accept...
		}

		catch(const SocketException& e)
		{		
		}

		catch(...)
		{
			throw;
		}
		m_queue.Enqueue(newSock);
	}

	ShutDown();
}

} //namespace advcpp