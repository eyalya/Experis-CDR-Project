#include <iostream>
#include <sstream>
#include "TCP_client.hpp"
#include "text_reader.hpp"
#include "parser.hpp"
#include "protocol.hpp"
#include "encoder.hpp"
#include "striper.hpp"

static const char* filename = "~/CDR_in/cdr1.txt";
static const size_t MAX_BUFF_LEN = 1024;
static const size_t BUFF_SIZE = 61;
static const char* LOOPBACK_ADDR = "127.0.0.1";
static const bool FOREVER = true;
static const int PORT = 2300;
typedef std::vector<std::string> Fields;

int main()
{
    advcpp::FileReader reader(filename);
    advcpp::ReplacerDelim striper('|', ' ');

    advcpp::TCPClient client(LOOPBACK_ADDR, PORT);    
    
    while(!reader.IsDone)
    {
        std::string& record = reader.Read();
        std::cout << "before strip: " << record << "\n";
        
        striper.Strip(record);
        std::cout << "after strip: " << record << "\n";

        std::stringstream ss << record;
        protocol::MOC moc;
        ss >> moc;

        char inBuff[MAX_BUFF_LEN];
        advcpp::EncodeMoc(buff, moc);
        buff[sizeof(buff) = '\0'];
        std::cout << buff "\n";


        //char outBuff[MAX_BUFF_LEN];
        //advcpp:Agre



        //client.Send(buff);
    }

    //move file to old files folder

    return 0;    
}