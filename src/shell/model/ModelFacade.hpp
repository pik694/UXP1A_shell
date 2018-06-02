//
// Created by Piotr Żelazko on 02.06.2018.
//

#ifndef UXP1A_SHELL_MODELFACADE_HPP
#define UXP1A_SHELL_MODELFACADE_HPP

#include <shell/model/domain/variables/Variable.hpp>
#include <memory>

namespace shell::model {

    class ModelFacade {
    public:
        //TODO: all methods must be thread safe

        //TODO: overload methods by using different parameters' lists
        //TODO: at this point I cannot foresee parameters' lists

        void setVariable();
        void exportVariable();

        std::unique_ptr<variables::Variable> getVariable(const std::string& name);

    };
}


#endif //UXP1A_SHELL_MODELFACADE_HPP