#include "mu_test.h"

#include <iostream>
#include "cdr_decoder.hpp"
#include "protocol.hpp"
#include "irecorder.hpp"
#include "record.hpp"


UNIT(check_decode)

    //char ch = 1;
    //int num(0);
    char test[] = "aa\0\0\0a\0\0\0ooooooooooooooooooooooooooooooooooo";
    advcpp::Record a_record;

    advcpp::RecordAggregator<char *> r;

    r.Generate(test, a_record);

    std::cout << a_record.m_outVoiceInOp << '\n';
	ASSERT_PASS();
END_UNIT


TEST_SUITE(thread tests)
	TEST(check_decode)
END_SUITE

