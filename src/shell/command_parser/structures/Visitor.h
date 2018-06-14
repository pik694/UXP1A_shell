//
// Created by Daniel Bigos on 14.06.18.
//

#include <shell/tasks/domain/tasks/Task.hpp>

namespace shell::parser::structures
{
    class AbstractSyntaxTree;
    class Assignment;
    class Command;
    class CommandList;
    class Err;
    class ErrAppend;
    class ErrRedirection;
    class HereDocument;
    class InRedirection;
    class Out;
    class OutAppend;
    class OutRedirection;
    class Pipeline;
    class Redirection;
}

#ifndef UXP1A_SHELL_VISITOR_H
#define UXP1A_SHELL_VISITOR_H

#include <memory>

namespace shell::parser::structures
{
    class Visitor
    {
    public:
        explicit Visitor() = default;
        virtual ~Visitor() = default;

        virtual std::unique_ptr<shell::tasks::Task> visit( Assignment &assignment ) = 0;
        virtual std::unique_ptr<shell::tasks::Task> visit( Pipeline &pipeline ) = 0;
        virtual std::unique_ptr<shell::tasks::Task> visit( HereDocument &here_document ) = 0;

    };
}

#endif //UXP1A_SHELL_VISITOR_H
