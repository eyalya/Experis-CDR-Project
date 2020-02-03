#include "mu_test.h"

#include <iostream>
#include "cdr_decoder.hpp"
#include "protocol.hpp"
#include "irecorder.hpp"
#include "record.hpp"


UNIT(check_decode)

    //char ch = 1;
    //int num(0);
    char test[] = "\0a\0\0\0a\0\0\0ooooooooooooooooooooooooooooooooooo";
    advcpp::Record a_record;

    std::vector<advcpp::IDecodeMassge *>  a_decoders;
    advcpp::DecodeMCO dmco;
    a_decoders.push_back(&dmco);
    advcpp::CdrDecoder cDecoder(a_decoders);
    protocol::Message a_message;
    cDecoder.Decode(test, a_message);

    std::cout << a_message.m_cdr.m_imsi;
    
    std::vector<advcpp::IReducing *> a_reducers;
    advcpp::MCOReducing mcoreducering;
    a_reducers.push_back(&mcoreducering);
    advcpp::Reducer reducer(a_reducers);
    advcpp::Record record;
    reducer.Reduce(a_message, record);

    
    // r.Generate(test, a_record);

    // std::cout << a_record.m_outVoiceInOp << '\n';
	ASSERT_PASS();
END_UNIT


TEST_SUITE(thread tests)
	TEST(check_decode)
END_SUITE

