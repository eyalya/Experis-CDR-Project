#include "mu_test.h"
#include "atomic.hpp"

UNIT(atomic_operations)
    advcpp::AtomicValue<int> a;
    ++a;
    ASSERT_EQUAL(a.Get(), 1);
    --a;
    ASSERT_EQUAL(a.Get(), 0);
    a+=10;
    ASSERT_EQUAL(a.Get(), 10);
    a-=60;
    ASSERT_EQUAL(a.Get(), -50);
    a.Set(888);
    ASSERT_EQUAL(a.Get(), 888);    
END_UNIT

TEST_SUITE( atomic tests )
    TEST(atomic_operations)
END_SUITE
