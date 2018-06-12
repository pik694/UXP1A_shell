//
// Created by Piotr Żelazko on 27.04.2018.
//
#define BOOST_TEST_DYN_LINK
#ifdef BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <shell/model/domain/variables/Variable.hpp>
#include <shell/model/domain/VariablesRepository.hpp>
#include <shell/model/ModelFacade.hpp>
#include <iostream>

BOOST_AUTO_TEST_SUITE(model_test_suite)

BOOST_AUTO_TEST_CASE(construct_varaible){
        std::unique_ptr<shell::model::variables::Variable> var = std::make_unique<shell::model::variables::Variable>("VAR", "/usr:/home/Documents:/libs");//new shell::model::variables::Variable("VAR", "/usr:/home/Documents:/libs");
        std::list<std::string> values;
        values.push_back("/usr");
        values.push_back("/home/Documents");
        values.push_back("/libs");
        BOOST_CHECK_EQUAL(3, var->getValues_().size());
        BOOST_CHECK_EQUAL_COLLECTIONS(values.begin(), values.end(), var->getValues_().begin(), var->getValues_().end());
}

BOOST_AUTO_TEST_CASE(set_and_get_varaible_from_repo){
    auto addedVar = new shell::model::variables::Variable("VAR", "/usr:/home/Documents:/libs");
    auto repository = new shell::model::VariablesRepository();

    repository->setVariable(*addedVar);
    auto receivedVar = repository->getVariable(addedVar->getName_());

    BOOST_CHECK_EQUAL_COLLECTIONS(addedVar->getValues_().begin(), addedVar->getValues_().end(),
                                  receivedVar.getValues_().begin(), receivedVar.getValues_().end());
}

    BOOST_AUTO_TEST_CASE(set_change_and_get_varaible_from_repo){
        auto addedVar = new shell::model::variables::Variable("VAR", "/usr:/home/Documents:/libs");
        auto repository = new shell::model::VariablesRepository();

        repository->setVariable(*addedVar);
        addedVar->setValues_("/usr/local/lib:/home/Downloads");
        repository->setVariable(*addedVar);

        auto expectedVar = new shell::model::variables::Variable("VAR", "/usr/local/lib:/home/Downloads");
        auto receivedVar = repository->getVariable(addedVar->getName_());


        BOOST_CHECK_EQUAL_COLLECTIONS(expectedVar->getValues_().begin(), expectedVar->getValues_().end(),
                                      receivedVar.getValues_().begin(), receivedVar.getValues_().end());
    }

    BOOST_AUTO_TEST_CASE(get_env_variable){
    auto varRepository = new shell::model::VariablesRepository();
    auto modelFacade = new shell::model::ModelFacade(*varRepository);
    std::list<std::string> values;
    auto variable = modelFacade->getVariable("HOME");
    values.push_back("/home/marcin");
    BOOST_CHECK_EQUAL_COLLECTIONS(values.begin(), values.end(), variable->getValues_().begin(),
                                  variable->getValues_().end());

}

BOOST_AUTO_TEST_SUITE_END()



#endif //BOOST_TEST_DYN_LINK