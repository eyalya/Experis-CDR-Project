#include <iostream>
#include "socket.hpp"

typedef advcpp::Socket S;
const char* LOOPBACK_ADDR = "127.0.0.1";
const char* AMIT_IP = "192.168.0.103";
const char* LIOR_IP = "192.168.0.40";

static const size_t MAX_BUFF_LEN = 1024;
int port = 2300;

int main()
{
    S s(LOOPBACK_ADDR, port);
    s.Connect();
    s.Send("Hello from Royi");
    char buff[MAX_BUFF_LEN];
    s.Recv(buff);
    std::cout << buff << "\n";
    s.Close();
}


