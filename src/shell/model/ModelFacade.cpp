//
// Created by Piotr Żelazko on 02.06.2018.
//

#include "ModelFacade.hpp"

using namespace shell::model;

void ModelFacade::setVariable(const std::string &varName, const std::string &varValues) {
    std::unique_ptr<variables::Variable> variable(new variables::Variable(varName, varValues));
    variablesRepository.setVariable(*variable);
}

void ModelFacade::exportVariable(const std::string &varName) {
    setenv(varName.c_str(), variablesRepository.getVariable(varName).getStringValues().c_str(), 1);
}

std::unique_ptr<variables::Variable>  ModelFacade::getVariable(const std::string &name) {
    std::unique_ptr<variables::Variable> variable(new variables::Variable(variablesRepository.getVariable(name)));
    if (variable->getName_() == ""){
        return std::unique_ptr<variables::Variable>(new variables::Variable(name, getenv(name.c_str())));
    } else {
        return variable;
    }

}

ModelFacade::ModelFacade(const VariablesRepository &variablesRepository) : variablesRepository(variablesRepository) {}
