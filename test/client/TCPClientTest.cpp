#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include "TCP_client.hpp"

typedef advcpp::TCPClient Client;
static const int port = 2300;
static const char* LOOPBACK_ADDR = "127.0.0.1";



int main()
{
    
    Client client(LOOPBACK_ADDR, port);
    const size_t size = 10000;
    for (size_t i=0; i<size; ++i)
    {
        std::ostringstream stream;
        stream << "Messege #" << i;
        std::cout << "sending msg: " << "Messege #" << i << "\n";
        std::string str =  stream.str();       
        client.Send(str.c_str());
    }
    client.Recv();
    client.Close();
}


