//
// Created by Piotr Żelazko on 02.06.2018.
//

#ifndef UXP1A_SHELL_VARIABLESFACTORY_HPP
#define UXP1A_SHELL_VARIABLESFACTORY_HPP

#include <memory>
#include <shell/model/domain/variables/Variable.hpp>

namespace shell::model::variables {
    class VariablesFactory {
    public:
        static std::unique_ptr<Variable> produce(const std::string &name, const std::string &values) {
            return std::make_unique<shell::model::variables::Variable>(name, values);
        }
    };
}


#endif //UXP1A_SHELL_VARIABLESFACTORY_HPP
