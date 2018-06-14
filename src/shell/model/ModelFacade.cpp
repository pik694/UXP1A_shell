//
// Created by Piotr Żelazko on 02.06.2018.
//

#include <shell/model/domain/VariablesFactory.hpp>
#include "ModelFacade.hpp"

using namespace shell::model;

void ModelFacade::setVariable(const std::string &varName, const std::string &varValues) {
    std::unique_ptr<variables::Variable> variable = variables::VariablesFactory::produce(varName, varValues);
    variablesRepository_->setVariable(*variable);
}

void ModelFacade::exportVariable(const std::string &varName) {
    setenv(varName.c_str(), variablesRepository_->getVariable(varName).getStringValues().c_str(), 1);
}

std::unique_ptr<variables::Variable>  ModelFacade::getVariable(const std::string &name) {
    std::unique_ptr<variables::Variable> variable(new variables::Variable(variablesRepository_->getVariable(name)));
    if (variable->getName_() == ""){
        char *env = getenv(name.c_str());
        return std::unique_ptr<variables::Variable>(new variables::Variable(name, env != nullptr ? env : "" ));
    } else {
        return variable;
    }

}

ModelFacade::ModelFacade() {
    variablesRepository_ = new VariablesRepository();
}
