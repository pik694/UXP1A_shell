//
// Created by Piotr Żelazko on 02.06.2018.
//

#ifndef UXP1A_SHELL_MODELFACADE_HPP
#define UXP1A_SHELL_MODELFACADE_HPP

#include <shell/model/domain/variables/Variable.hpp>
#include <memory>
#include <shell/model/domain/VariablesRepository.hpp>

namespace shell::model {

    class ModelFacade {
    private:
        VariablesRepository variablesRepository;
    public:
        ModelFacade(const VariablesRepository &variablesRepository);
        void setVariable(const std::string &varName, const std::string &varValues);
        void exportVariable(const std::string &varName);
        std::unique_ptr<variables::Variable> getVariable(const std::string& name);

    };
}


#endif //UXP1A_SHELL_MODELFACADE_HPP