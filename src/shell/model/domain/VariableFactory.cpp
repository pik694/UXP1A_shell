//
// Created by marcin on 13.06.18.
//

#include "VariablesFactory.hpp"

using namespace shell::model::variables;

std::unique_ptr<Variable> VariablesFactory::produce(const std::string &name, const std::string &values) {
    return std::make_unique<shell::model::variables::Variable>(name, values);
}