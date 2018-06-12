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
        Variable() {}

        Variable(const std::string &name_, const std::string values) : name_(name_), valuesStr_(values) {
            boost::split(values_, values,  boost::is_any_of(":"));
        }

        const std::string &getName_() const {
            return name_;
        }

        const std::list<std::string> &getValues_() const {
            return values_;
        }

        const std::string &getStringValues() const {
            return valuesStr_;
        }

        void setValues_(const std::string &values) {
            boost::split(values_, values,  boost::is_any_of(":"));
        }

    private:
        std::string name_;
        std::list<std::string> values_;
        std::string valuesStr_;
    };
}


#endif //UXP1A_SHELL_VARIABLE_HPP
