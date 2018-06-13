//
// Created by Piotr Żelazko on 02.06.2018.
//

#ifndef UXP1A_SHELL_VARIABLE_HPP
#define UXP1A_SHELL_VARIABLE_HPP

#include <string>
#include <list>
#include <boost/algorithm/string.hpp>

namespace shell::model::variables {

    class Variable {
    public:
        Variable();
        Variable(const std::string &name_, const std::string values);
        const std::string &getName_() const;
        const std::list<std::string> &getValues_() const;
        const std::string &getStringValues() const;
        void setValues_(const std::string &values);

    private:
        std::string name_;
        std::list<std::string> values_;
        std::string valuesStr_;
    };
}


#endif //UXP1A_SHELL_VARIABLE_HPP
