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
        //TODO: overload methods by using different parameters' lists
        //TODO: at this point I cannot foresee parameters' lists
        std::unique_ptr<Variable> produce();
    };
}


#endif //UXP1A_SHELL_VARIABLESFACTORY_HPP
