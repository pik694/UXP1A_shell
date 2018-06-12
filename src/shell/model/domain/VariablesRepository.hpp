//
// Created by Piotr Żelazko on 02.06.2018.
//

#ifndef UXP1A_SHELL_VARIABLESREPOSITORY_HPP
#define UXP1A_SHELL_VARIABLESREPOSITORY_HPP

#include <string>
#include <shell/model/domain/variables/Variable.hpp>
#include <map>

namespace shell::model {
    class VariablesRepository {
    public:
        void setVariable(shell::model::variables::Variable &variable) {
            variables_[variable.getName_()] = variable;
        }

        shell::model::variables::Variable getVariable(std::string varName) {
            return variables_[varName];
        }

    private:
        std::map<std::string, shell::model::variables::Variable> variables_;
    };
}


#endif //UXP1A_SHELL_VARIABLESREPOSITORY_HPP
