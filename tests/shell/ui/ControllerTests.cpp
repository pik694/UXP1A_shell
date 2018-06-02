//
// Created by Piotr Żelazko on 27.04.2018.
//
#define BOOST_TEST_DYN_LINK
#ifdef BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(controller_test_suite)

BOOST_AUTO_TEST_CASE(sample_test){
    BOOST_CHECK_EQUAL(1,1);
}


BOOST_AUTO_TEST_SUITE_END()



#endif //BOOST_TEST_DYN_LINK