//
// Created by marcin on 13.06.18.
//

#include "Variable.hpp"

using namespace shell::model::variables;

Variable::Variable() {}

Variable::Variable(const std::string &name_, const std::string values) : name_(name_), valuesStr_(values) {
    boost::split(values_, values,  boost::is_any_of(":"));
}

const std::string &Variable::getName_() const {
    return name_;
}

const std::list<std::string> &Variable::getValues_() const {
    return values_;
}

const std::string &Variable::getStringValues() const {
    return valuesStr_;
}

void Variable::setValues_(const std::string &values) {
    boost::split(values_, values,  boost::is_any_of(":"));
}