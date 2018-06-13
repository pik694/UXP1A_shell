//
// Created by marcin on 13.06.18.
//

#include <shell/model/domain/variables/Variable.hpp>
#include "VariablesRepository.hpp"

using namespace shell::model;

void VariablesRepository::setVariable(shell::model::variables::Variable &variable) {
    std::lock_guard guard(variablesMutex_);
    variables_[variable.getName_()] = variable;
}

shell::model::variables::Variable VariablesRepository::getVariable(std::string varName) {
    std::lock_guard guard(variablesMutex_);
    return variables_[varName];
}