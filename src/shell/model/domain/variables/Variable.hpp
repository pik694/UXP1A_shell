//
// Created by Piotr Żelazko on 02.06.2018.
//

#ifndef UXP1A_SHELL_VARIABLE_HPP
#define UXP1A_SHELL_VARIABLE_HPP

#include <string>
#include <list>

namespace shell::model::variables {

    class Variable {
    public:
        //TODO: getters and setters

    private:
        const std::string name_;

        // TODO: we get a list of values separated by a separator (ex. VARIABLE=value1:value2:value3)
        std::list<std::string> values_;
    };
}


#endif //UXP1A_SHELL_VARIABLE_HPP
