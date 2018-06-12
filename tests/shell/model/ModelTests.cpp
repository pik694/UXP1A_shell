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
#include <shell/model/domain/VariablesFactory.hpp>

BOOST_AUTO_TEST_SUITE(model_test_suite)

BOOST_AUTO_TEST_CASE(construct_varaible){
        std::unique_ptr<shell::model::variables::Variable> var = shell::model::variables::VariablesFactory::produce("VAR", "/usr:/home/Documents:/libs");
        std::list<std::string> values;
        values.push_back("/usr");
        values.push_back("/home/Documents");
        values.push_back("/libs");
        BOOST_CHECK_EQUAL(3, var->getValues_().size());
        BOOST_CHECK_EQUAL_COLLECTIONS(values.begin(), values.end(), var->getValues_().begin(), var->getValues_().end());
}

BOOST_AUTO_TEST_CASE(set_and_get_varaible_from_repo){
    std::unique_ptr<shell::model::variables::Variable> addedVar = shell::model::variables::VariablesFactory::produce("VAR", "/usr:/home/Documents:/libs");
    std::unique_ptr<shell::model::VariablesRepository> repository = std::make_unique<shell::model::VariablesRepository>();

    repository->setVariable(*addedVar);
    auto receivedVar = repository->getVariable(addedVar->getName_());

    BOOST_CHECK_EQUAL_COLLECTIONS(addedVar->getValues_().begin(), addedVar->getValues_().end(),
                                  receivedVar.getValues_().begin(), receivedVar.getValues_().end());
}

    BOOST_AUTO_TEST_CASE(set_change_and_get_varaible_from_repo){
        std::unique_ptr<shell::model::variables::Variable> addedVar = shell::model::variables::VariablesFactory::produce("VAR", "/usr:/home/Documents:/libs");
        std::unique_ptr<shell::model::VariablesRepository> repository = std::make_unique<shell::model::VariablesRepository>();

        repository->setVariable(*addedVar);
        addedVar->setValues_("/usr/local/lib:/home/Downloads");
        repository->setVariable(*addedVar);

        std::unique_ptr<shell::model::variables::Variable> expectedVar = shell::model::variables::VariablesFactory::produce("VAR", "/usr/local/lib:/home/Downloads");
        auto receivedVar = repository->getVariable(addedVar->getName_());


        BOOST_CHECK_EQUAL_COLLECTIONS(expectedVar->getValues_().begin(), expectedVar->getValues_().end(),
                                      receivedVar.getValues_().begin(), receivedVar.getValues_().end());
    }

    BOOST_AUTO_TEST_CASE(set_and_get_env_variable){
    std::unique_ptr<shell::model::ModelFacade> modelFacade = std::make_unique<shell::model::ModelFacade>();
    std::unique_ptr<shell::model::variables::Variable> var = shell::model::variables::VariablesFactory::produce("VAR", "/usr:/home/Documents:/libs");
    modelFacade->setVariable("VAR", "/usr:/home/Documents:/libs");
    modelFacade->exportVariable("VAR");
    auto variable = modelFacade->getVariable("VAR");
    BOOST_CHECK_EQUAL_COLLECTIONS(var->getValues_().begin(), var->getValues_().end(),
                                  variable->getValues_().begin(), variable->getValues_().end());

}

BOOST_AUTO_TEST_SUITE_END()



#endif //BOOST_TEST_DYN_LINK