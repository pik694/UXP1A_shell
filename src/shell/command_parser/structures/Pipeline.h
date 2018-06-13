//
// Created by Daniel Bigos on 12.06.18.
//

#ifndef UXP1A_SHELL_PIPELINE_H
#define UXP1A_SHELL_PIPELINE_H

#include <list>
#include <memory>
#include "AbstractSyntaxTree.hpp"
#include "ProgramExecution.h"

namespace shell::parser::structures
{
    class Pipeline : public AbstractSyntaxTree
    {
    public:
        explicit Pipeline() = default;
        virtual ~Pipeline() = default;

        std::list< std::unique_ptr< ProgramExecution > > &getPrograms();
        void addProgram( std::unique_ptr< ProgramExecution > & );
    private:
        std::list< std::unique_ptr< ProgramExecution > > programs_;
    };

}
#endif //UXP1A_SHELL_PIPELINE_H
