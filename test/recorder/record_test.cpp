#include "mu_test.h"

#include <iostream>
#include "cdr_decoder.hpp"
#include "protocol.hpp"
#include "irecorder.hpp"
#include "record.hpp"


UNIT(check_decode)

    //char ch = 1;
    //int num(0);
    char test[] = "\0\1\0\0\0\2\0\0\0\3\0\0\0aaaaaaaaaaaaaaaaa\2\0\0\0\0\0\0\0\1aaa111111111111111111111111111111111111111111111\0";
   
    advcpp::Record a_record;

    std::vector<advcpp::IDecodeMassge *>  a_decoders;
    advcpp::DecodeMCO dmco;
    a_decoders.push_back(&dmco);
    advcpp::CdrDecoder cDecoder(a_decoders);
    protocol::Message a_message;
    cDecoder.Decode(test, a_message);

    std::cout << "\na_message.m_type" << a_message.m_type << '\n';
    std::cout << a_message.m_cdr.m_imsi << '\n';
    std::cout << a_message.m_cdr.m_msisdn << '\n';
    std::cout << a_message.m_cdr.m_imei << '\n';
    std::cout << a_message.m_duration << '\n';

    std::vector<advcpp::IReducing *> a_reducers;
    advcpp::MCOReducing mcoreducering;
    a_reducers.push_back(&mcoreducering);
    advcpp::Reducer reducer(a_reducers);
    advcpp::Record record;
    // reducer.Reduce(a_message, record);

    // std::cout << record.m_outVoiceInOp << '\n';

    advcpp::RecordAggregator<char *> rA(cDecoder, reducer);
    rA.Generate(test, record);

    std::cout << "\ncheck " << record.m_outVoiceInOp << '\n';    
    // std::cout << sizeof(uchar) << sizeof(ushort) << '\n';
    // r.Generate(test, a_record);

    std::cout << a_record.m_outVoiceInOp << '\n';
	ASSERT_PASS();
END_UNIT


TEST_SUITE(thread tests)
	TEST(check_decode)
END_SUITE

