//
// Created by Piotr Żelazko on 27.04.2018.
//
#define BOOST_TEST_DYN_LINK
#ifdef BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <shell/model/domain/variables/Variable.hpp>

BOOST_AUTO_TEST_SUITE(model_test_suite)

BOOST_AUTO_TEST_CASE(sample_test){
    BOOST_CHECK_EQUAL(1,1);
}

BOOST_AUTO_TEST_CASE(construct_varaible){
        shell::model::variables::Variable *var = new shell::model::variables::Variable("VAR1", "/usr:/home/Documents:/libs");
        std::list<std::string> values;
        values.push_back("/usr");
        values.push_back("/home/Documents");
        values.push_back("/libs");
        BOOST_CHECK_EQUAL(3, var->getValues_().size());
        BOOST_CHECK_EQUAL_COLLECTIONS(values.begin(), values.end(), var->getValues_().begin(), var->getValues_().end());
}


BOOST_AUTO_TEST_SUITE_END()



#endif //BOOST_TEST_DYN_LINK